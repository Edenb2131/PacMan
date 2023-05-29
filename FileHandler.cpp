#include "FileHandler.h"
#include "Board.h"
#include "Ghost.h"
#include "Pacman.h"
#include "Cell.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

FileHandler::FileHandler() { did_load = -1;}

FileHandler::~FileHandler() {}

bool FileHandler::checkIfmapExists(const string& name_of_map)
{
    if (FILE* file = fopen(name_of_map.c_str(), "r")) {
        fclose(file);
        return true;
    }
    else {
        return false;
    }
}

void FileHandler::readMapFromFile(Board* board, const string &name_of_file) {
    ifstream file(name_of_file);
    
    _map.reserve(HEIGHT);
    for (auto& row : _map) {
        row.reserve(WIDTH);
    }

    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        exit(1);
    }
    
    // read the file
    string line;
    vector<string> lines;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    // set the board
    for(int i = 0; i < HEIGHT - 1; i++) {
        _map.push_back(std::vector<char>());
        for(int j = 0; j < WIDTH; j++) {
            char convertedChar = ConvertFileCharaterToBoardCharacter(lines[i][j]);
            _map[i].push_back(convertedChar);
        }
        cout << endl;
    } 
    file.close();   
    did_load = 1;
}

char FileHandler::ConvertFileCharaterToBoardCharacter(char ch) {
    switch (ch)
    {
    case EMPTY_IN_FILE:
        return EMPTY;
    case BREADCRUMB_IN_FILE:
        return BREADCRUMB;
    default:
        return ch;
    }
}

FileHandler& FileHandler::operator=(const FileHandler& other) {
    if (this != &other) {
        did_load = other.did_load;
    }
    return *this;
}