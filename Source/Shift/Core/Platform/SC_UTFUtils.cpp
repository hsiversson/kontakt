//ProjectFilter(String)
#include "Platform_Precompiled.h"
#include "SC_UTFUtils.h"
#include "SC_Relocate.h"

#include <locale>
#include <codecvt>
#include <algorithm>

namespace SC_UTF
{
	bool ToUTF8(char* aDestination, uint32& aDestinationLength, const wchar_t* aSourceString, uint32 aSourceStringLength)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		const std::wstring wstr = std::wstring(aSourceString, aSourceStringLength);
		const std::string str = converter.to_bytes(wstr);

		SC_Memcpy(aDestination, str.c_str(), sizeof(char)*aDestinationLength);

		return true;
	}

	bool ToUTF8(std::string& aDestination, const wchar_t* aSourceString, uint32 aSourceStringLength)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		const std::wstring wstr = std::wstring(aSourceString, aSourceStringLength);
		aDestination = converter.to_bytes(wstr);
		return true;
	}

	bool ToUTF8(std::string& aDestination, const std::wstring& aSource)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		aDestination = converter.to_bytes(aSource);
		return true;
	}

	std::string ToUTF8(const std::wstring& aSource)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.to_bytes(aSource);
	}

	bool ToUTF16(wchar_t* aDestination, uint32& aDestinationLength, const char* aSourceString, uint32 aSourceStringLength)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		const std::string str = std::string(aSourceString, aSourceStringLength);
		const std::wstring wstr = converter.from_bytes(str);

		SC_Memcpy(aDestination, wstr.c_str(), sizeof(wchar_t)*aDestinationLength);

		return true;
	}

	bool ToUTF16(std::wstring& aDestination, const char* aSourceString, uint32 aSourceStringLength)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		const std::string str = std::string(aSourceString, aSourceStringLength);
		aDestination = converter.from_bytes(str);
		return true;
	}
	bool ToUTF16(std::wstring& aDestination, const std::string& aSource)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		aDestination = converter.from_bytes(aSource);
		return true;
	}
	std::wstring ToUTF16(const std::string& aSource)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(aSource);
	}
}