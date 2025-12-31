/** ---------------------------------------- LICENSE SECTION -------------------------------------------------------------------
 *
 * Copyright (c) 2025 Piotr Wojtowicz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * -----------------------------------------------------------------------------------------------------------------------------
 */

#ifndef OSAL_LIB_TREES_C_
#define OSAL_LIB_TREES_C_
#endif

#ifndef OSAL_H_
#include "osal.h"
#endif

#ifndef OSAL_LIB_LISTS_INTERNAL_H_
#include "osal_lib_lists_internal.h"
#endif

typedef struct
{
   /* MUST BE FIRST IN THE STRUCTURE */
   OSAL_List_add_by_string_params_DT list;
   OSAL_Tree_Allocate_Sub_Branch_String_HT sub_branch_allocator;
   void          *new_leaf;
   char           branch_separator;
   uint32_t       offset_to_be_added;
}OSAL_add_by_string_params_DT;

void OSAL_Tree_Leaf_Init(void *leaf)
{
   ((OSAL_Tree_XT*)leaf)->list.previous = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);
   ((OSAL_Tree_XT*)leaf)->list.next     = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);
   ((OSAL_Tree_XT*)leaf)->branch_first  = OSAL_MAKE_INVALID_PTR(OSAL_Tree_XT);
} /* OSAL_Tree_Leaf_Init */

void *OSAL_Tree_Find_By_String(void *first_leaf, uint32_t id_offset, const char *id_string, char branch_separator)
{
   OSAL_Tree_XT  *item = (OSAL_Tree_XT*)first_leaf;
   uint32_t       string_offset = 0;
   uint32_t       ret_string_offset = 0;

   OSAL_ENTER_FUNC(OSAL_DBG_TREES);

   while(OSAL_CHECK_PTR(OSAL_Tree_XT, item))
   {
      item = OSAL_List_Find_By_String_Terminated(
         item, id_offset, &id_string[string_offset], branch_separator, string_offset, &ret_string_offset);

      if(OSAL_CHECK_PTR(OSAL_Tree_XT, item))
      {
         string_offset += ret_string_offset;

         if('\0' == id_string[string_offset])
         {
            break;
         }
         else
         {
            item = item->branch_first;
         }
      }
   }

   OSAL_EXIT_FUNC(OSAL_DBG_TREES);

   return item;
} /* OSAL_Tree_Find_By_String */

void *OSAL_Tree_Find_By_Vendor(void *first_leaf, OSAL_Tree_Vendor_Compare_HT compare, void *params)
{
   OSAL_Tree_XT *item = (OSAL_Tree_XT*)first_leaf;
   OSAL_Tree_Vendor_Compare_Result_ET compare_result;

   OSAL_ENTER_FUNC(OSAL_DBG_TREES);

   while(OSAL_CHECK_PTR(OSAL_Tree_XT, item))
   {
      compare_result = OSAL_CALL_HANDLER(OSAL_Tree_Vendor_Compare_HT, compare)(item, params);

      if(OSAL_TREE_LEAF_COMPARE_MATCH == compare_result)
      {
         break;
      }
      else if(OSAL_TREE_LEAF_COMPARE_BRANCH == compare_result)
      {
         item = item->branch_first;
      }
      else
      {
         item = (OSAL_Tree_XT*)(item->list.next);
      }
   }

   OSAL_EXIT_FUNC(OSAL_DBG_TREES);

   return item;
} /* OSAL_Tree_Find_By_Vendor */

