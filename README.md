# OpenGL Tutorial
Learning opengl

## Build
Install dependencies
```
sudo apt install xorg-dev libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules build-essential libxmu-dev libxi-dev libgl-dev python
```

Build the output file
```
make
```

## Error fix
- Unsuportet shader version execute: ``export MESA_GL_VERSION_OVERRIDE=3.3``
- error while loading shared libraries: libGLEW.so.2.2: cannot open shared object file: No such file or directory
  - Look at --> [Stack Overflow](https://stackoverflow.com/questions/26372359/error-loading-shared-library-glew)
