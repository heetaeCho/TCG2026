// File: parse_ccname_test_528.cc
#include <gtest/gtest.h>
#include "absl/strings/string_view.h"

// Include the implementation unit to access the internal-static function under test.
#include "re2/parse.cc"  // NOLINT(build/include_what_you_use)

using namespace re2;

namespace {

// Helper: a do-nothing parse_flags value.
static constexpr Regexp::ParseFlags kNoFlags =
    static_cast<Regexp::ParseFlags>(0);

// --- Tests ---

// Normal success path: valid POSIX character class.
// Verifies: returns kParseOk and consumes exactly the matched prefix.
TEST(ParseCCNameTest_528, OkOnValidGroup_528) {
  // Arrange
  absl::string_view s = "[:alnum:]XYZ";
  CharClassBuilder cc;
  RegexpStatus status;

  // Act
  ParseStatus ps = ParseCCName(&s, kNoFlags, &cc, &status);

  // Assert
  EXPECT_EQ(ps, kParseOk);
  // Should consume exactly "[:alnum:]" and leave the rest.
  EXPECT_EQ(s, "XYZ");
  // No error should be recorded on success.
  EXPECT_TRUE(status.ok());
}

// Error path: unknown/unsupported POSIX class name.
// Verifies: returns kParseError, does NOT consume input, and sets status code
// and error_arg to the full class token (including brackets and colons).
TEST(ParseCCNameTest_528, ErrorOnUnknownGroup_528) {
  // Arrange
  absl::string_view s = "[:notag:]rest";
  const absl::string_view original = s;
  CharClassBuilder cc;
  RegexpStatus status;

  // Act
  ParseStatus ps = ParseCCName(&s, kNoFlags, &cc, &status);

  // Assert
  EXPECT_EQ(ps, kParseError);
  // Input should remain unchanged on error.
  EXPECT_EQ(s, original);
  // Status should reflect a bad char range with the offending token.
  EXPECT_EQ(status.code(), kRegexpBadCharRange);
  EXPECT_EQ(status.error_arg(), "[:notag:]");
}

// Boundary: too short / missing required prefix "[:".
// Verifies: returns kParseNothing and does not modify input or status.
TEST(ParseCCNameTest_528, NothingWhenNoPrefix_528) {
  // Arrange
  absl::string_view s = "abc";
  const absl::string_view original = s;
  CharClassBuilder cc;
  RegexpStatus status;

  // Act
  ParseStatus ps = ParseCCName(&s, kNoFlags, &cc, &status);

  // Assert
  EXPECT_EQ(ps, kParseNothing);
  EXPECT_EQ(s, original);     // Unchanged
  EXPECT_TRUE(status.ok());   // No error set
}

// Boundary: starts with "[:" but lacks closing ":]".
// Verifies: returns kParseNothing and does not modify input or status.
TEST(ParseCCNameTest_528, NothingWhenNoClosing_528) {
  // Arrange
  absl::string_view s = "[:alpha";
  const absl::string_view original = s;
  CharClassBuilder cc;
  RegexpStatus status;

  // Act
  ParseStatus ps = ParseCCName(&s, kNoFlags, &cc, &status);

  // Assert
  EXPECT_EQ(ps, kParseNothing);
  EXPECT_EQ(s, original);     // Unchanged
  EXPECT_TRUE(status.ok());   // No error set
}

}  // namespace
