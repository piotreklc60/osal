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

#ifndef OSAL_CONTEXT_H_
#define OSAL_CONTEXT_H_

#ifndef STD_LIBS_H_
#include "std_libs.h"
#endif

#ifndef OSAL_PUBLIC_MACRO_H_
#include "osal_public_macro.h"
#endif

#ifndef OSAL_COMMON_TYPES_H_
#include "osal_common_types.h"
#endif

#ifndef OSAL_LIB_TREES_H_
#include "osal_lib_trees.h"
#endif

/**
 * maximum number of interrupts in the system.
 */
#ifndef OSAL_NUM_INTERRUPTS
#define OSAL_NUM_INTERRUPTS                        1
#endif

/**
 * maximum number of threads/tasks in the system.
 */
#ifndef OSAL_NUM_THREADS
#define OSAL_NUM_THREADS                           1
#endif

#ifndef OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED
#define OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED    OSAL_FEATURE_PRESENT
#endif

#ifndef OSAL_ALLOW_QUEUES_IN_INTERRUPTS
#define OSAL_ALLOW_QUEUES_IN_INTERRUPTS            OSAL_FEATURE_NOT_PRESENT
#endif

/**
 * maximum number of threads/interrupts in the system.
 */
#ifndef OSAL_NUM_PRE_ALLOCATED_CONTEXTS
#define OSAL_NUM_PRE_ALLOCATED_CONTEXTS            (OSAL_NUM_INTERRUPTS + OSAL_NUM_THREADS)
#endif

/** -------------------------------------------------------------------------------------------------------------------------------
 *                                           Context type
 *  ---------------------------------------------------------------------------------------------------------------------------- */

/** @defgroup ContextType Operating System Abstraction Layer - Context type definition
 *  @brief Obtaining current context type, specific context name.
 *  @{
 */

#ifndef OSAL_CONTEXT_TYPE_DT_EXTERNAL
/**
 * @brief defines types of contexts used in the system.
 */
typedef enum OSAL_Context_Type_Data_Tag
{
   /**
    * @brief Thread context type defines tasks/threads run by the operating system.
    */
   OSAL_CONTEXT_TYPE_THREAD            = 0,
   /**
    * @brief Interrupt context type describes microprocessor interrupts / events.
    */
   OSAL_CONTEXT_TYPE_INTERRUPT         = 1,
   OSAL_MAX_NUM_CONTEXT_TYPES          = 2
}OSAL_Context_Type_DT;
#endif

/**
 * @brief Gets type of curently active system context. It can be thread type, interrupt type or other (project specific).
 *
 * @return return type of curently active system context
 */
OSAL_Context_Type_DT OSAL_Get_Current_Context_Type(void);

/**
 * @brief Gets name of requested context type.
 *
 * @return pointer to requested context type name. It is always valid pointer - never will be NULL (can be for example "unknown").
 * @param context_type context type for which name is requested
 */
const char *OSAL_Get_Context_Type_Name(OSAL_Context_Type_DT context_type);

/** @} */ // end of ContextType


/** -------------------------------------------------------------------------------------------------------------------------------
 *                                           Context ID
 *  ---------------------------------------------------------------------------------------------------------------------------- */

/** @defgroup ContextID Operating System Abstraction Layer - Context identification
 *  @brief Obtaining current context ID, specific context name.
 *  @{
 */

/**
 * @brief defines number of the first task/thread context. If user wants to enumerate threads by himself,
 * must start from this value.
 */
#define OSAL_CONTEXT_FIRST_THREAD_ID            OSAL_NUM_INTERRUPTS

#ifndef OSAL_CONTEXT_UNIQUE_ID_DT_EXTERNAL

/**
 * @brief For interrupt mode it is interrupt ID, in thread mode it is thread_id + max number of interrupts.
 */
   #if(OSAL_OPTIMIZATION_BY_SPEED_PRIORITY > OSAL_OPTIMIZATION_BY_RAM_CONSUMPTION_PRIORITY)

      #if (OSAL_NUM_PRE_ALLOCATED_CONTEXTS < 256)
         typedef uint_fast8_t OSAL_Context_Unique_Id_DT;
      #elif (OSAL_NUM_PRE_ALLOCATED_CONTEXTS < 65536)
         typedef uint_fast16_t OSAL_Context_Unique_Id_DT;
      #else
         typedef uint_fast32_t OSAL_Context_Unique_Id_DT;
      #endif

   #else

      #if (OSAL_NUM_PRE_ALLOCATED_CONTEXTS < 256)
         typedef uint8_t OSAL_Context_Unique_Id_DT;
      #elif (OSAL_NUM_PRE_ALLOCATED_CONTEXTS < 65536)
         typedef uint16_t OSAL_Context_Unique_Id_DT;
      #else
         typedef uint32_t OSAL_Context_Unique_Id_DT;
      #endif

   #endif

#endif

#ifndef OSAL_CONTEXT_ID_XT_EXTERNAL
/**
 * @brief This is a structure used to identify specific context (like specific interrupt, specific thread).
 * This structure contains 2 fields and there is needed to set properly at least one of them, for example context path(name)
 * or id. Parameter not used MUST BE SET to NULL.
 * This structure is used for example for easily point for example destination thread for sending message to its queue.
 * In that case we don't have to know its ID, there is enough to set properly path(name). Of course id parameter is much faster for the system.
 * For this reason called function will fill missing parameter so if structure is "statis" then next call with same structure containing already filled params
 * will cause much faster navigating to the proper context destination.
 */
typedef struct
{
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
   const char *path;
#endif
   OSAL_Context_Unique_Id_DT id;
}OSAL_Context_Id_XT;

