#ifndef DEFS_H
#define DEFS_H

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

//định nghĩa về chiều dài và rộng của screen
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

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

#endif // DEFS_H
