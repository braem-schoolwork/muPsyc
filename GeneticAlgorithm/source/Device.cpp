#include "Device.h"
#include <random>

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> boolDist(0, 1);