#include "Swarm/Agent.hpp"
#include "ImageIO/ImageIOTypes.hpp"

double Solution::reMin() const
{
	return center.real() - (width/2.0);
}

double Solution::imMin() const
{
	return center.imag() - (height/2.0);
}

double Solution::reMax() const
{
	return center.real() + (width/2.0);
}

double Solution::imMax() const
{
	return center.imag() + (height/2.0);
}

std::string Solution::stringSolution() const
{
	return "{ReMin: " + std::to_string(reMin()) + " ImMin: " + std::to_string(imMin()) + " ReMax: "
		+ std::to_string(reMax()) + " ImMax: " + std::to_string(imMax()) + '}';
}

std::ostream& operator<<(std::ostream& os, const Solution& solution)
{
	os << "{center: " << solution.center << " width: " << solution.width << " height: " << solution.height << '}';
	return os;
}

Agent::Agent(Solution solution, int widthControlPointsCount, int heightControlPointsCount)
	: solution{solution}, widthControlPointsCount{widthControlPointsCount},
	  heightControlPointsCount{heightControlPointsCount}, personalBestPosition{solution.center},
	  personalBestWidth{solution.width}, personalBestHeight{solution.height} {}

double Agent::calculateAccuracy(const ValidationGrid& validationGrid, double tolerance)
{
	const auto grid = createGrid();

	assert(validationGrid.size() == grid.size());

	int correctCount = 0;
	const int pointsCount = static_cast<int>(grid.size());

	for (int i = 0; i < pointsCount; ++i)
	{
		const auto result = Mandelbrot::createMandelbrotPixel(grid.at(i),
			MAX_ITERATIONS);
		const auto expected = validationGrid.at(i);
		const double error = std::abs(double(result) - double(expected))
			/ double(std::numeric_limits<ImageIO::Byte>::max());

		if (error < tolerance)
		{
			++correctCount;
		}
	}

	double accuracy = double(correctCount) / double(pointsCount);
	lastAccuracy = accuracy;

	if (accuracy > bestAccuracy)
	{
		bestAccuracy = accuracy;
		personalBestPosition = solution.center;
		personalBestWidth = solution.width;
		personalBestHeight = solution.height;
	}

	return accuracy;
}

double Agent::getLastAccuracy() const
{
	return lastAccuracy;
}

std::vector<Mandelbrot::Complex> Agent::createGrid() const
{
	std::vector<Mandelbrot::Complex> grid {};

	const double widthStep = solution.width / static_cast<double>(widthControlPointsCount);
	const double heightStep = solution.height / static_cast<double>(heightControlPointsCount);

	const double reMin = solution.reMin();
	const double imMin = solution.imMin();

	for (int i = 0; i < widthControlPointsCount; ++i)
	{
		for (int j = 0; j < heightControlPointsCount; ++j)
		{
			grid.emplace_back(reMin + double(i) * widthStep, imMin + double(j) * heightStep);
		}
	}

	return grid;
}

void Agent::randomize(const Bounds& bounds, GeneratorHelper& generatorHelper, int maxDivisor)
{
	solution.width = 2.0/double(generatorHelper.randomIntBetween(1, maxDivisor));
	solution.height = 2.0/double(generatorHelper.randomIntBetween(1, maxDivisor));
	solution.center = {generatorHelper.randomDoubleBetween(bounds.reMin + (solution.width/2.0),
		bounds.reMax - (solution.width/2.0)),
		generatorHelper.randomDoubleBetween(bounds.imMin + (solution.height/2.0),
			bounds.imMax - (solution.height/2.0))};
}

void Agent::update(GeneratorHelper& generatorHelper, Mandelbrot::Complex globalBest, double inertia, double cognitive,
	double social, double globalBestWidth, double globalBestHeight, const ValidationGrid& validationGrid)
{
	velocity = inertia * velocity
		+ generatorHelper.randomDoubleBetween(0.0, 1.0)
			* cognitive * (personalBestPosition - solution.center)
		+ generatorHelper.randomDoubleBetween(0.0, 1.0)
		* social * (globalBest - solution.center);
	solution.center += velocity;

	widthVelocity = inertia * widthVelocity
		+ generatorHelper.randomDoubleBetween(0.0, 1.0)
			* cognitive * (personalBestWidth - solution.width)
		+ generatorHelper.randomDoubleBetween(0.0, 1.0)
			* social * (globalBestWidth - solution.width);
	solution.width += widthVelocity;

	heightVelocity = inertia * heightVelocity
		+ generatorHelper.randomDoubleBetween(0.0, 1.0)
			* cognitive * (personalBestHeight - solution.height)
		+ generatorHelper.randomDoubleBetween(0.0, 1.0)
			* social * (globalBestHeight - solution.height);
	solution.height += heightVelocity;

	calculateAccuracy(validationGrid);
}

const Solution& Agent::getSolution() const
{
	return solution;
}

std::string Agent::stringAgent() const
{
	return "(" + std::to_string(lastAccuracy * 100.0) + "%) " + solution.stringSolution();
}

std::ostream& operator<<(std::ostream& os, const Agent& agent)
{
	os << "{solution: " << agent.solution << " widthControlPointsCount: " << agent.widthControlPointsCount
		<< " heightControlPointsCount: " << agent.heightControlPointsCount << " (ReMin: " << agent.solution.reMin()
		<< " ImMin: " << agent.solution.imMin() << " ReMax: " << agent.solution.reMax() << " ImMax: "
		<< agent.solution.imMax() << ")}";
	return os;
}
