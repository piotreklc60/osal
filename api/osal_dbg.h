/** ---------------------------------------- LICENSE SECTION -------------------------------------------------------------------
 *
 * Copyright (c) 2024 Piotr Wojtowicz
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

#ifndef OSAL_DBG_H_
#define OSAL_DBG_H_



#ifdef OSAL_USE_IOCMD
#include "iocmd.h"

/**
 * Following groups are used by OSAL library and must be configured correctly:
 * OSAL_DBG
 * OSAL_DBG_LISTS
 * OSAL_DBG_TREES
 * OSAL_DBG_ALLOC
 * OSAL_DBG_CONTEXT
 * OSAL_DBG_CONTEXT_STATUS
 * OSAL_DBG_CONTEXT_INVALID_PARAMS
 * OSAL_DBG_THREAD
 * OSAL_DBG_TIME
 * OSAL_DBG_SEMAPHORE
 * OSAL_DBG_MUTEX
 * OSAL_DBG_INVOKE
 */

#define OSAL_COMPILATION_SWITCH_LOG(id, level)                                                        IOCMD_COMPILATION_SWITCH_LOG(id, level)
#define OSAL_COMPILATION_SWITCH_ENT(id)                                                               IOCMD_COMPILATION_SWITCH_ENT(id)

#define OSAL_ENTER_FUNC(id)                                                                           IOCMD_ENTER_FUNC(id)

#define OSAL_EXIT_FUNC(id)                                                                            IOCMD_EXIT_FUNC(id)

