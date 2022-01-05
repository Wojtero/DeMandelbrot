#include "Swarm/GeneratorHelper.hpp"
#include <string>

auto GeneratorHelper::randomNumbers(int length) -> std::string
{
	std::string result {};
	for (int i = 0; i < length; ++i)
	{
		result += std::to_string(randomIntBetween(0, 9));
	}
	return result;
}

auto GeneratorHelper::randomBool() -> bool
{
	return std::bernoulli_distribution{}(randomEngine);
}

auto GeneratorHelper::randomDoubleBetween(double minInclusive, double maxExclusive) -> double
{
	return std::uniform_real<double>(minInclusive, maxExclusive)(randomEngine);
}

inline auto GeneratorHelper::randomIntBetween(int minInclusive, int maxInclusive) -> int
{
	return std::uniform_int_distribution(minInclusive, maxInclusive)(randomEngine);
}
