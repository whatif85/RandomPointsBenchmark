#include <chrono>
#include <iostream>
#include <random>
#include <cstdint>

struct Point
{
    float x;
    float y;
};

int main()
{
    using clock = std::chrono::high_resolution_clock;

    constexpr std::uint64_t iterations = 200'000'000ULL;

    // Fast PRNG (Mersenne Twister is good compromise speed/quality)
    std::mt19937 rng(123456);
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    volatile float sink = 0.0f; // Prevent optimization removal

    auto start = clock::now();

    for (std::uint64_t i = 0; i < iterations; ++i)
    {
        Point p;
        p.x = dist(rng);
        p.y = dist(rng);

        // Minimal work to avoid full optimization away
        sink += p.x * p.y;
    }

    auto end = clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Generated " << iterations << " points\n";
    std::cout << "Time: " << elapsed.count() << " seconds\n";
    std::cout << "Throughput: "
        << static_cast<double>(iterations) / elapsed.count()
        << " points/sec\n";

    // Prevent compiler from removing sink
    std::cout << "Checksum: " << sink << "\n";

    return 0;
}