/*
 * Task.h
 *
 *  Created on: 23 mai 2016
 *      Author: jul
 */

#ifndef TASK_H_
#define TASK_H_

#include "../FreeRTOS/Source/CMSIS_RTOS/cmsis_os.h"
class Task {
public:
	Task(char * name,osPriority priority,uint32_t  instanceNb, uint32_t stacksize);
	virtual ~Task();
	Task();
	void Init();
	virtual void Thread(void const * argument);
private :
	osThreadId 		m_TaskHandle;
	osThreadDef_t 	m_TreadDef;

};

#endif /* TASK_H_ */
