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

#ifndef OSAL_H_
#define OSAL_H_

#ifndef STD_LIBS_H_
#include "std_libs.h"
#endif

#ifndef OSAL_CFG_H_
#include "osal_cfg.h"
#endif

#ifndef OSAL_COMMON_TYPES_H_
#include "osal_common_types.h"
#endif

#ifndef OSAL_PUBLIC_MACRO_H_
#include "osal_public_macro.h"
#endif

/** @defgroup Optimization
 *  @brief Defines priorities for OSAL implementation optimization. Higher value means it is more important.
 *  Using these priorities we do not decide about only one aspect but more - we simply define what is most important,
 *  what less and what we can sacrify (using smalest value).
 *  @{
 */

#ifndef OSAL_OPTIMIZATION_BY_SPEED_PRIORITY
#define OSAL_OPTIMIZATION_BY_SPEED_PRIORITY                    2
#endif
#ifndef OSAL_OPTIMIZATION_BY_RAM_CONSUMPTION_PRIORITY
#define OSAL_OPTIMIZATION_BY_RAM_CONSUMPTION_PRIORITY          3
#endif
#ifndef OSAL_OPTIMIZATION_BY_PROGRAM_CONSUMPTION_PRIORITY
#define OSAL_OPTIMIZATION_BY_PROGRAM_CONSUMPTION_PRIORITY      0
#endif

/** @} */ // end of Optimization

#ifndef OSAL_LIB_LISTS_H_
#include "osal_lib_lists.h"
#endif

#ifndef OSAL_LIB_TREES_H_
#include "osal_lib_trees.h"
#endif

#ifndef OSAL_ALLOC_H_
#include "osal_alloc.h"
#endif

#ifndef OSAL_TIME_H_
#include "osal_time.h"
#endif

#ifndef OSAL_CONTEXT_H_
#include "osal_context.h"
#endif

#ifndef OSAL_SEMAPHORE_H_
#include "osal_semaphore.h"
#endif

#ifndef OSAL_MUTEX_H_
#include "osal_mutex.h"
#endif

#ifndef OSAL_MESSAGE_H_
#include "osal_message.h"
#endif

#ifndef OSAL_THREAD_H_
#include "osal_thread.h"
#endif

#ifndef OSAL_INTERRUPT_H_
#include "osal_interrupt.h"
#endif

#ifndef OSAL_INVOKE_H_
#include "osal_invoke.h"
#endif

#ifndef OSAL_DBG_H_
#include "osal_dbg.h"
#endif

/**
 * @brief Initializes OS engine
 */
void OSAL_Init (void);

#endif
