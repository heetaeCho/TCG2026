// File: re2_regexp_top_equal_test_349.cc
#include "gtest/gtest.h"
#include "re2/regexp.h"

using re2::Regexp;

namespace {

// Small helper to call the public testing-only comparator from the interface.
// We don't assume anything about internal ownership beyond what's observable.
static bool TopEqualViaAPI(Regexp* a, Regexp* b) {
  Regexp* invoker = Regexp::NewLiteral('x', Regexp::Regexp::NoParseFlags);
  bool eq = invoker->RegexpEqualTestingOnly(a, b);
  invoker->Decref();
  return eq;
}

// Convenience parser that must succeed for these tests.
static Regexp* MustParse(const std::string& pat,
                         Regexp::ParseFlags flags = Regexp::Regexp::NoParseFlags) {
  re2::RegexpStatus status;
  Regexp* re = Regexp::Parse(pat, flags, &status);
  EXPECT_NE(re, nullptr) << "Parse failed for pattern: " << pat;
  return re;
}

}  // namespace

// ---------- kRegexpLiteral ----------

TEST(RegexpTopEqualTest_349, Literal_SameRuneSameFlags_AreEqual_349) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* b = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  ASSERT_TRUE(TopEqualViaAPI(a, b));
  a->Decref();
  b->Decref();
}

TEST(RegexpTopEqualTest_349, Literal_SameRuneDifferentFoldCase_NotEqual_349) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* b = Regexp::NewLiteral('a', Regexp::Regexp::FoldCase);
  ASSERT_FALSE(TopEqualViaAPI(a, b));
  a->Decref();
  b->Decref();
}

TEST(RegexpTopEqualTest_349, Literal_DifferentRune_NotEqual_349) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* b = Regexp::NewLiteral('b', Regexp::Regexp::NoParseFlags);
  ASSERT_FALSE(TopEqualViaAPI(a, b));
  a->Decref();
  b->Decref();
}

// ---------- kRegexpLiteralString ----------

TEST(RegexpTopEqualTest_349, LiteralString_SameRunesSameFlags_AreEqual_349) {
  Rune r1[] = {'h','i'};
  Rune r2[] = {'h','i'};
  Regexp* a = Regexp::LiteralString(r1, 2, Regexp::Regexp::NoParseFlags);
  Regexp* b = Regexp::LiteralString(r2, 2, Regexp::Regexp::NoParseFlags);
  ASSERT_TRUE(TopEqualViaAPI(a, b));
  a->Decref();
  b->Decref();
}

TEST(RegexpTopEqualTest_349, LiteralString_DifferentContent_NotEqual_349) {
  Rune r1[] = {'h','i'};
  Rune r2[] = {'b','y','e'};
  Regexp* a = Regexp::LiteralString(r1, 2, Regexp::Regexp::NoParseFlags);
  Regexp* b = Regexp::LiteralString(r2, 3, Regexp::Regexp::NoParseFlags);
  ASSERT_FALSE(TopEqualViaAPI(a, b));
  a->Decref();
  b->Decref();
}

TEST(RegexpTopEqualTest_349, LiteralString_DifferentFoldCase_NotEqual_349) {
  Rune r[] = {'a'};
  Regexp* a = Regexp::LiteralString(r, 1, Regexp::Regexp::NoParseFlags);
  Regexp* b = Regexp::LiteralString(r, 1, Regexp::Regexp::FoldCase);
  ASSERT_FALSE(TopEqualViaAPI(a, b));
  a->Decref();
  b->Decref();
}

// ---------- kRegexpAlternate / kRegexpConcat (top-level: nsub only) ----------

