#include "gtest/gtest.h"
#include "port/port_stdcxx.h"

#include <thread>
#include <atomic>
#include <chrono>

namespace leveldb {
namespace port {

class CondVarTest_34 : public ::testing::Test {
 protected:
  Mutex mu_;
};

// Test that CondVar can be constructed with a Mutex pointer
TEST_F(CondVarTest_34, ConstructWithMutex_34) {
  CondVar cv(&mu_);
  // If we reach here without crashing, construction succeeded.
}

// Test that Signal does not block or crash when called without waiters
TEST_F(CondVarTest_34, SignalWithoutWaiters_34) {
  CondVar cv(&mu_);
  cv.Signal();
  // Should not block or crash
}

// Test that SignalAll does not block or crash when called without waiters
TEST_F(CondVarTest_34, SignalAllWithoutWaiters_34) {
  CondVar cv(&mu_);
  cv.SignalAll();
  // Should not block or crash
}

// Test that Signal wakes up a waiting thread
TEST_F(CondVarTest_34, SignalWakesOneWaiter_34) {
  CondVar cv(&mu_);
  std::atomic<bool> ready(false);
  std::atomic<bool> woken(false);

  std::thread waiter([&]() {
    mu_.Lock();
    ready.store(true);
    cv.Wait();
    woken.store(true);
    mu_.Unlock();
  });

  // Wait until the waiter thread is ready and has entered Wait
  while (!ready.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  // Give a little extra time for the thread to actually enter Wait
  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  EXPECT_FALSE(woken.load());

  mu_.Lock();
  cv.Signal();
  mu_.Unlock();

  waiter.join();
  EXPECT_TRUE(woken.load());
}

// Test that SignalAll wakes up multiple waiting threads
TEST_F(CondVarTest_34, SignalAllWakesAllWaiters_34) {
  CondVar cv(&mu_);
  std::atomic<int> ready_count(0);
  std::atomic<int> woken_count(0);

  auto waiter_fn = [&]() {
    mu_.Lock();
    ready_count.fetch_add(1);
    cv.Wait();
    woken_count.fetch_add(1);
    mu_.Unlock();
  };

  const int kNumWaiters = 3;
  std::vector<std::thread> waiters;
  for (int i = 0; i < kNumWaiters; i++) {
    waiters.emplace_back(waiter_fn);
  }

  // Wait until all waiters are ready
  while (ready_count.load() < kNumWaiters) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  // Give extra time for all threads to actually enter Wait
  std::this_thread::sleep_for(std::chrono::milliseconds(20));

  EXPECT_EQ(0, woken_count.load());

  mu_.Lock();
  cv.SignalAll();
  mu_.Unlock();

  for (auto& t : waiters) {
    t.join();
  }
  EXPECT_EQ(kNumWaiters, woken_count.load());
}

// Test that Signal wakes only one waiter when multiple are waiting
TEST_F(CondVarTest_34, SignalWakesOnlyOneWaiter_34) {
  CondVar cv(&mu_);
  std::atomic<int> ready_count(0);
  std::atomic<int> woken_count(0);
  std::atomic<bool> keep_going(true);

  auto waiter_fn = [&]() {
    mu_.Lock();
    ready_count.fetch_add(1);
    cv.Wait();
    woken_count.fetch_add(1);
    mu_.Unlock();
  };

  const int kNumWaiters = 3;
  std::vector<std::thread> waiters;
  for (int i = 0; i < kNumWaiters; i++) {
    waiters.emplace_back(waiter_fn);
  }

  // Wait until all waiters are ready
  while (ready_count.load() < kNumWaiters) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(20));

  // Signal once - should wake exactly one
  mu_.Lock();
  cv.Signal();
  mu_.Unlock();

  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  EXPECT_EQ(1, woken_count.load());

  // Signal remaining waiters so threads can join
  mu_.Lock();
  cv.SignalAll();
  mu_.Unlock();

  for (auto& t : waiters) {
    t.join();
  }
  EXPECT_EQ(kNumWaiters, woken_count.load());
}

// Test that multiple Signals can be issued in succession
TEST_F(CondVarTest_34, MultipleSignalsInSuccession_34) {
  CondVar cv(&mu_);
  cv.Signal();
  cv.Signal();
  cv.Signal();
  // Should not block or crash
}

// Test that multiple SignalAll can be issued in succession
TEST_F(CondVarTest_34, MultipleSignalAllsInSuccession_34) {
  CondVar cv(&mu_);
  cv.SignalAll();
  cv.SignalAll();
  cv.SignalAll();
  // Should not block or crash
}

// Test Wait and Signal in a producer-consumer style pattern
TEST_F(CondVarTest_34, WaitAndSignalProducerConsumer_34) {
  CondVar cv(&mu_);
  bool data_ready = false;
  int result = 0;

  std::thread consumer([&]() {
    mu_.Lock();
    while (!data_ready) {
      cv.Wait();
    }
    result = 42;
    mu_.Unlock();
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  mu_.Lock();
  data_ready = true;
  cv.Signal();
  mu_.Unlock();

  consumer.join();
  EXPECT_EQ(42, result);
}

// Test that CondVar copy constructor is deleted (compile-time check is implicit;
// we just verify the object works normally after construction)
TEST_F(CondVarTest_34, NonCopyable_34) {
  // CondVar(const CondVar&) = delete and operator= deleted
  // We just verify we can create and use one normally
  CondVar cv(&mu_);
  cv.Signal();
  cv.SignalAll();
}

}  // namespace port
}  // namespace leveldb
