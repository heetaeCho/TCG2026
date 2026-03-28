// File: re2_trunc_test_241.cc
#include <string>
#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// Include the implementation unit so we can call the internal-linkage function.
// This is necessary because trunc() is declared 'static' inside the .cc file.
#include "re2/re2.cc"

using std::string;

class Re2TruncTest_241 : public ::testing::Test {};

// Normal operation: returns the original string when length < 100
TEST_F(Re2TruncTest_241, ReturnsOriginalWhenShort_241) {
  absl::string_view in = "hello world";
  string out = re2::trunc(in);
  EXPECT_EQ(out, string(in));
  EXPECT_EQ(out.size(), in.size());
}

// Boundary: length exactly 99 -> unchanged
TEST_F(Re2TruncTest_241, ReturnsOriginalWhenLen99_241) {
  string in(99, 'a');
  string out = re2::trunc(absl::string_view(in));
  EXPECT_EQ(out, in);
  EXPECT_EQ(out.size(), 99u);
}

// Boundary: length exactly 100 -> first 100 chars + "..."
TEST_F(Re2TruncTest_241, TruncatesAndAppendsEllipsisAtLen100_241) {
  string in(100, 'b');
  string out = re2::trunc(absl::string_view(in));
  EXPECT_EQ(out.size(), 103u);                 // 100 + 3 for "..."
  EXPECT_EQ(out.substr(0, 100), in);           // prefix preserved
  EXPECT_EQ(out.substr(100), string("..."));   // ellipsis appended
}

// Boundary/long: length 101 -> still first 100 + "..."
TEST_F(Re2TruncTest_241, TruncatesAndAppendsEllipsisWhenOver100_241) {
  string in(101, 'c');
  string out = re2::trunc(absl::string_view(in));
  EXPECT_EQ(out.size(), 103u);
  EXPECT_EQ(out.substr(0, 100), in.substr(0, 100));
  EXPECT_EQ(out.substr(100), string("..."));
}

// Edge: empty input -> empty output
TEST_F(Re2TruncTest_241, EmptyInputReturnsEmpty_241) {
  absl::string_view in = "";
  string out = re2::trunc(in);
  EXPECT_TRUE(out.empty());
}

// Edge: very long input -> only first 100 bytes + "..."
TEST_F(Re2TruncTest_241, VeryLongInputIsTruncatedTo100PlusEllipsis_241) {
  string in(1000, 'x');
  string out = re2::trunc(absl::string_view(in));
  EXPECT_EQ(out.size(), 103u);
  EXPECT_EQ(out.substr(0, 100), string(100, 'x'));
  EXPECT_EQ(out.substr(100), string("..."));
}

// Multibyte UTF-8: truncates by bytes; result is first 100 bytes + "..."
TEST_F(Re2TruncTest_241, Utf8InputTruncatedByBytes_241) {
  // "가" is 3 bytes in UTF-8; 50 copies => 150 bytes
  const std::string multibyte = []{
    std::string s;
    for (int i = 0; i < 50; ++i) s += u8"가";
    return s;
  }();

  ASSERT_EQ(multibyte.size(), 150u); // sanity check for the test setup

  std::string out = re2::trunc(absl::string_view(multibyte));
  EXPECT_EQ(out.size(), 103u);
  EXPECT_EQ(out.substr(0, 100), multibyte.substr(0, 100)); // exact byte prefix
  EXPECT_EQ(out.substr(100), std::string("..."));
}

// Multibyte UTF-8 under limit: unchanged when total bytes < 100
TEST_F(Re2TruncTest_241, Utf8InputUnderLimitUnchanged_241) {
  // 30 copies of "가" => 90 bytes
  std::string in;
  for (int i = 0; i < 30; ++i) in += u8"가";

  ASSERT_EQ(in.size(), 90u); // sanity check

  std::string out = re2::trunc(absl::string_view(in));
  EXPECT_EQ(out, in);
  EXPECT_EQ(out.size(), 90u);
}
