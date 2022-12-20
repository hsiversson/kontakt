//ProjectFilter(Interface/Shader)
#pragma once
#include "SR_ShaderCompiler.h"

// For COM interface (ComPtr)
#include <wrl.h>
template<class T>
using SR_ComPtr = Microsoft::WRL::ComPtr<T>;

struct IDxcCompiler3;
struct IDxcUtils;
struct IDxcIncludeHandler;

typedef HRESULT(__stdcall* DxcCreateInstanceProc)(_In_ REFCLSID rclsid, _In_ REFIID riid, _Out_ LPVOID* ppv);

class SR_DirectXShaderCompiler final : public SR_ShaderCompiler
{
public:
	enum class Backend
	{
		DXIL,
		SPIRV
	};

public:
	SR_DirectXShaderCompiler(const Backend& aBackend = Backend::DXIL);
	~SR_DirectXShaderCompiler();

	bool CompileFromFile(const SR_ShaderCompileArgs& aArgs, SR_ShaderByteCode& aOutResult, SR_ShaderMetaData* aOutMetaData = nullptr) override;
	bool CompileFromString(const std::string& aShadercode, const SR_ShaderCompileArgs& aArgs, SR_ShaderByteCode& aOutResult, SR_ShaderMetaData* aOutMetaData = nullptr, const std::string& aBaseDirectory = std::string()) override;

private:
	void SetupArgs(SC_Array<LPCWSTR>& aOutArgs, uint32 aCompilerFlags);

	//SR_ShaderCompilerCache mShaderCache;

	DxcCreateInstanceProc mDxcCreateInstance;

	Backend mCompilerBackend;
	uint8 mShaderOptimizationLevel;
	bool mSkipOptimizations : 1;
	bool mDebugShaders : 1;
};

