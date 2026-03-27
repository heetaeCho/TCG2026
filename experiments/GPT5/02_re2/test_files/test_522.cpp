// File: lookup_posix_group_test_522.cc
#include <gtest/gtest.h>

// Bring the internal static into this translation unit by including the .cc.
// This allows calling the function without re-implementing logic.
#include "re2/parse.cc"  // NOLINT(build/include_what_you_use)

namespace {

class LookupPosixGroupTest_522 : public ::testing::Test {};

TEST_F(LookupPosixGroupTest_522, KnownStandardGroupsReturnNonNull_522) {
  // A representative set of standard POSIX class names commonly supported by RE2.
  // We only assert that something is found (non-null), without assuming details.
  const char* kNames[] = {
      "alnum", "alpha", "ascii", "blank", "cntrl", "digit",
      "graph", "lower", "print", "punct", "space", "upper",
      "word", "xdigit",
  };
  for (const char* name : kNames) {
    const re2::UGroup* g = re2::LookupPosixGroup(name);
    EXPECT_NE(g, nullptr) << "Expected POSIX group for name: " << name;
  }
}

TEST_F(LookupPosixGroupTest_522, UnknownGroupReturnsNull_522) {
  const char* kUnknowns[] = {"notagroup", "hello_world", "digitals", "wdord", "x_digit"};
  for (const char* name : kUnknowns) {
    const re2::UGroup* g = re2::LookupPosixGroup(name);
    EXPECT_EQ(g, nullptr) << "Unexpectedly found group for unknown name: " << name;
  }
}

TEST_F(LookupPosixGroupTest_522, EmptyStringReturnsNull_522) {
  const re2::UGroup* g = re2::LookupPosixGroup("");
  EXPECT_EQ(g, nullptr);
}

TEST_F(LookupPosixGroupTest_522, SurroundingBracketsNotationIsNotAName_522) {
  // The function takes just the name (e.g., "digit"), not the full bracket class "[:digit:]".
  const re2::UGroup* g = re2::LookupPosixGroup("[:digit:]");
  EXPECT_EQ(g, nullptr);
}

TEST_F(LookupPosixGroupTest_522, LeadingOrTrailingWhitespaceDoesNotMatch_522) {
  // Treat whitespace differences as a separate, observable input.
  // We assert strict name matching (no trimming) by expecting nullptr.
  const re2::UGroup* g1 = re2::LookupPosixGroup(" digit");
  const re2::UGroup* g2 = re2::LookupPosixGroup("digit ");
  const re2::UGroup* g3 = re2::LookupPosixGroup("  digit  ");
  EXPECT_EQ(g1, nullptr);
  EXPECT_EQ(g2, nullptr);
  EXPECT_EQ(g3, nullptr);
}

TEST_F(LookupPosixGroupTest_522, VeryLongNameDoesNotCrashAndReturnsNull_522) {
  std::string long_name(10000, 'a');  // Boundary-ish input
  const re2::UGroup* g = re2::LookupPosixGroup(long_name);
  EXPECT_EQ(g, nullptr);
}

}  // namespace
