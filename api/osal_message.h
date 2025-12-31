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

#ifndef OSAL_MESSAGE_H_
#define OSAL_MESSAGE_H_

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

#ifndef BUFF_H_
#include "buff.h"
#endif

/** @defgroup Messaging Operating System Abstraction Layer - Messages management
 *  @brief Creating, destroying queues, sending, receiving messages.
 *  @{
 */

#ifndef OSAL_MESSAGE_SIZE_PRE_ALLOCATED_ON_QUEUE_INIT
/**
 * This is size of message which is stored directly in pre-allocated on init buffer. Messages with bigger size
 * can be also transferred but for them buffer is allocated using OSAL_Malloc in the moment of sending the message.
 */
#define OSAL_MESSAGE_SIZE_PRE_ALLOCATED_ON_QUEUE_INIT    32
#endif

typedef struct
{
   OSAL_Context_Id_XT   source;
   const void          *data;
   size_t               data_size;
   uint32_t             message_id;
}OSAL_Message_XT;

#ifndef OSAL_MESSAGE_QUEUE_XT_EXTERNAL
typedef struct
{
   /**
    * ring buffer which stores messages.
    */
   Buff_Ring_XT      ring;
   /**
    * table which messages managed by ring buffer.
    */
   OSAL_Message_XT  *msg_tab;
   /**
    * memory where small enough messages are stored. This small enough is OSAL_MESSAGE_SIZE_PRE_ALLOCATED_ON_QUEUE_INIT.
    */
   uint8_t          *msg_static_memory;
   /**
    * semaphore used to freeze owner thread waiting for the message.
    */
   OSAL_Semaphore_XT semaphore;
}OSAL_Message_Queue_XT;
#endif

/** -------------------------------------------------------------------------------------------------------------------------------
 *                                           Message queue creation
 *  ---------------------------------------------------------------------------------------------------------------------------- */

/**
 * @brief Initializes context queue.
 *
 * @param queue pointer to the queue to be initialized.
 * @param queue_num_elems maximum number of messages that can be stored in the queue.
 **/
void OSAL_Message_Queue_Init(OSAL_Message_Queue_XT *queue, size_t queue_num_elems);

/**
 * @brief Initializes context queue.
 *
 * @param queue pointer to the queue to be initialized.
 * @param queue_num_elems maximum number of messages that can be stored in the queue.
 * @param msg_tab pointer to the table of OSAL_Message_XT. This table must have at least queue_num_elems cells.
 * @param msg_static_memory pre-allocated by the caller memory for messages which size must be at least queue_num_elems * OSAL_MESSAGE_SIZE_PRE_ALLOCATED_ON_QUEUE_INIT
 **/
void OSAL_Message_Queue_Init_Static(OSAL_Message_Queue_XT *queue, size_t queue_num_elems, OSAL_Message_XT *msg_tab, uint8_t *msg_static_memory);

/**
 * @brief Deinitializes context queue.
 *
 * @param queue pointer to the queue to be initialized.
 **/
void OSAL_Message_Queue_Deinit(OSAL_Message_Queue_XT *queue);

/** -------------------------------------------------------------------------------------------------------------------------------
 *                                           Message sending
 *  ---------------------------------------------------------------------------------------------------------------------------- */

/**
 * @brief Sends a message to requested thread. This is basic send function which sends contineous piece of memory.
 * This function must be possible to be called from thread and from IRQ.
 *
 * @param destination ID of the thread to which we are sending the message.
 * @param message_id Identifier of the message, something used by the receiver to differentiate different messages.
 * @param data pointer to the data to be sent.
 * @param data_size number of bytes from data buffer to be sent.
 * @result OSAL_TRUE if message has been successfully stored in the destination context queue, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Send(OSAL_Context_Id_XT *destination, uint32_t message_id, const void *data, size_t data_size);

/**
 * @brief Sends a message to requested thread. This function is able to send vector od input data.
 * This function must be possible to be called from thread and from IRQ.
 *
 * @param destination ID of the thread to which we are sending the message.
 * @param message_id Identifier of the message, something used by the receiver to differentiate different messages.
 * @param data pointer to data vector to be sent.
 * @param data_num_elems number of vector cells.
 * @param data_size number of bytes from data buffer to be sent.
 * @result OSAL_TRUE if message has been successfully stored in the destination context queue, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Send_From_Vector(
   OSAL_Context_Id_XT           *destination,
   uint32_t                      message_id,
   const Buff_Readable_Vector_XT*data,
   Buff_Num_Elems_DT             data_num_elems,
   size_t                        data_size);

/**
 * @brief Sends a message to requested thread. This function is able to send tree od input data.
 * This function must be possible to be called from thread and from IRQ.
 *
 * @param destination ID of the thread to which we are sending the message.
 * @param message_id Identifier of the message, something used by the receiver to differentiate different messages.
 * @param data pointer to data tree to be sent.
 * @param data_num_elems number of tree cells on the main branch.
 * @param data_size number of bytes from data buffer to be sent.
 * @result OSAL_TRUE if message has been successfully stored in the destination context queue, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Send_From_Tree(
   OSAL_Context_Id_XT           *destination,
   uint32_t                      message_id,
   const Buff_Readable_Tree_XT  *data,
   Buff_Num_Elems_DT             data_num_elems,
   size_t                        data_size);

/**
 * @brief Sends a message to requested thread. This function is able to send data from a ring buffer.
 * This function must be possible to be called from thread and from IRQ.
 *
 * @param destination ID of the thread to which we are sending the message.
 * @param message_id Identifier of the message, something used by the receiver to differentiate different messages.
 * @param ring pointer to ring buffer from which data is to be sent.
 * @param data_size number of bytes from data buffer to be sent.
 * @result OSAL_TRUE if message has been successfully stored in the destination context queue, OSAL_FALSE otherwise.
 */
OSAL_Bool_DT OSAL_Send_From_Ring(
   OSAL_Context_Id_XT           *destination,
   uint32_t                      message_id,
   Buff_Ring_XT                 *ring,
   size_t                        data_size);

/** -------------------------------------------------------------------------------------------------------------------------------
 *                                           Message receiving
 *  ---------------------------------------------------------------------------------------------------------------------------- */

/**
 * @brief Tries to read oldest message from the context queue.
 * If tf there is no message, returns OSAL_MAKE_INVALID_PTR(const OSAL_Message_XT).
 * This function must be possible to be called from thread and from IRQ.
 *
 * @return pointer to received message if there is any message in the queue, OSAL_MAKE_INVALID_PTR(const OSAL_Message_XT) otherwise.
 */
const OSAL_Message_XT *OSAL_Try_Receive(void);

/**
 * @brief Tries to read oldest message from the context queue.
 * If there is no message in the queue, function blocks thread and wait until some message gets stored in teh context queue.
 * This function should be called ONLY from thread. If called from IRQ then its behavior will be same as @see OSAL_Try_Receive.
 *
 * @return pointer to received message.
 */
const OSAL_Message_XT *OSAL_Wait_And_Receive(void);

/**
 * @brief Tries to read oldest message from the context queue.
 * If there is no message in the queue, function blocks thread and wait until some message gets stored in teh context queue or timeout passes.
 * This function should be called ONLY from thread. If called from IRQ then its behavior will be same as @see OSAL_Try_Receive.
 *
 * @param timeout_ms time after which function must return, even there is no message in the queue.
 * @return pointer to received message.
 */
const OSAL_Message_XT *OSAL_Wait_And_Receive_Timeout(OSAL_Time_DT timeout_ms);

/** @} */ // end of Messaging

#endif
