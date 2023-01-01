//ProjectFilter(Interface/Shader)
#include "Render_Precompiled.h"
#include "SR_DirectXShaderCompiler.h"

#include "dxcapi.h"
#include <fstream>

static const wchar_t* GetShaderModelVersion()
{
	switch (SR_RenderDevice::gInstance->mCaps.mHighestShaderModel)
	{
	case SR_ShaderModel::SM_5_1:
		return L"5_1";
	case SR_ShaderModel::SM_6_0:
		return L"6_0";
	case SR_ShaderModel::SM_6_1:
		return L"6_1";
	case SR_ShaderModel::SM_6_2:
		return L"6_2";
	case SR_ShaderModel::SM_6_3:
		return L"6_3";
	case SR_ShaderModel::SM_6_4:
		return L"6_4";
	case SR_ShaderModel::SM_6_5:
		return L"6_5";
	case SR_ShaderModel::SM_6_6:
		return L"6_6";
	case SR_ShaderModel::SM_6_7:
		return L"6_7";
	case SR_ShaderModel::Unknown:
	default:
		return L"Unknown SM version.";
	}
}

static std::wstring GetTargetProfile(const SR_ShaderType& aShaderType)
{
	std::wstring shaderTarget;
	switch (aShaderType)
	{
	case SR_ShaderType::Vertex:
		shaderTarget = L"vs_";
		break;
#if SR_ENABLE_MESH_SHADERS
	case SR_ShaderType::Amplification:
		shaderTarget = L"as_";
		break;
	case SR_ShaderType::Mesh:
		shaderTarget = L"ms_";
		break;
#endif
	case SR_ShaderType::Pixel:
		shaderTarget = L"ps_";
		break;

	case SR_ShaderType::Compute:
		shaderTarget = L"cs_";
		break;
#if SR_ENABLE_RAYTRACING
	case SR_ShaderType::Raytracing:
		shaderTarget = L"lib_";
		break;
#endif // _DEBUG

	default:
		SC_ASSERT(false);
		return L"Unknown target";
	}

	shaderTarget += GetShaderModelVersion();
	return shaderTarget;
}

class SR_DxcIncludeHandler : public IDxcIncludeHandler
{
public:
	explicit SR_DxcIncludeHandler(IDxcUtils* aDxcUtils, const std::string& aBaseDirectory)
		: mDxcUtils(aDxcUtils)
		, gBaseDirectory((!aBaseDirectory.empty()) ? aBaseDirectory : "")
	{
	}

	HRESULT STDMETHODCALLTYPE LoadSource(_In_ LPCWSTR aFilename, _COM_Outptr_result_maybenull_ IDxcBlob** aIncludeSource) override
	{
		*aIncludeSource = nullptr;

		std::string path = gBaseDirectory;
		path += SC_UTF::ToUTF8(aFilename);
		path = SC_Path::MakeAbsolute(path);
		path = SC_Path::Normalize(path);

		SR_ComPtr<IDxcBlobEncoding> encoding;
		if (mIncludedFiles.find(path) != mIncludedFiles.end()) // Already included
		{
			static constexpr const char* nullStr = " ";
			mDxcUtils->CreateBlob(nullStr, 2, 0, encoding.GetAddressOf());
			*aIncludeSource = encoding.Detach();
			return S_OK;
		}
		else
		{
			// Recursively add includes
			std::wstring wpath = SC_UTF::ToUTF16(path);
			HRESULT hr = mDxcUtils->LoadFile(wpath.c_str(), nullptr, encoding.GetAddressOf());
			if (SUCCEEDED(hr))
			{
				mIncludedFiles.insert(path);
				*aIncludeSource = encoding.Detach();
			}
			else
			{
				SC_ERROR("File not found: {}", path);
				return E_FAIL;
			}
			return hr;
		}
	}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, _COM_Outptr_ void __RPC_FAR* __RPC_FAR* ppvObject) override
	{
		(void)riid;
		(void)ppvObject;
		return E_NOINTERFACE;
	}

	ULONG STDMETHODCALLTYPE AddRef(void) override { return 0; }
	ULONG STDMETHODCALLTYPE Release(void) override { return 0; }

private:
	std::unordered_set<std::string> mIncludedFiles;
	IDxcUtils* mDxcUtils;
	const std::string gBaseDirectory;
};

