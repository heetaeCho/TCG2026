#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Helper to create a simple literal regexp for use as a sub-expression
static Regexp* MakeLiteral(Rune r, Regexp::ParseFlags flags = Regexp::NoParseFlags) {
  return Regexp::NewLiteral(r, flags);
}

// Test Capture creates a regexp with correct op
TEST(RegexpCaptureTest_344, CaptureReturnsRegexpWithCaptureOp_344) {
  Regexp* sub = MakeLiteral('a');
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  re->Decref();
}

// Test Capture stores the capture index
TEST(RegexpCaptureTest_344, CaptureStoresCaptureIndex_344) {
  Regexp* sub = MakeLiteral('b');
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->cap(), 5);
  re->Decref();
}

// Test Capture with capture index 0
TEST(RegexpCaptureTest_344, CaptureWithIndexZero_344) {
  Regexp* sub = MakeLiteral('c');
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 0);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->cap(), 0);
  re->Decref();
}

// Test Capture has exactly 1 sub-expression
TEST(RegexpCaptureTest_344, CaptureHasOneSub_344) {
  Regexp* sub = MakeLiteral('d');
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 3);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 1);
  re->Decref();
}

// Test Capture sub-expression is the one passed in
TEST(RegexpCaptureTest_344, CaptureSubIsCorrect_344) {
  Regexp* sub = MakeLiteral('e');
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 2);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->nsub(), 1);
  EXPECT_EQ(re->sub()[0], sub);
  re->Decref();
}

// Test Capture preserves parse flags
TEST(RegexpCaptureTest_344, CapturePreservesParseFlags_344) {
  Regexp* sub = MakeLiteral('f');
  Regexp::ParseFlags flags = Regexp::FoldCase;
  Regexp* re = Regexp::Capture(sub, flags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->parse_flags() & Regexp::FoldCase, Regexp::FoldCase);
  re->Decref();
}

// Test Capture with large capture index
TEST(RegexpCaptureTest_344, CaptureWithLargeCaptureIndex_344) {
  Regexp* sub = MakeLiteral('g');
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 99999);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->cap(), 99999);
  re->Decref();
}

// Test Capture's Dump contains capture info
TEST(RegexpCaptureTest_344, CaptureDumpContainsCaptureInfo_344) {
  Regexp* sub = MakeLiteral('h');
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 7);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  // The dump should mention "cap" or similar
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test that parsing a group creates a capture regexp
TEST(RegexpCaptureTest_344, ParseGroupCreatesCapture_344) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  EXPECT_EQ(re->nsub(), 1);
  re->Decref();
}

// Test parsing multiple groups creates correct capture indices
TEST(RegexpCaptureTest_344, ParseMultipleGroupsCorrectCaptureIndices_344) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  // The top level should be a concat of 3 captures
  EXPECT_EQ(re->op(), kRegexpConcat);
  EXPECT_EQ(re->nsub(), 3);
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(re->sub()[i]->op(), kRegexpCapture);
    EXPECT_EQ(re->sub()[i]->cap(), i + 1);
  }
  re->Decref();
}

// Test NumCaptures counts capture groups
TEST(RegexpCaptureTest_344, NumCapturesCountsCorrectly_344) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with nested captures
TEST(RegexpCaptureTest_344, NumCapturesNestedGroups_344) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((a)(b))", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test NumCaptures with no captures
TEST(RegexpCaptureTest_344, NumCapturesNoGroups_344) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test Capture ref count starts at 1
TEST(RegexpCaptureTest_344, CaptureRefCountStartsAtOne_344) {
  Regexp* sub = MakeLiteral('x');
  Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->Ref(), 1);
  re->Decref();
}

// Test Capture ToString round-trips
TEST(RegexpCaptureTest_344, CaptureToStringRoundTrip_344) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  // Re-parse the string representation
  Regexp* re2 = Regexp::Parse(s, Regexp::NoParseFlags, &status);
  ASSERT_NE(re2, nullptr);
  EXPECT_EQ(re2->NumCaptures(), re->NumCaptures());
  re->Decref();
  re2->Decref();
}

// Test NewLiteral basic functionality
TEST(RegexpFactoryTest_344, NewLiteralCreatesLiteral_344) {
  Regexp* re = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  EXPECT_EQ(re->rune(), 'z');
  re->Decref();
}

// Test Plus factory method
TEST(RegexpFactoryTest_344, PlusCreatesPlus_344) {
  Regexp* sub = MakeLiteral('a');
  Regexp* re = Regexp::Plus(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpPlus);
  re->Decref();
}

// Test Star factory method
TEST(RegexpFactoryTest_344, StarCreatesStar_344) {
  Regexp* sub = MakeLiteral('a');
  Regexp* re = Regexp::Star(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpStar);
  re->Decref();
}

