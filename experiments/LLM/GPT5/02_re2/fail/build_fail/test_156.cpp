// File: regexp_rune_test_156.cc
#include "re2/regexp.h"

#include <gtest/gtest.h>

using re2::Regexp;

class RegexpRuneTest_156 : public ::testing::Test {
protected:
  // Convenience to get a zero/none parse flags value without assuming details.
  static Regexp::ParseFlags NoFlags() {
    return static_cast<Regexp::ParseFlags>(0);
  }
};

// Normal operation: when the Regexp is a literal, rune() returns that rune.
TEST_F(RegexpRuneTest_156, ReturnsRuneForLiteral_156) {
  Regexp* lit = Regexp::NewLiteral(static_cast<Rune>('a'), NoFlags());
  ASSERT_NE(lit, nullptr) << "Factory should return a non-null Regexp for a literal.";

  Rune r = lit->rune();
  EXPECT_EQ(r, static_cast<Rune>('a'));

  lit->Decref();  // Respect ownership; avoid leaks.
}

// Boundary condition: maximum Unicode code point commonly allowed by RE2.
TEST_F(RegexpRuneTest_156, ReturnsMaxUnicodeRuneForLiteral_156) {
  const Rune kMax = static_cast<Rune>(0x10FFFF);
  Regexp* lit = Regexp::NewLiteral(kMax, NoFlags());
  ASSERT_NE(lit, nullptr);

  EXPECT_EQ(lit->rune(), kMax);

  lit->Decref();
}

// Error/exceptional observable behavior: calling rune() on a non-literal.
// The interface uses ABSL_DCHECK to enforce kRegexpLiteral; in debug builds,
// this should cause death. Guard with death-test availability and debug mode.
#if GTEST_HAS_DEATH_TEST
TEST_F(RegexpRuneTest_156, DiesWhenCalledOnNonLiteral_156) {
#ifndef NDEBUG
  Regexp* lit = Regexp::NewLiteral(static_cast<Rune>('x'), NoFlags());
  ASSERT_NE(lit, nullptr);

  Regexp* star = Regexp::Star(lit, NoFlags());  // Make a non-literal Regexp.
  ASSERT_NE(star, nullptr);

  // rune() should DCHECK-fail for non-literals.
  ASSERT_DEATH({ (void)star->rune(); }, ".*");

  // Clean up only the top-level; ownership/refcounts are managed internally.
  star->Decref();
#else
  GTEST_SKIP() << "DCHECK-based death test only runs in debug builds.";
#endif
}
#endif  // GTEST_HAS_DEATH_TEST
