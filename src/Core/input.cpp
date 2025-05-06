#include "common.h"

#include "input.h"

extern App app;

//hàm nhả phím
static void doKeyUp(SDL_KeyboardEvent *event)//static void: dùng nội bộ trong file này
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)//đảm bảo chỉ xử lý khi phím nhấn lần đầu; tránh tràn mảng
	{
		app.keyboard[event->keysym.scancode] = 0;// ghi nhận phím được nhả ra; 0 = ko nhấn
	}
}

//hàm ấn phím
static void doKeyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 1;
	}
}

void doInput(void)
{
	SDL_Event event;

	memset(app.inputText, '\0', MAX_LINE_LENGTH);

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);//thoát toàn bộ ctrinh
				break;

			case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;

			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;

            case SDL_TEXTINPUT://nhập chữ
				STRNCPY(app.inputText, event.text.text, MAX_LINE_LENGTH);//copy và giữ độ dài
				break;

			default:
				break;
		}
	}
}
