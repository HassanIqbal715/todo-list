#include"../include/task.h"
#include"../include/utils.h"

void Task::print() {
    cout << "Id: " << this->id << " Task: " << this->description << " Status: ";
    cout << ((this->status == TaskStatus::TODO) ? "Todo" : 
            (this->status == TaskStatus::IN_PROGESS) ? "Working" : 
            "Done");
    auto createdAtTime = chrono::system_clock::to_time_t(this->createdAt);
    auto updatedAtTime = chrono::system_clock::to_time_t(this->updatedAt);
    cout << " Created At: ";
    printFormattedTime(ctime(&createdAtTime));
    cout << " Updated At: ";
    printFormattedTime(ctime(&updatedAtTime));
    cout << "\n";
}