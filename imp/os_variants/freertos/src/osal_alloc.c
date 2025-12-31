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

#ifndef OSAL_ALLOC_C_
#define OSAL_ALLOC_C_
#endif

#ifndef OSAL_H_
#include "osal.h"
#endif

void *OSAL_Malloc(size_t size)
{
   void *result;

   OSAL_ENTER_FUNC(OSAL_DBG_ALLOC);

   result = pvPortMalloc(size);

   OSAL_EXIT_FUNC(OSAL_DBG_ALLOC);

   return result;
} /* OSAL_Malloc */

void OSAL_Free(void *ptr)
{
   OSAL_ENTER_FUNC(OSAL_DBG_ALLOC);

   vPortFree(ptr);

   OSAL_EXIT_FUNC(OSAL_DBG_ALLOC);
} /* OSAL_Free */

