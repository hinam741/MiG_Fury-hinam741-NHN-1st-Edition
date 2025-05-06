#include <SDL_image.h>
#include <SDL_mixer.h>

#include "common.h"

#include "background.h"
#include "highscores.h"
#include "init.h"
#include "sound.h"
#include "text.h"

extern App app; // Dùng lại biến app đã được khai báo ở file khác

void initSDL(void)
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;//tăng tốc phần cứng

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)//hàm gọi âm thanh (tần số, định dạng, kênh, chunksize)
	{
		printf("Couldn't initialize SDL Mixer\n");
		exit(1);
	}

	Mix_AllocateChannels(MAX_SND_CHANNELS);//phát 8 hiệu ứng âm thanh cùng lúc (def là 8)

	app.window = SDL_CreateWindow("MiG Fury v1.0.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");//Thiết lập gợi ý cho SDL làm mượt hình ảnh "linear"

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);//sdl image

	SDL_ShowCursor(0);//ẩn con trỏ chuột
}

void initGame(void)
{
	initBackground();

	initStarfield();

	initSounds();

	initFonts();

	initHighscoreTable();

	loadMusic("music/Air Attack HD - White Storm Dam Music - 1.5x.mp3");

	playMusic(1);
}

void cleanup(void)
{
    IMG_Quit();

	SDL_DestroyRenderer(app.renderer);

	SDL_DestroyWindow(app.window);

	SDL_Quit();
}
