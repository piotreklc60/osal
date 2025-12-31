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

#ifndef OSAL_CONTEXT_C_
#define OSAL_CONTEXT_C_
#endif

#ifndef OSAL_H_
#include "osal.h"
#endif

#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)

#ifndef OSAL_NUM_PRE_ALOCATED_BRANCHES
#error "Please define OSAL_NUM_PRE_ALOCATED_BRANCHES. This definition is used to allocate branches statically"
#endif

#ifndef OSAL_NUM_PRE_ALOCATED_BRANCHES_DESC_BUF
#error "Please define OSAL_NUM_PRE_ALOCATED_BRANCHES_DESC_BUF. This definition is used to allocate branches description buffers statically"
#endif

#endif

typedef struct
{
   OSAL_Interrupt_Params_XT interrupts[OSAL_NUM_INTERRUPTS];
   OSAL_Thread_Params_XT    threads[OSAL_NUM_THREADS];
   uint_fast16_t num_installed_threads;
   uint_fast16_t critical_global_cntr_isr;
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
   OSAL_Context_Tracking_Params_XT *tree_first;
   OSAL_Context_Tracking_Params_XT  tree_branches[OSAL_NUM_PRE_ALOCATED_BRANCHES];
   char                             tree_branches_desc[OSAL_NUM_PRE_ALOCATED_BRANCHES_DESC_BUF];
   OSAL_Context_Unique_Id_DT        tree_branches_num_used_elems;
   size_t                           tree_branches_desc_num_used_elems;
   OSAL_Bool_DT                     init_ongoing;
#endif
   OSAL_Bool_DT                     scheduler_started;
}osal_context_data_xt;

static const char* const osal_context_type_names[OSAL_MAX_NUM_CONTEXT_TYPES] = {"Task", "Irq "};
static osal_context_data_xt osal_context;

#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)

static void OSAL_context_execute(
   OSAL_Hvoid_Two_Params_HT action, void *params, OSAL_Context_Tracking_Params_XT *item)
{
   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   while(OSAL_CHECK_PTR(OSAL_Context_Tracking_Params_XT, item))
   {
      if((item->context_id.id > 0) && (item->context_id.id < (osal_context.num_installed_threads + OSAL_NUM_INTERRUPTS)))
      {
         OSAL_CALL_HANDLER(OSAL_Hvoid_Two_Params_HT, action)(item, params);
      }
      if(OSAL_TREE_CHECK_CHILD_LEAF(osal_context.tree_first, item))
      {
         /* do for all children */
         OSAL_context_execute(action, params, (OSAL_Context_Tracking_Params_XT*)OSAL_TREE_GET_CHILD_LEAF(osal_context.tree_first, item));
      }

      if(OSAL_TREE_CHECK_NEXT_LEAF(osal_context.tree_first, item))
      {
         item = (OSAL_Context_Tracking_Params_XT*)OSAL_TREE_GET_NEXT_LEAF(osal_context.tree_first, item);
      }
      else
      {
         item = OSAL_MAKE_INVALID_PTR(OSAL_Context_Tracking_Params_XT);
      }
   }

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);
} /* OSAL_context_execute */

