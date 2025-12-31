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

#ifndef OSAL_INVOKE_C_
#define OSAL_INVOKE_C_
#endif

#ifndef OSAL_H_
#include "osal.h"
#endif

void OSAL_Invoke_Init(OSAL_Invoke_XT *invoke_params)
{
   OSAL_ENTER_FUNC(OSAL_DBG_INVOKE);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Invoke_XT, invoke_params)))
   {
      memset(invoke_params, 0, sizeof(*invoke_params));
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_INVOKE, "invalid params! %s: %p", "invoke_params", invoke_params);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_INVOKE);
} /* OSAL_Invoke_Init */

void OSAL_Set_Destination_Id_Vendor_Checker(OSAL_Invoke_XT *invoke_params, OSAL_Destination_Compare_HT vendor_checker)
{
   OSAL_ENTER_FUNC(OSAL_DBG_INVOKE);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Invoke_XT, invoke_params) && OSAL_CHECK_HANDLER(OSAL_Destination_Compare_HT, vendor_checker)))
   {
      invoke_params->destination_id.is_context_different = vendor_checker;
      invoke_params->destination_id_as_vendor_compare    = OSAL_TRUE;
   }
   else
   {
      OSAL_ERROR_4(OSAL_DBG_INVOKE, "invalid params! %s: %p; %s: %p",
         "invoke_params", invoke_params, "vendor_checker", vendor_checker);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_INVOKE);
} /* OSAL_Set_Destination_Id_Vendor_Checker */

void OSAL_Set_Destination_Irq_Lock_Unlock(OSAL_Invoke_XT *invoke_params, OSAL_Destination_Lock_HT lock, OSAL_Destination_Unlock_HT unlock)
{
   OSAL_ENTER_FUNC(OSAL_DBG_INVOKE);

   if(OSAL_BASIC_PARAMS_CHECK(
      OSAL_CHECK_PTR(OSAL_Invoke_XT, invoke_params)
      && OSAL_CHECK_HANDLER(OSAL_Destination_Lock_HT, lock)
      && OSAL_CHECK_HANDLER(OSAL_Destination_Unlock_HT, unlock)))
   {
      invoke_params->lock   = lock;
      invoke_params->unlock = unlock;
   }
   else
   {
      OSAL_ERROR_6(OSAL_DBG_INVOKE, "invalid params! %s: %p; %s: %p; %s: %p",
         "invoke_params", invoke_params, "lock", lock, "unlock", unlock);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_INVOKE);
} /* OSAL_Set_Destination_Irq_Lock_Unlock */

void OSAL_Mark_Invoke_Params(OSAL_Invoke_XT *invoke_params)
{
   OSAL_ENTER_FUNC(OSAL_DBG_INVOKE);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Invoke_XT, invoke_params)))
   {
      if(OSAL_BOOL_IS_FALSE(invoke_params->destination_id_as_vendor_compare))
      {
         invoke_params->destination_id.context_id = OSAL_Get_Current_Context_Id();
      }
      invoke_params->destination_type = OSAL_Get_Current_Context_Type();
      if(OSAL_MUTEX_IS_NOT_INITIALIZED(invoke_params->task_lock) && (OSAL_CONTEXT_TYPE_THREAD == invoke_params->destination_type))
      {
         (void)OSAL_Mutex_Init(&(invoke_params->task_lock));
      }
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_INVOKE, "invalid params! %s: %p", "invoke_params", invoke_params);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_INVOKE);
} /* OSAL_Mark_Invoke_Params */

OSAL_Bool_DT OSAL_Is_Invoke_Needed(OSAL_Invoke_XT *invoke_params)
{
   OSAL_Context_Id_XT current_context_id;
   OSAL_Bool_DT result = OSAL_FALSE;

   OSAL_ENTER_FUNC(OSAL_DBG_INVOKE);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Invoke_XT, invoke_params)))
   {
      current_context_id = OSAL_Get_Current_Context_Id();

      if(OSAL_BOOL_IS_FALSE(invoke_params->destination_id_as_vendor_compare))
      {
         result = (current_context_id.id != invoke_params->destination_id.context_id.id);
      }
      else
      {
         result = invoke_params->destination_id.is_context_different(invoke_params, &current_context_id);
      }

      invoke_params->is_invoke_needed = result;
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_INVOKE, "invalid params! %s: %p", "invoke_params", invoke_params);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_INVOKE);

   return result;
} /* OSAL_Is_Invoke_Needed */

