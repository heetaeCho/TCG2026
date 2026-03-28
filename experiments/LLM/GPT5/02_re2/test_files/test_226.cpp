// File: tostring_previsit_test_226.cc

#include <gtest/gtest.h>
#include <limits>
#include <string>

#include "re2/regexp.h"

// Forward declare just what we need from ToStringWalker (definition is in tostring.cc).
namespace re2 {
class ToStringWalker {
 public:
  explicit ToStringWalker(std::string* t);
  int PreVisit(Regexp* re, int parent_arg, bool* stop);
};
}  // namespace re2

namespace {

using re2::Regexp;
using re2::ToStringWalker;

using PF = Regexp::ParseFlags;

static PF kNoFlags = static_cast<PF>(0);

TEST(ToStringPreVisitTest_226, AtomDoesNotAppend_226) {
  // Setup: a simple literal is an "atom".
  Regexp* lit = Regexp::NewLiteral('x', kNoFlags);
  std::string out;
  ToStringWalker w(&out);
  bool stop = false;

  // Act
  int ret = w.PreVisit(lit, /*parent_arg=*/0, &stop);

  // Assert: no text appended for atom; stop is untouched; ret is some precedence value.
  EXPECT_TRUE(out.empty());
  (void)ret;    // We don't assert the numeric value, only behavior.
  EXPECT_FALSE(stop);

  // Cleanup
  lit->Decref();
}

TEST(ToStringPreVisitTest_226, Concat_AppendsNonCapturing_WhenLowPrec_226) {
  // Setup: concat of two literals.
  Regexp* a = Regexp::NewLiteral('a', kNoFlags);
  Regexp* b = Regexp::NewLiteral('b', kNoFlags);
  Regexp* subs[2] = {a, b};
  Regexp* cat = Regexp::Concat(subs, 2, kNoFlags);

  std::string out;
  ToStringWalker w(&out);
  bool stop = false;

  // Force "low parent precedence" using INT_MIN so condition (prec < PrecConcat) surely holds.
  int ret = w.PreVisit(cat, std::numeric_limits<int>::min(), &stop);

  EXPECT_EQ(out, "(?:");   // Non-capturing open added
  (void)ret;
  EXPECT_FALSE(stop);

  cat->Decref();
}

TEST(ToStringPreVisitTest_226, Concat_DoesNotAppend_WhenHighPrec_226) {
  // Setup
  Regexp* a = Regexp::NewLiteral('a', kNoFlags);
  Regexp* b = Regexp::NewLiteral('b', kNoFlags);
  Regexp* subs[2] = {a, b};
  Regexp* cat = Regexp::Concat(subs, 2, kNoFlags);

  std::string out;
  ToStringWalker w(&out);
  bool stop = false;

  // High parent precedence: condition should not trigger.
  int ret = w.PreVisit(cat, std::numeric_limits<int>::max(), &stop);

  EXPECT_TRUE(out.empty());
  (void)ret;
  EXPECT_FALSE(stop);

  cat->Decref();
}

TEST(ToStringPreVisitTest_226, Alternate_AppendsNonCapturing_WhenLowPrec_226) {
  // Setup: alternation of two literals.
  Regexp* a = Regexp::NewLiteral('a', kNoFlags);
  Regexp* b = Regexp::NewLiteral('b', kNoFlags);
  Regexp* subs[2] = {a, b};
  Regexp* alt = Regexp::Alternate(subs, 2, kNoFlags);

  std::string out;
  ToStringWalker w(&out);
  bool stop = false;

  int ret = w.PreVisit(alt, std::numeric_limits<int>::min(), &stop);

  EXPECT_EQ(out, "(?:");
  (void)ret;
  EXPECT_FALSE(stop);

  alt->Decref();
}

TEST(ToStringPreVisitTest_226, Alternate_DoesNotAppend_WhenHighPrec_226) {
  // Setup
  Regexp* a = Regexp::NewLiteral('a', kNoFlags);
  Regexp* b = Regexp::NewLiteral('b', kNoFlags);
  Regexp* subs[2] = {a, b};
  Regexp* alt = Regexp::Alternate(subs, 2, kNoFlags);

  std::string out;
  ToStringWalker w(&out);
  bool stop = false;

  int ret = w.PreVisit(alt, std::numeric_limits<int>::max(), &stop);

  EXPECT_TRUE(out.empty());
  (void)ret;
  EXPECT_FALSE(stop);

  alt->Decref();
}

TEST(ToStringPreVisitTest_226, Capture_AppendsParen_226) {
  // Setup: a simple capturing group around a literal.
  Regexp* lit = Regexp::NewLiteral('x', kNoFlags);
  Regexp* cap = Regexp::Capture(lit, kNoFlags, /*cap=*/1);  // any nonzero cap id

  std::string out;
  ToStringWalker w(&out);
  bool stop = false;

  int ret = w.PreVisit(cap, /*parent_arg=*/0, &stop);

  // PreVisit for capture always appends "(" (not "(?:") and returns some precedence value.
  EXPECT_EQ(out, "(");
  (void)ret;
  EXPECT_FALSE(stop);

  cap->Decref();
}

TEST(ToStringPreVisitTest_226, Unary_Star_AppendsNonCapturing_WhenLowPrec_226) {
  // Setup: "x*"
  Regexp* lit = Regexp::NewLiteral('x', kNoFlags);
  Regexp* star = Regexp::Star(lit, kNoFlags);

  std::string out;
  ToStringWalker w(&out);
  bool stop = false;

  int ret = w.PreVisit(star, std::numeric_limits<int>::min(), &stop);

  EXPECT_EQ(out, "(?:");  // For low parent precedence, unary gets "(?:"
  (void)ret;
  EXPECT_FALSE(stop);

  star->Decref();
}

TEST(ToStringPreVisitTest_226, Unary_PlusQuestRepeat_BehaviorMatchesUnaryRules_226) {
  // Setup: "x+", "x?", "x{2,3}"
  Regexp* base1 = Regexp::NewLiteral('x', kNoFlags);
  Regexp* base2 = Regexp::NewLiteral('y', kNoFlags);
  Regexp* base3 = Regexp::NewLiteral('z', kNoFlags);

  Regexp* plus   = Regexp::Plus(base1, kNoFlags);
  Regexp* quest  = Regexp::Quest(base2, kNoFlags);
  Regexp* repeat = Regexp::Repeat(base3, kNoFlags, /*min=*/2, /*max=*/3);

  // Use a fresh walker per check so output is independent.
  {
    std::string out;
    ToStringWalker w(&out);
    bool stop = false;
    (void)w.PreVisit(plus, std::numeric_limits<int>::min(), &stop);
    EXPECT_EQ(out, "(?:");
    EXPECT_FALSE(stop);
  }
  {
    std::string out;
    ToStringWalker w(&out);
    bool stop = false;
    (void)w.PreVisit(quest, std::numeric_limits<int>::min(), &stop);
    EXPECT_EQ(out, "(?:");
    EXPECT_FALSE(stop);
  }
  {
    std::string out;
    ToStringWalker w(&out);
    bool stop = false;
    (void)w.PreVisit(repeat, std::numeric_limits<int>::min(), &stop);
    EXPECT_EQ(out, "(?:");
    EXPECT_FALSE(stop);
  }

  plus->Decref();
  quest->Decref();
  repeat->Decref();
}

TEST(ToStringPreVisitTest_226, PrecedenceReturnValues_AreCategoryConsistent_226) {
  // This test only compares *relative* return values between categories.
  // We do not assert specific numeric constants.

  // Atom
  Regexp* lit = Regexp::NewLiteral('a', kNoFlags);

  // Unary (star) wraps an atom
  Regexp* star = Regexp::Star(Regexp::NewLiteral('b', kNoFlags), kNoFlags);

  // Concat and Alternate
  Regexp* csubs[2] = {Regexp::NewLiteral('c', kNoFlags), Regexp::NewLiteral('d', kNoFlags)};
  Regexp* concat = Regexp::Concat(csubs, 2, kNoFlags);

  Regexp* asubs[2] = {Regexp::NewLiteral('e', kNoFlags), Regexp::NewLiteral('f', kNoFlags)};
  Regexp* alt = Regexp::Alternate(asubs, 2, kNoFlags);

  // Capture
  Regexp* cap = Regexp::Capture(Regexp::NewLiteral('g', kNoFlags), kNoFlags, /*cap=*/1);

  std::string out_ign;
  ToStringWalker w(&out_ign);
  bool stop = false;

  const int p_atom   = w.PreVisit(lit,   /*parent_arg=*/0, &stop);
  const int p_unary  = w.PreVisit(star,  /*parent_arg=*/0, &stop);
  const int p_concat = w.PreVisit(concat,/*parent_arg=*/0, &stop);
  const int p_alt    = w.PreVisit(alt,   /*parent_arg=*/0, &stop);
  const int p_cap    = w.PreVisit(cap,   /*parent_arg=*/0, &stop);

  // Unary returns the same precedence category as atoms.
  EXPECT_EQ(p_unary, p_atom);

  // Concat and Alternate are distinct from the atom/unary category (and likely distinct from each other).
  EXPECT_NE(p_concat, p_atom);
  EXPECT_NE(p_alt,    p_atom);

  // Capture precedence differs from atom/unary as well.
  EXPECT_NE(p_cap,    p_atom);

  // Concat vs Alternate precedence should be different.
  EXPECT_NE(p_concat, p_alt);

  // Cleanup
  lit->Decref();
  star->Decref();
  concat->Decref();
  alt->Decref();
  cap->Decref();
}

}  // namespace
