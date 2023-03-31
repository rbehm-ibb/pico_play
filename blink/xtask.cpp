// ******************************************************
// * copyright (C) 2021 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/20/2021 by behm
// ******************************************************

#include <stdio.h>
#include "xtask.h"

Task::Task(const char *const name, configSTACK_DEPTH_TYPE stackDepth)
	: m_stackDepth(stackDepth)
	, m_name(name)
	, m_priority(1)
{
	init();
}

void Task::init()
{
}

void Task::taskStart()
{
	BaseType_t rc = xTaskCreate(tproc, m_name, m_stackDepth, this, tskIDLE_PRIORITY + m_priority, &m_task);
	printf("Task::start(<%s> %x) ->%d\n", m_name, this, rc);
}

void Task::tproc(void *prm)
{
	Task *const me = static_cast<Task *>(prm);
//	printf("Task::tproc(<%s> %x)", me->m_name, prm);
	me->proc();
}

void Task::proc()
{
	for (;;)
	{
		printf("Task::proc(<%s> %x)\n", m_name, this);
		vTaskDelay(1000 /  portTICK_PERIOD_MS);
	}
}





char *Task::taskInfo()
{
	static char s[1000];
	vTaskList(s);
	printf("Name                    State   Prio    Stack   Num\n");
	printf(s);
	printf("***********************************\n");
	return s;
}
