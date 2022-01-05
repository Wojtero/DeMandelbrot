#pragma once

#include <string_view>
#include <vector>
#include <CImg.h>
#include "ImageIOTypes.hpp"
#include <optional>
#include <filesystem>
#include "Swarm/SwarmTypes.hpp"

struct Solution;

namespace ImageIO
{
	Image loadImage(std::string_view pathToImage);

	void saveImage(const Image& image, std::string_view pathToImage);

	Image toGrayscale(const Image& image);

	void saveMandelbrot(std::string_view pathToImage, const Bounds& bounds);

	void printSolution(const Solution& solution, int time);

	void saveText(std::string_view pathToText, const Solution& solution, int time);

	std::string filenameNoExtension(std::optional<std::filesystem::path> file);
}
