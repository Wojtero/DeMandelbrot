#include "ImageIO/PixelMatrix.hpp"
#include <cassert>
#include <execution>

namespace ImageIO
{
	PixelMatrix::PixelMatrix(const Image& image) : width{image.width()}, height{image.height()},
		pixels{std::begin(image), std::end(image)}
	{
		assert(image.spectrum() == 1);
	}

	PixelMatrix::PixelMatrix(int width, int height)
		: width(width), height(height) 
	{
		pixels.assign(width * height, 0); // Fill with zeroes
	}

	Byte& PixelMatrix::at(int x, int y)
	{
		return pixels.at(x + width * y);
	}

	Byte PixelMatrix::at(int x, int y) const
	{
		return pixels.at(x + width * y);
	}

	int PixelMatrix::getWidth() const
	{
		return width;
	}

	int PixelMatrix::getHeight() const
	{
		return height;
	}

	const std::vector<Byte>& PixelMatrix::getPixels() const
	{
		return pixels;
	}

	Image PixelMatrix::toImage() const
	{
		Image image (width, height);

		cimg_forXY(image, x, y)
		{
			image.atXY(x, y) = at(x, y);
		}

		return image;
	}

	std::ostream& operator<<(std::ostream& out, const PixelMatrix& matrix)
	{
		for (int y = 0; y < matrix.getHeight(); y++)
		{
			for (int x = 0; x < matrix.getWidth(); x++)
			{
				Byte value = matrix.at(x, y);
				out << (int)value << " ";
			}
			out << std::endl;
		}

		return out;
	}

	void PixelMatrix::binarize()
	{
		std::for_each(std::execution::par, std::begin(pixels), std::end(pixels),
			[](auto& byte)
		{
			const auto middle = std::numeric_limits<Byte>::max()/2;
			byte = byte > middle ? std::numeric_limits<Byte>::max() : 0;
		});
	}
}
