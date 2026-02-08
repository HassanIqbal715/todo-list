#include"../include/json.h"

JsonObject::JsonObject() {}

bool JsonObject::checkKeyExist(string key) {
    auto it = keyValuePairs.find(key);
    return it != keyValuePairs.end();
}

void JsonObject::appendKeyValue(string key, void* value) {
    if (!checkKeyExist(key))
        keyValuePairs.insert(pair(key, value));
}

void JsonObject::print() {
    if (keyValuePairs.empty()) return;
    cout << "{\n";
    for (auto& it : keyValuePairs) {
        cout << '\t' << it.first << ": " << 
            *static_cast<string*>(it.second) << '\n';
    }
    cout << "}\n";
}

void* JsonObject::getValue(string key) {
    auto it = keyValuePairs.find(key);
    if (it != keyValuePairs.end())
        return it->second;
    return nullptr;
}

JsonObject::~JsonObject() {}

JSON* JSON::Instance = nullptr;

JSON* JSON::instance() {
    if (Instance == nullptr)
        Instance = new JSON;
    return Instance;
}

void JSON::storeToken(string value, TokenType type) {
    tokens.push_back(new Token{type, value});
}

void JSON::tokenize(string line) {
    bool hasStarted = false;
    bool hasEnded = false;
    bool isReading = false;
    bool isString = false;
    char buffer[500];
    int bufferIndex = 0;

    for (int i = 0; i < line.length(); i++) {
        switch(line[i]) {
            case '{':
                buffer[bufferIndex] = '\0';
                bufferIndex = 0;
                hasStarted = true; 
                hasEnded = false;
                isReading = true;
                break;

            case '}': 
                buffer[bufferIndex] = '\0';
                bufferIndex = 0;
                storeToken(buffer, TokenType::VALUE);
                extractKeyValue();
                hasEnded = true; 
                hasStarted = false;
                isReading = false;
                break;

            case ':': 
                if (isString) {
                    buffer[bufferIndex++] = line[i];
                    break;
                }

                buffer[bufferIndex] = '\0';
                bufferIndex = 0;
                storeToken(buffer, TokenType::KEY);
                isReading = false;
                break;

            case ',':
                if (isString) {
                    buffer[bufferIndex++] = line[i];
                    break;
                }

                buffer[bufferIndex] = '\0';
                bufferIndex = 0;
                if (!hasEnded)
                    storeToken(buffer, TokenType::VALUE);
                if (hasEnded == true && hasStarted == false) {
                    hasStarted = false;
                    hasEnded = false;
                }
                isReading = false;
                break;

            case '"':
                isString = !isString;
            case '\t':
            case '\r':
            case '\n':
                break;

            case ' ':
                if (isReading)
                    buffer[bufferIndex++] = line[i];
                break;

            default:
                isReading = true;
                buffer[bufferIndex++] = line[i];
                break;
        }
    }
}

void JSON::extractKeyValue() {
    JsonObject* obj = new JsonObject;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i]->type == TokenType::KEY) {
            obj->appendKeyValue(tokens[i]->value, 
                static_cast<void*>(&tokens[i+1]->value));
        }
    }
    objectsBuffer.push_back(obj);
    tokens.clear();
}

vector<JsonObject*> JSON::readLine(string line) {
    tokens.clear();
    objectsBuffer.clear();
    tokenize(line);
    return objectsBuffer;
}

void JSON::destroyObjectsVector(vector<JsonObject*> &objects) {
    for (int i = 0; i < objects.size(); i++) {
        delete objects[i];
    }
}

JSON::~JSON() {
    if (Instance != nullptr)
        delete Instance;
}