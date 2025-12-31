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

#ifndef OSAL_TIME_C_
#define OSAL_TIME_C_
#endif

#ifndef OSAL_H_
#include "osal.h"
#endif

OSAL_Time_DT OSAL_Get_Time(void)
{
   OSAL_Time_DT result = 0;
   uint32_t current_interrupt;

   OSAL_ENTER_FUNC(OSAL_DBG_TIME);

   result = xTaskGetTickCount();

   OSAL_EXIT_FUNC(OSAL_DBG_TIME);

   return result;
} /* OSAL_Get_Time */

void OSAL_Sleep_Ms(uint32_t miliseconds)
{
   OSAL_ENTER_FUNC(OSAL_DBG_TIME);

   vTaskDelay(miliseconds * configTICK_RATE_HZ / 1000);

   OSAL_EXIT_FUNC(OSAL_DBG_TIME);
} /* OSAL_Sleep_Ms */

void OSAL_Sleep_S(uint32_t seconds)
{
   OSAL_ENTER_FUNC(OSAL_DBG_TIME);

   vTaskDelay(seconds * configTICK_RATE_HZ);

   OSAL_EXIT_FUNC(OSAL_DBG_TIME);
} /* OSAL_Sleep_S */

