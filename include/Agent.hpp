#pragma once

#include <vector>
#include <ostream>
#include "Mandelbrot.hpp"
#include "SwarmTypes.hpp"
#include "GeneratorHelper.hpp"

struct Solution
{
	Mandelbrot::Complex center {};
	double width {};
	double height {};

	[[nodiscard]] double reMin() const;
	[[nodiscard]] double imMin() const;
	[[nodiscard]] double reMax() const;
	[[nodiscard]] double imMax() const;

	friend std::ostream& operator<<(std::ostream& os, const Solution& solution);
};

class Agent
{
  public:
	Agent() = default;
	Agent(Solution solution, int widthControlPointsCount, int heightControlPointsCount);
	double calculateAccuracy(const ValidationGrid& validationGrid, double tolerance = 0.05);
	[[nodiscard]] double getLastAccuracy() const;

	void update(GeneratorHelper& generatorHelper, Mandelbrot::Complex globalBest, double inertia, double cognitive,
		double social);

	void randomize(const Bounds& bounds, GeneratorHelper& generatorHelper, int maxDivisor = 100);

	[[nodiscard]] const Solution& getSolution() const;

	friend std::ostream& operator<<(std::ostream& os, const Agent& agent);

  private:
	Solution solution {};
  	int widthControlPointsCount {};
  	int heightControlPointsCount {};
	double lastAccuracy {};
	double bestAccuracy {};
	Mandelbrot::Complex velocity {};
	Mandelbrot::Complex personalBest {};

	[[nodiscard]] std::vector<Mandelbrot::Complex> createGrid() const;
};
