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

#ifndef OSAL_LIB_LISTS_C_
#define OSAL_LIB_LISTS_C_
#endif

#ifndef OSAL_H_
#include "osal.h"
#endif

#ifndef OSAL_LIB_LISTS_INTERNAL_H_
#include "osal_lib_lists_internal.h"
#endif

void OSAL_List_Leaf_Init(void *leaf)
{
   ((OSAL_List_XT*)leaf)->previous = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);
   ((OSAL_List_XT*)leaf)->next     = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);
} /* OSAL_List_Leaf_Init */

void *OSAL_List_Find_By_Number(void *first_leaf, uint32_t id_offset, uint_fast8_t id_mask, uint32_t id_number)
{
   OSAL_List_XT  *leaf = (OSAL_List_XT*)first_leaf;
   uint32_t       id;

   OSAL_ENTER_FUNC(OSAL_DBG_LISTS);

   while(OSAL_CHECK_PTR(OSAL_List_XT, leaf))
   {
      id = ((uint32_t*)(&((uint8_t*)leaf)[id_offset]))[0] & id_mask;

      if(id_number == id)
      {
         break;
      }

      leaf = leaf->next;
   }

   OSAL_EXIT_FUNC(OSAL_DBG_LISTS);

   return leaf;
} /* OSAL_List_Find_By_Number */

void *OSAL_List_Find_By_String(void *first_leaf, uint32_t id_offset, const char *id_string, uint32_t offset)
{
   OSAL_List_XT  *leaf = (OSAL_List_XT*)first_leaf;
   const char    *string;
   uint32_t       pos;

   OSAL_ENTER_FUNC(OSAL_DBG_LISTS);

   while(OSAL_CHECK_PTR(OSAL_List_XT, leaf))
   {
      string  = ((const char**)(&((uint8_t*)leaf)[id_offset]))[0];
      string += offset;

      for(pos = 0; (string[pos] == id_string[pos]) && ('\0' != string[pos]); ++pos)
      {
         ;
      }

      /* item compare passed - we found it */
      if(('\0' == string[pos]) && ('\0' == id_string[pos]))
      {
         break;
      }

      leaf = leaf->next;
   }

   OSAL_EXIT_FUNC(OSAL_DBG_LISTS);

   return leaf;
} /* OSAL_List_Find_By_String */

void *OSAL_List_Find_By_String_Terminated(
   void *first_leaf, uint32_t id_offset, const char *id_string, char terminate_char, uint32_t offset, uint32_t *ret_offset)
{
   OSAL_List_XT  *leaf = (OSAL_List_XT*)first_leaf;
   const char    *string;
   uint32_t       pos = 0;

   OSAL_ENTER_FUNC(OSAL_DBG_LISTS);

   while(OSAL_CHECK_PTR(OSAL_List_XT, leaf))
   {
      string  = ((const char**)(&((uint8_t*)leaf)[id_offset]))[0];
      string += offset;

      for(pos = 0; (string[pos] == id_string[pos]) && ('\0' != string[pos]); ++pos)
      {
         ;
      }

      if('\0' == string[pos])
      {
         /* item compare passed - we found it */
         if('\0' == id_string[pos])
         {
            break;
         }
         else if(terminate_char == id_string[pos])
         {
            ++pos;
            break;
         }
      }

      leaf = leaf->next;
   }

   if(OSAL_CHECK_PTR(OSAL_List_XT, leaf) && OSAL_CHECK_PTR(uint32_t, ret_offset))
   {
      *ret_offset = pos;
   }

   OSAL_EXIT_FUNC(OSAL_DBG_LISTS);

   return leaf;
} /* OSAL_List_Find_By_String_Terminated */

void *OSAL_List_Find_By_Vendor(void *first_leaf, OSAL_List_Vendor_Compare_HT compare, void *params)
{
   OSAL_List_XT *leaf = (OSAL_List_XT*)first_leaf;

   OSAL_ENTER_FUNC(OSAL_DBG_LISTS);

   while(OSAL_CHECK_PTR(OSAL_List_XT, leaf))
   {
      if(OSAL_BOOL_IS_TRUE(OSAL_CALL_HANDLER(OSAL_List_Vendor_Compare_HT, compare)(leaf, params)))
      {
         break;
      }

      leaf = leaf->next;
   }

   OSAL_EXIT_FUNC(OSAL_DBG_LISTS);

   return leaf;
} /* OSAL_List_Find_By_Vendor */

