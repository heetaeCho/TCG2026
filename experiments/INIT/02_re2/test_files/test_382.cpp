// File: subexpression_walker_shortvisit_test_382.cc

#include <gtest/gtest.h>
#include <climits>

// We rely only on the public interface. To access SubexpressionWalker,
// include the partial implementation translation unit that defines it.
#include "re2/fuzzing/re2_fuzzer.cc"

// Forward-declare re2::Regexp pointer type for clarity (not used directly in logic here).
namespace re2 { class Regexp; }

// Test: Normal operation with a typical integer value.
TEST(SubexpressionWalkerTest_382, ShortVisit_ReturnsParentArg_Normal_382) {
  SubexpressionWalker w;
  re2::Regexp* re = nullptr;  // We don't rely on internal use of this pointer.
  int parent_arg = 123;

  EXPECT_EQ(parent_arg, w.ShortVisit(re, parent_arg));
}

// Test: Boundary condition with zero.
TEST(SubexpressionWalkerTest_382, ShortVisit_ReturnsParentArg_Zero_382) {
  SubexpressionWalker w;
  re2::Regexp* re = nullptr;
  int parent_arg = 0;

  EXPECT_EQ(parent_arg, w.ShortVisit(re, parent_arg));
}

// Test: Negative value handling (observable return only).
TEST(SubexpressionWalkerTest_382, ShortVisit_ReturnsParentArg_Negative_382) {
  SubexpressionWalker w;
  re2::Regexp* re = nullptr;
  int parent_arg = -42;

  EXPECT_EQ(parent_arg, w.ShortVisit(re, parent_arg));
}

// Test: Boundary conditions with INT_MIN and INT_MAX.
TEST(SubexpressionWalkerTest_382, ShortVisit_ReturnsParentArg_IntLimits_382) {
  SubexpressionWalker w;
  re2::Regexp* re = nullptr;

  EXPECT_EQ(INT_MIN, w.ShortVisit(re, INT_MIN));
  EXPECT_EQ(INT_MAX, w.ShortVisit(re, INT_MAX));
}

// Test: The result is independent of the specific Regexp* passed (observable behavior only).
TEST(SubexpressionWalkerTest_382, ShortVisit_IgnoresRegexpPointer_382) {
  SubexpressionWalker w;

  // Use two distinct dummy pointers without dereferencing them.
  re2::Regexp* re_a = reinterpret_cast<re2::Regexp*>(0x1);
  re2::Regexp* re_b = reinterpret_cast<re2::Regexp*>(0x2);

  int parent_arg = 77;
  EXPECT_EQ(parent_arg, w.ShortVisit(re_a, parent_arg));
  EXPECT_EQ(parent_arg, w.ShortVisit(re_b, parent_arg));
}
