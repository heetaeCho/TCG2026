#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class ParseStatePushCaretTest_490 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test PushCaret with OneLine flag set - should push kRegexpBeginText
TEST_F(ParseStatePushCaretTest_490, PushCaretWithOneLineFlag_490) {
  RegexpStatus status;
  absl::string_view pattern("^test");
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::OneLine | Regexp::PerlX);
  
  Regexp::ParseState ps(flags, pattern, &status);
  
  bool result = ps.PushCaret();
  EXPECT_TRUE(result);
  
  // Finish the regexp and check the result
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  // With OneLine, PushCaret should have pushed kRegexpBeginText
  EXPECT_EQ(re->op(), kRegexpBeginText);
  re->Decref();
}

// Test PushCaret without OneLine flag - should push kRegexpBeginLine
TEST_F(ParseStatePushCaretTest_490, PushCaretWithoutOneLineFlag_490) {
  RegexpStatus status;
  absl::string_view pattern("^test");
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX);  // No OneLine flag
  
  Regexp::ParseState ps(flags, pattern, &status);
  
  bool result = ps.PushCaret();
  EXPECT_TRUE(result);
  
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  // Without OneLine, PushCaret should have pushed kRegexpBeginLine
  EXPECT_EQ(re->op(), kRegexpBeginLine);
  re->Decref();
}

// Test PushCaret with NoParseFlags - should push kRegexpBeginLine
TEST_F(ParseStatePushCaretTest_490, PushCaretWithNoFlags_490) {
  RegexpStatus status;
  absl::string_view pattern("^");
  Regexp::ParseFlags flags = Regexp::NoParseFlags;
  
  Regexp::ParseState ps(flags, pattern, &status);
  
  bool result = ps.PushCaret();
  EXPECT_TRUE(result);
  
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpBeginLine);
  re->Decref();
}

// Test PushCaret with only OneLine flag
TEST_F(ParseStatePushCaretTest_490, PushCaretWithOnlyOneLineFlag_490) {
  RegexpStatus status;
  absl::string_view pattern("^");
  Regexp::ParseFlags flags = Regexp::OneLine;
  
  Regexp::ParseState ps(flags, pattern, &status);
  
  bool result = ps.PushCaret();
  EXPECT_TRUE(result);
  
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpBeginText);
  re->Decref();
}

// Test PushCaret with LikePerl flags (which includes OneLine)
TEST_F(ParseStatePushCaretTest_490, PushCaretWithLikePerlFlags_490) {
  RegexpStatus status;
  absl::string_view pattern("^test");
  Regexp::ParseFlags flags = Regexp::LikePerl;
  
  Regexp::ParseState ps(flags, pattern, &status);
  
  bool result = ps.PushCaret();
  EXPECT_TRUE(result);
  
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  // LikePerl = 1940, and OneLine = 16. 1940 & 16 = 16, so OneLine is set.
  EXPECT_EQ(re->op(), kRegexpBeginText);
  re->Decref();
}

// Test PushCaret returns true (basic check)
TEST_F(ParseStatePushCaretTest_490, PushCaretReturnsTrueOneLine_490) {
  RegexpStatus status;
  absl::string_view pattern("^");
  Regexp::ParseFlags flags = Regexp::OneLine;
  
  Regexp::ParseState ps(flags, pattern, &status);
  
  EXPECT_TRUE(ps.PushCaret());
}

// Test PushCaret returns true without OneLine
TEST_F(ParseStatePushCaretTest_490, PushCaretReturnsTrueNoOneLine_490) {
  RegexpStatus status;
  absl::string_view pattern("^");
  Regexp::ParseFlags flags = Regexp::NoParseFlags;
  
  Regexp::ParseState ps(flags, pattern, &status);
  
  EXPECT_TRUE(ps.PushCaret());
}

// Test multiple PushCaret calls result in concatenation
TEST_F(ParseStatePushCaretTest_490, MultiplePushCaretCalls_490) {
  RegexpStatus status;
  absl::string_view pattern("^^");
  Regexp::ParseFlags flags = Regexp::NoParseFlags;
  
  Regexp::ParseState ps(flags, pattern, &status);
  
  EXPECT_TRUE(ps.PushCaret());
  EXPECT_TRUE(ps.PushCaret());
  
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  // Two carets should result in a concatenation of two BeginLine ops
  EXPECT_EQ(re->op(), kRegexpConcat);
  re->Decref();
}

// Test PushCaret with various flag combinations that don't include OneLine
TEST_F(ParseStatePushCaretTest_490, PushCaretWithFoldCaseFlag_490) {
  RegexpStatus status;
  absl::string_view pattern("^");
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::FoldCase | Regexp::ClassNL);
  
  Regexp::ParseState ps(flags, pattern, &status);
  
  bool result = ps.PushCaret();
  EXPECT_TRUE(result);
  
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpBeginLine);
  re->Decref();
}

// Test PushCaret with OneLine combined with other flags
TEST_F(ParseStatePushCaretTest_490, PushCaretOneLineWithOtherFlags_490) {
  RegexpStatus status;
  absl::string_view pattern("^");
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::OneLine | Regexp::FoldCase | Regexp::DotNL);
  
  Regexp::ParseState ps(flags, pattern, &status);
  
  bool result = ps.PushCaret();
  EXPECT_TRUE(result);
  
  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpBeginText);
  re->Decref();
}

// Integration test: Use Regexp::Parse to verify PushCaret behavior via the full parser
TEST_F(ParseStatePushCaretTest_490, ParseFullRegexpWithCaretOneLine_490) {
  RegexpStatus status;
  // Regexp::LikePerl includes OneLine
  Regexp* re = Regexp::Parse("^", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpBeginText);
  re->Decref();
}

TEST_F(ParseStatePushCaretTest_490, ParseFullRegexpWithCaretNoOneLine_490) {
  RegexpStatus status;
  // Use flags without OneLine
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlX | Regexp::PerlClasses | Regexp::PerlB | Regexp::UnicodeGroups);
  Regexp* re = Regexp::Parse("^", flags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpBeginLine);
  re->Decref();
}

}  // namespace re2
