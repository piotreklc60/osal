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

#ifndef OSAL_SEMAPHORE_H_
#define OSAL_SEMAPHORE_H_

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

/** @defgroup Semaphore Operating System Abstraction Layer - Semaphores management
 *  @brief Creating, destroying, obtaining, releasing.
 *  @{
 */

#ifndef OSAL_SEMAPHORE_XT_EXTERNAL
#error "OSAL_Semaphore_XT must be defined in osal_variant_pre_setup.h proper to OS used in the system!"
#endif

#ifndef OSAL_SEMAPHORE_IS_INITIALIZED
#error "macro OSAL_SEMAPHORE_IS_INITIALIZED must be defined together with OSAL_Semaphore_XT!"
#endif

#ifndef OSAL_SEMAPHORE_IS_NOT_INITIALIZED
#error "macro OSAL_SEMAPHORE_IS_NOT_INITIALIZED must be defined together with OSAL_Semaphore_XT!"
#endif

/**
 * @brief Inifializes semaphore as a binary semaphore (available or not available).
 * For most OS it is done by creating it, however for unification it is called "Init" here.
 *
 * @param semaphore pointer to the semaphore to be initialized.
 * @result OSAL_TRUE if initialization succeeded, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Semaphore_Init_Binary(OSAL_Semaphore_XT *semaphore);

/**
 * @brief Inifializes semaphore as a counting semaphore.
 * For most OS it is done by creating it, however for unification it is called "Init" here.
 *
 * @param semaphore pointer to the semaphore to be initialized.
 * @param max_value maximum possible value semaphore can reach.
 * @param initial_value value of the semaphose set at the end of the initialization.
 * @result OSAL_TRUE if initialization succeeded, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Semaphore_Init_Counting(OSAL_Semaphore_XT *semaphore, uint32_t max_value, uint32_t initial_value);

/**
 * @brief Deinifializes semaphore. For most OS it is done by freeing memory occupied by it.
 *
 * @param semaphore pointer to the semaphore to be deinitialized.
 */
void OSAL_Semaphore_Deinit(OSAL_Semaphore_XT *semaphore);

/**
 * @brief checks if the semaphore is available. If it is, takes it and return OSAL_TRUE.
 * If semaphore is not available, it immediately returns without waiting with result OSAL_FALSE.
 * This function must be possible to be called from thread and from IRQ.
 *
 * @param semaphore pointer to the semaphore which we want to take.
 * @result OSAL_TRUE when semaphore is available, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Semaphore_Try_Take(OSAL_Semaphore_XT *semaphore);

/**
 * @brief checks if the semaphore is available. If it is, takes it and return OSAL_TRUE.
 * If semaphore is not available, it waits for it indefinetely and when it becomes available, returns with result OSAL_TRUE.
 * This function should be called ONLY from thread. If called from IRQ then its behavior will be same as @see OSAL_Semaphore_Try_Take.
 *
 * @param semaphore pointer to the semaphore which we want to take.
 * @result OSAL_TRUE when semaphore is available, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Semaphore_Wait_And_Take(OSAL_Semaphore_XT *semaphore);

/**
 * @brief checks if the semaphore is available. If it is, takes it and return OSAL_TRUE.
 * If semaphore is not available, it waits for it but no longer than timeout_ms.
 * If it becomes available during that time, returns with result OSAL_TRUE.
 * If not then function returns after timeout_ms miliseconds with result OSAL_FALSE.
 * This function should be called ONLY from thread. If called from IRQ then its behavior will be same as @see OSAL_Semaphore_Try_Take.
 *
 * @param semaphore pointer to the semaphore which we want to take.
 * @param timeout_ms time after which function must return, even the semaphore is not yet available.
 * @result OSAL_TRUE when semaphore is available, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Semaphore_Wait_And_Take_Timeout(OSAL_Semaphore_XT *semaphore, OSAL_Time_DT timeout_ms);

/**
 * @brief Allows semaphore to be taken by anyone who is waiting for it.
 * This function must be possible to be called from thread and from IRQ.
 *
 * @param semaphore pointer to the semaphore which we want to make available.
 */
void OSAL_Semaphore_Release(OSAL_Semaphore_XT *semaphore);

/**
 * @brief Checks if semaphore is available or already occupied.
 *
 * @param semaphore pointer to the semaphore which we want to check.
 * @result 0 if semaphore is not available. 1 if binary semaptore is available. Value bigger than 0 for counting semaphore
 * indicated how many times it still can be taken.
 */
uint32_t OSAL_Semaphore_Get_Available_Count(OSAL_Semaphore_XT *semaphore);

/** @} */ // end of Semaphore

#endif
