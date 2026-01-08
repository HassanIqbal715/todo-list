#include "../include/file.h"

File::File(string path) {
    this->path = path;
}

void File::createFile() {
    char buffer[500];
    int bufferIndex = 0;
    int latestSlashIndex = -1;

    for (int i = 0; i < path.length(); i++) {
        if (path[i] == '/' || path[i] == '\\')
            latestSlashIndex = bufferIndex;

        buffer[bufferIndex] = path[i];
        bufferIndex++;
    }

    if (latestSlashIndex != -1) {
        buffer[latestSlashIndex] = '\0';
        std::filesystem::create_directories(buffer);
    }

    std::filesystem::path filePath = path;

    ofstream f(filePath);
    if (f.is_open()) f.close();
}

bool File::openFile() {
    if (file.is_open()) {
        return true;
    }

    std::filesystem::path filePath = path;

    if (!std::filesystem::exists(filePath))
        createFile();

    file.open(filePath, std::ios_base::openmode::_S_app |
        std::ios_base::openmode::_S_in);
    
    return file.is_open();
}

void File::writeFile(string line) {
    if (!openFile()) return;

    file << line;
}

string* File::readFile() {
    if (!openFile()) return nullptr;

    file.seekg(0);

    string line;
    string data[500];
    int index = 0;
    while(getline(file, line)) {
        data[index++] = line;
    }

    data[index] = '\0';
    return data;
}

File::~File() {
    if (file.is_open())
        file.close();
}