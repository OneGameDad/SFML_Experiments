#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

unsigned int getRandomClamped(unsigned int max) {
    return (max > 0) ? (std::rand() % (max + 1)) : 0;
}