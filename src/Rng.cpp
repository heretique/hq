#include "Hq/Rng.h"
#include "Hq/BasicTypes.h"

#include <ctime>
#include <random>

namespace hq
{
static auto                                  seed = time(nullptr);
static std::mt19937                          gRng(static_cast<uint>(seed));
static std::uniform_real_distribution<float> gDistribution;

float rand01()
{
    return gDistribution(gRng);
}

float randMinus11()
{
    return -1.f + 2.f * gDistribution(gRng);
}

}  // namespace hq
