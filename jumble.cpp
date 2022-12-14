//
// Created by Liam Salass on 2022-11-10.
// #20229595
//

#include "jumble.h"
#include <cstdlib>
#include <cstring>

//Error handling
char *BadJumbleException::what() {
    return (char *) "Bad Jumble Exception";
}

JumblePuzzle::JumblePuzzle(string hidden, string difficulty){
    //Normal Constructor
    if (hidden.length() < 3 || hidden.length() > 10) throw BadJumbleException();
    hide = hidden;
    dif = difficulty;
    size = genSize(); //sets size
    genJumble(); //genJumble() sets x, y, and arr
}

JumblePuzzle::JumblePuzzle(JumblePuzzle const &other){
    if (this == &other) return;
    //Copy constructor
    hide = other.hide;
    dif = other.dif;
    size = other.size;
    x = other.x;
    y = other.y;
    arr = other.arr;
    dir = other.dir;
}

JumblePuzzle::~JumblePuzzle(){
    //Destructor deletes each column and then the row.
    for (int i = 0; i < size; i++ )
        delete[] arr[i];
    delete[] arr;
}

int JumblePuzzle::genSize(){
    //Calculates the size of the square array
    int d = 0;
    if (dif == "easy") d = 2;
    else if (dif == "medium") d = 3;
    else if (dif == "hard") d = 4;
    else throw BadJumbleException();
    return hide.length() * d;
}

void JumblePuzzle::genJumble(){
    //Allocate the array in heap
    arr = new char * [size];
    for (int i = 0; i < size; i++)
        arr[i] = new char [size];
    //Pick random x, y and direction for placing letters
    x = rand() % size;
    y = rand() % size;
    dir = rand() % 4;

    //Turn string into array of char
    int n = hide.length();
    char char_array[n];
    strcpy (char_array, hide.c_str());

    //Fill array with random characters
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            arr[i][j] = (rand()% 25) + 97;

    //Place chars in jumble puzzle
    //If in a horizontal direction
    if (dir == 1 || dir == 3) {
        //Change x position so that it doesn't extend outside of the heap
        x = rand() % (size - n);
        //Revers the string array if it's going west
        if (dir == 3) {
            strrev(char_array);
        }
        //Fill the jumble puzzle with the word
        for (int i = 0; i < n ; i++) {
            arr[y][i + x] = char_array[i];
        }
        //Move x to correct position
        if (dir == 3) {
            x += n - 1;
        }
    }
    //If in a vertical direction
    if (dir == 0 || dir == 2) {
        //Change x position so that it doesn't extend outside of the heap
        y = rand() % (size - n);
        if (dir == 0) {
            strrev(char_array);
        }
        //Fill the jumble puzzle with the word
        for (int i = 0; i < n ; i++) {
            arr[y + i][x] = char_array[i];
        }
        //Move y to correct position
        if (dir == 0) {
            y += n - 1;
        }
    }
}

charArrayPtr* JumblePuzzle::getJumble(){
    //Returns a new jumble by allocating memory for a new
    //arry of equal size and then copies the contents from the
    //other array into the new one to be returned.
    char **newArr = new char* [size];
    for (int i = 0; i < size; i++ ){
        newArr[i] = new char [size];
        for (int j = 0; j < size; j++){
            newArr[i][j] = arr[i][j];
        }
    }
    return newArr;
}
//Getter functions
const int JumblePuzzle::getSize(){
    return size;
}
const int JumblePuzzle::getRowPos() {
    return y;
}
const int JumblePuzzle::getColPos() {
    return x;
}
const int JumblePuzzle::getDir(){
    return dir;
}
const char JumblePuzzle::getDirection() {
    switch (dir) {
        case 0:
            return 'n';
            break;
        case 1:
            return 'e';
            break;
        case 2:
            return 's';
            break;
        case 3:
            return 'w';
            break;
        default:
            throw BadJumbleException();
    }
}
const string JumblePuzzle::getWord(){
    return hide;
}
const string JumblePuzzle::getDif(){
    return dif;
}

//= operator override.
const JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& copy){
    //Creates new jumble puzzle using copy constructor
    JumblePuzzle *jumble = new JumblePuzzle(copy);
    return *jumble;
}
