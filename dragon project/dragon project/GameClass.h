#pragma once


#include "main.h"

#define DEFAULT_FONT "fonts/arialbd.ttf"
#define BG_MUSIC "Audacity/mario_1&2.wav"
#define DRAGON_SPRITE "boss/dragonsprite1.png"
#define DRAGON_FIRE "boss/rfgamefire.png"
#define BOSS_SPRITE "boss/dragonboss.png"
#define BACKGROUND_SPRITE "boss/rdgamebg.png"
#define TEMPORARYFONT "fonts/Calling Heart.ttf"
#define ICONPIC "boss/armatureName_normalAttack_0.png"

#define BG_SPEED 10

extern int BG_X_AXIS;
extern int BG_Y_AXIS;
extern int dragon_size_x;
extern int dragon_size_y;

extern bool Winner;

struct POSITION { int x, y; };

class RendererWindowOne
{
protected:
	bool activate_gravity = false;

	SDL_Renderer *renderer;
	unsigned long long int time = 0;
	SDL_Rect win_size_rect = { 0,0,0,0 };

	WriteWindow *write;


	//backgroud var
	bool bg_control = true;
	RenderImage *bg_image;
	SDL_Rect background_showing;
	SDL_Rect background_dst_rect;

	//dragon var
	bool Dcontrol = true;
	SDL_Rect *dragon_rect;
	SDL_Rect src_dragon_rect = { 0,0,200,200 };
	SDL_Rect dst_fire_rect = { 0,0,40,20 };
	RenderImage *dragon_image;
	RenderImage *dragon_fire;
	bool dragon_walk = false;
	bool face_left = false;
	SDL_Rect dragons_supreme_pos = { 0,0,0,0 };
	bool on_land = true;

	//boss var
	SDL_Rect *boss_rect;
	SDL_Rect src_boss_rect = { 0,0,200,200 };
	RenderImage *boss_image;

	//gravity
	bool allow_gravity = false;

	//sounds
	CreateMixer *dg_mix;


public:

	RendererWindowOne(SDL_Renderer *renderer, SDL_Rect *dragon_rect, SDL_Rect *boss_rect)
	{
		this->renderer = renderer;
		this->dragon_rect = dragon_rect;
		this->boss_rect = boss_rect;
		SDL_GetRendererOutputSize(renderer, &win_size_rect.w, &win_size_rect.h);
		this->background_showing.x = 0;
		this->background_showing.y = 0;
		this->background_showing.h = 720;
		this->background_showing.w = 720;

		this->background_dst_rect.x = 0;
		this->background_dst_rect.y = 0;
		this->background_dst_rect.h = 720;
		this->background_dst_rect.w = 720;

		static RenderImage dragon_img(DRAGON_SPRITE, this->renderer);
		static RenderImage dg_fire(DRAGON_FIRE, this->renderer);
		static RenderImage boss_img(BOSS_SPRITE, this->renderer);
		static RenderImage bg_img(BACKGROUND_SPRITE, this->renderer);
		dragon_image = &dragon_img;
		dragon_fire = &dg_fire;
		boss_image = &boss_img;
		bg_image = &bg_img;

		static WriteWindow write(DEFAULT_FONT, 60);
		this->write = &write;

		static CreateMixer bg_mx(BG_MUSIC, 100);
		bg_mx.play(-1);
		
	}
	/*
	FUNCTIONS IN CLASS

	void update_background_showing(int increament,int key_status)
	void dragon_walking()
	void update_walking(int key)
	void dragon_move(int key,int increament)
	void dragon_background_control(int key)
	void update_dragon_supreme_pos()
	void anti_collision()
	void gravity(SDL_Rect *rect)
	void h_anti_collision()
	*/

#define COLLISION1 dragons_supreme_pos.x<=1320
#define COLLISION2 dragons_supreme_pos.x>=1600&&dragons_supreme_pos.x<=2930
#define COLLISION3 dragons_supreme_pos.x>=3150&&dragons_supreme_pos.x<=4470
#define COLLISION4 dragons_supreme_pos.x>=4930&&dragons_supreme_pos.x<=6010
#define COLLISION5 dragons_supreme_pos.x>6010


	///******************** BACKGROUND FUNCTION
	void update_background_showing(int increament, const int key_status)
	{
		if (bg_control)
		{

			if (this->background_showing.x <= 7190 - 720)
			{
				if (key_status&RIGHT_BOTTON) {
					this->background_showing.x += increament;
				}
			}

			if (this->background_showing.x > 0)
			{
				if (key_status&LEFT_BOTTON) {
					this->background_showing.x -= increament;
				}
			}
		}
	}

