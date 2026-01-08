#include <iostream>
#include "../include/taskHandler.h"
#include "../include/file.h"
#include "../include/json.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        cerr << "Unexpected: File path not provided!\n";
        return 1;
    }

    JsonObject o1;
    string what = "hassan";
    o1.appendKeyValue("name", static_cast<void*>(&what));
    cout << *static_cast<string*>(o1.getValue("name")) << endl;

    File* file = new File("data/tasks.json");
    string* data = file->readFile();

    for (int i = 0; data[i] != "\0"; i++) {
        vector<JsonObject*> objects = JSON::instance()->readLine(data[i]);
        for (int j = 0; j < objects.size(); j++) {
            objects[j]->print();
        }
    }

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