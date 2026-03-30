// File: substring_walker_shortvisit_test.cc

#include <gtest/gtest.h>
#include <limits>

namespace re2 {
class Regexp;  // Forward declaration; tests must not rely on internal details.
}

// Forward-declare SubstringWalker to rely only on its public interface.
// In your build, prefer including the appropriate declaration if available.
// e.g., #include "re2/fuzzing/re2_fuzzer.h"
class SubstringWalker {
public:
  // We rely solely on the signature/observable behavior.
  int ShortVisit(re2::Regexp* re, int parent_arg);
};

class SubstringWalkerTest_384 : public ::testing::Test {
protected:
  SubstringWalker walker_;
};

// Normal operation: returns the parent_arg for typical positive values.
TEST_F(SubstringWalkerTest_384, ReturnsParentArgForPositiveValues_384) {
  int in = 42;
  // Passing nullptr for re2::Regexp*; test focuses on observable return value.
  EXPECT_EQ(walker_.ShortVisit(nullptr, in), in);
}

// Normal operation: returns the parent_arg for zero and negative values.
TEST_F(SubstringWalkerTest_384, ReturnsParentArgForZeroAndNegativeValues_384) {
  EXPECT_EQ(walker_.ShortVisit(nullptr, 0), 0);
  EXPECT_EQ(walker_.ShortVisit(nullptr, -7), -7);
}

// Boundary conditions: handles integer limits.
TEST_F(SubstringWalkerTest_384, ReturnsParentArgForIntBounds_384) {
  const int kMin = std::numeric_limits<int>::min();
  const int kMax = std::numeric_limits<int>::max();
  EXPECT_EQ(walker_.ShortVisit(nullptr, kMin), kMin);
  EXPECT_EQ(walker_.ShortVisit(nullptr, kMax), kMax);
}

// Robustness: accepting a non-null Regexp* should still yield the same observable result.
// We don't dereference or assume anything about the pointer (no internal access).
TEST_F(SubstringWalkerTest_384, IgnoresRegexpPointerForReturnValue_384) {
  // Use an arbitrary non-null pointer value without assuming validity.
  auto* fake_re = reinterpret_cast<re2::Regexp*>(0x1);
  int in = 123;
  EXPECT_EQ(walker_.ShortVisit(fake_re, in), in);
}

// Consistency: multiple calls with the same inputs are consistent (idempotent observable behavior).
TEST_F(SubstringWalkerTest_384, ConsistentAcrossMultipleCalls_384) {
  int in = -314;
  EXPECT_EQ(walker_.ShortVisit(nullptr, in), in);
  EXPECT_EQ(walker_.ShortVisit(nullptr, in), in);
  EXPECT_EQ(walker_.ShortVisit(nullptr, in), in);
}