#define OSAL_EMERG(id, format)                                                                        IOCMD_EMERG(id, format)
#define OSAL_EMERG_1(id,  format, a1)                                                                 IOCMD_EMERG_1(id,  format, a1)
#define OSAL_EMERG_2(id,  format, a1, a2)                                                             IOCMD_EMERG_2(id,  format, a1, a2)
#define OSAL_EMERG_3(id,  format, a1, a2, a3)                                                         IOCMD_EMERG_3(id,  format, a1, a2, a3)
#define OSAL_EMERG_4(id,  format, a1, a2, a3, a4)                                                     IOCMD_EMERG_4(id,  format, a1, a2, a3, a4)
#define OSAL_EMERG_5(id,  format, a1, a2, a3, a4, a5)                                                 IOCMD_EMERG_5(id,  format, a1, a2, a3, a4, a5)
#define OSAL_EMERG_6(id,  format, a1, a2, a3, a4, a5, a6)                                             IOCMD_EMERG_6(id,  format, a1, a2, a3, a4, a5, a6)
#define OSAL_EMERG_7(id,  format, a1, a2, a3, a4, a5, a6, a7)                                         IOCMD_EMERG_7(id,  format, a1, a2, a3, a4, a5, a6, a7)
#define OSAL_EMERG_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)                                     IOCMD_EMERG_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)
#define OSAL_EMERG_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)                                 IOCMD_EMERG_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define OSAL_EMERG_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)                             IOCMD_EMERG_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#define OSAL_EMERG_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)                         IOCMD_EMERG_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#define OSAL_EMERG_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)                     IOCMD_EMERG_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#define OSAL_EMERG_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)                 IOCMD_EMERG_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#define OSAL_EMERG_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)             IOCMD_EMERG_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#define OSAL_EMERG_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)         IOCMD_EMERG_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#define OSAL_EMERG_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)     IOCMD_EMERG_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#define OSAL_ALERT(id, format)                                                                        IOCMD_ALERT(id, format)
#define OSAL_ALERT_1(id,  format, a1)                                                                 IOCMD_ALERT_1(id,  format, a1)
#define OSAL_ALERT_2(id,  format, a1, a2)                                                             IOCMD_ALERT_2(id,  format, a1, a2)
#define OSAL_ALERT_3(id,  format, a1, a2, a3)                                                         IOCMD_ALERT_3(id,  format, a1, a2, a3)
#define OSAL_ALERT_4(id,  format, a1, a2, a3, a4)                                                     IOCMD_ALERT_4(id,  format, a1, a2, a3, a4)
#define OSAL_ALERT_5(id,  format, a1, a2, a3, a4, a5)                                                 IOCMD_ALERT_5(id,  format, a1, a2, a3, a4, a5)
#define OSAL_ALERT_6(id,  format, a1, a2, a3, a4, a5, a6)                                             IOCMD_ALERT_6(id,  format, a1, a2, a3, a4, a5, a6)
#define OSAL_ALERT_7(id,  format, a1, a2, a3, a4, a5, a6, a7)                                         IOCMD_ALERT_7(id,  format, a1, a2, a3, a4, a5, a6, a7)
#define OSAL_ALERT_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)                                     IOCMD_ALERT_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)
#define OSAL_ALERT_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)                                 IOCMD_ALERT_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define OSAL_ALERT_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)                             IOCMD_ALERT_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#define OSAL_ALERT_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)                         IOCMD_ALERT_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#define OSAL_ALERT_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)                     IOCMD_ALERT_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#define OSAL_ALERT_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)                 IOCMD_ALERT_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#define OSAL_ALERT_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)             IOCMD_ALERT_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#define OSAL_ALERT_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)         IOCMD_ALERT_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#define OSAL_ALERT_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)     IOCMD_ALERT_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#define OSAL_CRIT(id, format)                                                                         IOCMD_CRIT(id, format)
#define OSAL_CRIT_1(id,  format, a1)                                                                  IOCMD_CRIT_1(id,  format, a1)
#define OSAL_CRIT_2(id,  format, a1, a2)                                                              IOCMD_CRIT_2(id,  format, a1, a2)
#define OSAL_CRIT_3(id,  format, a1, a2, a3)                                                          IOCMD_CRIT_3(id,  format, a1, a2, a3)
#define OSAL_CRIT_4(id,  format, a1, a2, a3, a4)                                                      IOCMD_CRIT_4(id,  format, a1, a2, a3, a4)
#define OSAL_CRIT_5(id,  format, a1, a2, a3, a4, a5)                                                  IOCMD_CRIT_5(id,  format, a1, a2, a3, a4, a5)
#define OSAL_CRIT_6(id,  format, a1, a2, a3, a4, a5, a6)                                              IOCMD_CRIT_6(id,  format, a1, a2, a3, a4, a5, a6)
#define OSAL_CRIT_7(id,  format, a1, a2, a3, a4, a5, a6, a7)                                          IOCMD_CRIT_7(id,  format, a1, a2, a3, a4, a5, a6, a7)
#define OSAL_CRIT_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)                                      IOCMD_CRIT_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)
#define OSAL_CRIT_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)                                  IOCMD_CRIT_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define OSAL_CRIT_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)                              IOCMD_CRIT_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#define OSAL_CRIT_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)                          IOCMD_CRIT_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#define OSAL_CRIT_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)                      IOCMD_CRIT_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#define OSAL_CRIT_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)                  IOCMD_CRIT_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#define OSAL_CRIT_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)              IOCMD_CRIT_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#define OSAL_CRIT_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)          IOCMD_CRIT_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#define OSAL_CRIT_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)      IOCMD_CRIT_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#define OSAL_ERROR(id, format)                                                                        IOCMD_ERROR(id, format)
#define OSAL_ERROR_1(id,  format, a1)                                                                 IOCMD_ERROR_1(id,  format, a1)
#define OSAL_ERROR_2(id,  format, a1, a2)                                                             IOCMD_ERROR_2(id,  format, a1, a2)
#define OSAL_ERROR_3(id,  format, a1, a2, a3)                                                         IOCMD_ERROR_3(id,  format, a1, a2, a3)
#define OSAL_ERROR_4(id,  format, a1, a2, a3, a4)                                                     IOCMD_ERROR_4(id,  format, a1, a2, a3, a4)
#define OSAL_ERROR_5(id,  format, a1, a2, a3, a4, a5)                                                 IOCMD_ERROR_5(id,  format, a1, a2, a3, a4, a5)
#define OSAL_ERROR_6(id,  format, a1, a2, a3, a4, a5, a6)                                             IOCMD_ERROR_6(id,  format, a1, a2, a3, a4, a5, a6)
#define OSAL_ERROR_7(id,  format, a1, a2, a3, a4, a5, a6, a7)                                         IOCMD_ERROR_7(id,  format, a1, a2, a3, a4, a5, a6, a7)
#define OSAL_ERROR_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)                                     IOCMD_ERROR_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)
#define OSAL_ERROR_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)                                 IOCMD_ERROR_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define OSAL_ERROR_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)                             IOCMD_ERROR_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#define OSAL_ERROR_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)                         IOCMD_ERROR_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#define OSAL_ERROR_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)                     IOCMD_ERROR_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#define OSAL_ERROR_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)                 IOCMD_ERROR_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#define OSAL_ERROR_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)             IOCMD_ERROR_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#define OSAL_ERROR_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)         IOCMD_ERROR_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#define OSAL_ERROR_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)     IOCMD_ERROR_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#define OSAL_WARN(id, format)                                                                         IOCMD_WARN(id, format)
#define OSAL_WARN_1(id,  format, a1)                                                                  IOCMD_WARN_1(id,  format, a1)
#define OSAL_WARN_2(id,  format, a1, a2)                                                              IOCMD_WARN_2(id,  format, a1, a2)
#define OSAL_WARN_3(id,  format, a1, a2, a3)                                                          IOCMD_WARN_3(id,  format, a1, a2, a3)
#define OSAL_WARN_4(id,  format, a1, a2, a3, a4)                                                      IOCMD_WARN_4(id,  format, a1, a2, a3, a4)
#define OSAL_WARN_5(id,  format, a1, a2, a3, a4, a5)                                                  IOCMD_WARN_5(id,  format, a1, a2, a3, a4, a5)
#define OSAL_WARN_6(id,  format, a1, a2, a3, a4, a5, a6)                                              IOCMD_WARN_6(id,  format, a1, a2, a3, a4, a5, a6)
#define OSAL_WARN_7(id,  format, a1, a2, a3, a4, a5, a6, a7)                                          IOCMD_WARN_7(id,  format, a1, a2, a3, a4, a5, a6, a7)
#define OSAL_WARN_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)                                      IOCMD_WARN_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)
#define OSAL_WARN_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)                                  IOCMD_WARN_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define OSAL_WARN_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)                              IOCMD_WARN_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#define OSAL_WARN_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)                          IOCMD_WARN_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#define OSAL_WARN_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)                      IOCMD_WARN_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#define OSAL_WARN_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)                  IOCMD_WARN_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#define OSAL_WARN_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)              IOCMD_WARN_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#define OSAL_WARN_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)          IOCMD_WARN_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#define OSAL_WARN_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)      IOCMD_WARN_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#define OSAL_NOTICE(id, format)                                                                       IOCMD_NOTICE(id, format)
#define OSAL_NOTICE_1(id,  format, a1)                                                                IOCMD_NOTICE_1(id,  format, a1)
#define OSAL_NOTICE_2(id,  format, a1, a2)                                                            IOCMD_NOTICE_2(id,  format, a1, a2)
#define OSAL_NOTICE_3(id,  format, a1, a2, a3)                                                        IOCMD_NOTICE_3(id,  format, a1, a2, a3)
#define OSAL_NOTICE_4(id,  format, a1, a2, a3, a4)                                                    IOCMD_NOTICE_4(id,  format, a1, a2, a3, a4)
#define OSAL_NOTICE_5(id,  format, a1, a2, a3, a4, a5)                                                IOCMD_NOTICE_5(id,  format, a1, a2, a3, a4, a5)
#define OSAL_NOTICE_6(id,  format, a1, a2, a3, a4, a5, a6)                                            IOCMD_NOTICE_6(id,  format, a1, a2, a3, a4, a5, a6)
#define OSAL_NOTICE_7(id,  format, a1, a2, a3, a4, a5, a6, a7)                                        IOCMD_NOTICE_7(id,  format, a1, a2, a3, a4, a5, a6, a7)
#define OSAL_NOTICE_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)                                    IOCMD_NOTICE_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)
#define OSAL_NOTICE_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)                                IOCMD_NOTICE_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define OSAL_NOTICE_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)                            IOCMD_NOTICE_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#define OSAL_NOTICE_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)                        IOCMD_NOTICE_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#define OSAL_NOTICE_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)                    IOCMD_NOTICE_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#define OSAL_NOTICE_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)                IOCMD_NOTICE_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#define OSAL_NOTICE_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)            IOCMD_NOTICE_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#define OSAL_NOTICE_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)        IOCMD_NOTICE_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#define OSAL_NOTICE_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)    IOCMD_NOTICE_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#define OSAL_INFO_HI(id, format)                                                                      IOCMD_INFO_HI(id, format)
#define OSAL_INFO_HI_1(id,  format, a1)                                                               IOCMD_INFO_HI_1(id,  format, a1)
#define OSAL_INFO_HI_2(id,  format, a1, a2)                                                           IOCMD_INFO_HI_2(id,  format, a1, a2)
#define OSAL_INFO_HI_3(id,  format, a1, a2, a3)                                                       IOCMD_INFO_HI_3(id,  format, a1, a2, a3)
#define OSAL_INFO_HI_4(id,  format, a1, a2, a3, a4)                                                   IOCMD_INFO_HI_4(id,  format, a1, a2, a3, a4)
#define OSAL_INFO_HI_5(id,  format, a1, a2, a3, a4, a5)                                               IOCMD_INFO_HI_5(id,  format, a1, a2, a3, a4, a5)
#define OSAL_INFO_HI_6(id,  format, a1, a2, a3, a4, a5, a6)                                           IOCMD_INFO_HI_6(id,  format, a1, a2, a3, a4, a5, a6)
#define OSAL_INFO_HI_7(id,  format, a1, a2, a3, a4, a5, a6, a7)                                       IOCMD_INFO_HI_7(id,  format, a1, a2, a3, a4, a5, a6, a7)
#define OSAL_INFO_HI_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)                                   IOCMD_INFO_HI_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)
#define OSAL_INFO_HI_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)                               IOCMD_INFO_HI_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define OSAL_INFO_HI_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)                           IOCMD_INFO_HI_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#define OSAL_INFO_HI_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)                       IOCMD_INFO_HI_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#define OSAL_INFO_HI_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)                   IOCMD_INFO_HI_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#define OSAL_INFO_HI_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)               IOCMD_INFO_HI_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#define OSAL_INFO_HI_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)           IOCMD_INFO_HI_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#define OSAL_INFO_HI_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)       IOCMD_INFO_HI_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#define OSAL_INFO_HI_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)   IOCMD_INFO_HI_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#define OSAL_INFO_MID(id, format)                                                                     IOCMD_INFO_MID(id, format)
#define OSAL_INFO_MID_1(id,  format, a1)                                                              IOCMD_INFO_MID_1(id,  format, a1)
#define OSAL_INFO_MID_2(id,  format, a1, a2)                                                          IOCMD_INFO_MID_2(id,  format, a1, a2)
#define OSAL_INFO_MID_3(id,  format, a1, a2, a3)                                                      IOCMD_INFO_MID_3(id,  format, a1, a2, a3)
#define OSAL_INFO_MID_4(id,  format, a1, a2, a3, a4)                                                  IOCMD_INFO_MID_4(id,  format, a1, a2, a3, a4)
#define OSAL_INFO_MID_5(id,  format, a1, a2, a3, a4, a5)                                              IOCMD_INFO_MID_5(id,  format, a1, a2, a3, a4, a5)
#define OSAL_INFO_MID_6(id,  format, a1, a2, a3, a4, a5, a6)                                          IOCMD_INFO_MID_6(id,  format, a1, a2, a3, a4, a5, a6)
#define OSAL_INFO_MID_7(id,  format, a1, a2, a3, a4, a5, a6, a7)                                      IOCMD_INFO_MID_7(id,  format, a1, a2, a3, a4, a5, a6, a7)
#define OSAL_INFO_MID_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)                                  IOCMD_INFO_MID_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)
#define OSAL_INFO_MID_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)                              IOCMD_INFO_MID_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define OSAL_INFO_MID_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)                          IOCMD_INFO_MID_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#define OSAL_INFO_MID_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)                      IOCMD_INFO_MID_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#define OSAL_INFO_MID_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)                  IOCMD_INFO_MID_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#define OSAL_INFO_MID_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)              IOCMD_INFO_MID_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#define OSAL_INFO_MID_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)          IOCMD_INFO_MID_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#define OSAL_INFO_MID_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)      IOCMD_INFO_MID_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#define OSAL_INFO_MID_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)  IOCMD_INFO_MID_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#define OSAL_INFO_LO(id, format)                                                                      IOCMD_INFO_LO(id, format)
#define OSAL_INFO_LO_1(id,  format, a1)                                                               IOCMD_INFO_LO_1(id,  format, a1)
#define OSAL_INFO_LO_2(id,  format, a1, a2)                                                           IOCMD_INFO_LO_2(id,  format, a1, a2)
#define OSAL_INFO_LO_3(id,  format, a1, a2, a3)                                                       IOCMD_INFO_LO_3(id,  format, a1, a2, a3)
#define OSAL_INFO_LO_4(id,  format, a1, a2, a3, a4)                                                   IOCMD_INFO_LO_4(id,  format, a1, a2, a3, a4)
#define OSAL_INFO_LO_5(id,  format, a1, a2, a3, a4, a5)                                               IOCMD_INFO_LO_5(id,  format, a1, a2, a3, a4, a5)
#define OSAL_INFO_LO_6(id,  format, a1, a2, a3, a4, a5, a6)                                           IOCMD_INFO_LO_6(id,  format, a1, a2, a3, a4, a5, a6)
#define OSAL_INFO_LO_7(id,  format, a1, a2, a3, a4, a5, a6, a7)                                       IOCMD_INFO_LO_7(id,  format, a1, a2, a3, a4, a5, a6, a7)
#define OSAL_INFO_LO_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)                                   IOCMD_INFO_LO_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)
#define OSAL_INFO_LO_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)                               IOCMD_INFO_LO_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define OSAL_INFO_LO_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)                           IOCMD_INFO_LO_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#define OSAL_INFO_LO_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)                       IOCMD_INFO_LO_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#define OSAL_INFO_LO_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)                   IOCMD_INFO_LO_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#define OSAL_INFO_LO_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)               IOCMD_INFO_LO_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#define OSAL_INFO_LO_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)           IOCMD_INFO_LO_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#define OSAL_INFO_LO_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)       IOCMD_INFO_LO_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#define OSAL_INFO_LO_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)   IOCMD_INFO_LO_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#define OSAL_DEBUG_HI(id, format)                                                                     IOCMD_DEBUG_HI(id, format)
#define OSAL_DEBUG_HI_1(id,  format, a1)                                                              IOCMD_DEBUG_HI_1(id,  format, a1)
#define OSAL_DEBUG_HI_2(id,  format, a1, a2)                                                          IOCMD_DEBUG_HI_2(id,  format, a1, a2)
#define OSAL_DEBUG_HI_3(id,  format, a1, a2, a3)                                                      IOCMD_DEBUG_HI_3(id,  format, a1, a2, a3)
#define OSAL_DEBUG_HI_4(id,  format, a1, a2, a3, a4)                                                  IOCMD_DEBUG_HI_4(id,  format, a1, a2, a3, a4)
#define OSAL_DEBUG_HI_5(id,  format, a1, a2, a3, a4, a5)                                              IOCMD_DEBUG_HI_5(id,  format, a1, a2, a3, a4, a5)
#define OSAL_DEBUG_HI_6(id,  format, a1, a2, a3, a4, a5, a6)                                          IOCMD_DEBUG_HI_6(id,  format, a1, a2, a3, a4, a5, a6)
#define OSAL_DEBUG_HI_7(id,  format, a1, a2, a3, a4, a5, a6, a7)                                      IOCMD_DEBUG_HI_7(id,  format, a1, a2, a3, a4, a5, a6, a7)
#define OSAL_DEBUG_HI_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)                                  IOCMD_DEBUG_HI_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)
#define OSAL_DEBUG_HI_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)                              IOCMD_DEBUG_HI_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define OSAL_DEBUG_HI_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)                          IOCMD_DEBUG_HI_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#define OSAL_DEBUG_HI_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)                      IOCMD_DEBUG_HI_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#define OSAL_DEBUG_HI_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)                  IOCMD_DEBUG_HI_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#define OSAL_DEBUG_HI_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)              IOCMD_DEBUG_HI_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#define OSAL_DEBUG_HI_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)          IOCMD_DEBUG_HI_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#define OSAL_DEBUG_HI_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)      IOCMD_DEBUG_HI_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#define OSAL_DEBUG_HI_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)  IOCMD_DEBUG_HI_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#define OSAL_DEBUG_MID(id, format)                                                                    IOCMD_DEBUG_MID(id, format)
#define OSAL_DEBUG_MID_1(id,  format, a1)                                                             IOCMD_DEBUG_MID_1(id,  format, a1)
#define OSAL_DEBUG_MID_2(id,  format, a1, a2)                                                         IOCMD_DEBUG_MID_2(id,  format, a1, a2)
#define OSAL_DEBUG_MID_3(id,  format, a1, a2, a3)                                                     IOCMD_DEBUG_MID_3(id,  format, a1, a2, a3)
#define OSAL_DEBUG_MID_4(id,  format, a1, a2, a3, a4)                                                 IOCMD_DEBUG_MID_4(id,  format, a1, a2, a3, a4)
#define OSAL_DEBUG_MID_5(id,  format, a1, a2, a3, a4, a5)                                             IOCMD_DEBUG_MID_5(id,  format, a1, a2, a3, a4, a5)
#define OSAL_DEBUG_MID_6(id,  format, a1, a2, a3, a4, a5, a6)                                         IOCMD_DEBUG_MID_6(id,  format, a1, a2, a3, a4, a5, a6)
#define OSAL_DEBUG_MID_7(id,  format, a1, a2, a3, a4, a5, a6, a7)                                     IOCMD_DEBUG_MID_7(id,  format, a1, a2, a3, a4, a5, a6, a7)
#define OSAL_DEBUG_MID_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)                                 IOCMD_DEBUG_MID_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)
#define OSAL_DEBUG_MID_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)                             IOCMD_DEBUG_MID_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define OSAL_DEBUG_MID_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)                         IOCMD_DEBUG_MID_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#define OSAL_DEBUG_MID_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)                     IOCMD_DEBUG_MID_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#define OSAL_DEBUG_MID_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)                 IOCMD_DEBUG_MID_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#define OSAL_DEBUG_MID_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)             IOCMD_DEBUG_MID_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#define OSAL_DEBUG_MID_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)         IOCMD_DEBUG_MID_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#define OSAL_DEBUG_MID_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)     IOCMD_DEBUG_MID_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#define OSAL_DEBUG_MID_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG) IOCMD_DEBUG_MID_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#define OSAL_DEBUG_LO(id, format)                                                                     IOCMD_DEBUG_LO(id, format)
#define OSAL_DEBUG_LO_1(id,  format, a1)                                                              IOCMD_DEBUG_LO_1(id,  format, a1)
#define OSAL_DEBUG_LO_2(id,  format, a1, a2)                                                          IOCMD_DEBUG_LO_2(id,  format, a1, a2)
#define OSAL_DEBUG_LO_3(id,  format, a1, a2, a3)                                                      IOCMD_DEBUG_LO_3(id,  format, a1, a2, a3)
#define OSAL_DEBUG_LO_4(id,  format, a1, a2, a3, a4)                                                  IOCMD_DEBUG_LO_4(id,  format, a1, a2, a3, a4)
#define OSAL_DEBUG_LO_5(id,  format, a1, a2, a3, a4, a5)                                              IOCMD_DEBUG_LO_5(id,  format, a1, a2, a3, a4, a5)
#define OSAL_DEBUG_LO_6(id,  format, a1, a2, a3, a4, a5, a6)                                          IOCMD_DEBUG_LO_6(id,  format, a1, a2, a3, a4, a5, a6)
#define OSAL_DEBUG_LO_7(id,  format, a1, a2, a3, a4, a5, a6, a7)                                      IOCMD_DEBUG_LO_7(id,  format, a1, a2, a3, a4, a5, a6, a7)
#define OSAL_DEBUG_LO_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)                                  IOCMD_DEBUG_LO_8(id,  format, a1, a2, a3, a4, a5, a6, a7, a8)
#define OSAL_DEBUG_LO_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)                              IOCMD_DEBUG_LO_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define OSAL_DEBUG_LO_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)                          IOCMD_DEBUG_LO_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#define OSAL_DEBUG_LO_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)                      IOCMD_DEBUG_LO_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#define OSAL_DEBUG_LO_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)                  IOCMD_DEBUG_LO_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#define OSAL_DEBUG_LO_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)              IOCMD_DEBUG_LO_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#define OSAL_DEBUG_LO_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)          IOCMD_DEBUG_LO_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#define OSAL_DEBUG_LO_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)      IOCMD_DEBUG_LO_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#define OSAL_DEBUG_LO_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)  IOCMD_DEBUG_LO_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)

