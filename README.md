# HazelRoids
A not-so-simple clone for the game [Asteroids](https://en.wikipedia.org/wiki/Asteroids_(video_game)) from the 1980s.

This repository is used for educational purpose, serves as a demo for making a game using the [Hazel game engine](https://github.com/TheCherno/Hazel).

With this project, I want to test and show off the ability to link an executable project with Hazel static library externally. With this, you can have several different Sandbox game/application linked against Hazel at the same time, without the need to keep multiple copy of the whole engine source code itself. 
 
## Gameplay
- Press Left/Right arrow key to turn ship left/right.
- Press Up arrow key to accelerate and Down arrow key to decelerate faster.
- Hold Ctrl + R for a while to restart the game (there will be indicator appear).
- Press TAB key to toggle (Imgui) debug/info gui.
- *You can shoot down enemy UFO's bullets.* 

## Todo list
This version is final.
 
## Build
Windows only, with MS Visual Studio 2017/2019.
1. `git clone https://github.com/3x3y3z3t/HazelRoids` to clone this repository.
2. Switch to [this commit (3d3537d343)](https://github.com/TheCherno/Hazel/tree/3d3537d34345e5e81d1e5816809e5d3edabc7237) using `git checkout 3d3537d34345e5e81d1e5816809e5d3edabc7237`.
3. Edit the file `premake5.lua`: ** `IncludeDir["engine"]` should point to the location of your Hazel solution.**
4. Clone and build the Hazel library if you haven't.
5. Run the script `GenSolution-vs2017.bat`. ** You can edit the script if you use MS Visual Studio 2019.**
6. Open the generated solution in the same folder and build project using MSVS.

## Notes
- This project can be built against the primitive version of Hazel up to [this commit (3d3537d343)](https://github.com/TheCherno/Hazel/tree/3d3537d34345e5e81d1e5816809e5d3edabc7237). For newer version of the engine, please check out the newer version of the game listed below.
- You will need to have Hazel libraries already built before building this project.

## Other version
- [Latest version](https://github.com/3x3y3z3t/HazelRoids/tree/master)
- v1.1 **<- You are here**
