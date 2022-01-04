#include "ImageIO/InputParser.hpp"

namespace ImageIO
{
	auto InputParser::parseInput(const int argc, char* argv[]) const
		-> std::optional<std::vector<std::filesystem::path>>
	{
		if (argc != expectedArgumentCount)
		{
			return std::nullopt;
		}

		std::vector<std::filesystem::path> result {};

		std::filesystem::path pathToInput {argv[1]};
		if (!std::filesystem::exists(pathToInput)) { return std::nullopt; }
		result.emplace_back(pathToInput);

		std::filesystem::path pathToOutput {argv[2]};
		result.emplace_back(pathToOutput);

		return {result};
	}
}
