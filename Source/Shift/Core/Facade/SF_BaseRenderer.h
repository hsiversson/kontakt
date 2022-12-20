#pragma once

class SR_PipelineState;
class SR_BufferResource;

class SF_BaseRenderer
{
public:
	SF_BaseRenderer();
	~SF_BaseRenderer();

	bool Init();

	void Render();

private:

	SC_Ref<SR_PipelineState> mDefaultPipelineState;
	SC_Ref<SR_BufferResource> mDefaultVertexBuffer;
	SC_Ref<SR_BufferResource> mDefaultIndexBuffer;
};

