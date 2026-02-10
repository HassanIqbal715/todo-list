#pragma once
#include<iostream>
#include<string>
#include<chrono>
#include<ctime>
#include"task.h"
using namespace std;

TaskStatus stringToTaskStatus(string str);
string toLowerCase(string str);
void printFormattedTime(char* time);