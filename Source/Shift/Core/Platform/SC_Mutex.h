//ProjectFilter(Async)
#pragma once

#include <mutex>

using SC_Mutex = std::mutex;

using SC_MutexLock = std::lock_guard<SC_Mutex>;
using SC_MutexLockUnique = std::unique_lock<SC_Mutex>;