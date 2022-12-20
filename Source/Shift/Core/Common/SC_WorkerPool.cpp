#include "Common_Precompiled.h"
#include "SC_WorkerPool.h"

SC_WorkerPool* SC_WorkerPool::gInstance = nullptr;

bool SC_WorkerPool::Create()
{
	if (!gInstance)
		gInstance = new SC_WorkerPool();

	return true;
}

void SC_WorkerPool::Destroy()
{
	delete gInstance;
	gInstance = nullptr;
}

SC_WorkerPool* SC_WorkerPool::Get()
{
	return gInstance;
}

SC_WorkerPool::SC_WorkerPool()
{

}

SC_WorkerPool::~SC_WorkerPool()
{

}