	/// iterates through dragon sprite
	void dragon_walking()
	{
		if (time % 2 == 1) {
			if (this->dragon_walk)
			{
				if (src_dragon_rect.x < 1000)
				{
					src_dragon_rect.x += 200;
				}
				else {
					src_dragon_rect.x = 0;
				}
			}
			else {
				src_dragon_rect.x = 0;
			}
		}
	}
	///** checks key pressed and increment or decrement dragon position
	void dragon_move(int key, int increament)
	{
		if (Dcontrol)
		{

			if (this->dragon_rect->x <= (this->win_size_rect.w + 72))
			{
				if (key&RIGHT_BOTTON) {
					this->dragon_rect->x += increament;
				}
			}

			if (this->dragon_rect->x >= 72)
			{
				if (key&LEFT_BOTTON)
					this->dragon_rect->x -= increament;
			}
		}

		static int a = -1;
		static int aaa = 1;

		if (key&UP_BOTTON&&aaa == 1)
		{
			jump(dragon_rect);
			a++;

		}
		else if (a >= 3)
		{
			if (!(dragons_supreme_pos.x >= 4920 && dragons_supreme_pos.x <= 6020))
			{

				if (dragons_supreme_pos.y >= win_size_rect.h / 3.5 || (COLLISION3) && dragons_supreme_pos.y > win_size_rect.h / 6)
					aaa = 0;
			}
			else {
				if (COLLISION4&&dragons_supreme_pos.y > win_size_rect.h / 1.85)
					aaa = 0;
			}


			if (aaa == 0) {
				a = -1;
			}
			jump(dragon_rect);
			aaa++;

		}
		else {
			a = -1;
		}
	}
	///*****
	void update_walking(int key)
	{

		//walk movement
		if (key&LEFT_BOTTON || key & RIGHT_BOTTON) {
			dragon_walk = true;
		}
		else
			dragon_walk = false;
		//direction of dragon
		if (key&LEFT_BOTTON)
			this->face_left = true;
		if (key&RIGHT_BOTTON)
			this->face_left = false;


	}

	///********
	void dragon_background_control(int key)
	{
		bool a = false;
		bool b = false;
		///************************************* takes control from dragon and hand it to background
		if ((this->dragon_rect->x <= (int)(this->win_size_rect.w / 5)) && key&LEFT_BOTTON)
		{
			a = true;
			this->Dcontrol = false;
			this->bg_control = true;

			if (this->background_showing.x <= 0)
			{
				this->Dcontrol = true;
				this->bg_control = false;
			}
		}
		///************************************* takes control from dragon and hand it to background
		if ((this->dragon_rect->x >= (int)(this->win_size_rect.w - this->win_size_rect.w / 1.9)) && key&RIGHT_BOTTON)
		{
			b = true;
			this->Dcontrol = false;
			this->bg_control = true;

			if (this->background_showing.x >= (BG_X_AXIS - this->win_size_rect.w))
			{
				this->Dcontrol = true;
				this->bg_control = false;

			}

		}
		if ((!a) && (!b))
		{
			this->Dcontrol = true;
			this->bg_control = false;
		}

	}

	///*************
	void update_dragon_supreme_pos()
	{
		if (this->face_left)
			this->dragons_supreme_pos.x = this->background_showing.x + this->dragon_rect->x;
		else
			this->dragons_supreme_pos.x = this->background_showing.x + this->dragon_rect->x;
		this->dragons_supreme_pos.y = this->dragon_rect->y;

	}

	///*** checks for collision ###################################################
	void anti_collision()
	{
		if (on_land) {
			do {

				if ((dragons_supreme_pos.x >= 4920 && dragons_supreme_pos.x <= 6020) && dragons_supreme_pos.y > win_size_rect.h / 1.55)
				{
					this->allow_gravity = false;
					dragon_rect->y = (int)(win_size_rect.h / 1.5);
					break;
				}
				// assist the former function
				if (dragons_supreme_pos.x >= 4920 && dragons_supreme_pos.x <= 6010)
				{
					this->allow_gravity = true;
					break;
				}
				if ((dragons_supreme_pos.x >= 3150 && dragons_supreme_pos.x <= 4470) && dragons_supreme_pos.y > win_size_rect.h / 4)
				{
					this->allow_gravity = false;
					dragon_rect->y = (int)(win_size_rect.h / 3.97);
					break;
				}
				if (dragons_supreme_pos.y > win_size_rect.h / 2.65)
				{
					this->allow_gravity = false;
					dragon_rect->y = (int)(win_size_rect.h / 2.62);
				}
				else {
					this->allow_gravity = true;
				}
			} while (false);
		}
		else
			this->allow_gravity = true;
	}

	///***** GRAVITY
	void gravity(SDL_Rect *rect)
	{

		static int a2 = 2;
		a2 += 1;

		if (activate_gravity)
		{
			allow_gravity = true;
			a2 += 20;
		}

		if (allow_gravity)
		{
			rect->y += a2;
		}
		else {

			a2 = 2;
		}
	}
	///**** dragon jump.
	void jump(SDL_Rect *rect)
	{

		rect->y -= 20;


	}

