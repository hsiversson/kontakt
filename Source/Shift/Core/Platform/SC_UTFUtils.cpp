//ProjectFilter(String)
#include "Platform_Precompiled.h"
#include "SC_UTFUtils.h"

namespace SC_UTF
{
	bool ToUTF8(char* /*aDestination*/, uint32& /*aDestinationLength*/, const wchar_t* /*aSourceString*/, uint32 /*aSourceStringLength*/)
	{
		return false;
	}

	bool ToUTF8(std::string& /*aDestination*/, const wchar_t* /*aSourceString*/, uint32 /*aSourceStringLength*/)
	{
		return false;
	}

	bool ToUTF16(wchar_t* /*aDestination*/, uint32& /*aDestinationLength*/, const char* /*aSourceString*/, uint32 /*aSourceStringLength*/)
	{
		return false;
	}

	bool ToUTF16(std::wstring& /*aDestination*/, const char* /*aSourceString*/, uint32 /*aSourceStringLength*/)
	{
		return false;
	}
}