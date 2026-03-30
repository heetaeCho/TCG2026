// File: parse_do_right_paren_test_504.cc

#include "gtest/gtest.h"

// Pull in the production declarations (the inner ParseState lives here in this project layout)
#include "re2/regexp.h"
#include "re2/parse.cc"

using namespace re2;

class ParseStateDoRightParenTest_504 : public ::testing::Test {
protected:
  // Use 0 for flags unless a test needs otherwise; treat implementation as a black box.
  static constexpr Regexp::ParseFlags kFlags = static_cast<Regexp::ParseFlags>(0);

  // Small helper to fully finish and return the resulting regexp from the stack.
  static Regexp* Finish(Regexp::ParseState& ps) {
    Regexp* out = ps.DoFinish();
    return out;
  }
};

// ------------------------------ Error cases ------------------------------

TEST_F(ParseStateDoRightParenTest_504, ReturnsFalseAndSetsStatus_WhenStackEmpty_504) {
  RegexpStatus status;
  absl::string_view whole = "a)";
  Regexp::ParseState ps(kFlags, whole, &status);

  // No left paren or expression on the stack.
  bool ok = ps.DoRightParen();

  EXPECT_FALSE(ok);
  EXPECT_EQ(status.code(), kRegexpUnexpectedParen);
  EXPECT_EQ(status.error_arg(), whole);
}

TEST_F(ParseStateDoRightParenTest_504, ReturnsFalseAndSetsStatus_WhenBelowTopIsNotLeftParen_504) {
  RegexpStatus status;
  absl::string_view whole = "ab)";
  Regexp::ParseState ps(kFlags, whole, &status);

  // Push two ordinary expressions so that r2 exists but is NOT a left-paren marker.
  ASSERT_TRUE(ps.PushLiteral('a'));
  ASSERT_TRUE(ps.PushLiteral('b'));

  bool ok = ps.DoRightParen();

  EXPECT_FALSE(ok);
  EXPECT_EQ(status.code(), kRegexpUnexpectedParen);
  EXPECT_EQ(status.error_arg(), whole);
}

// ------------------------------ Normal operation ------------------------------

TEST_F(ParseStateDoRightParenTest_504, CapturingGroup_WrapsSubexpression_504) {
  RegexpStatus status;
  absl::string_view whole = "(x)";
  Regexp::ParseState ps(kFlags, whole, &status);

  // Open a capturing group, add a simple subexpression, then close it.
  ASSERT_TRUE(ps.DoLeftParen(/*name=*/absl::string_view()));  // capturing
  ASSERT_TRUE(ps.PushLiteral('x'));

  bool ok = ps.DoRightParen();
  ASSERT_TRUE(ok) << "DoRightParen should succeed for a well-formed capturing group";

  // Finishing should yield a single capture node containing the subexpression.
  Regexp* re = Finish(ps);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->nsub(), 1);
  ASSERT_NE(re->sub(), nullptr);
  ASSERT_NE(re->sub()[0], nullptr);
  EXPECT_TRUE(re->sub()[0]->op() == kRegexpLiteral || re->sub()[0]->op() == kRegexpLiteralString);
}

TEST_F(ParseStateDoRightParenTest_504, NonCapturingGroup_LeavesSubexpression_Unwrapped_504) {
  RegexpStatus status;
  absl::string_view whole = "(?:y)";
  Regexp::ParseState ps(kFlags, whole, &status);

  // Open a non-capturing group, add a simple subexpression, then close it.
  ASSERT_TRUE(ps.DoLeftParenNoCapture());
  ASSERT_TRUE(ps.PushLiteral('y'));

  bool ok = ps.DoRightParen();
  ASSERT_TRUE(ok) << "DoRightParen should succeed for a well-formed non-capturing group";

  // Finishing should yield the subexpression directly (no capture wrapper).
  Regexp* re = Finish(ps);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(re->op() == kRegexpLiteral || re->op() == kRegexpLiteralString);
}

// ------------------------------ Boundary-ish case ------------------------------

TEST_F(ParseStateDoRightParenTest_504, CapturingGroup_AllowsEmptyBody_504) {
  RegexpStatus status;
  absl::string_view whole = "()";
  Regexp::ParseState ps(kFlags, whole, &status);

  // Capturing group with an explicitly empty match as the body.
  ASSERT_TRUE(ps.DoLeftParen(/*name=*/absl::string_view()));  // capturing
  ASSERT_TRUE(ps.PushSimpleOp(kRegexpEmptyMatch));

  bool ok = ps.DoRightParen();
  ASSERT_TRUE(ok);

  Regexp* re = Finish(ps);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCapture);
  EXPECT_EQ(re->nsub(), 1);
  ASSERT_NE(re->sub(), nullptr);
  ASSERT_NE(re->sub()[0], nullptr);
  EXPECT_EQ(re->sub()[0]->op(), kRegexpEmptyMatch);
}
