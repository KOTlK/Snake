#include "Random.h"

#include <random>

int randomInt(const int& start, const int& end)
{
    std::random_device device;
    std::mt19937 generator(device());
    auto distribution = std::uniform_int_distribution<std::mt19937::result_type>(start, end);

    return distribution(generator);
}
