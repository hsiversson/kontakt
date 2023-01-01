//ProjectFilter(CommandLine)
#pragma once
#include <map>

class SC_CommandLine
{
public:
	static bool Init(char** aArgsV, int aArgsC);
	static void Destroy();

	static bool HasArgument(const char* aArg);

	static bool GetIntValue(const char* aArg, int& aReturnValue, int aIndex = 0);
	static bool GetFloatValue(const char* aArg, float& aReturnValue, int aIndex = 0);

private:
	SC_CommandLine(char** aArgsV, int aArgsC);
	~SC_CommandLine();

	struct ArgumentInfo
	{
		std::string mArgument;
		SC_Array<std::string> mValues;
	};
	SC_Array<ArgumentInfo> mArguments;

	static SC_CommandLine* gInstance;
};

