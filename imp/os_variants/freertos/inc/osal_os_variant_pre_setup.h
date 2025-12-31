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

#ifndef OSAL_OS_VARIANT_PRE_SETUP_H_
#define OSAL_OS_VARIANT_PRE_SETUP_H_

#include "std_libs.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#ifndef OSAL_SEMAPHORE_XT_EXTERNAL
#define OSAL_SEMAPHORE_XT_EXTERNAL
typedef SemaphoreHandle_t OSAL_Semaphore_XT;
#endif

#define OSAL_SEMAPHORE_IS_INITIALIZED(_semaphore)     ((SemaphoreHandle_t)NULL != _semaphore)
#define OSAL_SEMAPHORE_IS_NOT_INITIALIZED(_semaphore) ((SemaphoreHandle_t)NULL == _semaphore)

#ifndef OSAL_MUTEX_XT_EXTERNAL
#define OSAL_MUTEX_XT_EXTERNAL
typedef struct
{
   SemaphoreHandle_t mutex;
   OSAL_Bool_DT is_recursive;
} OSAL_Mutex_XT;
#endif

#define OSAL_MUTEX_IS_INITIALIZED(_mutex)             ((SemaphoreHandle_t)NULL != _mutex.mutex)
#define OSAL_MUTEX_IS_NOT_INITIALIZED(_mutex)         ((SemaphoreHandle_t)NULL == _mutex.mutex)

#endif
