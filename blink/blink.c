#include <stdio.h>
#include "pico/stdlib.h"
#include <FreeRTOS.h>
#include <task.h>
#include "xtask.h"

void vBlinkTask()
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
		printf("%d\n", ++tick);
		if ((tick % 20) == 0)
		{
			vTaskList(s);
			printf("Name                    State   Prio    Stack   Num\n");
			printf(s);
			printf("***********************************\n");

		}
	}
}

void vBlinkTask2()
{
	const int pin  = 2;
	gpio_init(pin);
	gpio_set_dir(pin, GPIO_OUT);
	for (;;)
	{
		gpio_put(pin, 1);
		vTaskDelay(pin*100);
		gpio_put(pin, 0);
		vTaskDelay(500);
	}
}

void vBlinkTask3()
{
	const int pin  = 3;
	gpio_init(pin);
	gpio_set_dir(pin, GPIO_OUT);
	for (;;)
	{
		gpio_put(pin, 1);
		vTaskDelay(pin*100);
		gpio_put(pin, 0);
		vTaskDelay(500);
	}
}

void vBlinkTask4()
{
	const int pin  = 4;
	gpio_init(pin);
	gpio_set_dir(pin, GPIO_OUT);
	for (;;)
	{
		gpio_put(pin, 1);
		vTaskDelay(pin*100);
		gpio_put(pin, 0);
		vTaskDelay(500);
	}
}

int main()
{
	stdio_init_all();
	while (! stdio_usb_connected())
	{
	}
	printf("FreeRTOS\n");
	xTaskCreate(vBlinkTask, "Blink1", 512, NULL, 1, NULL);
	xTaskCreate(vBlinkTask2, "Blink2", 128, NULL, 1, NULL);
	xTaskCreate(vBlinkTask3, "Blink3", 128, NULL, 1, NULL);
	xTaskCreate(vBlinkTask4, "Blink4", 128, NULL, 1, NULL);
	vTaskStartScheduler();
}
