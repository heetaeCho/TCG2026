// File: db_impl_max_next_level_bytes_test.cc
#include "db/db_impl.h"

#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <string>
#include <thread>
#include <vector>

using namespace leveldb;

namespace {

// Simple helper to produce a unique DB name per test run without relying on any private APIs.
static std::string UniqueDBName_305(const std::string& prefix) {
  auto now = std::chrono::system_clock::now().time_since_epoch();
  auto micros = std::chrono::duration_cast<std::chrono::microseconds>(now).count();
  return prefix + "_305_" + std::to_string(micros);
}

class DBImplMaxNextOverlapBytesTest_305 : public ::testing::Test {
 protected:
  Options opts_;
  std::string dbname_;

  void SetUp() override {
    // Keep options minimal and avoid side effects; rely only on defaults.
    // We do not open/Recover the DB here; we only construct DBImpl to call the test method.
    dbname_ = UniqueDBName_305("dbimpl_max_next_level_bytes");
    opts_.create_if_missing = true;  // Benign; we are not triggering I/O in these tests.
  }
};

}  // namespace

// Normal operation: method returns a valid (non-negative) byte count.
// We do not assume any particular number; only that overlapping *bytes* cannot be negative.
TEST_F(DBImplMaxNextOverlapBytesTest_305, ReturnsNonNegative_305) {
  DBImpl db(opts_, dbname_);
  const int64_t bytes = db.TEST_MaxNextLevelOverlappingBytes();
  EXPECT_GE(bytes, 0) << "Overlapping byte count should never be negative.";
}

// Idempotence under stable state: rapid repeated calls should produce a consistent value
// when no writes/compactions are performed by the test.
TEST_F(DBImplMaxNextOverlapBytesTest_305, ConsistentAcrossBackToBackCalls_305) {
  DBImpl db(opts_, dbname_);
  const int64_t first = db.TEST_MaxNextLevelOverlappingBytes();

  // Call several times back-to-back; observe consistent result.
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(db.TEST_MaxNextLevelOverlappingBytes(), first);
  }
}

// Concurrency safety: calling from multiple threads should not deadlock/crash and
// should provide a consistent snapshot value for each call.
TEST_F(DBImplMaxNextOverlapBytesTest_305, ThreadSafeMultiCaller_305) {
  DBImpl db(opts_, dbname_);

  const int kThreads = 8;
  std::vector<std::thread> threads;
  std::vector<int64_t> results(kThreads, -1);

  // Launch concurrent callers; each only observes the public return value.
  for (int t = 0; t < kThreads; ++t) {
    threads.emplace_back([&db, &results, t]() {
      results[t] = db.TEST_MaxNextLevelOverlappingBytes();
    });
  }
  for (auto& th : threads) th.join();

  // All calls must succeed and yield non-negative values.
  for (int t = 0; t < kThreads; ++t) {
    ASSERT_GE(results[t], 0) << "Per-thread result should be non-negative.";
  }

  // Under a quiescent DB (no writes/compactions induced by the test), values should match.
  // This checks for observable consistency of the method under concurrent access.
  const int64_t ref = results.front();
  for (int t = 1; t < kThreads; ++t) {
    EXPECT_EQ(results[t], ref);
  }
}

// Stability over time without user-triggered changes: calling the method with delays should
// remain stable in the absence of mutations from the test’s side.
TEST_F(DBImplMaxNextOverlapBytesTest_305, StableOverShortIntervalWithoutWrites_305) {
  DBImpl db(opts_, dbname_);
  const int64_t initial = db.TEST_MaxNextLevelOverlappingBytes();

  // Wait a little and call again; we didn't write or compact anything.
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  const int64_t after = db.TEST_MaxNextLevelOverlappingBytes();

  EXPECT_EQ(after, initial);
}
