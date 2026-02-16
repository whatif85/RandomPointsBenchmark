#include <algorithm>
#include <chrono>
#include <iostream>

#include "MTGenerator.h"
#include "XorShiftGenerator.h"


// constexpr means:
// This value must be known at compile time.
// The compiler replaces it directly in the code.
constexpr std::uint64_t ITERATIONS = 200'000'000ULL; // unsigned long long literal (64-bit integer)

// Generic Benchmark function.
// It works with ANY class that has Generate().
template<typename Generator>
static void Benchmark(const char* name)
{
    Generator gen;

    // volatile prevents compiler from deleting our loop.
    volatile float sink = 0.0f;

    const auto start = std::chrono::high_resolution_clock::now();

    for (std::uint64_t i = 0; i < ITERATIONS; ++i)
    {
        const Point p = gen.Generate();
        sink += p.x * p.y;
    }    

    const auto end = std::chrono::high_resolution_clock::now();

    // Compute elapsed time in seconds
    double elapsedSec = std::chrono::duration<double>(end - start).count();

    // Safety check: prevent division by zero if the loop was extremely fast
    elapsedSec = std::max(elapsedSec, 1e-9);

    std::cout << name << "\n";
    std::cout << "Time: " << elapsedSec << " seconds\n";
    std::cout << "Throughput: " << static_cast<double>(ITERATIONS) / elapsedSec << " points/sec\n";
    std::cout << "Checksum: " << sink << "\n\n";
}

int main()
{
    Benchmark<MTGenerator>("Mersenne Twister");
    Benchmark<XorShiftGenerator>("Xor Shift 32-Bit");

    return 0;
}