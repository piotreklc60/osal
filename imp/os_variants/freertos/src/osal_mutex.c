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

#ifndef OSAL_MUTEX_C_
#define OSAL_MUTEX_C_
#endif

#ifndef OSAL_H_
#include "osal.h"
#endif

OSAL_Bool_DT OSAL_Mutex_Init(OSAL_Mutex_XT *mutex)
{
   SemaphoreHandle_t xSemaphore;
   OSAL_Bool_DT result = OSAL_FALSE;

   OSAL_ENTER_FUNC(OSAL_DBG_MUTEX);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Mutex_XT, mutex)))
   {
      xSemaphore = xSemaphoreCreateMutex();

      if(NULL != xSemaphore)
      {
         mutex->mutex         = xSemaphore;
         mutex->is_recursive  = OSAL_FALSE;
         result               = OSAL_TRUE;
      }
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_MUTEX, "invalid params! %s: %p", "mutex", mutex);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_MUTEX);

   return result;
} /* OSAL_Mutex_Init */

OSAL_Bool_DT OSAL_Mutex_Init_Recursive(OSAL_Mutex_XT *mutex)
{
   SemaphoreHandle_t xSemaphore;
   OSAL_Bool_DT result = OSAL_FALSE;

   OSAL_ENTER_FUNC(OSAL_DBG_MUTEX);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Mutex_XT, mutex)))
   {
      xSemaphore = xSemaphoreCreateRecursiveMutex();

      if(NULL != xSemaphore)
      {
         mutex->mutex         = xSemaphore;
         mutex->is_recursive  = OSAL_TRUE;
         result               = OSAL_TRUE;
      }
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_MUTEX, "invalid params! %s: %p", "mutex", mutex);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_MUTEX);

   return result;
} /* OSAL_Mutex_Init_Recursive */

void OSAL_Mutex_Deinit(OSAL_Mutex_XT *mutex)
{
   OSAL_ENTER_FUNC(OSAL_DBG_MUTEX);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Mutex_XT, mutex)))
   {
      vSemaphoreDelete(mutex->mutex);
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_MUTEX, "invalid params! %s: %p", "mutex", mutex);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_MUTEX);
} /* OSAL_Mutex_Deinit */

OSAL_Bool_DT OSAL_Mutex_Try_Take(OSAL_Mutex_XT *mutex)
{
   return OSAL_Mutex_Wait_And_Take_Timeout(mutex, 0);
} /* OSAL_Mutex_Try_Take */

OSAL_Bool_DT OSAL_Mutex_Wait_And_Take(OSAL_Mutex_XT *mutex)
{
   return OSAL_Mutex_Wait_And_Take_Timeout(mutex, portMAX_DELAY * 1000 / configTICK_RATE_HZ);
} /* OSAL_Mutex_Wait_And_Take */

OSAL_Bool_DT OSAL_Mutex_Wait_And_Take_Timeout(OSAL_Mutex_XT *mutex, OSAL_Time_DT timeout_ms)
{
   BaseType_t retval;
   OSAL_Bool_DT result = OSAL_FALSE;

   OSAL_ENTER_FUNC(OSAL_DBG_MUTEX);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Mutex_XT, mutex)))
   {
      if(OSAL_BOOL_IS_TRUE(mutex->is_recursive))
      {
         retval = xSemaphoreTakeRecursive(mutex->mutex, timeout_ms * configTICK_RATE_HZ / 1000);
      }
      else
      {
         retval = xSemaphoreTake(mutex->mutex, timeout_ms * configTICK_RATE_HZ / 1000);
      }

      if(pdPASS == retval)
      {
         result = OSAL_TRUE;
      }
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_MUTEX, "invalid params! %s: %p", "mutex", mutex);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_MUTEX);

   return result;
} /* OSAL_Mutex_Wait_And_Take_Timeout */

void OSAL_Mutex_Release(OSAL_Mutex_XT *mutex)
{
   OSAL_ENTER_FUNC(OSAL_DBG_MUTEX);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Mutex_XT, mutex)))
   {
      if(OSAL_BOOL_IS_TRUE(mutex->is_recursive))
      {
         xSemaphoreGiveRecursive(mutex->mutex);
      }
      else
      {
         xSemaphoreGive(mutex->mutex);
      }
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_MUTEX, "invalid params! %s: %p", "mutex", mutex);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_MUTEX);
} /* OSAL_Mutex_Release */

uint32_t OSAL_Mutex_Get_Available_Count(OSAL_Mutex_XT *mutex)
{
   uint32_t result = 0;

   OSAL_ENTER_FUNC(OSAL_DBG_MUTEX);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Mutex_XT, mutex)))
   {
      result = (uint32_t)uxSemaphoreGetCount(mutex->mutex);
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_MUTEX, "invalid params! %s: %p", "mutex", mutex);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_MUTEX);

   return result;
} /* OSAL_Mutex_Get_Available_Count */

