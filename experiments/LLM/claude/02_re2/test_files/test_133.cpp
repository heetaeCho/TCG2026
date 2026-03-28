#include <gtest/gtest.h>
#include "re2/prog.h"
#include "absl/strings/string_view.h"

// Test normal operation with a regular string
TEST(BeginPtrTest_133, NormalString_133) {
  const char* str = "hello world";
  absl::string_view sv(str);
  EXPECT_EQ(re2::BeginPtr(sv), str);
}

// Test with an empty string view constructed from a literal
TEST(BeginPtrTest_133, EmptyStringView_133) {
  absl::string_view sv("");
  EXPECT_NE(sv.data(), nullptr);
  EXPECT_EQ(re2::BeginPtr(sv), sv.data());
}

// Test with a default-constructed string_view
TEST(BeginPtrTest_133, DefaultConstructedStringView_133) {
  absl::string_view sv;
  EXPECT_EQ(re2::BeginPtr(sv), sv.data());
}

// Test that BeginPtr returns a pointer to the beginning of the string data
TEST(BeginPtrTest_133, PointsToFirstCharacter_133) {
  const char* str = "abcdef";
  absl::string_view sv(str);
  EXPECT_EQ(*re2::BeginPtr(sv), 'a');
}

// Test with a substring (string_view pointing into the middle of a string)
TEST(BeginPtrTest_133, SubstringView_133) {
  const char* str = "hello world";
  absl::string_view sv(str + 6, 5);  // "world"
  EXPECT_EQ(re2::BeginPtr(sv), str + 6);
  EXPECT_EQ(*re2::BeginPtr(sv), 'w');
}

// Test with a single character string
TEST(BeginPtrTest_133, SingleCharacterString_133) {
  const char* str = "x";
  absl::string_view sv(str, 1);
  EXPECT_EQ(re2::BeginPtr(sv), str);
  EXPECT_EQ(*re2::BeginPtr(sv), 'x');
}

// Test that BeginPtr returns the same value as data()
TEST(BeginPtrTest_133, ConsistentWithData_133) {
  absl::string_view sv("test string");
  EXPECT_EQ(re2::BeginPtr(sv), sv.data());
}

// Test with a std::string backing
TEST(BeginPtrTest_133, StdStringBacking_133) {
  std::string s = "backed by std::string";
  absl::string_view sv(s);
  EXPECT_EQ(re2::BeginPtr(sv), s.data());
}

// Test with a string_view of length zero but non-null pointer
TEST(BeginPtrTest_133, ZeroLengthNonNull_133) {
  const char* str = "nonempty";
  absl::string_view sv(str, 0);
  EXPECT_EQ(re2::BeginPtr(sv), str);
}

// Test with a long string
TEST(BeginPtrTest_133, LongString_133) {
  std::string long_str(10000, 'a');
  absl::string_view sv(long_str);
  EXPECT_EQ(re2::BeginPtr(sv), long_str.data());
}

// Test that multiple calls return the same pointer
TEST(BeginPtrTest_133, Idempotent_133) {
  absl::string_view sv("idempotent test");
  const char* first = re2::BeginPtr(sv);
  const char* second = re2::BeginPtr(sv);
  EXPECT_EQ(first, second);
}

// Test with a string containing null bytes
TEST(BeginPtrTest_133, StringWithNullBytes_133) {
  const char data[] = "hel\0lo";
  absl::string_view sv(data, 6);
  EXPECT_EQ(re2::BeginPtr(sv), data);
  EXPECT_EQ(*re2::BeginPtr(sv), 'h');
}
