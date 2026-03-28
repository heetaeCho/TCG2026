#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

// Helper to parse a regexp and return it (caller must Decref)
static Regexp* ParseRegexp(const char* pattern, Regexp::ParseFlags flags = Regexp::LikePerl) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, flags, &status);
  return re;
}

// Test basic Parse and Decref
TEST(RegexpTest_336, ParseSimpleLiteral_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

// Test Incref and Decref reference counting
TEST(RegexpTest_336, IncrefDecref_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Initial ref should be 1
  // Incref should return the same pointer and increase ref
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  // After Incref, ref count should be 2
  // Decref twice to properly clean up
  re->Decref();
  re2->Decref();
}

// Test Ref() returns the current reference count
TEST(RegexpTest_336, RefCount_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->Ref(), 1);
  re->Incref();
  EXPECT_EQ(re->Ref(), 2);
  re->Decref();
  EXPECT_EQ(re->Ref(), 1);
  re->Decref();
}

// Test multiple Incref/Decref cycles
TEST(RegexpTest_336, MultipleIncrefDecref_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  for (int i = 0; i < 100; i++) {
    re->Incref();
  }
  EXPECT_EQ(re->Ref(), 101);
  for (int i = 0; i < 100; i++) {
    re->Decref();
  }
  EXPECT_EQ(re->Ref(), 1);
  re->Decref();
}

