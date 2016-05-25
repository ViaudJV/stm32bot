/*
 * Task.cpp
 *
 *  Created on: 23 mai 2016
 *      Author: jul
 */

#include "Middleware/Task.h"

Task::Task() {
	// TODO Auto-generated constructor stub

}

Task::Task(char * name,osPriority priority,uint32_t  instanceNb, uint32_t stacksize)
{
	m_TreadDef.instances = instanceNb;
	m_TreadDef.name = name;
	m_TreadDef.tpriority = priority;
	m_TreadDef.stacksize = stacksize;

}

void Task::Init()
{
	m_TaskHandle = osThreadCreate(&m_TreadDef,NULL);
}

Task::~Task() {
	// TODO Auto-generated destructor stub
}


void Task::Thread(void const * argument)
{

}
