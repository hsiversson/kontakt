//ProjectFilter(World)
#pragma once

class Gfx_World;
class Gfx_View;
class Gfx_MeshInstance;
class Gfx_Light;

class Gfx_SceneGraph
{
private:
	enum class ActionType
	{
		None,
		Add,
		Remove,
		Move,
		Activate,
		Inactivate
	};

	enum class ObjectType
	{
		Unknown,
		Mesh,
		Light,
		ParticleEffect,
		Decal
	};

	struct Action
	{
		Action()
			: mActionType(ActionType::None)
			, mObjectType(ObjectType::Unknown)
		{}

		Action(const Action& aOther)
		{
			SC_Memcpy(this, &aOther, sizeof(Action));
		}

		~Action() {}

		ActionType mActionType;
		ObjectType mObjectType;
		union
		{
			SC_Ref<Gfx_MeshInstance> mMeshInstance;
			SC_Ref<Gfx_Light> mLight;
		};
	};

public:
	Gfx_SceneGraph(Gfx_World* aParentWorld);
	~Gfx_SceneGraph();

	void Update();

	void PrepareView(Gfx_View* aView);

	void AddMeshInstance(Gfx_MeshInstance* aMeshInstance);
	void RemoveMeshInstance(Gfx_MeshInstance* aMeshInstance);
	
	void AddLight(Gfx_Light* aLight);
	void RemoveLight(Gfx_Light* aLight);

private:
	void FlushPendingActions();

	void AddInternal(Gfx_MeshInstance* aMeshInstance);
	void AddInternal(Gfx_Light* aLight);

	void RemoveInternal(Gfx_MeshInstance* aMeshInstance);
	void RemoveInternal(Gfx_Light* aLight);

	void MoveInternal(Gfx_MeshInstance* aMeshInstance);
	void MoveInternal(Gfx_Light* aLight);

	void CullMeshes_Stage1(Gfx_View* aView, uint32 aStartOffset, uint32 aNumItems); // Tests agains camera frustum, outputs all visible meshes.

	void CullLights_Stage1(Gfx_View* aView, uint32 aStartOffset, uint32 aNumItems); // Tests against camera frustum, outputs all visible lights
	void CullLights_Stage2(Gfx_View* aView, uint32 aTileIndex); // Tests agains individual macro tiles, outputs lights visible for specific tile.

private:
	SC_Mutex mPendingActionsMutex;
	SC_Array<Action> mPendingActions;

	SC_Array<SC_Ref<Gfx_MeshInstance>> mMeshInstances;
	SC_Array<SC_Ref<Gfx_Light>> mLights;

	Gfx_World* mParentWorld;
};