static void* osal_context_tree_branches_allocator(
   OSAL_Tree_XT *list_first_leaf, const char *string, uint32_t offset, uint32_t string_len, uint32_t id_offset)
{
   char *path;
   OSAL_Context_Tracking_Params_XT *result;
   OSAL_Bool_DT dynamically_allocated = OSAL_FALSE;
   OSAL_Bool_DT path_dynamically_allocated = OSAL_FALSE;

   OSAL_UNUSED_PARAM(list_first_leaf);
   OSAL_UNUSED_PARAM(offset);
   OSAL_UNUSED_PARAM(id_offset);

   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   if((osal_context.tree_branches_num_used_elems < Num_Elems(osal_context.tree_branches))
      && OSAL_BOOL_IS_TRUE(osal_context.init_ongoing))
   {
      result = &osal_context.tree_branches[osal_context.tree_branches_num_used_elems++];
   }
   else
   {
      result = OSAL_Malloc(sizeof(OSAL_Context_Tracking_Params_XT));
      dynamically_allocated = OSAL_TRUE;

      if(OSAL_BOOL_IS_TRUE(osal_context.init_ongoing))
      {
         OSAL_WARN_3(OSAL_DBG_CONTEXT_INVALID_PARAMS, "allocated branch%s buf for IRQ %.*s using malloc!",
            "", string_len, string);
      }
   }

   if(OSAL_CHECK_PTR(OSAL_Context_Tracking_Params_XT, result))
   {
      memset(result, 0, sizeof(*result));

      result->flags.dynamically_allocated = dynamically_allocated;

      if(((sizeof(osal_context.tree_branches_desc) - osal_context.tree_branches_desc_num_used_elems) >= string_len)
         && OSAL_BOOL_IS_TRUE(osal_context.init_ongoing))
      {
         path = &osal_context.tree_branches_desc[osal_context.tree_branches_desc_num_used_elems];
         osal_context.tree_branches_desc_num_used_elems += string_len;
      }
      else
      {
         path = OSAL_Malloc(string_len);
         path_dynamically_allocated = OSAL_TRUE;
         if(OSAL_BOOL_IS_TRUE(osal_context.init_ongoing))
         {
            OSAL_WARN_3(OSAL_DBG_CONTEXT_INVALID_PARAMS, "allocated branch%s buf for IRQ %.*s using malloc!",
               " description", string_len, string);
         }
      }

      if(OSAL_CHECK_PTR(char, path))
      {
         result->flags.path_dynamically_allocated = path_dynamically_allocated;
         string_len--;
         memcpy(path, string, string_len);
         path[string_len] = '\0';

         result->context_id.path = path;
      }
      else
      {
         if(OSAL_BOOL_IS_TRUE(dynamically_allocated))
         {
            OSAL_Free(result);
         }
         result = OSAL_MAKE_INVALID_PTR(OSAL_Context_Tracking_Params_XT);

         OSAL_EMERG(OSAL_DBG_CONTEXT_INVALID_PARAMS, "branch allocation failed!");
      }
   }
   else
   {
      OSAL_EMERG(OSAL_DBG_CONTEXT_INVALID_PARAMS, "branch allocation failed!");
   }

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);

   return (OSAL_Tree_XT*)result;
} /* osal_context_tree_branches_allocator */

void osal_context_tree_branches_free(void *leaf)
{
   OSAL_Context_Tracking_Params_XT *leaf_to_free = (OSAL_Context_Tracking_Params_XT*)leaf;

   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   if(0 != leaf_to_free->flags.path_dynamically_allocated)
   {
      OSAL_Free(leaf_to_free->context_id.path);

      leaf_to_free->context_id.path = OSAL_MAKE_INVALID_PTR(const char);
   }

   if(0 != leaf_to_free->flags.dynamically_allocated)
   {
      OSAL_Free(leaf_to_free);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);
} /* osal_context_tree_branches_free */

#endif

void OSAL_Context_Init(void)
{
   OSAL_Context_Unique_Id_DT cntr;

   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   osal_context.scheduler_started                        = OSAL_FALSE;
   osal_context.interrupts[0].tracking.context_id.id     = 0;
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
   osal_context.init_ongoing                             = OSAL_TRUE;
   osal_context.tree_branches_num_used_elems             = 0;
   osal_context.tree_branches_desc_num_used_elems        = 0;
   osal_context.interrupts[0].tracking.context_id.path   = OSAL_Get_Interrupt_Name(0);

   osal_context.tree_first = OSAL_MAKE_INVALID_PTR(OSAL_Context_Tracking_Params_XT);
#else
   osal_context.interrupts[0].tracking.name              = OSAL_Get_Interrupt_Name(0);
#endif

   for(cntr = 1; cntr < Num_Elems(osal_context.interrupts); ++cntr)
   {
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
      OSAL_Tree_Add_By_String(
         &(osal_context.tree_first),
         &osal_context.interrupts[cntr],
         offsetof(OSAL_Interrupt_Params_XT, tracking.context_id.path),
         0,
         OSAL_Get_Interrupt_Name(cntr),
         '.',
         osal_context_tree_branches_allocator,
         OSAL_TRUE);
#endif
      osal_context.interrupts[cntr].tracking.context_id.id = cntr;
   }

#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
   osal_context.init_ongoing                             = OSAL_FALSE;
#endif

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);
} /* OSAL_Context_Init */

