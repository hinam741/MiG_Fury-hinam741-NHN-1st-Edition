 //Khởi tạo logic trò chơi
#include "common.h"

#include "Graphics\draw.h"
#include "sound.h"
#include "stage.h"
#include "text.h"
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
static void drawBackground(void);
static void initStarfield(void);
static void drawStarfield(void);
static void doBackground(void);
static void doStarfield(void);
static void drawExplosions(void);
static void doExplosions(void);
static void addExplosions(int x, int y, int num);
static void addDebris(Entity *e);
static void doDebris(void);
static void drawDebris(void);
static void drawHud(void);
static void doPointsPods(void);
static void drawPointsPods(void);
static void addPointsPod(int x, int y);

static Entity      *player;
static SDL_Texture *bulletTexture;
static SDL_Texture *enemyTexture;
static SDL_Texture *alienBulletTexture;
static SDL_Texture *playerTexture;
static SDL_Texture *background;
static SDL_Texture *explosionTexture;
static SDL_Texture *pointsTexture;
static int          enemySpawnTimer;
static int          stageResetTimer;
static int          backgroundX;
static Star         stars[MAX_STARS];
static int          highscore;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;
	stage.explosionTail = &stage.explosionHead;
	stage.debrisTail = &stage.debrisHead;

	bulletTexture = loadTexture("gfx/playerBullet.png");
	enemyTexture = loadTexture("gfx/b52_enemy-110x110.png");
	alienBulletTexture = loadTexture("gfx/bossBullet-80x88.png");
	playerTexture = loadTexture("gfx/mig21_player-90x90.png");
	background = loadTexture("gfx/city_background.jpg");
	explosionTexture = loadTexture("gfx/explosion.png");
	pointsTexture = loadTexture("gfx/points.png");

	loadMusic("music/Air Attack HD - White Storm Dam Music - 1.5x.mp3");

	playMusic(1);

	resetStage();
}

