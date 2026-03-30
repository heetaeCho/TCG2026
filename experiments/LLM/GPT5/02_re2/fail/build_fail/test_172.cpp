// File: ./TestProjects/re2/tests/get_info_test_172.cc

#include <gtest/gtest.h>
#include <string>

// Pull in the interface under test.
// (If you have a proper header, include that instead.)
#include "../app/_re2.cc"

using re2_app::GetInfo;
using re2_app::Info;

class Re2AppGetInfoTest_172 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(Re2AppGetInfoTest_172, ParsesSimplePatternAndFindsRequiredPrefix_172) {
  const std::string pattern = "abc.*";
  Info info = GetInfo(pattern);

  // No parse/compile error
  EXPECT_TRUE(info.error.empty());
  EXPECT_EQ(info.pattern, pattern);

  // RequiredPrefix should detect the obvious literal prefix "abc".
  EXPECT_EQ(info.prefix, "abc");
  EXPECT_FALSE(info.prefix_foldcase);

  // accel prefix may or may not be provided; if provided, it should match the same literal.
  if (!info.accel_prefix.empty()) {
    EXPECT_EQ(info.accel_prefix, "abc");
    EXPECT_FALSE(info.accel_prefix_foldcase);
  }

  // No captures in the pattern
  EXPECT_EQ(info.num_captures, 0);

  // Successful compilation should yield non-empty artifacts
  EXPECT_FALSE(info.bytecode.empty());
  EXPECT_FALSE(info.bytemap.empty());
}

TEST_F(Re2AppGetInfoTest_172, CountsCapturingGroups_172) {
  const std::string pattern = "^(foo)(bar)?baz$";
  Info info = GetInfo(pattern);

  EXPECT_TRUE(info.error.empty());
  EXPECT_EQ(info.pattern, pattern);

  // Two capturing groups: (foo) and (bar)?
  EXPECT_EQ(info.num_captures, 2);

  EXPECT_FALSE(info.bytecode.empty());
  EXPECT_FALSE(info.bytemap.empty());
}

// --- Boundary conditions ---

TEST_F(Re2AppGetInfoTest_172, EmptyPatternCompiles_NoRequiredPrefix_172) {
  const std::string pattern = "";
  Info info = GetInfo(pattern);

  // Empty pattern is valid in RE2 and matches empty string.
  EXPECT_TRUE(info.error.empty());
  EXPECT_EQ(info.pattern, pattern);

  // No required literal prefix expected.
  EXPECT_TRUE(info.prefix.empty());

  // Zero captures
  EXPECT_EQ(info.num_captures, 0);

  // Compiled artifacts should exist
  EXPECT_FALSE(info.bytecode.empty());
  EXPECT_FALSE(info.bytemap.empty());
}

TEST_F(Re2AppGetInfoTest_172, CaseInsensitivePrefixSetsFoldcase_172) {
  const std::string pattern = "(?i)abc.*";
  Info info = GetInfo(pattern);

  EXPECT_TRUE(info.error.empty());
  EXPECT_EQ(info.pattern, pattern);

  // The required prefix should be "abc" with foldcase=true due to (?i).
  EXPECT_EQ(info.prefix, "abc");
  EXPECT_TRUE(info.prefix_foldcase);

  // If accelerator prefix is provided, its foldcase should also be true.
  if (!info.accel_prefix.empty()) {
    EXPECT_EQ(info.accel_prefix, "abc");
    EXPECT_TRUE(info.accel_prefix_foldcase);
  }

  EXPECT_FALSE(info.bytecode.empty());
  EXPECT_FALSE(info.bytemap.empty());
}

// --- Exceptional / error cases (observable through interface) ---

TEST_F(Re2AppGetInfoTest_172, InvalidPatternReportsParseError_172) {
  const std::string pattern = "(";  // Unbalanced parenthesis -> parse failure
  Info info = GetInfo(pattern);

  // On parse error, the function returns early with an error message.
  EXPECT_EQ(info.pattern, pattern);
  ASSERT_FALSE(info.error.empty());
  // The function prefixes errors with this exact text.
  EXPECT_NE(info.error.find("failed to parse pattern: "), std::string::npos);

  // Do NOT assert on other fields; they are not guaranteed to be set on error.
}

// --- Additional observable properties (without depending on internals) ---

TEST_F(Re2AppGetInfoTest_172, BytecodeAndBytemapAreNonEmptyOnSuccess_172) {
  const std::string pattern = "hello(world)?";
  Info info = GetInfo(pattern);

  EXPECT_TRUE(info.error.empty());
  EXPECT_EQ(info.pattern, pattern);

  // Sanity: one optional capture
  EXPECT_EQ(info.num_captures, 1);

  // Compiled program surfaces these dumps; content is opaque to the test.
  EXPECT_FALSE(info.bytecode.empty());
  EXPECT_FALSE(info.bytemap.empty());
}