TEST(RegexpTopEqualTest_349, Alternate_SameArity_AreEqual_349) {
  // Build two alternations with identical arity (2). Subtrees themselves do not
  // matter for top-level equality (we still give matching shapes).
  Regexp* s1a = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* s1b = Regexp::NewLiteral('b', Regexp::Regexp::NoParseFlags);
  Regexp* subs1[] = {s1a, s1b};
  Regexp* alt1 = Regexp::Alternate(subs1, 2, Regexp::Regexp::NoParseFlags);

  Regexp* s2a = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* s2b = Regexp::NewLiteral('b', Regexp::Regexp::NoParseFlags);
  Regexp* subs2[] = {s2a, s2b};
  Regexp* alt2 = Regexp::Alternate(subs2, 2, Regexp::Regexp::NoParseFlags);

  ASSERT_TRUE(TopEqualViaAPI(alt1, alt2));
  alt1->Decref();
  alt2->Decref();
}

TEST(RegexpTopEqualTest_349, Alternate_DifferentArity_NotEqual_349) {
  Regexp* s1 = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* subs1[] = {s1};
  Regexp* alt1 = Regexp::Alternate(subs1, 1, Regexp::Regexp::NoParseFlags);

  Regexp* s2a = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* s2b = Regexp::NewLiteral('b', Regexp::Regexp::NoParseFlags);
  Regexp* subs2[] = {s2a, s2b};
  Regexp* alt2 = Regexp::Alternate(subs2, 2, Regexp::Regexp::NoParseFlags);

  ASSERT_FALSE(TopEqualViaAPI(alt1, alt2));
  alt1->Decref();
  alt2->Decref();
}

TEST(RegexpTopEqualTest_349, Concat_SameArity_AreEqual_349) {
  Regexp* a1 = Regexp::NewLiteral('x', Regexp::Regexp::NoParseFlags);
  Regexp* a2 = Regexp::NewLiteral('y', Regexp::Regexp::NoParseFlags);
  Regexp* csubs1[] = {a1, a2};
  Regexp* c1 = Regexp::Concat(csubs1, 2, Regexp::Regexp::NoParseFlags);

  Regexp* b1 = Regexp::NewLiteral('x', Regexp::Regexp::NoParseFlags);
  Regexp* b2 = Regexp::NewLiteral('y', Regexp::Regexp::NoParseFlags);
  Regexp* csubs2[] = {b1, b2};
  Regexp* c2 = Regexp::Concat(csubs2, 2, Regexp::Regexp::NoParseFlags);

  ASSERT_TRUE(TopEqualViaAPI(c1, c2));
  c1->Decref();
  c2->Decref();
}

TEST(RegexpTopEqualTest_349, Concat_DifferentArity_NotEqual_349) {
  Regexp* a1 = Regexp::NewLiteral('x', Regexp::Regexp::NoParseFlags);
  Regexp* csubs1[] = {a1};
  Regexp* c1 = Regexp::Concat(csubs1, 1, Regexp::Regexp::NoParseFlags);

  Regexp* b1 = Regexp::NewLiteral('x', Regexp::Regexp::NoParseFlags);
  Regexp* b2 = Regexp::NewLiteral('y', Regexp::Regexp::NoParseFlags);
  Regexp* csubs2[] = {b1, b2};
  Regexp* c2 = Regexp::Concat(csubs2, 2, Regexp::Regexp::NoParseFlags);

  ASSERT_FALSE(TopEqualViaAPI(c1, c2));
  c1->Decref();
  c2->Decref();
}

// ---------- kRegexpStar / kRegexpPlus / kRegexpQuest (NonGreedy bit only) ----------

TEST(RegexpTopEqualTest_349, Star_NonGreedyFlagMatters_349) {
  Regexp* s1 = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* greedy  = Regexp::Star(s1, Regexp::Regexp::NoParseFlags);

  Regexp* s2 = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* nongreedy = Regexp::Star(s2, Regexp::Regexp::NonGreedy);

  ASSERT_FALSE(TopEqualViaAPI(greedy, nongreedy));

  Regexp* s3 = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* greedy2 = Regexp::Star(s3, Regexp::Regexp::NoParseFlags);
  ASSERT_TRUE(TopEqualViaAPI(greedy, greedy2));

  greedy->Decref();
  nongreedy->Decref();
  greedy2->Decref();
}

