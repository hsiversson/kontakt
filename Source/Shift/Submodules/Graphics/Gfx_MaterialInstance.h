#pragma once
#include "Gfx_Material.h"

class Gfx_MaterialInstance : public SC_ReferenceCounted
{
public:
	Gfx_MaterialInstance(Gfx_Material* aMaterial);
	~Gfx_MaterialInstance();

	Gfx_Material* GetMaterial() const;

private:
	SC_Ref<Gfx_Material> mMaterial;
};

