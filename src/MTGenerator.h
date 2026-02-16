#pragma once

#include <random>
#include "Point.h"


// This class generates random points using std::mt19937.
// It is slower but statistically stronger.
class MTGenerator
{
public:
    // Constructor: sets up the random number generator.
    MTGenerator();

    // Generates one random 2D point.
    Point Generate();

private:
    // The random engine (Mersenne Twister).
    std::mt19937 m_rng;

    // Converts integers into floating numbers between 0 and 1.
    std::uniform_real_distribution<float> m_dist;
};