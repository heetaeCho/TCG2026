// File: ./TestProjects/re2/re2/tests/charclassbuilder_removeabove_test.cc

#include "gtest/gtest.h"

#include "re2/regexp.h"
#include "re2/util/utf.h"

using re2::CharClassBuilder;
using re2::Rune;
using re2::Runemax;

class CharClassBuilderRemoveAboveTest_375 : public ::testing::Test {
protected:
  CharClassBuilder cc_;
};

// Normal operation: removing above mid-range trims the top.
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAbove_TrimsTopOfRange_375) {
  ASSERT_TRUE(cc_.AddRange(10, 20));
  EXPECT_TRUE(cc_.Contains(10));
  EXPECT_TRUE(cc_.Contains(15));
  EXPECT_TRUE(cc_.Contains(20));

  cc_.RemoveAbove(15);

  EXPECT_TRUE(cc_.Contains(10));
  EXPECT_TRUE(cc_.Contains(15));
  EXPECT_FALSE(cc_.Contains(16));
  EXPECT_FALSE(cc_.Contains(20));
}

// Boundary: r >= Runemax should be a no-op (no removal).
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAbove_NoOp_WhenRIsAtOrAboveRunemax_375) {
  ASSERT_TRUE(cc_.AddRange(100, 200));
  EXPECT_TRUE(cc_.Contains(100));
  EXPECT_TRUE(cc_.Contains(150));
  EXPECT_TRUE(cc_.Contains(200));

  cc_.RemoveAbove(static_cast<Rune>(Runemax));
  // Expect unchanged membership.
  EXPECT_TRUE(cc_.Contains(100));
  EXPECT_TRUE(cc_.Contains(150));
  EXPECT_TRUE(cc_.Contains(200));
}

// Overlapping/adjacent ranges: only content strictly above r disappears; boundary kept.
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAbove_WithMultipleRangesAndBoundary_375) {
  ASSERT_TRUE(cc_.AddRange(0, 5));
  ASSERT_TRUE(cc_.AddRange(8, 12));

  cc_.RemoveAbove(9);

  // Below r remains
  EXPECT_TRUE(cc_.Contains(0));
  EXPECT_TRUE(cc_.Contains(5));
  EXPECT_TRUE(cc_.Contains(8));
  EXPECT_TRUE(cc_.Contains(9));

  // Above r removed
  EXPECT_FALSE(cc_.Contains(10));
  EXPECT_FALSE(cc_.Contains(12));
}

// ASCII lowercase block: if r < 'a', lowercase block is cleared.
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAbove_ClearsLowercaseWhenRBelow_a_375) {
  ASSERT_TRUE(cc_.AddRange('a', 'z'));
  EXPECT_TRUE(cc_.Contains('a'));
  EXPECT_TRUE(cc_.Contains('m'));
  EXPECT_TRUE(cc_.Contains('z'));

  cc_.RemoveAbove('`'); // '`' == 'a' - 1

  EXPECT_FALSE(cc_.Contains('a'));
  EXPECT_FALSE(cc_.Contains('m'));
  EXPECT_FALSE(cc_.Contains('z'));
}

// ASCII lowercase block: truncates to r when 'a' <= r < 'z'.
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAbove_TruncatesLowercaseUpToR_375) {
  ASSERT_TRUE(cc_.AddRange('a', 'z'));
  cc_.RemoveAbove('f');

  EXPECT_TRUE(cc_.Contains('a'));
  EXPECT_TRUE(cc_.Contains('f'));
  EXPECT_FALSE(cc_.Contains('g'));
  EXPECT_FALSE(cc_.Contains('z'));
}

// ASCII uppercase block: if r < 'A', uppercase block is cleared.
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAbove_ClearsUppercaseWhenRBelow_A_375) {
  ASSERT_TRUE(cc_.AddRange('A', 'Z'));
  EXPECT_TRUE(cc_.Contains('A'));
  EXPECT_TRUE(cc_.Contains('M'));
  EXPECT_TRUE(cc_.Contains('Z'));

  cc_.RemoveAbove('@'); // '@' == 'A' - 1

  EXPECT_FALSE(cc_.Contains('A'));
  EXPECT_FALSE(cc_.Contains('M'));
  EXPECT_FALSE(cc_.Contains('Z'));
}

// ASCII uppercase block: truncates to r when 'A' <= r < 'Z'.
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAbove_TruncatesUppercaseUpToR_375) {
  ASSERT_TRUE(cc_.AddRange('A', 'Z'));
  cc_.RemoveAbove('M');

  EXPECT_TRUE(cc_.Contains('A'));
  EXPECT_TRUE(cc_.Contains('M'));
  EXPECT_FALSE(cc_.Contains('N'));
  EXPECT_FALSE(cc_.Contains('Z'));
}

// Empty set: calling RemoveAbove on empty builder should remain empty and not crash.
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAbove_OnEmpty_RemainsEmpty_375) {
  EXPECT_TRUE(cc_.empty());
  cc_.RemoveAbove(1234);
  EXPECT_TRUE(cc_.empty());
}

// Mixed ranges: non-alpha high range trimmed; low range preserved.
TEST_F(CharClassBuilderRemoveAboveTest_375, RemoveAbove_MixedAlphaAndNonAlpha_375) {
  ASSERT_TRUE(cc_.AddRange(0x0100, 0x0200)); // non-ASCII block
  ASSERT_TRUE(cc_.AddRange('a', 'z'));       // ASCII lowercase

  // Verify initial membership
  EXPECT_TRUE(cc_.Contains(0x0100));
  EXPECT_TRUE(cc_.Contains(0x0180));
  EXPECT_TRUE(cc_.Contains(0x0200));
  EXPECT_TRUE(cc_.Contains('a'));
  EXPECT_TRUE(cc_.Contains('z'));

  // Remove above a point inside the non-ASCII block and also inside lowercase
  cc_.RemoveAbove(0x0150);

  // Non-ASCII block truncated to 0x0150
  EXPECT_TRUE(cc_.Contains(0x0100));
  EXPECT_TRUE(cc_.Contains(0x0150));
  EXPECT_FALSE(cc_.Contains(0x0151));
  EXPECT_FALSE(cc_.Contains(0x0200));

  // Lowercase letters above 0x0150 are all above, but since 'a'..'z' are < 0x0150,
  // they should remain unaffected by this particular cutoff.
  EXPECT_TRUE(cc_.Contains('a'));
  EXPECT_TRUE(cc_.Contains('z'));
}
