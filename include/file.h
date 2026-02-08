#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
using namespace std;

class File {
private:
    string path;
    fstream file;

public:
    File(string Path);
    void createFile();
    bool openFile();
    void writeFile(string line, bool pointerReset);
    void clearFile();
    string* readFile();
    ~File();
};