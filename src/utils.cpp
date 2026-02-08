#include"../include/utils.h"

TaskStatus stringToTaskStatus(string str) {
    if (str.compare("0") == 0) {
        return TaskStatus::TODO;
    }
    else if (str.compare("1") == 0) {
        return TaskStatus::IN_PROGESS;
    }
    else if (str.compare("2") == 0) {
        return TaskStatus::DONE;
    }
    else {
        return TaskStatus::NA;
    }
}

void printFormattedTime(char* time) {
    string months[12] = { 
        "Jan", "Feb", "Mar", "Apr", 
        "May", "Jun", "Jul", "Aug", 
        "Sep", "Oct", "Nov", "Dec"
    };

    char month[4] = {time[4], time[5], time[6], '\0'};
    
    cout << time[8] << time[9] << "/";

    for (int i = 0; i < 12; i++) {
        if (months[i].compare(string(month)) == 0) {
            if (i + 1 < 10) cout << 0;
            cout << i+1 << "/";
            break;
        }
    }

    cout << time[20] << time[21] << time[22] << time[23] << " ";
    
    for (int i = 11 ; i <= 18; i++) {
        cout << time[i];
    }
}