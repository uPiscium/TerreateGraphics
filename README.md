# About TerreateCore
`TerreateCore` is a basic `OpenGL` handler for `C++`. This framework is using `glfw` and `glad` for handling `OpenGL`. You can get more information about `OpenGL` in `glfw` [homepage](https://www.glfw.org/docs/latest/) The license is BSD3(BSD 3-Clause "New" or "Revised" License). `cmake` is needed to build this project, so you have to install `cmake` before building this project.

# Sections
- [How to use](#how-to-use)
  - [Windows](#windows)
  - [Linux](#linux)
- [Contact](#contact)

# How to use
`TerreateCore` supports `Windows` and `Linux`.
You can use `TerreateCore` by following the steps below.
**Be sure to install `cmake` before building this project.**

## Windows
1. Make `build` folder in the root folder and go to the `build` folder.
2. Run `cmake ..` in the `build` folder.
3. Run `cmake --build .` in the `build` folder.

Here is the example of the steps above.
```bash
# C:/Users/username/.../TerreateCore
mkdir build
cd build
cmake ..
cmake --build .
```
Then `TerreateCore.lib` will be created in `build` folder.

** If you have `***\r~~` error, you can use the command below.
```bash
dos2unix build.sh
```

## Linux
1. Make `build` folder in the root folder and go to the `build` folder.
2. Run `cmake ..` in the `build` folder.
3. Run `cmake --build .` in the `build` folder.

Here is the example of the steps above.
```bash
# /home/username/.../TerreateCore
mkdir build
cd build
cmake ..
cmake --build .
```
Then `libTerreateCore.a` will be created in `build` folder.


# Contact
If you have any questions, please contact me by email.
- Email: [ uPiscium@gmail.com ]
