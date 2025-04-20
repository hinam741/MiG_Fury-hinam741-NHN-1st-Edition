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
static int  bulletHitFighter(Entity *b);//khi bullet hit địch
static void doEnemies(void);
static void fireAlienBullet(Entity *e);
static void clipPlayer(void);
static void resetStage(void);

static Entity      *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static SDL_Texture *alienBulletTexture;
static SDL_Texture *playerTexture;
static int          enemySpawnTimer;
static int          stageResetTimer;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;

	bulletTexture = loadTexture("gfx/playerBullet.png");
	enemyTexture = loadTexture("gfx/b52_enemy-200x200.png");
	alienBulletTexture = loadTexture("gfx/bossBullet-80x88.png");
	playerTexture = loadTexture("gfx/mig21_player-150x150.png");

	resetStage();
}

static void resetStage(void)
{
	Entity *e;//duyệt con trỏ e ở ds thực thể

	while (stage.fighterHead.next)//xóa máy bay enemy
	{
		e = stage.fighterHead.next;//duyệt từ phần tử đầu tiên sau fighterHead
		stage.fighterHead.next = e->next;
		free(e);
	}

	while (stage.bulletHead.next)//xóa đạn
	{
		e = stage.bulletHead.next;
		stage.bulletHead.next = e->next;
		free(e);
	}

	memset(&stage, 0, sizeof(Stage));//reset toàn bộ dữ liệu trong stage
	//khôi phục trạng thái ban đầu
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;

	initPlayer();

	enemySpawnTimer = 0;

	stageResetTimer = FPS * 2;//đặt lại bộ đếm reset màn chơi, trong khoảng 2s thêm hiệu ứng
}

static void initPlayer()
{
	player = (Entity*)malloc(sizeof(Entity));//ép kiểu
	memset(player, 0, sizeof(Entity));
	stage.fighterTail->next = player;
	stage.fighterTail = player;

	player->health = 1;
	player->x = 100;
	player->y = 100;
	player->texture = playerTexture;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);

	player->side = SIDE_PLAYER;
}


//logic của trò chơi
static void logic(void)
{
	doPlayer(); //liên kết với con trỏ logic của app.delegate

	doEnemies();

	doFighters();

	doBullets();

	spawnEnemies();

	clipPlayer();

	if (player == NULL && --stageResetTimer <= 0)//kiểm tra người chơi có bị giết ko
	{
		resetStage();
	}
}

static void doPlayer(void)
{
	if (player != NULL)//sẽ ko có gì dc thực thi nếu là NULL
	{
		player->dx = player->dy = 0;

		if (player->reload > 0)//nếu reload >0 thì giảm lại
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

		if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload <= 0)
		{
			fireBullet();
		}
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

static void doEnemies(void)
{
	Entity *e;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)//duyệt xem máy bay có phải người chơi hay ko; mỗi vòng lặp e trỏ đến next
	{
		if (e != player && player != NULL && --e->reload <= 0)//bỏ qua người chơi; đảm bảo người chơi != null; giảm reload (đếm ngược giữa các lần bắn) kiểm tra đã đến lúc bắn chưa
		{
			fireAlienBullet(e);//nếu mọi thứ đúng thì gọi hàm
		}
	}
}

static void fireAlienBullet(Entity *e)//con tror trỏ tới enemy
{
	Entity *bullet;//con trỏ trỏ tới viên đạn mới tạo

	bullet = (Entity*)malloc(sizeof(Entity));//cấp phát bộ nhớ cho viên đạn
	memset(bullet, 0, sizeof(Entity));
	stage.bulletTail->next = bullet; //nối đạn mới vào đuôi ds
	stage.bulletTail = bullet; //cập nhật con trỏ bulletTail trỏ đến viên đạn mới

	bullet->x = e->x;//gán vị trí ban đầu của viên đạn với enemy
	bullet->y = e->y;
	bullet->health = 1;
	bullet->texture = alienBulletTexture;//gán texture cho viên đạn
	bullet->side = SIDE_ALIEN;//gán phe địch; viên đạn chỉ trúng player, ko trúng enemy
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

	bullet->x += (e->w / 2) - (bullet->w / 2);//căn giữa
	bullet->y += (e->h / 2) - (bullet->h / 2);

	calcSlope(player->x + (player->w / 2), player->y + (player->h / 2), e->x, e->y, &bullet->dx, &bullet->dy);//tính hướng bay; player->x con trỏ tới tọa độ x (thuộc tính) của player

	bullet->dx *= ALIEN_BULLET_SPEED;//s=vt
	bullet->dy *= ALIEN_BULLET_SPEED;

	e->reload = (rand() % FPS * 2);
}

//hàm xử lý chuyển động và xóa fighters nếu ra khỏi màn hình bên trái
static void doFighters(void)
{
	Entity *e, *prev;

	prev = &stage.fighterHead;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)//duyệt toàn bộ fighter
	{
		e->x += e->dx;//cập nhật vị trí
		e->y += e->dy;

		if (e != player && e->x < -e->w)//nếu ko phải player hoặc ra khỏi màn hình
		{
			e->health = 0;
		}

		if (e->health == 0)//nếu e chết thì xóa
		{
			if (e == player)
			{
				player = NULL;
			}

			if (e == stage.fighterTail)//nếu kẻ thù ra khỏi màn hình
			{
				stage.fighterTail = prev;
			}

			//nếu đây là phần tử cuối cùng, cập nhật tail
			prev->next = e->next;
			free(e);
			e = prev;//xóa node e và cập nhật ds
		}

		prev = e;//cập nhật prev cho vòng tiếp theo
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

		if (bulletHitFighter(b) || b->x < -b->w || b->y < -b->h || b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT)//nếu đạn ra khỏi màn hình (từ mọi phía) hoặc đạn hit fighter thì giải phóng b
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
	Entity *enemy;//con trỏ enemy trỏ tới Entity(thực thể)

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

		//đặt thời gian cho player đủ tiêu diệt kẻ thù
		enemy->reload = FPS * (1 + (rand() % 3));

		//thời gian spawn tiếp theo từ 30-90 frame
		enemySpawnTimer = 30 + (rand() % 60);
	}
}

//hàm ngăn ko cho player ra ngoài màn hình
static void clipPlayer(void)
{
	if (player != NULL)
	{
		if (player->x < 0)
		{
			player->x = 0;
		}

		if (player->y < 0)
		{
			player->y = 0;
		}

		if (player->x > SCREEN_WIDTH / 2)
		{
			player->x = SCREEN_WIDTH / 2;
		}

		if (player->y > SCREEN_HEIGHT - player->h)
		{
			player->y = SCREEN_HEIGHT - player->h;
		}
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
