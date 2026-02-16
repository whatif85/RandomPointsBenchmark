#include "XorShiftGenerator.h"

// Constructor: sets the starting state.
XorShiftGenerator::XorShiftGenerator(uint32_t seed) :
    m_state(seed)
{}

// This function scrambles the bits of the state.
uint32_t XorShiftGenerator::XorShift32(uint32_t& state)
{
    // Shifts and XOR are:
	// - Extremely cheap CPU operations
    // - No memory access
    // - No branches
    // - No division
    // - Modern CPUs execute them in 1 cycle

    // ^= means: state = state XOR "state" (Flip bits where the two numbers disagree.)
    // Take the current bits, compare them with "state", and flip where different.
    // The specific shift values (13, 17, 5) are chosen based on research to produce a good distribution of bits.
    state ^= state << 13; // shifting left by 1 is the same as multiplying by 2 (<< 2 multiplies by 4, etc.)
    state ^= state >> 17; // shifting right by 1 is the same as dividing by 2 (for unsigned integers).
    state ^= state << 5;  // shift left and mix again
    
	return state;
}

// Converts scrambled integer to float in [0,1]
float XorShiftGenerator::SetFastFloat()
{
    const uint32_t r = XorShift32(m_state);

	// Remove lowest 8 bits, scale to decimal (2^24 = 16777216)
    return (r >> 8) * static_cast<uint32_t>(1.0f / 16777216);
}

// Generate two floats for a point
Point XorShiftGenerator::Generate()
{
    return {.x = SetFastFloat(), .y = SetFastFloat() };
}