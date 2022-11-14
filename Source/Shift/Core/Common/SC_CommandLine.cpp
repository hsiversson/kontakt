#include "Common_Precompiled.h"
#include "SC_CommandLine.h"

SC_CommandLine* SC_CommandLine::gInstance = nullptr;

bool SC_CommandLine::Init(char** aArgsV, int aArgsC)
{
	if (!gInstance)
		gInstance = new SC_CommandLine(aArgsV, aArgsC);
	
	return true;
}

void SC_CommandLine::Destroy()
{
	delete gInstance;
	gInstance = nullptr;
}

bool SC_CommandLine::HasCommand(const char* aCommand)
{
	if (!gInstance)
		return false;

	auto& commands = gInstance->mCommands;
	if (commands.find(aCommand) != commands.end())
		return true;

	return false;
}

bool SC_CommandLine::HasArgument(const char* aCommand, const char* aArg)
{
	if (!gInstance)
		return false;

	auto& commands = gInstance->mCommands;
	if (commands.find(aCommand) != commands.end())
	{
		for (decltype(commands.begin()->second)::size_type index(0); index < commands[aCommand].size(); ++index)
		{
			if (commands[aCommand][index] == aArg)
				return true;
		}
	}

	return false;
}

SC_CommandLine::SC_CommandLine(char** aArgsV, int aArgsC)
{
	char** args = aArgsV;
	int32 numArgs = aArgsC;

	std::string lastCommandEntered;

	for (int32 i = 0; i < numArgs; ++i)
	{
		std::string arg(args[i]);
		if (!arg.empty())
		{
			if (arg.front() != '-')
			{
				mCommands[lastCommandEntered].push_back(arg);
			}
			else
			{
				if (mCommands.find(arg) == mCommands.end())
				{
					arg = std::string(arg.begin() + 1, arg.end());
					mCommands[arg];
					lastCommandEntered = arg;
				}
			}
		}
	}
}

SC_CommandLine::~SC_CommandLine()
{

}

