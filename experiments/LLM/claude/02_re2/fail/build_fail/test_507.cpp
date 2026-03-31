#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <vector>

namespace re2 {

// We test the FactorAlternationImpl::Round2 indirectly through the public
// Regexp::Alternate and Regexp::Parse interfaces, since Round2 is called
// internally during alternation factoring. We also test related public
// Regexp functionality.

class FactorAlternationImplTest_507 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that parsing a simple alternation works correctly
TEST_F(FactorAlternationImplTest_507, SimpleAlternation_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);  // a|b should be optimized to [ab]
  re->Decref();
}

// Test alternation with common leading literal prefix triggers factoring
TEST_F(FactorAlternationImplTest_507, CommonLeadingLiteralPrefix_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|abd", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Should be factored to ab(c|d)
  std::string dump = re->Dump();
  EXPECT_NE(dump.find("cat"), std::string::npos);
  re->Decref();
}

// Test alternation with common leading regexp (e.g., ^) triggers Round2
TEST_F(FactorAlternationImplTest_507, CommonLeadingBeginLine_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^a|^b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Should be factored: ^ is the common leading regexp
  std::string dump = re->Dump();
  // The result should contain bol (begin of line) factored out
  EXPECT_NE(dump.find("bol"), std::string::npos);
  re->Decref();
}

// Test alternation with common leading EndLine
TEST_F(FactorAlternationImplTest_507, CommonLeadingEndLine_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a$|b$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  re->Decref();
}

// Test alternation with common leading dot (AnyChar)
TEST_F(FactorAlternationImplTest_507, CommonLeadingAnyChar_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".a|.b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  // Should factor out the dot: .(a|b) => .([ab])
  EXPECT_NE(dump.find("dot"), std::string::npos);
  re->Decref();
}

// Test alternation with no common prefix
TEST_F(FactorAlternationImplTest_507, NoCommonPrefix_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test single alternative (no factoring needed)
TEST_F(FactorAlternationImplTest_507, SingleAlternative_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_NE(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test alternation with word boundary as common leading regexp
TEST_F(FactorAlternationImplTest_507, CommonLeadingWordBoundary_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bfoo|\\bbar", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  // Word boundary should be factored out
  EXPECT_NE(dump.find("wb"), std::string::npos);
  re->Decref();
}

// Test alternation with BeginText (\A) as common leading regexp
TEST_F(FactorAlternationImplTest_507, CommonLeadingBeginText_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\Afoo|\\Abar", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  re->Decref();
}

// Test alternation with EndText (\z) as common leading regexp
TEST_F(FactorAlternationImplTest_507, CommonLeadingEndText_507) {
  RegexpStatus status;
  // \z at end - but we want it as leading. Use patterns where factoring applies.
  Regexp* re = Regexp::Parse("a\\z|b\\z", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test alternation with character class as common leading regexp
TEST_F(FactorAlternationImplTest_507, CommonLeadingCharClass_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[0-9]a|[0-9]b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  // [0-9] should be factored out
  EXPECT_NE(dump.find("cc"), std::string::npos);
  re->Decref();
}

// Test alternation with AnyByte as common leading regexp
TEST_F(FactorAlternationImplTest_507, CommonLeadingAnyByte_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?s:.a|.b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test alternation with many branches sharing a common prefix
TEST_F(FactorAlternationImplTest_507, ManyBranchesCommonPrefix_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^a|^b|^c|^d|^e", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  // All branches share ^, should factor
  EXPECT_NE(dump.find("bol"), std::string::npos);
  re->Decref();
}

// Test alternation where only some branches share a common leading regexp
TEST_F(FactorAlternationImplTest_507, PartialCommonPrefix_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^a|^b|cd", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  re->Decref();
}

// Test that Alternate with a single sub returns that sub
TEST_F(FactorAlternationImplTest_507, AlternateSingleSub_507) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* subs[] = {lit};
  Regexp* alt = Regexp::Alternate(subs, 1, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpLiteral);
  alt->Decref();
}

// Test Alternate with two identical subs
TEST_F(FactorAlternationImplTest_507, AlternateIdenticalSubs_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Should simplify to just 'a'
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test complex pattern with leading repeat
TEST_F(FactorAlternationImplTest_507, CommonLeadingRepeat_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}b|a{3}c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  // a{3} should be factored out (repeat with min==max and literal sub)
  EXPECT_NE(dump.find("rep"), std::string::npos);
  re->Decref();
}

// Test that factoring works with repeat where min != max (should NOT factor)
TEST_F(FactorAlternationImplTest_507, LeadingRepeatMinNeMax_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,3}b|a{2,3}c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // min != max so Round2 should not factor the repeat
  re->Decref();
}

// Test alternation with empty match
TEST_F(FactorAlternationImplTest_507, AlternationWithEmptyMatch_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test that ToString round-trips for factored alternation
TEST_F(FactorAlternationImplTest_507, ToStringRoundTrip_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|abd", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test alternation with no-word-boundary
TEST_F(FactorAlternationImplTest_507, CommonLeadingNoWordBoundary_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\Bfoo|\\Bbar", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  // \B should be factored
  EXPECT_NE(dump.find("nwb"), std::string::npos);
  re->Decref();
}

// Test that AlternateNoFactor does not factor
TEST_F(FactorAlternationImplTest_507, AlternateNoFactor_507) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* b = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* subs[] = {a, b};
  Regexp* alt = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpAlternate);
  EXPECT_EQ(alt->nsub(), 2);
  alt->Decref();
}

// Test deeply nested alternation with common leading char classes
TEST_F(FactorAlternationImplTest_507, DeepNestedAlternation_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]1|[a-z]2|[a-z]3|[a-z]4", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  // [a-z] should be factored out, result should be [a-z]cat(alt(...))
  EXPECT_NE(dump.find("cc"), std::string::npos);
  re->Decref();
}

// Test that common leading repeat with char class sub is factored
TEST_F(FactorAlternationImplTest_507, CommonLeadingRepeatCharClass_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]{3}foo|[a-z]{3}bar", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  re->Decref();
}

// Test two branches where leading regexp differs
TEST_F(FactorAlternationImplTest_507, DifferentLeadingRegexp_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^a|.b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // No factoring should happen - different leading regexps
  EXPECT_EQ(re->op(), kRegexpAlternate);
  re->Decref();
}

// Test empty pattern
TEST_F(FactorAlternationImplTest_507, EmptyPattern_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test multiple levels of factoring
TEST_F(FactorAlternationImplTest_507, MultipleLevelsFactoring_507) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abcx|abcy|abdx|abdy", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  // Should factor to ab(c(x|y)|d(x|y)) or similar
  re->Decref();
}

}  // namespace re2
