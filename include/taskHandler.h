#pragma once
#include<string>
#include"json.h"
#include"task.h"
#include"file.h"
#include"utils.h"
using namespace std;

class TaskHandler {
private:
    static TaskHandler* Instance;
    TaskHandler();
    ~TaskHandler();
    int findMinId(vector<Task*> &tasks);

public:
    static TaskHandler* instance();
    void extractTask(vector<Task*> &tasks, JsonObject* &newObject);
    void addTask(vector<Task*> &tasks, string task);
    void updateTask();
    void deleteTask(vector<Task*> &tasks, int id);
    void listTasks(vector<Task*> &tasks);
    void writeTasks(vector<Task*> tasks, File* file);
};