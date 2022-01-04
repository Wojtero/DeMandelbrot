#pragma once

#include <vector>
#include <filesystem>

namespace ImageIO
{
	/**
	 * Parses user input.
	 * @remark Kind of self-explanatory.
	 */
	class InputParser
	{
	  public:

		auto parseInput(int argc, char* argv[]) const -> std::optional<std::filesystem::path>;

	  private:

		int expectedArgumentCount = 2;
	};
}
