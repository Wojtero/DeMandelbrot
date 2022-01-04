#include <iostream>
#include <chrono>
#include "Mandelbrot.hpp"
#include "ImageIO.hpp"
#include "Swarm.hpp"

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

	Swarm swarm {100, 5, 5, pixelMatrix};
	for (int i = 0; i < 100; ++i) { swarm.update(); }
	swarm.print();

	auto timeEnd = std::chrono::high_resolution_clock::now();
	auto time = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>
	    (timeEnd - timeStart).count());
	const auto& solution = swarm.getAgents().front().getSolution();

	printSolution(solution, time);
	saveText(filenameNoExtension(file) + ".txt", solution, time);
	saveMandelbrot("../output/" + filenameNoExtension(file) + ".png",
		solution.reMin(), solution.imMin(), solution.reMax(), solution.imMax());

	return 0;
}
