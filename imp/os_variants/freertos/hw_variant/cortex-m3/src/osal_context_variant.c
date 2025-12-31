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

#ifndef OSAL_CONTEXT_VARIANT_C_
#define OSAL_CONTEXT_VARIANT_C_
#endif

OSAL_Context_Type_DT OSAL_Get_Current_Context_Type(void)
{
   uint32_t current_interrupt;
   OSAL_Context_Type_DT result = OSAL_CONTEXT_TYPE_THREAD;

   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   /* Obtain the number of the currently executing interrupt. */
   __asm volatile( "mrs %0, ipsr" : "=r"( current_interrupt ) );

   if(0 != current_interrupt)
   {
      result = OSAL_CONTEXT_TYPE_INTERRUPT;
   }

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);

   return result;
} /* OSAL_Get_Current_Context_Type */

OSAL_Context_Unique_Id_DT OSAL_Get_Current_Context_Unique_Id(void)
{
   TaskHandle_t task_handle;
   uint32_t current_interrupt;
   OSAL_Context_Unique_Id_DT result = -1;

   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   /* Obtain the number of the currently executing interrupt. */
   __asm volatile( "mrs %0, ipsr" : "=r"( current_interrupt ) );

   if(0 != current_interrupt)
   {
      result = (OSAL_Context_Unique_Id_DT)current_interrupt;
   }
   else if(OSAL_BOOL_IS_TRUE(osal_context.scheduler_started))
   {
      task_handle = xTaskGetCurrentTaskHandle();
      if(NULL != task_handle)
      {
         result = uxTaskGetTaskNumber(task_handle);
      }
   }

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);

   return result;
} /* OSAL_Get_Current_Context_Unique_Id */

OSAL_Context_Id_XT OSAL_Get_Current_Context_Id(void)
{
   TaskHandle_t task_handle;
   uint32_t current_interrupt;
   OSAL_Context_Id_XT result;

   OSAL_ENTER_FUNC(OSAL_DBG_CONTEXT);

   /* Obtain the number of the currently executing interrupt. */
   __asm volatile( "mrs %0, ipsr" : "=r"( current_interrupt ) );

   if(0 != current_interrupt)
   {
      result.id   = (OSAL_Context_Unique_Id_DT)current_interrupt;
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
      result.path = osal_context.interrupts[result.id].tracking.context_id.path;// OSAL_Get_Interrupt_Name(result.id);
#endif
   }
   else if(OSAL_BOOL_IS_TRUE(osal_context.scheduler_started))
   {
      task_handle = xTaskGetCurrentTaskHandle();
      if(NULL != task_handle)
      {
         result.id   = uxTaskGetTaskNumber(xTaskGetCurrentTaskHandle());
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
         result.path = osal_context.threads[result.id - OSAL_NUM_INTERRUPTS].tracking.context_id.path;
#endif
      }
      else
      {
         result.id   = -1;
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
         result.path = "---";
#endif
      }
   }
   else
   {
      result.id = -1;
#if(OSAL_FEATURE_PRESENT == OSAL_IDENTIFY_CONTEXT_BY_PATH_SUPPORTED)
         result.path = "main";
#endif
   }

   OSAL_EXIT_FUNC(OSAL_DBG_CONTEXT);

   return result;
} /* OSAL_Get_Current_Context_Id */

void OSAL_Enter_Critical_Section(void)
{
   /**
    * I would prefer to use something from OS, like portENTER_CRITICAL/portEXIT_CRITICAL
    * but unfortunately portENTER_CRITICAL/portEXIT_CRITICAL cannot be used from IRQ context
    */
   __asm volatile( "cpsid i" ::: "memory" );
   __asm volatile( "dsb" );
   __asm volatile( "isb" );
   ++osal_context.critical_global_cntr_isr;
} /* OSAL_Enter_Critical_Section */

void OSAL_Exit_Critical_Section(void)
{
   /**
    * I would prefer to use something from OS, like portENTER_CRITICAL/portEXIT_CRITICAL
    * but unfortunately portENTER_CRITICAL/portEXIT_CRITICAL cannot be used from IRQ context
    */
   if(osal_context.critical_global_cntr_isr > 0)
   {
      --osal_context.critical_global_cntr_isr;
   }
   if(0 == osal_context.critical_global_cntr_isr)
   {
      __asm volatile( "cpsie i" ::: "memory" );
      __asm volatile( "dsb" );
      __asm volatile( "isb" );
   }
} /* OSAL_Exit_Critical_Section */

