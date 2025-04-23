#include "common.h"

#include "draw.h"
#include "text.h"

#define GLYPH_HEIGHT 28//định nghĩa kích thước ký tự
#define GLYPH_WIDTH  18

static SDL_Texture *fontTexture;
static char         drawTextBuffer[MAX_LINE_LENGTH];

void initFonts(void)
{
	fontTexture = loadTexture("gfx/font.png");
}

void drawText(int x, int y, int r, int g, int b, char *format, ...)//định dạng format dùng varargs
{
	int      i, len, c;
	SDL_Rect rect;//chỉ định vùng kết cấu càn dùng
	va_list  args;//khai báo viến kiểu va_list

	memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));//xóa drawTextBuffer

	va_start(args, format);//định dạng varargs
	vsprintf(drawTextBuffer, format, args);//định dạng xong đưa kết quả vào drawTextBuffer
	va_end(args);

	len = strlen(drawTextBuffer);//duyệt độ dài chuỗi

	rect.w = GLYPH_WIDTH;//định nghĩa khung chữ với SDL_Rect
	rect.h = GLYPH_HEIGHT;
	rect.y = 0;

	SDL_SetTextureColorMod(fontTexture, r, g, b);

	for (i = 0; i < len; i++)
	{
		c = drawTextBuffer[i];//duyệt từng ký tự

		if (c >= ' ' && c <= 'Z')//xử lý nằm trong khoảng space -> z (mã SDL:90) - chỉ hỗ trợ 1 phần ascii
		{
			rect.x = (c - ' ') * GLYPH_WIDTH;//tính vị trí texture

			blitRect(fontTexture, &rect, x, y);//vẽ ký tự lên màn hình

			x += GLYPH_WIDTH;//chuẩn bị tiếp theo
		}
	}
}
