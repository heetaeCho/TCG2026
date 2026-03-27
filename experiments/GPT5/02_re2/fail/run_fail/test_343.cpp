// File: regexp_alternate_no_factor_test.cc

#include "re2/regexp.h"
#include <gtest/gtest.h>

namespace re2 {

class AlternateNoFactorTest_343 : public ::testing::Test {
protected:
  // Helper to create a simple literal sub-regexp.
  static Regexp* Lit(Rune r, Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(0)) {
    return Regexp::NewLiteral(r, flags);
  }
};

// ===== Normal operation =====

TEST_F(AlternateNoFactorTest_343, TwoLiterals_YieldsAlternateOp_343) {
  Regexp* a = Lit('a');
  Regexp* b = Lit('b');

  Regexp* subs[2] = {a, b};
  Regexp* alt = Regexp::AlternateNoFactor(subs, 2, static_cast<Regexp::ParseFlags>(0));

  ASSERT_NE(alt, nullptr) << "AlternateNoFactor should return a non-null Regexp for valid inputs";
  EXPECT_EQ(alt->op(), kRegexpAlternate) << "Resulting op should indicate alternation";
  EXPECT_GE(alt->nsub(), 2) << "Alternation of two items should have at least two children";

  // Intentionally avoid assumptions about ownership/refcounts or structure beyond op/nsub.
}

// ===== Boundary conditions =====

TEST_F(AlternateNoFactorTest_343, SingleLiteral_AllowsIdentityOrAlternate_343) {
  Regexp* a = Lit('x');
  Regexp* subs[1] = {a};

  Regexp* alt = Regexp::AlternateNoFactor(subs, 1, static_cast<Regexp::ParseFlags>(0));

  ASSERT_NE(alt, nullptr);

  // Treat as a black box: either it returns the subexpression unchanged (Literal),
  // or an alternate wrapper containing a single child. Both are acceptable from the interface.
  RegexpOp op = alt->op();
  EXPECT_TRUE(op == kRegexpLiteral || op == kRegexpAlternate)
      << "With one sub, implementation may return identity (Literal) or an Alternate wrapper";
}

TEST_F(AlternateNoFactorTest_343, ZeroSubs_ReturnsNullOrNeutral_343) {
  // When there are zero subs, behavior may vary by implementation.
  // We only assert on safe, observable outcomes through the interface.
  Regexp* alt = Regexp::AlternateNoFactor(nullptr, 0, static_cast<Regexp::ParseFlags>(0));

  // Accept either a null (failure) or a neutral/no-match/empty-match node if produced.
  if (alt == nullptr) {
    SUCCEED() << "AlternateNoFactor(nullptr, 0, ...) may validly return nullptr";
  } else {
    RegexpOp op = alt->op();
    EXPECT_TRUE(op == kRegexpNoMatch || op == kRegexpEmptyMatch || op == kRegexpAlternate)
        << "If non-null, zero-sub alternation may yield a special node or an alternate";
  }
}

// ===== Error-like / defensive inputs =====

TEST_F(AlternateNoFactorTest_343, NullSubsPointerWithPositiveCount_IsHandled_343) {
  // Passing a non-zero count with a null array pointer: ensure the API responds in a defined way
  // (either nullptr or a safe node). We don't assume internal error handling details.
  Regexp* alt = Regexp::AlternateNoFactor(nullptr, 2, static_cast<Regexp::ParseFlags>(0));

  if (alt == nullptr) {
    SUCCEED() << "Null subs with positive count may return nullptr";
  } else {
    // If a node is returned, it should still represent some form of alternation or neutral node.
    RegexpOp op = alt->op();
    EXPECT_TRUE(op == kRegexpAlternate || op == kRegexpNoMatch || op == kRegexpEmptyMatch)
        << "If non-null, expect an alternate or neutral/no-match form";
  }
}

// ===== Sanity w.r.t. flags passthrough (observable only via construction success) =====

TEST_F(AlternateNoFactorTest_343, FlagsArgument_DoesNotPreventConstruction_343) {
  // We can’t assert internal factoring behavior or exact flag effects here,
  // but we can verify that providing a non-zero flags value still produces a valid node.
  Regexp::ParseFlags some_flags = static_cast<Regexp::ParseFlags>(0x1); // treat flags as opaque
  Regexp* a = Lit('m', some_flags);
  Regexp* b = Lit('n', some_flags);
  Regexp* subs[2] = {a, b};

  Regexp* alt = Regexp::AlternateNoFactor(subs, 2, some_flags);
  ASSERT_NE(alt, nullptr);
  EXPECT_EQ(alt->op(), kRegexpAlternate);
  EXPECT_GE(alt->nsub(), 2);
}

}  // namespace re2
