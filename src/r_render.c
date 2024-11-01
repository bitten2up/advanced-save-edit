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

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "r_render.h"

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
SDL_Texture* text;
SDL_Rect textRec;

void* SDL_tex_loader(const char *path);

void InitWindow(const char* p_title, int p_w, int p_h)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window failed to init %s\n", SDL_GetError());
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Renderer failed to init %s\n", SDL_GetError());
	}
	TTF_Init();
	font = TTF_OpenFont("assets/BitPotionExt.ttf", 24);
	if (font == NULL) {
		printf("font failed to init %s\n", SDL_GetError());
  }
}

SDL_Texture* loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);
	if (texture == NULL)
	{
		printf("failed to load texture %s, SDL backtrace %s\n", p_filePath, SDL_GetError());
		exit(1);
	}
	return texture;
}



/*
- x, y: upper left corner.
- texture, rect: outputs.
*/
void r_text(char* message, int x, int y) {
  int text_width;
  int text_height;
  SDL_Surface *surface;
  SDL_Color textColor = {255, 255, 255, 0};

  surface = TTF_RenderText_Solid(font, message, textColor);
  text = SDL_CreateTextureFromSurface(renderer, surface);
  text_width = surface->w;
  text_height = surface->h;
  SDL_FreeSurface(surface);
  textRec.x = x - text_width * 0.5;
  textRec.y = y - text_height * 0.5;
  textRec.w = text_width;
  textRec.h = text_height;
  SDL_RenderCopy(renderer, text, NULL, &textRec);
	SDL_DestroyTexture(text);
}

void CloseWindow(void)
{
	SDL_DestroyTexture(text);
  TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void r_clear(void)
{
	SDL_RenderClear(renderer);
}

#if 0
void r_sprite(e_entitySprite* e)
{
	SDL_RenderCopy(renderer, e->sprite, &e->src, &e->dst);
}
#endif


void r_display()
{
	SDL_RenderPresent(renderer);
}
