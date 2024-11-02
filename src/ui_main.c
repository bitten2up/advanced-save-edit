/*
* MIT License
*
* Copyright (c) 2024 bitten2up
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

// shitty ui system, doesnt really matter rn as im not trying to make the best ui ever

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "globals.h"
#include "ui_main.h"
#include "r_render.h"

void ui_draw(void)
{
  r_textbox("enable boss time attack", 100,200);
}

void ui_handleclick(int x, int y)
{
  printf("%i:%i\n", x, y);
  if (x >= 10 && x <= 192 && y >= 185 && y <= 209)
    savedata.buffer[0x3D] |= 1 << 1;
}
