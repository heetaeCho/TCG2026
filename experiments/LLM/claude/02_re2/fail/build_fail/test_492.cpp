#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class PushDollarTest_492 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test PushDollar with OneLine flag set - should push kRegexpEndText
TEST_F(PushDollarTest_492, PushDollarWithOneLineFlag_492) {
  RegexpStatus status;
  absl::string_view pattern("$");
  Regexp::ParseState ps(
      static_cast<Regexp::ParseFlags>(Regexp::OneLine | Regexp::PerlX),
      pattern, &status);
  
  bool result = ps.PushDollar();
  EXPECT_TRUE(result);
  
  // The flags should not have WasDollar permanently set
  // (it's restored after PushSimpleOp)
  EXPECT_EQ(ps.flags() & Regexp::WasDollar, 0);
}

// Test PushDollar without OneLine flag - should push kRegexpEndLine
TEST_F(PushDollarTest_492, PushDollarWithoutOneLineFlag_492) {
  RegexpStatus status;
  absl::string_view pattern("$");
  Regexp::ParseState ps(
      static_cast<Regexp::ParseFlags>(Regexp::PerlX),
      pattern, &status);
  
  bool result = ps.PushDollar();
  EXPECT_TRUE(result);
}

// Test PushDollar with no flags at all (no OneLine)
TEST_F(PushDollarTest_492, PushDollarWithNoFlags_492) {
  RegexpStatus status;
  absl::string_view pattern("$");
  Regexp::ParseState ps(Regexp::NoParseFlags, pattern, &status);
  
  bool result = ps.PushDollar();
  EXPECT_TRUE(result);
}

// Test PushDollar with OneLine and other flags combined
TEST_F(PushDollarTest_492, PushDollarWithOneLineAndOtherFlags_492) {
  RegexpStatus status;
  absl::string_view pattern("$");
  Regexp::ParseState ps(
      static_cast<Regexp::ParseFlags>(Regexp::OneLine | Regexp::FoldCase | Regexp::PerlX),
      pattern, &status);
  
  bool result = ps.PushDollar();
  EXPECT_TRUE(result);
  
  // Verify flags are restored (WasDollar should not persist)
  EXPECT_EQ(ps.flags() & Regexp::WasDollar, 0);
  // OneLine should still be set
  EXPECT_NE(ps.flags() & Regexp::OneLine, 0);
  // FoldCase should still be set
  EXPECT_NE(ps.flags() & Regexp::FoldCase, 0);
}

// Test PushDollar with LikePerl flags (which includes OneLine)
TEST_F(PushDollarTest_492, PushDollarWithLikePerlFlags_492) {
  RegexpStatus status;
  absl::string_view pattern("$");
  Regexp::ParseState ps(Regexp::LikePerl, pattern, &status);
  
  // LikePerl = 1940; check if OneLine (16) is part of it
  bool has_one_line = (Regexp::LikePerl & Regexp::OneLine) != 0;
  
  bool result = ps.PushDollar();
  EXPECT_TRUE(result);
  
  if (has_one_line) {
    // WasDollar should NOT persist after PushDollar
    EXPECT_EQ(ps.flags() & Regexp::WasDollar, 0);
  }
}

// Test PushDollar flags restoration - WasDollar should be temporary
TEST_F(PushDollarTest_492, PushDollarFlagsRestoredAfterCall_492) {
  RegexpStatus status;
  absl::string_view pattern("test$");
  Regexp::ParseState ps(
      static_cast<Regexp::ParseFlags>(Regexp::OneLine),
      pattern, &status);
  
  Regexp::ParseFlags before = ps.flags();
  bool result = ps.PushDollar();
  EXPECT_TRUE(result);
  Regexp::ParseFlags after = ps.flags();
  
  // Flags should be the same before and after
  EXPECT_EQ(before, after);
}

// Test PushDollar can be called multiple times
TEST_F(PushDollarTest_492, PushDollarMultipleTimes_492) {
  RegexpStatus status;
  absl::string_view pattern("$$");
  Regexp::ParseState ps(
      static_cast<Regexp::ParseFlags>(Regexp::OneLine),
      pattern, &status);
  
  bool result1 = ps.PushDollar();
  EXPECT_TRUE(result1);
  
  bool result2 = ps.PushDollar();
  EXPECT_TRUE(result2);
}

// Test PushDollar without OneLine, multiple times
TEST_F(PushDollarTest_492, PushDollarMultipleTimesNoOneLine_492) {
  RegexpStatus status;
  absl::string_view pattern("$$");
  Regexp::ParseState ps(Regexp::NoParseFlags, pattern, &status);
  
  bool result1 = ps.PushDollar();
  EXPECT_TRUE(result1);
  
  bool result2 = ps.PushDollar();
  EXPECT_TRUE(result2);
}

// Test that PushDollar result can be used in DoFinish flow with OneLine
TEST_F(PushDollarTest_492, PushDollarInFullParseFlowOneLine_492) {
  RegexpStatus status;
  absl::string_view pattern("a$");
  Regexp::ParseState ps(
      static_cast<Regexp::ParseFlags>(Regexp::OneLine),
      pattern, &status);
  
  // Push a literal then dollar
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushDollar());
  
  Regexp* result = ps.DoFinish();
  EXPECT_NE(result, nullptr);
  if (result) {
    result->Decref();
  }
}

// Test that PushDollar result can be used in DoFinish flow without OneLine
TEST_F(PushDollarTest_492, PushDollarInFullParseFlowNoOneLine_492) {
  RegexpStatus status;
  absl::string_view pattern("a$");
  Regexp::ParseState ps(Regexp::NoParseFlags, pattern, &status);
  
  // Push a literal then dollar
  EXPECT_TRUE(ps.PushLiteral('a'));
  EXPECT_TRUE(ps.PushDollar());
  
  Regexp* result = ps.DoFinish();
  EXPECT_NE(result, nullptr);
  if (result) {
    result->Decref();
  }
}

// Test PushDollar with WasDollar already set in flags (edge case)
TEST_F(PushDollarTest_492, PushDollarWithWasDollarAlreadySet_492) {
  RegexpStatus status;
  absl::string_view pattern("$");
  // WasDollar | OneLine
  Regexp::ParseState ps(
      static_cast<Regexp::ParseFlags>(Regexp::OneLine | Regexp::WasDollar),
      pattern, &status);
  
  bool result = ps.PushDollar();
  EXPECT_TRUE(result);
}

// Integration: verify PushDollar vs PushCaret symmetry
TEST_F(PushDollarTest_492, PushDollarAndPushCaretBothSucceed_492) {
  RegexpStatus status;
  absl::string_view pattern("^$");
  Regexp::ParseState ps(
      static_cast<Regexp::ParseFlags>(Regexp::OneLine),
      pattern, &status);
  
  EXPECT_TRUE(ps.PushCaret());
  EXPECT_TRUE(ps.PushDollar());
  
  Regexp* result = ps.DoFinish();
  EXPECT_NE(result, nullptr);
  if (result) {
    result->Decref();
  }
}

// Test PushDollar with Literal flag
TEST_F(PushDollarTest_492, PushDollarWithLiteralFlag_492) {
  RegexpStatus status;
  absl::string_view pattern("$");
  Regexp::ParseState ps(
      static_cast<Regexp::ParseFlags>(Regexp::Literal),
      pattern, &status);
  
  // Literal flag doesn't include OneLine, so should push EndLine
  bool result = ps.PushDollar();
  EXPECT_TRUE(result);
}

}  // namespace re2
