TD-Game

#### Using:
- [OpenGL Loader Generator](https://bitbucket.org/alfonse/glloadgen/wiki/Home)
(Analog: https://github.com/Dav1dde/glad)
- [OpenGL](https://www.opengl.org)
- [GLFW](http://www.glfw.org) ([Git](https://github.com/glfw/glfw))
- [OpenGL Mathematics (GLM)](https://glm.g-truc.net/0.9.9/index.html) ([Git](https://github.com/g-truc/glm))
- [Open Asset Import Library](http://assimp.org) ([Git](https://github.com/assimp/assimp))
- [stb single-file public domain libraries for C/C++](https://github.com/nothings/stb) (stb_image.h)

BUGS
- Change to GCC Version 7.3.0 instead 8.2. (std::filesystem) https://sourceforge.net/p/mingw-w64/bugs/737/
- Change to MSVC. Not possible to build Assimp as dynamic library using mingw-w64 GCC Version 7.3.0.
