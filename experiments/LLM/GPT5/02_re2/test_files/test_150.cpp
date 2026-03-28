// File: regexp_nsub_test_150.cc
#include "re2/regexp.h"
#include <gtest/gtest.h>

using re2::Regexp;

// Utility helpers to keep tests tidy and avoid leaks.
// We never touch internal state; we only use public APIs.
namespace {

// Safely decref a possibly-null Regexp*
void SafeDecref(Regexp* re) {
  if (re) re->Decref();
}

// Create a simple literal sub-regexp with zero parse flags.
// We avoid assuming any ParseFlags names by passing 0.
Regexp* MakeLiteralRune(int c = 'a') {
  return Regexp::NewLiteral(static_cast<Rune>(c),
                            static_cast<Regexp::ParseFlags>(0));
}

}  // namespace

// --- Basic leaves ---

TEST(RegexpNsubTest_150, NewLiteral_HasZeroSubs_150) {
  Regexp* lit = MakeLiteralRune('x');
  ASSERT_NE(lit, nullptr) << "Factory should return a valid Regexp*";

  // Leaves should have no sub-regexps.
  EXPECT_EQ(lit->nsub(), 0);

  SafeDecref(lit);
}

TEST(RegexpNsubTest_150, LiteralString_HasZeroSubs_150) {
  Rune runes[3] = { 'a', 'b', 'c' };
  Regexp* str = Regexp::LiteralString(runes, /*nrunes=*/3,
                                      static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(str, nullptr);

  EXPECT_EQ(str->nsub(), 0);

  SafeDecref(str);
}

// --- Unary operators (expected to have exactly 1 sub) ---

TEST(RegexpNsubTest_150, Star_HasOneSub_150) {
  Regexp* lit = MakeLiteralRune('s');
  ASSERT_NE(lit, nullptr);

  Regexp* star = Regexp::Star(lit, static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(star, nullptr);

  // Observable behavior: unary operator wraps a single sub.
  EXPECT_EQ(star->nsub(), 1);

  // Ownership in these factories is internal to Regexp; we decref what we hold.
  SafeDecref(star);
  SafeDecref(lit);
}

TEST(RegexpNsubTest_150, Plus_HasOneSub_150) {
  Regexp* lit = MakeLiteralRune('p');
  ASSERT_NE(lit, nullptr);

  Regexp* plus = Regexp::Plus(lit, static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(plus, nullptr);

  EXPECT_EQ(plus->nsub(), 1);

  SafeDecref(plus);
  SafeDecref(lit);
}

TEST(RegexpNsubTest_150, Quest_HasOneSub_150) {
  Regexp* lit = MakeLiteralRune('q');
  ASSERT_NE(lit, nullptr);

  Regexp* quest = Regexp::Quest(lit, static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(quest, nullptr);

  EXPECT_EQ(quest->nsub(), 1);

  SafeDecref(quest);
  SafeDecref(lit);
}

// --- N-ary operators: Concat / Alternate ---

TEST(RegexpNsubTest_150, Concat_CountsAllSubs_150) {
  Regexp* a = MakeLiteralRune('a');
  Regexp* b = MakeLiteralRune('b');
  Regexp* c = MakeLiteralRune('c');
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  ASSERT_NE(c, nullptr);

  Regexp* subs[3] = {a, b, c};
  Regexp* cat = Regexp::Concat(subs, /*nsubs=*/3,
                               static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(cat, nullptr);

  // Observable behavior: result reflects number of provided subexpressions.
  EXPECT_EQ(cat->nsub(), 3);

  SafeDecref(cat);
  SafeDecref(a);
  SafeDecref(b);
  SafeDecref(c);
}

TEST(RegexpNsubTest_150, Alternate_CountsAllSubs_150) {
  Regexp* x = MakeLiteralRune('x');
  Regexp* y = MakeLiteralRune('y');
  ASSERT_NE(x, nullptr);
  ASSERT_NE(y, nullptr);

  Regexp* subs[2] = {x, y};
  Regexp* alt = Regexp::Alternate(subs, /*nsubs=*/2,
                                  static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(alt, nullptr);

  EXPECT_EQ(alt->nsub(), 2);

  SafeDecref(alt);
  SafeDecref(x);
  SafeDecref(y);
}

// --- Boundary-ish shapes the interface exposes ---

TEST(RegexpNsubTest_150, Concat_WithSingleSub_ReportsOne_150) {
  Regexp* only = MakeLiteralRune('1');
  ASSERT_NE(only, nullptr);

  Regexp* subs[1] = {only};
  Regexp* cat = Regexp::Concat(subs, /*nsubs=*/1,
                               static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(cat, nullptr);

  EXPECT_EQ(cat->nsub(), 1);

  SafeDecref(cat);
  SafeDecref(only);
}

TEST(RegexpNsubTest_150, Alternate_WithSingleSub_ReportsOne_150) {
  Regexp* only = MakeLiteralRune('Z');
  ASSERT_NE(only, nullptr);

  Regexp* subs[1] = {only};
  Regexp* alt = Regexp::Alternate(subs, /*nsubs=*/1,
                                  static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(alt, nullptr);

  EXPECT_EQ(alt->nsub(), 1);

  SafeDecref(alt);
  SafeDecref(only);
}

// --- Composition sanity check ---

TEST(RegexpNsubTest_150, NestedStructure_ReportsTopLevelArity_150) {
  // Build ( (a|b) (c|d) (e) ) as a concat of three items.
  Regexp* a = MakeLiteralRune('a');
  Regexp* b = MakeLiteralRune('b');
  Regexp* c = MakeLiteralRune('c');
  Regexp* d = MakeLiteralRune('d');
  Regexp* e = MakeLiteralRune('e');
  ASSERT_TRUE(a && b && c && d && e);

  Regexp* ab_subs[2] = {a, b};
  Regexp* cd_subs[2] = {c, d};

  Regexp* ab = Regexp::Alternate(ab_subs, 2, static_cast<Regexp::ParseFlags>(0));
  Regexp* cd = Regexp::Alternate(cd_subs, 2, static_cast<Regexp::ParseFlags>(0));
  Regexp* e1 = Regexp::Quest(e, static_cast<Regexp::ParseFlags>(0));  // unary wrapper
  ASSERT_TRUE(ab && cd && e1);

  Regexp* top_subs[3] = {ab, cd, e1};
  Regexp* top = Regexp::Concat(top_subs, 3, static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(top, nullptr);

  // We only assert the top-level arity as observed via the interface.
  EXPECT_EQ(top->nsub(), 3);

  SafeDecref(top);
  SafeDecref(ab);
  SafeDecref(cd);
  SafeDecref(e1);
  SafeDecref(a);
  SafeDecref(b);
  SafeDecref(c);
  SafeDecref(d);
  SafeDecref(e);
}