OSAL_Bool_DT OSAL_Invoke_Sync_To_Destination(OSAL_Invoke_XT *invoke_params, OSAL_Time_DT timeout)
{
   OSAL_Context_Type_DT current_context_type;
   OSAL_Bool_DT result = OSAL_FALSE;

   OSAL_ENTER_FUNC(OSAL_DBG_INVOKE);

   current_context_type = OSAL_Get_Current_Context_Type();

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Invoke_XT, invoke_params)))
   {
      if(OSAL_BOOL_IS_FALSE(OSAL_Is_Invoke_Needed(invoke_params)))
      {
         result = OSAL_TRUE;
      }
      /**
       * we are going to invoke to IRQ context.
       * If we are here then it means destination IRQ is higher priority and not active at this moment
       * or it is lower priority and not active or currently interrupted by us (if we are IRQ with higher priority).
       * Call "lock" function. If destination IRQ is currently not active then it should disable itself and return true.
       * If destination IRQ is currently active then "lock" function shall do nothing and return false.
       */
      else if(OSAL_CONTEXT_TYPE_INTERRUPT == invoke_params->destination_type)
      {
         result = OSAL_BOOL_IS_FALSE(invoke_params->locked_from_irq)
            && OSAL_CHECK_HANDLER(OSAL_Destination_Lock_HT, invoke_params->lock)
            && OSAL_CALL_HANDLER(OSAL_Destination_Lock_HT, invoke_params->lock)(invoke_params);

         if(OSAL_BOOL_IS_TRUE(result))
         {
            invoke_params->locked_from_irq = OSAL_TRUE;
         }
         else
         {
            OSAL_ERROR(OSAL_DBG_INVOKE, "invalid failed");
         }
      }
      /**
       * we are going to invoke to TASK context.
       */
      else if(OSAL_MUTEX_IS_INITIALIZED(invoke_params->task_lock))
      {
         /**
          * we are going to invoke to TASK context from IRQ.
          */
         if(OSAL_CONTEXT_TYPE_INTERRUPT == current_context_type)
         {
            /* for binary Mutex/mutex OSAL_Mutex_Get_Available_Count returns 1 when it is available */
            result = OSAL_BOOL_IS_FALSE(invoke_params->locked_from_irq) && (0 == OSAL_Mutex_Get_Available_Count(&(invoke_params->task_lock)));

            if(OSAL_BOOL_IS_TRUE(result))
            {
               invoke_params->locked_from_irq = OSAL_TRUE;
            }
            else
            {
               OSAL_ERROR(OSAL_DBG_INVOKE, "invalid failed");
            }
         }
         /**
          * we are going to invoke to TASK context from another task.
          */
         else
         {
            result = OSAL_Mutex_Wait_And_Take_Timeout(&(invoke_params->task_lock), timeout);
            if(OSAL_BOOL_IS_FALSE(result))
            {
               OSAL_ERROR(OSAL_DBG_INVOKE, "invalid failed");
            }
         }
      }
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_INVOKE, "invalid params! %s: %p", "invoke_params", invoke_params);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_INVOKE);

   return result;
} /* OSAL_Invoke_Sync_To_Destination */

OSAL_Bool_DT OSAL_Invoke_Release_Destination(OSAL_Invoke_XT *invoke_params)
{
   OSAL_Bool_DT result = OSAL_FALSE;

   OSAL_ENTER_FUNC(OSAL_DBG_INVOKE);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Invoke_XT, invoke_params)))
   {
      result = OSAL_TRUE;
      if(OSAL_BOOL_IS_TRUE(invoke_params->is_invoke_needed))
      {
         if(OSAL_CONTEXT_TYPE_INTERRUPT == invoke_params->destination_type)
         {
            OSAL_CHECK_AND_CALL_HANDLER(OSAL_Destination_Unlock_HT, invoke_params->unlock)(invoke_params);
            invoke_params->locked_from_irq = OSAL_FALSE;
         }
         else if(OSAL_CONTEXT_TYPE_INTERRUPT == OSAL_Get_Current_Context_Type())
         {
            invoke_params->locked_from_irq = OSAL_FALSE;
         }
         else if(OSAL_MUTEX_IS_INITIALIZED(invoke_params->task_lock))
         {
            OSAL_Mutex_Release(&(invoke_params->task_lock));
         }
      }
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_INVOKE, "invalid params! %s: %p", "invoke_params", invoke_params);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_INVOKE);

   return result;
} /* OSAL_Invoke_Release_Destination */

void OSAL_Destination_Thread_Open_Invoke_Window(OSAL_Invoke_XT *invoke_params)
{
   OSAL_ENTER_FUNC(OSAL_DBG_INVOKE);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Invoke_XT, invoke_params)) && OSAL_MUTEX_IS_INITIALIZED(invoke_params->task_lock))
   {
      OSAL_Mutex_Release(&(invoke_params->task_lock));
   }
   else
   {
      OSAL_ERROR_4(OSAL_DBG_INVOKE, "invalid params! %s: %p; %s: %p",
         "invoke_params", invoke_params, "task_lock", invoke_params->task_lock.mutex);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_INVOKE);
} /* OSAL_Destination_Thread_Open_Invoke_Window */

void OSAL_Destination_Thread_Close_Invoke_Window(OSAL_Invoke_XT *invoke_params)
{
   OSAL_ENTER_FUNC(OSAL_DBG_INVOKE);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Invoke_XT, invoke_params)) && OSAL_MUTEX_IS_INITIALIZED(invoke_params->task_lock))
   {
      OSAL_Mutex_Wait_And_Take(&(invoke_params->task_lock));
   }
   else
   {
      OSAL_ERROR_4(OSAL_DBG_INVOKE, "invalid params! %s: %p; %s: %p",
         "invoke_params", invoke_params, "task_lock", invoke_params->task_lock.mutex);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_INVOKE);
} /* OSAL_Destination_Thread_Close_Invoke_Window */
