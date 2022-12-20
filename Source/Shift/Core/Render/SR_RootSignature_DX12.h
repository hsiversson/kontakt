//ProjectFilter(DX12/Shader)
#pragma once

#if SR_ENABLE_DX12
#include "SR_RootSignature.h"

struct ID3D12RootSignature;

class SR_RootSignature_DX12 final : public SR_RootSignature
{
public:
	SR_RootSignature_DX12(const SR_RootSignatureProperties& aProperties);
	~SR_RootSignature_DX12();

	bool Init();

	ID3D12RootSignature* GetD3D12RootSignature() const;

private:
	SR_ComPtr<ID3D12RootSignature> mD3D12RootSignature;
};

#endif