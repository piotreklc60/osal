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

#ifndef OSAL_INTERRUPT_H_
#define OSAL_INTERRUPT_H_

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

/** @defgroup Thread Operating System Abstraction Layer - Interrupts management
 *  @brief Getting the name of each interrupt
 *  @{
 */

#ifndef OSAL_INTERRUPT_PARAMS_XT_EXTERNAL
typedef struct OSAL_Interrupt_Params_eXtendedTag
{
   /* OSAL_Context_Tracking_Params_XT structure with name "tracking" MUST be on the begining of OSAL_Interrupt_Params_XT structure */
   OSAL_Context_Tracking_Params_XT  tracking;
#if(OSAL_FEATURE_PRESENT == OSAL_ALLOW_QUEUES_IN_INTERRUPTS)
   OSAL_Message_Queue_XT           *queue;
#endif
}OSAL_Interrupt_Params_XT;
#endif

/**
 * @brief this is a function which must be defined for each processor independently. It is responsible for reading interrupt name/path.
 *
 * @param irq_id interrupt number for which we want to read the name.
 * @result pointer to ASCII string with interrupt name if irq_id is valid, pointer to string "---" otherwise.
 */
const char *OSAL_Get_Interrupt_Name(OSAL_Context_Unique_Id_DT irq_id);

/** @} */ // end of Interrupt

#endif
