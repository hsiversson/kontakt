
struct SR_ViewConstantsStruct
{
    float4x4 WorldToClip;
	float4x4 ClipToWorld;
	float4x4 mWorldToCamera;
	float4x4 mCameraToWorld;
	float4x4 mCameraToClip;
	float4x4 mClipToCamera;

	float4x4 mPrevWorldToClip;
	float4x4 mPrevClipToWorld;
	float4x4 mPrevWorldToCamera;
	float4x4 mPrevCameraToWorld;
	float4x4 mPrevCameraToClip;
	float4x4 mPrevClipToCamera;

    float3 CameraPosition;
    float CameraFov;

    float CameraNear;
    float CameraFar;
    float2 JitterOffsets;

    float4 ViewportPosAndInvSize;
    float4 RenderTargetSizeAndInvSize;
};