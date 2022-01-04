#include <iostream>
#include <chrono>
#include "Mandelbrot.hpp"
#include "ImageIO.hpp"
#include "Swarm.hpp"

int main(int argc, char* argv[])
{
	using namespace Mandelbrot;
	using namespace ImageIO;

	auto tic = std::chrono::high_resolution_clock::now();

	auto files = InputParser{}.parseInput(argc, argv);

	if (!files.has_value())
	{
		std::cout << "Usage: DeMandelbrot <pathToInput> <pathToOutput>\n";
		return 1;
	}

	auto image = loadImage(files.value().at(0).string());
	PixelMatrix pixelMatrix(image);
//	pixelMatrix.binarize();

	Swarm swarm {100, 30, 30, pixelMatrix};

	for (int i = 0; i < 10; ++i)
	{
		swarm.update();
	}

	swarm.print();

//	auto mandelbrot = createMandelbrotImage(-0.56671, 0.53432, -0.16671, 0.93432);
//	mandelbrot.binarize();
//	saveImage(mandelbrot.toImage(), files.value().at(1).string());
//	saveImage(pixelMatrix.toImage(), "../output/cos.png");
//
//	for (int i = -2; i < 3; ++i)
//	{
//		for (int j = -2; j < 3; ++j)
//		{
//			saveMandelbrot("../test/man_" + std::to_string(i) + '_' + std::to_string(j) + ".png",
//				-0.56671 + 0.02*i,
//				0.53432 + 0.02*j,
//				-0.16671 + 0.02*i,
//				0.93432 + 0.02*j);
//		}
//	}

	auto toc = std::chrono::high_resolution_clock::now();

	auto msInt = std::chrono::duration_cast<std::chrono::milliseconds>(toc - tic);

	/* Getting number of milliseconds as a double. */
	std::chrono::duration<double, std::milli> msDouble = toc - tic;

	std::cout << '\n';
	std::cout << msInt.count() << "ms\n";
	std::cout << msDouble.count() << "ms\n";

	auto winner = swarm.getAgents().front().getSolution();
	saveMandelbrot("../output/winner4.png",
		winner.reMin(), winner.imMin(), winner.reMax(), winner.imMax());

	return 0;
}
