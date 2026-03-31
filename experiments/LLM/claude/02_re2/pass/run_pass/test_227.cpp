#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2 {

class ToStringTest_227 : public ::testing::Test {
 protected:
};

// Test that a simple literal pattern round-trips through ToString
TEST_F(ToStringTest_227, SimpleLiteral_227) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  std::string pattern = re.pattern();
  EXPECT_EQ(pattern, "hello");
}

// Test that special metacharacters are properly escaped in ToString
TEST_F(ToStringTest_227, MetacharactersEscaped_227) {
  // Parentheses
  RE2 re1("\\(\\)");
  ASSERT_TRUE(re1.ok());

  // Brackets
  RE2 re2("\\[\\]");
  ASSERT_TRUE(re2.ok());

  // Dot
  RE2 re3("\\.");
  ASSERT_TRUE(re3.ok());
}

// Test alternation
TEST_F(ToStringTest_227, Alternation_227) {
  RE2 re("a|b");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "a|b");
}

// Test character class
TEST_F(ToStringTest_227, CharacterClass_227) {
  RE2 re("[abc]");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "[abc]");
}

// Test quantifiers
TEST_F(ToStringTest_227, Quantifiers_227) {
  RE2 re1("a*");
  ASSERT_TRUE(re1.ok());
  EXPECT_EQ(re1.pattern(), "a*");

  RE2 re2("a+");
  ASSERT_TRUE(re2.ok());
  EXPECT_EQ(re2.pattern(), "a+");

  RE2 re3("a?");
  ASSERT_TRUE(re3.ok());
  EXPECT_EQ(re3.pattern(), "a?");
}

// Test Regexp::ToString round-trip for various patterns
TEST_F(ToStringTest_227, RegexpToStringSimple_227) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "abc");
  re->Decref();
}

TEST_F(ToStringTest_227, RegexpToStringDot_227) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a.b", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a.b");
  re->Decref();
}

TEST_F(ToStringTest_227, RegexpToStringRepeat_227) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "a{3,5}");
  re->Decref();
}

TEST_F(ToStringTest_227, RegexpToStringAnchors_227) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "^abc$");
  re->Decref();
}

TEST_F(ToStringTest_227, RegexpToStringEscapedSpecialChars_227) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\(\\)\\{\\}\\[\\]\\*\\+\\?\\|\\^\\$\\\\", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->ToString();
  // The special chars should be escaped back
  re->Decref();
}

TEST_F(ToStringTest_227, RegexpToStringFoldCase_227) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->ToString();
  // Should contain case-insensitive representation
  re->Decref();
}

TEST_F(ToStringTest_227, RegexpToStringCapture_227) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "(abc)");
  re->Decref();
}

TEST_F(ToStringTest_227, EmptyPattern_227) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "");
  re->Decref();
}

TEST_F(ToStringTest_227, RegexpToStringCharClassRange_227) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "[a-z]");
  re->Decref();
}

TEST_F(ToStringTest_227, RegexpToStringNegatedCharClass_227) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[^a-z]", Regexp::NoParseFlags, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "[^a-z]");
  re->Decref();
}

TEST_F(ToStringTest_227, RegexpToStringNonCapture_227) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->ToString();
  EXPECT_EQ(s, "(?:abc)");
  re->Decref();
}

TEST_F(ToStringTest_227, RegexpToStringBackslashSpecials_227) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d\\w\\s", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr);
  std::string s = re->ToString();
  re->Decref();
}

}  // namespace re2
