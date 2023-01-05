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

void Gfx_SceneGraph::PrepareView(Gfx_View* aView)
{
	static constexpr uint32 minItemsPerTask = 16;
	const uint32 numWorkersAvailable = SC_WorkerPool::GetFrameTaskWorkerCount();

	Gfx_ViewRenderData& prepareData = aView->GetPrepareData();

	// Schedule mesh culling tasks
	{
		const uint32 totalNumMeshes = mMeshInstances.Count();
		if (totalNumMeshes > 0)
		{
			const uint32 numTasksNeeded = SC_Clamp((uint32)SC_Floor(totalNumMeshes / (float)minItemsPerTask), 1u, numWorkersAvailable);
			const uint32 defaultNumMeshesPerTask = SC_Max((uint32)SC_Floor(totalNumMeshes / (float)numTasksNeeded), minItemsPerTask);
			uint32 rest = totalNumMeshes % numTasksNeeded;

			SC_Array<SC_Future<void>> cullingTasks(numTasksNeeded);
			uint32 offset = 0;
			for (uint32 taskIdx = 0; taskIdx < numTasksNeeded; ++taskIdx)
			{
				uint32 numMeshes = defaultNumMeshesPerTask;
				if (rest > 0)
				{
					uint32 itemsToAdd = SC_Min(rest, minItemsPerTask);
					numMeshes += itemsToAdd;
					rest -= itemsToAdd;
				}

				cullingTasks.Add(SC_CreateFrameTask(std::bind(&Gfx_SceneGraph::CullMeshes_Stage1, this, aView, offset, numMeshes)));
				offset += numMeshes;
			}

			for (const SC_Future<void>& task : cullingTasks)
				task.Wait();

			prepareData.mQueues.mDepthQueue.Prepare(prepareData);
			prepareData.mQueues.mDepthQueue_MotionVectors.Prepare(prepareData);
			prepareData.mQueues.mOpaqueQueue.Prepare(prepareData);
			prepareData.mQueues.mTransparentQueue.Prepare(prepareData);
		}
	}

	// Schedule light culling tasks
	{
		const uint32 totalNumLights = mLights.Count();
		if (totalNumLights > 0)
		{
			const uint32 numTasksNeeded = SC_Clamp((uint32)SC_Floor(totalNumLights / (float)minItemsPerTask), 1u, numWorkersAvailable);
			const uint32 defaultNumLightsPerTask = SC_Max((uint32)SC_Floor(totalNumLights / (float)numTasksNeeded), minItemsPerTask);
			uint32 rest = totalNumLights % numTasksNeeded;

			SC_Array<SC_Future<void>> cullingTasks(numTasksNeeded);
			uint32 offset = 0;
			for (uint32 taskIdx = 0; taskIdx < numTasksNeeded; ++taskIdx)
			{
				uint32 numLights = defaultNumLightsPerTask;
				if (rest > 0)
				{
					uint32 itemsToAdd = SC_Min(rest, minItemsPerTask);
					numLights += itemsToAdd;
					rest -= itemsToAdd;
				}

				cullingTasks.Add(SC_CreateFrameTask(std::bind(&Gfx_SceneGraph::CullLights_Stage1, this, aView, offset, numLights)));
				offset += numLights;
			}

			for (const SC_Future<void>& task : cullingTasks)
				task.Wait();
			cullingTasks.RemoveAll();

			static constexpr uint32 macroTileSize = 64;
			const uint32 numTilesX = (uint32)SC_Ceil(aView->GetCamera().GetSize().x / (float)macroTileSize);
			const uint32 numTilesY = (uint32)SC_Ceil(aView->GetCamera().GetSize().y / (float)macroTileSize);
			const uint32 numTiles = numTilesX * numTilesY;

			cullingTasks.Reserve(numTiles);
			for (uint32 tileIdx = 0; tileIdx < numTiles; ++tileIdx)
				cullingTasks.Add(SC_CreateFrameTask(std::bind(&Gfx_SceneGraph::CullLights_Stage2, this, aView, tileIdx)));

			for (const SC_Future<void>& task : cullingTasks)
				task.Wait();
		}
	}

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
	Gfx_ViewRenderData& prepareData = aView->GetPrepareData();
	const Gfx_Camera& camera = aView->GetCamera();
	const Gfx_Frustum& frustum = camera.GetFrustum();

	SC_Array<Gfx_RenderQueueItem> depthQueueItems(aNumItems);
	SC_Array<Gfx_RenderQueueItem> depthMVQueueItems(aNumItems);
	SC_Array<Gfx_RenderQueueItem> opaqueQueueItems(aNumItems);
	SC_Array<Gfx_RenderQueueItem> transparentQueueItems(aNumItems);
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
		//const Gfx_Material* material = meshInstance->GetMaterial();

		const bool writeDepth = true;
		const bool transparent = false;// material->IsTransparent();
		const bool outputMotionVectors = false;// material->OutputMotionVectors();

		SR_PipelineState* depthPipelineState = nullptr;// material->GetPipelineState(mesh->GetVertexLayout(), Depth);
		SR_PipelineState* colorPipelineState = nullptr;// material->GetPipelineState(mesh->GetVertexLayout(), Color);

		if (writeDepth && !depthPipelineState)
			continue;

		if (!colorPipelineState)
			continue;

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

		//renderQueueItem.mTransform = meshInstance->GetTransform();
		//renderQueueItem.mPrevTransform = meshInstance->GetPrevTransform();
		//renderQueueItem.mMaterialIndex = material->GetMaterialIndex();
		renderQueueItem.mSortDistance = distanceToCamera;

		if (writeDepth)
		{
			renderQueueItem.mPipelineState = depthPipelineState;
			if (outputMotionVectors)
				depthMVQueueItems.Add(renderQueueItem);
			else
				depthQueueItems.Add(renderQueueItem);
		}

		renderQueueItem.mPipelineState = colorPipelineState;
		if (transparent)
			transparentQueueItems.Add(renderQueueItem);
		else
			opaqueQueueItems.Add(renderQueueItem);
	}

	{
		SC_MutexLock lock(prepareData.mQueues.mDepthQueue.GetMutex());
		prepareData.mQueues.mDepthQueue.AddItems(depthQueueItems.GetBuffer(), depthQueueItems.Count());
	}
	{
		SC_MutexLock lock(prepareData.mQueues.mDepthQueue_MotionVectors.GetMutex());
		prepareData.mQueues.mDepthQueue_MotionVectors.AddItems(depthMVQueueItems.GetBuffer(), depthMVQueueItems.Count());
	}
	{
		SC_MutexLock lock(prepareData.mQueues.mOpaqueQueue.GetMutex());
		prepareData.mQueues.mOpaqueQueue.AddItems(opaqueQueueItems.GetBuffer(), opaqueQueueItems.Count());
	}
	{
		SC_MutexLock lock(prepareData.mQueues.mTransparentQueue.GetMutex());
		prepareData.mQueues.mTransparentQueue.AddItems(transparentQueueItems.GetBuffer(), transparentQueueItems.Count());
	}
}

void Gfx_SceneGraph::CullLights_Stage1(Gfx_View* aView, uint32 aStartOffset, uint32 aNumItems)
{
	//Gfx_ViewRenderData& prepareData = aView->GetPrepareData();
	const Gfx_Camera& camera = aView->GetCamera();
	const Gfx_Frustum& frustum = camera.GetFrustum();

	SC_Array<Gfx_LocalLightRenderData> visibleLights(aNumItems);
	for (uint32 i = 0; i < aNumItems; ++i)
	{
		const Gfx_Light* light = mLights[i + aStartOffset];
		if (!light)
			continue;

		if (!frustum.Intersects(light->GetBoundingSphere()))
			continue;


	}
}

void Gfx_SceneGraph::CullLights_Stage2(Gfx_View* /*aView*/, uint32 /*aTileIndex*/)
{
}