static OSAL_Tree_Vendor_Compare_Result_ET OSAL_add_by_string_search_compare(OSAL_List_XT *leaf, OSAL_add_by_string_params_DT *params)
{
   const char    *string;
   uint32_t       pos;
   OSAL_Tree_Vendor_Compare_Result_ET result = OSAL_TREE_LEAF_COMPARE_NOT_MATCH;

   OSAL_ENTER_FUNC(OSAL_DBG_TREES);

   string  = ((const char**)(&((uint8_t*)leaf)[params->list.id_offset]))[0];
   string += params->list.offset;

   for(pos = 0; (string[pos] == params->list.new_leaf_string[pos]) && ('\0' != string[pos]); ++pos)
   {
      ;
   }

   if('\0' == string[pos])
   {
      if('\0' != params->list.new_leaf_string[pos])
      {
         if(params->branch_separator == params->list.new_leaf_string[pos])
         {
            ++pos;
            result = OSAL_TREE_LEAF_COMPARE_BRANCH;
            params->list.offset          += pos;
         }
      }
      /* item compare passed - we found it */
      else
      {
         result = OSAL_TREE_LEAF_COMPARE_MATCH;
      }
   }

   OSAL_EXIT_FUNC(OSAL_DBG_TREES);

   return result;
} /* OSAL_add_by_string_search_compare */

static OSAL_Tree_Vendor_Add_Analyzer_Result_ET OSAL_add_by_string_add_analyzer(OSAL_Tree_XT *list_first_leaf, OSAL_add_by_string_params_DT *params)
{
   const char   **new_leaf_id_container;
   uint32_t       pos;
   OSAL_Tree_Vendor_Add_Analyzer_Result_ET result = OSAL_TREE_LEAF_ADD_DIRECTLY;

   OSAL_UNUSED_PARAM(list_first_leaf);

   OSAL_ENTER_FUNC(OSAL_DBG_TREES);

   params->list.offset       += params->offset_to_be_added;
   params->offset_to_be_added = 0;

   for(pos = params->list.offset; ('\0' != params->list.new_leaf_string[pos]); ++pos)
   {
      if(params->branch_separator == params->list.new_leaf_string[pos])
      {
         ++pos;
         result = OSAL_TREE_LEAF_ADD_BRANCH;
         /**
          * pos will be added at next call of this function because OSAL_Tree_Add_By_Vendor will now allocate new branch
          * but that branch will be added to the parent branch with old offset value.
          */
         params->offset_to_be_added = pos;
         break;
      }
   }

   if(OSAL_TREE_LEAF_ADD_DIRECTLY == result)
   {
      new_leaf_id_container = (const char**)(&((uint8_t*)params->new_leaf)[params->list.id_offset]);
      if(*new_leaf_id_container != params->list.new_leaf_string)
      {
         *new_leaf_id_container = params->list.new_leaf_string;
      }
   }

   OSAL_EXIT_FUNC(OSAL_DBG_TREES);

   return result;
} /* OSAL_add_by_string_add_analyzer */

static void* OSAL_add_by_string_sub_branch_allocator_string(OSAL_Tree_XT *list_first_leaf, OSAL_add_by_string_params_DT *params)
{
   OSAL_Tree_XT* result;

   OSAL_ENTER_FUNC(OSAL_DBG_TREES);

   result = OSAL_CALL_HANDLER(OSAL_Tree_Allocate_Sub_Branch_String_HT, params->sub_branch_allocator)(
      list_first_leaf, params->list.new_leaf_string, params->list.offset, params->offset_to_be_added, params->list.id_offset);

   OSAL_EXIT_FUNC(OSAL_DBG_TREES);

   return result;
} /* OSAL_add_by_string_sub_branch_allocator_string */


