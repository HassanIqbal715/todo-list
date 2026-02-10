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
    vector<Task*> tasks;

    TaskHandler();
    ~TaskHandler();
    int findMinId(vector<Task*> &tasks);
    vector<Task*>::iterator searchById(vector<Task*> &tasks, int id);
    
public:
    static TaskHandler* instance();
    void setTasks(vector<Task*> &tasks);
    void extractTask(vector<Task*> &tasks, JsonObject* &newObject);
    void addTask(vector<Task*> &tasks, string task);
    void updateTask(vector<Task*> &tasks, int id, TaskStatus status);
    void deleteTask(vector<Task*> &tasks, int id);
    void listTasks(vector<Task*> &tasks);
    void writeTasks(vector<Task*> &tasks, File* &file);
};