static void resetStage(void)
{
	Entity *e;//duyệt con trỏ e ở ds thực thể
	Explosion *ex;
	Debris    *d;

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

	while (stage.explosionHead.next)
	{
		ex = stage.explosionHead.next;
		stage.explosionHead.next = ex->next;
		free(ex);
	}

	while (stage.debrisHead.next)
	{
		d = stage.debrisHead.next;
		stage.debrisHead.next = d->next;
		free(d);
	}

	while (stage.pointsHead.next)
	{
		e = stage.pointsHead.next;
		stage.pointsHead.next = e->next;
		free(e);
	}

	memset(&stage, 0, sizeof(Stage));//reset toàn bộ dữ liệu trong stage
	//khôi phục trạng thái ban đầu
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;
	stage.explosionTail = &stage.explosionHead;
	stage.debrisTail = &stage.debrisHead;
	stage.pointsTail = &stage.pointsHead;

	stage.score = 0;//tính điểm

	initPlayer();

	initStarfield(); //khởi tạo cánh đồng sao

	enemySpawnTimer = 0;

	stageResetTimer = FPS * 3;//đặt lại bộ đếm reset màn chơi, trong khoảng 3s thêm hiệu ứng
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

//khởi tạo cánh đồng sao
static void initStarfield(void)
{
	int i;

	for (i = 0; i < MAX_STARS; i++)
	{
		stars[i].x = rand() % SCREEN_WIDTH;
		stars[i].y = rand() % SCREEN_HEIGHT;
		stars[i].speed = 1 + rand() % 8;
	}
}

//logic của trò chơi
static void logic(void)
{
    doBackground();

	doStarfield();

	doPlayer(); //liên kết với con trỏ logic của app.delegate

	doEnemies();

	doFighters();

	doBullets();

	doExplosions();

	doDebris();

	doPointsPods();

	spawnEnemies();

	clipPlayer();

	if (player == NULL && --stageResetTimer <= 0)//kiểm tra người chơi có bị giết ko
	{
		resetStage();
	}
}

static void doBackground(void)
{
	if (--backgroundX < -SCREEN_WIDTH)
	{
		backgroundX = 0;
	}
}

static void doStarfield(void)
{
	int i;

	for (i = 0; i < MAX_STARS; i++)
	{
		stars[i].x -= stars[i].speed; //tạo hiệu ứng trôi ngang

		if (stars[i].x < 0)
		{
			stars[i].x = SCREEN_WIDTH + stars[i].x;//nếu ngôi sao ra khỏi màn trái thì đưa nó về lại màn phải; đặt thêm tọa độ của star để stars k bị xuất hiện cùng 1 chỗ
		}
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
			playSound(SND_PLAYER_FIRE, CH_PLAYER);//thêm âm thanh

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

			playSound(SND_ALIEN_FIRE, CH_ALIEN_FIRE);//thêm âm thanh
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

			addExplosions(e->x, e->y, 32);

			addDebris(e);

			if (e == player)
			{
				playSound(SND_PLAYER_DIE, CH_PLAYER);//thêm âm thanh
			}
			else
			{
				addPointsPod(e->x + e->w / 2, e->y + e->h / 2);

				playSound(SND_ALIEN_DIE, CH_ANY);//thêm âm thanh, phát nhiều âm thanh nổ cùng lúc, chọn kênh rảnh bất kỳ
			}

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

		//khi enemy xuất hiện thì thêm âm thanh
		//playSound(SND_ALIEN_APPEAR, CH_ALIEN);

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

static void doExplosions(void)
{
	Explosion *e, *prev;

	prev = &stage.explosionHead;

	for (e = stage.explosionHead.next; e != NULL; e = e->next)
	{
		e->x += e->dx;
		e->y += e->dy;

		if (--e->a <= 0)//giảm a của e (giảm tần suất vụ nổ)
		{
			if (e == stage.explosionTail)
			{
				stage.explosionTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

static void doDebris(void)
{
	Debris *d, *prev;

	prev = &stage.debrisHead;

	for (d = stage.debrisHead.next; d != NULL; d = d->next)
	{
		d->x += d->dx;
		d->y += d->dy;

		d->dy += 0.5;//tăng vận tốc rơi

		if (--d->life <= 0)
		{
			if (d == stage.debrisTail)
			{
				stage.debrisTail = prev;
			}

			prev->next = d->next;
			free(d);
			d = prev;
		}

		prev = d;
	}
}

static void doPointsPods(void)
{
	Entity *e, *prev;

	prev = &stage.pointsHead;

	for (e = stage.pointsHead.next; e != NULL; e = e->next)
	{
		if (e->x < 0)//làm pod nảy lên, nếu x ra khỏi màn hình
		{
			e->x = 0;
			e->dx = -e->dx;
		}

		if (e->x + e->w > SCREEN_WIDTH)
		{
			e->x = SCREEN_WIDTH - e->w;
			e->dx = -e->dx;
		}

		if (e->y < 0)
		{
			e->y = 0;
			e->dy = -e->dy;
		}

		if (e->y + e->h > SCREEN_HEIGHT)
		{
			e->y = SCREEN_HEIGHT - e->h;
			e->dy = -e->dy;
		}

		e->x += e->dx;
		e->y += e->dy;

		if (player != NULL && collision(e->x, e->y, e->w, e->h, player->x, player->y, player->w, player->h))//nếu va chạm với player
		{
			e->health = 0;

			stage.score++;

			highscore = MAX(stage.score, highscore);

			playSound(SND_POINTS, CH_POINTS);
		}

		if (--e->health <= 0)
		{
			if (e == stage.pointsTail)
			{
				stage.pointsTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

static void addExplosions(int x, int y, int num)
{
	Explosion *e;
	int        i;

	for (i = 0; i < num; i++)
	{
		e = (Explosion*)malloc(sizeof(Explosion));//cấp phát bộ nhớ
		memset(e, 0, sizeof(Explosion));//gán các byte trong struct = 0 đảm bảo ko có giá trị rác
		stage.explosionTail->next = e;
		stage.explosionTail = e;

		e->x = x + (rand() % 32) - (rand() % 32);//chọn vị trí xung quanh điểm x,y (dao động trong 31px)
		e->y = y + (rand() % 32) - (rand() % 32);
		e->dx = (rand() % 10) - (rand() % 10);//lấy vận tốc ngẫu nhiên trong đoạn -9;9
		e->dy = (rand() % 10) - (rand() % 10);

		e->dx /= 10;
		e->dy /= 10;

		switch (rand() % 4)//chọn màu ngẫu nhiên
		{
			case 0://đỏ, cháy mạnh
				e->r = 255;
				break;

			case 1://cam, cháy nhẹ hơn
				e->r = 255;
				e->g = 128;
				break;

			case 2://vàng, sáng nổ
				e->r = 255;
				e->g = 255;
				break;

			default://sáng trắng
				e->r = 255;
				e->g = 255;
				e->b = 255;
				break;
		}

		e->a = rand() % FPS * 3;//giá trị tuổi thọ của vụ nổ
	}
}

static void addDebris(Entity *e)//phá vỡ máy bay thành nhiều mảnh
{
	Debris *d;
	int     x, y, w, h;//chia hình thành 4 phần

	w = e->w / 2;
	h = e->h / 2;

	for (y = 0; y <= h; y += h)
	{
		for (x = 0; x <= w; x += w)
		{
			d = (Debris*)malloc(sizeof(Debris));
			memset(d, 0, sizeof(Debris));
			stage.debrisTail->next = d;
			stage.debrisTail = d;

			d->x = e->x + e->w / 2;//vị trí ban đầu là tâm của thực thể (x là góc bên trái cùng + w/2)
			d->y = e->y + e->h / 2;
			d->dx = (rand() % 5) - (rand() % 5);// v ngẫu nhiên từ -4;4
			d->dy = -(5 + (rand() % 12));// v dọc từ -5;-16
			d->life = FPS * 2;
			d->texture = e->texture;

			d->rect.x = x;//hiển thị mảnh vỡ theo tọa độ
			d->rect.y = y;
			d->rect.w = w;
			d->rect.h = h;
		}
	}
}

static void addPointsPod(int x, int y)
{
	Entity *e;

	e = (Entity*)malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.pointsTail->next = e;
	stage.pointsTail = e;

	e->x = x;
	e->y = y;
	e->dx = -(rand() % 5);
	e->dy = (rand() % 5) - (rand() % 5);
	e->health = FPS * 10;//tồn tại 10s trước khi biến mất
	e->texture = pointsTexture;

	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);

	e->x -= e->w / 2;
	e->y -= e->h / 2;
}

static void draw(void)
{
	drawBackground();

	drawStarfield();

	drawPointsPods();

	drawFighters();

	drawDebris();

	drawExplosions();

	drawBullets();

	drawHud();
}

static void drawPointsPods(void)
{
	Entity *e;

	for (e = stage.pointsHead.next; e != NULL; e = e->next)
	{
		blit(e->texture, e->x, e->y);
	}
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

static void drawStarfield(void)
{
	int i, c;//color

	for (i = 0; i < MAX_STARS; i++)
	{
		c = 32 * stars[i].speed;//màu càng sáng thì sao bay càng nhanh

		SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);//c,c,c tạo ra màu xám; 255 là đậm đặc

		SDL_RenderDrawLine(app.renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);//điểm kết thúc kéo dài thêm 3px, giữ nguyên chiều cao
	}
}

static void drawBackground(void)
{
	SDL_Rect dest;//đích vẽ
	int      x;

	for (x = backgroundX; x < SCREEN_WIDTH; x += SCREEN_WIDTH)//định nghĩa backgroundX ở đầu file
	{
		dest.x = x;
		dest.y = 0;
		dest.w = SCREEN_WIDTH;//kéo nền ra
		dest.h = SCREEN_HEIGHT;

		SDL_RenderCopy(app.renderer, background, NULL, &dest);// null vẽ toàn bộ k cắt, dest vẽ lên toàn bộ khu vực được định nghĩa
	}
}

static void drawDebris(void)
{
	Debris *d;

	for (d = stage.debrisHead.next; d != NULL; d = d->next)
	{
		blitRect(d->texture, &d->rect, d->x, d->y);
	}
}

static void drawExplosions(void)
{
	Explosion *e;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);//hàm hòa trộn cộng, làm sáng lên các lệnh vẽ cơ bản, vẽ trực tiếp bằng màu
	SDL_SetTextureBlendMode(explosionTexture, SDL_BLENDMODE_ADD);//trộn màu với các texture, vẽ bằng texture

	for (e = stage.explosionHead.next; e != NULL; e = e->next)
	{
		SDL_SetTextureColorMod(explosionTexture, e->r, e->g, e->b);//đặt màu explosionTexture là màu cam
		SDL_SetTextureAlphaMod(explosionTexture, e->a);//điều chỉnh độ trong suốt cho mờ dần theo thời gian

		blit(explosionTexture, e->x, e->y);
	}

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

static void drawHud(void)
{
	drawText(10, 10, 255, 255, 255, "SCORE: %03d", stage.score);//vẽ điểm hiện tại màu trắng, bên trái màn hình (x,y,r,g,b,định dạng điểm số 3 chữ số

	if (stage.score > 0 && stage.score == highscore)
	{
		drawText(1020, 10, 0, 255, 0, "HIGHSCORE: %03d", highscore);//vẽ điểm highscore, màu xanh lá cây ; %03 giá trị thay thế phải là sô nguyên (%), 0 là các số trước số cần tìm nếu độ dài ko đủ bằng 3 kí tự, độ dài là 3 kí tự
	}
	else
	{
		drawText(1020, 10, 255, 255, 255, "HIGHSCORE: %03d", highscore);//nếu ko phải highscore thì vẽ màu trắng
	}
}
