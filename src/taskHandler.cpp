#include "../include/taskHandler.h"
#include <unordered_map>

TaskHandler* TaskHandler::Instance = nullptr;

TaskHandler::TaskHandler() {}

// Find the minimum unused ID
int TaskHandler::findMinId(vector<Task*> &tasks) {
    unordered_map<int, int> m;

    for (int i = 0; i < tasks.size(); i++) {
        m[tasks[i]->id] = 1;
    }

    for (int k = 1; k < tasks.size() + 1; k++) {
        if (!m[k]) return k;
    }

    return tasks.size() + 1;
}

TaskHandler* TaskHandler::instance() {
    if (Instance == nullptr)
        Instance = new TaskHandler;
    return Instance;
}

void TaskHandler::extractTask(vector<Task*> &tasks, JsonObject* &object) {
    Task* task = new Task;
    task->id = atoi(static_cast<string*>(object->getValue("id"))->c_str());
    task->description = *static_cast<string*>(object->getValue("description"));
    task->status = stringToTaskStatus(
        *static_cast<string*>(object->getValue("status"))
    );
    task->createdAt = chrono::system_clock::time_point {
        chrono::seconds(stol(static_cast<string*>(
            object->getValue("createdAt"))->c_str()
        ))
    };
    task->updatedAt = chrono::system_clock::time_point {
        chrono::seconds(stol(static_cast<string*>(
            object->getValue("updatedAt"))->c_str()
        ))
    };
    tasks.push_back(task);
}

void TaskHandler::addTask(vector<Task*> &tasks, string desc) {
    int id = findMinId(tasks);
    string description = desc;
    TaskStatus status = TaskStatus::TODO;

    chrono::time_point<chrono::system_clock> createdAt = 
        chrono::system_clock::now();

    chrono::time_point<chrono::system_clock> updatedAt = 
        chrono::system_clock::now();

    Task* task = new Task{id, description, status, createdAt, updatedAt};
    tasks.push_back(task);
}

void TaskHandler::updateTask() {

}

void TaskHandler::deleteTask(vector<Task*> &tasks, int id) {
    for (vector<Task*>::iterator it = tasks.begin(); it != tasks.end(); it++) {
        if ((*it)->id == id) {
            tasks.erase(it);
            return;
        }
    }
    cerr << "Failed! provided ID \"" << id << "\" not found!" << endl; 
}

void TaskHandler::listTasks(vector<Task*> &tasks) {
    cout << "=================================\n";
    for (int i = 0; i < tasks.size(); i++) {
        tasks[i]->print();
    }
    cout << "=================================\n";
}

void TaskHandler::writeTasks(vector<Task*> tasks, File* file) {
    file->clearFile();
    string* data = new string[500];
    data[0] = "[\n";
    for (int i = 0; i < tasks.size(); i++) {
        string id = to_string(tasks[i]->id);
        string description = tasks[i]->description;
        string status = to_string(tasks[i]->status);

        auto duration = tasks[i]->createdAt.time_since_epoch();
        auto seconds = chrono::duration_cast<std::chrono::seconds>(duration).
        count();

        string createdAt = to_string(seconds);
        
        duration = tasks[i]->updatedAt.time_since_epoch();
        seconds = chrono::duration_cast<std::chrono::seconds>(duration).
        count();

        string updatedAt = to_string(seconds);

        data[i+1] = "\t{\"id\": " + id + ", \"description\": \"" + description 
            + "\", \"status\": " + status + ", \"createdAt\": " + createdAt 
            + ", \"updatedAt\": " + updatedAt + "},\n";
    }

    data[tasks.size() + 1] = ']';

    for (int i = 0; i < tasks.size() + 2; i++) {
        file->writeFile(data[i], (i == 0));
    }

    delete[] data;
}

TaskHandler::~TaskHandler() {
    if (Instance != nullptr)
        delete Instance;
}