#include "rando.h"
#include <ctime>
#include <cstdlib>
int rando::getRandomNumber(int min, int max)
{
    int num = rand() % max + 1 + min;
    return num;
}
double rando::getRandomProbability()
{
    double r = rand() / double(RAND_MAX);
    return r;
}