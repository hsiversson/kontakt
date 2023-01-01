//ProjectFilter(Async)
#pragma once
#include <future>
#include "SC_Ref.h"
#include <iostream>

#define SC_ENABLE_FUTURE_EXCEPTION_HANDLER (0)

template<class T>
class SC_Future : public SC_ReferenceCounted
{
public:
	SC_Future() {}
	SC_Future(std::shared_future<T>&& aFuture) : mFuture(aFuture) {}
	SC_Future(SC_Future&& aOther) : mFuture(SC_Move(aOther.mFuture)) { aOther.mFuture = std::shared_future<T>(); }
	SC_Future(const SC_Future& aOther) : mFuture(aOther.mFuture) {}
	void operator=(const SC_Future& aOther) { mFuture = aOther.mFuture; }
	~SC_Future() {}

	T GetValue() const // Block until value is available and retrieve it.
	{ 
		Wait();

#if SC_ENABLE_FUTURE_EXCEPTION_HANDLER
		try 
		{
			return mFuture.get();
		}
		catch (const std::future_error& e) 
		{
			SC_ERROR("Future threw an exception with code: {} - message: {}", e.code(), e.what());
		}
		return T();
#else
		return mFuture.get();
#endif // SC_ENABLE_FUTURE_EXCEPTION_HANDLER
	}

	bool IsReady() const
	{
		if (!mFuture.valid())
			return false;
		return mFuture.wait_for(std::chrono::microseconds(0)) == std::future_status::ready;
	}
	bool Wait(uint32 aMilliseconds = 0) const
	{
		if (!mFuture.valid())
			return false;

		if (aMilliseconds)
		{
			std::future_status status = mFuture.wait_for(std::chrono::milliseconds(aMilliseconds));
			return status == std::future_status::ready;
		}
		else
		{
			mFuture.wait();
			return true;
		}
	}

private:
	std::shared_future<T> mFuture;
};

template<class T>
class SC_Promise : public SC_ReferenceCounted
{
public:
	SC_Promise() {}
	SC_Promise(const SC_Promise&) = delete;
	void operator=(const SC_Promise&) = delete;
	~SC_Promise() {}

	void SetValue(const T& aValue) { mPromise.set_value(aValue); }
	void SetValue(T&& aValue) { mPromise.set_value(SC_Move(aValue)); }

	SC_Future<T> GetFuture() { return SC_Future<T>(mPromise.get_future()); }

private:
	std::promise<T> mPromise;
};

template<>
class SC_Promise<void> : public SC_ReferenceCounted
{
public:
	SC_Promise() {}
	SC_Promise(const SC_Promise&) = delete;
	void operator=(const SC_Promise&) = delete;
	~SC_Promise() {}

	void SetValue() { mPromise.set_value(); }

	SC_Future<void> GetFuture() { return SC_Future<void>(mPromise.get_future()); }

private:
	std::promise<void> mPromise;
};