// File: env_default_test_429.cc

#include "leveldb/env.h"
#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <atomic>

namespace {

class EnvDefaultTest_429 : public ::testing::Test {
protected:
  leveldb::Env* env_ = nullptr;

  void SetUp() override {
    // Obtain the default environment once for reuse in tests
    env_ = leveldb::Env::Default();
  }
};

}  // namespace

// [Normal operation] Default() returns a non-null pointer to an Env.
TEST_F(EnvDefaultTest_429, DefaultReturnsNonNull_429) {
  ASSERT_NE(env_, nullptr);
}

// [Normal operation] Repeated calls to Default() return the same instance (singleton behavior via interface).
TEST_F(EnvDefaultTest_429, DefaultReturnsSameInstanceOnRepeatedCalls_429) {
  leveldb::Env* again = leveldb::Env::Default();
  ASSERT_NE(env_, nullptr);
  ASSERT_NE(again, nullptr);
  EXPECT_EQ(env_, again);
}

// [Boundary / concurrency] Concurrent calls to Default() across multiple threads
// all observe the same instance. This checks thread-safety from the caller’s perspective.
TEST_F(EnvDefaultTest_429, DefaultReturnsSameInstanceAcrossThreads_429) {
  constexpr int kThreads = 16;
  std::vector<std::thread> threads;
  std::vector<leveldb::Env*> results(kThreads, nullptr);

  for (int i = 0; i < kThreads; ++i) {
    threads.emplace_back([&, i] {
      results[i] = leveldb::Env::Default();
    });
  }
  for (auto& t : threads) t.join();

  for (int i = 0; i < kThreads; ++i) {
    ASSERT_NE(results[i], nullptr) << "Thread " << i << " got null Env*";
    EXPECT_EQ(results[i], env_) << "Thread " << i << " observed a different Env*";
  }
}

// [Observable behavior] The default Env’s time source is usable.
// We do not assert a specific implementation—only that it returns a value and is monotonic-non-decreasing between two immediate calls.
TEST_F(EnvDefaultTest_429, NowMicrosIsUsable_429) {
  ASSERT_NE(env_, nullptr);
  const uint64_t t1 = env_->NowMicros();
  const uint64_t t2 = env_->NowMicros();

  // Basic sanity checks on observable outputs.
  // We don't rely on exact timing or sleep; just ensure calls succeed and are non-decreasing.
  EXPECT_GT(t1, 0u);
  EXPECT_GE(t2, t1);
}