const char *OSAL_Get_Context_Type_Name(OSAL_Context_Type_DT context_type)
{
   const char *result = "---";

   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   if(context_type < OSAL_MAX_NUM_CONTEXT_TYPES)
   {
      result = osal_context_type_names[context_type];
   }

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);

   return result;
} /* OSAL_Get_Context_Type_Name */

const char *OSAL_Get_Context_Name(OSAL_Context_Id_XT *context_id)
{
   const char *result = "---";

   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   if(OSAL_CHECK_PTR(OSAL_Context_Id_XT, context_id))
   {
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
      if(OSAL_CHECK_PTR(const char, context_id->path))
      {
         result = context_id->path;
      }
      else
#endif
         if(context_id->id < (Num_Elems(osal_context.threads) + OSAL_NUM_INTERRUPTS))
      {
         /* Thread */
         if(context_id->id >= OSAL_NUM_INTERRUPTS)
         {
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
            result = osal_context.threads[context_id->id - OSAL_NUM_INTERRUPTS].tracking.context_id.path;
#else
            result = osal_context.threads[context_id->id - OSAL_NUM_INTERRUPTS].tracking.name;
#endif
         }
         /* IRQ */
         else
         {
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
            result = osal_context.interrupts[context_id->id].tracking.context_id.path;
#else
            result = OSAL_Get_Interrupt_Name(context_id->id);
#endif
         }
      }
      else
      {
         result = "main";
      }
   }

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);

   return result;
} /* OSAL_Get_Context_Name */

OSAL_Context_Type_DT OSAL_Get_Context_Type(OSAL_Context_Id_XT *context_id)
{
   OSAL_Context_Type_DT result = OSAL_MAX_NUM_CONTEXT_TYPES;

   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   if(OSAL_CHECK_PTR(OSAL_Context_Id_XT, context_id)
      && (context_id->id > 0) && (context_id->id < (Num_Elems(osal_context.threads) + OSAL_NUM_INTERRUPTS)))
   {
      if(context_id->id < OSAL_NUM_INTERRUPTS)
      {
         result = OSAL_CONTEXT_TYPE_INTERRUPT;
      }
      else
      {
         result = OSAL_CONTEXT_TYPE_THREAD;
      }
   }

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);

   return result;
} /* OSAL_Get_Context_Type */

OSAL_Thread_Params_XT *OSAL_Allocate_Context_Thread(OSAL_Context_Id_XT *context_id)
{
   OSAL_Thread_Params_XT *result = OSAL_MAKE_INVALID_PTR(OSAL_Thread_Params_XT);
   OSAL_Context_Unique_Id_DT id;

   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   if(OSAL_CHECK_PTR(OSAL_Context_Id_XT, context_id)
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
      && OSAL_CHECK_PTR(const char, context_id->path)
#endif
   )
   {
      if(0 == context_id->id)
      {
         /* if next free context ID is already in use because it was allocated with fixed ID then skip it at first */
         while((osal_context.num_installed_threads < Num_Elems(osal_context.threads))
            && (0 != osal_context.threads[osal_context.num_installed_threads].tracking.context_id.id))
         {
            osal_context.num_installed_threads += 1;
         }
         if(osal_context.num_installed_threads < Num_Elems(osal_context.threads))
         {
            context_id->id = osal_context.num_installed_threads++;
            result = &(osal_context.threads[context_id->id]);
            context_id->id += OSAL_NUM_INTERRUPTS;
            memset(result, 0, sizeof(*result));
            result->tracking.context_id = *context_id;
         }
         /* search for free context */
         else
         {
            for(id = 0; id < Num_Elems(osal_context.threads); ++id)
            {
               if(0 == osal_context.threads[id].tracking.context_id.id)
               {
                  result = &(osal_context.threads[id]);
                  osal_context.threads[id].tracking.context_id.id += OSAL_NUM_INTERRUPTS;
                  context_id->id = id + OSAL_NUM_INTERRUPTS;
                  memset(result, 0, sizeof(*result));
                  result->tracking.context_id = *context_id;
                  break;
               }
            }
         }
      }
      else if((context_id->id < (Num_Elems(osal_context.threads) + OSAL_NUM_INTERRUPTS))
         && (0 == osal_context.threads[context_id->id - OSAL_NUM_INTERRUPTS].tracking.context_id.id))
      {
         result = &(osal_context.threads[context_id->id - OSAL_NUM_INTERRUPTS]);
         memset(result, 0, sizeof(*result));
         result->tracking.context_id = *context_id;
      }

#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
      if(OSAL_CHECK_PTR(OSAL_Thread_Params_XT, result))
      {
         OSAL_Tree_Add_By_String(
            &(osal_context.tree_first),
            result,
            offsetof(OSAL_Interrupt_Params_XT, tracking.context_id.path),
            0,
            context_id->path,
            '.',
            osal_context_tree_branches_allocator,
            OSAL_TRUE);
      }
#endif
   }

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);

   return result;
} /* OSAL_Allocate_Context_Thread */

