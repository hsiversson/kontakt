#pragma once

enum class SAF_ReturnCode
{
    Unknown,
    OK,
    Exit,
    Failed,
    Restart,
};

enum class SAF_ApplicationPlatform
{
    Windows,
    Linux
};

class SAF_ApplicationInterface
{
public:
    SAF_ApplicationInterface() {}
    virtual ~SAF_ApplicationInterface() {}

    virtual bool Init() = 0;
    virtual void Update() = 0;
    virtual void Exit() = 0;
};

class SAF_Application
{
public:
    static SAF_Application* Create(const SAF_ApplicationPlatform& aPlatform);
    
public:
    SAF_Application();
    virtual ~SAF_Application();

    virtual bool Init();

    SAF_ReturnCode Run();

protected:
    virtual bool Update(SAF_ReturnCode& aOutReturnCode);

};