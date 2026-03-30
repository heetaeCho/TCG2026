// File: parse_char_test_269.cc
#include <gtest/gtest.h>

// Forward declare the function under test exactly as exposed by the interface.
namespace re2 { namespace re2_internal {
bool Parse(const char* str, size_t n, char* dest);
}}

// Normal operation: n == 1, dest != nullptr, writes first char and returns true.
TEST(ParseCharTest_269, ReturnsTrueAndWritesChar_WhenNIsOne_269) {
  const char* input = "abc";
  char out = '\0';

  bool ok = re2::re2_internal::Parse(input, /*n=*/1, &out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, 'a');  // observable effect through output parameter
}

// Boundary: n == 1, dest == nullptr, should return true and not crash.
TEST(ParseCharTest_269, ReturnsTrue_WhenNIsOneAndDestNull_269) {
  const char* input = "Z";
  // Just verify the return value; absence of crash is also a behavioral check.
  bool ok = re2::re2_internal::Parse(input, /*n=*/1, /*dest=*/nullptr);
  EXPECT_TRUE(ok);
}

// Boundary: n == 0, should return false and not modify dest.
TEST(ParseCharTest_269, ReturnsFalse_WhenNIsZero_AndDoesNotModifyDest_269) {
  const char* input = "ignored";
  char out = 'X';

  bool ok = re2::re2_internal::Parse(input, /*n=*/0, &out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(out, 'X');  // ensure no observable modification
}

// Boundary: n > 1, should return false and not modify dest.
TEST(ParseCharTest_269, ReturnsFalse_WhenNGreaterThanOne_AndDoesNotModifyDest_269) {
  const char* input = "hello";
  char out = 'Y';

  bool ok = re2::re2_internal::Parse(input, /*n=*/2, &out);

  EXPECT_FALSE(ok);
  EXPECT_EQ(out, 'Y');  // ensure no observable modification
}

// Exceptional/edge: n != 1 and dest == nullptr, should return false and not crash.
TEST(ParseCharTest_269, ReturnsFalse_WhenNNotOneAndDestNull_269) {
  const char* input = "ignored";
  bool ok = re2::re2_internal::Parse(input, /*n=*/3, /*dest=*/nullptr);
  EXPECT_FALSE(ok);
}