#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
#define OSAL_CONTEXT_ID_BY_NUMBER(_id)    &(OSAL_Context_Id_XT){.path=NULL, .id=_id}
#define OSAL_CONTEXT_ID_BY_PATH(_path)    &(OSAL_Context_Id_XT){.path=_path, .id=-1}
#else
#define OSAL_CONTEXT_ID_BY_NUMBER(_id)    &(OSAL_Context_Id_XT){.id=_id}
#endif
#endif

#ifndef OSAL_CONTEXT_TRACKING_PARAMS_XT_EXTERNAL
typedef struct OSAL_Context_Tracking_Params_eXtendedTag
{
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
   OSAL_Tree_XT         path_tree;
#else
   const char          *name;
#endif
   OSAL_Context_Id_XT   context_id;
   struct
   {
      uint8_t           dynamically_allocated      : 1;
      uint8_t           path_dynamically_allocated : 1;
   }flags;
}OSAL_Context_Tracking_Params_XT;
#endif

/**
 * @brief Gets unique ID of curently working context. It is an integer which identifies the context.
 * For interrupt mode it is interrupt ID, in thread mode it is thread_id + max number of interrupts.
 *
 * @return ID of currently working contextnumber.
 */
OSAL_Context_Unique_Id_DT OSAL_Get_Current_Context_Unique_Id(void);

/**
 * @brief Gets ID STRUCTURE of curently working context. This structure contains context Unique ID and pointer to its path (string) describing it.
 *
 * @return ID of currently working contextnumber.
 */
OSAL_Context_Id_XT OSAL_Get_Current_Context_Id(void);

/**
 * @brief Gets name of requested service in particular mode space.
 * In thread mode it is thread name, in Inrettupt mode it is interrupt name. For other mode types it is project specific.
 *
 * @return pointer to requested service name. It is always valid pointer - never will be NULL (can be for example "unknown").
 * @param context_id number of service for which name is requested
 */
const char *OSAL_Get_Context_Name(OSAL_Context_Id_XT *context_id);

/**
 * @brief Gets type of requested requested context ID.
 *
 * @return return type of requested system context
 */
OSAL_Context_Type_DT OSAL_Get_Context_Type(OSAL_Context_Id_XT *context_id);

struct OSAL_Thread_Params_eXtendedTag;
/**
 * @brief allocates params pointer for a new context type thread. It is just a pointer into which anything can be stored.
 *
 * @param context_id number of service for which we allocate handler.
 * @result pointer to a pointer under which handler shall be stored by the caller of this function.
 */
struct OSAL_Thread_Params_eXtendedTag *OSAL_Allocate_Context_Thread(OSAL_Context_Id_XT *context_id);

/**
 * @brief dealocated parameters for the thread.
 *
 * @param context_id number of service for which we free the handler.
 */
void OSAL_Free_Context_Thread(OSAL_Context_Id_XT *context_id);

/**
 * @brief Returns pointer to context params (thread or interrupt) if context_id points to a valid context.
 * This function also fills invalid parameters in context_id structure so further call of this function with same context_id pointer will be faster.
 *
 * @param context_id number of service for which we request params. If this pointer is invalid then we return parameters of the currently running context.
 * @result pointer to params if context_id contains at least valid parameter, OSAL_MAKE_INVALID_PTR(void) otherwise.
 */
void *OSAL_Get_Context_Params(OSAL_Context_Id_XT *context_id);

/**
 * @brief executed specific action for all contexts specified by the context_id.
 * There can be more than one contexts if context_id points to path common for multiple contexts.
 * For example, there can be 2 contexts with paths: "uart.1" and "uart.2" running in the system. context_id contains path "uart".
 * In this case action will be executed for both "uart.1" and "uart.2" contexts.
 *
 * @param context_id number of service for which we request action.
 * @param action pointer to function to be called for each requested context.
 * @param params pointer to be provided to action function.
 */
void OSAL_Execute_For_Tree(OSAL_Context_Id_XT *context_id, OSAL_Hvoid_Two_Params_HT action, void *params);

/** @} */ // end of ContextID

/** -------------------------------------------------------------------------------------------------------------------------------
 *                                           Context LOCK
 *  ---------------------------------------------------------------------------------------------------------------------------- */

/** @defgroup CriticalSection Operating System Abstraction Layer - Critical sections management
 *  @brief Getting, calculating time, delays, etc.
 *  @{
 */

/**
 * @brief Prevents context switching.
 */
void OSAL_Enter_Critical_Section(void);

/**
 * @brief Allows context switching.
 */
void OSAL_Exit_Critical_Section(void);

/** @} */ // end of CriticalSection

/** -------------------------------------------------------------------------------------------------------------------------------
 *                                           Context STARTING
 *  ---------------------------------------------------------------------------------------------------------------------------- */

/** @defgroup ContextStart Operating System Abstraction Layer - OS scheduler starting
 *  @brief scheduler starting.
 *  @{
 */

/**
 * @brief Starts OS scheduler.
 */
void OSAL_Start(void);

/** @} */ // end of ContextStart

/** -------------------------------------------------------------------------------------------------------------------------------
 *                                           Context debugging
 *  ---------------------------------------------------------------------------------------------------------------------------- */

/** @defgroup ContextDebugging Operating System Abstraction Layer - Critical sections management
 *  @brief Getting, calculating time, delays, etc.
 *  @{
 */

#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)

/**
 * @brief Prints to logs all contextx registered in the OSAL layer.
 */
void OSAL_List_Contexts(void);

#endif

/** @} */ // end of ContextDebugging

#endif
