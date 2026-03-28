#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"

namespace re2 {

class InstMatchesTest_111 : public ::testing::Test {
 protected:
  Prog::Inst inst_;

  void SetupByteRange(int lo, int hi, int foldcase, uint32_t out = 0) {
    inst_.InitByteRange(lo, hi, foldcase, out);
  }
};

// Test exact match within range
TEST_F(InstMatchesTest_111, ExactMatchLowerBound_111) {
  SetupByteRange('a', 'z', 0);
  EXPECT_TRUE(inst_.Matches('a'));
}

TEST_F(InstMatchesTest_111, ExactMatchUpperBound_111) {
  SetupByteRange('a', 'z', 0);
  EXPECT_TRUE(inst_.Matches('z'));
}

TEST_F(InstMatchesTest_111, MatchMiddleOfRange_111) {
  SetupByteRange('a', 'z', 0);
  EXPECT_TRUE(inst_.Matches('m'));
}

// Test no match outside range
TEST_F(InstMatchesTest_111, NoMatchBelowRange_111) {
  SetupByteRange('a', 'z', 0);
  EXPECT_FALSE(inst_.Matches('`'));  // 'a' - 1
}

TEST_F(InstMatchesTest_111, NoMatchAboveRange_111) {
  SetupByteRange('a', 'z', 0);
  EXPECT_FALSE(inst_.Matches('{'));  // 'z' + 1
}

// Test single character range
TEST_F(InstMatchesTest_111, SingleCharRange_111) {
  SetupByteRange('x', 'x', 0);
  EXPECT_TRUE(inst_.Matches('x'));
  EXPECT_FALSE(inst_.Matches('w'));
  EXPECT_FALSE(inst_.Matches('y'));
}

// Test foldcase: uppercase input should match lowercase range
TEST_F(InstMatchesTest_111, FoldcaseUpperToLower_111) {
  SetupByteRange('a', 'z', 1);
  EXPECT_TRUE(inst_.Matches('A'));
  EXPECT_TRUE(inst_.Matches('Z'));
  EXPECT_TRUE(inst_.Matches('M'));
}

// Test foldcase: lowercase input still matches lowercase range
TEST_F(InstMatchesTest_111, FoldcaseLowercaseStillMatches_111) {
  SetupByteRange('a', 'z', 1);
  EXPECT_TRUE(inst_.Matches('a'));
  EXPECT_TRUE(inst_.Matches('z'));
}

// Test without foldcase: uppercase should NOT match lowercase range
TEST_F(InstMatchesTest_111, NoFoldcaseUpperDoesNotMatchLower_111) {
  SetupByteRange('a', 'z', 0);
  EXPECT_FALSE(inst_.Matches('A'));
  EXPECT_FALSE(inst_.Matches('Z'));
}

// Test foldcase only affects A-Z range
TEST_F(InstMatchesTest_111, FoldcaseDoesNotAffectDigits_111) {
  SetupByteRange('0', '9', 1);
  EXPECT_TRUE(inst_.Matches('0'));
  EXPECT_TRUE(inst_.Matches('9'));
  EXPECT_TRUE(inst_.Matches('5'));
  EXPECT_FALSE(inst_.Matches('a'));
}

// Test foldcase with range that is uppercase
TEST_F(InstMatchesTest_111, FoldcaseWithUppercaseRange_111) {
  // Range is 'A'-'Z', foldcase converts input 'A'-'Z' to 'a'-'z',
  // so 'A' becomes 'a' which is > 'Z', won't match
  SetupByteRange('A', 'Z', 1);
  EXPECT_FALSE(inst_.Matches('A'));  // 'A' folds to 'a' which is > 'Z'
  EXPECT_FALSE(inst_.Matches('Z'));  // 'Z' folds to 'z' which is > 'Z'
}

// Test numeric range
TEST_F(InstMatchesTest_111, NumericRange_111) {
  SetupByteRange('0', '9', 0);
  EXPECT_TRUE(inst_.Matches('0'));
  EXPECT_TRUE(inst_.Matches('9'));
  EXPECT_TRUE(inst_.Matches('5'));
  EXPECT_FALSE(inst_.Matches('/'));  // '0' - 1
  EXPECT_FALSE(inst_.Matches(':'));  // '9' + 1
}

// Test byte range with low values
TEST_F(InstMatchesTest_111, LowByteValues_111) {
  SetupByteRange(0, 10, 0);
  EXPECT_TRUE(inst_.Matches(0));
  EXPECT_TRUE(inst_.Matches(5));
  EXPECT_TRUE(inst_.Matches(10));
  EXPECT_FALSE(inst_.Matches(11));
}

// Test byte range with high values (up to 255)
TEST_F(InstMatchesTest_111, HighByteValues_111) {
  SetupByteRange(200, 255, 0);
  EXPECT_TRUE(inst_.Matches(200));
  EXPECT_TRUE(inst_.Matches(255));
  EXPECT_TRUE(inst_.Matches(230));
  EXPECT_FALSE(inst_.Matches(199));
}

// Test full byte range
TEST_F(InstMatchesTest_111, FullByteRange_111) {
  SetupByteRange(0, 255, 0);
  EXPECT_TRUE(inst_.Matches(0));
  EXPECT_TRUE(inst_.Matches(128));
  EXPECT_TRUE(inst_.Matches(255));
}

// Test boundary: character just at edges
TEST_F(InstMatchesTest_111, BoundaryJustBelowLo_111) {
  SetupByteRange(50, 100, 0);
  EXPECT_FALSE(inst_.Matches(49));
  EXPECT_TRUE(inst_.Matches(50));
}

TEST_F(InstMatchesTest_111, BoundaryJustAboveHi_111) {
  SetupByteRange(50, 100, 0);
  EXPECT_TRUE(inst_.Matches(100));
  EXPECT_FALSE(inst_.Matches(101));
}

// Test foldcase edge: exactly 'A' and 'Z'
TEST_F(InstMatchesTest_111, FoldcaseExactBoundaryA_111) {
  SetupByteRange('a', 'a', 1);
  EXPECT_TRUE(inst_.Matches('A'));  // 'A' folds to 'a'
  EXPECT_TRUE(inst_.Matches('a'));
  EXPECT_FALSE(inst_.Matches('B'));  // 'B' folds to 'b', not in ['a','a']
}

TEST_F(InstMatchesTest_111, FoldcaseExactBoundaryZ_111) {
  SetupByteRange('z', 'z', 1);
  EXPECT_TRUE(inst_.Matches('Z'));  // 'Z' folds to 'z'
  EXPECT_TRUE(inst_.Matches('z'));
  EXPECT_FALSE(inst_.Matches('Y'));  // 'Y' folds to 'y', not in ['z','z']
}

// Test foldcase does not affect characters outside A-Z
TEST_F(InstMatchesTest_111, FoldcaseDoesNotAffectNonAlpha_111) {
  SetupByteRange('[', '`', 1);  // Characters between 'Z'+1 and 'a'-1
  EXPECT_TRUE(inst_.Matches('['));
  EXPECT_TRUE(inst_.Matches('`'));
  EXPECT_TRUE(inst_.Matches('^'));
  EXPECT_FALSE(inst_.Matches('Z'));  // 'Z' folds to 'z', not in ['[','`']
}

// Test that opcode is correctly set after InitByteRange
TEST_F(InstMatchesTest_111, OpcodeAfterInitByteRange_111) {
  SetupByteRange('a', 'z', 0);
  EXPECT_EQ(inst_.opcode(), kInstByteRange);
}

// Test lo and hi accessors
TEST_F(InstMatchesTest_111, LoHiAccessors_111) {
  SetupByteRange(42, 84, 0);
  EXPECT_EQ(inst_.lo(), 42);
  EXPECT_EQ(inst_.hi(), 84);
}

// Test foldcase accessor
TEST_F(InstMatchesTest_111, FoldcaseAccessor_111) {
  SetupByteRange('a', 'z', 1);
  EXPECT_NE(inst_.foldcase(), 0);

  SetupByteRange('a', 'z', 0);
  EXPECT_EQ(inst_.foldcase(), 0);
}

}  // namespace re2