uint32_t OSAL_Tree_Add_By_String(
   void                                   *first_leaf_ptr,
   void                                   *new_leaf,
   uint32_t                                id_offset,
   uint32_t                                offset,
   const char                             *full_path,
   char                                    branch_separator,
   OSAL_Tree_Allocate_Sub_Branch_String_HT sub_branch_allocator,
   OSAL_Bool_DT                            order_growing)
{
   OSAL_add_by_string_params_DT params;

   OSAL_ENTER_FUNC(OSAL_DBG_TREES);

   if(OSAL_CHECK_PTR(const char, full_path))
   {
      params.list.new_leaf_string   = full_path;
   }
   else
   {
      params.list.new_leaf_string   = ((const char**)(&((uint8_t*)new_leaf)[id_offset]))[0];
   }
   params.list.id_offset         = id_offset;
   params.list.offset            = offset;
   params.branch_separator       = branch_separator;
   params.new_leaf               = new_leaf;
   params.sub_branch_allocator   = sub_branch_allocator;
   params.offset_to_be_added     = 0;

   OSAL_Tree_Add_By_Vendor(
      first_leaf_ptr,
      new_leaf,
      (OSAL_Tree_Vendor_Compare_HT)OSAL_add_by_string_search_compare,
      (OSAL_List_Vendor_Compare_HT)(OSAL_BOOL_IS_TRUE(order_growing) ? OSAL_List_add_by_string_growing : OSAL_List_add_by_string_falling),
      (OSAL_Tree_Vendor_Add_Analyzer_HT)OSAL_add_by_string_add_analyzer,
      (OSAL_Tree_Allocate_Sub_Branch_Vendor_HT)OSAL_add_by_string_sub_branch_allocator_string,
      &params);

   OSAL_EXIT_FUNC(OSAL_DBG_TREES);

   return params.list.offset;
} /* OSAL_Tree_Add_By_String */

void OSAL_Tree_Add_By_Vendor(
   void                                   *first_leaf_ptr,
   void                                   *new_leaf,
   OSAL_Tree_Vendor_Compare_HT             search_compare,
   OSAL_List_Vendor_Compare_HT             add_compare,
   OSAL_Tree_Vendor_Add_Analyzer_HT        add_analyzer,
   OSAL_Tree_Allocate_Sub_Branch_Vendor_HT sub_branch_allocator,
   void                                   *params)
{
   OSAL_Tree_XT                            **parent_branch_first = (OSAL_Tree_XT**)first_leaf_ptr;
   OSAL_Tree_XT                             *item;
#if(OSAL_FEATURE_PRESENT == OSAL_TREE_SUPPORT_LEAFS_REMOVING)
   OSAL_Tree_XT                             *parent = OSAL_MAKE_INVALID_PTR(OSAL_Tree_XT);
#endif
   OSAL_Tree_Vendor_Compare_Result_ET        compare_result;
   OSAL_Tree_Vendor_Add_Analyzer_Result_ET   add_analyzer_result;

   OSAL_ENTER_FUNC(OSAL_DBG_TREES);

   item = *parent_branch_first;

   while(OSAL_CHECK_PTR(OSAL_Tree_XT, item))
   {
      compare_result = OSAL_CALL_HANDLER(OSAL_Tree_Vendor_Compare_HT, search_compare)(item, params);

      if(OSAL_TREE_LEAF_COMPARE_BRANCH == compare_result)
      {
#if(OSAL_FEATURE_PRESENT == OSAL_TREE_SUPPORT_LEAFS_REMOVING)
         parent               = item;
#endif
         parent_branch_first  = &(item->branch_first);
         item                 = *parent_branch_first;
      }
      else
      {
         item = (OSAL_Tree_XT*)(item->list.next);
      }
   }

   while(OSAL_CHECK_PTR(OSAL_Tree_XT*, parent_branch_first))
   {
      add_analyzer_result = OSAL_CALL_HANDLER(OSAL_Tree_Vendor_Add_Analyzer_HT, add_analyzer)(*parent_branch_first, params);

      if(OSAL_TREE_LEAF_ADD_DIRECTLY == add_analyzer_result)
      {
         OSAL_List_Add_By_Vendor(parent_branch_first, new_leaf, add_compare, params);
#if(OSAL_FEATURE_PRESENT == OSAL_TREE_SUPPORT_LEAFS_REMOVING)
         ((OSAL_Tree_XT*)new_leaf)->parent = parent;
#endif
         break;
      }
      else /* OSAL_TREE_LEAF_ADD_BRANCH */
      {
         item = (OSAL_Tree_XT*)OSAL_CALL_HANDLER(OSAL_Tree_Allocate_Sub_Branch_Vendor_HT, sub_branch_allocator)(*parent_branch_first, params);
         if(OSAL_CHECK_PTR(OSAL_Tree_XT, item))
         {
            OSAL_List_Add_By_Vendor(parent_branch_first, item, add_compare, params);
#if(OSAL_FEATURE_PRESENT == OSAL_TREE_SUPPORT_LEAFS_REMOVING)
            item->parent         = parent;
            parent               = item;
#endif
            parent_branch_first  = &(item->branch_first);
         }
         else
         {
            /* ERROR */
            parent_branch_first = OSAL_MAKE_INVALID_PTR(OSAL_Tree_XT*);
            break;
         }
      }
   }

   OSAL_EXIT_FUNC(OSAL_DBG_TREES);
} /* OSAL_Tree_Add_By_Vendor */

