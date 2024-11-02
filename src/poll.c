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

#include <SDL2/SDL.h>

#include "globals.h"
#include "poll.h"
#include "ui_main.h"

SDL_Event event;
void i_poll(u8 *mainLoop)
{
  while (SDL_PollEvent(&event))
  {
    switch (event.type) {
      case SDL_QUIT:
        *mainLoop = false;
        break;
        
      case SDL_MOUSEBUTTONDOWN:
        int x, y;
        Uint32 buttons = SDL_GetMouseState(&x, &y);
        if (!ui_handleclick(x,y))
          *mainLoop = false;
        break;
      default:
        break;
    }
  }
}
