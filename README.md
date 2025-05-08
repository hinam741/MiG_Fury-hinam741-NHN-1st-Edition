
# MiG Fury v1.0.0
Final Project – Advanced Programming Course (INT2215 12 – G2)

Inspired by the "Dien Bien Phu in the Air" campaign, the main character takes on the role of a pilot flying a MiG-21, tasked with defending the skies against the U.S. Air Force.

Additionally, the game draws inspiration from [CounterAttack: Uprising](https://store.steampowered.com/app/451600/CounterAttack_Uprising/), with simplified features and modified gameplay mechanics.


## Author

- [@hinam741](https://www.github.com/hinam741): Nguyễn Hải Nam (24022697) - K69I - IS4 - UET


## Official Logo
![Logo](https://github.com/user-attachments/assets/4aa0d368-d928-4083-a16b-bec667f63e5c)


## Official Gameplay Video
Click this link to watch the Official GamePlay Video of
[MiG Fury v1.0.0.](https://youtu.be/mQJ_bt-EXpQ)

## Installation

To install my game, please use the Code::Blocks IDE!
Make sure that all SDL libraries are properly installed.

```bash
1. First, click the "Code" button and select "Download ZIP".
2. Next, extract the .zip file.
3. Finally, open `MiGFury_1stEdition.cbp` with Code::Blocks IDE.
   To play the game, click the "Build and Run" button.
```

## Acknowledgements
* Developed using C/C++ with support from the SDL, SDL_mixer, SDL_image, and SDL_ttf libraries.

* Implements multi-channel audio with support for 8 simultaneous sound effect channels.

* Features flat, boundary-less graphics that loop infinitely within the gameplay area.

* Incorporates advanced programming concepts learned in C/C++, including linked lists, pointers, self-referential structures, structs, classes, and more.
## How to play

* Controls:
Press Left Ctrl to start the game and to shoot bullets. Use the arrow keys to move the plane. During the game, shoot enemy planes and avoid their bullets.

* Scoring:
When you shoot down an enemy, it may drop random PodPoints. Move your plane to collect them. Points are only awarded when you collect PodPoints, not when you shoot enemies.

* High Score System:
There is no win condition — the goal is to get a high score. If your score is higher than one of the top 8 in the Highscores list, it will be marked as "A New Record". You can then enter your name and press Enter to save it.

* Game Over:
The game ends if your plane gets hit by an enemy bullet.

## Credits

There are several source that help me make the game easier
 - [SDL2_Wiki](https://wiki.libsdl.org/SDL2/FrontPage)
 - [Lazy Foo' Production](https://lazyfoo.net/tutorials/SDL/index.php)
 - [Youtube and Udemy's courses instructions](https://www.youtube.com/)
 - Other sources


## Resources

All resources are saved in the gfx folder.

There are several sources that I used to find images and sounds for my game:

 - [Audio](https://www.youtube.com/playlist?list=PL7Ra2mJBhymKUGzbngs3rMRqFTb9EFOQG)
 - [Image](https://www.google.com/)
 - [Remove Background](https://www.remove.bg/)
 - [AI-based](https://chatgpt.com/)

Here are some of the images I used in my game:

- Player bullet
![Image](https://github.com/user-attachments/assets/95b73b6c-5cd7-4f0a-b1f7-f50e66eadf03)       

- Enemy bullet
![Image](https://github.com/user-attachments/assets/a2e5a86a-094c-42cb-8c29-d396bd66e959)

- PodPoint
![Image](https://github.com/user-attachments/assets/a80fff6f-cc5b-48f3-b2cd-1f9ee2eb96d0)

- Player [MiG-21] and Enemy [Boeing B-52 Stratofortress] (not yet resized)

![Image](https://github.com/user-attachments/assets/f3261175-aa0d-41f0-93fb-fbd8b028dda7)

![Image](https://github.com/user-attachments/assets/2f730c81-83c7-484e-a866-745305ac3161)

- Background
![Image](https://github.com/user-attachments/assets/884c8a42-ddc5-44de-8626-4905e13a89a0)

Additionally, I have also saved some other supplementary resources such as backgrounds, which you can freely change to your liking by modifying the line of code that loads the texture.



## Screenshots

Here are some screenshots from MiG Fury.

- Title screen
![Image](https://github.com/user-attachments/assets/707f257e-fa56-4f8f-a2d7-60f6c290b29f)

- In-game – Here's what the game's interface looks like
![Image](https://github.com/user-attachments/assets/f793e937-163c-4d67-b2ae-fff6aa83dc2b)

- Effect – This is the explosion effect when your bullet hits an enemy
![Image](https://github.com/user-attachments/assets/b3e6e3b2-52eb-46a8-aa3b-7156d812766c)

- Record – When you're defeated, the game ends; but if you set a new record, you'll be prompted to enter your name here
![Image](https://github.com/user-attachments/assets/17a8dbd4-8c3d-4492-902e-0286c9252ffa)

- Highscore table – Keep enjoying the game and aim for new achievements!

![Image](https://github.com/user-attachments/assets/644d82e7-a931-4df9-afff-03d97ba926c7)