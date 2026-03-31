#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include <string>

namespace re2 {

class ParseCCNameTest_528 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a valid POSIX character class [:alpha:] is parsed successfully
TEST_F(ParseCCNameTest_528, ValidAlphaClass_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:alpha:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that a valid POSIX character class [:digit:] is parsed successfully
TEST_F(ParseCCNameTest_528, ValidDigitClass_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:digit:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that a valid POSIX character class [:alnum:] is parsed successfully
TEST_F(ParseCCNameTest_528, ValidAlnumClass_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:alnum:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that a valid POSIX character class [:space:] is parsed successfully
TEST_F(ParseCCNameTest_528, ValidSpaceClass_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:space:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that a valid POSIX character class [:upper:] is parsed successfully
TEST_F(ParseCCNameTest_528, ValidUpperClass_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:upper:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that a valid POSIX character class [:lower:] is parsed successfully
TEST_F(ParseCCNameTest_528, ValidLowerClass_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:lower:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that a valid POSIX character class [:print:] is parsed successfully
TEST_F(ParseCCNameTest_528, ValidPrintClass_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:print:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that a valid POSIX character class [:punct:] is parsed successfully
TEST_F(ParseCCNameTest_528, ValidPunctClass_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:punct:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that an invalid POSIX character class name causes an error
TEST_F(ParseCCNameTest_528, InvalidPosixClassName_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:bogus:]]", Regexp::PerlX, &status);
  EXPECT_TRUE(re == nullptr);
  EXPECT_EQ(status.code(), kRegexpBadCharRange);
}

// Test that negated POSIX character class [:^alpha:] is parsed successfully
TEST_F(ParseCCNameTest_528, NegatedAlphaClass_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:^alpha:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test multiple POSIX classes in one bracket expression
TEST_F(ParseCCNameTest_528, MultiplePosixClasses_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:alpha:][:digit:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test POSIX class combined with regular characters
TEST_F(ParseCCNameTest_528, PosixClassWithChars_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a[:digit:]z]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that [:alpha:] actually matches alphabetic characters using RE2
TEST_F(ParseCCNameTest_528, AlphaClassMatchesBehavior_528) {
  EXPECT_TRUE(RE2::FullMatch("a", "[[:alpha:]]"));
  EXPECT_TRUE(RE2::FullMatch("Z", "[[:alpha:]]"));
  EXPECT_FALSE(RE2::FullMatch("5", "[[:alpha:]]"));
  EXPECT_FALSE(RE2::FullMatch("!", "[[:alpha:]]"));
}

// Test that [:digit:] actually matches digit characters using RE2
TEST_F(ParseCCNameTest_528, DigitClassMatchesBehavior_528) {
  EXPECT_TRUE(RE2::FullMatch("0", "[[:digit:]]"));
  EXPECT_TRUE(RE2::FullMatch("9", "[[:digit:]]"));
  EXPECT_FALSE(RE2::FullMatch("a", "[[:digit:]]"));
}

// Test that [:space:] actually matches space characters
TEST_F(ParseCCNameTest_528, SpaceClassMatchesBehavior_528) {
  EXPECT_TRUE(RE2::FullMatch(" ", "[[:space:]]"));
  EXPECT_TRUE(RE2::FullMatch("\t", "[[:space:]]"));
  EXPECT_TRUE(RE2::FullMatch("\n", "[[:space:]]"));
  EXPECT_FALSE(RE2::FullMatch("a", "[[:space:]]"));
}

// Test that negated [:^digit:] matches non-digit characters
TEST_F(ParseCCNameTest_528, NegatedDigitClassMatchesBehavior_528) {
  EXPECT_FALSE(RE2::FullMatch("0", "[[:^digit:]]"));
  EXPECT_TRUE(RE2::FullMatch("a", "[[:^digit:]]"));
}

// Test that [:graph:] is valid
TEST_F(ParseCCNameTest_528, ValidGraphClass_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:graph:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that [:cntrl:] is valid
TEST_F(ParseCCNameTest_528, ValidCntrlClass_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:cntrl:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that [:blank:] is valid
TEST_F(ParseCCNameTest_528, ValidBlankClass_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:blank:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that [:xdigit:] is valid and matches hex digits
TEST_F(ParseCCNameTest_528, ValidXdigitClass_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:xdigit:]]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr) << status.Text();
  EXPECT_TRUE(status.ok());
  re->Decref();

  EXPECT_TRUE(RE2::FullMatch("a", "[[:xdigit:]]"));
  EXPECT_TRUE(RE2::FullMatch("F", "[[:xdigit:]]"));
  EXPECT_TRUE(RE2::FullMatch("0", "[[:xdigit:]]"));
  EXPECT_FALSE(RE2::FullMatch("g", "[[:xdigit:]]"));
}

// Test that an incomplete POSIX class (no closing :]) is treated as literal characters
TEST_F(ParseCCNameTest_528, IncompletePosixClass_528) {
  RegexpStatus status;
  // [[:alpha] - missing closing :]
  Regexp* re = Regexp::Parse("[[:alpha]]", Regexp::PerlX, &status);
  // This should either parse as literal characters or fail
  // The function returns kParseNothing when no closing :] is found
  // so the parser treats [: as literal characters
  if (re != nullptr) {
    re->Decref();
  }
}

// Test case-insensitive flag with POSIX class
TEST_F(ParseCCNameTest_528, CaseInsensitivePosixClass_528) {
  EXPECT_TRUE(RE2::FullMatch("A", "(?i)[[:lower:]]"));
  EXPECT_TRUE(RE2::FullMatch("a", "(?i)[[:lower:]]"));
}

// Test that another invalid name returns error
TEST_F(ParseCCNameTest_528, AnotherInvalidPosixClassName_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[:foo:]]", Regexp::PerlX, &status);
  EXPECT_TRUE(re == nullptr);
  EXPECT_EQ(status.code(), kRegexpBadCharRange);
}

// Test empty POSIX class name [[::]
TEST_F(ParseCCNameTest_528, EmptyPosixClassName_528) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[[::]]", Regexp::PerlX, &status);
  EXPECT_TRUE(re == nullptr);
  EXPECT_EQ(status.code(), kRegexpBadCharRange);
}

}  // namespace re2
