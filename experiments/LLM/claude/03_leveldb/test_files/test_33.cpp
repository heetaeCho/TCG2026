#include "port/port_stdcxx.h"

#include <atomic>
#include <chrono>
#include <thread>

#include "gtest/gtest.h"

namespace leveldb {
namespace port {

class CondVarTest_33 : public ::testing::Test {
 protected:
  Mutex mu_;
};

TEST_F(CondVarTest_33, ConstructionWithMutex_33) {
  // Test that a CondVar can be constructed with a Mutex pointer.
  CondVar cv(&mu_);
  // If we reach here without crashing, construction succeeded.
}

TEST_F(CondVarTest_33, SignalWakesOneWaitingThread_33) {
  CondVar cv(&mu_);
  std::atomic<bool> waiting{false};
  std::atomic<bool> done{false};

  std::thread t([&]() {
    mu_.Lock();
    waiting.store(true);
    cv.Wait();
    done.store(true);
    mu_.Unlock();
  });

  // Wait until the thread is actually waiting.
  while (!waiting.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  // Give a little extra time for the thread to enter cv.Wait()
  std::this_thread::sleep_for(std::chrono::milliseconds(20));

  // The thread should not be done yet.
  EXPECT_FALSE(done.load());

  // Signal the condvar to wake the thread.
  mu_.Lock();
  cv.Signal();
  mu_.Unlock();

  t.join();
  EXPECT_TRUE(done.load());
}

TEST_F(CondVarTest_33, SignalAllWakesAllWaitingThreads_33) {
  CondVar cv(&mu_);
  constexpr int kNumThreads = 4;
  std::atomic<int> waiting_count{0};
  std::atomic<int> done_count{0};

  std::vector<std::thread> threads;
  for (int i = 0; i < kNumThreads; ++i) {
    threads.emplace_back([&]() {
      mu_.Lock();
      waiting_count.fetch_add(1);
      cv.Wait();
      done_count.fetch_add(1);
      mu_.Unlock();
    });
  }

  // Wait until all threads are waiting.
  while (waiting_count.load() < kNumThreads) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  // Extra time for all to enter cv.Wait()
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  EXPECT_EQ(done_count.load(), 0);

  // SignalAll should wake all threads.
  mu_.Lock();
  cv.SignalAll();
  mu_.Unlock();

  for (auto& t : threads) {
    t.join();
  }
  EXPECT_EQ(done_count.load(), kNumThreads);
}

TEST_F(CondVarTest_33, SignalWithNoWaitersDoesNotBlock_33) {
  CondVar cv(&mu_);
  // Signaling with no waiters should not block or crash.
  mu_.Lock();
  cv.Signal();
  mu_.Unlock();
}

TEST_F(CondVarTest_33, SignalAllWithNoWaitersDoesNotBlock_33) {
  CondVar cv(&mu_);
  // SignalAll with no waiters should not block or crash.
  mu_.Lock();
  cv.SignalAll();
  mu_.Unlock();
}

TEST_F(CondVarTest_33, WaitReleasesAndReacquiresMutex_33) {
  CondVar cv(&mu_);
  std::atomic<bool> thread_in_wait{false};
  std::atomic<bool> mutex_acquired_by_main{false};

  std::thread t([&]() {
    mu_.Lock();
    thread_in_wait.store(true);
    cv.Wait();
    // After waking, mutex should be held again.
    // We verify by unlocking without error.
    mu_.Unlock();
  });

  // Wait until thread enters Wait.
  while (!thread_in_wait.load()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(20));

  // The mutex should be released by Wait(), so we can lock it.
  mu_.Lock();
  mutex_acquired_by_main.store(true);
  cv.Signal();
  mu_.Unlock();

  t.join();
  EXPECT_TRUE(mutex_acquired_by_main.load());
}

TEST_F(CondVarTest_33, MultipleSignalsCycle_33) {
  CondVar cv(&mu_);
  std::atomic<int> phase{0};

  std::thread t([&]() {
    mu_.Lock();
    phase.store(1);
    cv.Wait();
    phase.store(2);
    cv.Wait();
    phase.store(3);
    mu_.Unlock();
  });

  // Wait for phase 1
  while (phase.load() < 1) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  EXPECT_EQ(phase.load(), 1);

  mu_.Lock();
  cv.Signal();
  mu_.Unlock();

  // Wait for phase 2
  while (phase.load() < 2) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  EXPECT_EQ(phase.load(), 2);

  mu_.Lock();
  cv.Signal();
  mu_.Unlock();

  t.join();
  EXPECT_EQ(phase.load(), 3);
}

TEST_F(CondVarTest_33, SignalWakesOnlyOneThread_33) {
  CondVar cv(&mu_);
  std::atomic<int> waiting_count{0};
  std::atomic<int> done_count{0};

  auto worker = [&]() {
    mu_.Lock();
    waiting_count.fetch_add(1);
    cv.Wait();
    done_count.fetch_add(1);
    mu_.Unlock();
  };

  std::thread t1(worker);
  std::thread t2(worker);

  while (waiting_count.load() < 2) {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(50));

  // Signal should wake exactly one thread.
  mu_.Lock();
  cv.Signal();
  mu_.Unlock();

  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  EXPECT_EQ(done_count.load(), 1);

  // Signal again to wake the second thread.
  mu_.Lock();
  cv.Signal();
  mu_.Unlock();

  t1.join();
  t2.join();
  EXPECT_EQ(done_count.load(), 2);
}

}  // namespace port
}  // namespace leveldb
