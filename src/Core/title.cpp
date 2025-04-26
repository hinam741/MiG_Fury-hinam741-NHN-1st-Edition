#include "common.h"

#include "background.h"
#include "draw.h"
#include "highscores.h"
#include "stage.h"
#include "text.h"
#include "title.h"

extern App app;

static void logic(void);
static void draw(void);
static void drawLogo(void);

static SDL_Texture *logoTexture;
static SDL_Texture *creditTexture;
static int          reveal = 0;//khởi tạo biến tĩnh reveal để vẽ logo
static int          timeout;//thời gian chờ để nền và chữ k xuất hiện cùng nhau

void initTitle(void)
{
    initBackground();

	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

	logoTexture = loadTexture("gfx/logo.png");
	creditTexture = loadTexture("gfx/credit_400x118.png");

	timeout = FPS * 6;
}

static void logic(void)
{
	doBackground();

	doStarfield();

	if (reveal < SCREEN_HEIGHT)
	{
		reveal++;
	}

	if (--timeout <= 0)
	{
		initHighscores();
	}

	if (app.keyboard[SDL_SCANCODE_LCTRL])
	{
		initStage();
	}
}

static void draw(void)
{
	drawBackground();

	drawStarfield();

	drawLogo();

	if (timeout % 40 < 20)
	{
		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "PRESS LCTRL TO PLAY!");
	}
}

static void drawLogo(void)
{
	SDL_Rect r;

	r.x = 0;
	r.y = 0;

	SDL_QueryTexture(logoTexture, NULL, NULL, &r.w, &r.h);

	r.h = MIN(reveal, r.h);

	blitRect(logoTexture, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 100);

	SDL_QueryTexture(creditTexture, NULL, NULL, &r.w, &r.h);

	r.h = MIN(reveal, r.h);

	blitRect(creditTexture, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 280);
}
