#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class MimicsPCRETest_219 : public ::testing::Test {
 protected:
  Regexp* ParseRegexp(const char* pattern, Regexp::ParseFlags flags = Regexp::LikePerl) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, flags, &status);
    EXPECT_TRUE(re != nullptr) << "Failed to parse: " << pattern
                                << " error: " << status.Text();
    return re;
  }
};

// Test simple literal string mimics PCRE
TEST_F(MimicsPCRETest_219, SimpleLiteralMimicsPCRE_219) {
  Regexp* re = ParseRegexp("abc");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that ^ (beginning of line) does NOT mimic PCRE
TEST_F(MimicsPCRETest_219, BeginLineDoesNotMimicPCRE_219) {
  Regexp* re = ParseRegexp("^abc");
  ASSERT_NE(re, nullptr);
  EXPECT_FALSE(re->MimicsPCRE());
  re->Decref();
}

// Test that star with possibly empty subexpression does not mimic PCRE
TEST_F(MimicsPCRETest_219, StarEmptySubDoesNotMimicPCRE_219) {
  // (a*)* - the inner a* can be empty string
  Regexp* re = ParseRegexp("(a*)*");
  ASSERT_NE(re, nullptr);
  EXPECT_FALSE(re->MimicsPCRE());
  re->Decref();
}

// Test that plus with possibly empty subexpression does not mimic PCRE
TEST_F(MimicsPCRETest_219, PlusEmptySubDoesNotMimicPCRE_219) {
  // (a*)+ - the inner a* can be empty string
  Regexp* re = ParseRegexp("(a*)+");
  ASSERT_NE(re, nullptr);
  EXPECT_FALSE(re->MimicsPCRE());
  re->Decref();
}

// Test that quest with possibly empty subexpression does not mimic PCRE
TEST_F(MimicsPCRETest_219, QuestEmptySubDoesNotMimicPCRE_219) {
  // (a*)? - the inner a* can be empty string
  Regexp* re = ParseRegexp("(a*)?");
  ASSERT_NE(re, nullptr);
  EXPECT_FALSE(re->MimicsPCRE());
  re->Decref();
}

// Test that \v literal does not mimic PCRE
TEST_F(MimicsPCRETest_219, VerticalTabDoesNotMimicPCRE_219) {
  Regexp* re = ParseRegexp("\\x0b");
  ASSERT_NE(re, nullptr);
  EXPECT_FALSE(re->MimicsPCRE());
  re->Decref();
}

// Test that simple star mimics PCRE (non-empty sub)
TEST_F(MimicsPCRETest_219, SimpleStarMimicsPCRE_219) {
  Regexp* re = ParseRegexp("a*");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that simple plus mimics PCRE (non-empty sub)
TEST_F(MimicsPCRETest_219, SimplePlusMimicsPCRE_219) {
  Regexp* re = ParseRegexp("a+");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that simple quest mimics PCRE (non-empty sub)
TEST_F(MimicsPCRETest_219, SimpleQuestMimicsPCRE_219) {
  Regexp* re = ParseRegexp("a?");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test repeat with unbounded max and empty sub does not mimic PCRE
TEST_F(MimicsPCRETest_219, RepeatUnboundedEmptySubDoesNotMimicPCRE_219) {
  // (a*){2,} - unbounded repeat with sub that can be empty
  Regexp* re = ParseRegexp("(a*){2,}");
  ASSERT_NE(re, nullptr);
  EXPECT_FALSE(re->MimicsPCRE());
  re->Decref();
}

// Test repeat with bounded max mimics PCRE even with empty sub
TEST_F(MimicsPCRETest_219, RepeatBoundedMimicsPCRE_219) {
  // (a*){2,5} - bounded repeat should be ok
  Regexp* re = ParseRegexp("(a*){2,5}");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test simple repeat mimics PCRE
TEST_F(MimicsPCRETest_219, SimpleRepeatMimicsPCRE_219) {
  Regexp* re = ParseRegexp("a{3,5}");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test alternation mimics PCRE
TEST_F(MimicsPCRETest_219, AlternationMimicsPCRE_219) {
  Regexp* re = ParseRegexp("a|b");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test character class mimics PCRE
TEST_F(MimicsPCRETest_219, CharClassMimicsPCRE_219) {
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test dot (any char) mimics PCRE
TEST_F(MimicsPCRETest_219, DotMimicsPCRE_219) {
  Regexp* re = ParseRegexp(".");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test capture group mimics PCRE
TEST_F(MimicsPCRETest_219, CaptureGroupMimicsPCRE_219) {
  Regexp* re = ParseRegexp("(abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test $ (end text / WasDollar) in multiline mode does not mimic PCRE
TEST_F(MimicsPCRETest_219, DollarMultilineDoesNotMimicPCRE_219) {
  // In non-OneLine mode, $ becomes EndLine which is fine,
  // but with OneLine, $ sets WasDollar on EndText
  Regexp* re = ParseRegexp("abc$", Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // With LikePerl (includes OneLine), $ -> EndText with WasDollar
  EXPECT_FALSE(re->MimicsPCRE());
  re->Decref();
}

// Test \b word boundary mimics PCRE
TEST_F(MimicsPCRETest_219, WordBoundaryMimicsPCRE_219) {
  Regexp* re = ParseRegexp("\\bword\\b");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test begin text (\A) mimics PCRE
TEST_F(MimicsPCRETest_219, BeginTextMimicsPCRE_219) {
  Regexp* re = ParseRegexp("\\Aabc");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test complex pattern that mimics PCRE
TEST_F(MimicsPCRETest_219, ComplexPatternMimicsPCRE_219) {
  Regexp* re = ParseRegexp("[a-z]+[0-9]{2,4}");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test nested groups mimicking PCRE
TEST_F(MimicsPCRETest_219, NestedGroupsMimicsPCRE_219) {
  Regexp* re = ParseRegexp("((a)(b))");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test that a child not mimicking PCRE propagates up
TEST_F(MimicsPCRETest_219, ChildFailurePropagates_219) {
  // (^a)b - ^ inside group doesn't mimic PCRE
  Regexp* re = ParseRegexp("(^a)b");
  ASSERT_NE(re, nullptr);
  EXPECT_FALSE(re->MimicsPCRE());
  re->Decref();
}

// Test empty match mimics PCRE (without WasDollar flag)
TEST_F(MimicsPCRETest_219, EmptyStringPatternMimicsPCRE_219) {
  // Empty pattern should parse to an empty match
  Regexp* re = ParseRegexp("");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test alternation with begin line fails
TEST_F(MimicsPCRETest_219, AlternationWithBeginLineDoesNotMimicPCRE_219) {
  Regexp* re = ParseRegexp("^a|b");
  ASSERT_NE(re, nullptr);
  EXPECT_FALSE(re->MimicsPCRE());
  re->Decref();
}

// Test simple bounded repeat with non-empty sub mimics PCRE
TEST_F(MimicsPCRETest_219, BoundedRepeatNonEmptySubMimicsPCRE_219) {
  Regexp* re = ParseRegexp("a{1,3}");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

// Test unbounded repeat with non-empty sub mimics PCRE
TEST_F(MimicsPCRETest_219, UnboundedRepeatNonEmptySubMimicsPCRE_219) {
  Regexp* re = ParseRegexp("a{2,}");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->MimicsPCRE());
  re->Decref();
}

}  // namespace re2
