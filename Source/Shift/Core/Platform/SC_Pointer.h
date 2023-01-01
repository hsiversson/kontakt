//ProjectFilter(Memory)
#pragma once

template<class T>
class SC_Ptr
{
public:
	SC_Ptr() : mObject(nullptr) {}
	SC_Ptr(T* aPtr) : mObject(aPtr) {}
	SC_Ptr(std::nullptr_t) : mObject(nullptr) {}
	SC_Ptr(const SC_Ptr<T>&) = delete;
	SC_Ptr(SC_Ptr<T>&& aPtr) : mObject(aPtr.mObject) { aPtr.mObject = nullptr; }
	~SC_Ptr() { delete mObject; mObject = nullptr; }

	SC_Ptr<T>& operator=(SC_Ptr<T>&& aPtr)
	{
		if (mObject != aPtr.mObject)
			delete mObject;

		mObject = aPtr.mObject;
		aPtr.mObject = nullptr;
		return *this;
	}
	SC_Ptr<T>& operator=(const SC_Ptr<T>& aPtr) = delete;

	template<typename U>
	SC_Ptr(SC_Ptr<U>&& aPtr) : mObject(aPtr.mObject) { aPtr.mObject = nullptr; }

	T* Get() const { return mObject; }
	T* operator->() const { return mObject; }
	T& operator*() const { return *mObject; }
	operator T* () const { return mObject; }
	operator bool() { return (mObject != nullptr); }

private:
	template<typename U>
	friend class SC_Ptr;

	T* mObject;
};