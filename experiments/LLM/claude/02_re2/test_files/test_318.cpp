#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include "util/logging.h"

namespace re2 {

// Test that basic compilation through the public RE2 interface works
TEST(CompilerTest_318, BasicCompilation_318) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_318, SimpleAlternation_318) {
  RE2 re("a|b");
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_318, SimpleRepetition_318) {
  RE2 re("a*");
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_318, SimplePlusRepetition_318) {
  RE2 re("a+");
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_318, SimpleOptional_318) {
  RE2 re("a?");
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_318, CharacterClass_318) {
  RE2 re("[a-z]");
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_318, NestedGroups_318) {
  RE2 re("(a(b(c)))");
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_318, EmptyPattern_318) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_318, DotMatchesCharacter_318) {
  RE2 re(".");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a", re));
}

TEST(CompilerTest_318, AnchoredMatch_318) {
  RE2 re("^hello$");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("hello world", re));
}

TEST(CompilerTest_318, ComplexPattern_318) {
  RE2 re("(\\d{1,3}\\.){3}\\d{1,3}");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("192.168.1.1", re));
}

TEST(CompilerTest_318, CountedRepetition_318) {
  RE2 re("a{3,5}");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("aaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaa", re));
  EXPECT_TRUE(RE2::FullMatch("aaaaa", re));
  EXPECT_FALSE(RE2::FullMatch("aa", re));
  EXPECT_FALSE(RE2::FullMatch("aaaaaa", re));
}

TEST(CompilerTest_318, InvalidPattern_318) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
}

TEST(CompilerTest_318, CompileWithMaxMem_318) {
  RE2::Options opts;
  opts.set_max_mem(1 << 10);  // Very small memory limit
  RE2 re("a", opts);
  EXPECT_TRUE(re.ok());
}

TEST(CompilerTest_318, LiteralString_318) {
  RE2 re("abcdef");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abcdef", re));
  EXPECT_FALSE(RE2::FullMatch("abcde", re));
}

TEST(CompilerTest_318, CaptureGroup_318) {
  RE2 re("(\\w+)@(\\w+)");
  EXPECT_TRUE(re.ok());
  std::string user, domain;
  EXPECT_TRUE(RE2::FullMatch("user@host", re, &user, &domain));
  EXPECT_EQ(user, "user");
  EXPECT_EQ(domain, "host");
}

TEST(CompilerTest_318, NonCapturingGroup_318) {
  RE2 re("(?:abc)+");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("abcabc", re));
}

}  // namespace re2
