#include <iostream>
#include <string>
#include "../include/taskHandler.h"
#include "../include/file.h"
#include "../include/json.h"
#include "../include/task.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        cerr << "Unexpected: File path not provided!\n";
        return 1;
    }

    File* file = new File("data/tasks.json");
    string* data = file->readFile();
    vector<JsonObject*> objects;

    for (int i = 0; data[i] != "\0"; i++) {
        vector<JsonObject*> tempObjects = JSON::instance()->readLine(data[i]);
        for (int j = 0; j < tempObjects.size(); j++) {
            objects.push_back(tempObjects[j]);
        }
    }

    vector<Task*> tasks;

    for (int i = 0; i < objects.size(); i++) {
        TaskHandler::instance()->extractTask(tasks, objects[i]);
    }

    string arg1 = argv[1];
    if (arg1.compare("add") == 0) {
        cout << "what";
        TaskHandler::instance()->addTask(tasks, argv[2]);
        TaskHandler::instance()->writeTasks(tasks, file);
    }

    // else if (argv[1] == "update") {
    //     TaskHandler::instance()->updateTask();
    // }
    else if (arg1.compare("delete") == 0) {
        if (argv[2] == NULL || argv[2] == "")
            return 1;
        string arg2 = argv[2];
        TaskHandler::instance()->deleteTask(tasks, stoi(arg2));
        TaskHandler::instance()->writeTasks(tasks, file);
    }
    else if (arg1.compare("list") == 0) {
        TaskHandler::instance()->listTasks(tasks);
    }
    
    delete[] data;
    delete file;
    JSON::instance()->destroyObjectsVector(objects);
}