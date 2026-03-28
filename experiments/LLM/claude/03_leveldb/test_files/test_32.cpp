#include "gtest/gtest.h"
#include "port/port_stdcxx.h"

namespace leveldb {
namespace port {

// Test that Mutex can be default constructed
TEST(MutexTest_32, DefaultConstruction_32) {
  Mutex mu;
  // If we get here without crashing, construction succeeded
  SUCCEED();
}

// Test basic Lock and Unlock cycle
TEST(MutexTest_32, LockAndUnlock_32) {
  Mutex mu;
  mu.Lock();
  mu.Unlock();
  SUCCEED();
}

// Test multiple Lock/Unlock cycles
TEST(MutexTest_32, MultipleLockUnlockCycles_32) {
  Mutex mu;
  for (int i = 0; i < 100; ++i) {
    mu.Lock();
    mu.Unlock();
  }
  SUCCEED();
}

// Test that Unlock releases the mutex so another lock can be acquired
TEST(MutexTest_32, UnlockAllowsRelock_32) {
  Mutex mu;
  mu.Lock();
  mu.Unlock();
  // Should be able to lock again after unlock
  mu.Lock();
  mu.Unlock();
  SUCCEED();
}

// Test AssertHeld doesn't crash when mutex is held
TEST(MutexTest_32, AssertHeldWhenLocked_32) {
  Mutex mu;
  mu.Lock();
  mu.AssertHeld();
  mu.Unlock();
  SUCCEED();
}

// Test that mutex works correctly with multiple threads
TEST(MutexTest_32, ConcurrentAccess_32) {
  Mutex mu;
  int shared_counter = 0;
  const int kIterations = 1000;
  const int kThreads = 4;

  std::vector<std::thread> threads;
  for (int t = 0; t < kThreads; ++t) {
    threads.emplace_back([&]() {
      for (int i = 0; i < kIterations; ++i) {
        mu.Lock();
        ++shared_counter;
        mu.Unlock();
      }
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }

  EXPECT_EQ(shared_counter, kThreads * kIterations);
}

// Test that Unlock from one thread allows another thread to acquire
TEST(MutexTest_32, UnlockReleasesForOtherThread_32) {
  Mutex mu;
  bool flag = false;

  mu.Lock();

  std::thread t([&]() {
    mu.Lock();
    flag = true;
    mu.Unlock();
  });

  // Give the other thread a chance to attempt locking
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  EXPECT_FALSE(flag);  // Other thread should be blocked

  mu.Unlock();  // Release, allowing other thread to proceed

  t.join();
  EXPECT_TRUE(flag);
}

// Test rapid lock/unlock doesn't cause issues
TEST(MutexTest_32, RapidLockUnlock_32) {
  Mutex mu;
  for (int i = 0; i < 10000; ++i) {
    mu.Lock();
    mu.Unlock();
  }
  SUCCEED();
}

}  // namespace port
}  // namespace leveldb
