//ProjectFilter(World)
#include "Graphics_Precompiled.h"

#include "Gfx_SceneGraph.h"
#include "Gfx_View.h"
#include "Gfx_MeshInstance.h"
#include "Gfx_Light.h"
#include "Gfx_RenderQueueItem.h"

Gfx_SceneGraph::Gfx_SceneGraph(Gfx_World* aParentWorld)
	: mParentWorld(aParentWorld)
{

}

Gfx_SceneGraph::~Gfx_SceneGraph()
{

}

void Gfx_SceneGraph::Update()
{
	FlushPendingActions();
}

void Gfx_SceneGraph::PrepareView(Gfx_View* /*aView*/)
{

}

void Gfx_SceneGraph::AddMeshInstance(Gfx_MeshInstance* aMeshInstance)
{
	Action action;
	action.mActionType = ActionType::Add;
	action.mObjectType = ObjectType::Mesh;
	action.mMeshInstance = aMeshInstance;

	SC_MutexLock lock(mPendingActionsMutex);
	mPendingActions.Add(action);
}

void Gfx_SceneGraph::RemoveMeshInstance(Gfx_MeshInstance* aMeshInstance)
{
	Action action;
	action.mActionType = ActionType::Remove;
	action.mObjectType = ObjectType::Mesh;
	action.mMeshInstance = aMeshInstance;

	SC_MutexLock lock(mPendingActionsMutex);
	mPendingActions.Add(action);
}

void Gfx_SceneGraph::AddLight(Gfx_Light* aLight)
{
	Action action;
	action.mActionType = ActionType::Add;
	action.mObjectType = ObjectType::Light;
	action.mLight = aLight;

	SC_MutexLock lock(mPendingActionsMutex);
	mPendingActions.Add(action);
}

void Gfx_SceneGraph::RemoveLight(Gfx_Light* aLight)
{
	Action action;
	action.mActionType = ActionType::Remove;
	action.mObjectType = ObjectType::Light;
	action.mLight = aLight;

	SC_MutexLock lock(mPendingActionsMutex);
	mPendingActions.Add(action);
}

void Gfx_SceneGraph::FlushPendingActions()
{
	SC_MutexLock lock(mPendingActionsMutex);
	for (Action& action : mPendingActions)
	{
		switch (action.mActionType)
		{
		case ActionType::Add:
			if (action.mObjectType == ObjectType::Mesh)
				AddInternal(action.mMeshInstance);
			else if (action.mObjectType == ObjectType::Light)
				AddInternal(action.mLight);
			break;
		case ActionType::Remove:
			if (action.mObjectType == ObjectType::Mesh)
				RemoveInternal(action.mMeshInstance);
			else if (action.mObjectType == ObjectType::Light)
				RemoveInternal(action.mLight);
			break;
		case ActionType::Move:
			if (action.mObjectType == ObjectType::Mesh)
				MoveInternal(action.mMeshInstance);
			else if (action.mObjectType == ObjectType::Light)
				MoveInternal(action.mLight);
			break;
		}
	}

	mPendingActions.RemoveAll();
}

void Gfx_SceneGraph::AddInternal(Gfx_MeshInstance* aMeshInstance)
{
	mMeshInstances.Add(aMeshInstance);
}

void Gfx_SceneGraph::AddInternal(Gfx_Light* aLight)
{
	mLights.Add(aLight);
}

void Gfx_SceneGraph::RemoveInternal(Gfx_MeshInstance* aMeshInstance)
{
	mMeshInstances.RemoveCyclic(aMeshInstance);
}

void Gfx_SceneGraph::RemoveInternal(Gfx_Light* aLight)
{
	mLights.RemoveCyclic(aLight);
}

void Gfx_SceneGraph::MoveInternal(Gfx_MeshInstance* /*aMeshInstance*/)
{

}

void Gfx_SceneGraph::MoveInternal(Gfx_Light* /*aLight*/)
{

}

void Gfx_SceneGraph::CullMeshes_Stage1(Gfx_View* aView, uint32 aStartOffset, uint32 aNumItems)
{
	//Gfx_ViewRenderData& prepareData = aView->GetPrepareData();
	const Gfx_Camera& camera = aView->GetCamera();
	const Gfx_Frustum& frustum = camera.GetFrustum();

	SC_Array<Gfx_RenderQueueItem> renderQueueItems(aNumItems);
	for (uint32 i = 0; i < aNumItems; ++i)
	{
		const Gfx_MeshInstance* meshInstance = mMeshInstances[i + aStartOffset];
		if (!meshInstance)
			continue;

		const SC_AABB& boundingBox = meshInstance->GetBoundingBox();
		const SC_Sphere boundingSphere(boundingBox);
		const float distanceToCamera = (camera.GetPosition() - boundingBox.GetCenter()).Length();

		if (!frustum.Intersects(boundingSphere))
			continue;

		if (!frustum.Intersects(boundingBox))
			continue;

		// TODO: More fine-grained culling like occlusion culling here

		const Gfx_Mesh* mesh = meshInstance->GetMesh();
		Gfx_RenderQueueItem renderQueueItem;

#if SR_ENABLE_MESH_SHADERS
		if (SR_RenderDevice::gInstance->mCaps.mMeshShaders && mesh->IsUsingMeshlets())
		{
			const SGfx_MeshletBuffers& meshletBuffers = mesh->GetMeshletBuffers();
			renderQueueItem.mMeshletData.mVertexBuffer = meshletBuffers.mVertexBuffer;
			renderQueueItem.mMeshletData.mMeshletBuffer = meshletBuffers.mMeshletBuffer;
			renderQueueItem.mMeshletData.mVertexIndexBuffer = meshletBuffers.mVertexIndexBuffer;
			renderQueueItem.mMeshletData.mPrimitiveIndexBuffer = meshletBuffers.mPrimitiveIndexBuffer;
			renderQueueItem.mUseMeshlets = true;
		}
		else
#endif //SR_ENABLE_MESH_SHADERS
		{
			renderQueueItem.mVertexBuffer = mesh->GetVertexBufferResource();
			renderQueueItem.mIndexBuffer = mesh->GetIndexBufferResource();
			renderQueueItem.mUseMeshlets = false;
		}

		//renderQueueItem.mTransform = mesh->GetTransform();
		//renderQueueItem.mPrevTransform = mesh->GetPrevTransform();
		//renderQueueItem.mMaterialIndex = mesh->GetMaterialInstance()->GetMaterialIndex();
		renderQueueItem.mSortDistance = distanceToCamera;
	}
}

void Gfx_SceneGraph::CullLights_Stage1(Gfx_View* /*aView*/, uint32 /*aStartOffset*/, uint32 /*aNumItems*/)
{
	//for (uint32 i = 0; i < aNumItems; ++i)
	//{
	//	//const Gfx_Light* light = mLights[i + aStartOffset];
	//}
}

void Gfx_SceneGraph::CullLights_Stage2(Gfx_View* /*aView*/, uint32 /*aTileIndex*/)
{
}
