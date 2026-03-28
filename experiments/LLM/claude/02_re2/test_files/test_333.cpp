#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Test basic Regexp creation and reference counting through the public interface
TEST(RegexpTest_333, ParseSimpleLiteral_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, ParseEmptyString_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, ParseCharacterClass_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, ParseInvalidRegexp_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST(RegexpTest_333, ParseComplexPattern_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+|b*)?c{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, IncrefDecref_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  // Incref should return the same pointer
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  
  // Two decrefs needed now
  re->Decref();
  re2->Decref();
}

TEST(RegexpTest_333, MultipleIncrefDecref_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("xyz", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  // Multiple increfs
  re->Incref();
  re->Incref();
  re->Incref();
  
  // Corresponding decrefs
  re->Decref();
  re->Decref();
  re->Decref();
  re->Decref(); // The original reference
}

TEST(RegexpTest_333, ToString_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  
  re->Decref();
}

TEST(RegexpTest_333, ParseDot_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, ParseStar_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, ParsePlus_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, ParseQuestion_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, ParseAlternation_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, ParseGroup_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, ParseNestedGroups_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b(c)))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, ParseUnmatchedParen_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST(RegexpTest_333, ParseRepetition_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, ParseEscape_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, ParseAnchor_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, Op_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  // Op should return a valid RegexpOp
  RegexpOp op = re->op();
  // We can at least verify it's in a valid range
  EXPECT_GE(static_cast<int>(op), 0);
  
  re->Decref();
}

TEST(RegexpTest_333, ParseFlags_333) {
  RegexpStatus status;
  // Test with POSIX flags
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, ParseNamedCapture_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpTest_333, NumCaptures_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  int ncap = re->NumCaptures();
  EXPECT_EQ(ncap, 3);
  
  re->Decref();
}

TEST(RegexpTest_333, NumCapturesNone_333) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  
  int ncap = re->NumCaptures();
  EXPECT_EQ(ncap, 0);
  
  re->Decref();
}

}  // namespace re2
