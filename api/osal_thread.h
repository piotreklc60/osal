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

#ifndef OSAL_THREAD_H_
#define OSAL_THREAD_H_

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

#ifndef OSAL_SEMAPHORE_H_
#include "osal_semaphore.h"
#endif

#ifndef OSAL_MESSAGE_H_
#include "osal_message.h"
#endif

/** @defgroup Thread Operating System Abstraction Layer - Threads management
 *  @brief Creating, destroying, suspending, resuming.
 *  @{
 */

#ifndef OSAL_THREAD_SUPPORT_CREATE_STATIC
#define OSAL_THREAD_SUPPORT_CREATE_STATIC       OSAL_FEATURE_NOT_PRESENT
#endif

#ifndef OSAL_THREAD_PARAMS_XT_EXTERNAL
typedef struct OSAL_Thread_Params_eXtendedTag
{
   /* OSAL_Context_Tracking_Params_XT structure with name "tracking" MUST be on the begining of OSAL_Thread_Params_XT structure */
   OSAL_Context_Tracking_Params_XT  tracking;
   void                            *os_handle;
   OSAL_Message_Queue_XT           *queue;
}OSAL_Thread_Params_XT;
#endif

#ifndef OSAL_STACK_DEPTH_DT_EXTERNAL
typedef uint_fast16_t OSAL_Thread_Stack_Depth_DT;
#endif

#ifndef OSAL_STACK_DEPTH_DT_EXTERNAL
typedef uint_fast8_t OSAL_Thread_Priority_DT;
#endif

#ifndef OSAL_THREAD_HT_EXTERNAL
typedef void (*OSAL_Thread_HT) (void *parameters);
#endif

#if(OSAL_FEATURE_PRESENT == OSAL_THREAD_SUPPORT_CREATE_STATIC)
#ifndef OSAL_THREAD_STATIC_PARAMS_XT_EXTERNAL
#error "For static thread support there is needed to define OSAL_Thread_Static_Params_XT structure proper for your OS!"
#endif
#endif

/**
 * @brief Creates thread
 *
 * @param thread_func pointer to the function which will be the thread body.
 * @param thread_func_params pointer to data which will be provided to thread function in the moment of its start.
 * THIS PARAMETER CANNOT BE DELETED AS LONG AS THREAD EXECUTES.
 * @param path string with thread path. It is also the thread name.
 * @param stack_size size of stack created for this thread. if 0 then default value will be used.
 * @param priority thread priority - bigger value means bigger priority.
 * @param fixed_thread_id number of the thread we want to get. It is useful if user want to assign threads numbers
 * during program designing. If thread number shall be assigned dynamically, this parameter shall be set to 0.
 * @return thread_id if creating thread succeeded; OSAL_MAX_NUM_CONTEXTS otherwise
 */
OSAL_Context_Id_XT OSAL_Thread_Create(
   OSAL_Thread_HT             thread_func,
   void                      *thread_func_params,
   const char                *path,
   OSAL_Thread_Stack_Depth_DT stack_size,
   OSAL_Thread_Priority_DT    priority,
   OSAL_Context_Unique_Id_DT  fixed_thread_id);

#if(OSAL_FEATURE_PRESENT == OSAL_THREAD_SUPPORT_CREATE_STATIC)
/**
 * @brief Creates thread
 *
 * @param thread_func pointer to the function which will be the thread body.
 * @param thread_func_params pointer to data which will be provided to thread function in the moment of its start.
 * THIS PARAMETER CANNOT BE DELETED AS LONG AS THREAD EXECUTES.
 * @param thread_static_params pointer to the thread parameters.
 * THIS PARAMETER CANNOT BE DELETED AS LONG AS THREAD EXECUTES.
 * @param path string with thread path. It is also the thread name.
 * THIS PARAMETER CANNOT BE DELETED AS LONG AS THREAD EXECUTES.
 * @param stack pointer to the buffer which shall be used as thread stack.
 * THIS PARAMETER CANNOT BE DELETED AS LONG AS THREAD EXECUTES.
 * @param stack_size size of stack created for this thread. if 0 then default value will be used.
 * @param priority thread priority - bigger value means bigger priority.
 * @param fixed_thread_id number of the thread we want to get. It is useful if user want to assign threads numbers
 * during program designing. If thread number shall be assigned dynamically, this parameter shall be set to 0.
 * @return thread_id if creating thread succeeded; OSAL_MAX_NUM_CONTEXTS otherwise
 */
OSAL_Context_Id_XT OSAL_Thread_Create_Static(
   OSAL_Thread_HT                thread_func,
   void                         *thread_func_params,
   OSAL_Thread_Static_Params_XT *thread_static_params,
   const char                   *path,
   uint8_t                      *stack,
   OSAL_Thread_Stack_Depth_DT    stack_size,
   OSAL_Thread_Priority_DT       priority,
   OSAL_Context_Unique_Id_DT     fixed_thread_id);
#endif

/**
 * @brief This function destroys thread. If context_id is empty (all zeroes) then thread which calling the function will be destroyed.
 *
 * @param context_id parameters of the thread to be destroyed.
 */
void OSAL_Thread_Destroy(OSAL_Context_Id_XT *context_id);

/**
 * @brief Suspends thread. If context_id is empty (all zeroes) then thread which calling the function will be suspended.
 *
 * @param context_id parameters of the thread to be suspended.
 */
void OSAL_Thread_Suspend(OSAL_Context_Id_XT *context_id);

/**
 * @brief Resumes thread.
 *
 * @param context_id parameters of the thread to be resumed.
 */
void OSAL_Thread_Resume(OSAL_Context_Id_XT *context_id);

/**
 * Gets pointer to thread parameters.
 *
 * @param context_id parameters of the thread for which we request parameters. If invalid then parameters of the current thread will be returned.
 @result thread parameters pointer or OSAL_MAKE_INVALID_PTR(OSAL_Thread_Params_XT) if thread not found.
 */
OSAL_Thread_Params_XT *OSAL_Get_Thread_Params(OSAL_Context_Id_XT *context_id);


/** @} */ // end of Thread

#endif
