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

#ifndef OSAL_INVOKE_H_
#define OSAL_INVOKE_H_

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

/** @defgroup Invoke Operating System Abstraction Layer - Actions invoke (calls synchronization to different context) mechanism
 *  @brief Creating, destroying, obtaining, releasing.
 *  @{
 */

struct OSAL_Invoke_eXtendedTag;

/**
 * @brief Type of a function used to check if current context is a destination context.
 * This can be used for example if we have some functionality which uses 2 IRQs and we want to synchronize function execution to both of them.
 * In that case Destination_Compare function checks if our context is one of these 2 IRQs.
 *
 * @param invoke_params pointer to current Invoke synchronization structure parameters.
 * @param current_context_id ID of the current context to be compared with the desired destination.
 * @result OSAL_TRUE if current context is actually the destination context, OSAL_FALSE if currently running context is a different one.
 */
typedef OSAL_Bool_DT (*OSAL_Destination_Compare_HT) (struct OSAL_Invoke_eXtendedTag *invoke_params, OSAL_Context_Id_XT *current_context_id);

/**
 * @brief function to block switching to destination context. If destination context is some IRQ then this function usually disables that IRQ.
 *
 * @param invoke_params pointer to current Invoke synchronization structure parameters.
 * @result OSAL_TRUE if locking succeeded, OSAL_FALSE in case of any failure.
 */
typedef OSAL_Bool_DT (*OSAL_Destination_Lock_HT) (struct OSAL_Invoke_eXtendedTag *invoke_params);

/**
 * @brief function to unblock switching to destination context. If destination context is some IRQ then this function usually enables back that IRQ.
 *
 * @param invoke_params pointer to current Invoke synchronization structure parameters.
 */
typedef void (*OSAL_Destination_Unlock_HT) (struct OSAL_Invoke_eXtendedTag *invoke_params);

typedef struct OSAL_Invoke_eXtendedTag
{
   /** this function is used when destination is an IRQ. It is used to disable destination IRQ. */
   OSAL_Destination_Lock_HT         lock;
   /** this function is used when destination is an IRQ. It is used to re-enable destination IRQ. after previously disabled by lock */
   OSAL_Destination_Unlock_HT       unlock;
   union
   {
      /* to use compare function destination_id_as_vendor_compare must be set to true */
      OSAL_Destination_Compare_HT   is_context_different;
      OSAL_Context_Id_XT            context_id;
   }destination_id;
   OSAL_Mutex_XT                    task_lock;
   /*OSAL_Context_Type_DT*/uint8_t  destination_type;
   OSAL_Bool_DT                     destination_id_as_vendor_compare;
   OSAL_Bool_DT                     is_invoke_needed;
   OSAL_Bool_DT                     locked_from_irq;
}OSAL_Invoke_XT;

/**
 * @brief initializes Invoke parameters.
 *
 * @param invoke_params pointer to parameters to be initialized.
 */
void OSAL_Invoke_Init(OSAL_Invoke_XT *invoke_params);

/**
 * @brief sets vendor-specific function for comparing destination_id.
 *
 * @param invoke_params parameters of invoke destination
 * @param vendor_checker pointer to a function which will be used for comparing destination_id.
 */
void OSAL_Set_Destination_Id_Vendor_Checker(OSAL_Invoke_XT *invoke_params, OSAL_Destination_Compare_HT vendor_checker);

/**
 * @brief sets lock and unlock functions for IRQ destination.
 *
 * @param invoke_params parameters of invoke destination
 * @param lock pointer to a function which will be used to lock destination IRQ
 * @param unlock pointer to a function which will be used to unlock destination IRQ
 */
void OSAL_Set_Destination_Irq_Lock_Unlock(OSAL_Invoke_XT *invoke_params, OSAL_Destination_Lock_HT lock, OSAL_Destination_Unlock_HT unlock);

/**
 * @brief function which shall be called at least once from the context to which invoke operations are expected.
 *
 * @param invoke_params parameters of invoke destination
 */
void OSAL_Mark_Invoke_Params(OSAL_Invoke_XT *invoke_params);

/**
 * @brief This function only checks of current ocntext is different to the one pointed by invoke_params.
 *
 * @param invoke_params parameters of invoke destination
 * @return OSAL_TRUE if contexts are different so invoke would be needed, OSAL_FALSE if both contexts are same.
 */
OSAL_Bool_DT OSAL_Is_Invoke_Needed(OSAL_Invoke_XT *invoke_params);

