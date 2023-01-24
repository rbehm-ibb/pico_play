#include <Arduino.h>
#include <cstdint>
#include <math.h>
//#include <Arduino_DebugUtils.h>

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include "global.h"

Adafruit_ST7789 tft(A3, A1, A2);

void setup(void)
{
	delay(2000);
	Serial.begin(115200);
	while (! Serial) {}
	pinMode(A3, OUTPUT);
	digitalWrite(A3, 0);
	Serial.println(F("DisTest 0.1pico"));
	digitalWrite(A3, 1);
	tft.init(240, 320/*, SPI_MODE3*/);
	tft.setRotation(3);
	tft.setSPISpeed(100000000);
	tft.fillScreen(ST77XX_BLACK);
	tft.setTextColor(ST77XX_WHITE);
	tft.setTextSize(2);
	tft.setCursor(0, 0);
	tft.print("IbQt V0.1");
#if 0
	buttons.start();
	monitor.start();
	display.start(buttons.buttonQueue(), buttons.dwgQueue());
	Task::taskInfo();
	vTaskStartScheduler();
#endif

}

void loop()
{
	if (Serial.available())
	{
		char c = Serial.read();
		switch (c)
		{
		case 's':
			tft.fillScreen(ST77XX_BLACK);
			break;
		case 'w':
			tft.fillScreen(ST77XX_WHITE);
			break;
		case 'r':
			tft.fillScreen(ST77XX_RED);
			break;
		case 'g':
			tft.fillScreen(ST77XX_GREEN);
			break;
		case 'b':
			tft.fillScreen(ST77XX_BLUE);
			break;
		}
	}
}
