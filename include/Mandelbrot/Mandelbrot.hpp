#pragma once

#include <complex>
#include "ImageIO/PixelMatrix.hpp"
#include "GlobalParameters.hpp"

namespace Mandelbrot
{
	using Complex = std::complex<double>;

	auto createScaler(int minFrom, int maxFrom, double minTo, double maxTo);

	template<typename A, typename B>
	auto scaledComplex(A scalerX, B scalerY)
	{
		return [=](int x, int y)
		{
			return Complex{scalerX(x), scalerY(y)};
		};
	}

	int calculateMandelbrotIterations(Complex complex, int maxIterations);

	ImageIO::PixelMatrix createMandelbrotImage(double reMin, double imMin, double reMax, double imMax);

	ImageIO::Byte createMandelbrotPixel(Complex complex, int maxIterations);
}
