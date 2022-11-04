//ProjectFilter(Interface)
#pragma once

class SR_CommandList;
class SR_RenderContext
{
public:
    SR_RenderContext();
    virtual ~SR_RenderContext();

    void BeginTask(SR_CommandList* aCmdList);
    void EndTask();

private:
    SC_Ref<SR_CommandList> mCurrentCmdList;
};