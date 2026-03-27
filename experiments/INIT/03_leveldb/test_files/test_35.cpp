// File: condvar_signalall_test_35.cc

#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

// SUT
#include "port/port_stdcxx.h"

using namespace std::chrono_literals;

namespace leveldb {
namespace port {

class CondVarTest_35 : public ::testing::Test {
 protected:
  Mutex mu_;
  CondVar cv_{&mu_};

  // Shared state protected by mu_
  bool go_ = false;
  int awake_count_ = 0;

  // For coordinating the test harness itself (not the SUT)
  std::mutex harness_mu_;
  std::condition_variable harness_cv_;
  int waiting_count_ = 0;

  // Helper to spawn N waiter threads that:
  //   1) lock mu_
  //   2) announce "waiting" to the harness
  //   3) wait until go_ becomes true, using cv_.Wait()
  //   4) increment awake_count_ and unlock
  std::vector<std::thread> SpawnWaiters(int n) {
    std::vector<std::thread> threads;
    threads.reserve(n);
    for (int i = 0; i < n; ++i) {
      threads.emplace_back([this]() {
        mu_.Lock();
        {
          std::lock_guard<std::mutex> lk(harness_mu_);
          ++waiting_count_;
          harness_cv_.notify_all();
        }
        while (!go_) {
          cv_.Wait();  // Black-box wait; must be called with mu_ held
        }
        ++awake_count_;
        mu_.Unlock();
      });
    }
    return threads;
  }

  // Wait until the harness sees exactly n waiters ready (with timeout)
  bool WaitForWaiters(int n, std::chrono::milliseconds timeout = 2s) {
    std::unique_lock<std::mutex> lk(harness_mu_);
    return harness_cv_.wait_for(lk, timeout, [&] { return waiting_count_ == n; });
  }

  // Join all threads (best-effort; in these tests they should terminate cleanly)
  static void JoinAll(std::vector<std::thread>& ts) {
    for (auto& t : ts) {
      if (t.joinable()) t.join();
    }
  }
};

// Normal operation: SignalAll wakes all current waiters.
TEST_F(CondVarTest_35, SignalAll_WakesAllWaiters_35) {
  constexpr int kN = 6;
  auto waiters = SpawnWaiters(kN);

  ASSERT_TRUE(WaitForWaiters(kN)) << "Waiters did not reach Wait() in time";

  // Flip the predicate and wake all waiters.
  mu_.Lock();
  go_ = true;
  cv_.SignalAll();  // SUT call
  mu_.Unlock();

  // All waiters should finish.
  JoinAll(waiters);

  // Verify observable outcome via public effects.
  mu_.Lock();
  EXPECT_EQ(awake_count_, kN);
  mu_.Unlock();
}

// Boundary: SignalAll when there are no waiters should be a no-op (no crash/hang).
TEST_F(CondVarTest_35, SignalAll_NoWaiters_NoOp_35) {
  // No threads are waiting yet.
  mu_.Lock();
  // Calling SignalAll should be safe and return promptly.
  cv_.SignalAll();  // SUT call
  mu_.Unlock();

  // Now start a waiter after the fact; since go_ is false and nobody signaled now,
  // it should block. We'll clean it up by signaling afterwards.
  auto waiters = SpawnWaiters(1);
  ASSERT_TRUE(WaitForWaiters(1));

  // Wake it so the test can finish.
  mu_.Lock();
  go_ = true;
  cv_.SignalAll();  // SUT call to release the late waiter
  mu_.Unlock();

  JoinAll(waiters);

  mu_.Lock();
  EXPECT_EQ(awake_count_, 1);
  mu_.Unlock();
}

// Robustness: Multiple SignalAll calls do not over-wake but still release all waiters once.
TEST_F(CondVarTest_35, SignalAll_MultipleCalls_35) {
  constexpr int kN = 8;
  auto waiters = SpawnWaiters(kN);
  ASSERT_TRUE(WaitForWaiters(kN));

  mu_.Lock();
  // Call SignalAll even before flipping the predicate — waiters use a predicate loop,
  // so they must remain blocked until go_ becomes true.
  cv_.SignalAll();  // spurious broadcast should not release them without predicate change
  // Now make the condition true and broadcast again.
  go_ = true;
  cv_.SignalAll();  // actual release
  // And one more time for good measure; should be harmless.
  cv_.SignalAll();
  mu_.Unlock();

  JoinAll(waiters);

  mu_.Lock();
  EXPECT_EQ(awake_count_, kN);
  mu_.Unlock();
}

}  // namespace port
}  // namespace leveldb
