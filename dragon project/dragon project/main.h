#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>


enum CONST {
	LEFT_BOTTON = 0B000001,
	RIGHT_BOTTON = 0B000010,
	UP_BOTTON = 0B000100,
	DOWN_BOTTON = 0B001000,
	SPACE_BOTTON = 0B010000,
	S_BOTTON = 0B100000

};


///**************************** write class ********************************************///
// to write string to a window
class WriteWindow
{
private:
	std::string font_dir;
	TTF_Font *font;
	SDL_Surface *surface = NULL;
	int size_val;
	SDL_Rect Wrect;
public:

	SDL_Texture *texture = NULL;



	WriteWindow(std::string font_dir, int size_val)
	{
		switch (size_val)
		{
		case 12:
			this->size_val = size_val;
			break;
		case 24:
			this->size_val = size_val;
			break;
		case 32:
			this->size_val = size_val;
			break;
		case 48:
			this->size_val = size_val;
			break;
		case 60:
			this->size_val = size_val;
			break;
		case 72:
			this->size_val = size_val;
			break;
		default:
			std::cout << "Invalid Font Size" << std::endl << "size 32 is initialize" << std::endl;
			this->size_val = 32;
			break;
		}
		TTF_Init();
		this->font = TTF_OpenFont(font_dir.c_str(), this->size_val);
		if (this->font == NULL)
		{
			std::cout << "Invalid font directory" << std::endl << SDL_GetError() << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	~WriteWindow()
	{
		TTF_CloseFont(this->font);
		TTF_Quit();
	}

	void write_text(SDL_Renderer *renderer, std::string buffer, int pos_x, int pos_y, int size_w, int size_h, double orientation, SDL_Color color)
	{
		this->surface = TTF_RenderText_Blended(this->font, buffer.c_str(), color);
		this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);

		Wrect.h = size_h;
		Wrect.w = size_w;
		Wrect.x = pos_x;
		Wrect.y = pos_y;
		SDL_RenderCopyEx(renderer, this->texture, NULL, &Wrect, orientation, NULL, SDL_FLIP_NONE);
		SDL_FreeSurface(this->surface);
		SDL_DestroyTexture(this->texture);
	}

};
///*********************************** end of write class *******************************************///


///************************************* window class ****************************************************///
//create window
class WindowCreate {
private:
	std::string name;
	int win_w, win_h, win_x, win_y, win_flag;

	SDL_Event PEvent;
	bool done = false;
	int keyboard_status = 0;

public:
	SDL_Window *window;
	SDL_Renderer *renderer;

	std::string get_name()
	{
		return this->name;
	}

	void set_name(std::string name)
	{
		this->name = name;
	}

	void set_window(int win_w, int win_h, int win_x, int win_y, int win_flag)
	{
		this->win_w = win_w;
		this->win_h = win_h;
		this->win_x = win_x;
		this->win_y = win_y;
		this->win_flag = win_flag;
	}

	int get_key_status()
	{
		return this->keyboard_status;
	}
	void set_key_status(int key)
	{
		this->keyboard_status = key;
	}

	bool is_done()
	{
		return this->done;
	}

	void event()
	{

		this->done = false;

		while (SDL_PollEvent(&this->PEvent))
		{
			switch (this->PEvent.type)
			{
			case SDL_QUIT:
			case SDL_WINDOWEVENT_CLOSE:
				this->done = true;
				break;
			case SDL_KEYDOWN:
			{
				///game specific.
				switch (this->PEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					this->done = true;
					break;
				case SDLK_LEFT:
				case SDLK_a:
					this->keyboard_status |= LEFT_BOTTON;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					this->keyboard_status |= RIGHT_BOTTON;
					break;
				case SDLK_UP:
				case SDLK_w:
					this->keyboard_status |= UP_BOTTON;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					this->keyboard_status |= DOWN_BOTTON;
					break;
				case SDLK_SPACE:
					this->keyboard_status |= SPACE_BOTTON;
					break;
				default:
					std::cout << "KEY PRESSED NOT SET!" << std::endl;
					break;
				}
			}
			break;

			case SDL_KEYUP:
			{
				///game specific.
				switch (this->PEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					this->done = true;
					break;
				case SDLK_LEFT:
				case SDLK_a:
					this->keyboard_status ^= LEFT_BOTTON;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					this->keyboard_status ^= RIGHT_BOTTON;
					break;
				case SDLK_UP:
				case SDLK_w:
					this->keyboard_status ^= UP_BOTTON;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					this->keyboard_status ^= DOWN_BOTTON;
					break;
				case SDLK_SPACE:
					this->keyboard_status ^= SPACE_BOTTON;
					break;

				}
			}
			break;
			}
		}

	}

	WindowCreate(std::string name, int win_w, int win_h, int win_x, int win_y, int win_flag)
	{
		this->name = name;
		this->window = NULL;
		this->renderer = NULL;
		this->win_w = win_w;
		this->win_h = win_h;
		this->win_x = win_x;
		this->win_y = win_y;
		this->win_flag = win_flag;
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow(this->name.c_str(), win_x, win_y, win_w, win_h, win_flag);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	}

	~WindowCreate()
	{
		SDL_DestroyWindow(this->window);
		SDL_DestroyRenderer(this->renderer);
		SDL_Quit();
	}

};
///******************************* end of window class ******************************************************************///


///**************************************** mixer class *****************************************************///
//create specific sound
class CreateMixer
{
private:
	Mix_Chunk *chunk1 = NULL;

public:


	CreateMixer(std::string chunk_dir, int volume)
	{
		Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
		this->chunk1 = Mix_LoadWAV(chunk_dir.c_str());
		Mix_VolumeChunk(this->chunk1, volume);
	}
	void s_play(int repeat = 0)
	{
		Mix_HaltChannel(-1);
		Mix_PlayChannel(-1, chunk1, repeat);
	}
	void play(int repeat = 0, int channel = -1)
	{
		Mix_HaltChannel(channel);
		Mix_PlayChannel(channel, chunk1, repeat);
	}
	~CreateMixer()
	{
		Mix_FreeChunk(this->chunk1);
	}
};
///******************************************** end of mixer class ***************************************************///

///********************************************* renderer image to the window *****************************************///
//display image to window
class RenderImage
{
private:
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
public:


	RenderImage(std::string png_dir, SDL_Renderer *renderer)
	{
		this->surface = IMG_Load(png_dir.c_str());
		if (this->surface == NULL)
		{
			std::cout << IMG_GetError() << std::endl;
			system("pause");
			exit(EXIT_FAILURE);
		}
		this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
		if (this->texture == NULL)
		{
			std::cout << IMG_GetError() << std::endl;
			system("pause");
			exit(EXIT_FAILURE);
		}
		SDL_FreeSurface(this->surface);
	}
	~RenderImage()
	{
		SDL_DestroyTexture(this->texture);
	}

	void diplay(SDL_Renderer *renderer, SDL_Rect *src_rect, SDL_Rect *dst_rect, double angle, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(renderer, this->texture, src_rect, dst_rect, angle, NULL, flip);
	}
};
///********************************************** end of image class ****************************************************///

