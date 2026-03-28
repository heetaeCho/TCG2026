#include <gtest/gtest.h>
#include <string>

// Forward declaration of the function under test
void ElideMiddleInPlace(std::string& str, size_t max_width);

// ============================================================
// Tests for strings WITHOUT ANSI escape sequences
// ============================================================

TEST(ElideMiddleInPlaceTest_107, StringShorterThanMaxWidth_107) {
  std::string s = "short";
  ElideMiddleInPlace(s, 10);
  EXPECT_EQ(s, "short");
}

TEST(ElideMiddleInPlaceTest_107, StringEqualToMaxWidth_107) {
  std::string s = "exact";
  ElideMiddleInPlace(s, 5);
  EXPECT_EQ(s, "exact");
}

TEST(ElideMiddleInPlaceTest_107, StringLongerThanMaxWidth_107) {
  std::string s = "Hello, World!";
  ElideMiddleInPlace(s, 10);
  EXPECT_EQ(s.size(), 10u);
  // Should contain "..." in the middle
  EXPECT_NE(s.find("..."), std::string::npos);
}

TEST(ElideMiddleInPlaceTest_107, MaxWidthZero_107) {
  std::string s = "Hello";
  ElideMiddleInPlace(s, 0);
  EXPECT_EQ(s, "");
}

TEST(ElideMiddleInPlaceTest_107, MaxWidthOne_107) {
  std::string s = "Hello";
  ElideMiddleInPlace(s, 1);
  EXPECT_EQ(s, ".");
}

TEST(ElideMiddleInPlaceTest_107, MaxWidthTwo_107) {
  std::string s = "Hello";
  ElideMiddleInPlace(s, 2);
  EXPECT_EQ(s, "..");
}

TEST(ElideMiddleInPlaceTest_107, MaxWidthThree_107) {
  std::string s = "Hello";
  ElideMiddleInPlace(s, 3);
  EXPECT_EQ(s, "...");
}

TEST(ElideMiddleInPlaceTest_107, MaxWidthFour_107) {
  std::string s = "Hello World";
  ElideMiddleInPlace(s, 4);
  EXPECT_EQ(s.size(), 4u);
  // With max_width=4, ellipsis_width=3, remaining=1, left=0, right=1
  // So result = "" + "..." + last char "d"
  EXPECT_NE(s.find("..."), std::string::npos);
}

TEST(ElideMiddleInPlaceTest_107, EmptyString_107) {
  std::string s = "";
  ElideMiddleInPlace(s, 5);
  EXPECT_EQ(s, "");
}

TEST(ElideMiddleInPlaceTest_107, EmptyStringZeroWidth_107) {
  std::string s = "";
  ElideMiddleInPlace(s, 0);
  EXPECT_EQ(s, "");
}

TEST(ElideMiddleInPlaceTest_107, SingleCharStringMaxWidthOne_107) {
  std::string s = "A";
  ElideMiddleInPlace(s, 1);
  EXPECT_EQ(s, "A");
}

TEST(ElideMiddleInPlaceTest_107, EvenLengthString_107) {
  std::string s = "abcdefghij"; // 10 chars
  ElideMiddleInPlace(s, 7);
  EXPECT_EQ(s.size(), 7u);
  EXPECT_NE(s.find("..."), std::string::npos);
  // remaining = 4, left = 2, right = 2
  // "ab" + "..." + "ij"
  EXPECT_EQ(s, "ab...ij");
}

TEST(ElideMiddleInPlaceTest_107, OddLengthString_107) {
  std::string s = "abcdefghi"; // 9 chars
  ElideMiddleInPlace(s, 8);
  EXPECT_EQ(s.size(), 8u);
  EXPECT_NE(s.find("..."), std::string::npos);
  // remaining = 5, left = 2, right = 3
  // "ab" + "..." + "ghi"
  EXPECT_EQ(s, "ab...ghi");
}

TEST(ElideMiddleInPlaceTest_107, MaxWidthJustBelowStringLength_107) {
  std::string s = "abcdef"; // 6 chars
  ElideMiddleInPlace(s, 5);
  EXPECT_EQ(s.size(), 5u);
  // remaining = 2, left = 1, right = 1
  // "a" + "..." + "f"
  EXPECT_EQ(s, "a...f");
}

TEST(ElideMiddleInPlaceTest_107, LongString_107) {
  std::string s = "The quick brown fox jumps over the lazy dog";
  ElideMiddleInPlace(s, 20);
  EXPECT_EQ(s.size(), 20u);
  EXPECT_NE(s.find("..."), std::string::npos);
}

TEST(ElideMiddleInPlaceTest_107, VeryLargeMaxWidth_107) {
  std::string s = "Hello";
  ElideMiddleInPlace(s, 1000);
  EXPECT_EQ(s, "Hello");
}

// ============================================================
// Tests for strings WITH ANSI escape sequences
// ============================================================

TEST(ElideMiddleInPlaceTest_107, AnsiStringNoElisionNeeded_107) {
  // \x1b[31m is a red color escape, \x1b[0m is reset
  // "Hello" is 5 visible chars, with ANSI codes the string is longer
  std::string s = "\x1b[31mHello\x1b[0m";
  ElideMiddleInPlace(s, 5);
  // Visible width is 5, max_width is 5, should not elide
  EXPECT_EQ(s, "\x1b[31mHello\x1b[0m");
}

