#include "common.h"

#include "background.h"
#include "highscores.h"
#include "stage.h"
#include "text.h"

extern App        app;
extern Highscores highscores;

static void logic(void);
static void draw(void);

static void drawHighscores(void);
static void highscoreSort(Highscore *arr, int count);

void initHighscoreTable(void)
{
	int i;

	memset(&highscores, 0, sizeof(Highscores));

	for (i = 0; i < NUM_HIGHSCORES; i++)
	{
		highscores.highscore[i].score = NUM_HIGHSCORES - i;
	}
}

void initHighscores(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);//xóa trạng thái phím ngăn nhảy trò chơi
}

static void logic(void)
{
	doBackground();

	doStarfield();

	if (app.keyboard[SDL_SCANCODE_LCTRL])
	{
		initStage();
	}
}

static void draw(void)
{
	drawBackground();

	drawStarfield();

	drawHighscores();
}

static void drawHighscores(void)
{
	int i, y;

	y = 150;

	drawText(425, 70, 255, 255, 255, "HIGHSCORES");

	for (i = 0; i < NUM_HIGHSCORES; i++)
	{
		if (highscores.highscore[i].recent)
		{
			drawText(425, y, 255, 255, 0, "#%d ............. %03d", (i + 1), highscores.highscore[i].score);
		}
		else
		{
			drawText(425, y, 255, 255, 255, "#%d ............. %03d", (i + 1), highscores.highscore[i].score);
		}

		y += 50;
	}

	drawText(425, 600, 255, 255, 255, "PRESS FIRE TO PLAY!");
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

	for (i = 0; i < NUM_HIGHSCORES; i++)
	{
		newHighscores[i] = highscores.highscore[i];//duyệt qua bảng điểm cũ, lưu vào bảng mới
		newHighscores[i].recent = 0;
	}

	newHighscores[NUM_HIGHSCORES].score = score;//chèn điểm mới vào vị trí cuối
	newHighscores[NUM_HIGHSCORES].recent = 1;//đánh màu

	highscoreSort(newHighscores, NUM_HIGHSCORES + 1);

	for (i = 0; i < NUM_HIGHSCORES; i++)
	{
		highscores.highscore[i] = newHighscores[i];
	}
}
