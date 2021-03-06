#pragma once

#include <vector>
#include "ImageIO/ImageIOTypes.hpp"
#include <iostream>

namespace ImageIO
{
	/**
	 * Grayscale image as pixel matrix.
	 */
	class PixelMatrix
	{
	  public:

		PixelMatrix() = delete;

		PixelMatrix(int width, int height);

		explicit PixelMatrix(const Image& image);

		PixelMatrix(const PixelMatrix& pixelMatrix) = default;

		Byte& at(int x, int y);

		[[nodiscard]]
		Byte at(int x, int y) const;

		[[nodiscard]]
		int getWidth() const;

		[[nodiscard]]
		int getHeight() const;

		[[nodiscard]]
		const std::vector<Byte>& getPixels() const;

		[[nodiscard]]
		Image toImage() const;

		void binarize();

		friend std::ostream& operator<<(std::ostream& out, const PixelMatrix& matrix);

	  private:

		int width {};

		int height {};

		std::vector<Byte> pixels {};

	};
}