#define OSAL_LOG_DATA_EMERG(      id, data, size, description)                                        IOCMD_LOG_DATA_EMERG(      id, data, size, description)
#define OSAL_LOG_DATA_EMERG_1(    id, data, size, description, a1)                                    IOCMD_LOG_DATA_EMERG_1(    id, data, size, description, a1)
#define OSAL_LOG_DATA_EMERG_2(    id, data, size, description, a1, a2)                                IOCMD_LOG_DATA_EMERG_2(    id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_EMERG_3(    id, data, size, description, a1, a2, a3)                            IOCMD_LOG_DATA_EMERG_3(    id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_ALERT(      id, data, size, description)                                        IOCMD_LOG_DATA_ALERT(      id, data, size, description)
#define OSAL_LOG_DATA_ALERT_1(    id, data, size, description, a1)                                    IOCMD_LOG_DATA_ALERT_1(    id, data, size, description, a1)
#define OSAL_LOG_DATA_ALERT_2(    id, data, size, description, a1, a2)                                IOCMD_LOG_DATA_ALERT_2(    id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_ALERT_3(    id, data, size, description, a1, a2, a3)                            IOCMD_LOG_DATA_ALERT_3(    id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_CRIT(       id, data, size, description)                                        IOCMD_LOG_DATA_CRIT(       id, data, size, description)
#define OSAL_LOG_DATA_CRIT_1(     id, data, size, description, a1)                                    IOCMD_LOG_DATA_CRIT_1(     id, data, size, description, a1)
#define OSAL_LOG_DATA_CRIT_2(     id, data, size, description, a1, a2)                                IOCMD_LOG_DATA_CRIT_2(     id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_CRIT_3(     id, data, size, description, a1, a2, a3)                            IOCMD_LOG_DATA_CRIT_3(     id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_ERROR(      id, data, size, description)                                        IOCMD_LOG_DATA_ERROR(      id, data, size, description)
#define OSAL_LOG_DATA_ERROR_1(    id, data, size, description, a1)                                    IOCMD_LOG_DATA_ERROR_1(    id, data, size, description, a1)
#define OSAL_LOG_DATA_ERROR_2(    id, data, size, description, a1, a2)                                IOCMD_LOG_DATA_ERROR_2(    id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_ERROR_3(    id, data, size, description, a1, a2, a3)                            IOCMD_LOG_DATA_ERROR_3(    id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_WARN(       id, data, size, description)                                        IOCMD_LOG_DATA_WARN(       id, data, size, description)
#define OSAL_LOG_DATA_WARN_1(     id, data, size, description, a1)                                    IOCMD_LOG_DATA_WARN_1(     id, data, size, description, a1)
#define OSAL_LOG_DATA_WARN_2(     id, data, size, description, a1, a2)                                IOCMD_LOG_DATA_WARN_2(     id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_WARN_3(     id, data, size, description, a1, a2, a3)                            IOCMD_LOG_DATA_WARN_3(     id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_NOTICE(     id, data, size, description)                                        IOCMD_LOG_DATA_NOTICE(     id, data, size, description)
#define OSAL_LOG_DATA_NOTICE_1(   id, data, size, description, a1)                                    IOCMD_LOG_DATA_NOTICE_1(   id, data, size, description, a1)
#define OSAL_LOG_DATA_NOTICE_2(   id, data, size, description, a1, a2)                                IOCMD_LOG_DATA_NOTICE_2(   id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_NOTICE_3(   id, data, size, description, a1, a2, a3)                            IOCMD_LOG_DATA_NOTICE_3(   id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_INFO_HI(    id, data, size, description)                                        IOCMD_LOG_DATA_INFO_HI(    id, data, size, description)
#define OSAL_LOG_DATA_INFO_HI_1(  id, data, size, description, a1)                                    IOCMD_LOG_DATA_INFO_HI_1(  id, data, size, description, a1)
#define OSAL_LOG_DATA_INFO_HI_2(  id, data, size, description, a1, a2)                                IOCMD_LOG_DATA_INFO_HI_2(  id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_INFO_HI_3(  id, data, size, description, a1, a2, a3)                            IOCMD_LOG_DATA_INFO_HI_3(  id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_INFO_MID(   id, data, size, description)                                        IOCMD_LOG_DATA_INFO_MID(   id, data, size, description)
#define OSAL_LOG_DATA_INFO_MID_1( id, data, size, description, a1)                                    IOCMD_LOG_DATA_INFO_MID_1( id, data, size, description, a1)
#define OSAL_LOG_DATA_INFO_MID_2( id, data, size, description, a1, a2)                                IOCMD_LOG_DATA_INFO_MID_2( id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_INFO_MID_3( id, data, size, description, a1, a2, a3)                            IOCMD_LOG_DATA_INFO_MID_3( id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_INFO_LO(    id, data, size, description)                                        IOCMD_LOG_DATA_INFO_LO(    id, data, size, description)
#define OSAL_LOG_DATA_INFO_LO_1(  id, data, size, description, a1)                                    IOCMD_LOG_DATA_INFO_LO_1(  id, data, size, description, a1)
#define OSAL_LOG_DATA_INFO_LO_2(  id, data, size, description, a1, a2)                                IOCMD_LOG_DATA_INFO_LO_2(  id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_INFO_LO_3(  id, data, size, description, a1, a2, a3)                            IOCMD_LOG_DATA_INFO_LO_3(  id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_DEBUG_HI(   id, data, size, description)                                        IOCMD_LOG_DATA_DEBUG_HI(   id, data, size, description)
#define OSAL_LOG_DATA_DEBUG_HI_1( id, data, size, description, a1)                                    IOCMD_LOG_DATA_DEBUG_HI_1( id, data, size, description, a1)
#define OSAL_LOG_DATA_DEBUG_HI_2( id, data, size, description, a1, a2)                                IOCMD_LOG_DATA_DEBUG_HI_2( id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_DEBUG_HI_3( id, data, size, description, a1, a2, a3)                            IOCMD_LOG_DATA_DEBUG_HI_3( id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_DEBUG_MID(  id, data, size, description)                                        IOCMD_LOG_DATA_DEBUG_MID(  id, data, size, description)
#define OSAL_LOG_DATA_DEBUG_MID_1(id, data, size, description, a1)                                    IOCMD_LOG_DATA_DEBUG_MID_1(id, data, size, description, a1)
#define OSAL_LOG_DATA_DEBUG_MID_2(id, data, size, description, a1, a2)                                IOCMD_LOG_DATA_DEBUG_MID_2(id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_DEBUG_MID_3(id, data, size, description, a1, a2, a3)                            IOCMD_LOG_DATA_DEBUG_MID_3(id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_DEBUG_LO(   id, data, size, description)                                        IOCMD_LOG_DATA_DEBUG_LO(   id, data, size, description)
#define OSAL_LOG_DATA_DEBUG_LO_1( id, data, size, description, a1)                                    IOCMD_LOG_DATA_DEBUG_LO_1( id, data, size, description, a1)
#define OSAL_LOG_DATA_DEBUG_LO_2( id, data, size, description, a1, a2)                                IOCMD_LOG_DATA_DEBUG_LO_2( id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_DEBUG_LO_3( id, data, size, description, a1, a2, a3)                            IOCMD_LOG_DATA_DEBUG_LO_3( id, data, size, description, a1, a2, a3)


