#include "util/mutexlock.h"
#include "port/port.h"
#include "gtest/gtest.h"

#include <thread>
#include <atomic>
#include <chrono>

namespace leveldb {

// Test that MutexLock acquires the mutex on construction and releases on destruction
TEST(MutexLockTest_485, LockAndUnlockOnScopeEntry_485) {
  port::Mutex mu;
  {
    MutexLock lock(&mu);
    // If we got here, the mutex was successfully locked.
    // The destructor should unlock it when we leave this scope.
  }
  // Verify the mutex is unlocked by locking it again successfully.
  mu.Lock();
  mu.Unlock();
}

// Test that MutexLock actually holds the lock (mutual exclusion)
TEST(MutexLockTest_485, MutualExclusion_485) {
  port::Mutex mu;
  std::atomic<int> shared_value(0);
  std::atomic<bool> thread_started(false);
  std::atomic<bool> thread_acquired(false);

  {
    MutexLock lock(&mu);
    // Start a thread that tries to acquire the same mutex
    std::thread t([&]() {
      thread_started.store(true);
      MutexLock inner_lock(&mu);
      thread_acquired.store(true);
      shared_value.store(42);
    });

    // Wait for the thread to start
    while (!thread_started.load()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    // Give the thread some time to try to acquire the lock
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // The other thread should NOT have acquired the lock yet
    EXPECT_FALSE(thread_acquired.load());
    EXPECT_EQ(0, shared_value.load());

    // MutexLock destructor runs here, releasing the lock
    t.detach();
    // We need to wait for the thread but we detached it.
    // Let's rejoin differently.
    // Actually let's not detach - fix this:
    // We need to join after releasing the lock.
    // Restructure: keep thread handle, join after scope.
    // Let me redo with proper join.
    
    // Wait for thread to finish after lock is released
    // But we can't join a detached thread. Let's fix:
    // This approach is flawed. Let me just let the scope end and join outside.
    // For now, sleep and check.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  // After releasing the lock, the thread should eventually acquire it
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  EXPECT_TRUE(thread_acquired.load());
  EXPECT_EQ(42, shared_value.load());
}

// Test that after MutexLock is destroyed, the mutex can be re-acquired
TEST(MutexLockTest_485, UnlocksOnDestruction_485) {
  port::Mutex mu;
  
  // Lock and unlock via MutexLock
  {
    MutexLock lock(&mu);
  }
  
  // Should be able to lock again, proving it was unlocked
  {
    MutexLock lock2(&mu);
  }
}

// Test mutual exclusion with proper thread join
TEST(MutexLockTest_485, ProperMutualExclusionWithJoin_485) {
  port::Mutex mu;
  std::atomic<int> counter(0);

  auto increment = [&]() {
    for (int i = 0; i < 1000; i++) {
      MutexLock lock(&mu);
      int val = counter.load();
      counter.store(val + 1);
    }
  };

  std::thread t1(increment);
  std::thread t2(increment);
  
  t1.join();
  t2.join();

  EXPECT_EQ(2000, counter.load());
}

// Test that nested scopes with MutexLock on different mutexes work correctly
TEST(MutexLockTest_485, MultipleMutexes_485) {
  port::Mutex mu1;
  port::Mutex mu2;

  {
    MutexLock lock1(&mu1);
    {
      MutexLock lock2(&mu2);
      // Both mutexes locked
    }
    // mu2 unlocked, mu1 still locked
  }
  // Both unlocked
  
  // Verify both can be locked again
  mu1.Lock();
  mu2.Lock();
  mu2.Unlock();
  mu1.Unlock();
}

// Test that MutexLock works correctly with a single quick lock/unlock cycle
TEST(MutexLockTest_485, QuickLockUnlock_485) {
  port::Mutex mu;
  for (int i = 0; i < 100; i++) {
    MutexLock lock(&mu);
  }
  // If we get here without deadlock, the test passes
  mu.Lock();
  mu.Unlock();
}

}  // namespace leveldb
#include "util/mutexlock.h"
#include "port/port.h"
#include "gtest/gtest.h"

#include <thread>
#include <atomic>
#include <chrono>

namespace leveldb {

// Test that MutexLock acquires the mutex on construction and releases on destruction
TEST(MutexLockTest_485, LockAndUnlockOnScope_485) {
  port::Mutex mu;
  {
    MutexLock lock(&mu);
    // Lock acquired; destructor will release it
  }
  // Verify mutex is unlocked by acquiring it again
  mu.Lock();
  mu.Unlock();
}

// Test that after MutexLock is destroyed, the mutex can be re-acquired
TEST(MutexLockTest_485, UnlocksOnDestruction_485) {
  port::Mutex mu;
  {
    MutexLock lock(&mu);
  }
  {
    MutexLock lock2(&mu);
  }
}

// Test mutual exclusion: concurrent threads with MutexLock produce correct results
TEST(MutexLockTest_485, MutualExclusionCounterTest_485) {
  port::Mutex mu;
  int counter = 0;

  auto increment = [&]() {
    for (int i = 0; i < 10000; i++) {
      MutexLock lock(&mu);
      counter++;
    }
  };

  std::thread t1(increment);
  std::thread t2(increment);
  std::thread t3(increment);

  t1.join();
  t2.join();
  t3.join();

  EXPECT_EQ(30000, counter);
}

// Test that MutexLock blocks a second thread until released
TEST(MutexLockTest_485, BlocksUntilReleased_485) {
  port::Mutex mu;
  std::atomic<bool> locked_by_main(false);
  std::atomic<bool> thread_acquired(false);

  mu.Lock();
  locked_by_main.store(true);

  std::thread t([&]() {
    // This should block until main thread unlocks
    MutexLock lock(&mu);
    thread_acquired.store(true);
  });

  // Give thread time to attempt to acquire
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  EXPECT_FALSE(thread_acquired.load());

  // Release the lock
  mu.Unlock();

  t.join();
  EXPECT_TRUE(thread_acquired.load());
}

// Test multiple MutexLock instances on different mutexes
TEST(MutexLockTest_485, MultipleMutexes_485) {
  port::Mutex mu1;
  port::Mutex mu2;

  {
    MutexLock lock1(&mu1);
    {
      MutexLock lock2(&mu2);
    }
  }
  // Both unlocked; verify by locking again
  mu1.Lock();
  mu2.Lock();
  mu2.Unlock();
  mu1.Unlock();
}

// Test repeated lock/unlock cycles don't deadlock
TEST(MutexLockTest_485, RepeatedLockUnlock_485) {
  port::Mutex mu;
  for (int i = 0; i < 1000; i++) {
    MutexLock lock(&mu);
  }
  mu.Lock();
  mu.Unlock();
}

}  // namespace leveldb