/**
 * @brief function called during action invoking. It checks if invoke is needed,
 * if yes then secures conditions (for example blocks destination interrupt or waits for semaphore).
 *
 * @param invoke_params parameters of invoke destination
 * @param timeout time in miliseconds which defines how long function shall block source task. -1 fir indefinetly, 0 for no blocking.
 * @return OSAL_TRUE if OSAL_INVOKE/OSAL_TRY_INVOKE can call the action, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Invoke_Sync_To_Destination(OSAL_Invoke_XT *invoke_params, OSAL_Time_DT timeout);

/**
 * If invoke was executed then at the end this function restores destination conditions (enable back the IRQ / semaphore).
 *
 * @param invoke_params parameters of invoke destination
 * @return OSAL_TRUE when release succeeded OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Invoke_Release_Destination(OSAL_Invoke_XT *invoke_params);

/**
 * @brief function to be called from destination task.
 * From the moment of this function call all incomming invokes from any context will be simply called.
 *
 * @param invoke_params parameters of invoke destination
 */
void OSAL_Destination_Thread_Open_Invoke_Window(OSAL_Invoke_XT *invoke_params);

/**
 * @brief function to be called from destination task.
 * From the moment of this function call all incomming invokes from any context cannot be called and must wait.
 *
 * @param invoke_params parameters of invoke destination
 */
void OSAL_Destination_Thread_Close_Invoke_Window(OSAL_Invoke_XT *invoke_params);

/**
 * @brief this macro is used to invoke the action.
 * By invoke it means action will be called in the way that the action is synchronized to the destination thread / interrupt.
 * By synchronized to the destination it means source action execution will not be interrupted by destination execution and vice versa.
 * Action execution will be done in the moment when destination context is not running or when destination calls OSAL_Destination_Process_Waiting_Invokes.
 * If there is a invoke action from exactly the same context as the destination then invoke is reduced to simple call.
 * Invoking implementation between 2 different contexts can vary depends to destination / source type:
 * 1. Interrupt/Task -> Interrupt: If destination Interrupt is not currently active then:
 *   a) if destination priority is lower than caller priority then invoke is reduced to simple call.
 *   b) if destination priority is higher than caller then destination IRQ is temporarily disabled, action is called and IRQ is back enabled.
 *  IF DESTINATION INTERRUPT IS CURRENTLY ACTIVE AND CALLER IRQ INTERRUPTED IT THEN INVOKE FAILS. WE ARE NOT ABLE TO SWITCH FROM ONE INTERRUPT TO ANOTHER.
 * 2. Interrupt -> Task: If destination task is currently to running then invoke is reduced to simple call. IF DESTINATION TASK IS RUNNING THEN INVOKE WILL FAIL.
 * 2. Task -> Task: Here synchronisation can be implemented using a mutex. If destinaiton is busy then caller will be suspended  by th OS until destination is free.
 *
 * @return OSAL_TRUE if invoke succeeded, OSAL_FALSE otherwise.
 *
 * @param _invoke_params pointer to OSAL_Invoke_XT structure with parameters of the destination.
 * @param _action the code to be invoked to the destination.
 * ATTENTION! ACTION MUST ALWAYS RETURN TRUE!!! OTHWERISE AFTER ITS EXECUTION DESTINATION IRQ/SEMAPHORE WILL NOT BE UNLOCKED!!!
 */
#define OSAL_INVOKE(_invoke_params, _action)                     (OSAL_Invoke_Sync_To_Destination(_invoke_params, -1) && _action && OSAL_Invoke_Release_Destination(_invoke_params))

/**
 * @brief this macro is used to invoke the action.
 * This macro is very similar to OSAL_INVOKE with one exception - if source is a thread then it is blocked for _timeout miliseconds.
 * If invoke needs longer time to wait, it will fail.
 *
 * @return OSAL_TRUE if invoke succeeded, OSAL_FALSE otherwise.
 *
 * @param _invoke_params pointer to OSAL_Invoke_XT structure with parameters of the destination.
 * @param _action the code to be invoked to the destination.
 */
#define OSAL_INVOKE_TIMEOUT(_invoke_params, _action, _timeout)   (OSAL_Invoke_Sync_To_Destination(_invoke_params, _timeout) && _action && OSAL_Invoke_Release_Destination(_invoke_params))

/**
 * @brief this macro is used to invoke the action.
 * This macro is very similar to OSAL_INVOKE with one exception - if source is a thread then it is never blocked. If invoke needs waiting, it will fail.
 *
 * @return OSAL_TRUE if invoke succeeded, OSAL_FALSE otherwise.
 *
 * @param _invoke_params pointer to OSAL_Invoke_XT structure with parameters of the destination.
 * @param _action the code to be invoked to the destination.
 */
#define OSAL_TRY_INVOKE(_invoke_params, _action)                 (OSAL_Invoke_Sync_To_Destination(_invoke_params, 0) && _action && OSAL_Invoke_Release_Destination(_invoke_params))

/** @} */ // end of Invoke

#endif
