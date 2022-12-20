//ProjectFilter(Interface/Shader)
#include "Render_Precompiled.h"
#include "SR_ShaderCompiler.h"

SR_ShaderCompiler::SR_ShaderCompiler()
{

}

SR_ShaderCompiler::~SR_ShaderCompiler()
{

}

bool SR_ShaderCompiler::CompileFromFile(const SR_ShaderCompileArgs& /*aArgs*/, SR_ShaderByteCode& /*aOutResult*/, SR_ShaderMetaData* /*aOutMetaData*/)
{
	SC_ASSERT(false, "Not implemented!");
	return false;
}

bool SR_ShaderCompiler::CompileFromString(const std::string& /*aShadercode*/, const SR_ShaderCompileArgs& /*aArgs*/, SR_ShaderByteCode& /*aOutResult*/, SR_ShaderMetaData* /*aOutMetaData*/, const std::string& /*aBaseDirectory*/)
{
	SC_ASSERT(false, "Not implemented!");
	return false;
}
