#include "gtest/gtest.h"
#include "port/port_stdcxx.h"

#include <thread>
#include <atomic>
#include <chrono>
#include <vector>

namespace leveldb {
namespace port {

// Test fixture for CondVar tests
class CondVarTest_474 : public ::testing::Test {
 protected:
  Mutex mu_;
};

// Test that CondVar can be constructed with a valid Mutex pointer
TEST_F(CondVarTest_474, ConstructWithValidMutex_474) {
  CondVar cv(&mu_);
  // If we reach here without assertion failure, construction succeeded
  SUCCEED();
}

// Test that Signal wakes up a waiting thread
TEST_F(CondVarTest_474, SignalWakesWaitingThread_474) {
  CondVar cv(&mu_);
  std::atomic<bool> waiting{false};
  std::atomic<bool> done{false};

  std::thread waiter([&]() {
    mu_.Lock();
    waiting.store(true);
    cv.Wait();
    done.store(true);
    mu_.Unlock();
  });

  // Wait until the waiter thread is actually waiting
  while (!waiting.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  // Give a bit more time for the thread to enter Wait()
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // Signal the waiting thread
  mu_.Lock();
  cv.Signal();
  mu_.Unlock();

  waiter.join();
  EXPECT_TRUE(done.load());
}

// Test that SignalAll wakes up multiple waiting threads
TEST_F(CondVarTest_474, SignalAllWakesAllWaitingThreads_474) {
  CondVar cv(&mu_);
  const int kNumThreads = 5;
  std::atomic<int> waiting_count{0};
  std::atomic<int> done_count{0};

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

  // Wait until all threads are waiting
  while (waiting_count.load() < kNumThreads) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  // Give a bit more time for all threads to enter Wait()
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // Signal all waiting threads
  mu_.Lock();
  cv.SignalAll();
  mu_.Unlock();

  for (auto& t : threads) {
    t.join();
  }
  EXPECT_EQ(done_count.load(), kNumThreads);
}

// Test that Signal wakes only one thread when multiple are waiting
TEST_F(CondVarTest_474, SignalWakesOneThread_474) {
  CondVar cv(&mu_);
  std::atomic<int> waiting_count{0};
  std::atomic<int> done_count{0};
  std::atomic<bool> keep_going{true};

  const int kNumThreads = 3;
  std::vector<std::thread> threads;
  for (int i = 0; i < kNumThreads; i++) {
    threads.emplace_back([&]() {
      mu_.Lock();
      waiting_count.fetch_add(1);
      while (keep_going.load()) {
        cv.Wait();
        // After waking, check if we should exit
        break;
      }
      done_count.fetch_add(1);
      mu_.Unlock();
    });
  }

  // Wait until all threads are waiting
  while (waiting_count.load() < kNumThreads) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // Signal once - should wake at least one thread
  mu_.Lock();
  cv.Signal();
  mu_.Unlock();

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  int woken = done_count.load();
  EXPECT_GE(woken, 1);

  // Now wake up remaining threads
  keep_going.store(false);
  mu_.Lock();
  cv.SignalAll();
  mu_.Unlock();

  for (auto& t : threads) {
    t.join();
  }
  EXPECT_EQ(done_count.load(), kNumThreads);
}

// Test that Wait properly reacquires the mutex after being signaled
TEST_F(CondVarTest_474, WaitReacquiresMutexAfterSignal_474) {
  CondVar cv(&mu_);
  std::atomic<bool> waiting{false};
  bool shared_data = false;

  std::thread waiter([&]() {
    mu_.Lock();
    waiting.store(true);
    cv.Wait();
    // After Wait returns, we should hold the mutex
    shared_data = true;
    mu_.Unlock();
  });

  while (!waiting.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  mu_.Lock();
  cv.Signal();
  mu_.Unlock();

  waiter.join();
  EXPECT_TRUE(shared_data);
}

// Test CondVar with predicate pattern (typical usage)
TEST_F(CondVarTest_474, WaitWithPredicatePattern_474) {
  CondVar cv(&mu_);
  bool ready = false;
  bool result = false;

  std::thread waiter([&]() {
    mu_.Lock();
    while (!ready) {
      cv.Wait();
    }
    result = true;
    mu_.Unlock();
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  mu_.Lock();
  ready = true;
  cv.Signal();
  mu_.Unlock();

  waiter.join();
  EXPECT_TRUE(result);
}

// Test Signal on CondVar with no waiting threads (should not block or crash)
TEST_F(CondVarTest_474, SignalWithNoWaiters_474) {
  CondVar cv(&mu_);
  mu_.Lock();
  cv.Signal();
  mu_.Unlock();
  SUCCEED();
}

// Test SignalAll on CondVar with no waiting threads (should not block or crash)
TEST_F(CondVarTest_474, SignalAllWithNoWaiters_474) {
  CondVar cv(&mu_);
  mu_.Lock();
  cv.SignalAll();
  mu_.Unlock();
  SUCCEED();
}

// Test multiple Signal calls in sequence
TEST_F(CondVarTest_474, MultipleSignalCalls_474) {
  CondVar cv(&mu_);
  mu_.Lock();
  cv.Signal();
  cv.Signal();
  cv.Signal();
  mu_.Unlock();
  SUCCEED();
}

// Test multiple SignalAll calls in sequence
TEST_F(CondVarTest_474, MultipleSignalAllCalls_474) {
  CondVar cv(&mu_);
  mu_.Lock();
  cv.SignalAll();
  cv.SignalAll();
  cv.SignalAll();
  mu_.Unlock();
  SUCCEED();
}

// Test producer-consumer pattern with CondVar
TEST_F(CondVarTest_474, ProducerConsumerPattern_474) {
  CondVar cv(&mu_);
  int item = 0;
  bool item_ready = false;
  bool consumed = false;

  std::thread consumer([&]() {
    mu_.Lock();
    while (!item_ready) {
      cv.Wait();
    }
    EXPECT_EQ(item, 42);
    consumed = true;
    mu_.Unlock();
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  mu_.Lock();
  item = 42;
  item_ready = true;
  cv.Signal();
  mu_.Unlock();

  consumer.join();
  EXPECT_TRUE(consumed);
}

// Test that multiple CondVars can share the same Mutex
TEST_F(CondVarTest_474, MultipleCondVarsSameMutex_474) {
  CondVar cv1(&mu_);
  CondVar cv2(&mu_);
  std::atomic<bool> t1_waiting{false};
  std::atomic<bool> t2_waiting{false};
  std::atomic<bool> t1_done{false};
  std::atomic<bool> t2_done{false};

  std::thread t1([&]() {
    mu_.Lock();
    t1_waiting.store(true);
    cv1.Wait();
    t1_done.store(true);
    mu_.Unlock();
  });

  std::thread t2([&]() {
    mu_.Lock();
    t2_waiting.store(true);
    cv2.Wait();
    t2_done.store(true);
    mu_.Unlock();
  });

  while (!t1_waiting.load() || !t2_waiting.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // Signal cv1 - only t1 should wake
  mu_.Lock();
  cv1.Signal();
  mu_.Unlock();

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_TRUE(t1_done.load());
  // t2 might or might not be done (implementation dependent for spurious wakeups)

  // Signal cv2
  mu_.Lock();
  cv2.Signal();
  mu_.Unlock();

  t1.join();
  t2.join();

  EXPECT_TRUE(t1_done.load());
  EXPECT_TRUE(t2_done.load());
}

// Test Mutex basic Lock/Unlock
class MutexTest_474 : public ::testing::Test {
 protected:
  Mutex mu_;
};

TEST_F(MutexTest_474, LockAndUnlock_474) {
  mu_.Lock();
  mu_.Unlock();
  SUCCEED();
}

TEST_F(MutexTest_474, MultipleLockUnlockCycles_474) {
  for (int i = 0; i < 100; i++) {
    mu_.Lock();
    mu_.Unlock();
  }
  SUCCEED();
}

TEST_F(MutexTest_474, MutualExclusion_474) {
  int shared_counter = 0;
  const int kIterations = 10000;
  const int kNumThreads = 4;

  std::vector<std::thread> threads;
  for (int i = 0; i < kNumThreads; i++) {
    threads.emplace_back([&]() {
      for (int j = 0; j < kIterations; j++) {
        mu_.Lock();
        shared_counter++;
        mu_.Unlock();
      }
    });
  }

  for (auto& t : threads) {
    t.join();
  }

  EXPECT_EQ(shared_counter, kNumThreads * kIterations);
}

}  // namespace port
}  // namespace leveldb