static OSAL_Bool_DT OSAL_List_add_by_number_growing(OSAL_List_XT *leaf, OSAL_List_add_by_number_params_DT *params)
{
   uint32_t id = ((uint32_t*)(&((uint8_t*)leaf)[params->id_offset]))[0] & params->id_mask;

   return (params->new_leaf_id < id);
} /* OSAL_List_add_by_number_growing */

static OSAL_Bool_DT OSAL_List_add_by_number_falling(OSAL_List_XT *leaf, OSAL_List_add_by_number_params_DT *params)
{
   uint32_t id = ((uint32_t*)(&((uint8_t*)leaf)[params->id_offset]))[0] & params->id_mask;

   return (params->new_leaf_id > id);
} /* OSAL_List_add_by_number_falling */

void OSAL_List_Add_By_Number(void *first_leaf_ptr, void *new_leaf, uint32_t id_offset, uint_fast8_t id_mask, OSAL_Bool_DT order_growing)
{
   OSAL_List_add_by_number_params_DT params;

   OSAL_ENTER_FUNC(OSAL_DBG_LISTS);

   params.new_leaf_id   = ((uint32_t*)(&((uint8_t*)new_leaf)[id_offset]))[0] & id_mask;
   params.id_offset     = id_offset;
   params.id_mask       = id_mask;

   OSAL_List_Add_By_Vendor(
      first_leaf_ptr,
      new_leaf,
      (OSAL_List_Vendor_Compare_HT)(OSAL_BOOL_IS_TRUE(order_growing) ? OSAL_List_add_by_number_growing : OSAL_List_add_by_number_falling),
      &params);

   OSAL_EXIT_FUNC(OSAL_DBG_LISTS);
} /* OSAL_List_Add_By_Number */

OSAL_Bool_DT OSAL_List_add_by_string_growing(OSAL_List_XT *leaf, OSAL_List_add_by_string_params_DT *params)
{
   const char *string  = ((const char**)(&((uint8_t*)leaf)[params->id_offset]))[0];
   uint32_t    pos;

   string += params->offset;

   for(pos = 0; (string[pos] == params->new_leaf_string[pos]) && ('\0' != string[pos]); ++pos)
   {
      ;
   }

   return (params->new_leaf_string[pos] < (string[pos]));
} /* OSAL_List_add_by_string_growing */

OSAL_Bool_DT OSAL_List_add_by_string_falling(OSAL_List_XT *leaf, OSAL_List_add_by_string_params_DT *params)
{
   const char *string  = ((const char**)(&((uint8_t*)leaf)[params->id_offset]))[0];
   uint32_t    pos;

   string += params->offset;

   for(pos = 0; (string[pos] == params->new_leaf_string[pos]) && ('\0' != string[pos]); ++pos)
   {
      ;
   }

   return (params->new_leaf_string[pos] > (string[pos]));
} /* OSAL_List_add_by_string_falling */

void OSAL_List_Add_By_String(void *first_leaf_ptr, void *new_leaf, uint32_t id_offset, uint32_t offset, OSAL_Bool_DT order_growing)
{
   OSAL_List_add_by_string_params_DT params;

   OSAL_ENTER_FUNC(OSAL_DBG_LISTS);

   params.new_leaf_string  = ((const char**)(&((uint8_t*)new_leaf)[id_offset]))[0];
   params.id_offset        = id_offset;
   params.offset           = offset;

   OSAL_List_Add_By_Vendor(
      first_leaf_ptr,
      new_leaf,
      (OSAL_List_Vendor_Compare_HT)(OSAL_BOOL_IS_TRUE(order_growing) ? OSAL_List_add_by_string_growing : OSAL_List_add_by_string_falling),
      &params);

   OSAL_EXIT_FUNC(OSAL_DBG_LISTS);
} /* OSAL_List_Add_By_String */