SR_DirectXShaderCompiler::SR_DirectXShaderCompiler(const Backend& aBackend)
	: mCompilerBackend(aBackend)
	, mShaderOptimizationLevel(3)
	, mSkipOptimizations(false)
	, mDebugShaders(false)
{
	if (SC_CommandLine::HasArgument("debugshaders"))
		mDebugShaders = true;

	if (SC_CommandLine::HasArgument("skipshaderoptimizations"))
		mSkipOptimizations = true;

	if (!mSkipOptimizations)
	{
		int optimizationLevel = 3;
		SC_CommandLine::GetIntValue("shaderoptimizationlevel", optimizationLevel);
		mShaderOptimizationLevel = (uint8)optimizationLevel;
	}

	const char* dllPath = nullptr;
	switch (mCompilerBackend)
	{
	case SR_DirectXShaderCompiler::Backend::DXIL:
	case SR_DirectXShaderCompiler::Backend::SPIRV:
		dllPath = "dxcompiler.dll";
		break;
	default:
		SC_ASSERT(false, "Invalid Compiler backend specified.");
		break;
	}

	HMODULE hModule = LoadLibrary(dllPath);
	mDxcCreateInstance = (DxcCreateInstanceProc)GetProcAddress(hModule, "DxcCreateInstance");
	if (!mDxcCreateInstance)
	{
		SC_ASSERT(false, "Unable to find DxcCreateInstance entry in dll!");
	}
}

SR_DirectXShaderCompiler::~SR_DirectXShaderCompiler()
{

}

bool SR_DirectXShaderCompiler::CompileFromFile(const SR_ShaderCompileArgs& /*aArgs*/, SR_ShaderByteCode& /*aOutResult*/, SR_ShaderMetaData* /*aOutMetaData*/)
{
	return false;
}

bool SR_DirectXShaderCompiler::CompileFromString(const std::string& aShadercode, const SR_ShaderCompileArgs& aArgs, SR_ShaderByteCode& aOutResult, SR_ShaderMetaData* aOutMetaData, const std::string& aBaseDirectory)
{
	std::string shaderCode(aShadercode);

	SR_ComPtr<IDxcCompiler3> dxcCompiler;
	HRESULT result = mDxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler));

	SR_ComPtr<IDxcUtils> dxcUtils;
	result = mDxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils));

	SR_ComPtr<IDxcBlobEncoding> sourceBlob;
	dxcUtils->CreateBlobFromPinned(shaderCode.data(), (UINT32)shaderCode.size(), 0, &sourceBlob);

	DxcBuffer sourceBuffer;
	sourceBuffer.Ptr = sourceBlob->GetBufferPointer();
	sourceBuffer.Size = sourceBlob->GetBufferSize();
	sourceBuffer.Encoding = 0;

	SC_Array<LPCWSTR> compileArgs;
	compileArgs.Reserve(64);

	uint32 compilerFlags = SR_ShaderCompilerFlag_None;

	if (mDebugShaders)
		compilerFlags |= SR_ShaderCompilerFlag_Debug;
	if (mSkipOptimizations)
		compilerFlags |= SR_ShaderCompilerFlag_SkipOptimizations;

	SetupArgs(compileArgs, compilerFlags);

	compileArgs.Add(L"-E");
	std::wstring entryPoint = SC_UTF::ToUTF16(aArgs.mEntryPoint);
	compileArgs.Add(entryPoint.c_str());

	compileArgs.Add(L"-T");
	compileArgs.Add(GetTargetProfile(aArgs.mType).c_str());

	SC_Array<std::wstring> rawStrDefines;
	for (uint32 i = 0; i < aArgs.mDefines.Count(); ++i)
	{
		compileArgs.Add(L"-D");

		std::wstring& define = rawStrDefines.Add(SC_UTF::ToUTF16(aArgs.mDefines[i].mFirst.c_str()));
		define += L"=";
		define += SC_UTF::ToUTF16(aArgs.mDefines[i].mSecond.c_str());

		compileArgs.Add(define.c_str());
	}

	SR_ComPtr<IDxcResult> compileResults;
	SR_DxcIncludeHandler includeHandler(dxcUtils.Get(), aBaseDirectory);

	result = dxcCompiler->Compile(&sourceBuffer, compileArgs.GetBuffer(), compileArgs.Count(), &includeHandler, IID_PPV_ARGS(&compileResults));
	if (FAILED(result))
	{
		SC_ASSERT(false, "Failed to compile shader.");
		return false;
	}

	if (compileResults->HasOutput(DXC_OUT_ERRORS))
	{
		SR_ComPtr<IDxcBlobUtf8> errors;
		SR_ComPtr<IDxcBlobUtf16> errorsOutputName;
		result = compileResults->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&errors), &errorsOutputName);

		if (errors && errors->GetStringLength() > 0)
		{
			SC_ERROR("Shader compilation error: {}", errors->GetStringPointer());
			return false;
		}
	}
	
	if (compileResults->HasOutput(DXC_OUT_OBJECT))
	{
		SR_ComPtr<IDxcBlob> shaderByteCode;
		result = compileResults->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderByteCode), nullptr);
		if (SUCCEEDED(result))
		{
			aOutResult.mSize = static_cast<uint64>(shaderByteCode->GetBufferSize());
			aOutResult.mData = new uint8[aOutResult.mSize];
			SC_Memcpy(aOutResult.mData, shaderByteCode->GetBufferPointer(), aOutResult.mSize);
		}
		else
			return false;
	}
	else
		return false;

	if (aOutMetaData && compileResults->HasOutput(DXC_OUT_REFLECTION))
	{
		SR_ComPtr<IDxcBlob> reflectionData;
		result = compileResults->GetOutput(DXC_OUT_REFLECTION, IID_PPV_ARGS(&reflectionData), nullptr);
		if (SUCCEEDED(result))
		{
			DxcBuffer reflectionBuffer;
			reflectionBuffer.Ptr = reflectionData->GetBufferPointer();
			reflectionBuffer.Size = reflectionData->GetBufferSize();
			reflectionBuffer.Encoding = 0;

#if SR_ENABLE_DX12
			SR_ComPtr<ID3D12ShaderReflection> reflection;
			dxcUtils->CreateReflection(&reflectionBuffer, IID_PPV_ARGS(&reflection));
			if (reflection)
			{
				//D3D12_SHADER_DESC shaderDesc = {};
				//result = reflection->GetDesc(&shaderDesc);
				//if (FAILED(result))
				//	return false;

				//shaderDesc.

				// Read if shader is expecting any resource bindings.
				// Read other requirements to use this shader.

				uint32 threads[3];
				reflection->GetThreadGroupSize(&threads[0], &threads[1], &threads[2]);
				aOutMetaData->mNumThreads = SC_Vector3ui(threads[0], threads[1], threads[2]);
			}
#endif
		}
		else
			return false;
	}

	//if (compileResults->HasOutput(DXC_OUT_PDB))
	//{
	//	SR_ComPtr<IDxcBlob> pdbData;
	//	SR_ComPtr<IDxcBlobUtf16> outputName;
	//	result = compileResults->GetOutput(DXC_OUT_PDB, IID_PPV_ARGS(&pdbData), &outputName);
	//	if (SUCCEEDED(result))
	//	{
	//		static constexpr const char* gShaderDebugCacheFolder = "Cache/ShaderDebug";
	//		SC_FilePath::CreateDirectory(gShaderDebugCacheFolder);
	//
	//		std::string pdbName = SC_UTF16ToUTF8(outputName->GetStringPointer());
	//		std::string path = SC_FormatStr("{}/{}", gShaderDebugCacheFolder, pdbName.c_str());
	//		std::ofstream outStream(path, std::ios::binary);
	//		if (outStream.is_open())
	//			outStream.write((const char*)pdbData->GetBufferPointer(), pdbData->GetBufferSize());
	//		else
	//		{
	//			SC_ERROR("Couldn't write shader debug info.");
	//		}
	//	}
	//}
	return true;
}