// Test Parse with empty string
TEST(RegexpTest_336, ParseEmptyString_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Parse with invalid regex
TEST(RegexpTest_336, ParseInvalidRegex_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

// Test Parse with another invalid regex - unmatched bracket
TEST(RegexpTest_336, ParseUnmatchedBracket_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

// Test ToString roundtrip
TEST(RegexpTest_336, ToString_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Dump
TEST(RegexpTest_336, Dump_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
  re->Decref();
}

// Test NumCaptures with no captures
TEST(RegexpTest_336, NumCapturesNone_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test NumCaptures with captures
TEST(RegexpTest_336, NumCapturesMultiple_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested captures
TEST(RegexpTest_336, NumCapturesNested_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NamedCaptures
TEST(RegexpTest_336, NamedCaptures_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>a)(?P<value>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_EQ((*named)["name"], 1);
  EXPECT_EQ((*named)["value"], 2);
  delete named;
  re->Decref();
}

// Test NamedCaptures with no named groups
TEST(RegexpTest_336, NamedCapturesNone_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  EXPECT_EQ(named, nullptr);
  re->Decref();
}

// Test CaptureNames
TEST(RegexpTest_336, CaptureNames_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>a)(b)(?P<value>c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ((*names)[1], "name");
  EXPECT_EQ((*names)[3], "value");
  delete names;
  re->Decref();
}

// Test NewLiteral
TEST(RegexpTest_336, NewLiteral_336) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
  re->Decref();
}

// Test HaveMatch
TEST(RegexpTest_336, HaveMatch_336) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test Plus
TEST(RegexpTest_336, Plus_336) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Star
TEST(RegexpTest_336, Star_336) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Quest
TEST(RegexpTest_336, Quest_336) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Quest(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test Capture
TEST(RegexpTest_336, Capture_336) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  re->Decref();
}

// Test Concat
TEST(RegexpTest_336, Concat_336) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Concat with single element
TEST(RegexpTest_336, ConcatSingle_336) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Concat with zero elements
TEST(RegexpTest_336, ConcatEmpty_336) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate
TEST(RegexpTest_336, Alternate_336) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Alternate with single element
TEST(RegexpTest_336, AlternateSingle_336) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Alternate(subs, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test AlternateNoFactor
TEST(RegexpTest_336, AlternateNoFactor_336) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  Regexp* re = Regexp::AlternateNoFactor(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test Repeat
TEST(RegexpTest_336, Repeat_336) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test LiteralString
TEST(RegexpTest_336, LiteralString_336) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test Simplify
TEST(RegexpTest_336, Simplify_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp
TEST(RegexpTest_336, SimplifyRegexp_336) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test SimplifyRegexp with invalid pattern
TEST(RegexpTest_336, SimplifyRegexpInvalid_336) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("(", Regexp::LikePerl, &dst, &status);
  EXPECT_FALSE(ok);
}

// Test CompileToProg
TEST(RegexpTest_336, CompileToProg_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST(RegexpTest_336, CompileToReverseProg_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test RequiredPrefix
TEST(RegexpTest_336, RequiredPrefix_336) {
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

// Test RequiredPrefix when there's no required prefix
TEST(RegexpTest_336, RequiredPrefixNone_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*b", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST(RegexpTest_336, RequiredPrefixForAccel_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  re->RequiredPrefixForAccel(&prefix, &foldcase);
  re->Decref();
}

// Test op() accessor
TEST(RegexpTest_336, OpAccessor_336) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test parse_flags() accessor
TEST(RegexpTest_336, ParseFlagsAccessor_336) {
  Regexp* re = Regexp::NewLiteral('x', Regexp::FoldCase);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->parse_flags() & Regexp::FoldCase);
  re->Decref();
}

// Test NullWalk doesn't crash
TEST(RegexpTest_336, NullWalk_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();
  re->Decref();
}

// Test complex regex parse
TEST(RegexpTest_336, ParseComplexRegex_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a|b)*c+[d-f]?\\d{2,4}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  re->Decref();
}

// Test many Incref to trigger kMaxRef behavior
TEST(RegexpTest_336, ManyIncrefDecref_336) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  
  // Incref many times (enough to potentially trigger kMaxRef path)
  const int kCount = 70000;  // uint16_t max is 65535
  for (int i = 0; i < kCount; i++) {
    re->Incref();
  }
  
  // Decref all the extra refs
  for (int i = 0; i < kCount; i++) {
    re->Decref();
  }
  
  EXPECT_EQ(re->Ref(), 1);
  re->Decref();
}

// Test Parse with POSIX flags
TEST(RegexpTest_336, ParsePosixFlags_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test that Decref on a freshly created Regexp (ref=1) destroys it
// We verify indirectly by creating, incref-ing, then decref-ing twice
TEST(RegexpTest_336, DecrefDestroysAtZero_336) {
  Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  re->Incref();
  EXPECT_EQ(re->Ref(), 2);
  re->Decref();
  EXPECT_EQ(re->Ref(), 1);
  // Final Decref should destroy - no crash means success
  re->Decref();
}

// Test MimicsPCRE
TEST(RegexpTest_336, MimicsPCRE_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple regex should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// Test ToString roundtrip for various patterns
TEST(RegexpTest_336, ToStringRoundtrip_336) {
  RegexpStatus status;
  // Simple pattern
  Regexp* re = Regexp::Parse("a+b*c?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string str = re->ToString();
  EXPECT_FALSE(str.empty());
  
  // Parse the result again
  RegexpStatus status2;
  Regexp* re2 = Regexp::Parse(str, Regexp::LikePerl, &status2);
  ASSERT_NE(re2, nullptr);
  
  re->Decref();
  re2->Decref();
}

// Test Repeat with unbounded max (-1)
TEST(RegexpTest_336, RepeatUnbounded_336) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 3, -1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 3);
  EXPECT_EQ(re->max(), -1);
  re->Decref();
}

// Test Repeat with min == max
TEST(RegexpTest_336, RepeatExact_336) {
  Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 5, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->min(), 5);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test simple() accessor
TEST(RegexpTest_336, SimpleAccessor_336) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Just verify it doesn't crash; value depends on implementation
  re->simple();
  re->Decref();
}

// Test nsub() accessor
TEST(RegexpTest_336, NsubAccessor_336) {
  Regexp* subs[3];
  subs[0] = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  subs[1] = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  subs[2] = Regexp::NewLiteral('c', Regexp::NoParseFlags);
  Regexp* re = Regexp::Concat(subs, 3, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 3);
  re->Decref();
}

// Test FUZZING_ONLY_set_maximum_repeat_count
TEST(RegexpTest_336, FuzzingSetMaxRepeatCount_336) {
  // Just verify it doesn't crash
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(100);
  // Reset to a reasonable value
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(1000);
}

}  // namespace re2