void OSAL_List_Add_By_Vendor(void *first_leaf_ptr, void *new_leaf, OSAL_List_Vendor_Compare_HT compare, void *params)
{
   OSAL_List_XT  *previous          = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);
   OSAL_List_XT **previous__pnext   = (OSAL_List_XT**)first_leaf_ptr;
   OSAL_List_XT  *leaf_to_add       = new_leaf;
   OSAL_List_XT  *leaf;

   OSAL_ENTER_FUNC(OSAL_DBG_LISTS);

   leaf = *(OSAL_List_XT**)first_leaf_ptr;

   while(OSAL_CHECK_PTR(OSAL_List_XT, leaf))
   {
      if(OSAL_BOOL_IS_TRUE(OSAL_CALL_HANDLER(OSAL_List_Vendor_Compare_HT, compare)(leaf, params)))
      {
         *previous__pnext     = leaf_to_add;
         leaf_to_add->previous= previous;
         leaf_to_add->next    = leaf;
         leaf->previous       = leaf_to_add;
         leaf_to_add          = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);
         break;
      }

      previous__pnext= &(leaf->next);
      previous       = leaf;
      leaf           = leaf->next;
   }

   if(OSAL_CHECK_PTR(OSAL_List_XT, leaf_to_add))
   {
      *previous__pnext     = leaf_to_add;
      leaf_to_add->previous= previous;
      leaf_to_add->next    = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_LISTS);
} /* OSAL_List_Add_By_Vendor */

void OSAL_List_Remove_Leaf(void *first_leaf_ptr, void *leaf, OSAL_List_Free_Leaf_HT free_func)
{
   OSAL_List_XT  *leaf_to_remove = leaf;

   OSAL_ENTER_FUNC(OSAL_DBG_LISTS);

   if(OSAL_CHECK_PTR(OSAL_List_XT, leaf_to_remove))
   {
      if(OSAL_CHECK_PTR(OSAL_List_XT, leaf_to_remove->previous) && OSAL_CHECK_PTR(OSAL_List_XT, leaf_to_remove->next))
      {
         leaf_to_remove->previous->next   = leaf_to_remove->next;
         leaf_to_remove->next->previous   = leaf_to_remove->previous;
      }
      else if(OSAL_CHECK_PTR(OSAL_List_XT, leaf_to_remove->previous))
      {
         leaf_to_remove->previous->next = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);
      }
      else if(OSAL_CHECK_PTR(OSAL_List_XT, leaf_to_remove->next))
      {
         leaf_to_remove->next->previous   = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);
         *(OSAL_List_XT**)first_leaf_ptr  = leaf_to_remove->next;
      }
      else if(OSAL_CHECK_PTR(OSAL_List_XT, *(OSAL_List_XT**)first_leaf_ptr))
      {
         *(OSAL_List_XT**)first_leaf_ptr  = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);
      }
      leaf_to_remove->previous = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);
      leaf_to_remove->next     = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);

      OSAL_CHECK_AND_CALL_HANDLER(OSAL_List_Free_Leaf_HT, free_func)(leaf_to_remove);

   }

   OSAL_EXIT_FUNC(OSAL_DBG_LISTS);
} /* OSAL_List_Remove_Leaf */

void OSAL_List_Clear_List(void *first_leaf_ptr, OSAL_List_Free_Leaf_HT free_func)
{
   OSAL_List_XT *next_leaf;
   OSAL_List_XT *leaf;

   OSAL_ENTER_FUNC(OSAL_DBG_LISTS);

   leaf = *(OSAL_List_XT**)first_leaf_ptr;

   while(OSAL_CHECK_PTR(OSAL_List_XT, leaf))
   {
      next_leaf = leaf->next;

      leaf->previous = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);
      leaf->next     = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);

      OSAL_CHECK_AND_CALL_HANDLER(OSAL_List_Free_Leaf_HT, free_func)(leaf);

      leaf = next_leaf;
   }

   *(OSAL_List_XT**)first_leaf_ptr  = OSAL_MAKE_INVALID_PTR(OSAL_List_XT);

   OSAL_EXIT_FUNC(OSAL_DBG_LISTS);
} /* OSAL_List_Clear_List */

