// File: sparse_set_max_size_test_90.cc
#include <gtest/gtest.h>
#include "re2/sparse_set.h"

namespace re2 {

// A simple fixture to group max_size() tests.
// We don't rely on any private state or internal behavior.
class SparseSetT_MaxSizeTest_90 : public ::testing::Test {};

// [Normal] Default construction ⇒ observable max_size()
TEST_F(SparseSetT_MaxSizeTest_90, DefaultConstructed_MaxSizeIsZero_90) {
  SparseSetT<int> s;  // default-constructed
  EXPECT_EQ(s.max_size(), 0);
}

// [Normal] Construct with a positive capacity ⇒ observable max_size()
TEST_F(SparseSetT_MaxSizeTest_90, ConstructWithCapacity_ReportsSame_90) {
  const int kCap = 8;
  SparseSetT<int> s(kCap);
  EXPECT_EQ(s.max_size(), kCap);
}

// [Boundary] Construct with zero capacity ⇒ observable max_size()
TEST_F(SparseSetT_MaxSizeTest_90, ConstructWithZeroCapacity_ReportsZero_90) {
  const int kCap = 0;
  SparseSetT<int> s(kCap);
  EXPECT_EQ(s.max_size(), 0);
}

// [Boundary] Construct with a larger capacity ⇒ observable max_size()
// (Pick a moderate size to avoid stressing the allocator in unit tests.)
TEST_F(SparseSetT_MaxSizeTest_90, ConstructWithLargeCapacity_ReportsSame_90) {
  const int kCap = 1024;
  SparseSetT<int> s(kCap);
  EXPECT_EQ(s.max_size(), kCap);
}

// [Normal/Boundary] resize() updates observable max_size() when increasing and decreasing
TEST_F(SparseSetT_MaxSizeTest_90, Resize_UpdatesMaxSize_90) {
  SparseSetT<int> s(4);
  EXPECT_EQ(s.max_size(), 4);

  s.resize(10);
  EXPECT_EQ(s.max_size(), 10);

  s.resize(3);
  EXPECT_EQ(s.max_size(), 3);
}

// [Exceptional/Edge via interface] Repeated resize to same value keeps observable max_size()
// (Idempotence of reported capacity; we’re only checking public result.)
TEST_F(SparseSetT_MaxSizeTest_90, ResizeToSameValue_KeepsReportedMaxSize_90) {
  SparseSetT<int> s(5);
  EXPECT_EQ(s.max_size(), 5);

  s.resize(5);
  EXPECT_EQ(s.max_size(), 5);
}

}  // namespace re2
