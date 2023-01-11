#include "Graphics_Precompiled.h"
#include "Gfx_MaterialInstance.h"

Gfx_MaterialInstance::Gfx_MaterialInstance(Gfx_Material* aMaterial)
	: mMaterial(aMaterial)
{

}

Gfx_MaterialInstance::~Gfx_MaterialInstance()
{

}

Gfx_Material* Gfx_MaterialInstance::GetMaterial() const
{
	return mMaterial;
}
