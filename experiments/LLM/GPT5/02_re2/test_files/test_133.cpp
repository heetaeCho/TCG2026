// File: tests/prog_beginptr_test_133.cc

#include <gtest/gtest.h>
#include <string>
#include "absl/strings/string_view.h"
#include "re2/prog.h"  // contains re2::BeginPtr

// Normal operation: std::string-backed view returns pointer to first char.
TEST(BeginPtrTest_133, ReturnsStartForStdString_133) {
  std::string s = "hello";
  absl::string_view sv(s);
  EXPECT_EQ(re2::BeginPtr(sv), s.data());
  EXPECT_EQ(re2::BeginPtr(sv), &s[0]);
}

// Boundary: empty std::string-backed view should return the same pointer as string::data().
TEST(BeginPtrTest_133, EmptyStdStringView_133) {
  std::string s;
  absl::string_view sv(s);
  // For an empty string, data() is a valid pointer to an internal buffer; we only check equality.
  EXPECT_EQ(re2::BeginPtr(sv), s.data());
}

// Boundary: default-constructed string_view (no backing storage) should yield nullptr from data().
TEST(BeginPtrTest_133, DefaultConstructedStringView_133) {
  absl::string_view sv;  // size==0, data()==nullptr
  EXPECT_EQ(re2::BeginPtr(sv), nullptr);
}

// Normal operation: view over a substring should return pointer to that substring start.
TEST(BeginPtrTest_133, SubstringViewReturnsCorrectPointer_133) {
  std::string s = "abcdef";
  absl::string_view sv(s.data() + 2, 3);  // "cde"
  EXPECT_EQ(re2::BeginPtr(sv), s.data() + 2);
}

// Normal operation: C-string literal view returns the literal's base pointer.
TEST(BeginPtrTest_133, CStringLiteralView_133) {
  const char* lit = "abc";
  absl::string_view sv(lit);
  EXPECT_EQ(re2::BeginPtr(sv), lit);
}

// Normal operation with UTF-8: multibyte content still returns the same start pointer.
TEST(BeginPtrTest_133, Utf8ContentView_133) {
  std::string utf8 = u8"한글 테스트";  // UTF-8 multibyte
  absl::string_view sv(utf8);
  EXPECT_EQ(re2::BeginPtr(sv), utf8.data());
}
