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

#ifndef OSAL_MUTEX_H_
#define OSAL_MUTEX_H_

#ifndef STD_LIBS_H_
#include "std_libs.h"
#endif

#ifndef OSAL_PUBLIC_MACRO_H_
#include "osal_public_macro.h"
#endif

#ifndef OSAL_COMMON_TYPES_H_
#include "osal_common_types.h"
#endif

#ifndef OSAL_CONTEXT_H_
#include "osal_context.h"
#endif

#ifndef OSAL_TIME_H_
#include "osal_time.h"
#endif

/** @defgroup Mutex Operating System Abstraction Layer - Mutexes management
 *  @brief Creating, destroying, obtaining, releasing.
 *  @{
 */

#ifndef OSAL_MUTEX_XT_EXTERNAL
#error "OSAL_Semaphore_XT must be defined in osal_variant_pre_setup.h proper to OS used in the system!"
#endif

/**
 * @brief Inifializes mutex as a simple mutex (available or not available).
 * For most OS it is done by creating it, however for unification it is called "Init" here.
 *
 * @param mutex pointer to the mutex to be initialized.
 * @result OSAL_TRUE if initialization succeeded, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Mutex_Init(OSAL_Mutex_XT *mutex);

/**
 * @brief Inifializes mutex as a recursive mutex.
 * For most OS it is done by creating it, however for unification it is called "Init" here.
 *
 * @param mutex pointer to the mutex to be initialized.
 * @result OSAL_TRUE if initialization succeeded, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Mutex_Init_Recursive(OSAL_Mutex_XT *mutex);

/**
 * @brief Deinifializes mutex. For most OS it is done by freeing memory occupied by it.
 *
 * @param mutex pointer to the mutex to be deinitialized
 */
void OSAL_Mutex_Deinit(OSAL_Mutex_XT *mutex);

/**
 * @brief checks if the mutex is available. If it is, takes it and return OSAL_TRUE.
 * If mutex is not available, it immediately returns without waiting with result OSAL_FALSE.
 * This function should be called ONLY from thread. Mutexes shal not be used in IRQ.
 * If oyu want to signal something from IRQ to Thread please use Semaphore.
 *
 * @param mutex pointer to the mutex which we want to take.
 * @result OSAL_TRUE when mutex is available, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Mutex_Try_Take(OSAL_Mutex_XT *mutex);

/**
 * @brief checks if the mutex is available. If it is, takes it and return OSAL_TRUE.
 * If mutex is not available, it waits for it indefinetely and when it becomes available, returns with result OSAL_TRUE.
 * This function should be called ONLY from thread. Mutexes shal not be used in IRQ.
 * If oyu want to signal something from IRQ to Thread please use Semaphore.
 *
 * @param mutex pointer to the mutex which we want to take.
 * @result OSAL_TRUE when mutex is available, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Mutex_Wait_And_Take(OSAL_Mutex_XT *mutex);

/**
 * @brief checks if the mutex is available. If it is, takes it and return OSAL_TRUE.
 * If mutex is not available, it waits for it but no longer than timeout_ms.
 * If it becomes available during that time, returns with result OSAL_TRUE.
 * If not then function returns after timeout_ms miliseconds with result OSAL_FALSE.
 * This function should be called ONLY from thread. Mutexes shal not be used in IRQ.
 * If oyu want to signal something from IRQ to Thread please use Semaphore.
 *
 * @param mutex pointer to the mutex which we want to take.
 * @param timeout_ms time after which function must return, even the mutex is not yet available.
 * @result OSAL_TRUE when mutex is available, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Mutex_Wait_And_Take_Timeout(OSAL_Mutex_XT *mutex, OSAL_Time_DT timeout_ms);

/**
 * @brief Allows mutex to be taken by anyone who is waiting for it.
 * This function should be called ONLY from thread. Mutexes shal not be used in IRQ.
 * If oyu want to signal something from IRQ to Thread please use Semaphore.
 *
 * @param mutex pointer to the mutex which we want to make available.
 */
void OSAL_Mutex_Release(OSAL_Mutex_XT *mutex);

/**
 * @brief Checks if mutex is available or already occupied.
 *
 * @param mutex pointer to the mutex which we want to check.
 * @result 0 if mutex is not available. 1 if binary mutex is available. Value bigger than 0 for counting mutex
 * indicated how many times it still can be taken.
 */
uint32_t OSAL_Mutex_Get_Available_Count(OSAL_Mutex_XT *mutex);

/** @} */ // end of Mutex

#endif
