// ******************************************************
// * copyright (C) 2021 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 1/22/2021 by behm
// ******************************************************

#ifndef ARDDEF_H
#define ARDDEF_H

#include <Arduino.h>
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); obj.print(" "); return obj; }
template<class T> inline Print &operator <<=(Print &obj, T arg) { obj.println(arg); return obj; }

void strcpyN(char *dest, const char * src, size_t max);

#ifdef QT_CORE_LIB

#include <String.h>
//using arduino;

typedef int BaseType_t;
typedef uint UBaseType_t;
const int LED_BUILTIN=17;
//const int OUTPUT=1;
//const int INPUT=2;
//const int INPUT_PULLUP=2;
const int A0=0;
const int A1=1;
const int A2=2;
const int A3=3;
const int A4=4;
const int A5=5;
const int A6=6;
const int A7=7;
const int A8=8;
const int A9=9;
const int A10=10;
const int SPI_MODE3= 3;
const int portTICK_PERIOD_MS=1000;
extern void delay(int);
extern void pinMode(int, int);
extern int digitalRead(int);
extern void digitalWrite(int,int);
Print Serial;
Print Serial1;

#endif

#endif // ARDDEF_H
