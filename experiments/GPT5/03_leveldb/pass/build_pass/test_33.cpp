// File: condvar_wait_test_33.cc
#include "port/port_stdcxx.h"

#include <gtest/gtest.h>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

using leveldb::port::CondVar;
using leveldb::port::Mutex;

class CondVarTest_33 : public ::testing::Test {
protected:
  // Helper: wait until predicate is true or timeout elapses.
  template <typename Pred>
  static bool SpinUntil(Pred pred,
                        std::chrono::milliseconds timeout = std::chrono::milliseconds(2000)) {
    const auto start = std::chrono::steady_clock::now();
    while (!pred()) {
      if (std::chrono::steady_clock::now() - start > timeout) return false;
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return true;
  }
};

// Verifies a single waiter unblocks after a matching Signal.
TEST_F(CondVarTest_33, WaitUnblocksOnSignal_33) {
  Mutex mu;
  CondVar cv(&mu);

  std::atomic<bool> waiting{false};
  bool ready = false;  // Guarded by mu

  std::thread t([&] {
    mu.Lock();
    // Enter the typical predicate loop with the mutex held.
    while (!ready) {
      waiting.store(true, std::memory_order_release);
      cv.Wait();  // Should block until signaled.
    }
    mu.Unlock();
  });

  // Wait until the thread has reached the wait state.
  ASSERT_TRUE(SpinUntil([&] { return waiting.load(std::memory_order_acquire); }));

  // Now signal while holding the mutex and updating the predicate.
  mu.Lock();
  ready = true;
  cv.Signal();
  mu.Unlock();

  // Join should complete if Wait unblocks correctly.
  t.join();
  SUCCEED();
}

// Verifies SignalAll wakes all waiting threads that are waiting on the same predicate.
TEST_F(CondVarTest_33, SignalAllWakesAll_33) {
  Mutex mu;
  CondVar cv(&mu);

  constexpr int kWaiters = 6;
  std::atomic<int> waiting_count{0};
  bool go = false;  // Guarded by mu

  std::vector<std::thread> threads;
  threads.reserve(kWaiters);

  for (int i = 0; i < kWaiters; ++i) {
    threads.emplace_back([&] {
      mu.Lock();
      waiting_count.fetch_add(1, std::memory_order_acq_rel);
      while (!go) {
        cv.Wait();
      }
      mu.Unlock();
    });
  }

  // Ensure all threads are waiting.
  ASSERT_TRUE(CondVarTest_33::SpinUntil([&] { return waiting_count.load() == kWaiters; }));

  // Flip predicate and wake everyone.
  mu.Lock();
  go = true;
  cv.SignalAll();
  mu.Unlock();

  for (auto& th : threads) th.join();
  SUCCEED();
}

// Verifies that Wait releases the mutex while blocked and then re-acquires it upon wakeup.
// Observable behavior: another thread can acquire the mutex while the waiter is blocked.
TEST_F(CondVarTest_33, WaitReleasesAndReacquiresMutex_33) {
  Mutex mu;
  CondVar cv(&mu);

  std::atomic<bool> waiter_waiting{false};
  std::atomic<bool> worker_acquired{false};
  bool proceed = false;  // Guarded by mu

  // Waiter thread: waits on the condition.
  std::thread waiter([&] {
    mu.Lock();
    while (!proceed) {
      waiter_waiting.store(true, std::memory_order_release);
      cv.Wait();  // Should release mu while waiting, then re-acquire before returning.
    }
    mu.Unlock();
  });

  // Ensure waiter is in Wait (or about to call it).
  ASSERT_TRUE(SpinUntil([&] { return waiter_waiting.load(std::memory_order_acquire); }));

  // Worker tries to lock the mutex; this should succeed only if Wait has released it.
  std::thread worker([&] {
    mu.Lock();  // This must succeed if Wait released the lock internally.
    worker_acquired.store(true, std::memory_order_release);
    // Set predicate and signal to resume waiter.
    proceed = true;
    cv.Signal();
    mu.Unlock();
  });

  // Confirm the worker managed to acquire the mutex within a reasonable time.
  ASSERT_TRUE(SpinUntil([&] { return worker_acquired.load(std::memory_order_acquire); }));

  worker.join();
  waiter.join();
  SUCCEED();
}
