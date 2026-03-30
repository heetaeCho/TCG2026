// TEST_ID: 748
// File: annotborder_getdash_test_748.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <vector>

// Adjust include as needed by your build/include paths.
#include "Annot.h"

namespace {

// Small test harness to allow construction (AnnotBorder ctor is protected) and
// to provide a way to set up observable state for getDash() without asserting
// on any private state.
class TestableAnnotBorder_748 : public AnnotBorder {
public:
  TestableAnnotBorder_748() : AnnotBorder() {}

  void setDashForTest(std::vector<double> v) { dash = std::move(v); }
};

class AnnotBorderTest_748 : public ::testing::Test {
protected:
  TestableAnnotBorder_748 border_;
};

} // namespace

TEST_F(AnnotBorderTest_748, DefaultDashIsAccessibleAndStableReference_748) {
  const auto& d1 = border_.getDash();
  const auto& d2 = border_.getDash();

  // Observable behavior: returns a const reference that remains stable.
  EXPECT_EQ(&d1, &d2);

  // Boundary: default/empty dash array should be a valid vector reference.
  EXPECT_GE(d1.size(), static_cast<std::size_t>(0));
}

TEST_F(AnnotBorderTest_748, GetDashReflectsAssignedValues_748) {
  const std::vector<double> expected{1.0, 2.5, 3.0};
  border_.setDashForTest(expected);

  const auto& got = border_.getDash();
  EXPECT_EQ(got, expected);
}

TEST_F(AnnotBorderTest_748, GetDashHandlesEmptyArray_748) {
  border_.setDashForTest({});

  const auto& got = border_.getDash();
  EXPECT_TRUE(got.empty());
}

TEST_F(AnnotBorderTest_748, GetDashHandlesLargerArray_748) {
  std::vector<double> big;
  big.reserve(1024);
  for (int i = 0; i < 1024; ++i) {
    big.push_back(static_cast<double>(i) + 0.25);
  }
  border_.setDashForTest(big);

  const auto& got = border_.getDash();
  EXPECT_EQ(got.size(), big.size());
  EXPECT_TRUE(std::equal(got.begin(), got.end(), big.begin(), big.end()));
}