void OSAL_Free_Context_Thread(OSAL_Context_Id_XT *context_id)
{
   OSAL_Thread_Params_XT *thread;

   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   if(OSAL_CHECK_PTR(OSAL_Context_Id_XT, context_id)
      && (context_id->id < (Num_Elems(osal_context.threads) + OSAL_NUM_INTERRUPTS)) && (context_id->id >= OSAL_NUM_INTERRUPTS))
   {
      thread = &(osal_context.threads[context_id->id - OSAL_NUM_INTERRUPTS]);

      thread->tracking.context_id.id = 0;

#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
      OSAL_Tree_Remove_Leaf(&(osal_context.tree_first), thread, OSAL_MAKE_INVALID_HANDLER(OSAL_Tree_Free_Leaf_HT));
#endif
   }

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);
} /* OSAL_Free_Context_Thread */

void *OSAL_Get_Context_Params(OSAL_Context_Id_XT *context_id)
{
   OSAL_Context_Id_XT current_context;
   void *result = OSAL_MAKE_INVALID_PTR(void);

   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   if(!OSAL_CHECK_PTR(OSAL_Context_Id_XT, context_id))
   {
      current_context = OSAL_Get_Current_Context_Id();
      context_id = &current_context;
   }

   if((context_id->id > 0) && (context_id->id < (Num_Elems(osal_context.threads) + OSAL_NUM_INTERRUPTS)))
   {
      if(context_id->id < OSAL_NUM_INTERRUPTS)
      {
         result = &(osal_context.interrupts[context_id->id]);
      }
      else
      {
         result = &(osal_context.threads[context_id->id - OSAL_NUM_INTERRUPTS]);
      }
   }
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
   else if(OSAL_CHECK_PTR(const char, context_id->path))
   {
      result = OSAL_Tree_Find_By_String(
         osal_context.tree_first, offsetof(OSAL_Context_Tracking_Params_XT, context_id.path), context_id->path, '.');

      if(OSAL_CHECK_PTR(void, result))
      {
         context_id->id = ((OSAL_Context_Tracking_Params_XT*)result)->context_id.id;
      }
   }
#endif

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);

   return result;
} /* OSAL_Get_Context_Params */

