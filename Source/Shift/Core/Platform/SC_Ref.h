//ProjectFilter(Memory)
#pragma once

template<class T> class SC_Ref;

#pragma pack(push, 4)
class SC_ReferenceCounted
{
public:
	SC_ReferenceCounted();
	SC_ReferenceCounted(const SC_ReferenceCounted&);

	SC_ReferenceCounted& operator=(const SC_ReferenceCounted&);

	void IncrementRef() const;
	void DecrementRef() const;

	uint32 GetRefCount() const;

protected:
	virtual ~SC_ReferenceCounted();
	virtual bool CanDestruct(volatile uint32& aRefCount);

private:
	mutable volatile uint32 mRefCount;
};
#pragma pack(pop)

template <class T>
class SC_Ref
{
	template<class U>
	struct SC_ReferenceCountedBase { using Type = SC_ReferenceCounted; };

	template<class U>
	struct SC_ReferenceCountedBase<const U> { using Type = const SC_ReferenceCounted; };

	using BaseType = class SC_ReferenceCountedBase<T>::Type;

	template<class U> friend class SC_Ref;

public:
	SC_Ref();
	SC_Ref(T* aObject);
	SC_Ref(const SC_Ref& aRef);

	~SC_Ref();

	template<class Y>
	SC_Ref(const SC_Ref<Y>& aRef)
	{
		T* obj = aRef.Get();
		mObject = obj;
		if (mObject)
			mObject->IncrementRef();
	}

	template<class U>
	SC_Ref(SC_Ref<U>&& aRef)
	{
		static_assert(std::is_convertible<U*, T*>::value, "Trying to cast object into invalid type.");
		mObject = aRef.mObject;
		aRef.mObject = nullptr;
	}

	SC_Ref& operator=(T* aObject);
	SC_Ref& operator=(const SC_Ref& aRef);
	SC_Ref& operator=(SC_Ref&& aRef) noexcept;

	template<class Y>
	SC_Ref& operator=(const SC_Ref<Y>& aObject)
	{
		Reset(aObject);
		return *this;
	}

	void Reset();
	void Reset(T* aObject);
	T* Detach();

	T* Get() const { return static_cast<T*>(mObject); }
	T* operator->() const { return static_cast<T*>(mObject); }
	T& operator*() const { return *static_cast<T*>(mObject); }
	operator T* () const { return static_cast<T*>(mObject); }
	bool operator!() const { return !mObject; }

	template<class Y>
	bool operator==(const SC_Ref<Y>& aRef) const { return mObject == aRef.mObject; }
	template<class Y>
	bool operator!=(const SC_Ref<Y>& aRef) const { return mObject != aRef.mObject; }
private:
	BaseType* mObject;

	void operator[](uint32) {} // disable index operator
};

template<class T>
inline SC_Ref<T>::SC_Ref() 
	: mObject(nullptr)
{
}

template<class T>
inline SC_Ref<T>::SC_Ref(T* aObject) 
	: mObject(aObject)
{
	if (mObject)
		mObject->IncrementRef();
}

template<class T>
inline SC_Ref<T>::SC_Ref(const SC_Ref& aRef)
{
	BaseType* obj = aRef.mObject;
	mObject = obj;
	if (mObject)
		mObject->IncrementRef();
}

template<class T>
inline SC_Ref<T>::~SC_Ref()
{
	if (BaseType* obj = mObject)
		obj->DecrementRef();
}

template<class T>
inline SC_Ref<T>& SC_Ref<T>::operator=(T* aObject)
{
	Reset(aObject);
	return *this;
}

template<class T>
inline SC_Ref<T>& SC_Ref<T>::operator=(const SC_Ref& aRef)
{
	BaseType* oldObj = mObject;
	BaseType* newObj = aRef.mObject;
	if (oldObj != newObj)
	{
		mObject = newObj;
		if (mObject)
			mObject->IncrementRef();
		if (oldObj)
			oldObj->DecrementRef();
	}
	return *this;
}

template<class T>
inline SC_Ref<T>& SC_Ref<T>::operator=(SC_Ref&& aRef) noexcept
{
	BaseType* oldObj = mObject;
	BaseType* newObj = aRef.mObject;
	if (oldObj != newObj)
	{
		mObject = newObj;
		aRef.mObject = nullptr;
		if (oldObj)
			oldObj->DecrementRef();
	}
	return *this;
}

template<class T>
void SC_Ref<T>::Reset()
{
	BaseType* oldObj = mObject;
	if (oldObj)
	{
		mObject = nullptr;
		oldObj->DecrementRef();
	}
}

template<class T>
inline void SC_Ref<T>::Reset(T* aObject)
{
	const BaseType* oldObj = mObject;
	if (oldObj != aObject)
	{
		mObject = aObject;

		if (mObject)
			mObject->IncrementRef();
		if (oldObj)
			oldObj->DecrementRef();
	}
}

template<class T>
inline T* SC_Ref<T>::Detach()
{
	T* obj = static_cast<T*>(mObject);
	mObject = nullptr;
	return obj;
}
