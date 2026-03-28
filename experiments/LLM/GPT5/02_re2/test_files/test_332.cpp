// File: re2_ref_mutex_test.cc
#include <gtest/gtest.h>
#include "absl/synchronization/mutex.h"

#include <atomic>
#include <thread>
#include <chrono>

// The function under test lives in the re2 namespace.
// We declare it here and rely on the build to link in its definition.
namespace re2 {
absl::Mutex* ref_mutex();
}  // namespace re2

class Re2RefMutexTest_332 : public ::testing::Test {};

// [Normal] Returns a valid, non-null mutex pointer.
TEST_F(Re2RefMutexTest_332, ReturnsNonNull_332) {
  absl::Mutex* m = re2::ref_mutex();
  EXPECT_NE(m, nullptr);
}

// [Normal] Successive calls return the same address (stable singleton accessor).
TEST_F(Re2RefMutexTest_332, ReturnsSameAddressAcrossCalls_332) {
  absl::Mutex* m1 = re2::ref_mutex();
  absl::Mutex* m2 = re2::ref_mutex();
  ASSERT_NE(m1, nullptr);
  ASSERT_NE(m2, nullptr);
  EXPECT_EQ(m1, m2);
}

// [Boundary/Semantics] Basic lock/unlock works and TryLock fails while held.
TEST_F(Re2RefMutexTest_332, BasicLockUnlockAndTryLockBehavior_332) {
  absl::Mutex* m = re2::ref_mutex();
  ASSERT_NE(m, nullptr);

  // Lock once.
  m->Lock();

  // While held, TryLock() should fail (non-reentrant).
  bool try_lock_while_held = m->TryLock();
  EXPECT_FALSE(try_lock_while_held) << "Mutex should not be re-locked by the same thread via TryLock while held";

  // Unlock the first lock.
  m->Unlock();

  // After unlock, TryLock() should succeed.
  bool try_lock_after_unlock = m->TryLock();
  EXPECT_TRUE(try_lock_after_unlock) << "Mutex TryLock should succeed after being unlocked";

  // Balance the successful TryLock().
  m->Unlock();
}

// [Concurrency] Proves mutual exclusion across threads using TryLock polling.
TEST_F(Re2RefMutexTest_332, EnforcesMutualExclusionAcrossThreads_332) {
  absl::Mutex* m = re2::ref_mutex();
  ASSERT_NE(m, nullptr);

  std::atomic<bool> released{false};
  std::atomic<bool> acquired_after_release{false};
  std::atomic<int> attempts{0};

  // Main thread acquires the lock first.
  m->Lock();

  std::thread t([&] {
    // Keep trying until we eventually acquire the mutex.
    for (;;) {
      ++attempts;
      if (m->TryLock()) {
        // We acquired it; record whether this happened only after release.
        acquired_after_release.store(released.load(), std::memory_order_relaxed);
        m->Unlock();
        break;
      }
      // Back off a little to avoid busy-spinning.
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  });

  // Give the other thread time to start and attempt TryLock a few times.
  std::this_thread::sleep_for(std::chrono::milliseconds(20));

  // Now release the mutex and signal that release has happened.
  released.store(true, std::memory_order_relaxed);
  m->Unlock();

  t.join();

  // The worker thread should have failed TryLock at least once while held...
  EXPECT_GT(attempts.load(), 0);

  // ...and only succeeded after we released the lock.
  EXPECT_TRUE(acquired_after_release.load())
      << "Second thread should acquire the mutex only after the first thread releases it";
}
