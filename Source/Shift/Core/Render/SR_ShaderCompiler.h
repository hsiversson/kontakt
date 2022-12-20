//ProjectFilter(Interface/Shader)
#pragma once

enum SR_ShaderCompilerFlags
{
	SR_ShaderCompilerFlag_None = 0,
	SR_ShaderCompilerFlag_Debug = 1 << 0,
	SR_ShaderCompilerFlag_SkipOptimizations = 1 << 1,
	SR_ShaderCompilerFlag_Enable16BitTypes = 1 << 2,
	SR_ShaderCompilerFlag_EnablePayloadQualifiers = 1 << 3,
	SR_ShaderCompilerFlag_IEEEStrictness = 1 << 4,
	//SR_ShaderCompilerFlag_Debug = 1 << 2,
	//SR_ShaderCompilerFlag_Debug = 1 << 3,
	//SR_ShaderCompilerFlag_Debug = 1 << 4,
};

struct SR_ShaderCompileArgs
{
	SR_ShaderCompileArgs() : mType(SR_ShaderType::COUNT), mEntryPoint(nullptr) {}

	SC_Array<SC_Pair<std::string, std::string>> mDefines;
	SR_ShaderType mType;
	std::string mShaderFile;
	const char* mEntryPoint;
};

struct SR_ShaderByteCode;
struct SR_ShaderMetaData;
class SR_ShaderCompiler
{
public:
	SR_ShaderCompiler();
	virtual ~SR_ShaderCompiler();

	virtual bool CompileFromFile(const SR_ShaderCompileArgs& aArgs, SR_ShaderByteCode& aOutResult, SR_ShaderMetaData* aOutMetaData = nullptr);
	virtual bool CompileFromString(const std::string& aShadercode, const SR_ShaderCompileArgs& aArgs, SR_ShaderByteCode& aOutResult, SR_ShaderMetaData* aOutMetaData = nullptr, const std::string& aBaseDirectory = std::string());

protected:

};

