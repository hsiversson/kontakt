//ProjectFilter(Interface/Shader)
#include "Render_Precompiled.h"
#include "SR_Shader.h"

SR_Shader::SR_Shader()
	: mShaderType(SR_ShaderType::COUNT)
{

}

SR_Shader::~SR_Shader()
{

}

const SR_ShaderByteCode& SR_Shader::GetByteCode() const
{
	return mShaderByteCode;
}

const SR_ShaderMetaData& SR_Shader::GetMetaData() const
{
	return mMetaData;
}

const SR_ShaderType& SR_Shader::GetType() const
{
	return mShaderType;
}