TEST(RegexpTopEqualTest_349, Plus_NonGreedyFlagMatters_349) {
  Regexp* a1 = Regexp::NewLiteral('x', Regexp::Regexp::NoParseFlags);
  Regexp* p1 = Regexp::Plus(a1, Regexp::Regexp::NoParseFlags);

  Regexp* a2 = Regexp::NewLiteral('x', Regexp::Regexp::NoParseFlags);
  Regexp* p2 = Regexp::Plus(a2, Regexp::Regexp::NonGreedy);

  ASSERT_FALSE(TopEqualViaAPI(p1, p2));
  p1->Decref();
  p2->Decref();
}

TEST(RegexpTopEqualTest_349, Quest_NonGreedyFlagMatters_349) {
  Regexp* a1 = Regexp::NewLiteral('x', Regexp::Regexp::NoParseFlags);
  Regexp* q1 = Regexp::Quest(a1, Regexp::Regexp::NoParseFlags);

  Regexp* a2 = Regexp::NewLiteral('x', Regexp::Regexp::NoParseFlags);
  Regexp* q2 = Regexp::Quest(a2, Regexp::Regexp::NonGreedy);

  ASSERT_FALSE(TopEqualViaAPI(q1, q2));
  q1->Decref();
  q2->Decref();
}

// ---------- kRegexpRepeat (min/max + NonGreedy) ----------

TEST(RegexpTopEqualTest_349, Repeat_SameBoundsSameGreediness_AreEqual_349) {
  Regexp* s1 = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* r1 = Regexp::Repeat(s1, Regexp::Regexp::NoParseFlags, 2, 5);

  Regexp* s2 = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* r2 = Regexp::Repeat(s2, Regexp::Regexp::NoParseFlags, 2, 5);

  ASSERT_TRUE(TopEqualViaAPI(r1, r2));
  r1->Decref();
  r2->Decref();
}

TEST(RegexpTopEqualTest_349, Repeat_DifferentBounds_NotEqual_349) {
  Regexp* s1 = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* r1 = Regexp::Repeat(s1, Regexp::Regexp::NoParseFlags, 1, 3);

  Regexp* s2 = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* r2 = Regexp::Repeat(s2, Regexp::Regexp::NoParseFlags, 1, 4);

  ASSERT_FALSE(TopEqualViaAPI(r1, r2));
  r1->Decref();
  r2->Decref();
}

TEST(RegexpTopEqualTest_349, Repeat_DifferentGreediness_NotEqual_349) {
  Regexp* s1 = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* r1 = Regexp::Repeat(s1, Regexp::Regexp::NoParseFlags, 2, 2);

  Regexp* s2 = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* r2 = Regexp::Repeat(s2, Regexp::Regexp::NonGreedy, 2, 2);

  ASSERT_FALSE(TopEqualViaAPI(r1, r2));
  r1->Decref();
  r2->Decref();
}

// ---------- kRegexpCapture (cap and optional name) ----------

TEST(RegexpTopEqualTest_349, Capture_UnnamedSameCap_AreEqual_349) {
  Regexp* s1 = Regexp::NewLiteral('x', Regexp::Regexp::NoParseFlags);
  Regexp* c1 = Regexp::Capture(s1, Regexp::Regexp::NoParseFlags, /*cap=*/1);

  Regexp* s2 = Regexp::NewLiteral('y', Regexp::Regexp::NoParseFlags);
  Regexp* c2 = Regexp::Capture(s2, Regexp::Regexp::NoParseFlags, /*cap=*/1);

  ASSERT_TRUE(TopEqualViaAPI(c1, c2));
  c1->Decref();
  c2->Decref();
}

TEST(RegexpTopEqualTest_349, Capture_UnnamedDifferentCap_NotEqual_349) {
  Regexp* s1 = Regexp::NewLiteral('x', Regexp::Regexp::NoParseFlags);
  Regexp* c1 = Regexp::Capture(s1, Regexp::Regexp::NoParseFlags, /*cap=*/1);

  Regexp* s2 = Regexp::NewLiteral('y', Regexp::Regexp::NoParseFlags);
  Regexp* c2 = Regexp::Capture(s2, Regexp::Regexp::NoParseFlags, /*cap=*/2);

  ASSERT_FALSE(TopEqualViaAPI(c1, c2));
  c1->Decref();
  c2->Decref();
}

