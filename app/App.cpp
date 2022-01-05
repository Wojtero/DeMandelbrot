#include <iostream>
#include <chrono>
#include "Mandelbrot/Mandelbrot.hpp"
#include "ImageIO.hpp"
#include "Swarm/Swarm.hpp"
#include "GlobalParameters.hpp"

#define DEVELOPMENT

const std::filesystem::path pathToOutput = "../output/";

int main(int argc, char* argv[])
{
	using namespace Mandelbrot;
	using namespace ImageIO;

	auto timeStart = std::chrono::high_resolution_clock::now();
	auto file = InputParser{}.parseInput(argc, argv);
	if (!file.has_value())
	{
		std::cout << "Usage: DeMandelbrot <pathToInput>\n";
		return 1;
	}

	auto image = loadImage(file->string());
	PixelMatrix pixelMatrix (image);

	Swarm swarm {AGENT_COUNT, WIDTH_CONTROL_POINTS_COUNT,
		HEIGHT_CONTROL_POINTS_COUNT, pixelMatrix};
	swarm.compute(timeStart);

	auto timeEnd = std::chrono::high_resolution_clock::now();
	auto time = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>
	    (timeEnd - timeStart).count());
	const auto& solution = swarm.getBestAgent().getSolution();

	saveText(filenameNoExtension(file) + ".txt", solution, time);

#ifdef DEVELOPMENT
	printSolution(solution, time);
	saveMandelbrot("../output/" + filenameNoExtension(file) + ".png",
		{solution.reMin(), solution.imMin(), solution.reMax(), solution.imMax()});
#endif

	return 0;
}
