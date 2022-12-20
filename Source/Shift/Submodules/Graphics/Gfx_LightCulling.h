//ProjectFilter(Lighting)
#pragma once

enum class Gfx_LightCullingType
{
	Standard,
	Tiled,
	Clustered
};

class Gfx_LightCulling
{
public:
	Gfx_LightCulling(const Gfx_LightCullingType& aType);
	~Gfx_LightCulling();

private:

};

