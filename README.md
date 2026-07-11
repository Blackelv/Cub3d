___This project has been created as part of the 42 curriculum by Kelemayi, Ffrattar___

# Cub3D

## Description
Cub3D is a programming project whose goal is the dynamic creation and navigation of a "realistic" 3D first-person maze "game" written in C.

The map of the game is provided by the user and validated by the Cub3D program, before being rendered using raytracing. It is developed using primarily user-created functions, with the exception of an imported MinilibX library and the standard C Math library. This project teaches file parsing and validation as well as raytracing and texture rendering concepts.

The Cub3D program must correctly parse a map scene passed to it as an initial argument and show the user a 3D scene that the user can then navigate.

The user should be able to navigate using the following commands:
```
// L / R arrows look left and right
// WASD key move player relative to view orientation
// ESC & [X] quits program cleanly
// [SPACEBAR] toggles minimap
// [+]/[-] keys grow and shrink minimap (FOV visible on max size)
```

Note:  Bonus features include a togglable mini-map and wall collision detection. 

## Instructions

### Dependencies

- Linux, w/clang compiler
- X11 windows manager
- Minilibx Library (external dependency imported upon make if user has internet connection)

The program is designed to to be run on a linux system with a clang compiler and X11 windows manager. The user must also use the [minilibx 42 rendering library](https://github.com/42paris/minilibx-linux) which should be included in the project makefile, but can also be downloaded from the linked source and included in the main project directory.

Assuming you have all required dependencies, from the main project directory, to start the program for the first time first run `make` to compile the program before use.
The `./maps` folder in the main project folder contains demo maps and the `./maps/textures` folder contains multiple textures that are referenced by the demo maps. Feel free to import your own textures and/or create your own maps.


See the following example usage.

### Example Usage

To launch, enter `./cub3D ./path/to/map/file/map.cub` where `map.cub` is a file containing map information structured like the below example:

```jsx
NO ./maps/big_textures/n.xpm
SO ./maps/big_textures/s.xpm
WE ./maps/big_textures/w.xpm
EA ./maps/big_textures/e.xpm

F 50,50,50
C 20,20,20

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000E00000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010000001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
1100000111010101111101111000111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Valid Map requirements in order of appearance:
1. Wall textures are to be saved as `.xpm` files and associated with a specific map orientation (NO, SO, WE, WA).
2. Floor and ceiling colors must be defined in RGB format
3. Aerial map layout represented with 0,1, spaces, & player location letter (NESW)
   - 1 = walls
   - 0 = floor
   - Single N/E/S/W reflects player spawn point and orientation
   - All floor must be enclosed by walls

Your map will be rejected with a descriptive error message if invalid.

If you map is valid then you should see something like this:

<img width="1199" height="744" alt="image" src="https://github.com/user-attachments/assets/ead04144-b322-405f-9e1c-88b64b2b26df" />
---

From here, use the following controls to navigate the scene:

```
// L / R arrows look left and right
// WASD key move player relative to view orientation
// ESC & [X] quits program cleanly
// [SPACEBAR] toggles minimap
// [+]/[-] keys grow and shrink minimap (FOV visible on max size)
```

# Resources

The concepts that required the most research were the math behind raytracing and the proper usage of the Minilibx library.

### Minilibx

https://harm-smits.github.io/42docs/libs/minilibx

## Raycasting Resources

https://en.wikipedia.org/wiki/Field_of_view_in_video_games

https://en.wikipedia.org/wiki/Ray_casting

[Wolfstein 3D Map Rendering Video](https://www.youtube.com/watch?v=eOCQfxRQ2pY&t=54s)

[Raycasting in C from scratch video](https://www.youtube.com/watch?v=2IEUa2gYJHQ)

[Make your own raycaster tutorial video](https://www.youtube.com/watch?v=gYRrGTC7GtA)

### AI Usage

AI was used for conceptual research purposes (ex. "how does raytracing work?" "what does this equation do?". No AI generated code was used in this project.
