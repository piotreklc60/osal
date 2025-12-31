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

#ifndef OSAL_MESSAGE_C_
#define OSAL_MESSAGE_C_
#endif

#ifndef OSAL_H_
#include "osal.h"
#endif

/**
 * will be soon.
 */

void OSAL_Message_Queue_Init(OSAL_Message_Queue_XT *queue, size_t queue_num_elems)
{

} /*  */

void OSAL_Message_Queue_Init_Static(OSAL_Message_Queue_XT *queue, size_t queue_num_elems, OSAL_Message_XT *msg_tab, uint8_t *msg_static_memory)
{

} /*  */

void OSAL_Message_Queue_Deinit(OSAL_Message_Queue_XT *queue)
{

} /*  */

OSAL_Bool_DT OSAL_Send(OSAL_Context_Id_XT *destination, uint32_t message_id, const void *data, size_t data_size)
{

} /*  */

OSAL_Bool_DT OSAL_Send_From_Vector(
   OSAL_Context_Id_XT           *destination,
   uint32_t                      message_id,
   const Buff_Readable_Vector_XT*data,
   Buff_Num_Elems_DT             data_num_elems,
   size_t                        data_size)
{

} /*  */

OSAL_Bool_DT OSAL_Send_From_Tree(
   OSAL_Context_Id_XT           *destination,
   uint32_t                      message_id,
   const Buff_Readable_Tree_XT  *data,
   Buff_Num_Elems_DT             data_num_elems,
   size_t                        data_size)
{

} /*  */

OSAL_Bool_DT OSAL_Send_From_Ring(
   OSAL_Context_Id_XT           *destination,
   uint32_t                      message_id,
   Buff_Ring_XT                 *ring,
   size_t                        data_size)
{

} /*  */

const OSAL_Message_XT *OSAL_Try_Receive(void)
{

} /*  */

const OSAL_Message_XT *OSAL_Wait_And_Receive(void)
{

} /*  */

const OSAL_Message_XT *OSAL_Wait_And_Receive_Timeout(OSAL_Time_DT timeout_ms)
{

} /*  */
