#include "Swarm/Swarm.hpp"
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
		agent.update(generatorHelper, globalBestPosition, inertia, cognitive, social,
			globalBestWidth, globalBestHeight, validationGrid);
	});

	const auto best = findBest();

	if (best.getLastAccuracy() > bestAccuracy)
	{
		globalBestPosition = best.getSolution().center;
		bestAccuracy = best.getLastAccuracy();
		globalBestWidth = best.getSolution().width;
		globalBestHeight = best.getSolution().height;
		bestAgent = best;
	}
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
		std::cout << agent.stringAgent() << '\n';
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

	globalBestPosition = agents.begin()->getSolution().center;
	bestAccuracy = agents.begin()->getLastAccuracy();
	globalBestWidth = agents.begin()->getSolution().width;
	globalBestHeight = agents.begin()->getSolution().height;
	bestAgent = *agents.begin();
	isGlobalBestInitialized = true;
}

Agent Swarm::findBest() const
{
	auto best = std::max_element(std::execution::par, std::begin(agents), std::end(agents),
		[](const Agent& largest, const Agent& next)
	{
		return next.getLastAccuracy() > largest.getLastAccuracy();
	});

	return *best;
}

void Swarm::compute(std::chrono::time_point<std::chrono::high_resolution_clock> startTime, int maxMilis)
{
	int iterationBatch = 0;
	int iterationCount = 0;
	const int iterationTiersCount = static_cast<int>(iterationTiers.size());

	while(static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>
	    (std::chrono::high_resolution_clock::now() - startTime).count()) < maxMilis
		&& bestAccuracy < ACCURACY_THRESHOLD)
	{
		update();

		if constexpr (OPTIMIZE_LOOP)
		{
			if (iterationBatch < iterationTiersCount && iterationCount > iterationTiers.at(iterationBatch).first)
			{
				sortAgentsBestToWorst();
				agents.resize(std::size_t(agents.size() * iterationTiers.at(iterationBatch).second));
				++iterationBatch;
			}
			++iterationCount;
		}
	}

	sortAgentsBestToWorst();
}

Agent Swarm::getBestAgent() const
{
	return bestAgent;
}
