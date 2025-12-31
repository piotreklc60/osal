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

#ifndef OSAL_PUBLIC_MACRO_H_
#define OSAL_PUBLIC_MACRO_H_

#ifndef OSAL_OS_VARIANT_PRE_SETUP_H_
#include "osal_os_variant_pre_setup.h"
#endif

#ifndef OSAL_HW_VARIANT_PRE_SETUP_H_
#include "osal_hw_variant_pre_setup.h"
#endif

#ifndef OSAL_FEATURE_PRESENT
#define OSAL_FEATURE_PRESENT                                      (1)
#endif

#ifndef OSAL_FEATURE_NOT_PRESENT
#define OSAL_FEATURE_NOT_PRESENT                                  (0)
#endif

#ifndef OSAL_BASIC_PARAMS_CHECK
/**
 * @brief Checking basic parameters which usually are met.
 * For example xxx_Init function gets pointer of the structure to be initialized.
 * Usually, such pointer is always valid and it doesn't have to be checked. However, it is good to implement proper validation mechanism.
 * If we don't need it it is enough to redefine this macto to true.
 */
#define OSAL_BASIC_PARAMS_CHECK(expresion)                        (expresion)
//#define OSAL_BASIC_PARAMS_CHECK(expresion)                        (1)
#endif

#ifndef OSAL_BOOL_IS_TRUE
#define OSAL_BOOL_IS_TRUE(bl)                                     (bl)
#endif

#ifndef OSAL_BOOL_IS_FALSE
#define OSAL_BOOL_IS_FALSE(bl)                                    (!(bl))
#endif

#ifndef OSAL_BOOL_TOGGLE
#define OSAL_BOOL_TOGGLE(bl)                                      (bl) = (!bl)
#endif

#ifndef OSAL_ATOMIC_BOOL_IS_TRUE
#define OSAL_ATOMIC_BOOL_IS_TRUE(bl)                              (bl)
#endif

#ifndef OSAL_ATOMIC_BOOL_IS_FALSE
#define OSAL_ATOMIC_BOOL_IS_FALSE(bl)                             (!(bl))
#endif

#ifndef OSAL_ATOMIC_BOOL_GET
#define OSAL_ATOMIC_BOOL_GET(_data)                               (OSAL_Bool_DT)(_data)
#endif

#ifndef OSAL_ATOMIC_BOOL_SET
#define OSAL_ATOMIC_BOOL_SET(_data, _value)                       (_data) = (_value)
#endif

#ifndef OSAL_ATOMIC_UINT8_GET
#define OSAL_ATOMIC_UINT8_GET(_data)                              (uint8_t)(_data)
#endif

#ifndef OSAL_ATOMIC_UINT8_SET
#define OSAL_ATOMIC_UINT8_SET(_data, _value)                      (_data) = (_value)
#endif

#ifndef OSAL_ATOMIC_UINT16_GET
#define OSAL_ATOMIC_UINT16_GET(_data)                             (uint16_t)(_data)
#endif

#ifndef OSAL_ATOMIC_UINT16_SET
#define OSAL_ATOMIC_UINT16_SET(_data, _value)                     (_data) = (_value)
#endif

#ifndef OSAL_ATOMIC_UINT32_GET
#define OSAL_ATOMIC_UINT32_GET(_data)                             (uint32_t)(_data)
#endif

#ifndef OSAL_ATOMIC_UINT32_SET
#define OSAL_ATOMIC_UINT32_SET(_data, _value)                     (_data) = (_value)
#endif

#ifndef OSAL_ATOMIC_UINT64_GET
#define OSAL_ATOMIC_UINT64_GET(_data)                             (uint64_t)(_data)
#endif

#ifndef OSAL_ATOMIC_UINT64_SET
#define OSAL_ATOMIC_UINT64_SET(_data, _value)                     (_data) = (_value)
#endif

#ifndef OSAL_CHECK_PTR
#define OSAL_CHECK_PTR(type, ptr)                                 (((type*)0) != (ptr))
#endif

#ifndef OSAL_CHECK_HANDLER
#define OSAL_CHECK_HANDLER(type, handler)                         (((type)0) != (handler))
#endif

