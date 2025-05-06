#include <SDL_image.h>

#include "common.h"

#include "draw.h"

extern App app;

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);//giữ nội dung đã vẽ lên màn hình
}

static SDL_Texture *getTexture(char *name)//kiểm tra texture đã load được chưa
{
	Texture *t;

	for (t = app.textureHead.next; t != NULL; t = t->next)
	{
		if (strcmp(t->name, name) == 0)//hàm strcmp so sánh 2 chuỗi; nếu texture có tên trùng khóp
		{
			return t->texture;
		}
	}

	return NULL;
}

static void addTextureToCache(char *name, SDL_Texture *sdlTexture)
{
	Texture *texture;

	texture = (Texture*)malloc(sizeof(Texture));
	memset(texture, 0, sizeof(Texture));
	app.textureTail->next = texture;
	app.textureTail = texture;

	STRNCPY(texture->name, name, MAX_NAME_LENGTH);// macro được định nghĩa
	texture->texture = sdlTexture;
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	texture = getTexture(filename);

	if (texture == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
		texture = IMG_LoadTexture(app.renderer, filename);
		addTextureToCache(filename, texture);//lưu texture vào dslk
	}

	return texture;
}

void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;//destination vẽ

	dest.x = x;//vị trí vẽ
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);//lấy toàn bộ kích thước hình ảnh

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);//vẽ toàn bộ nên đặt src = NULL
}

//cho phép vẽ phần nhỏ từ texture(mảnh vỡ,...)
void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)//truyền vào con trỏ src tới SDL_Rect vùng cần cắt từ texture gốc
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = src->w;
	dest.h = src->h;

	SDL_RenderCopy(app.renderer, texture, src, &dest);//chỉ vẽ kích thước nhỏ của texture được chỉ định bới src
}
