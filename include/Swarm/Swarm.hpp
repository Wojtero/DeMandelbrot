#pragma once

#include <vector>
#include "Swarm/Agent.hpp"
#include "ImageIO/ImageIOTypes.hpp"
#include "ImageIO/PixelMatrix.hpp"
#include "SwarmTypes.hpp"
#include "GlobalParameters.hpp"

/** Swarm of Agents looking for the best Solution. */
class Swarm
{
  public:

	Swarm(int agentCount, int widthControlPointsCount, int heightControlPointsCount,
		const ImageIO::PixelMatrix& pixelMatrix, bool shouldRandomizeAgents = true);

	Swarm(std::pair<int, int> agentsInWidthAndHeight, int widthControlPointsCount, int heightControlPointsCount,
		const ImageIO::PixelMatrix& pixelMatrix);

	void randomizeAgents();

	void agentsInGrid(int inWidth, int inHeight);

	void update();

	void validateAgents();

	void sortAgentsWorstToBest();

	void sortAgentsBestToWorst();

	void print();

	void compute(std::chrono::time_point<std::chrono::steady_clock> startTime, int maxMilis = MAX_MILIS);

	[[nodiscard]]
	Agent findBest() const;

	[[nodiscard]]
	const std::vector<Agent>& getAgents() const;

	[[nodiscard]]
	Agent getBestAgent() const;

  private:

	std::vector<Agent> agents {};

	int widthControlPointsCount {};

	int heightControlPointsCount {};

	Bounds bounds {};

	ValidationGrid validationGrid {};

	Mandelbrot::Complex globalBestPosition {};

	double bestAccuracy {};

	bool isGlobalBestInitialized {};

	double inertia = INERTIA;

	double cognitive = COGNITIVE;

	double social = SOCIAL;

	double globalBestWidth {};

	double globalBestHeight {};

	Agent bestAgent {};

	std::vector<std::pair<int, double>> iterationTiers =
	{
		{5, 0.8},
		{10, 0.6},
		{20, 0.4}
	};

	void initializeGlobalBest();

	void initializeValidationGrid(const ImageIO::PixelMatrix& pixelMatrix);
};
