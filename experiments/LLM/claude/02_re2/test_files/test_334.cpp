#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

class RegexpTest_334 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that Parse returns a non-null Regexp for a simple pattern
TEST_F(RegexpTest_334, ParseSimplePattern_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that Parse returns a non-null Regexp for an empty pattern
TEST_F(RegexpTest_334, ParseEmptyPattern_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test that Parse handles invalid regex
TEST_F(RegexpTest_334, ParseInvalidPattern_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test Ref on a newly created Regexp (should be 1 after Parse)
TEST_F(RegexpTest_334, RefAfterParse_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // After parse, reference count should be at least 1
  EXPECT_GE(re->Ref(), 1);
  re->Decref();
}

// Test Incref increases Ref count
TEST_F(RegexpTest_334, IncrefIncreasesRef_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  int initial_ref = re->Ref();
  re->Incref();
  EXPECT_EQ(re->Ref(), initial_ref + 1);
  re->Decref();
  re->Decref();
}

// Test multiple Incref/Decref
TEST_F(RegexpTest_334, MultipleIncrefDecref_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  int initial_ref = re->Ref();
  re->Incref();
  re->Incref();
  EXPECT_EQ(re->Ref(), initial_ref + 2);
  re->Decref();
  EXPECT_EQ(re->Ref(), initial_ref + 1);
  re->Decref();
  EXPECT_EQ(re->Ref(), initial_ref);
  re->Decref();
}

// Test ToString returns a string representation
TEST_F(RegexpTest_334, ToStringSimple_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Dump returns something non-empty
TEST_F(RegexpTest_334, DumpSimple_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Test NumCaptures with no captures
TEST_F(RegexpTest_334, NumCapturesZero_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with captures
TEST_F(RegexpTest_334, NumCapturesNonZero_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested captures
TEST_F(RegexpTest_334, NumCapturesNested_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NamedCaptures when there are none
TEST_F(RegexpTest_334, NamedCapturesNone_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

// Test NamedCaptures with named groups
TEST_F(RegexpTest_334, NamedCapturesPresent_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>a)(?P<value>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_NE(named->find("name"), named->end());
  EXPECT_NE(named->find("value"), named->end());
  delete named;
  re->Decref();
}

// Test CaptureNames
TEST_F(RegexpTest_334, CaptureNamesPresent_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  // Capture 1 should be named "foo"
  auto it = names->find(1);
  ASSERT_NE(it, names->end());
  EXPECT_EQ(it->second, "foo");
  delete names;
  re->Decref();
}

// Test CaptureNames when no captures
TEST_F(RegexpTest_334, CaptureNamesNone_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
  re->Decref();
}

// Test NewLiteral creates a literal regexp
TEST_F(RegexpTest_334, NewLiteral_334) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test HaveMatch
TEST_F(RegexpTest_334, HaveMatch_334) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test Plus
TEST_F(RegexpTest_334, Plus_334) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Plus(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Star
TEST_F(RegexpTest_334, Star_334) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Star(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Quest
TEST_F(RegexpTest_334, Quest_334) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Quest(sub, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Concat
TEST_F(RegexpTest_334, Concat_334) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Concat with zero elements
TEST_F(RegexpTest_334, ConcatZero_334) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Concat with one element
TEST_F(RegexpTest_334, ConcatOne_334) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('x', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate
TEST_F(RegexpTest_334, Alternate_334) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test AlternateNoFactor
TEST_F(RegexpTest_334, AlternateNoFactor_334) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Capture
TEST_F(RegexpTest_334, Capture_334) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Capture(sub, Regexp::LikePerl, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Repeat
TEST_F(RegexpTest_334, Repeat_334) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Repeat with min == max
TEST_F(RegexpTest_334, RepeatExact_334) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 3, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), 3);
  re->Decref();
}

// Test LiteralString
TEST_F(RegexpTest_334, LiteralString_334) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test Simplify
TEST_F(RegexpTest_334, SimplifySimple_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(RegexpTest_334, SimplifyRegexpStatic_334) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,4}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test CompileToProg
TEST_F(RegexpTest_334, CompileToProg_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST_F(RegexpTest_334, CompileToReverseProg_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test RequiredPrefix for anchored literal
TEST_F(RegexpTest_334, RequiredPrefixAnchored_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::LikePerl, &status);
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

// Test RequiredPrefix for non-anchored pattern
TEST_F(RegexpTest_334, RequiredPrefixNonAnchored_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  // Non-anchored pattern should not have a required prefix
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// Test NullWalk doesn't crash
TEST_F(RegexpTest_334, NullWalk_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // NullWalk should not crash
  re->NullWalk();
  re->Decref();
}

// Test op() returns correct operation
TEST_F(RegexpTest_334, OpLiteral_334) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test parse_flags()
TEST_F(RegexpTest_334, ParseFlags_334) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // parse_flags should contain the flags used during creation
  Regexp::ParseFlags flags = re->parse_flags();
  // LikePerl is a combination of flags, just ensure it's non-zero
  EXPECT_NE(flags, 0);
  re->Decref();
}

// Test complex pattern parsing
TEST_F(RegexpTest_334, ParseComplexPattern_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:a|b)*(?:c+d{2,5})?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test character class pattern
TEST_F(RegexpTest_334, ParseCharClassPattern_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z0-9]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Parse with unmatched closing paren
TEST_F(RegexpTest_334, ParseUnmatchedCloseParen_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(")", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test Parse with bad escape
TEST_F(RegexpTest_334, ParseBadEscape_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test Parse with bad repetition (nothing to repeat)
TEST_F(RegexpTest_334, ParseBadRepetition_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("*", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test that Incref returns the same pointer
TEST_F(RegexpTest_334, IncrefReturnsSamePointer_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* same = re->Incref();
  EXPECT_EQ(same, re);
  re->Decref();
  re->Decref();
}

// Test Repeat with min=0, max=-1 (unbounded)
TEST_F(RegexpTest_334, RepeatUnbounded_334) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* re = Regexp::Repeat(sub, Regexp::LikePerl, 0, -1);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test simple() accessor
TEST_F(RegexpTest_334, SimpleAccessor_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // After Simplify, simple() should be true
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  EXPECT_TRUE(simplified->simple());
  simplified->Decref();
  re->Decref();
}

// Test ToString round trip
TEST_F(RegexpTest_334, ToStringRoundTrip_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s1 = re->ToString();
  RegexpStatus status2;
  Regexp* re2 = Regexp::Parse(s1, Regexp::LikePerl, &status2);
  ASSERT_NE(re2, nullptr);
  std::string s2 = re2->ToString();
  EXPECT_EQ(s1, s2);
  re->Decref();
  re2->Decref();
}

// Test RequiredPrefixForAccel
TEST_F(RegexpTest_334, RequiredPrefixForAccel_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  bool has = re->RequiredPrefixForAccel(&prefix, &foldcase);
  if (has) {
    EXPECT_FALSE(prefix.empty());
  }
  re->Decref();
}

// Test MimicsPCRE
TEST_F(RegexpTest_334, MimicsPCRE_334) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple pattern should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// Test nsub accessor
TEST_F(RegexpTest_334, NsubAccessor_334) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::LikePerl);
  ASSERT_NE(re, nullptr);
  // For a concat of 3, nsub should be >= 1
  // The exact value depends on internal optimizations
  EXPECT_GE(re->nsub(), 1);
  re->Decref();
}

}  // namespace re2
