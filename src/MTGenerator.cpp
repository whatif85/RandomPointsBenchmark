#include "MTGenerator.h"

// Constructor definition.
// We initialize:
// - m_rng with a fixed seed (so results are repeatable)
// - m_dist with a range [0.0, 1.0]
MTGenerator::MTGenerator() :
    m_rng(123456),
    m_dist(0.0f, 1.0f)
{}

// This function produces one random point.
// It asks the distribution for two numbers.
Point MTGenerator::Generate()
{
    return {.x = m_dist(m_rng), .y = m_dist(m_rng) };
}