// File: elide_middle_test_107.cc

#include <gtest/gtest.h>
#include <string>

// Include the implementation or its header, depending on your project layout.
// If you have elide_middle.h, prefer that:
// #include "elide_middle.h"
#include "elide_middle.cc"

namespace {

// Helper: extract only *visible* characters using the public iterator API.
// This does not reimplement internal logic; it just consumes the iterator.
std::string ExtractVisibleChars(const std::string& input) {
    std::string visible;
    VisibleInputCharsIterator it(input);
    for (; it.HasChar(); it.NextChar()) {
        if (it.IsVisible()) {
            visible.push_back(input[it.InputIndex()]);
        }
    }
    return visible;
}

}  // namespace

// ---- Tests for non-ANSI strings ----

TEST(ElideMiddleInPlaceTest_107, ShortStringWithoutAnsi_RemainsUnchanged_107) {
    std::string s = "hello";
    ElideMiddleInPlace(s, 10);
    EXPECT_EQ("hello", s);

    // Also check boundary: exactly equal to max_width.
    std::string t = "world";
    ElideMiddleInPlace(t, 5);
    EXPECT_EQ("world", t);
}

TEST(ElideMiddleInPlaceTest_107, LongStringWithoutAnsi_ElidesEvenSplit_107) {
    // 10 chars, max_width 7 -> expect left 2, "..." (3), right 2.
    std::string s = "abcdefghij";
    ElideMiddleInPlace(s, 7);
    EXPECT_EQ("ab...ij", s);
    EXPECT_LE(s.size(), 7u);
}

TEST(ElideMiddleInPlaceTest_107, LongStringWithoutAnsi_ElidesOddSplit_107) {
    // 10 chars, max_width 6 -> expect left 1, "..." (3), right 2.
    std::string s = "abcdefghij";
    ElideMiddleInPlace(s, 6);
    EXPECT_EQ("a...ij", s);
    EXPECT_LE(s.size(), 6u);
}

TEST(ElideMiddleInPlaceTest_107, LongStringWithoutAnsi_MaxWidthZeroOrSmall_107) {
    // max_width == 0: result should be empty.
    std::string s = "abcdef";
    ElideMiddleInPlace(s, 0);
    EXPECT_EQ("", s);

    // max_width == 2 (less than ellipsis width 3): truncated ellipsis.
    std::string t = "abcdef";
    ElideMiddleInPlace(t, 2);
    EXPECT_EQ("..", t);

    // max_width == 3: full ellipsis.
    std::string u = "abcdef";
    ElideMiddleInPlace(u, 3);
    EXPECT_EQ("...", u);
}

// ---- Tests for ANSI-colored strings ----

TEST(ElideMiddleInPlaceTest_107, AnsiColoredString_VisibleWidthWithinLimit_NoChange_107) {
    // "\x1b[31mRED\x1b[0m" is 3 visible chars ("RED") but longer in bytes.
    std::string s = "\x1b[31mRED\x1b[0m";
    std::string original = s;

    // max_width equals visible width -> no eliding expected.
    ElideMiddleInPlace(s, 3);

    EXPECT_EQ(original, s);
    EXPECT_NE(std::string::npos, s.find("\x1b[31m"));
    EXPECT_NE(std::string::npos, s.find("\x1b[0m"));
}

TEST(ElideMiddleInPlaceTest_107, AnsiColoredString_ElidesMiddle_PreservesColorCodes_107) {
    // Visible text: "HelloWorld" (10 chars), wrapped in red color + reset.
    std::string s = "\x1b[31mHelloWorld\x1b[0m";

    // Request shortening to visible width 7.
    ElideMiddleInPlace(s, 7);

    // Check that visible characters were elided to something like "He...ld".
    std::string visible = ExtractVisibleChars(s);
    EXPECT_EQ("He...ld", visible);
    EXPECT_LE(visible.size(), 7u);

    // Check that color escape and reset sequences are still present.
    EXPECT_NE(std::string::npos, s.find("\x1b[31m"));
    EXPECT_NE(std::string::npos, s.find("\x1b[0m"));
}

TEST(ElideMiddleInPlaceTest_107, AnsiColoredString_MaxWidthLessThanThree_VisibleDots_107) {
    // Same colored "RED" example, but with very small max_width.
    std::string s = "\x1b[31mRED\x1b[0m";

    ElideMiddleInPlace(s, 2);

    // Visible part should be two dots; ANSI sequences may still wrap them.
    std::string visible = ExtractVisibleChars(s);
    EXPECT_EQ("..", visible);
    EXPECT_NE(std::string::npos, s.find("\x1b[31m"));
    EXPECT_NE(std::string::npos, s.find("\x1b[0m"));
}

