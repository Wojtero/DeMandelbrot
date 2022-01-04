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
	[[nodiscard]] const std::vector<Agent>& getAgents() const;

  private:
	std::vector<Agent> agents {};
	int widthControlPointsCount {};
	int heightControlPointsCount {};
	Bounds bounds {};

	ValidationGrid validationGrid {};
	Mandelbrot::Complex globalBest {};
	bool isGlobalBestInitialized {};
	double inertia = 0.7;
	double cognitive = 0.5;
	double social = 0.5;

	void initializeGlobalBest();
	void initializeValidationGrid(const ImageIO::PixelMatrix& pixelMatrix);
};
