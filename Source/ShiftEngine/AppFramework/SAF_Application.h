#pragma once

enum class SAF_ReturnCode
{
    Unknown,
    OK,
    Failed,
    Restart,
};

class SAF_Application
{
public:
    SAF_Application();
    ~SAF_Application();

    bool Init();

    SAF_ReturnCode Run();

private:
};