#pragma once

#include "CImg.h"

namespace ImageIO
{
	/** One byte used in image processing. */
	using Byte = unsigned char;

	/** Image from bytes. */
	using Image = cimg_library::CImg<Byte>;
}
