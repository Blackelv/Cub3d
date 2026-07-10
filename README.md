__This project has been created as part of the 42 curriculum by Kelemayi, Ffrattar__

# Cub3D

## Description
Cub3D is a programming project whose goal is the dynamic creation and navigation of a "realistic" 3D first-person maze "game" in C.The map of the game is provided by the user and validated by the Cub3D program, before being rendered using raytracing. It is developed using primarily user-created functions, with the exception of an imported MinilibX library and the standard C Math library. This project teaches file parsing and validation as well as raytracing and texture rendering concepts.

The Cub3D program must correctly parse a map scene passed to it as an initial argument and show the user a 3D scene that the user can then navigate.

The user should be able to navigate using the following commands:

// L / R arrows look left and right
// WASD key move player relative to view orientation
// ESC & [X] quits program cleanly
// [SPACEBAR] toggles minimap
// [+]/[-] keys grow and shrink minimap (FOV visible on max size)

***Note** Bonus features include a togglable mini-map and collisions. 

## Instructions

The program is designed to to be run on a linux system with a clang compiler and X11 windows manager. The user must also use the [minilibx 42 rendering library](https://github.com/42paris/minilibx-linux) which should be included in the project makefile, but can also be downloaded from the linked source and included in the main project directory.

Assuming you have all required dependencies, from the main project directory, to start the program for the first time run `make` and then you're good to go. See the following example usage.

### Example Usage

To launch, enter `./cub3D ./path/to/map/file/map.cub` where `map.cub` is a file containing map information structured like the below example:

```jsx
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

           1111111111111111111111111
           1000000000110000000000001
           1011000001110000000000001
           1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

If you map is valid (1 = walls, 0 = floor, N/E/S/W reflects player spawn point, all floor must be enclosed by walls), then you should see something like this:
<img width="1199" height="744" alt="image" src="https://github.com/user-attachments/assets/ead04144-b322-405f-9e1c-88b64b2b26df" />
---

# Resources

https://harm-smits.github.io/42docs/libs/minilibx

### Parsing

Walkthrough cub3D parsing.pdf

## Raycasting Resources

https://en.wikipedia.org/wiki/Field_of_view_in_video_games

https://en.wikipedia.org/wiki/Ray_casting

https://www.youtube.com/watch?v=eOCQfxRQ2pY&t=54s

https://www.youtube.com/watch?v=2IEUa2gYJHQ

https://www.youtube.com/watch?v=gYRrGTC7GtA

https://www.youtube.com/@SebastianLague

https://github.com/wwwwelton/raycasting-c - Pokuma

