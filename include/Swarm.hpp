#pragma once

#include <vector>
#include "Agent.hpp"
#include "ImageIO/ImageIOTypes.hpp"
#include "ImageIO/PixelMatrix.hpp"
#include "SwarmTypes.hpp"

class Swarm
{
  public:

	Swarm(int agentCount, int widthControlPointsCount, int heightControlPointsCount,
		const ImageIO::PixelMatrix& pixelMatrix, bool shouldRandomizeAgents = true);

	void randomizeAgents();

	void update();

	void validateAgents();

	void sortAgentsWorstToBest();

	void sortAgentsBestToWorst();

	void print();

	void compute(std::chrono::time_point<std::chrono::steady_clock> startTime, int maxMilis = 9500);

	[[nodiscard]]
	std::tuple<Mandelbrot::Complex, double, double, double> findBest() const;

	[[nodiscard]]
	const std::vector<Agent>& getAgents() const;

  private:
	std::vector<Agent> agents {};

	int widthControlPointsCount {};

	int heightControlPointsCount {};

	Bounds bounds {};

	ValidationGrid validationGrid {};

	Mandelbrot::Complex globalBest {};

	double bestAccuracy {};

	bool isGlobalBestInitialized {};

	double inertia = 0.7;

	double cognitive = 0.5;

	double social = 0.5;

	double globalBestWidth {};

	double globalBestHeight {};

	void initializeGlobalBest();

	void initializeValidationGrid(const ImageIO::PixelMatrix& pixelMatrix);
};
