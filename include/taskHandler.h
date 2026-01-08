#include<string>
using namespace std;

class TaskHandler {
private:
    static TaskHandler* Instance;
    TaskHandler();

public:
    static TaskHandler* instance();
    void addTask(string task);
    void updateTask();
    void deleteTask();
    void listTasks();
};