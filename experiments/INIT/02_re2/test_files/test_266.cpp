// File: re2_parse_test_266.cc
#include <gtest/gtest.h>
#include <cstddef>
#include <limits>

// Forward declaration of the function under test based on the provided interface.
// (We do not include or depend on private headers or internals.)
namespace re2 {
namespace re2_internal {
bool Parse(const char* str, size_t n, void* dest);
}  // namespace re2_internal
}  // namespace re2

using re2::re2_internal::Parse;

// Normal operation: when dest == nullptr, Parse should return true (per observable behavior).
TEST(ParseTest_266, NullDestReturnsTrueRegardlessOfStrAndN_266) {
  const char* text = "anything";
  EXPECT_TRUE(Parse(text, 0, nullptr));
  EXPECT_TRUE(Parse(text, 3, nullptr));
  EXPECT_TRUE(Parse(text, 999, nullptr));
}

// Normal operation: when dest != nullptr, Parse should return false.
TEST(ParseTest_266, NonNullDestReturnsFalse_266) {
  int out = 0;
  const char* text = "abc";
  EXPECT_FALSE(Parse(text, 0, &out));
  EXPECT_FALSE(Parse(text, 3, &out));
}

// Boundary condition: str may be nullptr; since behavior depends only on dest,
// a nullptr str should not affect the return value.
TEST(ParseTest_266, AcceptsNullStrPointer_266) {
  int out = 0;
  EXPECT_TRUE(Parse(nullptr, 0, nullptr));        // dest == nullptr => true
  EXPECT_FALSE(Parse(nullptr, 10, &out));         // dest != nullptr => false
}

// Boundary condition: very large n should not affect the result (n is ignored per observable behavior).
TEST(ParseTest_266, IgnoresNIncludingMaxValue_266) {
  int out = 0;
  const size_t huge = std::numeric_limits<size_t>::max();
  EXPECT_TRUE(Parse("x", huge, nullptr));         // still true because dest == nullptr
  EXPECT_FALSE(Parse("x", huge, &out));           // still false because dest != nullptr
}
