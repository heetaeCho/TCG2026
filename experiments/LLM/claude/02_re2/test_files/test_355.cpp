#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

// Helper to parse a regexp and manage its lifetime
class RegexpTest_355 : public ::testing::Test {
 protected:
  Regexp* Parse(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    EXPECT_TRUE(re != nullptr) << "Failed to parse: " << pattern
                                << " error: " << status.Text();
    return re;
  }
};

// Test NumCaptures with no capturing groups
TEST_F(RegexpTest_355, NumCapturesNoGroups_355) {
  Regexp* re = Parse("abc");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with a single capturing group
TEST_F(RegexpTest_355, NumCapturesSingleGroup_355) {
  Regexp* re = Parse("(abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

// Test NumCaptures with multiple capturing groups
TEST_F(RegexpTest_355, NumCapturesMultipleGroups_355) {
  Regexp* re = Parse("(a)(b)(c)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested capturing groups
TEST_F(RegexpTest_355, NumCapturesNestedGroups_355) {
  Regexp* re = Parse("((a)(b))");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with non-capturing groups
TEST_F(RegexpTest_355, NumCapturesNonCapturingGroups_355) {
  Regexp* re = Parse("(?:abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with mix of capturing and non-capturing groups
TEST_F(RegexpTest_355, NumCapturesMixedGroups_355) {
  Regexp* re = Parse("(a)(?:b)(c)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 2);
  re->Decref();
}

// Test NumCaptures with named capturing groups
TEST_F(RegexpTest_355, NumCapturesNamedGroups_355) {
  Regexp* re = Parse("(?P<name>abc)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

// Test NumCaptures with alternation containing captures
TEST_F(RegexpTest_355, NumCapturesAlternation_355) {
  Regexp* re = Parse("(a)|(b)|(c)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with repetition containing captures
TEST_F(RegexpTest_355, NumCapturesRepetition_355) {
  Regexp* re = Parse("(a)+");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

// Test NumCaptures with deeply nested groups
TEST_F(RegexpTest_355, NumCapturesDeeplyNested_355) {
  Regexp* re = Parse("(((((a)))))");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 5);
  re->Decref();
}

// Test NumCaptures with empty capturing group
TEST_F(RegexpTest_355, NumCapturesEmptyGroup_355) {
  Regexp* re = Parse("()");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 1);
  re->Decref();
}

// Test NumCaptures with complex pattern
TEST_F(RegexpTest_355, NumCapturesComplexPattern_355) {
  Regexp* re = Parse("(?P<first>\\d+)-(?P<second>\\w+)(?:foo)(bar)");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NamedCaptures returns null when no named captures
TEST_F(RegexpTest_355, NamedCapturesNone_355) {
  Regexp* re = Parse("(abc)");
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

// Test NamedCaptures with named groups
TEST_F(RegexpTest_355, NamedCapturesPresent_355) {
  Regexp* re = Parse("(?P<name>abc)(?P<value>\\d+)");
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_EQ((*named)["name"], 1);
  EXPECT_EQ((*named)["value"], 2);
  delete named;
  re->Decref();
}

// Test CaptureNames with captures
TEST_F(RegexpTest_355, CaptureNamesPresent_355) {
  Regexp* re = Parse("(?P<first>a)(b)(?P<third>c)");
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ((*names)[1], "first");
  EXPECT_EQ((*names)[3], "third");
  // Unnamed group (2) may or may not be present depending on implementation
  delete names;
  re->Decref();
}

// Test Parse with empty string
TEST_F(RegexpTest_355, ParseEmptyString_355) {
  Regexp* re = Parse("");
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test Parse with invalid pattern returns null
TEST_F(RegexpTest_355, ParseInvalidPattern_355) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
}

// Test ToString roundtrip
TEST_F(RegexpTest_355, ToStringBasic_355) {
  Regexp* re = Parse("abc");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Dump produces non-empty output
TEST_F(RegexpTest_355, DumpNonEmpty_355) {
  Regexp* re = Parse("(a|b)*");
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Test Simplify returns a valid regexp
TEST_F(RegexpTest_355, SimplifyBasic_355) {
  Regexp* re = Parse("a{3,5}");
  ASSERT_NE(re, nullptr);
  Regexp* simple = re->Simplify();
  ASSERT_NE(simple, nullptr);
  simple->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(RegexpTest_355, SimplifyRegexpStatic_355) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,4}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test Incref and Decref
TEST_F(RegexpTest_355, IncrefDecref_355) {
  Regexp* re = Parse("abc");
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re->Decref();  // Final decref
}

// Test HaveMatch
TEST_F(RegexpTest_355, HaveMatch_355) {
  Regexp* re = Regexp::HaveMatch(0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->match_id(), 0);
  re->Decref();
}

// Test NewLiteral
TEST_F(RegexpTest_355, NewLiteral_355) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test Plus
TEST_F(RegexpTest_355, PlusOp_355) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Star
TEST_F(RegexpTest_355, StarOp_355) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Quest
TEST_F(RegexpTest_355, QuestOp_355) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Quest(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Concat with multiple subs
TEST_F(RegexpTest_355, ConcatMultiple_355) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate with multiple subs
TEST_F(RegexpTest_355, AlternateMultiple_355) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Capture
TEST_F(RegexpTest_355, CaptureOp_355) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Repeat
TEST_F(RegexpTest_355, RepeatOp_355) {
  Regexp* sub = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test LiteralString
TEST_F(RegexpTest_355, LiteralStringOp_355) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test RequiredPrefix on pattern with literal prefix
TEST_F(RegexpTest_355, RequiredPrefixLiteral_355) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix != nullptr) {
      suffix->Decref();
    }
  }
  re->Decref();
}

// Test RequiredPrefix on pattern without prefix
TEST_F(RegexpTest_355, RequiredPrefixNone_355) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (!has_prefix) {
    EXPECT_TRUE(prefix.empty());
  } else {
    if (suffix != nullptr) suffix->Decref();
  }
  re->Decref();
}

// Test CompileToProg
TEST_F(RegexpTest_355, CompileToProg_355) {
  Regexp* re = Parse("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST_F(RegexpTest_355, CompileToReverseProg_355) {
  Regexp* re = Parse("abc");
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test NumCaptures with many groups
TEST_F(RegexpTest_355, NumCapturesManyGroups_355) {
  // Build pattern with 10 capturing groups
  std::string pattern;
  for (int i = 0; i < 10; i++) {
    pattern += "(a)";
  }
  Regexp* re = Parse(pattern);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 10);
  re->Decref();
}

// Test Concat with zero subs
TEST_F(RegexpTest_355, ConcatZeroSubs_355) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate with zero subs
TEST_F(RegexpTest_355, AlternateZeroSubs_355) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Concat with single sub
TEST_F(RegexpTest_355, ConcatSingleSub_355) {
  Regexp* sub = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(&sub, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate with single sub
TEST_F(RegexpTest_355, AlternateSingleSub_355) {
  Regexp* sub = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(&sub, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test op() accessor
TEST_F(RegexpTest_355, OpAccessor_355) {
  Regexp* re = Parse("a+");
  ASSERT_NE(re, nullptr);
  // Should be kRegexpPlus at the top level
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test parse_flags() accessor
TEST_F(RegexpTest_355, ParseFlagsAccessor_355) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // parse_flags should include what was passed
  re->Decref();
}

// Test NullWalk doesn't crash
TEST_F(RegexpTest_355, NullWalkNoCrash_355) {
  Regexp* re = Parse("(a|b)*c+");
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// Test MimicsPCRE for simple pattern
TEST_F(RegexpTest_355, MimicsPCRESimple_355) {
  Regexp* re = Parse("abc");
  ASSERT_NE(re, nullptr);
  // Simple literal should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// Test AlternateNoFactor
TEST_F(RegexpTest_355, AlternateNoFactor_355) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST_F(RegexpTest_355, RequiredPrefixForAccel_355) {
  Regexp* re = Parse("^hello.*");
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  // May or may not find a prefix; just ensure no crash
  re->Decref();
}

// Test Repeat with min == max
TEST_F(RegexpTest_355, RepeatExact_355) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// Test Repeat with unbounded max (-1 typically means unlimited)
TEST_F(RegexpTest_355, RepeatUnbounded_355) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 1, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 1);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

}  // namespace re2