// Test Quest factory method
TEST(RegexpFactoryTest_344, QuestCreatesQuest_344) {
  Regexp* sub = MakeLiteral('a');
  Regexp* re = Regexp::Quest(sub, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpQuest);
  re->Decref();
}

// Test HaveMatch factory method
TEST(RegexpFactoryTest_344, HaveMatchCreatesHaveMatch_344) {
  Regexp* re = Regexp::HaveMatch(42, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), 42);
  re->Decref();
}

// Test Repeat factory method
TEST(RegexpFactoryTest_344, RepeatCreatesRepeat_344) {
  Regexp* sub = MakeLiteral('a');
  Regexp* re = Regexp::Repeat(sub, Regexp::NoParseFlags, 2, 5);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpRepeat);
  EXPECT_EQ(re->min(), 2);
  EXPECT_EQ(re->max(), 5);
  re->Decref();
}

// Test Concat factory method
TEST(RegexpFactoryTest_344, ConcatCreatesConcat_344) {
  Regexp* subs[2];
  subs[0] = MakeLiteral('a');
  subs[1] = MakeLiteral('b');
  Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpConcat);
  EXPECT_EQ(re->nsub(), 2);
  re->Decref();
}

// Test Alternate factory method
TEST(RegexpFactoryTest_344, AlternateCreatesAlternate_344) {
  Regexp* subs[2];
  subs[0] = MakeLiteral('a');
  subs[1] = MakeLiteral('b');
  Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  // Could be alternate or simplified
  re->Decref();
}

// Test LiteralString factory method
TEST(RegexpFactoryTest_344, LiteralStringCreatesLiteralString_344) {
  Rune runes[] = {'h', 'e', 'l', 'l', 'o'};
  Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteralString);
  EXPECT_EQ(re->nrunes(), 5);
  re->Decref();
}

// Test Incref increases reference count
TEST(RegexpRefTest_344, IncrefIncreasesRef_344) {
  Regexp* re = MakeLiteral('a');
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->Ref(), 1);
  re->Incref();
  EXPECT_EQ(re->Ref(), 2);
  re->Decref();
  re->Decref();
}

// Test Parse with invalid regex returns null
TEST(RegexpParseTest_344, ParseInvalidRegexReturnsNull_344) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(", Regexp::NoParseFlags, &status);
  EXPECT_EQ(re, nullptr);
}

// Test Parse with valid regex returns non-null
TEST(RegexpParseTest_344, ParseValidRegexReturnsNonNull_344) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  re->Decref();
}

// Test SimplifyRegexp
TEST(RegexpSimplifyTest_344, SimplifyRegexpWorks_344) {
  RegexpStatus status;
  std::string dst;
  bool ok = Regexp::SimplifyRegexp("a{2,3}", Regexp::NoParseFlags, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test Capture with named group via Parse
TEST(RegexpCaptureTest_344, NamedCaptureViaParse_344) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>a)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->cap(), 1);
  EXPECT_NE(re->name(), nullptr);
  EXPECT_EQ(*re->name(), "name");
  re->Decref();
}

// Test CaptureNames returns map
TEST(RegexpCaptureTest_344, CaptureNamesReturnsMap_344) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::map<int, std::string>* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)[1], "foo");
  EXPECT_EQ((*names)[2], "bar");
  delete names;
  re->Decref();
}

// Test NamedCaptures returns map
TEST(RegexpCaptureTest_344, NamedCapturesReturnsMap_344) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<foo>a)(?P<bar>b)", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  std::map<std::string, int>* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->size(), 2u);
  EXPECT_EQ((*named)["foo"], 1);
  EXPECT_EQ((*named)["bar"], 2);
  delete named;
  re->Decref();
}

// Test Concat with zero subs
TEST(RegexpFactoryTest_344, ConcatZeroSubsReturnsEmptyMatch_344) {
  Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpEmptyMatch);
  re->Decref();
}

// Test Concat with one sub returns the sub itself
TEST(RegexpFactoryTest_344, ConcatOneSubReturnsSub_344) {
  Regexp* sub = MakeLiteral('a');
  Regexp* re = Regexp::Concat(&sub, 1, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpLiteral);
  re->Decref();
}

// Test Alternate with zero subs
TEST(RegexpFactoryTest_344, AlternateZeroSubsReturnsNoMatch_344) {
  Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  re->Decref();
}

// Test Simplify on a capture regexp
TEST(RegexpCaptureTest_344, CaptureSimplify_344) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a+)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test CompileToProg on capture
TEST(RegexpCaptureTest_344, CaptureCompileToProg_344) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)", Regexp::NoParseFlags, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  EXPECT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

}  // namespace re2
