#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class RegexpTest_153 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Decref any regexp we created
  }
};

// Test parsing a simple literal string
TEST_F(RegexpTest_153, ParseSimpleLiteral_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing an empty string
TEST_F(RegexpTest_153, ParseEmptyString_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing a complex pattern
TEST_F(RegexpTest_153, ParseComplexPattern_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+d?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing an invalid pattern
TEST_F(RegexpTest_153, ParseInvalidPattern_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test ToString roundtrip
TEST_F(RegexpTest_153, ToStringRoundtrip_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+b*c?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Dump produces non-empty output
TEST_F(RegexpTest_153, DumpNonEmpty_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Test NumCaptures with no captures
TEST_F(RegexpTest_153, NumCapturesZero_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(0, re->NumCaptures());
  re->Decref();
}

// Test NumCaptures with captures
TEST_F(RegexpTest_153, NumCapturesMultiple_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(3, re->NumCaptures());
  re->Decref();
}

// Test NumCaptures with nested captures
TEST_F(RegexpTest_153, NumCapturesNested_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(3, re->NumCaptures());
  re->Decref();
}

// Test NamedCaptures returns nullptr when there are no named captures
TEST_F(RegexpTest_153, NamedCapturesNone_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

// Test NamedCaptures with named captures
TEST_F(RegexpTest_153, NamedCapturesPresent_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_NE(named->find("foo"), named->end());
  EXPECT_NE(named->find("bar"), named->end());
  delete named;
  re->Decref();
}

// Test CaptureNames
TEST_F(RegexpTest_153, CaptureNamesPresent_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  delete names;
  re->Decref();
}

// Test CaptureNames with no named captures returns nullptr
TEST_F(RegexpTest_153, CaptureNamesNone_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* names = re->CaptureNames();
  EXPECT_EQ(names, nullptr);
  delete names;
  re->Decref();
}

// Test Incref and Decref
TEST_F(RegexpTest_153, IncrefDecref_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re2->Decref();
}

// Test op() returns a valid RegexpOp
TEST_F(RegexpTest_153, OpAccessor_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  RegexpOp op = re->op();
  // kRegexpLiteral for a single character
  EXPECT_EQ(op, kRegexpLiteral);
  re->Decref();
}

// Test nsub() for a concatenation
TEST_F(RegexpTest_153, NsubConcat_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpConcat) {
    EXPECT_GT(re->nsub(), 1);
  }
  re->Decref();
}

// Test sub() for pattern with subexpressions
TEST_F(RegexpTest_153, SubAccessor_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  EXPECT_EQ(re->nsub(), 1);
  Regexp** subs = re->sub();
  ASSERT_NE(subs, nullptr);
  EXPECT_NE(subs[0], nullptr);
  re->Decref();
}

// Test sub() for multiple subexpressions (nsub > 1)
TEST_F(RegexpTest_153, SubAccessorMultiple_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpConcat && re->nsub() > 1) {
    Regexp** subs = re->sub();
    ASSERT_NE(subs, nullptr);
    for (int i = 0; i < re->nsub(); i++) {
      EXPECT_NE(subs[i], nullptr);
    }
  }
  re->Decref();
}

// Test Plus factory method
TEST_F(RegexpTest_153, PlusFactory_153) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  Regexp* plus = Regexp::Plus(lit, Regexp::LikePerl);
  ASSERT_NE(plus, nullptr);
  EXPECT_EQ(plus->op(), kRegexpPlus);
  EXPECT_EQ(plus->nsub(), 1);
  plus->Decref();
}

// Test Star factory method
TEST_F(RegexpTest_153, StarFactory_153) {
  Regexp* lit = Regexp::NewLiteral('b', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  Regexp* star = Regexp::Star(lit, Regexp::LikePerl);
  ASSERT_NE(star, nullptr);
  EXPECT_EQ(star->op(), kRegexpStar);
  EXPECT_EQ(star->nsub(), 1);
  star->Decref();
}

// Test Quest factory method
TEST_F(RegexpTest_153, QuestFactory_153) {
  Regexp* lit = Regexp::NewLiteral('c', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  Regexp* quest = Regexp::Quest(lit, Regexp::LikePerl);
  ASSERT_NE(quest, nullptr);
  EXPECT_EQ(quest->op(), kRegexpQuest);
  EXPECT_EQ(quest->nsub(), 1);
  quest->Decref();
}

// Test NewLiteral factory method
TEST_F(RegexpTest_153, NewLiteralFactory_153) {
  Regexp* lit = Regexp::NewLiteral('x', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  EXPECT_EQ(lit->op(), kRegexpLiteral);
  EXPECT_EQ(lit->rune(), 'x');
  lit->Decref();
}

// Test HaveMatch factory method
TEST_F(RegexpTest_153, HaveMatchFactory_153) {
  Regexp* hm = Regexp::HaveMatch(42, Regexp::LikePerl);
  ASSERT_NE(hm, nullptr);
  EXPECT_EQ(hm->op(), kRegexpHaveMatch);
  EXPECT_EQ(hm->match_id(), 42);
  hm->Decref();
}

// Test Capture factory method
TEST_F(RegexpTest_153, CaptureFactory_153) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* cap = Regexp::Capture(lit, Regexp::LikePerl, 1);
  ASSERT_NE(cap, nullptr);
  EXPECT_EQ(cap->op(), kRegexpCapture);
  EXPECT_EQ(cap->cap(), 1);
  EXPECT_EQ(cap->nsub(), 1);
  cap->Decref();
}

// Test Concat factory method
TEST_F(RegexpTest_153, ConcatFactory_153) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  subs[2] = Regexp::NewLiteral('c', Regexp::LikePerl);
  Regexp* concat = Regexp::Concat(subs, 3, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->op(), kRegexpConcat);
  EXPECT_EQ(concat->nsub(), 3);
  concat->Decref();
}

// Test Concat with zero subs
TEST_F(RegexpTest_153, ConcatZeroSubs_153) {
  Regexp* concat = Regexp::Concat(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  EXPECT_EQ(concat->op(), kRegexpEmptyMatch);
  concat->Decref();
}

// Test Concat with one sub
TEST_F(RegexpTest_153, ConcatOneSub_153) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* concat = Regexp::Concat(&sub, 1, Regexp::LikePerl);
  ASSERT_NE(concat, nullptr);
  // With one sub, might just return the sub itself
  EXPECT_EQ(concat->op(), kRegexpLiteral);
  concat->Decref();
}

// Test Alternate factory method
TEST_F(RegexpTest_153, AlternateFactory_153) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* alt = Regexp::Alternate(subs, 2, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  alt->Decref();
}

// Test Alternate with zero subs
TEST_F(RegexpTest_153, AlternateZeroSubs_153) {
  Regexp* alt = Regexp::Alternate(nullptr, 0, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpNoMatch);
  alt->Decref();
}

// Test LiteralString factory method
TEST_F(RegexpTest_153, LiteralStringFactory_153) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* ls = Regexp::LiteralString(runes, 5, Regexp::LikePerl);
  ASSERT_NE(ls, nullptr);
  EXPECT_EQ(ls->op(), kRegexpLiteralString);
  EXPECT_EQ(ls->nrunes(), 5);
  ls->Decref();
}

// Test Repeat factory method
TEST_F(RegexpTest_153, RepeatFactory_153) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* rep = Regexp::Repeat(lit, Regexp::LikePerl, 2, 5);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->min(), 2);
  EXPECT_EQ(rep->max(), 5);
  rep->Decref();
}

// Test Repeat with unbounded max (-1)
TEST_F(RegexpTest_153, RepeatUnbounded_153) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  Regexp* rep = Regexp::Repeat(lit, Regexp::LikePerl, 3, -1);
  ASSERT_NE(rep, nullptr);
  EXPECT_EQ(rep->op(), kRegexpRepeat);
  EXPECT_EQ(rep->min(), 3);
  EXPECT_EQ(rep->max(), -1);
  rep->Decref();
}

// Test Simplify
TEST_F(RegexpTest_153, Simplify_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST_F(RegexpTest_153, SimplifyRegexpStatic_153) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test CompileToProg
TEST_F(RegexpTest_153, CompileToProg_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST_F(RegexpTest_153, CompileToReverseProg_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test RequiredPrefix
TEST_F(RegexpTest_153, RequiredPrefixTrue_153) {
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

// Test RequiredPrefix when no prefix exists
TEST_F(RegexpTest_153, RequiredPrefixFalse_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST_F(RegexpTest_153, RequiredPrefixForAccel_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  bool has = re->RequiredPrefixForAccel(&prefix, &foldcase);
  if (has) {
    EXPECT_FALSE(prefix.empty());
  }
  re->Decref();
}

// Test parse_flags accessor
TEST_F(RegexpTest_153, ParseFlagsAccessor_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp::ParseFlags flags = re->parse_flags();
  // Just ensure it doesn't crash and returns something
  (void)flags;
  re->Decref();
}

// Test simple accessor
TEST_F(RegexpTest_153, SimpleAccessor_153) {
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

// Test MimicsPCRE for a simple pattern
TEST_F(RegexpTest_153, MimicsPCRESimple_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// Test NullWalk doesn't crash
TEST_F(RegexpTest_153, NullWalkNoCrash_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_NO_FATAL_FAILURE(re->NullWalk());
  re->Decref();
}

// Test parsing character classes
TEST_F(RegexpTest_153, ParseCharacterClass_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->op(), kRegexpCharClass);
  re->Decref();
}

// Test parsing with POSIX flags
TEST_F(RegexpTest_153, ParsePOSIX_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc|def", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test AlternateNoFactor
TEST_F(RegexpTest_153, AlternateNoFactor_153) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::LikePerl);
  subs[1] = Regexp::NewLiteral('b', Regexp::LikePerl);
  Regexp* alt = Regexp::AlternateNoFactor(subs, 2, Regexp::LikePerl);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpAlternate);
  alt->Decref();
}

// Test parsing Unicode
TEST_F(RegexpTest_153, ParseUnicode_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test Ref count
TEST_F(RegexpTest_153, RefCount_153) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  // Initial ref should be 1 (or at least non-zero)
  // After Incref, it should increase
  lit->Incref();
  // We can't directly check Ref value from the interface easily,
  // but we can ensure Decref twice doesn't crash
  lit->Decref();
  lit->Decref();
}

// Test parsing a dot
TEST_F(RegexpTest_153, ParseDot_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing anchors
TEST_F(RegexpTest_153, ParseAnchors_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test parsing backreference (should fail in POSIX mode)
TEST_F(RegexpTest_153, ParseInvalidBackref_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)\\1", Regexp::POSIX, &status);
  // Backreferences are not supported in RE2's POSIX mode
  EXPECT_EQ(re, nullptr);
}

// Test a deeply nested pattern
TEST_F(RegexpTest_153, ParseDeeplyNested_153) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((((a))))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 4);
  re->Decref();
}

// Test rune accessor on a literal
TEST_F(RegexpTest_153, RuneAccessor_153) {
  Regexp* lit = Regexp::NewLiteral('Z', Regexp::LikePerl);
  ASSERT_NE(lit, nullptr);
  EXPECT_EQ(lit->rune(), 'Z');
  lit->Decref();
}

// Test runes accessor on a literal string
TEST_F(RegexpTest_153, RunesAccessor_153) {
  Rune runes[] = {'a', 'b', 'c'};
  Regexp* ls = Regexp::LiteralString(runes, 3, Regexp::LikePerl);
  ASSERT_NE(ls, nullptr);
  EXPECT_EQ(ls->nrunes(), 3);
  Rune* r = ls->runes();
  EXPECT_EQ(r[0], 'a');
  EXPECT_EQ(r[1], 'b');
  EXPECT_EQ(r[2], 'c');
  ls->Decref();
}

}  // namespace re2
