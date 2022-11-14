//ProjectFilter(Windows)
#pragma once
#include "SAF_Application.h"

#if IS_WINDOWS_PLATFORM
#include "SAF_Window_Win64.h"

class SAF_Application_Win64 final : public SAF_Application
{
public:
    SAF_Application_Win64();
    ~SAF_Application_Win64();

    bool Init() override;

private:
	bool Update(SAF_ReturnCode& aOutReturnCode) override;

    SAF_Window_Win64 mWindow;
};
#endif