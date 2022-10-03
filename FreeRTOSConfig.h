/*
 * FreeRTOS V202112.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <lpc21xx.h>
#include "GPIO.h"

extern int Task_1_inTime,Task_1_outTime,Task_1_TotTime;
extern int Task_2_inTime,Task_2_outTime,Task_2_TotTime;
extern int Task_3_inTime,Task_3_outTime,Task_3_TotTime;
extern int Task_4_inTime,Task_4_outTime,Task_4_TotTime;
extern int Task_5_inTime,Task_5_outTime,Task_5_TotTime;
extern int Task_6_inTime,Task_6_outTime,Task_6_TotTime;
extern int Sys_Time;
extern float CPU_Load;

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE. 
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION		1
#define configUSE_IDLE_HOOK			0
#define configUSE_TICK_HOOK			1
#define configCPU_CLOCK_HZ			( ( unsigned long ) 60000000 )	/* =12.0MHz xtal multiplied by 5 using the PLL. */
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES		( 4 )
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 90 )
#define configTOTAL_HEAP_SIZE		( ( size_t ) 13 * 1024 )
#define configMAX_TASK_NAME_LEN		( 8 )
#define configUSE_TRACE_FACILITY	1
#define configUSE_16_BIT_TICKS		0
#define configIDLE_SHOULD_YIELD		0
#define configUSE_TIME_SLICING    0
#define configUSE_APPLICATION_TASK_TAG	1
#define configUSE_EDF_SCHEDULER		1
#define configSUPPORT_DYNAMIC_ALLOCATION 1
#define configQUEUE_REGISTRY_SIZE 0
#define configUSE_MUTEXES					1

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1

/************Trace Hooks*************/
#define traceTASK_SWITCHED_OUT()		do{ \
																			if((int)pxCurrentTCB->pxTaskTag==1)\
																			{\
																				GPIO_write(PORT_1,PIN1,PIN_IS_LOW); \
																				Task_1_outTime=T1TC; \
																				Task_1_TotTime+=(Task_1_outTime-Task_1_inTime); \
																			}\
																			else if((int)pxCurrentTCB->pxTaskTag==2)\
																			{\
																				GPIO_write(PORT_1,PIN2,PIN_IS_LOW); \
																				Task_2_outTime=T1TC; \
																				Task_2_TotTime+=(Task_2_outTime-Task_2_inTime); \
																			}\
																			else if((int)pxCurrentTCB->pxTaskTag==3)\
																			{\
																				GPIO_write(PORT_1,PIN3,PIN_IS_LOW); \
																				Task_3_outTime=T1TC; \
																				Task_3_TotTime+=(Task_3_outTime-Task_3_inTime); \
																			}\
																			else if((int)pxCurrentTCB->pxTaskTag==4)\
																			{\
																				GPIO_write(PORT_1,PIN4,PIN_IS_LOW); \
																				Task_4_outTime=T1TC; \
																				Task_4_TotTime+=(Task_4_outTime-Task_4_inTime); \
																			}\
																			else if((int)pxCurrentTCB->pxTaskTag==5)\
																			{\
																				GPIO_write(PORT_1,PIN5,PIN_IS_LOW); \
																				Task_5_outTime=T1TC; \
																				Task_5_TotTime+=(Task_5_outTime-Task_5_inTime); \
																			}\
																			else if((int)pxCurrentTCB->pxTaskTag==6)\
																			{\
																				GPIO_write(PORT_1,PIN6,PIN_IS_LOW); \
																				Task_6_outTime=T1TC; \
																				Task_6_TotTime+=(Task_6_outTime-Task_6_inTime); \
																			}\
																			else if((int)pxCurrentTCB->pxTaskTag==0)\
																			{\
																				GPIO_write(PORT_1,PIN7,PIN_IS_LOW); \
																			}\
																			Sys_Time=T1TC;\
																			CPU_Load=((Task_1_TotTime+Task_2_TotTime+Task_3_TotTime+Task_4_TotTime+Task_5_TotTime+Task_6_TotTime)/(float)Sys_Time)*100;\
																			}while(0)
#define traceTASK_SWITCHED_IN() 		do{ \
																			if((int)pxCurrentTCB->pxTaskTag==1)\
																			{\
																				GPIO_write(PORT_1,PIN1,PIN_IS_HIGH); \
																				Task_1_inTime = T1TC;\
																			}\
																			if((int)pxCurrentTCB->pxTaskTag==2)\
																			{\
																				GPIO_write(PORT_1,PIN2,PIN_IS_HIGH); \
																				Task_2_inTime=T1TC; \
																			}\
																			else if((int)pxCurrentTCB->pxTaskTag==3)\
																			{\
																				GPIO_write(PORT_1,PIN3,PIN_IS_HIGH); \
																				Task_3_inTime=T1TC; \
																			}\
																			else if((int)pxCurrentTCB->pxTaskTag==4)\
																			{\
																				GPIO_write(PORT_1,PIN4,PIN_IS_HIGH); \
																				Task_4_inTime=T1TC; \
																			}\
																			else if((int)pxCurrentTCB->pxTaskTag==5)\
																			{\
																				GPIO_write(PORT_1,PIN5,PIN_IS_HIGH); \
																				Task_5_inTime=T1TC; \
																			}\
																			else if((int)pxCurrentTCB->pxTaskTag==6)\
																			{\
																				GPIO_write(PORT_1,PIN6,PIN_IS_HIGH); \
																				Task_6_inTime=T1TC; \
																			}\
																			else if((int)pxCurrentTCB->pxTaskTag==0)\
																			{\
																				GPIO_write(PORT_1,PIN7,PIN_IS_HIGH); \
																			}\
																			}while(0)
																	
																		

/***********************************************************************************/


#define configSUPPORT_DYNAMIC_ALLOCATION			1
#define configUSE_STATS_FORMATTING_FUNCTIONS	1
#define configGENERATE_RUN_TIME_STATS					1
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() 
#define portGET_RUN_TIME_COUNTER_VALUE()	(T1TC)



#endif /* FREERTOS_CONFIG_H */
