// ******************************************************
// * copyright (C) 2021 by Reinhardt Behm/rbehm@hushmail.com
// * All Rights reserved
// * created 2/15/2021 by behm
// ******************************************************

#ifndef XIAODISPDEF_H
#define XIAODISPDEF_H

#include "arddef.h"

// I/O
namespace XIAO
{
const int DWG_S = A0;
const int TFT_DC = A1;
const int TFT_RES = A2;
const int TFT_CS = A3;
const int DWG_A = A4;
const int DWG_B = A5;
const int SW3 = A6;
const int SW2 = A7;
const int SCK = A8;
const int SW1 = A9;
const int MOSI = A10;

// disp parm
const int TFT_W = 320;
const int TFT_H = 240;

};

#endif // XIAODISPDEF_H
