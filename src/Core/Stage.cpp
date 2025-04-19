 //Khởi tạo logic trò chơi
#include "common.h"
#include "Graphics\draw.h"
#include "stage.h"
#include "util.h"

extern App   app;
extern Stage stage;
//Khai báo các hàm cần thiết
static void logic(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void doPlayer(void);
static void doFighters(void);
static void doBullets(void);
static void drawFighters(void);
static void drawBullets(void);
static void spawnEnemies(void);
static int  bulletHitFighter(Entity *b); //khai báo hàm khi đạn hit fighter

static Entity      *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static int          enemySpawnTimer;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;

	initPlayer();

	bulletTexture = loadTexture("gfx/playerBullet.png");
	enemyTexture = loadTexture("gfx/b52_enemy-200x200.png");

	enemySpawnTimer = 0;
}

static void initPlayer()
{
	player = (Entity*)malloc(sizeof(Entity));//ép kiểu
	memset(player, 0, sizeof(Entity));
	stage.fighterTail->next = player;
	stage.fighterTail = player;

	player->x = 100;
	player->y = 100;
	player->texture = loadTexture("gfx/mig21_player-150x150.png");
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);

	player->side = SIDE_PLAYER;
}


//logic của trò chơi
static void logic(void)
{
	doPlayer(); //liên kết với con trỏ logic của app.delegate

	doFighters();

	doBullets();

	spawnEnemies();
}

static void doPlayer(void)
{
	player->dx = player->dy = 0;

	//nếu reload lớn hớn 0 thì giảm lại
	if (player->reload > 0)
	{
		player->reload--;
	}

	if (app.keyboard[SDL_SCANCODE_UP])
	{
		player->dy = -PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_DOWN])
	{
		player->dy = PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_LEFT])
	{
		player->dx = -PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_RIGHT])
	{
		player->dx = PLAYER_SPEED;
	}

	if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0)
	{
		fireBullet();
	}
}

static void fireBullet(void)
{
    //tạo đối tượng cho bullet
	Entity *bullet;

	bullet = (Entity*)malloc(sizeof(Entity));//ép kiểu
	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->x = player->x;//gán tọa độ của bullet cho người chơi
	bullet->y = player->y;
	bullet->dx = PLAYER_BULLET_SPEED;
	bullet->health = 1;
	bullet->texture = bulletTexture;//gán kết cấu bullet cho bộ kết cấu trước đó
	bullet->side = SIDE_PLAYER; //side player

	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	//gán bullet ở vị trí trung tâm hơn, vì bị lệch
	bullet->y += (player->h / 2) - (bullet->h / 2);

	//thời gian nạp đạn là 8 khung hình
	player->reload = 8;
}

//hàm xử lý chuyển động và xóa fighters nếu ra khỏi màn hình bên trái
static void doFighters(void)
{
	Entity *e, *prev;

	prev = &stage.fighterHead;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		e->x += e->dx;
		e->y += e->dy;

		if (e != player && (e->x < -e->w || e->health == 0))//cập nhật vị trí theo vận tốc, xóa nếu health bằng 0
		{
			if (e == stage.fighterTail)//nếu kẻ thù ra khỏi màn hình
			{
				stage.fighterTail = prev;
			}

			//nếu đây là phần tử cuối cùng, cập nhật tail
			prev->next = e->next;
			free(e);
			e = prev;//xóa node e và cập nhật ds
		}

		prev = e; //cập nhật prev cho vòng tiếp theo
	}
}

static void doBullets(void)
{
	Entity *b, *prev;

	prev = &stage.bulletHead;

	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		b->x += b->dx;
		b->y += b->dy;

		if (bulletHitFighter(b) || b->x > SCREEN_WIDTH)//nếu đạn ra khỏi màn hình hoặc đạn hit fighter thì giải phóng b
		{
			if (b == stage.bulletTail)
			{
				stage.bulletTail = prev;
			}

			prev->next = b->next;
			free(b);
			b = prev;
		}

		prev = b;
	}
}

//hàm nội bộ trong file nếu địch bị đạn bắn trúng
static int bulletHitFighter(Entity *b)
{
	Entity *e;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))//chỉ kiểm tra va chạm khác phe; kiểm tra va chạm của viên đạn với địch (trong util.cpp)
		{
			b->health = 0;//bullet
			e->health = 0;//enemy

			return 1;//trả về 1 nếu trúng mục tiêu true
		}
	}

	return 0;//false
}

static void spawnEnemies(void)
{
	Entity *enemy;

	if (--enemySpawnTimer <= 0)//thêm kẻ thù khi giảm xuống dưới 1
	{
		//nếu hết timer thì tạo enemy mới
		enemy = (Entity*)malloc(sizeof(Entity));
		memset(enemy, 0, sizeof(Entity));
		//reset enemy
		stage.fighterTail->next = enemy;
		stage.fighterTail = enemy;

		enemy->x = SCREEN_WIDTH;
		enemy->y = rand() % SCREEN_HEIGHT; //đặt tọa độ của kẻ thù là ngẫu nhiên theo screen height
		enemy->texture = enemyTexture;
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

		//tốc độ di chuyển ngẫu nhiên từ -2 -> -5
		enemy->dx = -(2 + (rand() % 4));

		enemy->side = SIDE_ALIEN; //side địch
		enemy->health = 1;

		//thời gian spawn tiếp theo từ 30-90 frame
		enemySpawnTimer = 30 + (rand() % 60);
	}
}

static void draw(void)
{
	drawFighters();

	drawBullets();
}

static void drawFighters(void)
{
	Entity *e;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		blit(e->texture, e->x, e->y);
	}
}

static void drawBullets(void)
{
	Entity *b;

	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		blit(b->texture, b->x, b->y);
	}
}
