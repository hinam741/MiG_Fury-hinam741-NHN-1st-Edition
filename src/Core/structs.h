#ifndef STRUCTS_H
#define STRUCTS_H
#include "defs.h"

typedef struct Entity Entity;
typedef struct Explosion Explosion;
typedef struct Debris    Debris;
typedef struct Texture   Texture;

//struct xử lý logic và các hàm draw trong vòng lặp chính
typedef struct
{
	void (*logic)(void);//con trỏ hàm ko tham số, ko trả về
	void (*draw)(void);
} Delegate;

struct Texture
{
	char         name[MAX_NAME_LENGTH];
	SDL_Texture *texture;
	Texture     *next;
};

//struct vẽ, xử lý độ phân giải, window, keyboard
typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window   *window;
	Delegate      delegate; //đại diện
	int           keyboard[MAX_KEYBOARD_KEYS];
	Texture       textureHead, *textureTail;
} App;//biến toàn cục

//struct thực thể
struct Entity
{
	float        x;
	float        y;
	int          w;
	int          h;
	float        dx;
	float        dy;
	int          health;
	int          reload; //theo dõi khả năng bắn của player, reload đạn
	int          side;//khai báo trong defs.h; hoạt động trong stage.cpp
	SDL_Texture *texture;
	Entity      *next; //con trỏ next đến Entity khác
};

//struct thông tin về vụ nổ
struct Explosion
{
	float      x;
	float      y;
	float      dx;
	float      dy;
	int        r, g, b, a;//a là độ trong suốt
	Explosion *next;
};

//struct mảnh vỡ
struct Debris
{
	float        x;
	float        y;
	float        dx;
	float        dy;
	SDL_Rect     rect;
	SDL_Texture *texture;
	int          life;
	Debris      *next;
};

//struct chứa thông tin máy bay và đạn
typedef struct
{
	Entity    fighterHead, *fighterTail;
	Entity    bulletHead, *bulletTail;
	Entity    pointsHead, *pointsTail;
	Explosion explosionHead, *explosionTail;
	Debris    debrisHead, *debrisTail;
	int       score; //tính điểm
} Stage;

//struct các ngôi sao
typedef struct
{
	int x;
	int y;
	int speed;
} Star;

typedef struct
{
	int recent;
	int score;
} Highscore;//cấu trúc điểm

typedef struct
{
	Highscore highscore[NUM_HIGHSCORES];
} Highscores;//lưu mảng điểm cao

#endif // STRUCTS_H