#define OSAL_COMPARE_DATA_EMERG(      id, data1, size1, data2, size2, description)                    IOCMD_COMPARE_DATA_EMERG(      id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_EMERG_1(    id, data1, size1, data2, size2, description, a1)                IOCMD_COMPARE_DATA_EMERG_1(    id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_EMERG_2(    id, data1, size1, data2, size2, description, a1, a2)            IOCMD_COMPARE_DATA_EMERG_2(    id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_EMERG_3(    id, data1, size1, data2, size2, description, a1, a2, a3)        IOCMD_COMPARE_DATA_EMERG_3(    id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_ALERT(      id, data1, size1, data2, size2, description)                    IOCMD_COMPARE_DATA_ALERT(      id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_ALERT_1(    id, data1, size1, data2, size2, description, a1)                IOCMD_COMPARE_DATA_ALERT_1(    id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_ALERT_2(    id, data1, size1, data2, size2, description, a1, a2)            IOCMD_COMPARE_DATA_ALERT_2(    id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_ALERT_3(    id, data1, size1, data2, size2, description, a1, a2, a3)        IOCMD_COMPARE_DATA_ALERT_3(    id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_CRIT(       id, data1, size1, data2, size2, description)                    IOCMD_COMPARE_DATA_CRIT(       id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_CRIT_1(     id, data1, size1, data2, size2, description, a1)                IOCMD_COMPARE_DATA_CRIT_1(     id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_CRIT_2(     id, data1, size1, data2, size2, description, a1, a2)            IOCMD_COMPARE_DATA_CRIT_2(     id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_CRIT_3(     id, data1, size1, data2, size2, description, a1, a2, a3)        IOCMD_COMPARE_DATA_CRIT_3(     id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_ERROR(      id, data1, size1, data2, size2, description)                    IOCMD_COMPARE_DATA_ERROR(      id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_ERROR_1(    id, data1, size1, data2, size2, description, a1)                IOCMD_COMPARE_DATA_ERROR_1(    id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_ERROR_2(    id, data1, size1, data2, size2, description, a1, a2)            IOCMD_COMPARE_DATA_ERROR_2(    id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_ERROR_3(    id, data1, size1, data2, size2, description, a1, a2, a3)        IOCMD_COMPARE_DATA_ERROR_3(    id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_WARN(       id, data1, size1, data2, size2, description)                    IOCMD_COMPARE_DATA_WARN(       id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_WARN_1(     id, data1, size1, data2, size2, description, a1)                IOCMD_COMPARE_DATA_WARN_1(     id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_WARN_2(     id, data1, size1, data2, size2, description, a1, a2)            IOCMD_COMPARE_DATA_WARN_2(     id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_WARN_3(     id, data1, size1, data2, size2, description, a1, a2, a3)        IOCMD_COMPARE_DATA_WARN_3(     id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_NOTICE(     id, data1, size1, data2, size2, description)                    IOCMD_COMPARE_DATA_NOTICE(     id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_NOTICE_1(   id, data1, size1, data2, size2, description, a1)                IOCMD_COMPARE_DATA_NOTICE_1(   id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_NOTICE_2(   id, data1, size1, data2, size2, description, a1, a2)            IOCMD_COMPARE_DATA_NOTICE_2(   id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_NOTICE_3(   id, data1, size1, data2, size2, description, a1, a2, a3)        IOCMD_COMPARE_DATA_NOTICE_3(   id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_INFO_HI(    id, data1, size1, data2, size2, description)                    IOCMD_COMPARE_DATA_INFO_HI(    id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_INFO_HI_1(  id, data1, size1, data2, size2, description, a1)                IOCMD_COMPARE_DATA_INFO_HI_1(  id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_INFO_HI_2(  id, data1, size1, data2, size2, description, a1, a2)            IOCMD_COMPARE_DATA_INFO_HI_2(  id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_INFO_HI_3(  id, data1, size1, data2, size2, description, a1, a2, a3)        IOCMD_COMPARE_DATA_INFO_HI_3(  id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_INFO_MID(   id, data1, size1, data2, size2, description)                    IOCMD_COMPARE_DATA_INFO_MID(   id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_INFO_MID_1( id, data1, size1, data2, size2, description, a1)                IOCMD_COMPARE_DATA_INFO_MID_1( id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_INFO_MID_2( id, data1, size1, data2, size2, description, a1, a2)            IOCMD_COMPARE_DATA_INFO_MID_2( id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_INFO_MID_3( id, data1, size1, data2, size2, description, a1, a2, a3)        IOCMD_COMPARE_DATA_INFO_MID_3( id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_INFO_LO(    id, data1, size1, data2, size2, description)                    IOCMD_COMPARE_DATA_INFO_LO(    id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_INFO_LO_1(  id, data1, size1, data2, size2, description, a1)                IOCMD_COMPARE_DATA_INFO_LO_1(  id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_INFO_LO_2(  id, data1, size1, data2, size2, description, a1, a2)            IOCMD_COMPARE_DATA_INFO_LO_2(  id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_INFO_LO_3(  id, data1, size1, data2, size2, description, a1, a2, a3)        IOCMD_COMPARE_DATA_INFO_LO_3(  id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_DEBUG_HI(   id, data1, size1, data2, size2, description)                    IOCMD_COMPARE_DATA_DEBUG_HI(   id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_DEBUG_HI_1( id, data1, size1, data2, size2, description, a1)                IOCMD_COMPARE_DATA_DEBUG_HI_1( id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_DEBUG_HI_2( id, data1, size1, data2, size2, description, a1, a2)            IOCMD_COMPARE_DATA_DEBUG_HI_2( id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_DEBUG_HI_3( id, data1, size1, data2, size2, description, a1, a2, a3)        IOCMD_COMPARE_DATA_DEBUG_HI_3( id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_DEBUG_MID(  id, data1, size1, data2, size2, description)                    IOCMD_COMPARE_DATA_DEBUG_MID(  id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_DEBUG_MID_1(id, data1, size1, data2, size2, description, a1)                IOCMD_COMPARE_DATA_DEBUG_MID_1(id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_DEBUG_MID_2(id, data1, size1, data2, size2, description, a1, a2)            IOCMD_COMPARE_DATA_DEBUG_MID_2(id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_DEBUG_MID_3(id, data1, size1, data2, size2, description, a1, a2, a3)        IOCMD_COMPARE_DATA_DEBUG_MID_3(id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_DEBUG_LO(   id, data1, size1, data2, size2, description)                    IOCMD_COMPARE_DATA_DEBUG_LO(   id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_DEBUG_LO_1( id, data1, size1, data2, size2, description, a1)                IOCMD_COMPARE_DATA_DEBUG_LO_1( id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_DEBUG_LO_2( id, data1, size1, data2, size2, description, a1, a2)            IOCMD_COMPARE_DATA_DEBUG_LO_2( id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_DEBUG_LO_3( id, data1, size1, data2, size2, description, a1, a2, a3)        IOCMD_COMPARE_DATA_DEBUG_LO_3( id, data1, size1, data2, size2, description, a1, a2, a3)

