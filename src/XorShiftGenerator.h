#pragma once

#include <cstdint>
#include "Point.h"


// This class generates random points using a fast bit trick method.
// It is much faster than mt19937 but less statistically strong.
class XorShiftGenerator
{
public:
    // Constructor with optional seed value.
    explicit XorShiftGenerator(uint32_t seed = 123456);

    // Generates one random 2D point.
    Point Generate();

private:
    // Stores the current internal state.
    // Each call scrambles this number.
    uint32_t m_state;

    /****************************************************/

    // Core random scrambling function.
    static uint32_t XorShift32(uint32_t& state);

    // Converts integer output to float between 0 and 1.
    float SetFastFloat();
};