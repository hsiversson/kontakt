//ProjectFilter(File)
#pragma once
#include <filesystem>

namespace SC_Path
{
	std::string Normalize(const std::string& aPath);

	bool IsAbsolute(const std::string& aPath);
	bool IsRelative(const std::string& aPath);
	std::string MakeAbsolute(const std::string& aPath);
}

