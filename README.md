# Astroids
This is the repository for my take on the classic arcade game [Astroids](https://en.wikipedia.org/wiki/Asteroids_(video_game)) built in C using [GLFW](https://www.glfw.org) and OpenGL.

## Building

### Requirements
- [CMake](https://cmake.org/download/)
- (MacOS) [Xcode CLT](https://medium.com/@mrjohnkilonzi/how-to-resolve-no-xcode-or-clt-version-detected-d0cf2b10a750) or the full [Xcode application](https://apps.apple.com/nl/app/xcode/id497799835?mt=12).
- (Windows) [Visual Studio](https://visualstudio.microsoft.com)
- [Git](https://git-scm.com)

### Steps

1. Clone this repository: `git clone --recursive https://github.com/stickyPiston/astroids.git && cd astroids`.
2. _For Windows users_: Open the `astroids` folder in Visual Studio. Press play to build and run the application.

   _For Unix users_: run CMake: `cmake -S . -B build`. This will create a build directory. Go into that folder (`cd build`) and run `make`. This will create an executable called `Astroids` inside the build folder. Run that (`./Astroids`) and enjoy the application.
