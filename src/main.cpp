#include <iostream>
#include "../include/taskHandler.h"
#include "../include/file.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        cerr << "Unexpected: File path not provided!\n";
        return 1;
    }

    File* file = new File("data/tasks.json");
    file->readFile();

    // if (argv[1] == "add") {
    //     TaskHandler::instance()->addTask(argv[2]);
    // }
    // else if (argv[1] == "update") {
    //     TaskHandler::instance()->updateTask();
    // }
    // else if (argv[1] == "delete") {
    //     TaskHandler::instance()->deleteTask();
    // }
    // else if (argv[1] = "list") {
    //     TaskHandler::instance()->listTasks();
    // }
}