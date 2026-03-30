// File: comparator_bytewise_test_426.cc

#include <gtest/gtest.h>
#include <thread>
#include <vector>
#include <atomic>

#include "leveldb/comparator.h"
#include "leveldb/slice.h"

namespace {

class ComparatorTest_426 : public ::testing::Test {};

}  // namespace

// Verifies the function returns a non-null pointer.
// Behavior under test: construction/availability of a Comparator instance.
TEST_F(ComparatorTest_426, ReturnsNonNull_426) {
  const leveldb::Comparator* cmp = leveldb::BytewiseComparator();
  ASSERT_NE(cmp, nullptr);
}

// Verifies BytewiseComparator() returns the same instance across multiple calls.
// Behavior under test: singleton semantics (identity stability).
TEST_F(ComparatorTest_426, ReturnsSameInstanceAcrossCalls_426) {
  const leveldb::Comparator* a = leveldb::BytewiseComparator();
  const leveldb::Comparator* b = leveldb::BytewiseComparator();
  const leveldb::Comparator* c = leveldb::BytewiseComparator();

  ASSERT_NE(a, nullptr);
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

// Verifies that comparing a Slice with itself yields equality (0).
// Behavior under test: Comparator contract for self-comparison via public API.
TEST_F(ComparatorTest_426, SelfComparisonIsZero_426) {
  const leveldb::Comparator* cmp = leveldb::BytewiseComparator();
  ASSERT_NE(cmp, nullptr);

  const leveldb::Slice s1("abc");
  const leveldb::Slice s2("");      // also check empty
  const leveldb::Slice s3("\0x", 2); // binary data (includes a null byte)

  EXPECT_EQ(0, cmp->Compare(s1, s1));
  EXPECT_EQ(0, cmp->Compare(s2, s2));
  EXPECT_EQ(0, cmp->Compare(s3, s3));
}

// Verifies thread-safe singleton initialization: all threads observe the same instance.
// Behavior under test: identity stability and thread-safety of access.
TEST_F(ComparatorTest_426, ThreadSafeSingleton_426) {
  constexpr int kThreads = 16;
  std::vector<const leveldb::Comparator*> got(kThreads, nullptr);
  std::vector<std::thread> threads;
  threads.reserve(kThreads);

  for (int i = 0; i < kThreads; ++i) {
    threads.emplace_back([i, &got]() {
      got[i] = leveldb::BytewiseComparator();
    });
  }
  for (auto& t : threads) t.join();

  const leveldb::Comparator* first = leveldb::BytewiseComparator();
  ASSERT_NE(first, nullptr);
  for (int i = 0; i < kThreads; ++i) {
    ASSERT_NE(got[i], nullptr);
    EXPECT_EQ(first, got[i]) << "Thread " << i << " observed a different instance pointer";
  }
}
