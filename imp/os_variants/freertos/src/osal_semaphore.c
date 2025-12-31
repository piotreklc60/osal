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

#ifndef OSAL_SEMAPHORE_C_
#define OSAL_SEMAPHORE_C_
#endif

#ifndef OSAL_H_
#include "osal.h"
#endif

OSAL_Bool_DT OSAL_Semaphore_Init_Binary(OSAL_Semaphore_XT *semaphore)
{
   SemaphoreHandle_t xSemaphore;
   OSAL_Bool_DT result = OSAL_FALSE;

   OSAL_ENTER_FUNC(OSAL_DBG_SEMAPHORE);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Semaphore_XT, semaphore)))
   {
      xSemaphore = xSemaphoreCreateBinary();

      if(NULL != xSemaphore)
      {
         *semaphore = xSemaphore;
         result = OSAL_TRUE;
      }
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_SEMAPHORE, "invalid params! %s: %p", "semaphore", semaphore);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_SEMAPHORE);

   return result;
} /* OSAL_Semaphore_Init_Binary */

OSAL_Bool_DT OSAL_Semaphore_Init_Counting(OSAL_Semaphore_XT *semaphore, uint32_t max_value, uint32_t initial_value)
{
   SemaphoreHandle_t xSemaphore;
   OSAL_Bool_DT result = OSAL_FALSE;

   OSAL_ENTER_FUNC(OSAL_DBG_SEMAPHORE);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Semaphore_XT, semaphore)))
   {
      xSemaphore = xSemaphoreCreateCounting(max_value, initial_value);

      if(NULL != xSemaphore)
      {
         *semaphore = xSemaphore;
         result = OSAL_TRUE;
      }
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_SEMAPHORE, "invalid params! %s: %p", "semaphore", semaphore);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_SEMAPHORE);

   return result;
} /* OSAL_Semaphore_Init_Counting */

void OSAL_Semaphore_Deinit(OSAL_Semaphore_XT *semaphore)
{
   OSAL_ENTER_FUNC(OSAL_DBG_SEMAPHORE);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Semaphore_XT, semaphore)))
   {
      vSemaphoreDelete(*semaphore);
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_SEMAPHORE, "invalid params! %s: %p", "semaphore", semaphore);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_SEMAPHORE);
} /* OSAL_Semaphore_Deinit */

OSAL_Bool_DT OSAL_Semaphore_Try_Take(OSAL_Semaphore_XT *semaphore)
{
   return OSAL_Semaphore_Wait_And_Take_Timeout(semaphore, 0);
} /* OSAL_Semaphore_Try_Take */

OSAL_Bool_DT OSAL_Semaphore_Wait_And_Take(OSAL_Semaphore_XT *semaphore)
{
   return OSAL_Semaphore_Wait_And_Take_Timeout(semaphore, portMAX_DELAY * 1000 / configTICK_RATE_HZ);
} /* OSAL_Semaphore_Wait_And_Take */

OSAL_Bool_DT OSAL_Semaphore_Wait_And_Take_Timeout(OSAL_Semaphore_XT *semaphore, OSAL_Time_DT timeout_ms)
{
   OSAL_Context_Type_DT current_context_type;
   BaseType_t retval;
   BaseType_t xHigherPriorityTaskWoken = pdFALSE;
   OSAL_Bool_DT result = OSAL_FALSE;

   OSAL_ENTER_FUNC(OSAL_DBG_SEMAPHORE);

   current_context_type = OSAL_Get_Current_Context_Type();

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Semaphore_XT, semaphore)))
   {
      if(OSAL_CONTEXT_TYPE_INTERRUPT != current_context_type)
      {
         retval = xSemaphoreTake(*semaphore, timeout_ms * configTICK_RATE_HZ / 1000);
      }
      else
      {
         /* for IRQ there is no waiting possible */
         retval = xSemaphoreTakeFromISR(*semaphore, &xHigherPriorityTaskWoken);

         if(pdFALSE != xHigherPriorityTaskWoken)
         {
            // TODO: request tasks context switch acording to FreeRTOS port for this MCU
         }
      }

      if(pdPASS == retval)
      {
         result = OSAL_TRUE;
      }
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_SEMAPHORE, "invalid params! %s: %p", "semaphore", semaphore);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_SEMAPHORE);

   return result;
} /* OSAL_Semaphore_Wait_And_Take_Timeout */

void OSAL_Semaphore_Release(OSAL_Semaphore_XT *semaphore)
{
   OSAL_Context_Type_DT current_context_type;
   BaseType_t xHigherPriorityTaskWoken = pdFALSE;

   OSAL_ENTER_FUNC(OSAL_DBG_SEMAPHORE);

   current_context_type = OSAL_Get_Current_Context_Type();

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Semaphore_XT, semaphore)))
   {
      if(OSAL_CONTEXT_TYPE_INTERRUPT != current_context_type)
      {
         (void)xSemaphoreGive(*semaphore);
      }
      else
      {
         (void)xSemaphoreGiveFromISR(*semaphore, &xHigherPriorityTaskWoken);

         if(pdFALSE != xHigherPriorityTaskWoken)
         {
            // TODO: request tasks context switch acording to FreeRTOS port for this MCU
         }
      }
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_SEMAPHORE, "invalid params! %s: %p", "semaphore", semaphore);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_SEMAPHORE);
} /* OSAL_Semaphore_Release */

uint32_t OSAL_Semaphore_Get_Available_Count(OSAL_Semaphore_XT *semaphore)
{
   uint32_t result = 0;

   OSAL_ENTER_FUNC(OSAL_DBG_SEMAPHORE);

   if(OSAL_BASIC_PARAMS_CHECK(OSAL_CHECK_PTR(OSAL_Semaphore_XT, semaphore)))
   {
      result = (uint32_t)uxSemaphoreGetCount(*semaphore);
   }
   else
   {
      OSAL_ERROR_2(OSAL_DBG_SEMAPHORE, "invalid params! %s: %p", "semaphore", semaphore);
   }

   OSAL_EXIT_FUNC(OSAL_DBG_SEMAPHORE);

   return result;
} /* OSAL_Semaphore_Get_Available_Count */
