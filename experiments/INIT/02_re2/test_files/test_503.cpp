// File: parse_state_do_vertical_bar_test_503.cc
#include "re2/regexp.h"   // public API with Regexp and nested ParseState
#include "gtest/gtest.h"

using namespace re2;

namespace {

// Small RAII to decref non-null Regexp*.
struct RegexpHolder {
  Regexp* re;
  explicit RegexpHolder(Regexp* r) : re(r) {}
  ~RegexpHolder() { if (re) re->Decref(); }
  Regexp* get() const { return re; }
};

// Helper: build an alternation via the ParseState surface API:
// left (already pushed by caller) | right, then collapse with DoVerticalBar and finish.
static Regexp* FinishWithBarAndRight(Regexp::ParseState& ps, Rune right_rune) {
  EXPECT_TRUE(ps.PushLiteral(right_rune));
  EXPECT_TRUE(ps.DoVerticalBar());
  return ps.DoFinish();
}

// --- Tests ---

// Normal operation: literal 'a' | literal 'b' collapses to an Alternate
// whose two children are both Literals with runes 'a' and 'b'.
TEST(ParseState_DoVerticalBar_503, AlternationLiteralLiteral_503) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::NoParseFlags, /*whole_regexp=*/"a|b", &status);

  ASSERT_TRUE(ps.PushLiteral('a'));
  ASSERT_TRUE(ps.PushSimpleOp(static_cast<RegexpOp>(kMaxRegexpOp + 2)));  // kVerticalBar
  Regexp* out = FinishWithBarAndRight(ps, 'b');
  RegexpHolder hold(out);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->op(), kRegexpAlternate);
  ASSERT_EQ(out->nsub(), 2);

  Regexp** subs = out->sub();
  ASSERT_NE(subs, nullptr);
  // Both sides are literals; order should be the two expected runes in some order.
  ASSERT_EQ(subs[0]->op(), kRegexpLiteral);
  ASSERT_EQ(subs[1]->op(), kRegexpLiteral);

  const Rune r0 = subs[0]->rune();
  const Rune r1 = subs[1]->rune();
  // Accept either ordering of {'a','b'}.
  EXPECT_TRUE( (r0=='a' && r1=='b') || (r0=='b' && r1=='a') );
}

// Special-case simplification: "." | "a" should simplify to "." (AnyChar).
TEST(ParseState_DoVerticalBar_503, AnyCharOrLiteral_LeftAnyCharSimplifiesToAnyChar_503) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::NoParseFlags, /*whole_regexp=*/".|a", &status);

  ASSERT_TRUE(ps.PushDot());  // left operand: AnyChar
  ASSERT_TRUE(ps.PushSimpleOp(static_cast<RegexpOp>(kMaxRegexpOp + 2)));  // kVerticalBar

  Regexp* out = FinishWithBarAndRight(ps, 'a');
  RegexpHolder hold(out);
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->op(), kRegexpAnyChar);
}

// Special-case simplification: "a" | "." should simplify to "." (AnyChar).
TEST(ParseState_DoVerticalBar_503, LiteralOrAnyChar_RightAnyCharSimplifiesToAnyChar_503) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::NoParseFlags, /*whole_regexp=*/"a|.", &status);

  ASSERT_TRUE(ps.PushLiteral('a'));  // left: Literal
  ASSERT_TRUE(ps.PushSimpleOp(static_cast<RegexpOp>(kMaxRegexpOp + 2)));  // kVerticalBar

  // right: AnyChar; push, then collapse
  ASSERT_TRUE(ps.PushDot());
  ASSERT_TRUE(ps.DoVerticalBar());

  Regexp* out = ps.DoFinish();
  RegexpHolder hold(out);
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->op(), kRegexpAnyChar);
}

// Boundary/marker behavior: Calling DoVerticalBar() when there is NOT yet a
// vertical-bar marker on the stack should act like pushing the marker,
// enabling a later collapse after the right-hand operand arrives.
TEST(ParseState_DoVerticalBar_503, ActsAsMarkerWhenMissing_503) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::NoParseFlags, /*whole_regexp=*/"a|b", &status);

  ASSERT_TRUE(ps.PushLiteral('a'));
  // No marker on stack yet; this call should succeed by pushing the marker.
  EXPECT_TRUE(ps.DoVerticalBar());

  // Provide right operand and collapse.
  Regexp* out = FinishWithBarAndRight(ps, 'b');
  RegexpHolder hold(out);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->op(), kRegexpAlternate);
  ASSERT_EQ(out->nsub(), 2);

  Regexp** subs = out->sub();
  ASSERT_NE(subs, nullptr);
  EXPECT_EQ(subs[0]->op(), kRegexpLiteral);
  EXPECT_EQ(subs[1]->op(), kRegexpLiteral);
}

// General sanity: Alternation with two dots ".|." remains an alternation
// of AnyChar with AnyChar (still valid and collapsible via the public interface).
TEST(ParseState_DoVerticalBar_503, AnyCharOrAnyChar_RemainsAlternate_503) {
  RegexpStatus status;
  Regexp::ParseState ps(Regexp::NoParseFlags, /*whole_regexp=*/".|.", &status);

  ASSERT_TRUE(ps.PushDot());
  ASSERT_TRUE(ps.PushSimpleOp(static_cast<RegexpOp>(kMaxRegexpOp + 2)));  // kVerticalBar
  ASSERT_TRUE(ps.PushDot());
  ASSERT_TRUE(ps.DoVerticalBar());

  Regexp* out = ps.DoFinish();
  RegexpHolder hold(out);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->op(), kRegexpAlternate);
  ASSERT_EQ(out->nsub(), 2);

  Regexp** subs = out->sub();
  ASSERT_NE(subs, nullptr);
  EXPECT_EQ(subs[0]->op(), kRegexpAnyChar);
  EXPECT_EQ(subs[1]->op(), kRegexpAnyChar);
}

}  // namespace
