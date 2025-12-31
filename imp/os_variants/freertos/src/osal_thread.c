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

#ifndef OSAL_THREAD_C_
#define OSAL_THREAD_C_
#endif

#ifndef OSAL_H_
#include "osal.h"
#endif

OSAL_Context_Id_XT OSAL_Thread_Create(
   OSAL_Thread_HT             thread_func,
   void                      *thread_func_params,
   const char                *path,
   OSAL_Thread_Stack_Depth_DT stack_size,
   OSAL_Thread_Priority_DT    priority,
   OSAL_Context_Unique_Id_DT  fixed_thread_id)
{
   TaskHandle_t handle;
   OSAL_Thread_Params_XT *thread_params;
   OSAL_Context_Id_XT result;

   OSAL_ENTER_FUNC(OSAL_DBG_THREAD);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_HANDLER(OSAL_Thread_HT, thread_func) && OSAL_CHECK_PTR(const char, path)))
   {
      result.id   = fixed_thread_id;
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
      result.path = path;
#endif

      thread_params = OSAL_Allocate_Context_Thread(&result);

      if(OSAL_CHECK_PTR(OSAL_Thread_Params_XT, thread_params))
      {
#if(OSAL_FEATURE_PRESENT != OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
         thread_params->tracking.name = path;
#endif

         if (pdPASS == xTaskCreate( thread_func, path, stack_size, thread_func_params, priority, &handle ))
         {
            thread_params->os_handle = handle;
            vTaskSetTaskNumber(handle, result.id);
         }
      }
   }
   else
   {
      OSAL_ERROR_4(OSAL_DBG_THREAD, "invalid params! %s: %p; %s: %p", "thread_func", thread_func, "path", path);
      result.id   = -1;
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
      result.path = "---";
#endif
   }

   OSAL_EXIT_FUNC(OSAL_DBG_THREAD);

   return result;
} /* OSAL_Thread_Create */

#if(OSAL_FEATURE_PRESENT == OSAL_THREAD_SUPPORT_CREATE_STATIC)
OSAL_Context_Id_XT OSAL_Thread_Create_Static(
   OSAL_Thread_HT                thread_func,
   void                         *thread_func_params,
   OSAL_Thread_Static_Params_XT *thread_static_params,
   const char                   *path,
   uint8_t                      *stack,
   OSAL_Thread_Stack_Depth_DT    stack_size,
   OSAL_Thread_Priority_DT       priority,
   OSAL_Context_Unique_Id_DT     fixed_thread_id)
{
   TaskHandle_t handle;
   OSAL_Thread_Params_XT *thread_params;
   OSAL_Context_Id_XT result;

   OSAL_ENTER_FUNC(OSAL_DBG_THREAD);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_HANDLER(OSAL_Thread_HT, thread_func) && OSAL_CHECK_PTR(const char, path)
      && OSAL_CHECK_PTR(OSAL_Thread_Static_Params_XT, thread_static_params)))
   {
      result.id   = fixed_thread_id;
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
      result.path = path;
#endif

      thread_params = OSAL_Allocate_Context_Thread(&result);

      if(OSAL_CHECK_PTR(OSAL_Thread_Params_XT, thread_params))
      {
#if(OSAL_FEATURE_PRESENT != OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
         thread_params->tracking.name = path;
#endif

         handle = xTaskCreateStatic( thread_func, path, stack_size, thread_func_params, priority, stack, thread_static_params );

         if (NULL != handle)
         {
            thread_params->os_handle = handle;
            vTaskSetTaskNumber(handle, result.id);
         }
      }
   }
   else
   {
      OSAL_ERROR_6(OSAL_DBG_THREAD, "invalid params! %s: %p; %s: %p; %s: %p",
         "thread_func", thread_func, "path", path, "thread_static_params", thread_static_params);
      result.id   = -1;
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
      result.path = "---";
#endif
   }

   OSAL_EXIT_FUNC(OSAL_DBG_THREAD);

   return result;
} /* OSAL_Thread_Create_Static */
#endif

void OSAL_Thread_Destroy(OSAL_Context_Id_XT *context_id)
{
   OSAL_Thread_Params_XT *thread_params;

   OSAL_ENTER_FUNC(OSAL_DBG_THREAD);

   thread_params = OSAL_Get_Context_Params(context_id);

   if(OSAL_CHECK_PTR(OSAL_Thread_Params_XT, thread_params)
      && (OSAL_CONTEXT_TYPE_THREAD == OSAL_Get_Context_Type(context_id))
      && OSAL_CHECK_PTR(void, thread_params->os_handle))
   {
      vTaskDelete((TaskHandle_t)(thread_params->os_handle));

      OSAL_Message_Queue_Deinit(thread_params->queue);

      thread_params->os_handle = OSAL_MAKE_INVALID_PTR(void);

      OSAL_Free_Context_Thread(context_id);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_THREAD);
} /* OSAL_Thread_Destroy */

void OSAL_Thread_Suspend(OSAL_Context_Id_XT *context_id)
{

} /* OSAL_Thread_Suspend */

void OSAL_Thread_Resume(OSAL_Context_Id_XT *context_id)
{

} /* OSAL_Thread_Resume */

OSAL_Thread_Params_XT *OSAL_Get_Thread_Params(OSAL_Context_Id_XT *context_id)
{
   OSAL_Thread_Params_XT *result;

   OSAL_ENTER_FUNC(OSAL_DBG_THREAD);

   result = OSAL_Get_Context_Params(context_id);

   OSAL_EXIT_FUNC(OSAL_DBG_THREAD);

   return result;
} /* OSAL_Get_Thread_Params */


