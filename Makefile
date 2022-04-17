all: build

install: glfw glew build

glfw:
	@echo "Cloneing glfw"
	git clone https://github.com/glfw/glfw.git
	@echo "Compiling glfw"
	cmake -S glfw -B glfw/build
	make install -C glfw/build
	@echo "Removeing glfw repo"
	rm -rf glfw

glew:
	@echo "Cloneing glew"
	git clone https://github.com/nigels-com/glew.git
	@echo "Compiling glew"
	make -C glew/auto
	make -C glew
	make install -C glew
	@echo "Removeing glew"
	rm -rf glew

build:
	@echo "Building"
	g++ -g src/*.cpp vendor/stb/*.cpp vendor/imgui/*.cpp -Ivendor -Ilib -lGLEW -lGLU -lglfw3 -ldl -lpthread -lGL

log:
	@echo "Building with logging"
	rm -f log.txt
	touch log.txt
	g++ -g -std=c++20 src/*.cpp vendor/stb/*.cpp vendor/imgui/*.cpp -Ivendor -Ilib -lGLEW -lGLU -lglfw3 -ldl -lpthread -lGL &> log.txt
