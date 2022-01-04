#include "Swarm.hpp"
#include <cassert>
#include <iostream>
#include <execution>

Swarm::Swarm(int agentCount, int widthControlPointsCount, int heightControlPointsCount,
	const ImageIO::PixelMatrix& pixelMatrix, bool shouldRandomizeAgents)
	: agents(agentCount, Agent{Solution{}, widthControlPointsCount, heightControlPointsCount}),
	  widthControlPointsCount{widthControlPointsCount}, heightControlPointsCount{heightControlPointsCount}
{
	assert(agentCount >= 0);

	initializeValidationGrid(pixelMatrix);

	if (shouldRandomizeAgents)
	{
		randomizeAgents();
	}
}

void Swarm::randomizeAgents()
{
	for (auto& agent : agents)
	{
		GeneratorHelper generatorHelper {};
		agent.randomize(bounds, generatorHelper);
	}
}

void Swarm::update()
{
	if (!isGlobalBestInitialized) { initializeGlobalBest(); }

	std::for_each(std::execution::par, std::begin(agents), std::end(agents), [&](Agent& agent)
	{
		GeneratorHelper generatorHelper {};
		agent.update(generatorHelper, globalBest, inertia, cognitive, social);
	});

	validateAgents();
	sortAgentsBestToWorst();
	globalBest = agents.front().getSolution().center;
}

void Swarm::initializeValidationGrid(const ImageIO::PixelMatrix& pixelMatrix)
{
	const int widthStep = pixelMatrix.getWidth() / widthControlPointsCount;
	const int heightStep = pixelMatrix.getHeight() / heightControlPointsCount;

	for (int i = 0; i < widthControlPointsCount; ++i)
	{
		for (int j = 0; j < heightControlPointsCount; ++j)
		{
			validationGrid.emplace_back(pixelMatrix.at(i*widthStep, j*heightStep));
		}
	}
}

void Swarm::validateAgents()
{
	std::for_each(std::execution::par, std::begin(agents), std::end(agents), [&](Agent& agent)
	{
		agent.calculateAccuracy(validationGrid);
	});
}

void Swarm::sortAgentsWorstToBest()
{
	std::sort(std::execution::par, std::begin(agents), std::end(agents),
		[](const Agent& first, const Agent& second)
	{
		return first.getLastAccuracy() < second.getLastAccuracy();
	});
}

void Swarm::sortAgentsBestToWorst()
{
	std::sort(std::execution::par, std::begin(agents), std::end(agents),
		[](const Agent& first, const Agent& second)
		{
			return first.getLastAccuracy() > second.getLastAccuracy();
		});
}

void Swarm::print()
{
	std::cout << "[\n";

	for (const auto& agent : agents)
	{
		std::cout << agent.getLastAccuracy() * 100.0 << "% " << agent << '\n';
	}

	std::cout << "]\n";
}

const std::vector<Agent>& Swarm::getAgents() const
{
	return agents;
}

void Swarm::initializeGlobalBest()
{
	validateAgents();
	sortAgentsBestToWorst();
	globalBest = agents.begin()->getSolution().center;
	isGlobalBestInitialized = true;
}
