# HazelRoids
A simple clone for the game [Asteroids](https://en.wikipedia.org/wiki/Asteroids_(video_game)) from the 1980s.

This repository is used for educational purpose, serves as a demo for making a game using the [Hazel] game engine](https://github.com/TheCherno/Hazel).

With this project, I want to test and show off the ability to link an executable project with Hazel static library externally. With this, you can have several different Sandbox game/application linked against Hazel at the same time, without the need to keep multiple copy of the whole engine source code itself.
 
## Gameplay
- Press Left/Right arrow key  to turn ship left/right.
- Press Up arrow key to accelerate and Down arrow key to decelerate faster.
- Hold Ctrl + R for a while to restart the game (there will be indicator appear).
- Hold Alt key to show (Imgui) debug/info gui.

## Todo list
- [ ] Add debug/info gui
- [x] Add particles.
- [ ] Add more particles.
    - [ ] Add bullet trail.
    - [ ] Add player ship thruster trail.
 
## Build
Windows only, with MS Visual Studio 2017/2019.
1. `git clone https://github.com/3x3y3z3t/HazelRoids` to clone this repository.
2. Edit the file `premake5.lua`:
** `IncludeDir["engine"]` should point to the location of your Hazel solution.
3. Run the script `GenSolution-vs2017.bat` or `GenSolution-vs2019.bat`.
4. Open the generated solution in the same folder and build project using MSVS.

## Notes
- This project can be built against the primitive version of Hazel, which is currently the latest version. I will continue updating the project when Hazel API have minor change.
- You will need to have Hazel libraries already built before building this project.
