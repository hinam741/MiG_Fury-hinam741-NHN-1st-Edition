#ifndef SOUND_H
#define SOUND_H

void initSounds(void);
void loadMusic(char *filename);
void playMusic(int loop);
void playSound(int id, int channel);

#endif // SOUND_H
