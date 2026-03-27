#include <gtest/gtest.h>

#include "re2/regexp.h"
// Pull in the implementation that defines re2::PCREWalker (no public header provided)
#include "re2/mimics_pcre.cc"

using re2::PCREWalker;
using re2::Regexp;

class PCREWalkerTest_219 : public ::testing::Test {
protected:
  PCREWalker walker_;

  // Helper: parse a pattern into a Regexp*. Returns nullptr on parse error.
  Regexp* P(const char* pat, Regexp::ParseFlags flags = Regexp::NoParseFlags) {
    return Regexp::Parse(pat, flags, /*status=*/nullptr);
  }
};

// --- Short-circuit on child args ---

TEST(PCREWalkerTest_219, ChildArgFalseShortCircuits_219) {
  PCREWalker walker;
  // Any simple regexp is fine; use a literal.
  Regexp* lit = Regexp::NewLiteral('a', Regexp::NoParseFlags);

  bool children[] = {true, false, true};
  EXPECT_FALSE(walker.PostVisit(lit, /*parent_arg=*/true, /*pre_arg=*/true,
                                children, /*nchild_args=*/3));

  lit->Decref();
}

TEST(PCREWalkerTest_219, NoChildrenFallsThroughSwitch_219) {
  PCREWalker walker;
  Regexp* lit = Regexp::NewLiteral('a', Regexp::NoParseFlags);

  bool* none = nullptr;
  EXPECT_TRUE(walker.PostVisit(lit, /*parent_arg=*/false, /*pre_arg=*/false,
                               none, /*nchild_args=*/0));

  lit->Decref();
}

// --- Quantifiers: Star / Plus / Quest with non-empty sub (should return true) ---

TEST(PCREWalkerTest_219, StarWithNonEmptySub_AllChildrenTrue_ReturnsTrue_219) {
  PCREWalker walker;
  // "a*" → Star over non-empty literal 'a'
  Regexp* re = Regexp::Parse("a*", Regexp::NoParseFlags, nullptr);
  ASSERT_NE(re, nullptr);

  bool children[] = {true};
  EXPECT_TRUE(walker.PostVisit(re, true, true, children, 1));

  re->Decref();
}

TEST(PCREWalkerTest_219, PlusWithNonEmptySub_AllChildrenTrue_ReturnsTrue_219) {
  PCREWalker walker;
  Regexp* re = Regexp::Parse("a+", Regexp::NoParseFlags, nullptr);
  ASSERT_NE(re, nullptr);

  bool children[] = {true};
  EXPECT_TRUE(walker.PostVisit(re, true, true, children, 1));

  re->Decref();
}

TEST(PCREWalkerTest_219, QuestWithNonEmptySub_AllChildrenTrue_ReturnsTrue_219) {
  PCREWalker walker;
  Regexp* re = Regexp::Parse("a?", Regexp::NoParseFlags, nullptr);
  ASSERT_NE(re, nullptr);

  bool children[] = {true};
  EXPECT_TRUE(walker.PostVisit(re, true, true, children, 1));

  re->Decref();
}

// --- Quantifiers: Star/Repeat false-path when sub can be empty ---

TEST(PCREWalkerTest_219, StarWithEmptySub_ReturnsFalse_219) {
  PCREWalker walker;
  // "()*" → Star over an empty-capturing group; sub can be empty
  Regexp* re = Regexp::Parse("()*", Regexp::NoParseFlags, nullptr);
  ASSERT_NE(re, nullptr);

  bool children[] = {true};
  EXPECT_FALSE(walker.PostVisit(re, true, true, children, 1));

  re->Decref();
}

TEST(PCREWalkerTest_219, RepeatUnbounded_WithEmptySub_ReturnsFalse_219) {
  PCREWalker walker;
  // "(){0,}" → Repeat(min=0, max=-1) over empty sub; should be rejected
  Regexp* re = Regexp::Parse("(){0,}", Regexp::NoParseFlags, nullptr);
  ASSERT_NE(re, nullptr);

  bool children[] = {true};
  EXPECT_FALSE(walker.PostVisit(re, true, true, children, 1));

  re->Decref();
}

TEST(PCREWalkerTest_219, RepeatUnbounded_WithNonEmptySub_ReturnsTrue_219) {
  PCREWalker walker;
  // "a{0,}" → Repeat(min=0, max=-1) over non-empty literal 'a'
  Regexp* re = Regexp::Parse("a{0,}", Regexp::NoParseFlags, nullptr);
  ASSERT_NE(re, nullptr);

  bool children[] = {true};
  EXPECT_TRUE(walker.PostVisit(re, true, true, children, 1));

  re->Decref();
}

// --- Literal-specific rule: vertical tab ---

TEST(PCREWalkerTest_219, LiteralVerticalTab_ReturnsFalse_219) {
  PCREWalker walker;
  Regexp* re = Regexp::NewLiteral('\v', Regexp::NoParseFlags);

  bool children[] = {true};
  EXPECT_FALSE(walker.PostVisit(re, false, false, children, 1));

  re->Decref();
}

TEST(PCREWalkerTest_219, LiteralRegularChar_ReturnsTrue_219) {
  PCREWalker walker;
  Regexp* re = Regexp::NewLiteral('x', Regexp::NoParseFlags);

  bool children[] = {true};
  EXPECT_TRUE(walker.PostVisit(re, false, false, children, 1));

  re->Decref();
}

// --- Anchor rules ---

TEST(PCREWalkerTest_219, BeginLineAlwaysReturnsFalse_219) {
  PCREWalker walker;
  Regexp* re = Regexp::Parse("^", Regexp::NoParseFlags, nullptr);
  ASSERT_NE(re, nullptr);

  bool children[] = {true};
  EXPECT_FALSE(walker.PostVisit(re, true, true, children, 1));

  re->Decref();
}

TEST(PCREWalkerTest_219, EmptyMatchWithWasDollarFlag_ReturnsFalse_219) {
  PCREWalker walker;
  // Parse empty pattern but set WasDollar flag on the node.
  Regexp* re = Regexp::Parse("", Regexp::WasDollar, nullptr);
  ASSERT_NE(re, nullptr);

  bool children[] = {true};
  EXPECT_FALSE(walker.PostVisit(re, false, false, children, 1));

  re->Decref();
}

// --- Default switch branch example (no special handling) ---

TEST(PCREWalkerTest_219, CaptureFallsThroughAndReturnsTrue_219) {
  PCREWalker walker;
  Regexp* re = Regexp::Parse("(a)", Regexp::NoParseFlags, nullptr);
  ASSERT_NE(re, nullptr);

  bool children[] = {true};
  EXPECT_TRUE(walker.PostVisit(re, true, true, children, 1));

  re->Decref();
}
