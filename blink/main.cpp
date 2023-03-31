#include <stdio.h>
#include "pico/stdlib.h"
#include <FreeRTOS.h>
#include <task.h>
#include <portable.h>
#include "../ibblib/debug.h"
#include "xtask.h"

class Monitor : public Task
{
public:
	Monitor();
protected:
	void proc() override;
};

Monitor::Monitor()
	: Task("Monitor", 512)
{

}

void Monitor::proc()
{
	static char s[1000];
	int tick =  0;
	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
	for (;;)
	{
		gpio_put(PICO_DEFAULT_LED_PIN, 1);
		vTaskDelay(500);
		gpio_put(PICO_DEFAULT_LED_PIN, 0);
		vTaskDelay(100);
		if (++tick < 10)
		{
			printf("%d\n", tick);
		}
		if (tick == 10)
		{
			vTaskList(s);
			printf("Name                    State   Prio    Stack   Num\n");
			printf(s);
			struct xHeapStats hs;
			vPortGetHeapStats(&hs );
			printf("heap size=%zu, largest=%zu\n", hs.xAvailableHeapSpaceInBytes, hs.xSizeOfLargestFreeBlockInBytes);
		}
	}
}

class Blink : public Task
{
public:
	Blink(int pin);
protected:
	void proc() override;
private:
	int m_pin;
	char *name(int pin);
	char m_name[20];
};


Blink::Blink(int pin)
	: Task(name(pin))
	, m_pin(pin)
{

}

void Blink::proc()
{
	gpio_init(m_pin);
	gpio_set_dir(m_pin, GPIO_OUT);
	for (;;)
	{
		gpio_put(m_pin, 1);
		vTaskDelay(m_pin*100);
		gpio_put(m_pin, 0);
		vTaskDelay((8-m_pin)*100);
	}
}

char *Blink::name(int pin)
{
	sprintf(m_name, "Blink%d", pin);
	return m_name;
}

int main()
{
	stdio_init_all();
	while (! stdio_usb_connected())
	{
	}
	Debug::showSysInfo("FreeRTOS-test");
	printf("FreeRTOS %s\n", tskKERNEL_VERSION_NUMBER);
	Monitor moni;
	Blink blink1(2);
	Blink blink2(3);
	Blink blink3(4);
	Blink blink5(5);
	moni.taskStart();
	blink1.taskStart();
	blink2.taskStart();
	blink3.taskStart();
	blink5.taskStart();
	vTaskStartScheduler();
}
