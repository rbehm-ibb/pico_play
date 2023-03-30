#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

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
			printf("Name            State   Prio    Stack   Num\n");
			printf(s);
			printf("***********************************\n");

		}
	}
}
void vBlinkTask2()
{
	gpio_init(0);
	gpio_set_dir(0, GPIO_OUT);
	for (;;)
	{
		gpio_put(0, 1);
		vTaskDelay(500);
		gpio_put(0, 0);
		vTaskDelay(500);
	}
}
void vBlinkTask3()
{
	gpio_init(1);
	gpio_set_dir(1, GPIO_OUT);
	for (;;)
	{
		gpio_put(1, 1);
		vTaskDelay(500);
		gpio_put(1, 0);
		vTaskDelay(200);
	}
}

int main()
{
	stdio_init_all();
	while (! stdio_usb_connected())
	{
	}
	printf("FreeRTOS\n");
	xTaskCreate(vBlinkTask, "Blink Task", 512, NULL, 1, NULL);
//	xTaskCreate(vBlinkTask2, "Blink Task", 128, NULL, 1, NULL);
//	xTaskCreate(vBlinkTask3, "Blink Task", 128, NULL, 1, NULL);
	vTaskStartScheduler();
}