void OSAL_Execute_For_Tree(OSAL_Context_Id_XT *context_id, OSAL_Hvoid_Two_Params_HT action, void *params)
{
   OSAL_Context_Tracking_Params_XT *item;

   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   if(OSAL_CHECK_PTR(OSAL_Context_Id_XT, context_id) && OSAL_CHECK_HANDLER(OSAL_Hvoid_Two_Params_HT, action))
   {
      if((context_id->id > 0) && (context_id->id < (osal_context.num_installed_threads + OSAL_NUM_INTERRUPTS)))
      {
         if(context_id->id < OSAL_NUM_INTERRUPTS)
         {
            OSAL_CALL_HANDLER(OSAL_Hvoid_Two_Params_HT, action)(&(osal_context.interrupts[context_id->id]), params);
         }
         else
         {
            OSAL_CALL_HANDLER(OSAL_Hvoid_Two_Params_HT, action)(&(osal_context.threads[context_id->id - OSAL_NUM_INTERRUPTS]), params);
         }
      }
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
      else if(OSAL_CHECK_PTR(const char, context_id->path))
      {
         item = OSAL_Tree_Find_By_String(
            osal_context.tree_first, offsetof(OSAL_Context_Tracking_Params_XT, context_id.path), context_id->path, '.');

         if((item->context_id.id > 0) && (item->context_id.id < (osal_context.num_installed_threads + OSAL_NUM_INTERRUPTS)))
         {
            OSAL_CALL_HANDLER(OSAL_Hvoid_Two_Params_HT, action)(item, params);
         }
         if(OSAL_TREE_CHECK_CHILD_LEAF(osal_context.tree_first, item))
         {
            /* do for all children */
            OSAL_context_execute(action, params, (OSAL_Context_Tracking_Params_XT*)OSAL_TREE_GET_CHILD_LEAF(osal_context.tree_first, item));
         }
      }
#endif
   }

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);
} /* OSAL_Execute_For_Tree */

void OSAL_Start(void)
{
   osal_context.scheduler_started = OSAL_TRUE;
   vTaskStartScheduler();
} /* OSAL_Start */

#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)

static size_t osal_list_trees_max_len(OSAL_Context_Tracking_Params_XT *first, uint8_t branch_level, size_t max)
{
   size_t len;
   while(OSAL_CHECK_PTR(OSAL_Context_Tracking_Params_XT, first))
   {
      len = strlen(first->context_id.path) + (branch_level * 3);

      if(len > max)
      {
         max = len;
      }

      if(OSAL_CHECK_PTR(OSAL_Tree_XT, first->path_tree.branch_first))
      {
         max = osal_list_trees_max_len((OSAL_Context_Tracking_Params_XT*)(first->path_tree.branch_first), branch_level + 1, max);
      }
      first = (OSAL_Context_Tracking_Params_XT*)(first->path_tree.list.next);
   }
   return max;
}

static void osal_list_trees(OSAL_Context_Tracking_Params_XT *first, uint8_t branch_level, size_t margin)
{
   while(OSAL_CHECK_PTR(OSAL_Context_Tracking_Params_XT, first))
   {
      OSAL_NOTICE_7(OSAL_DBG_CONTEXT_STATUS, "%*s -> %s %*s (%s.%u)",
         branch_level * 3, "", first->context_id.path, margin - (branch_level * 3) - strlen(first->context_id.path), "",
         OSAL_Get_Context_Type_Name(OSAL_Get_Context_Type(&(first->context_id))), first->context_id.id);

      if(OSAL_CHECK_PTR(OSAL_Tree_XT, first->path_tree.branch_first))
      {
         osal_list_trees((OSAL_Context_Tracking_Params_XT*)(first->path_tree.branch_first), branch_level + 1, margin);
      }
      first = (OSAL_Context_Tracking_Params_XT*)(first->path_tree.list.next);
   }
} /* osal_list_trees */

void OSAL_List_Contexts(void)
{
   size_t margin;
   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   margin = osal_list_trees_max_len(osal_context.tree_first, 0, 0);
   OSAL_NOTICE(OSAL_DBG_CONTEXT_STATUS, "OSAL CONTEXTS:");
   osal_list_trees(osal_context.tree_first, 0, margin);
   OSAL_NOTICE(OSAL_DBG_CONTEXT_STATUS, "OSAL CONTEXTS END");
   OSAL_NOTICE_4(OSAL_DBG_CONTEXT_STATUS, "OSAL pre-aloc branches: %u/%u, desc: %u/%u",
      osal_context.tree_branches_num_used_elems, Num_Elems(osal_context.tree_branches),
      osal_context.tree_branches_desc_num_used_elems, Num_Elems(osal_context.tree_branches_desc));

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);
} /* OSAL_List_Contexts */

#endif

/* we include variant implementation directly here so it can easily use this file static variables as its own */
#include "osal_context_variant.c"