#if(OSAL_FEATURE_PRESENT == OSAL_TREE_SUPPORT_LEAFS_REMOVING)

void OSAL_Tree_Remove_Leaf(void *first_leaf_ptr, void *leaf, OSAL_Tree_Free_Leaf_HT free_func)
{
   OSAL_Tree_XT *leaf_to_remove = leaf;
   OSAL_Tree_XT *parent;

   OSAL_ENTER_FUNC(OSAL_DBG_TREES);

   if(OSAL_CHECK_PTR(OSAL_Tree_XT, leaf_to_remove))
   {
      parent = leaf_to_remove->parent;

      if(OSAL_CHECK_PTR(OSAL_Tree_XT, leaf_to_remove->branch_first))
      {
         OSAL_Tree_Clear_List(&(leaf_to_remove->branch_first), free_func);

         leaf_to_remove->branch_first = OSAL_MAKE_INVALID_PTR(OSAL_Tree_XT);
      }

      if(OSAL_CHECK_PTR(OSAL_Tree_XT, parent))
      {
         OSAL_List_Remove_Leaf(&(parent->branch_first), leaf, free_func);
      }
      else
      {
         OSAL_List_Remove_Leaf(first_leaf_ptr, leaf, free_func);
      }
   }

   OSAL_EXIT_FUNC(OSAL_DBG_TREES);
} /* OSAL_Tree_Remove_Leaf */

void OSAL_Tree_Clear_List(void *first_leaf_ptr, OSAL_Tree_Free_Leaf_HT free_func)
{
   OSAL_Tree_XT *leaf_next;
   OSAL_Tree_XT *leaf_to_remove;

   OSAL_ENTER_FUNC(OSAL_DBG_TREES);

   leaf_to_remove = *((OSAL_Tree_XT**)first_leaf_ptr);

   while(OSAL_CHECK_PTR(OSAL_Tree_XT, leaf_to_remove))
   {
      if(OSAL_CHECK_PTR(OSAL_Tree_XT, leaf_to_remove->branch_first))
      {
         OSAL_Tree_Clear_List(&(leaf_to_remove->branch_first), free_func);

         leaf_to_remove->branch_first = OSAL_MAKE_INVALID_PTR(OSAL_Tree_XT);
      }

      leaf_next = (OSAL_Tree_XT*)(leaf_to_remove->list.next);

      leaf_to_remove->list.previous = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);
      leaf_to_remove->list.next     = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);

      OSAL_CHECK_AND_CALL_HANDLER(OSAL_Tree_Free_Leaf_HT, free_func)(leaf_to_remove);

      leaf_to_remove = leaf_next;
   }

   *(OSAL_Tree_XT**)first_leaf_ptr  = OSAL_MAKE_INVALID_PTR(OSAL_Tree_XT);

   OSAL_EXIT_FUNC(OSAL_DBG_TREES);
} /* OSAL_Tree_Clear_List */

#endif

