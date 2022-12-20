#pragma once

template<class T>
class SC_Ptr
{
public:
	SC_Ptr() : mObject(nullptr) {}
	SC_Ptr(T* aObject) : mObject(aObject) {}
	~SC_Ptr() { delete mObject; mObject = nullptr; }

	T* Get() const { return mObject; }
	T* operator->() const { return mObject; }
	T& operator*() const { return *mObject; }
	operator T* () const { return mObject; }
	operator bool() { return (mObject != nullptr); }

private:
	T* mObject;
};