// File: parse_do_collapse_test_509.cc

#include "re2/regexp.h"
#include "re2/parse.h"   // If ParseState is exposed here in your tree; otherwise include the header that declares it.
#include "gtest/gtest.h"

using re2::Regexp;

namespace {

class ParseStateDoCollapseTest_509 : public ::testing::Test {
protected:
  // Convenience aliases to match RE2 types without assuming internals.
  using ParseState = Regexp::ParseState;
  using ParseFlags = Regexp::ParseFlags;
  using RegexpOp   = RegexpOp; // Assuming RegexpOp is visible from the same header.

  // Minimal helpers to create a fresh ParseState for each test.
  ParseState* NewState() {
    return new ParseState(static_cast<ParseFlags>(0), absl::string_view(), &status_);
  }

  // Finish the current stack into a single Regexp* and return it (caller Decref()).
  Regexp* Finish(ParseState* ps) {
    Regexp* re = ps->DoFinish();
    return re;
  }

  // Utility: make a literal.
  static Regexp* Lit(char c) {
    return Regexp::NewLiteral(static_cast<Rune>(c), static_cast<ParseFlags>(0));
  }

  // Utility: stringify finished regex (nullptr-safe).
  static std::string ToString(Regexp* re) {
    return re ? re->ToString() : std::string();
  }

  re2::RegexpStatus status_;
};

// --- Tests ---

// Collapsing concatenation of adjacent literals should yield a single concatenation,
// observable as a joined string via ToString().
TEST_F(ParseStateDoCollapseTest_509, CollapseConcat_CombinesAdjacentLiterals_509) {
  std::unique_ptr<ParseState> ps(NewState());

  ASSERT_TRUE(ps->PushLiteral('a'));
  ASSERT_TRUE(ps->PushLiteral('b'));
  ASSERT_TRUE(ps->PushLiteral('c'));

  // Collapse all adjacent items into a concat node.
  ps->DoCollapse(kRegexpConcat);

  Regexp* re = Finish(ps.get());
  ASSERT_NE(re, nullptr);

  // Expect "abc" in order (observable behavior via public ToString()).
  EXPECT_EQ(ToString(re), "abc");

  re->Decref();
}

// Collapsing concatenation should FLATTEN nested concat nodes:
// concat(x, y) followed by z becomes concat(x, y, z) preserving order.
TEST_F(ParseStateDoCollapseTest_509, CollapseConcat_FlattensNestedConcat_509) {
  std::unique_ptr<ParseState> ps(NewState());

  // Build concat(x, y) as a single Regexp and push it, then push literal 'z'.
  Regexp* xy_subs[2] = { Lit('x'), Lit('y') };
  Regexp* xy = Regexp::Concat(xy_subs, 2, static_cast<ParseFlags>(0));
  ASSERT_TRUE(ps->PushRegexp(xy));
  ASSERT_TRUE(ps->PushLiteral('z'));

  ps->DoCollapse(kRegexpConcat);

  Regexp* re = Finish(ps.get());
  ASSERT_NE(re, nullptr);

  // Expect flattening: "xyz", not "(xy)z" or reversed.
  EXPECT_EQ(ToString(re), "xyz");

  re->Decref();
}

// If there is only a single element to the left of a marker, DoCollapse(kRegexpConcat)
// should be a no-op (no structural change). We validate by observing ToString().
TEST_F(ParseStateDoCollapseTest_509, CollapseConcat_NoOpWithSingleElement_509) {
  std::unique_ptr<ParseState> ps(NewState());

  // Create a marker boundary (non-capturing left paren is a typical marker).
  ASSERT_TRUE(ps->DoLeftParenNoCapture());
  ASSERT_TRUE(ps->PushLiteral('a'));

  // With only one item above the marker, collapsing concatenation should do nothing observable.
  ps->DoCollapse(kRegexpConcat);

  Regexp* re = Finish(ps.get());
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(ToString(re), "a");

  re->Decref();
}

// Collapsing alternation should combine adjacent alternatives into a single alternation,
// observable via ToString() as "a|b|c" (order must be preserved).
TEST_F(ParseStateDoCollapseTest_509, CollapseAlternate_CombinesAndFlattens_509) {
  std::unique_ptr<ParseState> ps(NewState());

  // Prepare nested alternate: (a|b) as a single Regexp, then push 'c'.
  Regexp* ab_subs[2] = { Lit('a'), Lit('b') };
  Regexp* ab = Regexp::Alternate(ab_subs, 2, static_cast<ParseFlags>(0));
  ASSERT_TRUE(ps->PushRegexp(ab));
  ASSERT_TRUE(ps->PushLiteral('c'));

  // Collapse using the alternate op; should flatten to a|b|c.
  ps->DoCollapse(kRegexpAlternate);

  Regexp* re = Finish(ps.get());
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(ToString(re), "a|b|c");

  re->Decref();
}

// Mixed case: a nested concat followed by another concat candidate and then an alternation
// boundary ensures DoCollapse respects the requested op and preserves order.
TEST_F(ParseStateDoCollapseTest_509, CollapseRespectsOpAndOrder_509) {
  std::unique_ptr<ParseState> ps(NewState());

  // Build concat("m", "n") then push "o".
  Regexp* mn_subs[2] = { Lit('m'), Lit('n') };
  Regexp* mn = Regexp::Concat(mn_subs, 2, static_cast<ParseFlags>(0));
  ASSERT_TRUE(ps->PushRegexp(mn));
  ASSERT_TRUE(ps->PushLiteral('o'));

  // Collapse concat first -> expect "mno".
  ps->DoCollapse(kRegexpConcat);

  // Now introduce an alternation boundary and another branch "p".
  ASSERT_TRUE(ps->DoVerticalBar());   // push alternation marker
  ASSERT_TRUE(ps->PushLiteral('p'));

  // Collapse alternation -> expect "mno|p".
  ps->DoCollapse(kRegexpAlternate);

  Regexp* re = Finish(ps.get());
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(ToString(re), "mno|p");

  re->Decref();
}

}  // namespace
