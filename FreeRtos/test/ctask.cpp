// ******************************************************
// * copyright (C) 2021 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/20/2021 by behm
// ******************************************************

#include "ctask.h"

CTask::CTask(const char *const name, configSTACK_DEPTH_TYPE stackDepth)
	: m_stackDepth(stackDepth)
	, m_name(name)
	, m_priority(1)
{
	init();
}

void CTask::init()
{
}

void CTask::taskStart()
{
	BaseType_t rc = xTaskCreate(tproc, m_name, m_stackDepth, this, tskIDLE_PRIORITY + m_priority, &m_task);
//	Debug.print(DBG_VERBOSE, F("Task::start(<%s> %x) ->%d"), m_name, this, rc);
}

void CTask::tproc(void *prm)
{
	CTask *const me = static_cast<CTask *>(prm);
//	Debug.print(DBG_VERBOSE, F("Task::tproc(<%s> %x)"), me->m_name, prm);
	me->proc();
}

void CTask::proc()
{
	for (;;)
	{
//		Debug.print(DBG_VERBOSE, F("Task::proc(<%s> %x)"), m_name, this);
		vTaskDelay(1000 /  portTICK_PERIOD_MS);
	}
}





char *CTask::taskInfo()
{
	static char s[1000];
	vTaskList(s);
//	Serial.println("Name    State   Prio    Stack   Num");
//	Serial.println("***********************************");
//	Serial.print(s);
//	Serial.println("***********************************");
	return s;
}
