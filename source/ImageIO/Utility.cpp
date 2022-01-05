#include "ImageIO/Utility.hpp"

#include <cassert>
#include <iostream>
#include <fstream>
#include <execution>
#include <iomanip>
#include "Mandelbrot/Mandelbrot.hpp"
#include "Swarm/Agent.hpp"

namespace ImageIO
{
	Image loadImage(std::string_view pathToImage)
	{
		return Image{pathToImage.data()};
	}

	void saveImage(const Image& image, std::string_view pathToImage)
	{
		image.save(pathToImage.data());
	}

	Image toGrayscale(const Image& image)
	{
		assert(image.spectrum() >= 3);

		auto calculateGray = [](Byte red, Byte green, Byte blue) -> Byte
		{
			const auto [redWeight, greenWeight, blueWeight]
				= std::tuple{0.299f, 0.587f, 0.114f};

			const float weightedRed = redWeight * static_cast<float>(red);
			const float weightedGreen = greenWeight * static_cast<float>(green);
			const float weightedBlue = blueWeight * static_cast<float>(blue);

			return static_cast<Byte>(weightedRed + weightedGreen + weightedBlue);
		};

		Image grayImage (image.width(), image.height());

		const int redIndex = 0;
		const int greenIndex = 1;
		const int blueIndex = 2;

		cimg_forXYZ(grayImage, x, y, z)
		{
			grayImage.atXY(x, y) = calculateGray(image(x, y, z, redIndex),
				image(x, y, z, greenIndex),
				image(x, y, z, blueIndex));
		}

		return grayImage;
	}

	void saveMandelbrot(std::string_view pathToImage, const Bounds& bounds)
	{
		auto mandelbrot = Mandelbrot::createMandelbrotImage(bounds.reMin, bounds.imMin,
			bounds.reMax, bounds.imMax);
		saveImage(mandelbrot.toImage(), pathToImage);
	}

	void printSolution(const Solution& solution, int time)
	{
		std::cout << std::setprecision(5);
		std::cout << "ReMin: " << solution.reMin() << '\n';
		std::cout << "ImMin: " << solution.imMin() << '\n';
		std::cout << "ReMax: " << solution.reMax() << '\n';
		std::cout << "ImMax: " << solution.imMax() << '\n';
		std::cout << time;
	}

	void saveText(std::string_view pathToText, const Solution& solution, int time)
	{
		std::ofstream fileStream {pathToText};
		fileStream << std::setprecision(5);
		fileStream << solution.reMin() << '\n';
		fileStream << solution.reMax() << '\n';
		fileStream << solution.imMin() << '\n';
		fileStream << solution.imMax() << '\n';
		fileStream << time;
	}

	std::string filenameNoExtension(std::optional<std::filesystem::path> file)
	{
		return file->filename().string().substr(0, file->filename().string().find_last_of('.'));
	}
}
