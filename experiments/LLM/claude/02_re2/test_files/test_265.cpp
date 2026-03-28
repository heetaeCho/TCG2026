#include "gtest/gtest.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

class RE2RewriteTest_265 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Simple literal rewrite with no backslash substitutions
TEST_F(RE2RewriteTest_265, SimpleLiteralRewrite_265) {
  RE2 re("(\\w+)");
  std::string out;
  absl::string_view vec[] = {"hello"};
  bool result = re.Rewrite(&out, "world", vec, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "world");
}

// Test: Rewrite with group substitution \0
TEST_F(RE2RewriteTest_265, SubstitutionGroup0_265) {
  RE2 re("(\\w+)");
  std::string out;
  absl::string_view vec[] = {"fullmatch", "group1"};
  bool result = re.Rewrite(&out, "\\0", vec, 2);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "fullmatch");
}

// Test: Rewrite with group substitution \1
TEST_F(RE2RewriteTest_265, SubstitutionGroup1_265) {
  RE2 re("(\\w+)");
  std::string out;
  absl::string_view vec[] = {"fullmatch", "group1"};
  bool result = re.Rewrite(&out, "\\1", vec, 2);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "group1");
}

// Test: Rewrite with multiple group substitutions
TEST_F(RE2RewriteTest_265, MultipleSubstitutions_265) {
  RE2 re("(\\w+)-(\\w+)");
  std::string out;
  absl::string_view vec[] = {"hello-world", "hello", "world"};
  bool result = re.Rewrite(&out, "\\2-\\1", vec, 3);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "world-hello");
}

// Test: Rewrite with escaped backslash \\
TEST_F(RE2RewriteTest_265, EscapedBackslash_265) {
  RE2 re("(\\w+)");
  std::string out;
  absl::string_view vec[] = {"hello"};
  bool result = re.Rewrite(&out, "a\\\\b", vec, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "a\\b");
}

// Test: Rewrite with invalid group number (out of range)
TEST_F(RE2RewriteTest_265, InvalidGroupNumber_265) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("(\\w+)", opts);
  std::string out;
  absl::string_view vec[] = {"hello"};
  bool result = re.Rewrite(&out, "\\2", vec, 1);
  EXPECT_FALSE(result);
}

// Test: Rewrite with invalid escape character
TEST_F(RE2RewriteTest_265, InvalidEscapeCharacter_265) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("(\\w+)", opts);
  std::string out;
  absl::string_view vec[] = {"hello"};
  bool result = re.Rewrite(&out, "\\a", vec, 1);
  EXPECT_FALSE(result);
}

// Test: Empty rewrite string
TEST_F(RE2RewriteTest_265, EmptyRewriteString_265) {
  RE2 re("(\\w+)");
  std::string out;
  absl::string_view vec[] = {"hello"};
  bool result = re.Rewrite(&out, "", vec, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "");
}

// Test: Empty vec (veclen = 0)
TEST_F(RE2RewriteTest_265, EmptyVec_265) {
  RE2 re(".*");
  std::string out;
  bool result = re.Rewrite(&out, "literal", nullptr, 0);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "literal");
}

// Test: Empty vec with group reference should fail
TEST_F(RE2RewriteTest_265, EmptyVecWithGroupRef_265) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re(".*", opts);
  std::string out;
  bool result = re.Rewrite(&out, "\\0", nullptr, 0);
  EXPECT_FALSE(result);
}

// Test: Rewrite with mixed literal and substitution
TEST_F(RE2RewriteTest_265, MixedLiteralAndSubstitution_265) {
  RE2 re("(\\w+)");
  std::string out;
  absl::string_view vec[] = {"fullmatch", "group1"};
  bool result = re.Rewrite(&out, "prefix_\\1_suffix", vec, 2);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "prefix_group1_suffix");
}

// Test: Rewrite with empty group match
TEST_F(RE2RewriteTest_265, EmptyGroupMatch_265) {
  RE2 re("(\\w*)");
  std::string out;
  absl::string_view vec[] = {"", ""};
  bool result = re.Rewrite(&out, "result=\\1", vec, 2);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "result=");
}

// Test: Rewrite with backslash at end of string (no following char)
TEST_F(RE2RewriteTest_265, BackslashAtEnd_265) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("(\\w+)", opts);
  std::string out;
  absl::string_view vec[] = {"hello"};
  // Trailing backslash with no following character: c = -1, not a digit or '\\'
  bool result = re.Rewrite(&out, "test\\", vec, 1);
  EXPECT_FALSE(result);
}

