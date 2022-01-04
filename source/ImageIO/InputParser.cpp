#include "ImageIO/InputParser.hpp"

namespace ImageIO
{
	auto InputParser::parseInput(const int argc, char* argv[]) const
		-> std::optional<std::filesystem::path>
	{
		if (argc != expectedArgumentCount)
		{
			return std::nullopt;
		}

		std::filesystem::path result {};

		std::filesystem::path pathToInput {argv[1]};
		if (!std::filesystem::exists(pathToInput)) { return std::nullopt; }
		result = pathToInput;

		return {result};
	}
}
