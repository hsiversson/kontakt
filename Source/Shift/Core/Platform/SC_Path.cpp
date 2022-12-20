#include "Platform_Precompiled.h"
#include "SC_Path.h"

std::string SC_Path::Normalize(const std::string& aPath)
{
	std::filesystem::path p = std::filesystem::weakly_canonical(aPath);
	return p.make_preferred().string();
}

bool SC_Path::IsAbsolute(const std::string& aPath)
{
	std::filesystem::path p(aPath);
	return p.is_absolute();
}

bool SC_Path::IsRelative(const std::string& aPath)
{
	std::filesystem::path p(aPath);
	return p.is_relative();
}

std::string SC_Path::MakeAbsolute(const std::string& aPath)
{
	std::filesystem::path absPath = std::filesystem::absolute(aPath);
	return absPath.make_preferred().string();
}
