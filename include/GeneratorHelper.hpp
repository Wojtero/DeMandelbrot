#pragma once

#include <random>
#include <chrono>
#include <locale>
#include <codecvt>
#include <set>
#include <cassert>
#include <filesystem>
class GeneratorHelper
{
  public:
	auto randomNumbers(int length) -> std::string;
	auto randomBool() -> bool;
	auto randomDoubleBetween(double minInclusive, double maxExclusive) -> double;
	inline auto randomIntBetween(int minInclusive, int maxInclusive) -> int;

	template<typename T>
	const T& randomFrom(const std::vector<T>& vector)
	{
		assert(!vector.empty());
		return vector.at(randomIntBetween(0, vector.size() - 1));
	}

	template<typename T>
	T& randomFromMut(std::vector<T>& vector)
	{
		assert(!vector.empty());
		return vector.at(randomIntBetween(0, vector.size() - 1));
	}

  private:
	std::default_random_engine randomEngine {std::random_device{}()};
};
