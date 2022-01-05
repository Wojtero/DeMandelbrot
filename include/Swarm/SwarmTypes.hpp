#pragma once

/** Grid with values for points that can be used to validate Agent's Solution. */
using ValidationGrid = std::vector<ImageIO::Byte>;

/** Bounds of the area of Mandelbrot searching. */
struct Bounds
{
	double reMin = -1.0;

	double imMin = -1.0;

	double reMax = 1.0;

	double imMax = 1.0;
};
