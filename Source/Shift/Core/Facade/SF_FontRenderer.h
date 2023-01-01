#pragma once

class SR_PipelineState;

class SF_FontRenderer
{
public:
	SF_FontRenderer();
	~SF_FontRenderer();

	bool Init();

	void Render();

private:
	SC_Ref<SR_PipelineState> mFont2DShader;
};

