//ProjectFilter(CommandLine)
#pragma once
#include <map>

class SC_CommandLine
{
public:
	static bool Init(char** aArgsV, int aArgsC);
	static void Destroy();
	static bool HasCommand(const char* aCommand);
	static bool HasArgument(const char* aCommand, const char* aArg);

private:
	SC_CommandLine(char** aArgsV, int aArgsC);
	~SC_CommandLine();

	std::map<std::string, std::vector<std::string>> mCommands;

	static SC_CommandLine* gInstance;
};

