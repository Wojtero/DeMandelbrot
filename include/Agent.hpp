#pragma once

#include <vector>
#include <ostream>
#include "Mandelbrot.hpp"
#include "SwarmTypes.hpp"
#include "GeneratorHelper.hpp"
#include "GlobalParameters.hpp"

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

	double calculateAccuracy(const ValidationGrid& validationGrid, double tolerance = TOLERANCE);

	[[nodiscard]]
	double getLastAccuracy() const;

	void update(GeneratorHelper& generatorHelper, Mandelbrot::Complex globalBest, double inertia, double cognitive,
		double social, double globalBestWidth, double globalBestHeight);

	void randomize(const Bounds& bounds, GeneratorHelper& generatorHelper, int maxDivisor = MAX_DIVISOR);

	[[nodiscard]]
	const Solution& getSolution() const;

	friend std::ostream& operator<<(std::ostream& os, const Agent& agent);

  private:

	Solution solution {};

  	int widthControlPointsCount {};

  	int heightControlPointsCount {};

	double lastAccuracy {};

	double bestAccuracy {};

	Mandelbrot::Complex velocity {};

	Mandelbrot::Complex personalBest {};

	double widthVelocity {};

	double personalBestWidth {};

	double heightVelocity {};

	double personalBestHeight {};

	[[nodiscard]]
	std::vector<Mandelbrot::Complex> createGrid() const;
};
