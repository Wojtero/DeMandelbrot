#include "../include/Mandelbrot.hpp"

#include <future>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <iostream>
#include <execution>

namespace Mandelbrot
{
	auto createScaler(int minFrom, int maxFrom, double minTo, double maxTo)
	{
		const int wFrom = maxFrom - minFrom;
		const double wTo = maxTo - minTo;
		const int midFrom = (maxFrom - minFrom) / 2 + minFrom;
		const double midTo = (maxTo - minTo) / 2.0 + minTo;

		return [=](int from)
		{
			return double(from - midFrom) / wFrom * wTo + midTo;
		};
	}

	int calculateMandelbrotIterations(Complex complex, const int maxIterations)
	{
		Complex z {};
		int iterations = 0;
		while (std::abs(z) < 2 && iterations < maxIterations)
		{
			++iterations;
			z = std::pow(z, 2) + complex;
		}
		return iterations;
	}

	ImageIO::PixelMatrix createMandelbrotImage(double reMin, double imMin, double reMax, double imMax)
	{
		using namespace ImageIO;

		const int width = 400;
		const int height = 400;

		PixelMatrix pixelMatrix (width, height);

		auto scale = scaledComplex(
			createScaler(0, width, reMin, reMax),
			createScaler(0, height, imMin, imMax));
		auto iToXY = [=](int i) { return scale(i % width, i / width); };
		auto toIterationCount = [=](int i, int maxIterations = 255)
			{ return calculateMandelbrotIterations(iToXY(i), maxIterations); };

		std::vector<int> vec (width * height);
		std::iota(std::begin(vec), std::end(vec), 0);

		std::for_each(std::execution::par, std::begin(vec), std::end(vec), [&](int num)
		{
			const int maxIterations = 100;
			int iterationCount = toIterationCount(num, maxIterations);
			Byte scaledCount = Byte((float(iterationCount)/float(maxIterations)) * 255.f);
			pixelMatrix.at(num % width, num / width)
				= Byte(255) - scaledCount;
		});

		return pixelMatrix;
	}

	ImageIO::Byte createMandelbrotPixel(Complex complex, const int maxIterations)
	{
		return std::numeric_limits<ImageIO::Byte>::max()
			- (ImageIO::Byte((float(calculateMandelbrotIterations(complex, maxIterations))
			/ float(maxIterations)) * 255.f));
	}
}
