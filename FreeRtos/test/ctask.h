// ******************************************************
// * copyright (C) 2021 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/20/2021 by behm
// ******************************************************

#ifndef TASK_H
#define TASK_H

#include <stdint.h>
#include "FreeRTOS.h"

//typedef int UBaseType_t;
//typedef int BaseType_t;
//typedef int TickType_t;
typedef void * TaskHandle_t;

class CTask
{
public:
	CTask(const char *const name, configSTACK_DEPTH_TYPE stackDepth = 256);
	void init();
	void taskStart();
	void setPriority(const UBaseType_t &priority) { m_priority = priority; }
	UBaseType_t priority() const { return m_priority; }

	static char *taskInfo();
protected:
	static void tproc(void *prm);
	virtual void proc();
	TaskHandle_t m_task;
	configSTACK_DEPTH_TYPE m_stackDepth;
	const char *const m_name;
	UBaseType_t m_priority;
};

#endif // TASK_H
