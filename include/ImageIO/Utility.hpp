#pragma once

#include <string_view>
#include <vector>
#include <CImg.h>
#include "ImageIOTypes.hpp"

namespace ImageIO
{
	Image loadImage(std::string_view pathToImage);

	void saveImage(const Image& image, std::string_view pathToImage);

	Image toGrayscale(const Image& image);

	void saveMandelbrot(std::string_view pathToImage, double reMin, double imMin, double reMax, double imMax);
}
