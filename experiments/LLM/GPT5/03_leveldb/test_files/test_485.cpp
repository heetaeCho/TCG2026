// File: util/mutexlock_test.cc

#include "util/mutexlock.h"
#include "port/port_stdcxx.h"

#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <thread>
#include <type_traits>

using leveldb::MutexLock;
using leveldb::port::Mutex;

namespace {

// Helper: small steady sleeps to avoid flakiness.
inline void SleepForMs(int ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

}  // namespace

// Verifies that constructing MutexLock acquires the mutex (so another thread
// trying to Lock() will block until the MutexLock is destroyed).
TEST(MutexLockTest_485, RAII_LocksAndUnlocks_BlockingBehavior_485) {
  Mutex mu;
  std::atomic<bool> worker_entered{false};
  std::atomic<bool> worker_exited{false};

  // Main thread acquires via RAII.
  {
    MutexLock hold(&mu);

    // Worker tries to enter; should block until 'hold' leaves scope.
    std::thread worker([&]() {
      mu.Lock();                        // blocks while RAII guard is alive
      worker_entered.store(true);
      mu.Unlock();
      worker_exited.store(true);
    });

    // Give worker a moment to attempt the lock.
    SleepForMs(30);

    // While RAII guard is alive, worker should not have entered.
    EXPECT_FALSE(worker_entered.load());

    // Clean up after scope to let worker proceed.
    worker.join();  // NOTE: If MutexLock didn't hold the lock, worker would have run immediately.
    // After the worker thread completes, it must have entered+exited.
    EXPECT_TRUE(worker_entered.load());
    EXPECT_TRUE(worker_exited.load());
  }
}

// After the MutexLock goes out of scope (destructor), the same thread
// can re-acquire the mutex normally.
TEST(MutexLockTest_485, DestructorUnlocks_AllowsRelockOnSameThread_485) {
  Mutex mu;

  {
    MutexLock hold(&mu);  // lock held
    // No explicit checks inside scope to avoid relying on internal state.
  }  // destructor should unlock here

  // If destructor didn’t unlock, this Lock() would deadlock; instead it should succeed.
  mu.Lock();
  mu.Unlock();
  SUCCEED();
}

// Basic mutual exclusion sanity across multiple threads using the *public*
// locking effects of MutexLock. We ensure only one thread claims the critical
// section at a time (observable via an atomic guard).
TEST(MutexLockTest_485, MutualExclusionAcrossThreads_485) {
  Mutex mu;
  std::atomic<bool> in_critical{false};
  std::atomic<int> entries{0};

  const int kThreads = 8;
  std::thread ts[kThreads];

  for (int i = 0; i < kThreads; ++i) {
    ts[i] = std::thread([&]() {
      // Each thread tries to enter once.
      MutexLock hold(&mu);
      // No other thread should be in the critical section at the same time.
      bool was_in = in_critical.exchange(true);
      EXPECT_FALSE(was_in) << "Two threads entered critical section concurrently";
      // Simulate work
      entries.fetch_add(1);
      SleepForMs(5);
      in_critical.store(false);
      // hold goes out of scope -> unlock
    });
  }

  for (int i = 0; i < kThreads; ++i) ts[i].join();

  // All threads should have entered exactly once.
  EXPECT_EQ(entries.load(), kThreads);
}

// Interface-level trait checks: the type is non-copyable and non-assignable.
// These checks are compile-time and do not rely on internal state.
TEST(MutexLockTest_485, NonCopyableNonAssignable_485) {
  static_assert(!std::is_copy_constructible<MutexLock>::value,
                "MutexLock should not be copy-constructible");
  static_assert(!std::is_copy_assignable<MutexLock>::value,
                "MutexLock should not be copy-assignable");
  SUCCEED();
}
