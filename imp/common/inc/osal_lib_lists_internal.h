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

#ifndef OSAL_LIB_LISTS_INTERNAL_H_
#define OSAL_LIB_LISTS_INTERNAL_H_

#ifndef OSAL_PUBLIC_MACRO_H_
#include "osal_public_macro.h"
#endif

/** @defgroup Lists Operating System Abstraction Layer - universal library for manipulating lists
 *  @brief searching, inserting, removing objects
 *  @{
 */

typedef struct
{
   uint32_t       new_leaf_id;
   uint32_t       id_offset;
   uint_fast8_t   id_mask;
}OSAL_List_add_by_number_params_DT;

typedef struct
{
   const char    *new_leaf_string;
   uint32_t       id_offset;
   uint32_t       offset;
}OSAL_List_add_by_string_params_DT;

OSAL_Bool_DT OSAL_List_add_by_string_growing(OSAL_List_XT *leaf, OSAL_List_add_by_string_params_DT *params);
OSAL_Bool_DT OSAL_List_add_by_string_falling(OSAL_List_XT *leaf, OSAL_List_add_by_string_params_DT *params);

/** @} */ // end of Lists

#endif