void SR_DirectXShaderCompiler::SetupArgs(SC_Array<LPCWSTR>& aOutArgs, uint32 aCompilerFlags)
{
	if (aCompilerFlags & SR_ShaderCompilerFlag_Enable16BitTypes)
		aOutArgs.Add(L"-enable-16bit-types");
	if (aCompilerFlags & SR_ShaderCompilerFlag_EnablePayloadQualifiers)
		aOutArgs.Add(L"-enable-payload-qualifiers");
	if (aCompilerFlags & SR_ShaderCompilerFlag_IEEEStrictness)
		aOutArgs.Add(DXC_ARG_IEEE_STRICTNESS);

	if (mDebugShaders || (aCompilerFlags & SR_ShaderCompilerFlag_Debug))
		aOutArgs.Add(DXC_ARG_DEBUG);

	if (mSkipOptimizations || (aCompilerFlags & SR_ShaderCompilerFlag_SkipOptimizations))
		aOutArgs.Add(DXC_ARG_SKIP_OPTIMIZATIONS);
	else
	{
		if (mShaderOptimizationLevel == 2)
			aOutArgs.Add(DXC_ARG_OPTIMIZATION_LEVEL2);
		else if (mShaderOptimizationLevel == 1)
			aOutArgs.Add(DXC_ARG_OPTIMIZATION_LEVEL1);
		else if (mShaderOptimizationLevel == 0)
			aOutArgs.Add(DXC_ARG_OPTIMIZATION_LEVEL0);
		else
			aOutArgs.Add(DXC_ARG_OPTIMIZATION_LEVEL3);
	}

	aOutArgs.Add(L"-D");
	if (mCompilerBackend == Backend::SPIRV)
		aOutArgs.Add(L"IS_SPIRV=1");
	else
		aOutArgs.Add(L"IS_DXIL=1");

	if (mCompilerBackend == Backend::SPIRV)
	{
		aOutArgs.Add(L"-spirv");
		aOutArgs.Add(L"-fvk-use-dx-layout");
		aOutArgs.Add(L"-fvk-use-dx-position-w");
	}

	aOutArgs.Add(L"-HV 2021"); // TEMPORARY UNTIL HLSL 2021 BECOMES DEFAULT
	aOutArgs.Add(L"-Qstrip_debug");
	aOutArgs.Add(L"-Qstrip_rootsignature");
	aOutArgs.Add(L"-Qstrip_reflect");
	aOutArgs.Add(L"-flegacy-macro-expansion");
	aOutArgs.Add(DXC_ARG_ALL_RESOURCES_BOUND);
	aOutArgs.Add(DXC_ARG_RESOURCES_MAY_ALIAS);
}
