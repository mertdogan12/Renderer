# Renderer

### Dependencies
#### Arch Linux
```
pacman -S glu glew
```

### Install lib from source
```bash
sudo make install clean
```

### Build
```bash
# Build the lib
make build-lib

# Build an executalble for testing the renderer
make

# Then run it with
bin/renderer.out <name of the test>
```
