#pragma once

#include <vector>
#include <ostream>
#include "Mandelbrot/Mandelbrot.hpp"
#include "SwarmTypes.hpp"
#include "GeneratorHelper.hpp"
#include "GlobalParameters.hpp"

/** Result of algorithm. */
struct Solution
{
	Mandelbrot::Complex center {};

	double width {};

	double height {};

	[[nodiscard]]
	double reMin() const;

	[[nodiscard]]
	double imMin() const;

	[[nodiscard]]
	double reMax() const;

	[[nodiscard]]
	double imMax() const;

	[[nodiscard]]
	std::string stringSolution() const;

	friend std::ostream& operator<<(std::ostream& os, const Solution& solution);
};

/** Agent that holds solution and moves as a result of PSO. */
class Agent
{
  public:

	Agent() = default;

	Agent(Solution solution, int widthControlPointsCount, int heightControlPointsCount);

	double calculateAccuracy(const ValidationGrid& validationGrid, double tolerance = TOLERANCE);

	[[nodiscard]]
	double getLastAccuracy() const;

	void update(GeneratorHelper& generatorHelper, Mandelbrot::Complex globalBest, double inertia, double cognitive,
		double social, double globalBestWidth, double globalBestHeight, const ValidationGrid& validationGrid);

	void randomize(const Bounds& bounds, GeneratorHelper& generatorHelper, int maxDivisor = MAX_DIVISOR);

	void inGrid(Mandelbrot::Complex position, double width, double height, GeneratorHelper& generatorHelper);

	[[nodiscard]]
	const Solution& getSolution() const;

	[[nodiscard]]
	std::string stringAgent() const;

	friend std::ostream& operator<<(std::ostream& os, const Agent& agent);

  private:

	Solution solution {};

  	int widthControlPointsCount {};

  	int heightControlPointsCount {};

	double lastAccuracy {};

	double bestAccuracy {};

	Mandelbrot::Complex velocity {};

	Mandelbrot::Complex personalBestPosition {};

	double widthVelocity {};

	double personalBestWidth {};

	double heightVelocity {};

	double personalBestHeight {};

	[[nodiscard]]
	std::vector<Mandelbrot::Complex> createGrid() const;
};
