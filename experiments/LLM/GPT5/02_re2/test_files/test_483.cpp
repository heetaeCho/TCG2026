// File: parse_state_pushregexp_test_483.cc

#include <string>
#include "gtest/gtest.h"

// Abseil string_view is referenced by the interfaces.
#include "absl/strings/string_view.h"

// Public interface for Regexp & enums.
#include "re2/regexp.h"

// Expose Regexp::ParseState and its public methods used by the tests.
// (These tests validate behavior strictly via public methods.)
#include "re2/parse.cc"

using re2::Regexp;
using re2::kRegexpCharClass;
using re2::kRegexpLiteral;

class ParseStatePushRegexpTest_483 : public ::testing::Test {};

// Helper that uses the public ParseState::ParseCharClass to obtain a Regexp*
// representing a character class, then pushes it via PushRegexp and returns
// the finished Regexp* for observation (op, rune, flags, simple, etc.).
static Regexp* BuildByPushingParsedCharClass(const std::string& text,
                                             Regexp::ParseFlags flags = Regexp::NoParseFlags) {
  absl::string_view whole(text);
  Regexp::ParseState ps(flags, whole, /*status=*/nullptr);

  // s points at the start of the class, e.g. "[x]" or "[Aa]".
  absl::string_view s = whole;
  Regexp* out_re = nullptr;

  // Parse the char class and then push it. Both are public & observable.
  EXPECT_TRUE(ps.ParseCharClass(&s, &out_re, /*status=*/nullptr));
  EXPECT_TRUE(ps.PushRegexp(out_re));

  // Finish and return the Regexp we can inspect via public accessors.
  Regexp* finished = ps.DoFinish();
  EXPECT_NE(finished, nullptr);
  return finished;
}

// Normal operation: singleton char class like "[x]" should be simplified
// into a literal 'x' (per observable result of DoFinish()).
TEST(ParseStatePushRegexpTest_483, SingletonCharClassBecomesLiteral_483) {
  Regexp* r = BuildByPushingParsedCharClass("[x]");
  ASSERT_NE(r, nullptr);

  EXPECT_EQ(r->op(), kRegexpLiteral);
  EXPECT_EQ(r->rune(), static_cast<int>('x'));
  // No foldcase bit expected for a single literal.
  EXPECT_EQ((r->parse_flags() & Regexp::FoldCase), 0);
  // Literal should be simple.
  EXPECT_TRUE(r->simple());

  r->Decref();
}

// ASCII case-pair: "[Aa]" should become a folded literal 'a' with FoldCase set,
// according to the observable flags and rune value.
TEST(ParseStatePushRegexpTest_483, CasePairCharClassBecomesFoldedLiteral_483) {
  Regexp* r = BuildByPushingParsedCharClass("[Aa]");
  ASSERT_NE(r, nullptr);

  EXPECT_EQ(r->op(), kRegexpLiteral);
  // Lowercase 'a' is expected as the canonical rune.
  EXPECT_EQ(r->rune(), static_cast<int>('a'));
  // FoldCase flag should be present.
  EXPECT_NE((r->parse_flags() & Regexp::FoldCase), 0);
  EXPECT_TRUE(r->simple());

  r->Decref();
}

// Boundary: uppercase only "[A]" is still a singleton and should reduce to a
// literal 'A' without FoldCase.
TEST(ParseStatePushRegexpTest_483, UpperOnlySingletonDoesNotFold_483) {
  Regexp* r = BuildByPushingParsedCharClass("[A]");
  ASSERT_NE(r, nullptr);

  EXPECT_EQ(r->op(), kRegexpLiteral);
  EXPECT_EQ(r->rune(), static_cast<int>('A'));
  EXPECT_EQ((r->parse_flags() & Regexp::FoldCase), 0);
  EXPECT_TRUE(r->simple());

  r->Decref();
}

// Boundary: when the class has more than two distinct members (e.g., "[AaB]"),
// it should NOT be converted to a single literal. The observable result
// remains a char class.
TEST(ParseStatePushRegexpTest_483, LargeCharClassIsNotConverted_483) {
  Regexp* r = BuildByPushingParsedCharClass("[AaB]");
  ASSERT_NE(r, nullptr);

  EXPECT_EQ(r->op(), kRegexpCharClass);
  // We can't depend on internal details; just verify it's not a literal.
  EXPECT_NE(r->op(), kRegexpLiteral);

  r->Decref();
}

// Smoke test: pushing an already-literal regexp via the public factory
// still yields a literal on finish (verifying push path & simple() computation).
TEST(ParseStatePushRegexpTest_483, PushLiteralRemainsLiteral_483) {
  // Create a literal via the public factory.
  Regexp* lit = Regexp::NewLiteral(static_cast<int>('z'), Regexp::NoParseFlags);
  ASSERT_NE(lit, nullptr);

  absl::string_view whole("");
  Regexp::ParseState ps(Regexp::NoParseFlags, whole, /*status=*/nullptr);

  ASSERT_TRUE(ps.PushRegexp(lit));
  Regexp* out = ps.DoFinish();
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->op(), kRegexpLiteral);
  EXPECT_EQ(out->rune(), static_cast<int>('z'));
  EXPECT_TRUE(out->simple());

  out->Decref();
}