TEST(ElideMiddleInPlaceTest_107, AnsiStringElisionNeeded_107) {
  // "Hello World" = 11 visible chars, with ANSI codes
  std::string s = "\x1b[31mHello World\x1b[0m";
  size_t original_size = s.size();
  ElideMiddleInPlace(s, 8);
  // Result should have "..." and be 8 visible chars
  EXPECT_NE(s.find("..."), std::string::npos);
  // The ANSI sequences should be preserved in some form
  EXPECT_NE(s.find("\x1b"), std::string::npos);
}

TEST(ElideMiddleInPlaceTest_107, AnsiStringVisibleWidthEqualsMaxWidth_107) {
  std::string s = "\x1b[32mABCDE\x1b[0m"; // 5 visible chars
  ElideMiddleInPlace(s, 5);
  EXPECT_EQ(s, "\x1b[32mABCDE\x1b[0m");
}

TEST(ElideMiddleInPlaceTest_107, AnsiStringVisibleWidthLessThanMaxWidth_107) {
  std::string s = "\x1b[32mABC\x1b[0m"; // 3 visible chars
  ElideMiddleInPlace(s, 10);
  EXPECT_EQ(s, "\x1b[32mABC\x1b[0m");
}

TEST(ElideMiddleInPlaceTest_107, AnsiStringMaxWidthOne_107) {
  std::string s = "\x1b[31mHello World\x1b[0m";
  ElideMiddleInPlace(s, 1);
  // Should contain just "." as visible, plus possibly ANSI codes
  size_t dot_count = 0;
  for (char c : s) {
    if (c == '.') dot_count++;
  }
  EXPECT_GE(dot_count, 1u);
}

TEST(ElideMiddleInPlaceTest_107, AnsiStringMaxWidthTwo_107) {
  std::string s = "\x1b[31mHello World\x1b[0m";
  ElideMiddleInPlace(s, 2);
  size_t dot_count = 0;
  for (char c : s) {
    if (c == '.') dot_count++;
  }
  EXPECT_GE(dot_count, 2u);
}

TEST(ElideMiddleInPlaceTest_107, AnsiStringMaxWidthThree_107) {
  std::string s = "\x1b[31mHello World\x1b[0m";
  ElideMiddleInPlace(s, 3);
  EXPECT_NE(s.find("..."), std::string::npos);
}

TEST(ElideMiddleInPlaceTest_107, MultipleAnsiSequences_107) {
  // Multiple color codes interspersed
  std::string s = "\x1b[31mHe\x1b[32mllo \x1b[33mWorld\x1b[0m"; // 10 visible chars "Hello World" minus space = "Hello World"
  ElideMiddleInPlace(s, 6);
  EXPECT_NE(s.find("..."), std::string::npos);
}

TEST(ElideMiddleInPlaceTest_107, AnsiOnlyString_107) {
  // String with only ANSI escape and no visible chars
  std::string s = "\x1b[31m\x1b[0m";
  ElideMiddleInPlace(s, 0);
  // Visible width is 0, max_width is 0, should not change
  EXPECT_EQ(s, "\x1b[31m\x1b[0m");
}

TEST(ElideMiddleInPlaceTest_107, PlainStringExactlyEllipsisWidth_107) {
  std::string s = "abcd"; // 4 chars
  ElideMiddleInPlace(s, 3);
  EXPECT_EQ(s, "...");
}

TEST(ElideMiddleInPlaceTest_107, ResultPreservesCorrectEndsPlain_107) {
  std::string s = "0123456789"; // 10 chars
  ElideMiddleInPlace(s, 7);
  // remaining = 4, left = 2, right = 2
  // "01" + "..." + "89"
  EXPECT_EQ(s, "01...89");
}

TEST(ElideMiddleInPlaceTest_107, ResultPreservesCorrectEndsPlainOddRemaining_107) {
  std::string s = "0123456789"; // 10 chars
  ElideMiddleInPlace(s, 6);
  // remaining = 3, left = 1, right = 2
  // "0" + "..." + "89"
  EXPECT_EQ(s, "0...89");
}

TEST(ElideMiddleInPlaceTest_107, TwoCharStringMaxWidthOne_107) {
  std::string s = "AB";
  ElideMiddleInPlace(s, 1);
  EXPECT_EQ(s, ".");
}

TEST(ElideMiddleInPlaceTest_107, ResultSizeMatchesMaxWidthPlain_107) {
  for (size_t max_width = 0; max_width <= 10; ++max_width) {
    std::string s = "abcdefghijklmnop"; // 16 chars
    ElideMiddleInPlace(s, max_width);
    EXPECT_EQ(s.size(), max_width) << "Failed for max_width=" << max_width;
  }
}

TEST(ElideMiddleInPlaceTest_107, AnsiStringPreservesResetCode_107) {
  std::string s = "\x1b[31mHello World!\x1b[0m"; // 12 visible chars
  ElideMiddleInPlace(s, 8);
  // The reset code at the end should still be present
  size_t reset_pos = s.rfind("\x1b[0m");
  EXPECT_NE(reset_pos, std::string::npos);
}

TEST(ElideMiddleInPlaceTest_107, AnsiAtBoundaryOfElision_107) {
  // Place ANSI code right in the middle where elision happens
  std::string s = "abc\x1b[31mdefghij\x1b[0m"; // visible: "abcdefghij" = 10 chars
  ElideMiddleInPlace(s, 7);
  EXPECT_NE(s.find("..."), std::string::npos);
}

TEST(ElideMiddleInPlaceTest_107, MaxWidthLargerThanStringNoAnsi_107) {
  std::string s = "test";
  std::string original = s;
  ElideMiddleInPlace(s, 100);
  EXPECT_EQ(s, original);
}
