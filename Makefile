all: build

install: build-lib
	@echo Installing the lib
	mkdir -p /usr/include/renderer
	cp bin/static/librenderer.a /usr/lib
	cp src/renderer/*.h /usr/include/renderer

build:
	@echo "Building"
	mkdir -p bin
	g++ -g src/main.cpp src/*/*.cpp vendor/stb/*.cpp vendor/imgui/*.cpp -Isrc -Ivendor -lGLEW -lGLU -lglfw3 -ldl -lpthread -lGL -o bin/renderer.out

log:
	@echo "Building with logging"
	rm -f log.txt
	touch log.txt
	mkdir -p bin
	g++ -g src/main.cpp src/*/*.cpp vendor/stb/*.cpp vendor/imgui/*.cpp -Isrc -Ivendor -lGLEW -lGLU -lglfw3 -ldl -lpthread -lGL -o bin/renderer.out &> log.txt

build-lib:
	@echo "Building the lib"
	mkdir -p bin/static
	g++ -c -Isrc -Ivendor -Ilib src/renderer/Renderer.cpp -o bin/static/renderer.o
	g++ -c -Isrc -Ivendor -Ilib src/renderer/Encoder.cpp -o bin/static/encoder.o
	g++ -c -Isrc -Ivendor -Ilib src/renderer/Shader.cpp -o bin/static/shader.o
	g++ -c -Isrc -Ivendor -Ilib src/renderer/Texture.cpp -o bin/static/texure.o
	g++ -c -Isrc -Ivendor -Ilib src/renderer/VertexObject.cpp -o bin/static/vertex-object.o
	ar rcs bin/static/librenderer.a bin/static/*.o

clean:
	rm -rf bin
