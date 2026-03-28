#include <gtest/gtest.h>
#include <string>
#include "absl/strings/string_view.h"

// Include the header under test
#include "re2/prog.h"

namespace re2 {
namespace {

// Test normal operation with a typical string
TEST(EndPtrTest_134, NormalString_134) {
  std::string str = "hello";
  absl::string_view sv(str);
  const char* result = EndPtr(sv);
  EXPECT_EQ(result, sv.data() + sv.size());
  EXPECT_EQ(result, str.data() + str.size());
}

// Test with an empty string
TEST(EndPtrTest_134, EmptyString_134) {
  absl::string_view sv("");
  const char* result = EndPtr(sv);
  EXPECT_EQ(result, sv.data() + sv.size());
  EXPECT_EQ(result, sv.data());
}

// Test with a default-constructed string_view
TEST(EndPtrTest_134, DefaultConstructedStringView_134) {
  absl::string_view sv;
  const char* result = EndPtr(sv);
  // For default-constructed string_view, data() may be nullptr and size() is 0
  EXPECT_EQ(result, sv.data() + sv.size());
}

// Test with a single character string
TEST(EndPtrTest_134, SingleCharacterString_134) {
  absl::string_view sv("x");
  const char* result = EndPtr(sv);
  EXPECT_EQ(result, sv.data() + 1);
}

// Test with a substring (partial view)
TEST(EndPtrTest_134, SubstringView_134) {
  std::string str = "hello world";
  absl::string_view sv(str.data() + 3, 5);  // "lo wo"
  const char* result = EndPtr(sv);
  EXPECT_EQ(result, str.data() + 3 + 5);
  EXPECT_EQ(result, sv.data() + sv.size());
}

// Test that EndPtr points one past the last character
TEST(EndPtrTest_134, PointsOnePastLastChar_134) {
  std::string str = "abcdef";
  absl::string_view sv(str);
  const char* result = EndPtr(sv);
  // result should point one past 'f'
  EXPECT_EQ(*(result - 1), 'f');
}

// Test with a longer string
TEST(EndPtrTest_134, LongerString_134) {
  std::string str(1000, 'a');
  absl::string_view sv(str);
  const char* result = EndPtr(sv);
  EXPECT_EQ(result, sv.data() + 1000);
}

// Test with a string containing null bytes
TEST(EndPtrTest_134, StringWithNullBytes_134) {
  std::string str("abc\0def", 7);
  absl::string_view sv(str.data(), str.size());
  const char* result = EndPtr(sv);
  EXPECT_EQ(result, sv.data() + 7);
}

// Test that EndPtr(sv) - sv.data() equals sv.size()
TEST(EndPtrTest_134, DifferenceEqualsSize_134) {
  std::string str = "testing123";
  absl::string_view sv(str);
  const char* result = EndPtr(sv);
  EXPECT_EQ(static_cast<size_t>(result - sv.data()), sv.size());
}

// Test with a zero-length view into a non-empty string
TEST(EndPtrTest_134, ZeroLengthViewIntoString_134) {
  std::string str = "hello";
  absl::string_view sv(str.data() + 2, 0);
  const char* result = EndPtr(sv);
  EXPECT_EQ(result, str.data() + 2);
  EXPECT_EQ(result, sv.data());
}

}  // namespace
}  // namespace re2
