#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include <string>
#include <map>
#include <memory>

namespace re2 {

// Helper to parse and auto-decref
class RegexpPtr {
 public:
  explicit RegexpPtr(Regexp* re = nullptr) : re_(re) {}
  ~RegexpPtr() { if (re_) re_->Decref(); }
  RegexpPtr(const RegexpPtr&) = delete;
  RegexpPtr& operator=(const RegexpPtr&) = delete;
  RegexpPtr(RegexpPtr&& o) : re_(o.re_) { o.re_ = nullptr; }
  RegexpPtr& operator=(RegexpPtr&& o) {
    if (re_) re_->Decref();
    re_ = o.re_;
    o.re_ = nullptr;
    return *this;
  }
  Regexp* get() const { return re_; }
  Regexp* operator->() const { return re_; }
  explicit operator bool() const { return re_ != nullptr; }
  Regexp* release() { Regexp* r = re_; re_ = nullptr; return r; }
 private:
  Regexp* re_;
};

static Regexp::ParseFlags kDefaultFlags = Regexp::LikePerl;

// ============================================================
// Parse Tests
// ============================================================

TEST(RegexpParseTest_478, ParseSimpleLiteral_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("hello", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_478, ParseEmptyString_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_478, ParseSimpleAlternation_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a|b", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_478, ParseCharacterClass_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("[abc]", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_478, ParseRepetition_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a{3,5}", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_478, ParseStar_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a*", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_478, ParsePlus_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a+", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_478, ParseQuestion_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a?", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_478, ParseCapturingGroup_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("(abc)", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->NumCaptures(), 1);
}

TEST(RegexpParseTest_478, ParseNamedCapturingGroup_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("(?P<name>abc)", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->NumCaptures(), 1);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_TRUE(named != nullptr);
  EXPECT_EQ(named->count("name"), 1);
  delete named;
}

TEST(RegexpParseTest_478, ParseInvalidRegexp_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("(abc", kDefaultFlags, &status));
  EXPECT_TRUE(re.get() == nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_478, ParseInvalidRepetition_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("*", kDefaultFlags, &status));
  EXPECT_TRUE(re.get() == nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_478, ParseBadCharClass_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("[z-a]", kDefaultFlags, &status));
  EXPECT_TRUE(re.get() == nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_478, ParseDot_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse(".", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_478, ParseAnchorBeginEnd_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("^abc$", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpParseTest_478, ParseNestedGroups_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("((a)(b))", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
  EXPECT_EQ(re->NumCaptures(), 3);
}

TEST(RegexpParseTest_478, ParseComplexPattern_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("(?:a|b)*c+[d-f]{2,4}(?P<grp>g)?", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

// ============================================================
// ToString / Dump Tests
// ============================================================

TEST(RegexpToStringTest_478, ToStringRoundTrip_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("abc", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
}

TEST(RegexpToStringTest_478, DumpProducesOutput_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a*b+", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  std::string d = re->Dump();
  EXPECT_FALSE(d.empty());
}

// ============================================================
// NumCaptures Tests
// ============================================================

TEST(RegexpNumCapturesTest_478, ZeroCaptures_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("abc", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
}

TEST(RegexpNumCapturesTest_478, MultipleCaptures_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("(a)(b)(c)", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
}

TEST(RegexpNumCapturesTest_478, NonCapturingGroup_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("(?:abc)", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
}

// ============================================================
// NamedCaptures / CaptureNames Tests
// ============================================================

TEST(RegexpNamedCapturesTest_478, NoNamedCaptures_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("(abc)", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  // When there are no named captures, should return nullptr
  EXPECT_TRUE(named == nullptr);
  delete named;
}

TEST(RegexpNamedCapturesTest_478, HasNamedCaptures_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("(?P<foo>a)(?P<bar>b)", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_TRUE(named != nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_TRUE(named->count("foo") > 0);
  EXPECT_TRUE(named->count("bar") > 0);
  delete named;
}

TEST(RegexpCaptureNamesTest_478, CaptureNamesMapping_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("(?P<foo>a)(b)(?P<bar>c)", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_TRUE(names != nullptr);
  // Named captures should be present
  EXPECT_TRUE(names->count(1) > 0);
  EXPECT_EQ((*names)[1], "foo");
  EXPECT_TRUE(names->count(3) > 0);
  EXPECT_EQ((*names)[3], "bar");
  delete names;
}

// ============================================================
// Simplify Tests
// ============================================================

TEST(RegexpSimplifyTest_478, SimplifyBasic_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a{3}", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  RegexpPtr simplified(re->Simplify());
  ASSERT_TRUE(simplified.get() != nullptr);
}

TEST(RegexpSimplifyTest_478, SimplifyRegexpStatic_478) {
  RegexpStatus status;
  std::string dst;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", kDefaultFlags, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// ============================================================
// RequiredPrefix Tests
// ============================================================

TEST(RegexpRequiredPrefixTest_478, HasPrefix_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("^hello.*", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has) {
    EXPECT_FALSE(prefix.empty());
    if (suffix) suffix->Decref();
  }
}

TEST(RegexpRequiredPrefixTest_478, NoPrefixForAlternation_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a|b", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has);
}

// ============================================================
// Incref / Decref / Ref Tests
// ============================================================

TEST(RegexpRefTest_478, IncrefDecref_478) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", kDefaultFlags, &status);
  ASSERT_TRUE(re != nullptr);
  // Initial ref should be at least 1
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re2, re);
  // Now decref twice
  re->Decref();
  re->Decref();
}

// ============================================================
// Static Factory Tests
// ============================================================

TEST(RegexpFactoryTest_478, NewLiteral_478) {
  RegexpPtr re(Regexp::NewLiteral('a', kDefaultFlags));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'a');
}

TEST(RegexpFactoryTest_478, HaveMatch_478) {
  RegexpPtr re(Regexp::HaveMatch(42, kDefaultFlags));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
}

TEST(RegexpFactoryTest_478, LiteralString_478) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  RegexpPtr re(Regexp::LiteralString(runes, 5, kDefaultFlags));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
}

TEST(RegexpFactoryTest_478, Star_478) {
  Regexp* sub = Regexp::NewLiteral('a', kDefaultFlags);
  ASSERT_TRUE(sub != nullptr);
  RegexpPtr re(Regexp::Star(sub, kDefaultFlags));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
}

TEST(RegexpFactoryTest_478, Plus_478) {
  Regexp* sub = Regexp::NewLiteral('a', kDefaultFlags);
  ASSERT_TRUE(sub != nullptr);
  RegexpPtr re(Regexp::Plus(sub, kDefaultFlags));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
}

TEST(RegexpFactoryTest_478, Quest_478) {
  Regexp* sub = Regexp::NewLiteral('a', kDefaultFlags);
  ASSERT_TRUE(sub != nullptr);
  RegexpPtr re(Regexp::Quest(sub, kDefaultFlags));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
}

TEST(RegexpFactoryTest_478, Repeat_478) {
  Regexp* sub = Regexp::NewLiteral('a', kDefaultFlags);
  ASSERT_TRUE(sub != nullptr);
  RegexpPtr re(Regexp::Repeat(sub, kDefaultFlags, 2, 5));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
}

TEST(RegexpFactoryTest_478, Capture_478) {
  Regexp* sub = Regexp::NewLiteral('a', kDefaultFlags);
  ASSERT_TRUE(sub != nullptr);
  RegexpPtr re(Regexp::Capture(sub, kDefaultFlags, 1));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
}

TEST(RegexpFactoryTest_478, Concat_478) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', kDefaultFlags);
  subs[1] = Regexp::NewLiteral('b', kDefaultFlags);
  RegexpPtr re(Regexp::Concat(subs, 2, kDefaultFlags));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
}

TEST(RegexpFactoryTest_478, ConcatSingle_478) {
  Regexp* subs[1];
  subs[0] = Regexp::NewLiteral('a', kDefaultFlags);
  RegexpPtr re(Regexp::Concat(subs, 1, kDefaultFlags));
  ASSERT_TRUE(re.get() != nullptr);
  // Single element concat may simplify to the element itself
}

TEST(RegexpFactoryTest_478, Alternate_478) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', kDefaultFlags);
  subs[1] = Regexp::NewLiteral('b', kDefaultFlags);
  RegexpPtr re(Regexp::Alternate(subs, 2, kDefaultFlags));
  ASSERT_TRUE(re.get() != nullptr);
}

TEST(RegexpFactoryTest_478, AlternateNoFactor_478) {
  Regexp* subs[2];
  subs[0] = Regexp::NewLiteral('a', kDefaultFlags);
  subs[1] = Regexp::NewLiteral('b', kDefaultFlags);
  RegexpPtr re(Regexp::AlternateNoFactor(subs, 2, kDefaultFlags));
  ASSERT_TRUE(re.get() != nullptr);
}

// ============================================================
// FUZZING_ONLY_set_maximum_repeat_count Tests
// ============================================================

TEST(RegexpFuzzingTest_478, SetMaximumRepeatCount_478) {
  // Save original and set a custom value
  // After setting a low repeat count, large repeats should fail to parse
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(10);

  RegexpStatus status;
  // Attempt to parse a repeat larger than the max
  RegexpPtr re(Regexp::Parse("a{100}", kDefaultFlags, &status));
  EXPECT_TRUE(re.get() == nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);

  // Restore to default
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(1000);
}

TEST(RegexpFuzzingTest_478, SetMaximumRepeatCountAllowsSmall_478) {
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(10);

  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a{5}", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);

  Regexp::FUZZING_ONLY_set_maximum_repeat_count(1000);
}

TEST(RegexpFuzzingTest_478, DefaultRepeatCountAllowsThousand_478) {
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(1000);

  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a{999}", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

// ============================================================
// Compile Tests
// ============================================================

TEST(RegexpCompileTest_478, CompileToProg_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a*b", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_TRUE(prog != nullptr);
  delete prog;
}

TEST(RegexpCompileTest_478, CompileToReverseProg_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a*b", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  EXPECT_TRUE(prog != nullptr);
  delete prog;
}

// ============================================================
// Parse Flags Tests
// ============================================================

TEST(RegexpParseFlagsTest_478, CaseInsensitive_478) {
  RegexpStatus status;
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      kDefaultFlags | Regexp::FoldCase);
  RegexpPtr re(Regexp::Parse("abc", flags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpParseFlagsTest_478, PosixSyntax_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("[[:alpha:]]", Regexp::PerlX, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

// ============================================================
// Escaping / Special Characters
// ============================================================

TEST(RegexpParseEscapeTest_478, EscapedDot_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("\\.", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpParseEscapeTest_478, UnicodeEscape_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("\\x{41}", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpParseEscapeTest_478, WordBoundary_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("\\bword\\b", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

// ============================================================
// Boundary / Edge Cases
// ============================================================

TEST(RegexpBoundaryTest_478, RepeatZeroZero_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a{0,0}", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpBoundaryTest_478, RepeatZeroMax_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a{0,1000}", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpBoundaryTest_478, EmptyAlternation_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("|", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpBoundaryTest_478, NestedRepetition_478) {
  RegexpStatus status;
  // In Perl mode, nested repetitions like (a*)* should work
  RegexpPtr re(Regexp::Parse("(a*)*", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpBoundaryTest_478, VeryLongLiteral_478) {
  std::string long_str(1000, 'a');
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse(long_str, kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

TEST(RegexpBoundaryTest_478, UnbalancedBracket_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("[abc", kDefaultFlags, &status));
  EXPECT_TRUE(re.get() == nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

TEST(RegexpBoundaryTest_478, UnbalancedParen_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("abc)", kDefaultFlags, &status));
  EXPECT_TRUE(re.get() == nullptr);
  EXPECT_NE(status.code(), kRegexpSuccess);
}

// ============================================================
// MimicsPCRE Tests
// ============================================================

TEST(RegexpMimicsPCRETest_478, SimpleLiteralMimicsPCRE_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("abc", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  // Simple literals should mimic PCRE
  EXPECT_TRUE(re->MimicsPCRE());
}

// ============================================================
// NullWalk Test
// ============================================================

TEST(RegexpNullWalkTest_478, NullWalkDoesNotCrash_478) {
  RegexpStatus status;
  RegexpPtr re(Regexp::Parse("a*b+c?", kDefaultFlags, &status));
  ASSERT_TRUE(re.get() != nullptr);
  // NullWalk should not crash
  re->NullWalk();
}

}  // namespace re2
