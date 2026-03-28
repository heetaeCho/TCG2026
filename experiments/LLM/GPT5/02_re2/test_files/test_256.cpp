// File: re2_replace_test_256.cc
#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"  // Adjust include path if needed

using re2::RE2;

class RE2ReplaceTest_256 : public ::testing::Test {};

// Replaces only the first occurrence when multiple matches exist.
TEST_F(RE2ReplaceTest_256, SimpleReplaceFirstMatch_256) {
  RE2 pattern("\\d+");            // one or more digits
  RE2 caller(".*");               // any pattern; used only to invoke member Replace
  std::string s = "hello 123 world 456";
  const std::string original = s;

  bool ok = caller.Replace(&s, pattern, "X");

  EXPECT_TRUE(ok);
  EXPECT_EQ("hello X world 456", s);
  // Ensure only the first match is replaced (not global).
  EXPECT_NE(std::string::npos, original.find("456"));
  EXPECT_NE(std::string::npos, s.find("456"));
}

// Uses a capturing group in the rewrite and verifies substitution.
TEST_F(RE2ReplaceTest_256, ReplaceWithCapturingGroup_256) {
  RE2 pattern("(\\d+)");
  RE2 caller(".*");
  std::string s = "abc 42 def";

  bool ok = caller.Replace(&s, pattern, "<\\1>");

  EXPECT_TRUE(ok);
  EXPECT_EQ("abc <42> def", s);
}

// Pattern anchored to start should match and replace at the start.
TEST_F(RE2ReplaceTest_256, ReplaceAtStartWithAnchorPattern_256) {
  RE2 pattern("^hello");
  RE2 caller(".*");
  std::string s = "hello world";

  bool ok = caller.Replace(&s, pattern, "hi");

  EXPECT_TRUE(ok);
  EXPECT_EQ("hi world", s);
}

// Empty rewrite should delete the matched portion.
TEST_F(RE2ReplaceTest_256, ReplaceDeletesWhenEmptyRewrite_256) {
  RE2 pattern("\\s+");
  RE2 caller(".*");
  std::string s = "A   B";

  bool ok = caller.Replace(&s, pattern, "");

  EXPECT_TRUE(ok);
  // Only the first whitespace run is removed.
  EXPECT_EQ("AB", s) << "First whitespace run removed; 'B' should abut 'A'";
}

// No match -> function returns false and the string remains unchanged.
TEST_F(RE2ReplaceTest_256, NoMatchReturnsFalseAndUnchanged_256) {
  RE2 pattern("zzz");
  RE2 caller(".*");
  std::string s = "abc 123 def";
  const std::string before = s;

  bool ok = caller.Replace(&s, pattern, "X");

  EXPECT_FALSE(ok);
  EXPECT_EQ(before, s);
}

// Rewrite references a capture index greater than available groups -> returns false, string unchanged.
// (This exercises the check using MaxSubmatch(rewrite) vs NumberOfCapturingGroups().)
TEST_F(RE2ReplaceTest_256, RewriteReferencesTooManyGroups_ReturnsFalseAndUnchanged_256) {
  RE2 pattern("(\\w+)");  // Only 1 capturing group
  RE2 caller(".*");
  std::string s = "token";
  const std::string before = s;

  // Rewrite requests group \2, but only one group exists.
  bool ok = caller.Replace(&s, pattern, "\\2");

  EXPECT_FALSE(ok);
  EXPECT_EQ(before, s);
}

// Multiple capturing groups; verify complex rewrite ordering works.
TEST_F(RE2ReplaceTest_256, ReplaceWithMultipleGroups_256) {
  RE2 pattern("(\\w+)-(\\d+)");
  RE2 caller(".*");
  std::string s = "item-77 tail";

  bool ok = caller.Replace(&s, pattern, "\\2:<\\1>");

  EXPECT_TRUE(ok);
  EXPECT_EQ("77:<item> tail", s);
}

// Ensure only the matched span is replaced; surrounding text remains intact.
TEST_F(RE2ReplaceTest_256, ReplacesOnlyMatchedSpan_256) {
  RE2 pattern("world");
  RE2 caller(".*");
  std::string s = "hello world!";
  const std::string prefix = "hello ";
  const std::string suffix = "!";

  bool ok = caller.Replace(&s, pattern, "earth");

  EXPECT_TRUE(ok);
  EXPECT_EQ(prefix + "earth" + suffix, s);
}
