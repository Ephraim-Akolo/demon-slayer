
#include "pch.h"
#include "main.h"
#include "GameClass.h"

extern int BG_X_AXIS = 7190;
extern int BG_Y_AXIS = 720;
extern int dragon_size_x = 0;
extern int dragon_size_y = 0;
extern bool Winner = false;

void won(SDL_Renderer *renderer);

int main(int argc, char** argv)
{
	//hide console
	//ShowWindow(FindWindowA("ConsoleWindowClass",NULL),SW_HIDE);

	/// designed to run on fixed window
	///window size is 720 x 680 pixels
	WindowCreate mainwin("game",
		720, 680,
		600, 30,
		SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);

	//window 1 config

	SDL_GetRendererOutputSize(mainwin.renderer, &dragon_size_x, &dragon_size_y);
	//std::cout<<x<<"\t"<<y<<std::endl;
	dragon_size_x = dragon_size_x / 13.66;
	dragon_size_y = dragon_size_y / 7.68;
	SDL_Rect dragon_rect = { 400,20,dragon_size_x,dragon_size_y };
	SDL_Rect boss_rect = { BG_X_AXIS - dragon_size_x * 2,100,dragon_size_x * 2,dragon_size_y * 2 };

	BossActivity win1(mainwin.renderer, &dragon_rect, &boss_rect);

	SDL_Surface *icon = IMG_Load(ICONPIC);
	SDL_SetWindowIcon(mainwin.window, icon);

	int a = 0;
	bool done = false;

	while ((!mainwin.is_done()) && !done)
	{
		//check for keyboard events on window
		mainwin.event();

		//desplay rendered window
		done = win1.display_window(mainwin.get_key_status());

		//check if game if won
		if (Winner == true)
		{
			for (int ii = 100; ii > 0; ii--)
			{
				won(mainwin.renderer);
				SDL_RenderPresent(mainwin.renderer);
			}
		}


		SDL_RenderPresent(mainwin.renderer);
		SDL_SetRenderDrawColor(mainwin.renderer, 100, 100, 100, 255);
		SDL_RenderClear(mainwin.renderer);

		//cheat2
		if (mainwin.get_key_status() == 23)
			SDL_SetWindowResizable(mainwin.window, SDL_TRUE);


	}


	return 0;
}

void won(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
	SDL_RenderClear(renderer);
	WriteWindow w(DEFAULT_FONT, 60);
	w.write_text(renderer, "you won!", 20, 20, 600, 600 / 8, 0, { 0,255,0,255 });
	static RenderImage m(DRAGON_SPRITE, renderer);
	SDL_Rect drect = { 300,160,400,400 };
	SDL_Rect srect = { 0,0,200,200 };
	m.diplay(renderer, &srect, &drect, 0, SDL_FLIP_NONE);
}
