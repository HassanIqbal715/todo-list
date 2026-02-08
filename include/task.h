#pragma once
#include<iostream>
#include<chrono>
#include<ctime>
using namespace std;

enum TaskStatus {TODO, IN_PROGESS, DONE, NA};

struct Task {
    int id;
    string description;
    TaskStatus status;
    chrono::time_point<chrono::system_clock> createdAt;
    chrono::time_point<chrono::system_clock> updatedAt;

    void print();
};