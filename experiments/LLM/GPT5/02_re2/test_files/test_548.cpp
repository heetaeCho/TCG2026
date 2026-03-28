// File: prefilter_info_star_test_548.cc

#include <gtest/gtest.h>

// Assume the library exposes the required declarations in these headers.
// If your project uses a different include path, adjust accordingly.
#include "re2/prefilter.h"

using namespace re2;

class PrefilterInfoStarTest_548 : public ::testing::Test {
protected:
  // Helper to create a simple operand; each call returns a fresh instance
  static Prefilter::Info* MakeEmpty() { return Prefilter::Info::EmptyString(); }
  static Prefilter::Info* MakeAny() { return Prefilter::Info::AnyCharOrAnyByte(); }
  static Prefilter::Info* MakeLiteralLatin1(char c) {
    return Prefilter::Info::LiteralLatin1(static_cast<Rune>(static_cast<unsigned char>(c)));
  }
};

// Star should behave identically to Quest for the same logical operand (EmptyString)
TEST_F(PrefilterInfoStarTest_548, StarBehavesLikeQuest_OnEmptyString_548) {
  Prefilter::Info* a1 = MakeEmpty();
  Prefilter::Info* star = Prefilter::Info::Star(a1);
  ASSERT_NE(nullptr, star);

  Prefilter::Info* a2 = MakeEmpty();
  Prefilter::Info* quest = Prefilter::Info::Quest(a2);
  ASSERT_NE(nullptr, quest);

  // Compare via observable ToString results only (black-box)
  EXPECT_EQ(star->ToString(), quest->ToString());
}

// Star should behave identically to Quest for AnyChar/AnyByte
TEST_F(PrefilterInfoStarTest_548, StarBehavesLikeQuest_OnAnyCharOrAnyByte_548) {
  Prefilter::Info* a1 = MakeAny();
  Prefilter::Info* star = Prefilter::Info::Star(a1);
  ASSERT_NE(nullptr, star);

  Prefilter::Info* a2 = MakeAny();
  Prefilter::Info* quest = Prefilter::Info::Quest(a2);
  ASSERT_NE(nullptr, quest);

  EXPECT_EQ(star->ToString(), quest->ToString());
}

// Star should behave identically to Quest for a simple Latin1 literal (boundary-ish: non-ASCII possible too)
TEST_F(PrefilterInfoStarTest_548, StarBehavesLikeQuest_OnLiteralLatin1_548) {
  Prefilter::Info* a1 = MakeLiteralLatin1('A');
  Prefilter::Info* star = Prefilter::Info::Star(a1);
  ASSERT_NE(nullptr, star);

  Prefilter::Info* a2 = MakeLiteralLatin1('A');
  Prefilter::Info* quest = Prefilter::Info::Quest(a2);
  ASSERT_NE(nullptr, quest);

  EXPECT_EQ(star->ToString(), quest->ToString());
}

// Star vs Quest should stay equivalent across a composed operand created through public API (Concat)
// (normal operation across combination)
TEST_F(PrefilterInfoStarTest_548, StarBehavesLikeQuest_OnComposedOperand_Concat_548) {
  // Build operand via public factories only
  Prefilter::Info* left1  = MakeLiteralLatin1('x');
  Prefilter::Info* right1 = MakeAny();
  Prefilter::Info* concat1 = Prefilter::Info::Concat(left1, right1);
  ASSERT_NE(nullptr, concat1);

  Prefilter::Info* star = Prefilter::Info::Star(concat1);
  ASSERT_NE(nullptr, star);

  Prefilter::Info* left2  = MakeLiteralLatin1('x');
  Prefilter::Info* right2 = MakeAny();
  Prefilter::Info* concat2 = Prefilter::Info::Concat(left2, right2);
  ASSERT_NE(nullptr, concat2);

  Prefilter::Info* quest = Prefilter::Info::Quest(concat2);
  ASSERT_NE(nullptr, quest);

  EXPECT_EQ(star->ToString(), quest->ToString());
}