	///***** check if on land
	void update_on_land()
	{
		do {
			if (COLLISION4)
			{
				this->on_land = true;
				break;
			}
			if (COLLISION5)
			{
				this->on_land = true;
				break;
			}
			if (COLLISION2)
			{
				this->on_land = true;
				break;
			}
			if (COLLISION3)
			{
				this->on_land = true;
				break;
			}
			if (COLLISION1)
			{
				this->on_land = true;
			}
			else
			{
				this->on_land = false;
			}
		} while (false);
	}

	/// horizontal collision detection
	void h_anti_collision(int*key)
	{
		do {
			if (this->dragons_supreme_pos.x == 6000 && (dragons_supreme_pos.y > win_size_rect.h / 2.42))
			{
				if (*key&RIGHT_BOTTON)
					*key ^= RIGHT_BOTTON;
				break;
			}
			if (this->dragons_supreme_pos.x == 4920 && (dragons_supreme_pos.y > win_size_rect.h / 1.5))
			{
				if (*key&RIGHT_BOTTON)
					*key ^= RIGHT_BOTTON;
				break;
			}
			if (this->dragons_supreme_pos.x == 4480 && (dragons_supreme_pos.y > win_size_rect.h / 4))
			{
				if (*key&LEFT_BOTTON)
					*key ^= LEFT_BOTTON;
				break;
			}
			if (this->dragons_supreme_pos.x == 3140 && (dragons_supreme_pos.y > win_size_rect.h / 4))
			{
				if (*key&RIGHT_BOTTON)
					*key ^= RIGHT_BOTTON;
				break;
			}
			if (this->dragons_supreme_pos.x == 2940 && (dragons_supreme_pos.y > win_size_rect.h / 2.42))
			{
				if (*key&LEFT_BOTTON)
					*key ^= LEFT_BOTTON;
				break;
			}
			if (this->dragons_supreme_pos.x == 1590 && (dragons_supreme_pos.y > win_size_rect.h / 2.42))
			{
				if (*key&RIGHT_BOTTON)
					*key ^= RIGHT_BOTTON;
				break;
			}
			if (this->dragons_supreme_pos.x == 1330 && (dragons_supreme_pos.y > win_size_rect.h / 2.42))
			{
				if (*key&LEFT_BOTTON)
					*key ^= LEFT_BOTTON;
				break;
			}

		} while (false);
	}

	///********************************************
	~RendererWindowOne()
	{
		SDL_DestroyRenderer(this->renderer);
	}

	void display(int keyboard_status);
	void animate_dragon_fire(int key);

};





class BossActivity : public RendererWindowOne
{
private:

	POSITION dragon_fire[20];
	POSITION boss_fire[10];
	bool walk = false;
	int boss_life = 200;

	int boss_init_pos = 0;
	short int hit_point = 2;




	SDL_Rect fd_rect = { boss_init_pos - this->background_showing.x,(int)(boss_rect->y + (dragon_size_y / 1.3)),100,100 };
	SDL_Rect fs_rect = { 1200,0,200,200 };

	SDL_Rect static_rect[7];
	int speed_b = 3;

public:

#define BOSS_SPEED time%100==1
	BossActivity(SDL_Renderer *renderer, SDL_Rect *dragon_rect, SDL_Rect *boss_rect) :
		RendererWindowOne(renderer, dragon_rect, boss_rect)
	{
		//boss_rect->x=BG_X_AXIS-dragon_size_x*2;
		boss_init_pos = boss_rect->x;
		for (int i = 0; i < 20; i++)
		{
			dragon_fire[i] = { 0,0 };
			if (i < 10)
				boss_fire[i] = { 0,0 };
		}
	}

	/// display RendererOne window
	int display_window(int key);

	/// update boss position
	void boss_update_pos()
	{
		this->boss_rect->x = boss_init_pos - this->background_showing.x;
		this->boss_rect->y = win_size_rect.h / 4;
	}

	/// iterates through boss sprite
	void boss_walking()
	{

		if (BOSS_SPEED)
		{
			walk = true;
		}
		if (walk&&time % 5 == 1) {

			if (src_boss_rect.x < 1000)
			{
				src_boss_rect.x += 200;
			}
			else {
				src_boss_rect.x = 0;
				walk = false;
			}
		}
	}



