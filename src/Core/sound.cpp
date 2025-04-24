#include <SDL_mixer.h>

#include "common.h"

#include "sound.h"

static void loadSounds(void);

static Mix_Chunk *sounds[SND_MAX];//lưu trữ hiệu ứng âm thanh; SND_MAX xác định số lượng phần tử trong mảng sound
static Mix_Music *music;//con trỏ tới music, lưu trữ music

void initSounds(void)
{
	memset(sounds, 0, sizeof(Mix_Chunk *) * SND_MAX);

	music = NULL;//thể hiện ko có nhạc nào chạy nền

	loadSounds();
}

void loadMusic(char *filename)
{
	if (music != NULL)
	{
		Mix_HaltMusic();//dừng phát nhạc
		Mix_FreeMusic(music);//giải phóng nhạc
		music = NULL;//đặt lại nhạc
	}

	music = Mix_LoadMUS(filename);//lưu trữ trỏ đến file nhạc, cho vào bộ nhớ; ko phát nhạc
}

void playMusic(int loop)//phát nhạc
{
	Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);//phát âm thanh(kênh,id,số lần lặp lại)
}

static void loadSounds(void)
{
	sounds[SND_PLAYER_FIRE] = Mix_LoadWAV("sound/334227__jradcoolness__laser.ogg");
	sounds[SND_ALIEN_FIRE] = Mix_LoadWAV("sound/196914__dpoggioli__laser-gun.ogg");
	sounds[SND_PLAYER_DIE] = Mix_LoadWAV("sound/245372__quaker540__hq-explosion.ogg");
	sounds[SND_ALIEN_DIE] = Mix_LoadWAV("sound/10 Guage Shotgun-SoundBible.com-74120584.ogg");
	//sounds[SND_ALIEN_APPEAR] = Mix_LoadWAV("sound/warning-alarm-loop-1-cut.mp3");
	sounds[SND_POINTS] = Mix_LoadWAV("sound/342749__rhodesmas__notification-01.ogg");
}
