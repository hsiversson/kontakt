//ProjectFilter(String)
#pragma once
#include <string>

class SC_String
{
public:
	SC_String();
	SC_String(const char* aStr);
	SC_String(const std::string& aStr);
	SC_String(const SC_String& aStr);
	SC_String(SC_String&& aStr);
	~SC_String();

	SC_SizeT Length() const;

	void Append();

private:
	std::string mNativeString;
};

