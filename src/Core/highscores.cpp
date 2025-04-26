#include "common.h"

#include "background.h"
#include "highscores.h"
#include "stage.h"
#include "text.h"
#include "title.h"

extern App        app;
extern Highscores highscores;

static void logic(void);
static void draw(void);

static void drawHighscores(void);
static void highscoreSort(Highscore *arr, int count);
static void doNameInput(void);
static void drawNameInput(void);

static Highscore *newHighscore;
static int        cursorBlink;
static int        timeout;

void initHighscoreTable(void)
{
	int i;

	memset(&highscores, 0, sizeof(Highscores));

	for (i = 0; i < NUM_HIGHSCORES; i++)
	{
		highscores.highscore[i].score = NUM_HIGHSCORES - i;
		STRNCPY(highscores.highscore[i].name, "ANONYMOUS", MAX_SCORE_NAME_LENGTH);
	}

	newHighscore = NULL;

	cursorBlink = 0;
}

void initHighscores(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);//xóa trạng thái phím ngăn nhảy trò chơi

	timeout = FPS * 5;
}

static void logic(void)
{
	doBackground();

	doStarfield();

	if (newHighscore != NULL)
	{
		doNameInput();
	}
	else
	{
	    if (--timeout <= 0)
		{
			initTitle();
		}

		if (app.keyboard[SDL_SCANCODE_LCTRL])
		{
			initStage();
		}
	}

	if (++cursorBlink >= FPS)//hiện con trỏ tên nhấp nháy
	{
		cursorBlink = 0;
	}
}

static void doNameInput(void)
{
	int  i, n;
	char c;

	n = strlen(newHighscore->name);//lấy độ dài tên

	for (i = 0; i < strlen(app.inputText); i++)
	{
		c = toupper(app.inputText[i]);//chuyển thành in hoa

		if (n < MAX_SCORE_NAME_LENGTH - 1 && c >= ' ' && c <= 'Z')
		{
			newHighscore->name[n++] = c;//nếu ký tự hợp lệ thì thêm vào mảng tên
		}
	}

	if (n > 0 && app.keyboard[SDL_SCANCODE_BACKSPACE])//backspace
	{
		newHighscore->name[--n] = '\0';//xóa

		app.keyboard[SDL_SCANCODE_BACKSPACE] = 0;
	}

	if (app.keyboard[SDL_SCANCODE_RETURN])//enter
	{
		if (strlen(newHighscore->name) == 0)
		{
			STRNCPY(newHighscore->name, "ANONYMOUS", MAX_SCORE_NAME_LENGTH);// nếu ấn enter mà tên trống
		}

		newHighscore = NULL;//quay lại logic
	}
}

static void draw(void)
{
	drawBackground();

	drawStarfield();

	if (newHighscore != NULL)
	{
		drawNameInput();
	}
	else
	{
		drawHighscores();
		if (timeout % 40 < 20)
		{
			drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "PRESS LCTRL TO PLAY!");
		}
	}
}

static void drawNameInput(void)
{
	SDL_Rect r;

	drawText(SCREEN_WIDTH / 2, 70, 255, 255, 255, TEXT_CENTER, "CONGRATULATIONS, YOU'VE WON A NEW RECORD!");//màu chữ trắng

	drawText(SCREEN_WIDTH / 2, 120, 255, 255, 255, TEXT_CENTER, "ENTER YOUR NAME BELOW:");

	drawText(SCREEN_WIDTH / 2, 250, 128, 255, 128, TEXT_CENTER, newHighscore->name);//in tên màu xanh nhạt

	if (cursorBlink < FPS / 2)//con trỏ hiện 30/60 frame
	{
		r.x = ((SCREEN_WIDTH / 2) + (strlen(newHighscore->name) * GLYPH_WIDTH) / 2) + 5;
		r.y = 250;
		r.w = GLYPH_WIDTH;//kích thước con trỏ khớp với kích thước chữ
		r.h = GLYPH_HEIGHT;

		SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 255);//đặt màu xanh lá cây
		SDL_RenderFillRect(app.renderer, &r);//vẽ hình chữ nhật là con trỏ
	}

	drawText(SCREEN_WIDTH / 2, 625, 255, 255, 255, TEXT_CENTER, "PRESS ENTER WHEN FINISHED");
}

static void drawHighscores(void)
{
	int i, y, r, g, b;

	y = 150;

	drawText(SCREEN_WIDTH / 2, 70, 255, 255, 255, TEXT_CENTER, "HIGHSCORES");

	for (i = 0; i < NUM_HIGHSCORES; i++)
	{
		r = 255;
		g = 255;
		b = 255;

		if (highscores.highscore[i].recent)//nếu là điểm số mới, recent là 1 thì đổi màu xanh thành vàng b=0
		{
			b = 0;
		}

		drawText(SCREEN_WIDTH / 2, y, r, g, b, TEXT_CENTER, "#%d. %-15s ...... %03d", (i + 1), highscores.highscore[i].name, highscores.highscore[i].score);

		y += 50;
	}
}

static void highscoreSort(Highscore *arr, int count)
{
    int i, j;
    for (i = 0; i < count - 1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (arr[j].score > arr[i].score)
            {
                Highscore temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void addHighscore(int score)
{
	Highscore newHighscores[NUM_HIGHSCORES + 1];//mục mới tăng 1 để lưu thêm 1 đầu điểm mới
	int       i;

	memset(newHighscores, 0, sizeof(Highscore) * (NUM_HIGHSCORES + 1));

	for (i = 0; i < NUM_HIGHSCORES; i++)
	{
		newHighscores[i] = highscores.highscore[i];//duyệt qua bảng điểm cũ, lưu vào bảng mới
		newHighscores[i].recent = 0;
	}

	newHighscores[NUM_HIGHSCORES].score = score;//chèn điểm mới vào vị trí cuối
	newHighscores[NUM_HIGHSCORES].recent = 1;//đánh màu

	highscoreSort(newHighscores, NUM_HIGHSCORES + 1);

	newHighscore = NULL;

	for (i = 0; i < NUM_HIGHSCORES; i++)
	{
		highscores.highscore[i] = newHighscores[i];

		if (highscores.highscore[i].recent)//nếu mục điểm nào recent = 1 thì là điểm mới
		{
			newHighscore = &highscores.highscore[i];
		}
	}
}
