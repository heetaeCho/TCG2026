// MutexUnlock_tests_32.cc
#include <gtest/gtest.h>
#include <atomic>
#include <thread>
#include <condition_variable>
#include <chrono>

// Include the header under test
#include "port/port_stdcxx.h"

using namespace std::chrono_literals;

namespace leveldb {
namespace port {

class MutexTest_32 : public ::testing::Test {};

TEST(MutexTest_32, UnlockAllowsOtherThreadToAcquire_32) {
  Mutex m;
  std::atomic<bool> acquired{false};
  std::condition_variable cv;
  std::mutex cv_mu;

  m.Lock();  // Hold the lock so the worker must wait.

  std::thread worker([&] {
    m.Lock();  // Should block until main thread unlocks.
    acquired.store(true, std::memory_order_release);
    {
      std::lock_guard<std::mutex> lk(cv_mu);
    }
    cv.notify_one();
    m.Unlock();
  });

  // While still holding the lock, the worker should not have acquired it.
  std::this_thread::sleep_for(20ms);
  EXPECT_FALSE(acquired.load(std::memory_order_acquire));

  // Now release; this should let the worker proceed and signal.
  m.Unlock();

  std::unique_lock<std::mutex> lk(cv_mu);
  const bool notified = cv.wait_for(lk, 1s, [&] { return acquired.load(std::memory_order_acquire); });
  EXPECT_TRUE(notified) << "Worker did not acquire the mutex after Unlock";

  worker.join();
}

TEST(MutexTest_32, UnlockAllowsRelockBySameThread_32) {
  Mutex m;

  // Lock and unlock once.
  m.Lock();
  m.Unlock();

  // Re-acquire after unlocking (should succeed and not deadlock/crash).
  m.Lock();
  // If we reached here, relock succeeded.
  SUCCEED();
  m.Unlock();
}

TEST(MutexTest_32, UnlockWakesOneWaiterThenOthersOnSubsequentUnlocks_32) {
  Mutex m;
  std::atomic<int> ran{0};
  std::condition_variable cv;
  std::mutex cv_mu;

  m.Lock();  // Block both workers initially.

  auto worker = [&](int /*id*/) {
    m.Lock();            // Wait until available
    ran.fetch_add(1);    // Observable effect
    {
      std::lock_guard<std::mutex> lk(cv_mu);
    }
    cv.notify_one();     // Signal progress
    m.Unlock();
  };

  std::thread t1(worker, 1);
  std::thread t2(worker, 2);

  // Give threads a moment to start and block.
  std::this_thread::sleep_for(20ms);
  EXPECT_EQ(ran.load(), 0) << "No worker should pass while main holds the lock";

  // First unlock should wake exactly one waiter eventually.
  m.Unlock();
  {
    std::unique_lock<std::mutex> lk(cv_mu);
    bool one_done = cv.wait_for(lk, 1s, [&] { return ran.load() >= 1; });
    EXPECT_TRUE(one_done) << "At least one worker should have proceeded after first Unlock";
  }

  // Wait for the second worker to complete as well.
  {
    std::unique_lock<std::mutex> lk(cv_mu);
    bool two_done = cv.wait_for(lk, 1s, [&] { return ran.load() >= 2; });
    EXPECT_TRUE(two_done) << "Both workers should complete eventually";
  }

  t1.join();
  t2.join();
}

}  // namespace port
}  // namespace leveldb