#else

#define OSAL_COMPILATION_SWITCH_LOG(id, level)                                                        0
#define OSAL_COMPILATION_SWITCH_ENT(id)                                                               0

#ifndef OSAL_ENTER_FUNC
#define OSAL_ENTER_FUNC(id)
#endif

#ifndef OSAL_EXIT_FUNC
#define OSAL_EXIT_FUNC(id)
#endif

#ifndef OSAL_EMERG
#define OSAL_EMERG(id, format)
#endif

#ifndef OSAL_EMERG_1
#define OSAL_EMERG_1(id, format, a1)
#endif

#ifndef OSAL_EMERG_2
#define OSAL_EMERG_2(id, format, a1, a2)
#endif

#ifndef OSAL_EMERG_3
#define OSAL_EMERG_3(id, format, a1, a2, a3)
#endif

#ifndef OSAL_EMERG_4
#define OSAL_EMERG_4(id, format, a1, a2, a3, a4)
#endif

#ifndef OSAL_EMERG_5
#define OSAL_EMERG_5(id, format, a1, a2, a3, a4, a5)
#endif

#ifndef OSAL_EMERG_6
#define OSAL_EMERG_6(id, format, a1, a2, a3, a4, a5, a6)
#endif

#ifndef OSAL_EMERG_7
#define OSAL_EMERG_7(id, format, a1, a2, a3, a4, a5, a6, a7)
#endif

#ifndef OSAL_EMERG_8
#define OSAL_EMERG_8(id, format, a1, a2, a3, a4, a5, a6, a7, a8)
#endif

#ifndef OSAL_EMERG_9
#define OSAL_EMERG_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#endif

#ifndef OSAL_EMERG_10
#define OSAL_EMERG_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#endif

#ifndef OSAL_EMERG_11
#define OSAL_EMERG_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#endif

#ifndef OSAL_EMERG_12
#define OSAL_EMERG_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#endif

#ifndef OSAL_EMERG_13
#define OSAL_EMERG_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#endif

#ifndef OSAL_EMERG_14
#define OSAL_EMERG_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#endif

#ifndef OSAL_EMERG_15
#define OSAL_EMERG_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#endif

#ifndef OSAL_EMERG_16
#define OSAL_EMERG_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#endif

#ifndef OSAL_ALERT
#define OSAL_ALERT(id, format)
#endif

#ifndef OSAL_ALERT_1
#define OSAL_ALERT_1(id, format, a1)
#endif

#ifndef OSAL_ALERT_2
#define OSAL_ALERT_2(id, format, a1, a2)
#endif

#ifndef OSAL_ALERT_3
#define OSAL_ALERT_3(id, format, a1, a2, a3)
#endif

#ifndef OSAL_ALERT_4
#define OSAL_ALERT_4(id, format, a1, a2, a3, a4)
#endif

#ifndef OSAL_ALERT_5
#define OSAL_ALERT_5(id, format, a1, a2, a3, a4, a5)
#endif

#ifndef OSAL_ALERT_6
#define OSAL_ALERT_6(id, format, a1, a2, a3, a4, a5, a6)
#endif

