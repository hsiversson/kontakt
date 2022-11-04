//ProjectFilter(Interface)
#include "Render_Precompiled.h"
#include "SR_RenderContext.h"

SR_RenderContext::SR_RenderContext()
{
}

SR_RenderContext::~SR_RenderContext()
{
}

void SR_RenderContext::BeginTask(SR_CommandList* aCmdList)
{
	mCurrentCmdList = aCmdList;
}

void SR_RenderContext::EndTask()
{
	mCurrentCmdList = nullptr;
}