	/// animate moving fire and boss characteristics
	int animate_boss_fire()
	{
		bool done = false;


		static_rect[0] = { 800 - this->background_showing.x,(int)(win_size_rect.h / 2.6),dragon_size_x,dragon_size_y };
		static_rect[1] = { 3400 - this->background_showing.x,(int)(win_size_rect.h / 3.9),dragon_size_x,dragon_size_y };
		static_rect[2] = { 3900 - this->background_showing.x,(int)(win_size_rect.h / 3.9),dragon_size_x,dragon_size_y };
		static_rect[3] = { 2000 - this->background_showing.x,(int)(win_size_rect.h / 2.6),dragon_size_x,dragon_size_y };
		static_rect[4] = { 2500 - this->background_showing.x,(int)(win_size_rect.h / 2.6),dragon_size_x,dragon_size_y };
		static_rect[5] = { 5300 - this->background_showing.x,(int)(win_size_rect.h / 1.5),dragon_size_x,dragon_size_y };
		static_rect[6] = { 5600 - this->background_showing.x,(int)(win_size_rect.h / 1.5),dragon_size_x,dragon_size_y };

		static int i = 0;
		if (src_boss_rect.x == 800)
		{
			i = 0;
			fd_rect.y = boss_rect->y + (int)(dragon_size_y / 1.3);
		}
		fd_rect.x = (boss_init_pos - this->background_showing.x) - 20 - i;
		i += BG_SPEED * speed_b;
		///display boss fire ball
		boss_image->diplay(renderer, &fs_rect, &fd_rect, 0, SDL_FLIP_NONE);
		///display static fire balls
		for (int i = 0; i < 7; i++)
		{
			boss_image->diplay(renderer, &fs_rect, &static_rect[i], 0, SDL_FLIP_NONE);
		}

		/// check for collision with fire balls
		///main dragon fire ball
		if (((dragon_rect->x + dragon_size_x / 1.7) <= (fd_rect.x + dragon_size_x / 1.7) &&
			(dragon_rect->x + dragon_size_x / 1.7) >= fd_rect.x))
		{
			if ((dragon_rect->y <= fd_rect.y + dragon_size_y && dragon_rect->y >= fd_rect.y) ||
				(dragon_rect->y + dragon_size_y / 1.7 <= fd_rect.y + dragon_size_y / 1.7&&dragon_rect->y + dragon_size_y / 1.7 >= fd_rect.y))
			{
				fd_rect.y = -200;
				activate_gravity = true;
			}
		}
		/// contact with dragon
		if ((dragon_rect->x <= boss_rect->x + dragon_size_x * 2 && dragon_rect->x*1.03 >= boss_rect->x) ||
			(dragon_rect->x + dragon_size_x <= boss_rect->y + dragon_size_x * 2 && dragon_rect->x + dragon_size_x >= boss_rect->x))
		{
			if ((dragon_rect->y <= boss_rect->y + dragon_size_y * 2 && dragon_rect->y >= boss_rect->y) ||
				(dragon_rect->y + dragon_size_y <= boss_rect->y + dragon_size_y * 2 && dragon_rect->y + dragon_size_y >= boss_rect->y))
			{
				activate_gravity = true;
			}
		}

		/// contact with static fire balls
		for (int u = 0; u < 7; u++)
		{
			if ((dragon_rect->x <= static_rect[u].x + dragon_size_x / 1.7&&dragon_rect->x >= static_rect[u].x) ||
				(dragon_rect->x + dragon_size_x / 1.7 <= static_rect[u].x + dragon_size_x / 1.7&&dragon_rect->x + dragon_size_x / 1.7 >= static_rect[u].x))
			{
				if ((dragon_rect->y <= static_rect[u].y + dragon_size_y && dragon_rect->y >= static_rect[u].y) ||
					(dragon_rect->y + dragon_size_y / 1.7 <= static_rect[u].y + dragon_size_y / 1.7&&dragon_rect->y + dragon_size_y / 1.7 >= static_rect[u].y))
				{
					activate_gravity = true;
				}
			}
		}

		///dragon fire balls contact with boss
		if ((dst_fire_rect.x <= boss_rect->x + dragon_size_x * 2 && dst_fire_rect.x >= boss_rect->x) ||
			(dst_fire_rect.x + 50 <= boss_rect->y + dragon_size_x * 2 && dst_fire_rect.x + 50 >= boss_rect->x))
		{
			if ((dst_fire_rect.y <= boss_rect->y + dragon_size_y * 1.6 && dst_fire_rect.y >= boss_rect->y) ||
				(dst_fire_rect.y + 20 <= boss_rect->y + dragon_size_y * 1.6 && dst_fire_rect.y + 20 >= boss_rect->y))
			{
				boss_life -= hit_point;
				if (boss_life <= 0) {
					Winner = true;
					done = true;
				}
				if (boss_life < 50 && boss_rect->x + background_showing.x>6400) {
					boss_init_pos -= (int)((boss_rect->x - dragon_rect->x) / 1.5);
					speed_b =(int) 3.5;
				}
				dst_fire_rect.y = -200;
			}
		}


		return done;
	}
	void display_boss_life();
	void cheat1(int key);

};

