// File: charclass_begin_tests_143.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace re2 {

class CharClassBeginTest_143 : public ::testing::Test {
protected:
  // Helper to safely dispose CharClass*
  static void Dispose(CharClass* cc) {
    if (cc) cc->Delete();
  }
};

TEST_F(CharClassBeginTest_143, BeginEqualsEndWhenEmpty_143) {
  // Arrange
  CharClass* cc = CharClass::New(/*maxranges=*/0);
  ASSERT_NE(cc, nullptr);

  // Act
  auto b = cc->begin();
  auto e = cc->end();

  // Assert (observable behavior only)
  EXPECT_TRUE(cc->empty());
  EXPECT_EQ(cc->size(), 0);
  EXPECT_EQ(b, e);

  // Cleanup
  CharClassBeginTest_143::Dispose(cc);
}

TEST_F(CharClassBeginTest_143, MultipleBeginCallsAreStableOnEmpty_143) {
  CharClass* cc = CharClass::New(/*maxranges=*/4);
  ASSERT_NE(cc, nullptr);

  // Call begin() multiple times and compare results; end() should still match.
  auto b1 = cc->begin();
  auto b2 = cc->begin();
  auto e  = cc->end();

  EXPECT_TRUE(cc->empty());
  EXPECT_EQ(cc->size(), 0);
  EXPECT_EQ(b1, b2);
  EXPECT_EQ(b1, e);

  CharClassBeginTest_143::Dispose(cc);
}

TEST_F(CharClassBeginTest_143, IterationCountMatchesSizeOnEmpty_143) {
  CharClass* cc = CharClass::New(/*maxranges=*/8);
  ASSERT_NE(cc, nullptr);

  int count = 0;
  for (auto it = cc->begin(); it != cc->end(); ++it) {
    ++count;  // Should not execute for an empty set.
  }

  EXPECT_TRUE(cc->empty());
  EXPECT_EQ(cc->size(), 0);
  EXPECT_EQ(count, cc->size());

  CharClassBeginTest_143::Dispose(cc);
}

TEST_F(CharClassBeginTest_143, BeginEndUsableAfterNegateOnEmpty_143) {
  CharClass* cc = CharClass::New(/*maxranges=*/0);
  ASSERT_NE(cc, nullptr);

  // Negate() returns a new CharClass*. We don't assume semantics (full/empty);
  // we only verify begin()/end() are usable and iteration count equals size().
  CharClass* neg = cc->Negate();
  ASSERT_NE(neg, nullptr);

  int count = 0;
  for (auto it = neg->begin(); it != neg->end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, neg->size());  // purely based on public interface

  CharClassBeginTest_143::Dispose(neg);
  CharClassBeginTest_143::Dispose(cc);
}

TEST_F(CharClassBeginTest_143, BeginEndWorkWithDifferentCapacities_143) {
  // Boundary-like capacities: 0 and a larger number.
  CharClass* small = CharClass::New(/*maxranges=*/0);
  CharClass* large = CharClass::New(/*maxranges=*/64);
  ASSERT_NE(small, nullptr);
  ASSERT_NE(large, nullptr);

  // We do not infer internal storage; we just verify observable begin/end facts.
  EXPECT_EQ(small->begin(), small->end());
  EXPECT_EQ(large->begin(), large->end());
  EXPECT_TRUE(small->empty());
  EXPECT_TRUE(large->empty());
  EXPECT_EQ(small->size(), 0);
  EXPECT_EQ(large->size(), 0);

  CharClassBeginTest_143::Dispose(small);
  CharClassBeginTest_143::Dispose(large);
}

} // namespace re2
