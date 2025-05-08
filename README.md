
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

To install the game, please use the Code::Blocks IDE.
Make sure all required SDL libraries are properly installed.

- First, click the `Code` button and select **Download ZIP**.

- Extract the `.zip` file.

- Open `MiGFury_1stEdition.cbp` with Code::Blocks IDE.

- Click **Build and Run** to play the game.

You can also install it using the `git clone` command.
## Acknowledgements

- Developed using C/C++ with SDL2, SDL_mixer, SDL_image, and SDL_ttf.

- Supports 8 simultaneous audio channels.

- Implements seamless, boundary-less 2D graphics with infinite looping.

- Applies advanced programming concepts: linked lists, pointers, structs, classes, etc.
## Game Mechanics and Features

### Scoring
- PodPoints (1–2 points & lasts for 10s) drop when an enemy is shot.
- Points are awarded only when collected, not simply by shooting.

### Win / Lose Conditions
- No specific win state; the goal is to achieve a high score.
- If your score enters the top 8, it's marked as **A New Record**.
- The game ends when the player is hit by an enemy bullet.

### Features
- **Explosion Effects**: Bright-colored explosion with directional split visuals.
- **Sound**: Audio feedback for actions like shooting and explosions.
- **Starfield**: Continuous scrolling starfield for a dynamic background.
- **Vector Normalization**: Ensures accurate targeting based on last known position.
## How to play

* Controls:
Press Left Ctrl to start the game and to shoot bullets. Use the arrow keys to move the plane. During the game, shoot enemy planes and avoid their bullets.

* Scoring:
When you shoot down an enemy, it may drop random PodPoints. Move your plane to collect them. Points are only awarded when you collect PodPoints, not when you shoot enemies.

* High Score System:
There is no win condition — the goal is to get a high score. If your score is higher than one of the top 8 in the Highscores list, it will be marked as `A New Record`. You can then enter your name and press Enter to save it.

* Game Over:
The game ends if your plane gets hit by an enemy bullet.

## Credits

There are several source that help me make the game easier
 - [SDL2_Wiki](https://wiki.libsdl.org/SDL2/FrontPage)
 - [Lazy Foo' Production](https://lazyfoo.net/tutorials/SDL/index.php)
 - [Youtube and Udemy's courses instructions](https://www.youtube.com/)
 - Other various online resources


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

- `Title screen`

![Image](https://github.com/user-attachments/assets/707f257e-fa56-4f8f-a2d7-60f6c290b29f)

- `In-game` – Here's what the game's interface looks like

![Image](https://github.com/user-attachments/assets/f793e937-163c-4d67-b2ae-fff6aa83dc2b)

- `Effect`– This is the explosion effect when your bullet hits an enemy

![Image](https://github.com/user-attachments/assets/b3e6e3b2-52eb-46a8-aa3b-7156d812766c)

- `Record`– When you're defeated, the game ends; but if you set a new record, you'll be prompted to enter your name here

![Image](https://github.com/user-attachments/assets/3a50e30e-9dad-4f88-81e9-ee36e5183e58)

- `Highscore table`– Keep enjoying the game and aim for new achievements!

![Image](https://github.com/user-attachments/assets/644d82e7-a931-4df9-afff-03d97ba926c7)
## Project Structure

The project consists of 23 `.cpp` and `.h` files, organized in the `src` directory:

### `src/Core` – Core Logic

- `background` – Background initialization
- `highscores` – Scoreboard logic
- `init` – SDL and game setup
- `input` – Input event handling
- `sound` – Audio functionality
- `stage` – Game logic (player, alien, bullets)
- `structs` – Essential data structures
- `title` – Title screen rendering

### `src/Graphics` – Rendering

- `draw` – Scene rendering functions
- `text` – Font and text drawing

### `src/Physics` – Game Physics

- `util` – Collision detection, vector math, interpolation

### Other folders

- `common` – Third-party libraries
- `defs` – Game-wide constants and enums
- `main` – Main loop and frame rate limiter
## Final Words

Thank you for checking out **MiG Fury**!  
I truly appreciate your time and interest.  
I hope you enjoy playing and create unforgettable moments with this game.

**Let the skies be yours — good luck, pilot!**
