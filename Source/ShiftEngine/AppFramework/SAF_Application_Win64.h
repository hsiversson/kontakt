#pragma once
#include "SAF_Application.h"

#if IS_WINDOWS_PLATFORM
class SAF_Application_Win64 final : public SAF_Application
{
public:
    SAF_Application_Win64();
    ~SAF_Application_Win64();

private:

};
#endif