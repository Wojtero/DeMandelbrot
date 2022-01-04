#pragma once

using ValidationGrid = std::vector<ImageIO::Byte>;

struct Bounds
{
	double reMin = -1.0;
	double imMin = -1.0;
	double reMax = 1.0;
	double imMax = 1.0;
};
