#include "util/mutexlock.h"
#include "port/port.h"
#include "gtest/gtest.h"

#include <thread>
#include <atomic>
#include <chrono>

namespace leveldb {

// Test that MutexLock locks the mutex on construction and unlocks on destruction
TEST(MutexLockTest_296, LockAndUnlockOnScope_296) {
  port::Mutex mu;
  {
    MutexLock lock(&mu);
    // Mutex should be held here. We can verify by checking that
    // another attempt to lock in a different thread would block.
    // Instead, we simply verify the object is constructible and destructible.
  }
  // After the scope, the mutex should be unlocked.
  // Verify by locking it again successfully.
  mu.Lock();
  mu.Unlock();
}

// Test that MutexLock properly provides mutual exclusion between threads
TEST(MutexLockTest_296, MutualExclusionBetweenThreads_296) {
  port::Mutex mu;
  std::atomic<int> shared_value(0);
  std::atomic<bool> thread_started(false);
  std::atomic<bool> thread_acquired(false);

  // Lock the mutex in the main thread
  mu.Lock();

  // Start a thread that tries to acquire the same mutex via MutexLock
  std::thread t([&]() {
    thread_started.store(true);
    MutexLock lock(&mu);
    thread_acquired.store(true);
    shared_value.store(42);
  });

  // Wait for thread to start
  while (!thread_started.load()) {
    std::this_thread::yield();
  }

  // Give the other thread some time to attempt acquisition
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // The other thread should NOT have acquired the lock yet
  EXPECT_FALSE(thread_acquired.load());
  EXPECT_EQ(shared_value.load(), 0);

  // Release the mutex so the other thread can proceed
  mu.Unlock();

  t.join();

  // Now the thread should have acquired and released the lock
  EXPECT_TRUE(thread_acquired.load());
  EXPECT_EQ(shared_value.load(), 42);
}

// Test that MutexLock unlocks the mutex when it goes out of scope (RAII)
TEST(MutexLockTest_296, RAIIUnlockOnDestruction_296) {
  port::Mutex mu;
  std::atomic<bool> inner_done(false);

  {
    MutexLock lock(&mu);
    inner_done.store(true);
  }

  EXPECT_TRUE(inner_done.load());

  // Mutex should be unlocked now; verify by locking from another thread
  std::atomic<bool> second_lock_acquired(false);
  std::thread t([&]() {
    MutexLock lock(&mu);
    second_lock_acquired.store(true);
  });

  t.join();
  EXPECT_TRUE(second_lock_acquired.load());
}

// Test multiple sequential lock/unlock cycles
TEST(MutexLockTest_296, MultipleSequentialLocks_296) {
  port::Mutex mu;

  for (int i = 0; i < 100; ++i) {
    MutexLock lock(&mu);
    // Each iteration should lock and unlock without issue
  }

  // Verify mutex is still usable after many cycles
  mu.Lock();
  mu.Unlock();
}

// Test that MutexLock provides correct protection for a shared counter
TEST(MutexLockTest_296, ProtectsSharedCounter_296) {
  port::Mutex mu;
  int counter = 0;
  const int kIterations = 10000;
  const int kThreads = 4;

  auto increment = [&]() {
    for (int i = 0; i < kIterations; ++i) {
      MutexLock lock(&mu);
      ++counter;
    }
  };

  std::vector<std::thread> threads;
  for (int i = 0; i < kThreads; ++i) {
    threads.emplace_back(increment);
  }

  for (auto& t : threads) {
    t.join();
  }

  EXPECT_EQ(counter, kIterations * kThreads);
}

// Test nested scopes with different MutexLock instances on different mutexes
TEST(MutexLockTest_296, NestedLocksOnDifferentMutexes_296) {
  port::Mutex mu1;
  port::Mutex mu2;

  {
    MutexLock lock1(&mu1);
    {
      MutexLock lock2(&mu2);
      // Both mutexes should be held here
    }
    // mu2 should be unlocked, mu1 still held
  }
  // Both should be unlocked

  // Verify both are unlocked
  mu1.Lock();
  mu1.Unlock();
  mu2.Lock();
  mu2.Unlock();
}

}  // namespace leveldb
