#include "common.h"

#include "background.h"
#include "draw.h"

extern App app;

static int          backgroundX;
static Star         stars[MAX_STARS];
static SDL_Texture *background;

void initBackground(void)
{
	background = loadTexture("gfx/city_background_3.jpg");

	backgroundX = 0;
}

//khởi tạo cánh đồng sao
void initStarfield(void)
{
	int i;

	for (i = 0; i < MAX_STARS; i++)
	{
		stars[i].x = rand() % SCREEN_WIDTH;
		stars[i].y = rand() % SCREEN_HEIGHT;
		stars[i].speed = 1 + rand() % 8;//đặt random speed từ 1-8
	}
}

void doBackground(void)
{
	if (--backgroundX < -SCREEN_WIDTH)
	{
		backgroundX = 0;
	}
}

void doStarfield(void)
{
	int i;

	for (i = 0; i < MAX_STARS; i++)
	{
		stars[i].x -= stars[i].speed;//tạo hiệu ứng trôi ngang

		if (stars[i].x < 0)
		{
			stars[i].x = SCREEN_WIDTH + stars[i].x;//nếu ngôi sao ra khỏi màn trái thì đưa nó về lại màn phải; đặt thêm tọa độ của star để stars k bị xuất hiện cùng 1 chỗ
		}
	}
}

void drawStarfield(void)
{
	int i, c;//color

	for (i = 0; i < MAX_STARS; i++)
	{
		c = 32 * stars[i].speed;//màu càng sáng thì sao bay càng nhanh

		SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);//c,c,c tạo ra màu xám; 255 là đậm đặc

		SDL_RenderDrawLine(app.renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);//điểm kết thúc kéo dài thêm 3px, giữ nguyên chiều cao
	}
}

void drawBackground(void)
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
