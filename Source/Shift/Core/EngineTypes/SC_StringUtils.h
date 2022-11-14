//ProjectFilter(String)
#pragma once

#include <string>
#include <string_view>
#include <format>


template<typename ... Args>
std::string SC_FormatStr(std::string_view aFormat, Args&&... aArgs)
{
	return std::vformat(aFormat, std::make_format_args(aArgs...));
}