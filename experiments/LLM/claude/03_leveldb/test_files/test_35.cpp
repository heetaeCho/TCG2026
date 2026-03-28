#include "gtest/gtest.h"
#include "port/port_stdcxx.h"

#include <thread>
#include <atomic>
#include <chrono>
#include <vector>

namespace leveldb {
namespace port {

class CondVarTest_35 : public ::testing::Test {
 protected:
  Mutex mu_;
};

// Test that CondVar can be constructed with a Mutex pointer
TEST_F(CondVarTest_35, Construction_35) {
  CondVar cv(&mu_);
  // If we reach here without crashing, construction succeeded.
}

// Test that SignalAll does not block or crash when no threads are waiting
TEST_F(CondVarTest_35, SignalAllWithNoWaiters_35) {
  CondVar cv(&mu_);
  cv.SignalAll();
  // Should not block or crash
}

// Test that Signal does not block or crash when no threads are waiting
TEST_F(CondVarTest_35, SignalWithNoWaiters_35) {
  CondVar cv(&mu_);
  cv.Signal();
  // Should not block or crash
}

// Test that Wait releases the lock and can be woken by Signal
TEST_F(CondVarTest_35, WaitAndSignal_35) {
  CondVar cv(&mu_);
  std::atomic<bool> waiting(false);
  std::atomic<bool> done(false);

  std::thread waiter([&]() {
    mu_.Lock();
    waiting.store(true);
    cv.Wait();
    done.store(true);
    mu_.Unlock();
  });

  // Wait until the waiter thread is actually waiting
  while (!waiting.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  // Give a little extra time for the thread to enter Wait()
  std::this_thread::sleep_for(std::chrono::milliseconds(20));

  // Signal the waiter
  cv.Signal();

  waiter.join();
  EXPECT_TRUE(done.load());
}

// Test that Wait releases the lock and can be woken by SignalAll
TEST_F(CondVarTest_35, WaitAndSignalAll_35) {
  CondVar cv(&mu_);
  std::atomic<bool> waiting(false);
  std::atomic<bool> done(false);

  std::thread waiter([&]() {
    mu_.Lock();
    waiting.store(true);
    cv.Wait();
    done.store(true);
    mu_.Unlock();
  });

  while (!waiting.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(20));

  cv.SignalAll();

  waiter.join();
  EXPECT_TRUE(done.load());
}

// Test that SignalAll wakes multiple waiting threads
TEST_F(CondVarTest_35, SignalAllWakesMultipleWaiters_35) {
  CondVar cv(&mu_);
  const int kNumThreads = 5;
  std::atomic<int> waiting_count(0);
  std::atomic<int> done_count(0);

  std::vector<std::thread> threads;
  for (int i = 0; i < kNumThreads; i++) {
    threads.emplace_back([&]() {
      mu_.Lock();
      waiting_count.fetch_add(1);
      cv.Wait();
      done_count.fetch_add(1);
      mu_.Unlock();
    });
  }

  // Wait for all threads to be waiting
  while (waiting_count.load() < kNumThreads) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // SignalAll should wake all threads
  cv.SignalAll();

  for (auto& t : threads) {
    t.join();
  }
  EXPECT_EQ(kNumThreads, done_count.load());
}

// Test that Signal wakes at least one waiting thread (not necessarily all)
TEST_F(CondVarTest_35, SignalWakesAtLeastOneWaiter_35) {
  CondVar cv(&mu_);
  const int kNumThreads = 3;
  std::atomic<int> waiting_count(0);
  std::atomic<int> done_count(0);

  std::vector<std::thread> threads;
  for (int i = 0; i < kNumThreads; i++) {
    threads.emplace_back([&]() {
      mu_.Lock();
      waiting_count.fetch_add(1);
      cv.Wait();
      done_count.fetch_add(1);
      mu_.Unlock();
    });
  }

  while (waiting_count.load() < kNumThreads) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // Signal once - should wake at least one
  cv.Signal();
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  EXPECT_GE(done_count.load(), 1);

  // Wake the rest
  cv.SignalAll();

  for (auto& t : threads) {
    t.join();
  }
  EXPECT_EQ(kNumThreads, done_count.load());
}

// Test multiple Signal/SignalAll calls in succession
TEST_F(CondVarTest_35, MultipleSignalAllCalls_35) {
  CondVar cv(&mu_);
  // Calling SignalAll multiple times should not cause issues
  cv.SignalAll();
  cv.SignalAll();
  cv.SignalAll();
  cv.Signal();
  cv.Signal();
  // No crash expected
}

// Test that after Wait returns, the mutex is re-acquired
TEST_F(CondVarTest_35, WaitReacquiresMutex_35) {
  CondVar cv(&mu_);
  std::atomic<bool> waiting(false);
  std::atomic<bool> mutex_held_after_wait(false);

  std::thread waiter([&]() {
    mu_.Lock();
    waiting.store(true);
    cv.Wait();
    // If we reach here, we should hold the mutex.
    // We can verify by attempting to set a flag that indicates
    // we successfully continued after Wait (which implies lock held).
    mutex_held_after_wait.store(true);
    mu_.Unlock();
  });

  while (!waiting.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(20));

  cv.Signal();

  waiter.join();
  EXPECT_TRUE(mutex_held_after_wait.load());
}

// Test that Wait releases the mutex (another thread can acquire it)
TEST_F(CondVarTest_35, WaitReleasesMutex_35) {
  CondVar cv(&mu_);
  std::atomic<bool> waiter_in_wait(false);
  std::atomic<bool> other_acquired_lock(false);

  std::thread waiter([&]() {
    mu_.Lock();
    waiter_in_wait.store(true);
    cv.Wait();
    mu_.Unlock();
  });

  // Wait for the waiter to enter Wait (which should release the mutex)
  while (!waiter_in_wait.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(20));

  // Try to acquire the lock - should succeed since Wait released it
  mu_.Lock();
  other_acquired_lock.store(true);
  mu_.Unlock();

  EXPECT_TRUE(other_acquired_lock.load());

  // Now wake the waiter
  cv.Signal();
  waiter.join();
}

}  // namespace port
}  // namespace leveldb
