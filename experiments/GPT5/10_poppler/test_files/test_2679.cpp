// pdfsig_trim_test_2679.cc
#include <gtest/gtest.h>

#include <string>
#include <string_view>

// To test a `static` function with internal linkage, include the implementation
// file into this test translation unit so the symbol is visible here.
// NOTE: This is intentional and avoids re-implementing the function logic.
#include "TestProjects/poppler/utils/pdfsig.cc"

class TrimTest_2679 : public ::testing::Test {};

TEST_F(TrimTest_2679, EmptyInputReturnsEmpty_2679) {
  std::string_view in;
  std::string_view out = trim(in);
  EXPECT_TRUE(out.empty());
  EXPECT_EQ(out.size(), 0u);
}

TEST_F(TrimTest_2679, AllSpacesReturnsEmpty_2679) {
  std::string s = "     ";
  std::string_view out = trim(std::string_view{s});
  EXPECT_TRUE(out.empty());
}

TEST_F(TrimTest_2679, AllTabsReturnsEmpty_2679) {
  std::string s = "\t\t\t";
  std::string_view out = trim(std::string_view{s});
  EXPECT_TRUE(out.empty());
}

TEST_F(TrimTest_2679, AllSpacesAndTabsReturnsEmpty_2679) {
  std::string s = " \t \t\t  \t ";
  std::string_view out = trim(std::string_view{s});
  EXPECT_TRUE(out.empty());
}

TEST_F(TrimTest_2679, NoLeadingOrTrailingWhitespaceReturnsSameView_2679) {
  std::string s = "abcDEF123";
  std::string_view in{s};
  std::string_view out = trim(in);

  EXPECT_EQ(out, "abcDEF123");
  EXPECT_EQ(out.data(), in.data());
  EXPECT_EQ(out.size(), in.size());
}

TEST_F(TrimTest_2679, TrimsLeadingSpaces_2679) {
  std::string s = "   hello";
  std::string_view out = trim(std::string_view{s});
  EXPECT_EQ(out, "hello");
}

TEST_F(TrimTest_2679, TrimsTrailingSpaces_2679) {
  std::string s = "hello   ";
  std::string_view out = trim(std::string_view{s});
  EXPECT_EQ(out, "hello");
}

TEST_F(TrimTest_2679, TrimsLeadingAndTrailingSpaces_2679) {
  std::string s = "   hello world   ";
  std::string_view out = trim(std::string_view{s});
  EXPECT_EQ(out, "hello world");
}

TEST_F(TrimTest_2679, TrimsLeadingAndTrailingTabs_2679) {
  std::string s = "\t\thello\t";
  std::string_view out = trim(std::string_view{s});
  EXPECT_EQ(out, "hello");
}

TEST_F(TrimTest_2679, TrimsMixedSpacesAndTabsAtBothEnds_2679) {
  std::string s = " \t  \thello\t \t ";
  std::string_view out = trim(std::string_view{s});
  EXPECT_EQ(out, "hello");
}

TEST_F(TrimTest_2679, PreservesInteriorSpacesAndTabs_2679) {
  std::string s = "  a\t b  c\t\t d  ";
  std::string_view out = trim(std::string_view{s});
  EXPECT_EQ(out, "a\t b  c\t\t d");
}

TEST_F(TrimTest_2679, DoesNotTrimNewlinesBecauseNotInTrimSet_2679) {
  // The trim set is exactly " \t" (space and tab), so '\n' should remain.
  std::string s = "\n hello \n";
  std::string_view out = trim(std::string_view{s});

  // Leading '\n' is not trimmed; trailing '\n' is not trimmed; only the spaces adjacent may be.
  EXPECT_EQ(out, "\n hello \n");
}

TEST_F(TrimTest_2679, SingleNonWhitespaceCharacterUnchanged_2679) {
  std::string s = "x";
  std::string_view out = trim(std::string_view{s});
  EXPECT_EQ(out, "x");
  EXPECT_EQ(out.data(), s.data());
  EXPECT_EQ(out.size(), 1u);
}

TEST_F(TrimTest_2679, SingleSpaceReturnsEmpty_2679) {
  std::string s = " ";
  std::string_view out = trim(std::string_view{s});
  EXPECT_TRUE(out.empty());
}

TEST_F(TrimTest_2679, ReturnedViewPointsIntoOriginalBuffer_2679) {
  std::string s = " \t  hello  \t ";
  std::string_view in{s};
  std::string_view out = trim(in);

  ASSERT_EQ(out, "hello");
  // Ensure it's a view into the same underlying buffer (no copy).
  EXPECT_GE(out.data(), in.data());
  EXPECT_LE(out.data(), in.data() + in.size());
  EXPECT_EQ(out.data(), s.data() + s.find('h'));
}