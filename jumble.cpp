//
// Created by liams on 2022-11-10.
//

#include "jumble.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

//Error handling
char *BadJumbleException::what() {
    return (char *) "Bad Jumble Exception";
}


JumblePuzzle::JumblePuzzle(){
    //Empty constructor
    hide = "";
    dif = "";
    size = 0;
    arr = NULL;
    x = 0;
    y = 0;
}

JumblePuzzle::JumblePuzzle(string hidden, string difficulty){
    //Normal Constructor
    hide = hidden;
    dif = difficulty;
    size = genSize(); //sets size
    genJumble(); //genJumble() sets x, y, and arr
}

JumblePuzzle::JumblePuzzle(JumblePuzzle const &other){
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
        free(arr[i]);
    free(arr);
    cout << "Deleted" << endl;
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
    //Allocate the array
    try {
        arr = (char **) malloc(size * sizeof(char *));
        for (int i = 0; i < size; i++)
            arr[i] = (char *) malloc(size * sizeof(char));
    } catch (BadJumbleException& e) {
        cerr << e.what() << endl;
    }
    //Pick random x, y and direction for placing letters
    x = rand() % size;
    y = rand() % size;
    dir = rand() % 4;

    //Turn string into array of char
    int n = hide.length();
    char char_array[n + 1];
    strcpy (char_array, hide.c_str());

    //Fill array with random characters
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            arr[i][j] = (rand()% 25) + 97;

    //Place chars in heap
    /*
     * If reaches edge of the heap, changes dir and
     * resets i  to begin placing chars again from the beginning
    */
    for (int i = 0; i < n; i++){
        switch (dir){
            case 0: // North
                if ((y - i) < 0){
                    i = 0;
                    dir = 1;
                    continue;
                }
                arr[y - i][x] = char_array[i];
                break;
            case 1: // East
                if ((x + i)> size){
                    i = 0;
                    dir = 2;
                    continue;
                }
                arr[y][x+i] = char_array[i];
                break;
            case 2: // South
                if ((y+i)> size){
                    i = 0;
                    dir = 3;
                    continue;
                }
                arr[y + i][x] = char_array[i];
                break;
            case 3: // West
                if ((x-i)<0){
                    i = 0;
                    dir = 0;
                    continue;
                }
                arr[y][x - i] = char_array[i];
                break;
            default:
                throw BadJumbleException();
        }
    }
}

charArrayPtr* JumblePuzzle::getJumble(){
    //Returns a new jumble by allocating memory for a new
    //arry of equal size and then copies the contents from the
    //other array into the new one to be returned.
    char **newArr = (char**) malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++ ){
        newArr[i] = (char*) malloc(size * sizeof(char));
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
