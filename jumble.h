//
// Created by Liam Salass on 2022-11-10.
// #20229595
//

#ifndef JUMBLE_PUZZLE_JUMBLE_H
#define JUMBLE_PUZZLE_JUMBLE_H

#include <stdexcept>

using namespace std;

typedef char* charArrayPtr;

class BadJumbleException : public std::exception {
public:
    char *what();
};


class JumblePuzzle {
private:
    charArrayPtr *arr;
    string hide;
    string dif;
    int size;
    int x;
    int y;
    /* For direction int dir
     * 0 means north
     * 1 means east
     * 2 means south
     * 3 means west         */
    int dir;
    void genJumble();
    int genSize();

public:
    //Constructors
    JumblePuzzle();
    JumblePuzzle(JumblePuzzle const &copy);
    JumblePuzzle(string hide, string difficulty);

    //Destructor
    ~JumblePuzzle();
    //Equals operator overload
    const JumblePuzzle& operator=(const JumblePuzzle& copy);

    //Getters
    charArrayPtr* getJumble();
    const std::string getWord();
    const int getSize();
    const int getRowPos();
    const int getColPos();
    const char getDirection();
    const std::string getDif();
    const int getDir();
};



#endif //JUMBLE_PUZZLE_JUMBLE_H
