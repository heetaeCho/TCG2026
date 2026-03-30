// File: prog_endptr_test.cc
#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

#include "re2/prog.h"  // contains re2::EndPtr

namespace {

using re2::EndPtr;

// Empty input -> end pointer should equal begin pointer
TEST(EndPtrTest_134, EmptyStringView_ReturnsBeginPtr_134) {
  absl::string_view sv;
  const char* begin = sv.data();
  const char* end = EndPtr(sv);
  EXPECT_EQ(end, begin);
}

// Simple non-empty ASCII -> end pointer should be begin + size
TEST(EndPtrTest_134, NonEmptyAscii_ReturnsPastLastChar_134) {
  const std::string s = "re2";
  absl::string_view sv(s);
  const char* begin = sv.data();
  const char* end = EndPtr(sv);
  EXPECT_EQ(end - begin, static_cast<std::ptrdiff_t>(sv.size()));
}

// Embedded NUL bytes -> function must honor size, not C-string terminators
TEST(EndPtrTest_134, EmbeddedNull_UsesSizeNotTerminator_134) {
  const char raw[] = {'a', '\0', 'b', '\0', 'c'};
  absl::string_view sv(raw, sizeof(raw));  // length = 5
  const char* begin = sv.data();
  const char* end = EndPtr(sv);
  EXPECT_EQ(end, begin + sv.size());       // should be 5 past begin
}

// View constructed from a substring (non-owning) -> still past-end of the view
TEST(EndPtrTest_134, SubstringView_PastEndOfView_134) {
  const std::string backing = "0123456789";
  absl::string_view sv(backing.data() + 3, 4);  // "3456"
  const char* begin = sv.data();
  const char* end = EndPtr(sv);
  EXPECT_EQ(end, begin + sv.size());            // 4 past begin
  // Sanity: the pointed-to "end" should equal address of '7' in backing
  EXPECT_EQ(end, backing.data() + 7);
}

// UTF-8 multibyte content -> movement is by bytes, not code points
TEST(EndPtrTest_134, Utf8Content_AdvancesByByteCount_134) {
  // "한글" in UTF-8 (each char is 3 bytes in UTF-8)
  const std::string utf8 = u8"한글";
  absl::string_view sv(utf8);
  const char* begin = sv.data();
  const char* end = EndPtr(sv);
  EXPECT_EQ(end, begin + sv.size());
  // Expect exactly 6 bytes for two Korean syllables in UTF-8
  EXPECT_EQ(sv.size(), 6u);
}

// Large input -> still correct pointer arithmetic
TEST(EndPtrTest_134, LargeInput_CorrectPastEnd_134) {
  std::string s(1 << 20, 'x');  // 1 MiB
  absl::string_view sv(s);
  const char* begin = sv.data();
  const char* end = EndPtr(sv);
  EXPECT_EQ(end, begin + sv.size());
}

}  // namespace
