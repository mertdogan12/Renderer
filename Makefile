all: glfw glew build

glfw:
	@echo "Cloneing glfw"
	git clone https://github.com/glfw/glfw.git
	@echo "Compiling glfw"
	cmake -S glfw -B glfw/build
	sudo make install -C glfw/build
	@echo "Removeing glfw repo"
	sudo rm -rf glfw

glew:
	@echo "Cloneing glew"
	git clone https://github.com/nigels-com/glew.git
	@echo "Compiling glew"
	make -C glew/auto
	make -C glew
	sudo make install -C glew
	@echo "Removeing glew"
	sudo rm -rf glew

build:
	@echo "Building"
	g++ -g src/*.cpp vendor/stb/*.cpp vendor/imgui/*.cpp -Ivendor -Isrc -Ilib -lGLEW -lGLU -lglfw3 -ldl -lpthread -lGL
