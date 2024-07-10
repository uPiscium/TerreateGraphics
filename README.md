# About TerreateCore
`TerreateCore` is a basic `OpenGL` handler for `C++`. This framework is using `glfw` and `glad` for handling `OpenGL`. You can get more information about `OpenGL` in `glfw` [homepage](https://www.glfw.org/docs/latest/) The license is BSD3(BSD 3-Clause "New" or "Revised" License). `cmake` is needed to build this project, so you have to install `cmake` before building this project.

# Sections
- [About TerreateCore](#about-terreatecore)
- [Sections](#sections)
- [How to use](#how-to-use)
  - [Windows](#windows)
    - [CMake setup](#cmake-setup)
  - [Linux](#linux)
- [Contact](#contact)

# How to use
`TerreateCore` supports `Windows` and `Linux`.
You can use `TerreateCore` by following the steps below.
**Be sure to install `cmake` before building this project.**

## Windows
### CMake setup
If you doesn't setup your cmake, you should do it before building this project with cmake. Please follow the instructions below. ( If you already do this, you can go to [next step](#build-with-cmake)! )
1. Install `Visual Studio Code (VSCode)` and `Visual Studio`.
2. Open this repositry folder with `VSCode`.
3. Open `Command Palette` with `Ctrl+Shift+P`.
4. Find `CMake: Quick start` command and run it. ( You can find it with entering `CMake` to the text box. )
5. Select `Visual Studio Community 20XX Release ~~`.

Now, you can go to next step!

Build with following command.
```bash
# pwd  =>  .../TerreateCore/
cmake -S . -B build
cmake --build build
```
`TerreateCore.lib` is generated in `build/lib/Debug/TerreateCore.lib`.

You can run test with following command.
```bash
# pwd  =>  .../TerreateCore/
./build/bin/Debug/TCTest.exe
```
execute in different folder is **NOT** supported. It will cause `Failed to load XXX` error.\

## Linux
Build with following command.
```bash
# pwd  =>  .../TerreateCore/
cmake -S . -B build
cmake --build build
```
`libTerreateCore.a` is generated in `build/lib/libTerreateCore.a`.

You can run test with following command.
```bash
# pwd  =>  .../TerreateCore/
./build/bin/TCTest
```
execute in different folder is **NOT** supported. It will cause `Failed to load XXX` error.\

# Contact
If you have any questions, please contact me by email.
- Email: [ uPiscium@gmail.com ]
