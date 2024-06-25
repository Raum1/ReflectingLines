#include "rando.h"
#include <ctime>
#include <cstdlib> 
int rando::getRandomNumber(int min, int max){
    int num = rand() % max + 1 + min;
    return num;
}