// Test: Substitution with group 9
TEST_F(RE2RewriteTest_265, SubstitutionGroup9_265) {
  RE2 re("(.)(.)(.)(.)(.)(.)(.)(.)(.)(.)");
  std::string out;
  absl::string_view vec[] = {"0123456789", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  bool result = re.Rewrite(&out, "\\9", vec, 11);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "9");
}

// Test: Multiple escaped backslashes
TEST_F(RE2RewriteTest_265, MultipleEscapedBackslashes_265) {
  RE2 re("(.+)");
  std::string out;
  absl::string_view vec[] = {"test"};
  bool result = re.Rewrite(&out, "\\\\\\\\", vec, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "\\\\");
}

// Test: Rewrite appends to existing out string content
TEST_F(RE2RewriteTest_265, AppendsToExistingOutput_265) {
  RE2 re("(\\w+)");
  std::string out = "existing_";
  absl::string_view vec[] = {"hello", "world"};
  bool result = re.Rewrite(&out, "\\1", vec, 2);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "existing_world");
}

// Test: Rewrite with only a substitution
TEST_F(RE2RewriteTest_265, OnlySubstitution_265) {
  RE2 re("(.+)");
  std::string out;
  absl::string_view vec[] = {"entire_match"};
  bool result = re.Rewrite(&out, "\\0", vec, 1);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "entire_match");
}

// Test: Group reference exactly at boundary (veclen equals group number)
TEST_F(RE2RewriteTest_265, GroupRefAtBoundary_265) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("(.+)", opts);
  std::string out;
  absl::string_view vec[] = {"match", "group1"};
  // \2 references index 2, but veclen is 2, so index 2 is out of range
  bool result = re.Rewrite(&out, "\\2", vec, 2);
  EXPECT_FALSE(result);
}

// Test: Group reference just within boundary
TEST_F(RE2RewriteTest_265, GroupRefWithinBoundary_265) {
  RE2 re("(.+)");
  std::string out;
  absl::string_view vec[] = {"match", "group1"};
  // \1 references index 1, veclen is 2, so it's valid
  bool result = re.Rewrite(&out, "\\1", vec, 2);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "group1");
}

// Test: Using the Replace static method that internally uses Rewrite
TEST_F(RE2RewriteTest_265, ReplaceUsesRewrite_265) {
  std::string str = "hello world";
  bool result = RE2::Replace(&str, RE2("(\\w+)"), "bye");
  EXPECT_TRUE(result);
  EXPECT_EQ(str, "bye world");
}

// Test: Using Extract which internally uses Rewrite
TEST_F(RE2RewriteTest_265, ExtractUsesRewrite_265) {
  std::string out;
  bool result = RE2::Extract("boris@kremlin.ru", RE2("(.*)@([^.]*)"), "\\2!\\1", &out);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "kremlin!boris");
}

// Test: Rewrite with log_errors enabled on invalid substitution
TEST_F(RE2RewriteTest_265, InvalidSubstitutionWithLogErrors_265) {
  RE2 re("(\\w+)");  // log_errors defaults to true
  std::string out;
  absl::string_view vec[] = {"hello"};
  // \5 is out of range for veclen=1
  bool result = re.Rewrite(&out, "\\5", vec, 1);
  EXPECT_FALSE(result);
}

// Test: Rewrite with log_errors disabled on invalid escape
TEST_F(RE2RewriteTest_265, InvalidEscapeWithLogErrorsDisabled_265) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("test", opts);
  std::string out;
  absl::string_view vec[] = {"test"};
  bool result = re.Rewrite(&out, "\\z", vec, 1);
  EXPECT_FALSE(result);
}

// Test: Consecutive substitutions without separator
TEST_F(RE2RewriteTest_265, ConsecutiveSubstitutions_265) {
  RE2 re("(.)(.)(.)");
  std::string out;
  absl::string_view vec[] = {"abc", "a", "b", "c"};
  bool result = re.Rewrite(&out, "\\3\\2\\1", vec, 4);
  EXPECT_TRUE(result);
  EXPECT_EQ(out, "cba");
}

// Test: GlobalReplace with rewrite pattern
TEST_F(RE2RewriteTest_265, GlobalReplaceWithRewrite_265) {
  std::string str = "aaa bbb ccc";
  int count = RE2::GlobalReplace(&str, RE2("(\\w+)"), "(\\1)");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "(aaa) (bbb) (ccc)");
}

}  // namespace re2
