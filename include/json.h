#pragma once
#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

class JsonObject {
private:
    unordered_map<string, void*> keyValuePairs;
    bool checkKeyExist(string key);

public:
    JsonObject();
    void appendKeyValue(string key, void* value);
    void print();
    void* getValue(string key);
    ~JsonObject();
};

enum TokenType {KEY, VALUE};

struct Token {
    TokenType type;
    string value;
};

class JSON {
private:
    vector<Token*> tokens;
    vector<JsonObject*> objectsBuffer; // Temporarily stores objects here
    static JSON* Instance;
    ~JSON();

public:
    static JSON* instance();
    void storeToken(string value, TokenType type);
    void tokenize(string line);
    void extractKeyValue();
    vector<JsonObject*> readLine(string line);
    void destroyObjectsVector(vector<JsonObject*> &objects);
};