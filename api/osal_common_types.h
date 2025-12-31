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

#ifndef OSAL_COMMON_TYPES_H_
#define OSAL_COMMON_TYPES_H_

#ifndef STD_LIBS_H_
#include "std_libs.h"
#endif

/** @defgroup OSAL_COMMON_TYPES
 * @{
 */

#ifndef OSAL_BOOL_TYPES_ET_EXTERNAL
/**
 * \typedef OSAL_Bool_Types_ET
 */
typedef enum OSAL_Bool_Types_Enum_Tag
{
   OSAL_FALSE  = false,
   OSAL_TRUE   = true
}OSAL_Bool_Types_ET;
#endif



#ifndef OSAL_BOOL_DT_EXTERNAL
/**
 * \typedef OSAL_Bool_DT
 */
#if((OSAL_OPTIMIZATION_BY_SPEED_PRIORITY > OSAL_OPTIMIZATION_BY_RAM_CONSUMPTION_PRIORITY) && (OSAL_OPTIMIZATION_BY_SPEED_PRIORITY > OSAL_OPTIMIZATION_BY_PROGRAM_CONSUMPTION_PRIORITY))
typedef uint_fast8_t OSAL_Bool_DT;
#else
typedef uint8_t OSAL_Bool_DT;
#endif
#endif



#ifndef OSAL_ATOMIC_BOOL_DT_EXTERNAL
/**
 * \typedef OSAL_Atomic_Bool_DT
 */
#if((OSAL_OPTIMIZATION_BY_SPEED_PRIORITY > OSAL_OPTIMIZATION_BY_RAM_CONSUMPTION_PRIORITY) && (OSAL_OPTIMIZATION_BY_SPEED_PRIORITY > OSAL_OPTIMIZATION_BY_PROGRAM_CONSUMPTION_PRIORITY))
typedef uint_fast8_t OSAL_Atomic_Bool_DT;
#else
typedef uint8_t OSAL_Atomic_Bool_DT;
#endif
#endif



#ifndef OSAL_ATOMIC_UINT8_DT_EXTERNAL
/**
 * \typedef OSAL_Atomic_Uint8_DT
 */
typedef uint8_t OSAL_Atomic_Uint8_DT;
#endif



#ifndef OSAL_ATOMIC_UINT16_DT_EXTERNAL
/**
 * \typedef OSAL_Atomic_Uint16_DT
 */
typedef uint16_t OSAL_Atomic_Uint16_DT;
#endif



#ifndef OSAL_ATOMIC_UINT32_DT_EXTERNAL
/**
 * \typedef OSAL_Atomic_Uint32_DT
 */
typedef uint32_t OSAL_Atomic_Uint32_DT;
#endif



#ifndef OSAL_ATOMIC_UINT64_DT_EXTERNAL
/**
 * \typedef OSAL_Atomic_Uint64_DT
 */
typedef uint64_t OSAL_Atomic_Uint64_DT;
#endif



#ifndef OSAL_HVOID_HT_EXTERNAL
/**
 * \typedef OSAL_Hvoid_HT
 */
typedef void (*OSAL_Hvoid_HT) (void);
#endif



#ifndef OSAL_HVOID_PARAM_HT_EXTERNAL
/**
 * \typedef OSAL_Hvoid_Param_HT
 */
typedef void (*OSAL_Hvoid_Param_HT) (void *param);
#endif



#ifndef OSAL_HVOID_TWO_PARAMS_HT_EXTERNAL
/**
 * \typedef OSAL_Hvoid_Two_Params_HT
 */
typedef void (*OSAL_Hvoid_Two_Params_HT) (void *param1, void *param2);
#endif



#ifndef OSAL_VENDOR_DATA_XT_EXTERNAL
/**
 * \struct OSAL_Vendor_Data_XT
 */
typedef union OSAL_Vendor_Data_eXtended_Tag
{
   OSAL_Hvoid_HT  hvoid;
   void          *pvoid;
   uint32_t       u32;
   uint16_t       u16;
   uint16_t       u16tab[2];
   uint8_t        u8;
   uint8_t        u8tab[4];
   OSAL_Bool_DT   boolean;
   OSAL_Atomic_Uint32_DT au32;
   OSAL_Atomic_Uint16_DT au16;
   OSAL_Atomic_Uint8_DT  au8;
   OSAL_Atomic_Bool_DT   aboolean;
}OSAL_Vendor_Data_XT;
#endif

/** @} */ /* OSAL_COMMON_TYPES */

#endif
