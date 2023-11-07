# About GeoFrame
`GeoFrame` is a basic `OpenGL` handler for `C++`. This framework is using `glfw` and `glad` for handling `OpenGL`. You can get more information about `OpenGL` in `glfw` [homepage](https://www.glfw.org/docs/latest/) The license is BSD3(BSD 3-Clause "New" or "Revised" License).

# How to Install
Select release build which is compatible to your OS.
- [Windows](#install-to-windows)
- [Linux](#install-to-linux)

## Install to Windows
1. Download ZIP file and unzip downloaded file.
2. Run following command.
```
mkdir build
cd build
cmake ../
cmake --build .
```
3. `GeoFrame.dll` file is generated at `build/Debug/GeoFrame.dll`.

## Install to Linux (WIP)
**WARNING : THIS IS NOT TESTED YET.**

Install `FreeType` and `glfw` before install `GeoFrame`.
You can download `FreeType` source code from [here](https://www.freetype.org/download.html) and you can install `glfw` by using package manager.

1. Download ZIP file and unzip downloaded file.
2. Copy `freetype.a` to `GeoFrame/libs/` directory.
3. Copy `glfw3.a` to `GeoFrame/libs/` directory.
4. Run following command.
```
mkdir build
cd build
cmake ../
cmake --build .
```
5. `GeoFrame.so` file is generated at `build/Debug/GeoFrame.so`.