#ifndef OSAL_ALERT_7
#define OSAL_ALERT_7(id, format, a1, a2, a3, a4, a5, a6, a7)
#endif

#ifndef OSAL_ALERT_8
#define OSAL_ALERT_8(id, format, a1, a2, a3, a4, a5, a6, a7, a8)
#endif

#ifndef OSAL_ALERT_9
#define OSAL_ALERT_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#endif

#ifndef OSAL_ALERT_10
#define OSAL_ALERT_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#endif

#ifndef OSAL_ALERT_11
#define OSAL_ALERT_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#endif

#ifndef OSAL_ALERT_12
#define OSAL_ALERT_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#endif

#ifndef OSAL_ALERT_13
#define OSAL_ALERT_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#endif

#ifndef OSAL_ALERT_14
#define OSAL_ALERT_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#endif

#ifndef OSAL_ALERT_15
#define OSAL_ALERT_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#endif

#ifndef OSAL_ALERT_16
#define OSAL_ALERT_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#endif

#ifndef OSAL_CRIT
#define OSAL_CRIT(id, format)
#endif

#ifndef OSAL_CRIT_1
#define OSAL_CRIT_1(id, format, a1)
#endif

#ifndef OSAL_CRIT_2
#define OSAL_CRIT_2(id, format, a1, a2)
#endif

#ifndef OSAL_CRIT_3
#define OSAL_CRIT_3(id, format, a1, a2, a3)
#endif

#ifndef OSAL_CRIT_4
#define OSAL_CRIT_4(id, format, a1, a2, a3, a4)
#endif

#ifndef OSAL_CRIT_5
#define OSAL_CRIT_5(id, format, a1, a2, a3, a4, a5)
#endif

#ifndef OSAL_CRIT_6
#define OSAL_CRIT_6(id, format, a1, a2, a3, a4, a5, a6)
#endif

#ifndef OSAL_CRIT_7
#define OSAL_CRIT_7(id, format, a1, a2, a3, a4, a5, a6, a7)
#endif

#ifndef OSAL_CRIT_8
#define OSAL_CRIT_8(id, format, a1, a2, a3, a4, a5, a6, a7, a8)
#endif

#ifndef OSAL_CRIT_9
#define OSAL_CRIT_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#endif

#ifndef OSAL_CRIT_10
#define OSAL_CRIT_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#endif

#ifndef OSAL_CRIT_11
#define OSAL_CRIT_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#endif

#ifndef OSAL_CRIT_12
#define OSAL_CRIT_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#endif

#ifndef OSAL_CRIT_13
#define OSAL_CRIT_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#endif

#ifndef OSAL_CRIT_14
#define OSAL_CRIT_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#endif

#ifndef OSAL_CRIT_15
#define OSAL_CRIT_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#endif

#ifndef OSAL_CRIT_16
#define OSAL_CRIT_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#endif

#ifndef OSAL_ERROR
#define OSAL_ERROR(id, format)
#endif

#ifndef OSAL_ERROR_1
#define OSAL_ERROR_1(id, format, a1)
#endif

#ifndef OSAL_ERROR_2
#define OSAL_ERROR_2(id, format, a1, a2)
#endif

#ifndef OSAL_ERROR_3
#define OSAL_ERROR_3(id, format, a1, a2, a3)
#endif

#ifndef OSAL_ERROR_4
#define OSAL_ERROR_4(id, format, a1, a2, a3, a4)
#endif

#ifndef OSAL_ERROR_5
#define OSAL_ERROR_5(id, format, a1, a2, a3, a4, a5)
#endif

#ifndef OSAL_ERROR_6
#define OSAL_ERROR_6(id, format, a1, a2, a3, a4, a5, a6)
#endif

#ifndef OSAL_ERROR_7
#define OSAL_ERROR_7(id, format, a1, a2, a3, a4, a5, a6, a7)
#endif

#ifndef OSAL_ERROR_8
#define OSAL_ERROR_8(id, format, a1, a2, a3, a4, a5, a6, a7, a8)
#endif

#ifndef OSAL_ERROR_9
#define OSAL_ERROR_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#endif

#ifndef OSAL_ERROR_10
#define OSAL_ERROR_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#endif

#ifndef OSAL_ERROR_11
#define OSAL_ERROR_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#endif

#ifndef OSAL_ERROR_12
#define OSAL_ERROR_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#endif

#ifndef OSAL_ERROR_13
#define OSAL_ERROR_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#endif

#ifndef OSAL_ERROR_14
#define OSAL_ERROR_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#endif

#ifndef OSAL_ERROR_15
#define OSAL_ERROR_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#endif

#ifndef OSAL_ERROR_16
#define OSAL_ERROR_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#endif

#ifndef OSAL_WARN
#define OSAL_WARN(id, format)
#endif

#ifndef OSAL_WARN_1
#define OSAL_WARN_1(id, format, a1)
#endif

#ifndef OSAL_WARN_2
#define OSAL_WARN_2(id, format, a1, a2)
#endif

#ifndef OSAL_WARN_3
#define OSAL_WARN_3(id, format, a1, a2, a3)
#endif

#ifndef OSAL_WARN_4
#define OSAL_WARN_4(id, format, a1, a2, a3, a4)
#endif

#ifndef OSAL_WARN_5
#define OSAL_WARN_5(id, format, a1, a2, a3, a4, a5)
#endif

#ifndef OSAL_WARN_6
#define OSAL_WARN_6(id, format, a1, a2, a3, a4, a5, a6)
#endif

#ifndef OSAL_WARN_7
#define OSAL_WARN_7(id, format, a1, a2, a3, a4, a5, a6, a7)
#endif

#ifndef OSAL_WARN_8
#define OSAL_WARN_8(id, format, a1, a2, a3, a4, a5, a6, a7, a8)
#endif

#ifndef OSAL_WARN_9
#define OSAL_WARN_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#endif

#ifndef OSAL_WARN_10
#define OSAL_WARN_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#endif

#ifndef OSAL_WARN_11
#define OSAL_WARN_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#endif

#ifndef OSAL_WARN_12
#define OSAL_WARN_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#endif

#ifndef OSAL_WARN_13
#define OSAL_WARN_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#endif

#ifndef OSAL_WARN_14
#define OSAL_WARN_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#endif

#ifndef OSAL_WARN_15
#define OSAL_WARN_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#endif

#ifndef OSAL_WARN_16
#define OSAL_WARN_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#endif

#ifndef OSAL_NOTICE
#define OSAL_NOTICE(id, format)
#endif

#ifndef OSAL_NOTICE_1
#define OSAL_NOTICE_1(id, format, a1)
#endif

#ifndef OSAL_NOTICE_2
#define OSAL_NOTICE_2(id, format, a1, a2)
#endif

#ifndef OSAL_NOTICE_3
#define OSAL_NOTICE_3(id, format, a1, a2, a3)
#endif

#ifndef OSAL_NOTICE_4
#define OSAL_NOTICE_4(id, format, a1, a2, a3, a4)
#endif

#ifndef OSAL_NOTICE_5
#define OSAL_NOTICE_5(id, format, a1, a2, a3, a4, a5)
#endif

#ifndef OSAL_NOTICE_6
#define OSAL_NOTICE_6(id, format, a1, a2, a3, a4, a5, a6)
#endif

#ifndef OSAL_NOTICE_7
#define OSAL_NOTICE_7(id, format, a1, a2, a3, a4, a5, a6, a7)
#endif

#ifndef OSAL_NOTICE_8
#define OSAL_NOTICE_8(id, format, a1, a2, a3, a4, a5, a6, a7, a8)
#endif

#ifndef OSAL_NOTICE_9
#define OSAL_NOTICE_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#endif

#ifndef OSAL_NOTICE_10
#define OSAL_NOTICE_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#endif

#ifndef OSAL_NOTICE_11
#define OSAL_NOTICE_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#endif

#ifndef OSAL_NOTICE_12
#define OSAL_NOTICE_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#endif

#ifndef OSAL_NOTICE_13
#define OSAL_NOTICE_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#endif

#ifndef OSAL_NOTICE_14
#define OSAL_NOTICE_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#endif

#ifndef OSAL_NOTICE_15
#define OSAL_NOTICE_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#endif

#ifndef OSAL_NOTICE_16
#define OSAL_NOTICE_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#endif

#ifndef OSAL_INFO_HI
#define OSAL_INFO_HI(id, format)
#endif

#ifndef OSAL_INFO_HI_1
#define OSAL_INFO_HI_1(id, format, a1)
#endif

#ifndef OSAL_INFO_HI_2
#define OSAL_INFO_HI_2(id, format, a1, a2)
#endif

