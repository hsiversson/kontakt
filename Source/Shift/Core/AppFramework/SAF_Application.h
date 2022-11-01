#pragma once

enum class SAF_ReturnCode
{
    Unknown,
    OK,
    Failed,
    Restart,
};

enum class SAF_ApplicationPlatform
{
    Windows,
    Linux
};

class SAF_Application
{
public:
    static SAF_Application* Create(const SAF_ApplicationPlatform& aPlatform);
    
public:
    SAF_Application();
    virtual ~SAF_Application();

    virtual bool Init();

    virtual SAF_ReturnCode Run();

private:
};