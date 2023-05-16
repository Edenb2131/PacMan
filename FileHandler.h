#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Board.h"

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


    void readMapFromFile(Board* board, const std::string &name_of_file);

};

