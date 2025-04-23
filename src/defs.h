#ifndef DEFS_H
#define DEFS_H

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

//định nghĩa về chiều dài và rộng của screen
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

//định nghĩa độ dài ký tự tối đa
#define MAX_LINE_LENGTH 1024

#define FPS 60

//định nghĩa bullet
#define PLAYER_SPEED        4
#define PLAYER_BULLET_SPEED 20
#define ALIEN_BULLET_SPEED  8

//định nghĩa tối đa có thể xử lý được 350 phím, tránh tràn mảng
#define MAX_KEYBOARD_KEYS 350 //gọi lại trong struct app của struct.h

//định nghĩa có hiệu lực khi bắn đạn
#define SIDE_PLAYER 0 //phe ta là 0 f
#define SIDE_ALIEN  1 //phe địch là 1 t

#define MAX_STARS 500

#define MAX_SND_CHANNELS 8//phân 8 kênh hiệu ứng âm thanh

enum//ch_ kênh phát âm thanh
{
	CH_ANY = -1,
	CH_PLAYER,
	CH_ALIEN,
	CH_ALIEN_FIRE
};

enum//snd_ hiệu ứng âm thanh
{
	SND_PLAYER_FIRE,
	SND_ALIEN_FIRE,
	SND_PLAYER_DIE,
	SND_ALIEN_DIE,
	SND_ALIEN_APPEAR,
	SND_MAX
};

#endif // DEFS_H
