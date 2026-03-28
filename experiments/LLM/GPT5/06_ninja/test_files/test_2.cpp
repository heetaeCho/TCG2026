#include <gtest/gtest.h>
#include <string>
#include "string_piece.h"

class StringPieceTest_2 : public ::testing::Test {};

// Basic reflexivity: an object must not be != to itself.
TEST_F(StringPieceTest_2, NotEqualIsFalseForSameInstance_2) {
  StringPiece sp("hello");

  EXPECT_TRUE(sp == sp);
  EXPECT_FALSE(sp != sp);
}

// Two StringPieces with the same contents constructed from std::string
// should compare equal, and therefore != should be false.
TEST_F(StringPieceTest_2, NotEqualIsFalseForEqualContents_2) {
  std::string text = "ninja";
  StringPiece sp1(text);
  StringPiece sp2(text);

  EXPECT_TRUE(sp1 == sp2);
  EXPECT_FALSE(sp1 != sp2);
  EXPECT_FALSE(sp2 != sp1);
}

// StringPieces with different contents should compare not equal,
// and therefore != should be true.
TEST_F(StringPieceTest_2, NotEqualIsTrueForDifferentContents_2) {
  StringPiece sp1("abc");
  StringPiece sp2("abd");

  EXPECT_FALSE(sp1 == sp2);
  EXPECT_TRUE(sp1 != sp2);
  EXPECT_TRUE(sp2 != sp1);
}

// StringPieces with different lengths but same prefix should be not equal,
// and therefore != should be true.
TEST_F(StringPieceTest_2, NotEqualIsTrueForDifferentLengths_2) {
  StringPiece sp_short("abc");
  StringPiece sp_long("abcd");

  EXPECT_FALSE(sp_short == sp_long);
  EXPECT_TRUE(sp_short != sp_long);
  EXPECT_TRUE(sp_long != sp_short);
}

// Default-constructed StringPiece: check that != is consistent with ==.
TEST_F(StringPieceTest_2, NotEqualIsFalseForDefaultConstructedSelfComparison_2) {
  StringPiece sp_default;

  EXPECT_TRUE(sp_default == sp_default);
  EXPECT_FALSE(sp_default != sp_default);
}

// General consistency: for several representative cases, verify that
// operator!= is exactly the logical negation of operator==.
TEST_F(StringPieceTest_2, NotEqualIsLogicalNegationOfEqual_2) {
  struct Case {
    std::string a;
    std::string b;
  } cases[] = {
      {"", ""},          // both empty
      {"", "x"},         // empty vs non-empty
      {"x", ""},         // non-empty vs empty
      {"same", "same"},  // equal non-empty
      {"foo", "bar"},    // completely different
      {"abcd", "abce"},  // differ at last character
  };

  for (const auto& c : cases) {
    StringPiece sp1(c.a);
    StringPiece sp2(c.b);

    bool eq = (sp1 == sp2);
    bool neq = (sp1 != sp2);

    EXPECT_EQ(eq, !neq) << "Failed for a=\"" << c.a
                        << "\" b=\"" << c.b << "\"";
  }
}
