// File: parse_string_view_test_268.cc

#include <cstddef>
#include <string>

#include "gtest/gtest.h"
#include "absl/strings/string_view.h"

// The function under test lives in this namespace per the snippet.
namespace re2 { namespace re2_internal {
  // Declaration only; definition is in re2/re2.cc (provided in the codebase).
  bool Parse(const char* str, size_t n, absl::string_view* dest);
}}

// Test suite for the Parse specialization that writes to absl::string_view.
class ParseStringViewTest_268 : public ::testing::Test {};

// [Normal] Non-null dest should be assigned a view of exactly n bytes; returns true.
TEST_F(ParseStringViewTest_268, SetsDestWhenNonNull_268) {
  const char* src = "hello world";
  absl::string_view out;  // uninitialized view
  bool ok = re2::re2_internal::Parse(src, 5, &out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out.size(), 5u);
  EXPECT_EQ(out, "hello");  // verifies content and length
}

// [Boundary] If dest is NULL, function should be a no-op and still return true.
TEST_F(ParseStringViewTest_268, ReturnsTrueWhenDestNull_268) {
  const char* src = "anything";
  // Expect no crash and true return even when dest is nullptr.
  bool ok = re2::re2_internal::Parse(src, 3, /*dest=*/nullptr);
  EXPECT_TRUE(ok);
}

// [Boundary] Zero-length parse should yield an empty view; returns true.
TEST_F(ParseStringViewTest_268, HandlesZeroLength_268) {
  const char* src = "nonempty";
  absl::string_view out("preset");  // set to non-empty to ensure it becomes empty
  bool ok = re2::re2_internal::Parse(src, 0, &out);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(out.empty());
  EXPECT_EQ(out.size(), 0u);
}

// [Boundary] Should support embedded NUL bytes since length n is explicit.
TEST_F(ParseStringViewTest_268, SupportsEmbeddedNul_268) {
  // Construct a buffer with an embedded '\0'
  std::string buffer = std::string("ab", 2) + std::string("\0", 1) + "cd"; // "ab\0cd"
  ASSERT_EQ(buffer.size(), 5u);

  absl::string_view out;
  bool ok = re2::re2_internal::Parse(buffer.data(), buffer.size(), &out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out.size(), buffer.size());
  // Verify bytes around the NUL; direct equality with string_view that includes NUL.
  absl::string_view expected(buffer.data(), buffer.size());
  EXPECT_EQ(out, expected);
  // Spot-check positions to ensure NUL is preserved.
  EXPECT_EQ(out[0], 'a');
  EXPECT_EQ(out[1], 'b');
  EXPECT_EQ(out[2], '\0');
  EXPECT_EQ(out[3], 'c');
  EXPECT_EQ(out[4], 'd');
}

// [Behavior] Verify it does not stop at C-string terminator and uses exact n bytes.
TEST_F(ParseStringViewTest_268, UsesExactLengthNotCStrTerminator_268) {
  // "xyz\0uvw" with explicit length should include bytes after the NUL.
  std::string buffer = std::string("xyz", 3) + std::string("\0", 1) + "uvw"; // 7 bytes
  ASSERT_EQ(buffer.size(), 7u);

  absl::string_view out;
  bool ok = re2::re2_internal::Parse(buffer.c_str(), 7, &out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out.size(), 7u);
  absl::string_view expected(buffer.data(), buffer.size());
  EXPECT_EQ(out, expected);
}
