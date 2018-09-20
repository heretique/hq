#include "Hq/Rng.h"

#include <ctime>
#include <random>

namespace hq
{
static auto                                  seed = time(nullptr);
static std::mt19937                          gRng(seed);
static std::uniform_real_distribution<float> gDistribution;

float rand01()
{
    return gDistribution(gRng);
}
}  // namespace hq