#ifndef OSAL_INFO_HI_3
#define OSAL_INFO_HI_3(id, format, a1, a2, a3)
#endif

#ifndef OSAL_INFO_HI_4
#define OSAL_INFO_HI_4(id, format, a1, a2, a3, a4)
#endif

#ifndef OSAL_INFO_HI_5
#define OSAL_INFO_HI_5(id, format, a1, a2, a3, a4, a5)
#endif

#ifndef OSAL_INFO_HI_6
#define OSAL_INFO_HI_6(id, format, a1, a2, a3, a4, a5, a6)
#endif

#ifndef OSAL_INFO_HI_7
#define OSAL_INFO_HI_7(id, format, a1, a2, a3, a4, a5, a6, a7)
#endif

#ifndef OSAL_INFO_HI_8
#define OSAL_INFO_HI_8(id, format, a1, a2, a3, a4, a5, a6, a7, a8)
#endif

#ifndef OSAL_INFO_HI_9
#define OSAL_INFO_HI_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#endif

#ifndef OSAL_INFO_HI_10
#define OSAL_INFO_HI_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#endif

#ifndef OSAL_INFO_HI_11
#define OSAL_INFO_HI_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#endif

#ifndef OSAL_INFO_HI_12
#define OSAL_INFO_HI_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#endif

#ifndef OSAL_INFO_HI_13
#define OSAL_INFO_HI_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#endif

#ifndef OSAL_INFO_HI_14
#define OSAL_INFO_HI_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#endif

#ifndef OSAL_INFO_HI_15
#define OSAL_INFO_HI_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#endif

#ifndef OSAL_INFO_HI_16
#define OSAL_INFO_HI_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#endif

#ifndef OSAL_INFO_MID
#define OSAL_INFO_MID(id, format)
#endif

#ifndef OSAL_INFO_MID_1
#define OSAL_INFO_MID_1(id, format, a1)
#endif

#ifndef OSAL_INFO_MID_2
#define OSAL_INFO_MID_2(id, format, a1, a2)
#endif

#ifndef OSAL_INFO_MID_3
#define OSAL_INFO_MID_3(id, format, a1, a2, a3)
#endif

#ifndef OSAL_INFO_MID_4
#define OSAL_INFO_MID_4(id, format, a1, a2, a3, a4)
#endif

#ifndef OSAL_INFO_MID_5
#define OSAL_INFO_MID_5(id, format, a1, a2, a3, a4, a5)
#endif

#ifndef OSAL_INFO_MID_6
#define OSAL_INFO_MID_6(id, format, a1, a2, a3, a4, a5, a6)
#endif

#ifndef OSAL_INFO_MID_7
#define OSAL_INFO_MID_7(id, format, a1, a2, a3, a4, a5, a6, a7)
#endif

#ifndef OSAL_INFO_MID_8
#define OSAL_INFO_MID_8(id, format, a1, a2, a3, a4, a5, a6, a7, a8)
#endif

#ifndef OSAL_INFO_MID_9
#define OSAL_INFO_MID_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#endif

#ifndef OSAL_INFO_MID_10
#define OSAL_INFO_MID_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#endif

#ifndef OSAL_INFO_MID_11
#define OSAL_INFO_MID_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#endif

#ifndef OSAL_INFO_MID_12
#define OSAL_INFO_MID_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#endif

#ifndef OSAL_INFO_MID_13
#define OSAL_INFO_MID_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#endif

#ifndef OSAL_INFO_MID_14
#define OSAL_INFO_MID_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#endif

#ifndef OSAL_INFO_MID_15
#define OSAL_INFO_MID_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#endif

#ifndef OSAL_INFO_MID_16
#define OSAL_INFO_MID_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#endif

#ifndef OSAL_INFO_LO
#define OSAL_INFO_LO(id, format)
#endif

#ifndef OSAL_INFO_LO_1
#define OSAL_INFO_LO_1(id, format, a1)
#endif

#ifndef OSAL_INFO_LO_2
#define OSAL_INFO_LO_2(id, format, a1, a2)
#endif

#ifndef OSAL_INFO_LO_3
#define OSAL_INFO_LO_3(id, format, a1, a2, a3)
#endif

#ifndef OSAL_INFO_LO_4
#define OSAL_INFO_LO_4(id, format, a1, a2, a3, a4)
#endif

#ifndef OSAL_INFO_LO_5
#define OSAL_INFO_LO_5(id, format, a1, a2, a3, a4, a5)
#endif

#ifndef OSAL_INFO_LO_6
#define OSAL_INFO_LO_6(id, format, a1, a2, a3, a4, a5, a6)
#endif

#ifndef OSAL_INFO_LO_7
#define OSAL_INFO_LO_7(id, format, a1, a2, a3, a4, a5, a6, a7)
#endif

#ifndef OSAL_INFO_LO_8
#define OSAL_INFO_LO_8(id, format, a1, a2, a3, a4, a5, a6, a7, a8)
#endif

#ifndef OSAL_INFO_LO_9
#define OSAL_INFO_LO_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#endif

#ifndef OSAL_INFO_LO_10
#define OSAL_INFO_LO_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#endif

#ifndef OSAL_INFO_LO_11
#define OSAL_INFO_LO_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#endif

#ifndef OSAL_INFO_LO_12
#define OSAL_INFO_LO_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#endif

#ifndef OSAL_INFO_LO_13
#define OSAL_INFO_LO_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#endif

#ifndef OSAL_INFO_LO_14
#define OSAL_INFO_LO_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#endif

#ifndef OSAL_INFO_LO_15
#define OSAL_INFO_LO_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#endif

#ifndef OSAL_INFO_LO_16
#define OSAL_INFO_LO_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#endif

#ifndef OSAL_DEBUG_HI
#define OSAL_DEBUG_HI(id, format)
#endif

#ifndef OSAL_DEBUG_HI_1
#define OSAL_DEBUG_HI_1(id, format, a1)
#endif

#ifndef OSAL_DEBUG_HI_2
#define OSAL_DEBUG_HI_2(id, format, a1, a2)
#endif

#ifndef OSAL_DEBUG_HI_3
#define OSAL_DEBUG_HI_3(id, format, a1, a2, a3)
#endif

#ifndef OSAL_DEBUG_HI_4
#define OSAL_DEBUG_HI_4(id, format, a1, a2, a3, a4)
#endif

#ifndef OSAL_DEBUG_HI_5
#define OSAL_DEBUG_HI_5(id, format, a1, a2, a3, a4, a5)
#endif

#ifndef OSAL_DEBUG_HI_6
#define OSAL_DEBUG_HI_6(id, format, a1, a2, a3, a4, a5, a6)
#endif

#ifndef OSAL_DEBUG_HI_7
#define OSAL_DEBUG_HI_7(id, format, a1, a2, a3, a4, a5, a6, a7)
#endif

#ifndef OSAL_DEBUG_HI_8
#define OSAL_DEBUG_HI_8(id, format, a1, a2, a3, a4, a5, a6, a7, a8)
#endif

#ifndef OSAL_DEBUG_HI_9
#define OSAL_DEBUG_HI_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#endif

#ifndef OSAL_DEBUG_HI_10
#define OSAL_DEBUG_HI_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#endif

#ifndef OSAL_DEBUG_HI_11
#define OSAL_DEBUG_HI_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#endif

#ifndef OSAL_DEBUG_HI_12
#define OSAL_DEBUG_HI_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#endif

#ifndef OSAL_DEBUG_HI_13
#define OSAL_DEBUG_HI_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#endif

#ifndef OSAL_DEBUG_HI_14
#define OSAL_DEBUG_HI_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#endif

#ifndef OSAL_DEBUG_HI_15
#define OSAL_DEBUG_HI_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#endif

#ifndef OSAL_DEBUG_HI_16
#define OSAL_DEBUG_HI_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#endif

#ifndef OSAL_DEBUG_MID
#define OSAL_DEBUG_MID(id, format)
#endif

#ifndef OSAL_DEBUG_MID_1
#define OSAL_DEBUG_MID_1(id, format, a1)
#endif

#ifndef OSAL_DEBUG_MID_2
#define OSAL_DEBUG_MID_2(id, format, a1, a2)
#endif

#ifndef OSAL_DEBUG_MID_3
#define OSAL_DEBUG_MID_3(id, format, a1, a2, a3)
#endif

#ifndef OSAL_DEBUG_MID_4
#define OSAL_DEBUG_MID_4(id, format, a1, a2, a3, a4)
#endif

#ifndef OSAL_DEBUG_MID_5
#define OSAL_DEBUG_MID_5(id, format, a1, a2, a3, a4, a5)
#endif

