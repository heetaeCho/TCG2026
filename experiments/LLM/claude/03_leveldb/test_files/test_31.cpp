#include "gtest/gtest.h"
#include "port/port_stdcxx.h"
#include <thread>
#include <vector>
#include <atomic>

namespace leveldb {
namespace port {

// Test that Lock() can be called and the mutex is acquired
TEST(MutexTest_31, LockBasic_31) {
  Mutex mu;
  mu.Lock();
  // If we got here, Lock() succeeded
  mu.Unlock();
}

// Test that Lock() and Unlock() can be called in sequence
TEST(MutexTest_31, LockUnlockSequence_31) {
  Mutex mu;
  mu.Lock();
  mu.Unlock();
  // Lock again to verify mutex is reusable after unlock
  mu.Lock();
  mu.Unlock();
}

// Test that Lock() provides mutual exclusion between threads
TEST(MutexTest_31, LockProvidesMutualExclusion_31) {
  Mutex mu;
  std::atomic<int> counter{0};
  const int kIterations = 10000;
  const int kThreads = 4;

  auto worker = [&]() {
    for (int i = 0; i < kIterations; ++i) {
      mu.Lock();
      // Non-atomic increment protected by mutex
      int val = counter.load(std::memory_order_relaxed);
      counter.store(val + 1, std::memory_order_relaxed);
      mu.Unlock();
    }
  };

  std::vector<std::thread> threads;
  for (int i = 0; i < kThreads; ++i) {
    threads.emplace_back(worker);
  }
  for (auto& t : threads) {
    t.join();
  }

  EXPECT_EQ(counter.load(), kThreads * kIterations);
}

// Test that Lock() blocks a second thread until Unlock() is called
TEST(MutexTest_31, LockBlocksOtherThread_31) {
  Mutex mu;
  std::atomic<bool> locked_by_main{false};
  std::atomic<bool> thread_acquired{false};

  mu.Lock();
  locked_by_main.store(true);

  std::thread t([&]() {
    // This should block until main thread unlocks
    mu.Lock();
    thread_acquired.store(true);
    mu.Unlock();
  });

  // Give the thread some time to attempt to acquire the lock
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  // The thread should not have acquired the lock yet
  EXPECT_FALSE(thread_acquired.load());

  mu.Unlock();

  t.join();
  // Now the thread should have acquired and released the lock
  EXPECT_TRUE(thread_acquired.load());
}

// Test multiple Lock/Unlock cycles work correctly
TEST(MutexTest_31, MultipleLockUnlockCycles_31) {
  Mutex mu;
  for (int i = 0; i < 1000; ++i) {
    mu.Lock();
    mu.Unlock();
  }
}

// Test AssertHeld can be called while lock is held
TEST(MutexTest_31, AssertHeldWhileLocked_31) {
  Mutex mu;
  mu.Lock();
  mu.AssertHeld();  // Should not crash/assert
  mu.Unlock();
}

// Test that Lock works correctly with multiple mutexes
TEST(MutexTest_31, MultipleMutexesIndependent_31) {
  Mutex mu1;
  Mutex mu2;

  mu1.Lock();
  mu2.Lock();

  // Both should be independently lockable
  mu1.Unlock();
  mu2.Unlock();
}

// Test that Lock and Unlock work with interleaved mutex operations
TEST(MutexTest_31, InterleavedMutexOperations_31) {
  Mutex mu1;
  Mutex mu2;

  mu1.Lock();
  mu2.Lock();
  mu1.Unlock();
  mu1.Lock();
  mu2.Unlock();
  mu1.Unlock();
}

}  // namespace port
}  // namespace leveldb
