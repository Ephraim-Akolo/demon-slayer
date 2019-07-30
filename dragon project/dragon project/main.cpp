// dragon project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>


int main(int argc,char* argv[])
{
    std::cout << "Hello World!\n"; 
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
	}
	if (TTF_Init()<0)
	{
		std::cout << TTF_GetError << std::endl;
	}
	if (Mix_Init(MIX_INIT_MP3)<0)
	{
		std::cout << Mix_GetError << std::endl;
	}
	if (IMG_Init(IMG_INIT_PNG) < 0)
	{
		std::cout << IMG_GetError << std::endl;
	}
	return 0;
}
