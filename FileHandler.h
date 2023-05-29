#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include "Board.h"

#define BREADCRUMB_IN_FILE ' '
#define EMPTY_IN_FILE '%'


class Board;
/*
    * This class is responsible for reading the screens and initilize ghosts and Pac-MAn.
    * The screens called "pacman_a.screen.txt", "pacman_b.screen.txt", "pacman_c.screen.txt".
    * It will be used to read the map from a file.
*/

class FileHandler
{
   
public:
    int did_load;
    FileHandler();
    ~FileHandler();

    // operator overloading
    FileHandler& operator=(const FileHandler& other);

    static bool checkIfmapExists(const std::string& name_of_map);
    void readMapFromFile(Board* board, const std::string &name_of_file);
    char ConvertFileCharaterToBoardCharacter(char ch);

    const std::vector<std::vector<char>>& get() { return _map; }

private:
    std::vector<std::vector<char>> _map;
};

