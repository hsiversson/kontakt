//ProjectFilter(CommandLine)
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

bool SC_CommandLine::HasArgument(const char* aArg)
{
	if (!gInstance)
		return false;

	const SC_Array<ArgumentInfo>& commands = gInstance->mArguments;
	for (const ArgumentInfo& argInfo : commands)
	{
		if (strcmp(aArg, argInfo.mArgument.c_str()) == 0)
			return true;
	}

	return false;
}

bool SC_CommandLine::GetIntValue(const char* aArg, int& aReturnValue, int aIndex /*= 0*/)
{
	if (!gInstance)
		return false;

	const SC_Array<ArgumentInfo>& commands = gInstance->mArguments;
	for (const ArgumentInfo& argInfo : commands)
	{
		if (strcmp(aArg, argInfo.mArgument.c_str()) == 0)
		{
			for (int i = 0; i < argInfo.mValues.ICount(); ++i)
			{
				if (i == aIndex)
				{
					aReturnValue = atoi(argInfo.mValues[i].c_str());
					return true;
				}
			}
			return false;
		}
	}
	return false;
}

bool SC_CommandLine::GetFloatValue(const char* aArg, float& aReturnValue, int aIndex /*= 0*/)
{
	if (!gInstance)
		return false;

	const SC_Array<ArgumentInfo>& commands = gInstance->mArguments;
	for (const ArgumentInfo& argInfo : commands)
	{
		if (strcmp(aArg, argInfo.mArgument.c_str()) == 0)
		{
			for (int i = 0; i < argInfo.mValues.ICount(); ++i)
			{
				if (i == aIndex)
				{
					aReturnValue = (float)atof(argInfo.mValues[i].c_str());
					return true;
				}
			}
			return false;
		}
	}
	return false;
}

SC_CommandLine::SC_CommandLine(char** aArgsV, int aArgsC)
{
	char** args = aArgsV;
	int32 numArgs = aArgsC;

	for (int32 i = 1; i < numArgs; ++i) // first arg is always exe filename
	{
		std::string arg(args[i]);
		if (!arg.empty())
		{
			if (arg.front() == '-' || arg.front() == '/') // Found an argument
			{
				ArgumentInfo& newArgInfo = mArguments.Add();
				newArgInfo.mArgument = arg.substr(1);
			}
			else
			{
				ArgumentInfo& argInfo = mArguments.Last();
				argInfo.mValues.Add(arg);
			}
		}
	}

	// Make sure to remove unused allocations since this data will live for the lifetime of the application session.
	for (ArgumentInfo& argInfo : mArguments)
		argInfo.mValues.Compact();
	mArguments.Compact();
}

SC_CommandLine::~SC_CommandLine()
{

}

