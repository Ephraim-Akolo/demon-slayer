
#include "pch.h"
#include "GameClass.h"

extern int BG_X_AXIS;
extern int BG_Y_AXIS;
extern int dragon_size_x;
extern int dragon_size_y;



void RendererWindowOne::display(int keyboard_status)
{
	time++;
	//background
	h_anti_collision(&keyboard_status);
	dragon_background_control(keyboard_status);
	update_walking(keyboard_status);
	dragon_walking();
	update_on_land();
	dragon_move(keyboard_status, BG_SPEED);

	update_background_showing(BG_SPEED, keyboard_status);
	update_dragon_supreme_pos();

	anti_collision();
	gravity(this->dragon_rect);

	bg_image->diplay(this->renderer, &background_showing, &this->background_dst_rect, 0, SDL_FLIP_NONE);

	//dragon
	if (this->face_left)
		dragon_image->diplay(this->renderer, &src_dragon_rect, dragon_rect, 0, SDL_FLIP_NONE);
	else
		dragon_image->diplay(this->renderer, &src_dragon_rect, dragon_rect, 0, SDL_FLIP_HORIZONTAL);
}

/// dragon fire animation
void RendererWindowOne::animate_dragon_fire(int key)
{
	static short int key_dir = RIGHT_BOTTON;
	static short int processing = 0;
	/// adjust
	static short int adj = dragon_size_y / 5;
	/// adjust
	static short int proces_time = 20;
	static short int running_block = 2;

	static short int speed = BG_SPEED * 3;

	if (key&RIGHT_BOTTON)
		key_dir = RIGHT_BOTTON;
	else if (key&LEFT_BOTTON)
		key_dir = LEFT_BOTTON;


	if (processing <= 0)
	{
		if (key_dir&LEFT_BOTTON&&key&SPACE_BOTTON)
		{
			dst_fire_rect.x = dragon_rect->x - dragon_size_x / 2;
			dst_fire_rect.y = dragon_rect->y + adj;
			processing = proces_time;
			running_block = 0;
		}
		else if (key_dir&RIGHT_BOTTON&&key&SPACE_BOTTON)
		{
			dst_fire_rect.x = (int)(dragon_rect->x + dragon_size_x / 1.8);
			dst_fire_rect.y = dragon_rect->y + adj;
			processing = proces_time;
			running_block = 1;
		}
		else
		{
			running_block = 2;
		}

		///
		if (running_block == 0)
		{
			dst_fire_rect.x -= (speed);
			processing--;
			dragon_fire->diplay(this->renderer, NULL, &dst_fire_rect, 0, SDL_FLIP_HORIZONTAL);
		}
		else if (running_block == 1)
		{
			dst_fire_rect.x += (speed);
			processing--;
			dragon_fire->diplay(this->renderer, NULL, &dst_fire_rect, 0, SDL_FLIP_NONE);
		}
	}
	else {
		if (running_block == 0)
		{
			dst_fire_rect.x -= (speed);
			processing--;
			dragon_fire->diplay(this->renderer, NULL, &dst_fire_rect, 0, SDL_FLIP_HORIZONTAL);
		}
		else if (running_block == 1)
		{
			dst_fire_rect.x += (speed);
			processing--;
			dragon_fire->diplay(this->renderer, NULL, &dst_fire_rect, 0, SDL_FLIP_NONE);
		}
	}
}

/// BossActivity function
int BossActivity::display_window(int key)
{
	bool done = false;

	/// display background and dragon in parent class
	display(key);

	/// update boss position
	boss_update_pos();

	///iterates through boss sprite
	boss_walking();

	/// boss shoot fire balls and checks for collision
	done = animate_boss_fire();
	///dragon shoot fire balls
	animate_dragon_fire(key);

	///display boss
	this->boss_image->diplay(this->renderer, &src_boss_rect, boss_rect, 0, SDL_FLIP_HORIZONTAL);

	///display boss life
	display_boss_life();

	///GAME OVER
	if (this->dragons_supreme_pos.y >= this->win_size_rect.h)
	{
		done = true;
	}

	//cheat1
	cheat1(key);
	return done;
}

void BossActivity::display_boss_life()
{

	SDL_Rect life_bar = { 700 - boss_life,20,boss_life,20 };
	SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(this->renderer, &life_bar);
	write->write_text(this->renderer, "BOSS LIFE", 510, 20, 180, 20, 0, { 50,50,50,255 });
}

///cheats
void BossActivity::cheat1(int key)
{
	if (key == 30)
		hit_point = 40;
}


