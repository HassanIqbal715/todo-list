build: src/main.cpp
	@g++ -o main.o src/main.cpp src/file.cpp src/taskHandler.cpp src/json.cpp src/utils.cpp src/task.cpp