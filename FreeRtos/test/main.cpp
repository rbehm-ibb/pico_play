#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "ctask.h"

static char s[2000];

static void taskInfo()
{
	vTaskList(s);
	printf("Name    State   Prio    Stack   Num\n");
	printf(s);
}

class Blink : public CTask
{
public:
	Blink();

	// CTask interface
protected:
	virtual void proc() override;
};

class Report : public CTask
{
public:
	Report();

	// CTask interface
protected:
	virtual void proc() override;
};

Blink::Blink()
	: CTask("Blink", 256)
{

}

void Blink::proc()
{
	for (;;)
	{
		gpio_put(PICO_DEFAULT_LED_PIN, 1);
		vTaskDelay(100);
		gpio_put(PICO_DEFAULT_LED_PIN, 0);
		vTaskDelay(250);
	}
}

Report::Report()
	: CTask("Report", 256)
{
}

void Report::proc()
{
	char *p = NULL;
	for (int i = 1;; ++i)
	{
//		vTaskDelay(2000);
		if (i % 10 == 0)
		{
			vTaskList(s);
			p = s;
		}
		if (p)
		{
			char ss[21];
			memset(ss, 0, 21);
			memcpy(ss, p, 20);
			for (int i = 0; i < 20; ++i)
			{
				if (*p == 0)
				{
					p = NULL;
					break;
				}
				++p;
			}
			printf(ss);
			vTaskDelay(10);
		}
		else
		{
			printf("Hello %d\n", i);
			vTaskDelay(2000);
		}
	}
}

#if 0
void vBlinkTask()
{
//	taskInfo();
	for (;;)
	{
		gpio_put(PICO_DEFAULT_LED_PIN, 1);
		vTaskDelay(100);
		gpio_put(PICO_DEFAULT_LED_PIN, 0);
		vTaskDelay(250);
	}
}

void vReportTask()
{
	char *p = NULL;
	for (int i = 1;; ++i)
	{
//		vTaskDelay(2000);
		if (i % 10 == 0)
		{
			vTaskList(s);
			p = s;
		}
		if (p)
		{
			char ss[21];
			memset(ss, 0, 21);
			memcpy(ss, p, 20);
			for (int i = 0; i < 20; ++i)
			{
				if (*p == 0)
				{
					p = NULL;
					break;
				}
				++p;
			}
			printf(ss);
			vTaskDelay(10);
		}
		else
		{
			printf("Hello %d\n", i);
			vTaskDelay(2000);
		}
	}
}
}
#endif

int main()
{
	stdio_usb_init();
	while (! stdio_usb_connected())
	{
	}
	printf("FreeRTOS test\n");
	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
	Blink blink;
	Report report;
//	xTaskCreate(&vBlinkTask, "Blink Task", 128, NULL, 1, NULL);
//	xTaskCreate(vReportTask, "Report Task", 256, NULL, 1, NULL);
//	taskInfo();
	printf("FreeRTOS start\n");
	vTaskStartScheduler();
	return 0;
}

