#pragma once
#include <filesystem>

namespace SC_Path
{
	static std::string Normalize(const std::string& aPath);

	static bool IsAbsolute(const std::string& aPath);
	static bool IsRelative(const std::string& aPath);
	static std::string MakeAbsolute(const std::string& aPath);
}

