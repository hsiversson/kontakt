//ProjectFilter(Functional)
#pragma once
#include "SC_Array.h"
#include "SC_Function.h"

template<typename Signature> struct SC_SlotStorage;

template<class ...Args>
struct SC_SlotStorage<void(Args...)>
{
	void operator()(Args... aArgs) const
	{
		for (auto& callback : mCallbacks)
		{
			if (callback)
				callback(aArgs...);
		}
	}
protected:
	SC_Array<SC_Function<void(Args...)>> mCallbacks;
};

template<class Signature>
class SC_Slot : public SC_SlotStorage<Signature>
{
public:
	template<class Fn>
	uint32 Connect(const Fn& aFunction) 
	{ 
		return ConnectInternal(SC_Function<Signature>(aFunction));
	}

	template<class ObjectType, class MemberFn>
	uint32 Connect(ObjectType* aObject, MemberFn aMemberFunction)
	{
		return ConnectInternal(SC_Function<Signature>(aObject, aMemberFunction));
	}

	bool IsConnected(void* aIdentifier)
	{
		for (SC_Function<Signature>& callback : this->mCallbacks)
		{
			if (callback.GetUserData() == aIdentifier)
				return true;
		}
		return false;
	}

	void Reset()
	{
		this->mCallbacks.RemoveAll();
	}

	void DetachAll()
	{
		for (SC_Function<Signature>& callback : this->mCallbacks)
			callback.Reset();
	}

	void Detach(void* aIdentifier)
	{
		for (SC_Function<Signature>& callback : this->mCallbacks)
		{
			if (callback.GetUserData() == aIdentifier)
				callback.Reset();
		}
	}

	void Detach(uint32 aIdentifier)
	{
		if (aIdentifier != 0 && aIdentifier <= this->mCallbacks.Count())
		{
			this->mCallbacks[aIdentifier - 1].Reset();
		}
	}

	uint32 NumConnected() const 
	{
		uint32 numConnected = 0;
		for (const SC_Function<Signature>& callback : this->mCallbacks)
		{
			if (callback)
				++numConnected;
		}
		return numConnected;
	}

private:
	uint32 ConnectInternal(const SC_Function<Signature>& aCallback)
	{
		uint32 n = this->mCallbacks.Count();
		for (uint32 i = 0; i < n; ++i)
		{
			if (!this->mCallbacks[i])
			{
				this->mCallbacks[i] = aCallback;
				return i + 1;
			}
		}

		this->mCallbacks.Add(aCallback);
		return n + 1;
	}
};

template <class Type>
struct SC_AllowMemcpyRelocation<SC_Slot<Type>>
{
	static const bool mValue = true;
};