// mutex_port_tests_31.cc
#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <future>
#include <thread>
#include <type_traits>
#include <vector>

#include "port/port_stdcxx.h"

using leveldb::port::Mutex;
using namespace std::chrono_literals;

// Verifies compile-time interface constraints (deleted copy/assign).
TEST(MutexTest_31, CopyAndAssignAreDeleted_31) {
  static_assert(!std::is_copy_constructible<Mutex>::value,
                "Mutex must not be copy-constructible");
  static_assert(!std::is_copy_assignable<Mutex>::value,
                "Mutex must not be copy-assignable");
  SUCCEED();
}

// Verifies that a second thread cannot progress past Lock() until Unlock() is called.
TEST(MutexTest_31, LockBlocksOtherThreadsUntilUnlock_31) {
  Mutex mu;
  std::atomic<bool> progressed{false};

  mu.Lock();  // Hold the lock in this thread.

  std::thread t([&] {
    mu.Lock();                // Should block until main thread unlocks.
    progressed.store(true);   // Observable side effect only after acquiring.
    mu.Unlock();
  });

  // Give the worker a moment to attempt Lock().
  std::this_thread::sleep_for(50ms);
  EXPECT_FALSE(progressed.load()) << "Worker should still be blocked";

  mu.Unlock();  // Release so worker can proceed.
  t.join();

  EXPECT_TRUE(progressed.load()) << "Worker should have acquired the lock after unlock";
}

// Verifies Unlock() allows progress within a reasonable timeframe (observable via future readiness).
TEST(MutexTest_31, UnlockAllowsProgressWithinTimeout_31) {
  Mutex mu;
  mu.Lock();

  std::promise<void> acquired;
  auto fut = acquired.get_future();

  std::thread t([&] {
    mu.Lock();       // Will block until main thread unlocks.
    acquired.set_value();
    mu.Unlock();
  });

  // While held, future should not be ready.
  EXPECT_EQ(fut.wait_for(50ms), std::future_status::timeout);

  mu.Unlock();  // Permit the worker to proceed.

  EXPECT_EQ(fut.wait_for(1s), std::future_status::ready)
      << "Worker did not acquire the lock in time after unlock";
  t.join();
}

// Verifies mutual exclusion by protecting a shared counter from races (observable final count).
TEST(MutexTest_31, ExclusiveAccessAcrossThreads_31) {
  Mutex mu;
  int counter = 0;

  const int kThreads = 8;
  const int kItersPerThread = 1000;

  std::vector<std::thread> threads;
  threads.reserve(kThreads);

  for (int i = 0; i < kThreads; ++i) {
    threads.emplace_back([&] {
      for (int j = 0; j < kItersPerThread; ++j) {
        mu.Lock();
        ++counter;  // Critical section guarded purely by the public interface.
        mu.Unlock();
      }
    });
  }

  for (auto& th : threads) th.join();

  EXPECT_EQ(counter, kThreads * kItersPerThread);
}

// If available in the interface, AssertHeld() should be callable while locked (no crash/UB observable).
TEST(MutexTest_31, AssertHeldAfterLock_NoCrash_31) {
  Mutex mu;
  mu.Lock();
  // Observable expectation: calling AssertHeld() while holding the lock should not fail/crash.
  mu.AssertHeld();
  mu.Unlock();
  SUCCEED();
}
