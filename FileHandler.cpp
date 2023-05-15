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

FileHandler::FileHandler() {}

FileHandler::~FileHandler() {}

void FileHandler::readMapFromFile(Board* board, const string &name_of_file) {
    ifstream file(name_of_file);
    
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
    for(int i = 0; i < HEIGHT - 2; i++) {
        for(int j = 0; j < WIDTH; j++) {
            board->setCellInvers(i, j, lines[i][j]);

            

        }
        cout << endl;
    }


    file.close();
}
