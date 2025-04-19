#ifndef DRAW_H
#define DRAW_H

void prepareScene(void);
void presentScene(void);
SDL_Texture *loadTexture(char *filename);
void         blit(SDL_Texture *texture, int x, int y);

#endif // DRAW_H
