//ProjectFilter(String)
#pragma once

#include "SC_TypeDefines.h"

#include <string>

namespace SC_UTF
{
	bool ToUTF8(char* aDestination, uint32& aDestinationLength, const wchar_t* aSourceString, uint32 aSourceStringLength);
	bool ToUTF8(std::string& aDestination, const wchar_t* aSourceString, uint32 aSourceStringLength);
	bool ToUTF8(std::string& aDestination, const std::wstring& aSource);
	std::string ToUTF8(const std::wstring& aSource);

	bool ToUTF16(wchar_t* aDestination, uint32& aDestinationLength, const char* aSourceString, uint32 aSourceStringLength);
	bool ToUTF16(std::wstring& aDestination, const char* aSourceString, uint32 aSourceStringLength);
	bool ToUTF16(std::wstring& aDestination, const std::string& aSource);
	std::wstring ToUTF16(const std::string& aSource);
}

