//ProjectFilter(DX12/Resources)
#include "Render_Precompiled.h"

#if SR_ENABLE_DX12
#include "SR_Buffer_DX12.h"
#include "SR_RenderDevice_DX12.h"

SR_Buffer_DX12::SR_Buffer_DX12(const SR_BufferProperties& aProperties, const SC_Ref<SR_BufferResource>& aResource)
	: SR_Buffer(aProperties, aResource)
{

}

SR_Buffer_DX12::~SR_Buffer_DX12()
{

}

bool SR_Buffer_DX12::Init()
{
	if (!InitSRV())
		return false;

	if (mProperties.mWritable)
	{
		if (!mResource->GetProperties().mWritable)
		{
			SC_ASSERT(false, "Resource does not allow write access.");
			return false;
		}
		if (!InitUAV())
			return false;
	}

	return true;
}

D3D12_CPU_DESCRIPTOR_HANDLE SR_Buffer_DX12::GetCPUHandleSRV() const
{
	return D3D12_CPU_DESCRIPTOR_HANDLE{ mDescriptors[0].mDescriptorHandleCPU };
}

D3D12_GPU_DESCRIPTOR_HANDLE SR_Buffer_DX12::GetGPUHandleSRV() const
{
	return D3D12_GPU_DESCRIPTOR_HANDLE{ mDescriptors[0].mDescriptorHandleGPU };
}

D3D12_CPU_DESCRIPTOR_HANDLE SR_Buffer_DX12::GetCPUHandleUAV() const
{
	return D3D12_CPU_DESCRIPTOR_HANDLE{ mDescriptors[1].mDescriptorHandleCPU };
}

D3D12_GPU_DESCRIPTOR_HANDLE SR_Buffer_DX12::GetGPUHandleUAV() const
{
	return D3D12_GPU_DESCRIPTOR_HANDLE{ mDescriptors[1].mDescriptorHandleGPU };
}

bool SR_Buffer_DX12::InitSRV()
{
	const SR_BufferResourceProperties& bufferResourceProperties = mResource->GetProperties();
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;

	ID3D12Resource* resource = nullptr;
	if (mProperties.mType == SR_BufferType::Bytes)
	{
		//SC_ASSERT(!(mProperties.mFirstElement & 3));
		//SC_ASSERT(!(mProperties.mElementCount & 3));

		srvDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_RAW;
		srvDesc.Buffer.FirstElement = mResource ? (mProperties.mOffset) / 4 : 0;
		srvDesc.Buffer.NumElements = mProperties.mElementCount / 4;

		resource = mResource->mD3D12Resource;
	}
	else if (mProperties.mType == SR_BufferType::RaytracingBuffer)
	{
		SC_ASSERT(bufferResourceProperties.mBindFlags & SR_BufferBindFlag_RaytracingBuffer);
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_RAYTRACING_ACCELERATION_STRUCTURE;
		srvDesc.RaytracingAccelerationStructure.Location = mResource->mD3D12Resource->GetGPUVirtualAddress();
	}
	else
	{
		uint32 elementStride = 0;
		if (mProperties.mType == SR_BufferType::Structured)
		{
			srvDesc.Format = DXGI_FORMAT_UNKNOWN;
			srvDesc.Buffer.StructureByteStride = bufferResourceProperties.mElementSize;
			elementStride = bufferResourceProperties.mElementSize;
		}
		else
		{
			srvDesc.Format = SR_ConvertFormat_DX12(mProperties.mFormat);
			elementStride = SR_GetFormatBitsPerPixel(mProperties.mFormat) / 8;
		}

		srvDesc.Buffer.NumElements = mProperties.mElementCount;
		srvDesc.Buffer.FirstElement = mProperties.mOffset / elementStride;

		resource = mResource->mD3D12Resource;
	}

	mDescriptors[0] = SR_RenderDevice_DX12::gInstance->GetDescriptorHeap(SR_DescriptorHeapType::CBV_SRV_UAV)->Alloc();
	SR_RenderDevice_DX12::gInstance->GetD3D12Device()->CreateShaderResourceView(resource, &srvDesc, D3D12_CPU_DESCRIPTOR_HANDLE{ mDescriptors[0].mDescriptorHandleCPU });

	return true;
}

bool SR_Buffer_DX12::InitUAV()
{
	const SR_BufferResourceProperties& bufferResourceProperties = mResource->GetProperties();
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;

	if (mProperties.mType == SR_BufferType::Bytes)
	{
		SC_ASSERT(!(mProperties.mFirstElement & 3));
		SC_ASSERT(!(mProperties.mElementCount & 3));

		uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
		uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_RAW;
		uavDesc.Buffer.FirstElement = mProperties.mOffset / 4;
		uavDesc.Buffer.NumElements = mProperties.mElementCount / 4;
	}
	else
	{
		uint32 elementStride = 0;
		if (mProperties.mType == SR_BufferType::Structured)
		{
			uavDesc.Format = DXGI_FORMAT_UNKNOWN;
			uavDesc.Buffer.StructureByteStride = bufferResourceProperties.mElementSize;
			elementStride = bufferResourceProperties.mElementSize;
		}
		else
		{
			uavDesc.Format = SR_ConvertFormat_DX12(mProperties.mFormat);
			elementStride = SR_GetFormatBitsPerPixel(mProperties.mFormat) / 8;
		}

		uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
		uavDesc.Buffer.FirstElement = mProperties.mOffset / elementStride;
		uavDesc.Buffer.NumElements = mProperties.mElementCount;
	}

	mDescriptors[1] = SR_RenderDevice_DX12::gInstance->GetDescriptorHeap(SR_DescriptorHeapType::CBV_SRV_UAV)->Alloc();
	SR_RenderDevice_DX12::gInstance->GetD3D12Device()->CreateUnorderedAccessView(mResource->mD3D12Resource, nullptr, &uavDesc, D3D12_CPU_DESCRIPTOR_HANDLE{ mDescriptors[1].mDescriptorHandleCPU });

	return true;
}

#endif