/** true when pointers are equal */
#ifndef OSAL_COMPARE_PTRS
#define OSAL_COMPARE_PTRS(type1, ptr1, type2, ptr2)               (((type1*)(ptr1)) == ((type2*)(ptr2)))
#endif

/** true when handlers are equal */
#ifndef OSAL_COMPARE_HANDLERS
#define OSAL_COMPARE_HANDLERS(type1, handler1, type2, handler2)   (((type1)(handler1)) == ((type2)(handler2)))
#endif

#ifndef OSAL_GET_PTR
#define OSAL_GET_PTR(type, ptr)                                   (/*(type*)*/(ptr))
#endif

#ifndef OSAL_GET_HANDLER
#define OSAL_GET_HANDLER(type, handler)                           (/*(type)*/(handler))
#endif

#ifndef OSAL_SET_PTR
#define OSAL_SET_PTR(type, ptr, new_value)                        (ptr) = /*(type*)*/(new_value)
#endif

#ifndef OSAL_SET_HANDLER
#define OSAL_SET_HANDLER(type, handler, new_value)                (handler) = /*(type)*/(new_value)
#endif

#ifndef OSAL_CALL_HANDLER
#define OSAL_CALL_HANDLER(type, handler)                          ((type)(handler))
#endif

#ifndef OSAL_CHECK_AND_CALL_HANDLER
#define OSAL_CHECK_AND_CALL_HANDLER(type, handler)                if(OSAL_CHECK_HANDLER(type, (handler)))    ((type)(handler))
#endif

#ifndef OSAL_MAKE_INVALID_PTR
#define OSAL_MAKE_INVALID_PTR(type)                               ((type*)(NULL))
#endif

#ifndef OSAL_MAKE_INVALID_HANDLER
#define OSAL_MAKE_INVALID_HANDLER(type)                           ((type)(NULL))
#endif

#ifndef OSAL_INVALIDATE_PTR
#define OSAL_INVALIDATE_PTR(type, ptr)                            (ptr) = OSAL_MAKE_INVALID_PTR(type)
#endif

#ifndef OSAL_INVALIDATE_HANDLER
#define OSAL_INVALIDATE_HANDLER(type, handler)                    (handler) = OSAL_MAKE_INVALID_HANDLER(type)
#endif

#ifndef OSAL_UNUSED_PARAM
#define OSAL_UNUSED_PARAM(param)                                  (void)(param)
#endif

#ifndef OSAL_USE_INVALIDATION_ON_INIT
#define OSAL_USE_INVALIDATION_ON_INIT                             OSAL_FEATURE_PRESENT
#endif

#if (OSAL_FEATURE_NOT_PRESENT == OSAL_USE_INVALIDATION_ON_INIT)

#ifndef OSAL_INVALIDATE_PTR_ON_INIT
#define OSAL_INVALIDATE_PTR_ON_INIT(type, ptr)
#endif
#ifndef OSAL_INVALIDATE_HANDLER_ON_INIT
#define OSAL_INVALIDATE_HANDLER_ON_INIT(type, handler)
#endif

#else

#ifndef OSAL_INVALIDATE_PTR_ON_INIT
#define OSAL_INVALIDATE_PTR_ON_INIT(type, ptr)                    (ptr) = OSAL_MAKE_INVALID_PTR(type)
#endif
#ifndef OSAL_INVALIDATE_HANDLER_ON_INIT
#define OSAL_INVALIDATE_HANDLER_ON_INIT(type, handler)            (handler) = OSAL_MAKE_INVALID_HANDLER(type)
#endif

#endif


#ifndef OSAL_MUL_BY_POWER_OF_2
#define OSAL_MUL_BY_POWER_OF_2(_a, _2_power_x)                    ((_a) << (_2_power_x))
#endif


#ifndef OSAL_DIV_BY_POWER_OF_2
#define OSAL_DIV_BY_POWER_OF_2(_a, _2_power_x)                    ((_a) >> (_2_power_x))
#endif

#ifndef Num_Elems
#define Num_Elems(tab)                          (sizeof(tab) / sizeof(tab[0]))
#endif


#endif
