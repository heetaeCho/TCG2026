// File: condvar_signal_test.cc
#include <gtest/gtest.h>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

// Header under test
#include "port/port_stdcxx.h"

using leveldb::port::CondVar;
using leveldb::port::Mutex;

class CondVarSignalTest_34 : public ::testing::Test {
protected:
  Mutex mu_;
  CondVar cv_{&mu_};
};

// Helper: waiters block until cv_.Wait() returns, then increment `woken`.
static void WaiterBody(Mutex* mu, CondVar* cv, std::atomic<int>* arrived, std::atomic<int>* woken, std::atomic<bool>* keep_waiting) {
  // Tell the test we've arrived and are about to wait.
  {
    mu->Lock();
    arrived->fetch_add(1, std::memory_order_acq_rel);

    // Wait until signaled; loop guards against spurious wakeups.
    while (keep_waiting->load(std::memory_order_acquire)) {
      cv->Wait();
    }
    // Once released by the test (keep_waiting=false), we still pass through one Wait wakeup.
    woken->fetch_add(1, std::memory_order_acq_rel);
    mu->Unlock();
  }
}

// 1) Signal wakes exactly one waiter when multiple are waiting.
TEST_F(CondVarSignalTest_34, SignalWakesExactlyOneOfTwo_34) {
  std::atomic<int> arrived{0};
  std::atomic<int> woken{0};
  std::atomic<bool> keep_waiting{true};

  std::thread t1(WaiterBody, &mu_, &cv_, &arrived, &woken, &keep_waiting);
  std::thread t2(WaiterBody, &mu_, &cv_, &arrived, &woken, &keep_waiting);

  // Wait until both waiters have locked and are ready to Wait().
  while (arrived.load(std::memory_order_acquire) < 2) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  // First Signal should wake exactly one waiter.
  mu_.Lock();
  cv_.Signal();
  mu_.Unlock();

  // Give the woken thread a brief moment to run.
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  EXPECT_EQ(woken.load(std::memory_order_acquire), 1);

  // Second Signal should wake the remaining waiter.
  mu_.Lock();
  cv_.Signal();
  mu_.Unlock();

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  EXPECT_EQ(woken.load(std::memory_order_acquire), 2);

  // Allow both threads to exit their wait loops safely.
  keep_waiting.store(false, std::memory_order_release);
  // A SignalAll ensures exit even if a thread is between checks.
  mu_.Lock();
  cv_.SignalAll();
  mu_.Unlock();

  t1.join();
  t2.join();
}

// 2) Signal with no waiters is a no-op (doesn't crash/hang) and does not wake future waiters.
TEST_F(CondVarSignalTest_34, SignalWithNoWaitersDoesNotWakeFutureWaiter_34) {
  // Signal when nobody is waiting; should be a no-op.
  mu_.Lock();
  cv_.Signal();
  mu_.Unlock();

  std::atomic<int> arrived{0};
  std::atomic<int> woken{0};
  std::atomic<bool> keep_waiting{true};

  std::thread t(WaiterBody, &mu_, &cv_, &arrived, &woken, &keep_waiting);

  // Ensure the waiter reached the waiting state.
  while (arrived.load(std::memory_order_acquire) < 1) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  // Give a short grace period: since we signaled earlier (no waiters), the new waiter should *not* be woken.
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  EXPECT_EQ(woken.load(std::memory_order_acquire), 0) << "Future waiter should not receive past signal";

  // Now wake it intentionally.
  mu_.Lock();
  cv_.Signal();
  mu_.Unlock();

  // Allow it to observe keep_waiting=false and exit.
  keep_waiting.store(false, std::memory_order_release);
  mu_.Lock();
  cv_.SignalAll();  // ensure progress out of the loop
  mu_.Unlock();

  t.join();
  EXPECT_EQ(woken.load(std::memory_order_acquire), 1);
}

// 3) Multiple signals only wake up to the number of waiting threads (no extra wakeups).
TEST_F(CondVarSignalTest_34, MultipleSignalsWakeAtMostNumWaiters_34) {
  constexpr int kWaiters = 5;
  constexpr int kSignals = 3;

  std::atomic<int> arrived{0};
  std::atomic<int> woken{0};
  std::atomic<bool> keep_waiting{true};

  std::vector<std::thread> threads;
  threads.reserve(kWaiters);
  for (int i = 0; i < kWaiters; ++i) {
    threads.emplace_back(WaiterBody, &mu_, &cv_, &arrived, &woken, &keep_waiting);
  }

  while (arrived.load(std::memory_order_acquire) < kWaiters) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  // Issue fewer signals than waiters.
  for (int i = 0; i < kSignals; ++i) {
    mu_.Lock();
    cv_.Signal();
    mu_.Unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }

  // Expect exactly kSignals waiters to have progressed so far.
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  EXPECT_EQ(woken.load(std::memory_order_acquire), kSignals);

  // Clean up: release all remaining waiters.
  keep_waiting.store(false, std::memory_order_release);
  mu_.Lock();
  cv_.SignalAll();
  mu_.Unlock();

  for (auto& th : threads) th.join();
  EXPECT_EQ(woken.load(std::memory_order_acquire), kWaiters);
}

// 4) Signal wakes a waiter that is legitimately blocked (sanity under quick signal-after-wait pattern).
TEST_F(CondVarSignalTest_34, SignalWakesBlockedWaiter_Sanity_34) {
  std::atomic<int> arrived{0};
  std::atomic<int> woken{0};
  std::atomic<bool> keep_waiting{true};

  std::thread t(WaiterBody, &mu_, &cv_, &arrived, &woken, &keep_waiting);

  while (arrived.load(std::memory_order_acquire) < 1) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  // Wake it.
  mu_.Lock();
  cv_.Signal();
  mu_.Unlock();

  // Give time to run.
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  EXPECT_EQ(woken.load(std::memory_order_acquire), 1);

  // Ensure thread exits cleanly.
  keep_waiting.store(false, std::memory_order_release);
  mu_.Lock();
  cv_.SignalAll();
  mu_.Unlock();

  t.join();
}
