#include "ImageIO/Utility.hpp"

#include <cassert>
#include <iostream>
#include <execution>
#include "Mandelbrot.hpp"

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

	void saveMandelbrot(std::string_view pathToImage, double reMin, double imMin, double reMax, double imMax)
	{
		auto mandelbrot = Mandelbrot::createMandelbrotImage(reMin, imMin, reMax, imMax);
		saveImage(mandelbrot.toImage(), pathToImage);
	}
}
