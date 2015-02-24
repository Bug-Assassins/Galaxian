A traveller of the skies - Guide your space-ship through the sea of cosmos.

Galaxian is an Open-GL based "old-day" type 2D game. This project was done as a part of Computer Graphics Course, 4th Semester (B.Tech), Department of Information Technology, National Institute of Technology Karnataka, Surathkal.

The project was made with an objective of learning 2D Animations and basic transformations. It has been written in C++ but can be converted to C language without much change. (No Classes has been used). This game is inspired by the classical DOS-era shooting games.


Installation on Linux Distribution

1. Install OpenGL using the following command: sudo apt-get install freeglut3 freeglut3-dev mesa-utils
2. Open the main.cpp file and compile it with: gcc main.cpp -lGL -lGLU -lglut -lstdc++

Note : Game may not work properly in windows. For best result use any linux distribution.


Play-Controls

Left Key = Move the ship left

Right Key =  Move the ship right

Mouse Movement = Ship moves left and right with mouse

Spacebar/Left Click = Shooting

'P'/'p'/Right Click = Pause/Resume Game

'R'/'r' = Resume Game (Works only in Pause Game Screen)

'Q'/Esc Key = Quit Game

'S'/'s' = Start the game (works only in start screen)


Settings

When the program is executed for the first time the setting file with default values is generated. User can edit that file in order to achieve desired effect in the game.


Project Highlights

1. Collision-Detection Algorithm in the file move.cpp
2. Mouse Hovering Effect in all the Menu
3. Double Buffering to achieve flicker-free animation. High FPS (60 Frames per seconds)
4. All Basic OpenGl function has been used
5. Settings and highscore saved using files


Basic Function

We have implemented all the basic functions of a graphics engine like Line Drawing, Circle Drawing, Ellipse Drawing, Scan-Line Polygon Fill, Line Clipping, Polygon Clipping and 3-D transformations (translation, rotation and scaling). All these implementation can be found in the folder basic_cg. Line/Circle/Ellipse/Scan-line Polygon fill are in file primitives.cpp.

To test the transformations use the right and left mouse clicks to enable or disable the transformation.

Note: These basic function has nothing to do with our main project. It has been included for learning purpose only.


Project Contributors :

Team Bug Assassins

1. Ashish Kedia (ashish1294@gmail.com)

2. Ajith P S (ajithpandel@gmail.com)

3. Adarsh Mohata (amohta163@gmail.com)