#ifndef OSAL_DEBUG_MID_6
#define OSAL_DEBUG_MID_6(id, format, a1, a2, a3, a4, a5, a6)
#endif

#ifndef OSAL_DEBUG_MID_7
#define OSAL_DEBUG_MID_7(id, format, a1, a2, a3, a4, a5, a6, a7)
#endif

#ifndef OSAL_DEBUG_MID_8
#define OSAL_DEBUG_MID_8(id, format, a1, a2, a3, a4, a5, a6, a7, a8)
#endif

#ifndef OSAL_DEBUG_MID_9
#define OSAL_DEBUG_MID_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#endif

#ifndef OSAL_DEBUG_MID_10
#define OSAL_DEBUG_MID_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#endif

#ifndef OSAL_DEBUG_MID_11
#define OSAL_DEBUG_MID_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#endif

#ifndef OSAL_DEBUG_MID_12
#define OSAL_DEBUG_MID_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#endif

#ifndef OSAL_DEBUG_MID_13
#define OSAL_DEBUG_MID_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#endif

#ifndef OSAL_DEBUG_MID_14
#define OSAL_DEBUG_MID_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#endif

#ifndef OSAL_DEBUG_MID_15
#define OSAL_DEBUG_MID_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#endif

#ifndef OSAL_DEBUG_MID_16
#define OSAL_DEBUG_MID_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#endif

#ifndef OSAL_DEBUG_LO
#define OSAL_DEBUG_LO(id, format)
#endif

#ifndef OSAL_DEBUG_LO_1
#define OSAL_DEBUG_LO_1(id, format, a1)
#endif

#ifndef OSAL_DEBUG_LO_2
#define OSAL_DEBUG_LO_2(id, format, a1, a2)
#endif

#ifndef OSAL_DEBUG_LO_3
#define OSAL_DEBUG_LO_3(id, format, a1, a2, a3)
#endif

#ifndef OSAL_DEBUG_LO_4
#define OSAL_DEBUG_LO_4(id, format, a1, a2, a3, a4)
#endif

#ifndef OSAL_DEBUG_LO_5
#define OSAL_DEBUG_LO_5(id, format, a1, a2, a3, a4, a5)
#endif

#ifndef OSAL_DEBUG_LO_6
#define OSAL_DEBUG_LO_6(id, format, a1, a2, a3, a4, a5, a6)
#endif

#ifndef OSAL_DEBUG_LO_7
#define OSAL_DEBUG_LO_7(id, format, a1, a2, a3, a4, a5, a6, a7)
#endif

#ifndef OSAL_DEBUG_LO_8
#define OSAL_DEBUG_LO_8(id, format, a1, a2, a3, a4, a5, a6, a7, a8)
#endif

#ifndef OSAL_DEBUG_LO_9
#define OSAL_DEBUG_LO_9(id,  format, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#endif

#ifndef OSAL_DEBUG_LO_10
#define OSAL_DEBUG_LO_10(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA)
#endif

#ifndef OSAL_DEBUG_LO_11
#define OSAL_DEBUG_LO_11(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB)
#endif

#ifndef OSAL_DEBUG_LO_12
#define OSAL_DEBUG_LO_12(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC)
#endif

#ifndef OSAL_DEBUG_LO_13
#define OSAL_DEBUG_LO_13(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD)
#endif

#ifndef OSAL_DEBUG_LO_14
#define OSAL_DEBUG_LO_14(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE)
#endif

#ifndef OSAL_DEBUG_LO_15
#define OSAL_DEBUG_LO_15(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF)
#endif

#ifndef OSAL_DEBUG_LO_16
#define OSAL_DEBUG_LO_16(id, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, aA, aB, aC, aD, aE, aF, aG)
#endif

#define OSAL_LOG_DATA_EMERG(      id, data, size, description)
#define OSAL_LOG_DATA_EMERG_1(    id, data, size, description, a1)
#define OSAL_LOG_DATA_EMERG_2(    id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_EMERG_3(    id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_ALERT(      id, data, size, description)
#define OSAL_LOG_DATA_ALERT_1(    id, data, size, description, a1)
#define OSAL_LOG_DATA_ALERT_2(    id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_ALERT_3(    id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_CRIT(       id, data, size, description)
#define OSAL_LOG_DATA_CRIT_1(     id, data, size, description, a1)
#define OSAL_LOG_DATA_CRIT_2(     id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_CRIT_3(     id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_ERROR(      id, data, size, description)
#define OSAL_LOG_DATA_ERROR_1(    id, data, size, description, a1)
#define OSAL_LOG_DATA_ERROR_2(    id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_ERROR_3(    id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_WARN(       id, data, size, description)
#define OSAL_LOG_DATA_WARN_1(     id, data, size, description, a1)
#define OSAL_LOG_DATA_WARN_2(     id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_WARN_3(     id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_NOTICE(     id, data, size, description)
#define OSAL_LOG_DATA_NOTICE_1(   id, data, size, description, a1)
#define OSAL_LOG_DATA_NOTICE_2(   id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_NOTICE_3(   id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_INFO_HI(    id, data, size, description)
#define OSAL_LOG_DATA_INFO_HI_1(  id, data, size, description, a1)
#define OSAL_LOG_DATA_INFO_HI_2(  id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_INFO_HI_3(  id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_INFO_MID(   id, data, size, description)
#define OSAL_LOG_DATA_INFO_MID_1( id, data, size, description, a1)
#define OSAL_LOG_DATA_INFO_MID_2( id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_INFO_MID_3( id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_INFO_LO(    id, data, size, description)
#define OSAL_LOG_DATA_INFO_LO_1(  id, data, size, description, a1)
#define OSAL_LOG_DATA_INFO_LO_2(  id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_INFO_LO_3(  id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_DEBUG_HI(   id, data, size, description)
#define OSAL_LOG_DATA_DEBUG_HI_1( id, data, size, description, a1)
#define OSAL_LOG_DATA_DEBUG_HI_2( id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_DEBUG_HI_3( id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_DEBUG_MID(  id, data, size, description)
#define OSAL_LOG_DATA_DEBUG_MID_1(id, data, size, description, a1)
#define OSAL_LOG_DATA_DEBUG_MID_2(id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_DEBUG_MID_3(id, data, size, description, a1, a2, a3)

#define OSAL_LOG_DATA_DEBUG_LO(   id, data, size, description)
#define OSAL_LOG_DATA_DEBUG_LO_1( id, data, size, description, a1)
#define OSAL_LOG_DATA_DEBUG_LO_2( id, data, size, description, a1, a2)
#define OSAL_LOG_DATA_DEBUG_LO_3( id, data, size, description, a1, a2, a3)


#define OSAL_COMPARE_DATA_EMERG(      id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_EMERG_1(    id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_EMERG_2(    id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_EMERG_3(    id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_ALERT(      id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_ALERT_1(    id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_ALERT_2(    id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_ALERT_3(    id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_CRIT(       id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_CRIT_1(     id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_CRIT_2(     id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_CRIT_3(     id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_ERROR(      id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_ERROR_1(    id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_ERROR_2(    id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_ERROR_3(    id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_WARN(       id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_WARN_1(     id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_WARN_2(     id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_WARN_3(     id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_NOTICE(     id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_NOTICE_1(   id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_NOTICE_2(   id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_NOTICE_3(   id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_INFO_HI(    id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_INFO_HI_1(  id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_INFO_HI_2(  id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_INFO_HI_3(  id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_INFO_MID(   id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_INFO_MID_1( id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_INFO_MID_2( id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_INFO_MID_3( id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_INFO_LO(    id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_INFO_LO_1(  id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_INFO_LO_2(  id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_INFO_LO_3(  id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_DEBUG_HI(   id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_DEBUG_HI_1( id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_DEBUG_HI_2( id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_DEBUG_HI_3( id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_DEBUG_MID(  id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_DEBUG_MID_1(id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_DEBUG_MID_2(id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_DEBUG_MID_3(id, data1, size1, data2, size2, description, a1, a2, a3)

#define OSAL_COMPARE_DATA_DEBUG_LO(   id, data1, size1, data2, size2, description)
#define OSAL_COMPARE_DATA_DEBUG_LO_1( id, data1, size1, data2, size2, description, a1)
#define OSAL_COMPARE_DATA_DEBUG_LO_2( id, data1, size1, data2, size2, description, a1, a2)
#define OSAL_COMPARE_DATA_DEBUG_LO_3( id, data1, size1, data2, size2, description, a1, a2, a3)

#endif

#endif
