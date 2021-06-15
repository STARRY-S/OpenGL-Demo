# OpenGL Demo

![](res/preview.png)

(Core-profile) OpenGL Camera + Light demo written in C based on GLFW, GLAD and stb_image.

[简体中文](README_CN.md)

## Usage

Install GLAD, GLFW and CMake utils refers to [Learn OpenGL](https://learnopengl.com/).

Download `stb_image.h` and `glad.c` into `src` and move `glad.h` into your build library.

For Linux/Unix：

```
$ mkdir build && cd build
$ cmake .. && make
$ ./main -h     # show usage information (-f for fullscreen, no args for window mode)
```
---

## License

Texture:
[Faithful x32](https://www.curseforge.com/minecraft/texture-packs/faithful-team),

Refer: [Learn OpenGL](https://learnopengl.com/)

> License: Apache-2.0