TEST(RegexpTopEqualTest_349, Capture_NamedSameCapName_AreEqual_349) {
  // Build named-capture top-level nodes via parsing.
  Regexp* c1 = MustParse("(?P<g>a)");
  Regexp* c2 = MustParse("(?P<g>b)");
  ASSERT_TRUE(TopEqualViaAPI(c1, c2));
  c1->Decref();
  c2->Decref();
}

TEST(RegexpTopEqualTest_349, Capture_NamedDifferentName_NotEqual_349) {
  Regexp* c1 = MustParse("(?P<left>a)");
  Regexp* c2 = MustParse("(?P<right>a)");
  ASSERT_FALSE(TopEqualViaAPI(c1, c2));
  c1->Decref();
  c2->Decref();
}

TEST(RegexpTopEqualTest_349, Capture_NamedVsUnnamed_NotEqual_349) {
  Regexp* named = MustParse("(?P<n>a)");
  Regexp* sub = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* unnamed = Regexp::Capture(sub, Regexp::Regexp::NoParseFlags, /*cap=*/1);
  ASSERT_FALSE(TopEqualViaAPI(named, unnamed));
  named->Decref();
  unnamed->Decref();
}

// ---------- kRegexpHaveMatch (match_id only) ----------

TEST(RegexpTopEqualTest_349, HaveMatch_SameId_AreEqual_349) {
  Regexp* a = Regexp::HaveMatch(7, Regexp::Regexp::NoParseFlags);
  Regexp* b = Regexp::HaveMatch(7, Regexp::Regexp::NoParseFlags);
  ASSERT_TRUE(TopEqualViaAPI(a, b));
  a->Decref();
  b->Decref();
}

TEST(RegexpTopEqualTest_349, HaveMatch_DifferentId_NotEqual_349) {
  Regexp* a = Regexp::HaveMatch(7, Regexp::Regexp::NoParseFlags);
  Regexp* b = Regexp::HaveMatch(8, Regexp::Regexp::NoParseFlags);
  ASSERT_FALSE(TopEqualViaAPI(a, b));
  a->Decref();
  b->Decref();
}

// ---------- kRegexpCharClass (content equality) ----------

TEST(RegexpTopEqualTest_349, CharClass_SameRanges_AreEqual_349) {
  Regexp* a = MustParse("[a-c]");
  Regexp* b = MustParse("[a-c]");
  ASSERT_TRUE(TopEqualViaAPI(a, b));
  a->Decref();
  b->Decref();
}

TEST(RegexpTopEqualTest_349, CharClass_DifferentRanges_NotEqual_349) {
  Regexp* a = MustParse("[a-c]");
  Regexp* b = MustParse("[b-d]");
  ASSERT_FALSE(TopEqualViaAPI(a, b));
  a->Decref();
  b->Decref();
}

// ---------- Anchors / simple ops (top-level equal if op matches) ----------

TEST(RegexpTopEqualTest_349, BeginLine_WithBeginLine_AreEqual_349) {
  Regexp* a = MustParse("^");
  Regexp* b = MustParse("^");
  ASSERT_TRUE(TopEqualViaAPI(a, b));
  a->Decref();
  b->Decref();
}

TEST(RegexpTopEqualTest_349, Dot_WithDot_AreEqual_349) {
  Regexp* a = MustParse(".");
  Regexp* b = MustParse(".");
  ASSERT_TRUE(TopEqualViaAPI(a, b));
  a->Decref();
  b->Decref();
}

// ---------- Op mismatch ----------

TEST(RegexpTopEqualTest_349, DifferentOps_AreNotEqual_349) {
  Regexp* lit = Regexp::NewLiteral('a', Regexp::Regexp::NoParseFlags);
  Regexp* dot = MustParse(".");
  ASSERT_FALSE(TopEqualViaAPI(lit, dot));
  lit->Decref();
  dot->Decref();
}
