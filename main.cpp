#include "common.h"

#include "Graphics\draw.h"
#include "highscores.h"
#include "Core\init.h"
#include "Core\input.h"
#include "main.h"
#include "title.h"

#include "SDL.h"

App   app;//biến toàn cục chưa trạng thái chung
Highscores highscores;
Stage stage;//biến toàn cục chứa thực thể, logic

//khai báo hàm giới hạn tốc độ khung hình
static void capFrameRate(long *then, float *remainder);

int main(int argc, char *argv[])
{
	//đo thời gian giữa các frame
	long  then;//thời điểm bắt đầu
	float remainder;//dư frame

	//đặt giá trị của app thành 0
	memset(&app, 0, sizeof(App));
	app.textureTail = &app.textureHead;

	initSDL();

	atexit(cleanup);//gọi hàm cleanup sau khi kết thúc

	initGame();

	initTitle();

	then = SDL_GetTicks();//hàm lấy thời gian

	remainder = 0;//phần dư giữa các frame

	while (1)
	{
		prepareScene();

		doInput();//xử lý sự kiện bàn phím...

		SDL_Event event;

		app.delegate.logic();//logic game

		app.delegate.draw();//vẽ

		presentScene();//renderPresent

		capFrameRate(&then, &remainder);//gọi hàm giữ fps
	}

	return 0;
}

static void capFrameRate(long *then, float *remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder; //thời gian giữa 2 frame nếu muốn đạt 60 fps 16ms = 1000ms/60fps + thêm remainder phần dư từ frame trước

	*remainder -= (int)*remainder; //giữ phần thập phân dư để cộng dồn vào frame sau

	frameTime = SDL_GetTicks() - *then;//hàm thời gian

	wait -= frameTime;

	//đảm bảo có thời gian nghỉ
	if (wait < 1)
	{
		wait = 1;
	}

	//tạm dừng để giữ nhịp fps
	SDL_Delay(wait);

	//cộng phần dư để bù lại sai số
	*remainder += 0.667;

	//thời gian bắt đầu của frame mới
	*then = SDL_GetTicks();
}
