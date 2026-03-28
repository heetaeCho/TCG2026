// File: re2_isemptyop_test_431.cc
#include <gtest/gtest.h>
#include <string>

// Public interface
#include "re2/regexp.h"

// We include the translation unit that defines the internal helper we want to test.
// This keeps us from re-implementing logic while allowing us to call the function.
#include "re2/simplify.cc"

namespace {

using re2::Regexp;

// Convenience: parse with default/zero flags.
static Regexp* ParseRe(const char* pattern) {
  return Regexp::Parse(pattern,
                       static_cast<Regexp::ParseFlags>(0),
                       /*status=*/nullptr);
}

// RAII helper to avoid leaks even if an assertion fails.
struct ReHolder {
  Regexp* re;
  explicit ReHolder(Regexp* r) : re(r) {}
  ~ReHolder() { if (re) re->Decref(); }
  Regexp* get() const { return re; }
};

}  // namespace

// ----- Positive cases: IsEmptyOp should return true -----

TEST(IsEmptyOpTest_431, ReturnsTrueForBeginLine_431) {
  ReHolder h(ParseRe("^"));
  ASSERT_NE(h.get(), nullptr);
  EXPECT_TRUE(re2::IsEmptyOp(h.get())) << "Expected '^' to be an empty op (BeginLine).";
}

TEST(IsEmptyOpTest_431, ReturnsTrueForEndLine_431) {
  ReHolder h(ParseRe("$"));
  ASSERT_NE(h.get(), nullptr);
  EXPECT_TRUE(re2::IsEmptyOp(h.get())) << "Expected '$' to be an empty op (EndLine).";
}

TEST(IsEmptyOpTest_431, ReturnsTrueForWordBoundary_431) {
  ReHolder h(ParseRe("\\b"));
  ASSERT_NE(h.get(), nullptr);
  EXPECT_TRUE(re2::IsEmptyOp(h.get())) << "Expected '\\b' to be an empty op (WordBoundary).";
}

TEST(IsEmptyOpTest_431, ReturnsTrueForNoWordBoundary_431) {
  ReHolder h(ParseRe("\\B"));
  ASSERT_NE(h.get(), nullptr);
  EXPECT_TRUE(re2::IsEmptyOp(h.get())) << "Expected '\\B' to be an empty op (NoWordBoundary).";
}

TEST(IsEmptyOpTest_431, ReturnsTrueForBeginText_431) {
  ReHolder h(ParseRe("\\A"));
  ASSERT_NE(h.get(), nullptr);
  EXPECT_TRUE(re2::IsEmptyOp(h.get())) << "Expected '\\A' to be an empty op (BeginText).";
}

TEST(IsEmptyOpTest_431, ReturnsTrueForEndText_431) {
  ReHolder h(ParseRe("\\z"));
  ASSERT_NE(h.get(), nullptr);
  EXPECT_TRUE(re2::IsEmptyOp(h.get())) << "Expected '\\z' to be an empty op (EndText).";
}

// ----- Negative cases: IsEmptyOp should return false -----

TEST(IsEmptyOpTest_431, ReturnsFalseForLiteral_431) {
  ReHolder h(ParseRe("a"));
  ASSERT_NE(h.get(), nullptr);
  EXPECT_FALSE(re2::IsEmptyOp(h.get())) << "Literal should not be an empty op.";
}

TEST(IsEmptyOpTest_431, ReturnsFalseForAnyChar_431) {
  ReHolder h(ParseRe("."));
  ASSERT_NE(h.get(), nullptr);
  EXPECT_FALSE(re2::IsEmptyOp(h.get())) << "AnyChar '.' should not be an empty op.";
}

TEST(IsEmptyOpTest_431, ReturnsFalseForEmptyMatch_431) {
  // Empty pattern parses to an empty-match node in RE2.
  ReHolder h(ParseRe(""));
  ASSERT_NE(h.get(), nullptr);
  EXPECT_FALSE(re2::IsEmptyOp(h.get())) << "Empty match should not be considered an empty op.";
}

TEST(IsEmptyOpTest_431, ReturnsFalseForAlternate_431) {
  ReHolder h(ParseRe("a|b"));
  ASSERT_NE(h.get(), nullptr);
  EXPECT_FALSE(re2::IsEmptyOp(h.get())) << "Alternation should not be an empty op.";
}

TEST(IsEmptyOpTest_431, ReturnsFalseForConcat_431) {
  ReHolder h(ParseRe("ab"));
  ASSERT_NE(h.get(), nullptr);
  EXPECT_FALSE(re2::IsEmptyOp(h.get())) << "Concatenation should not be an empty op.";
}

TEST(IsEmptyOpTest_431, ReturnsFalseForStar_431) {
  ReHolder h(ParseRe("a*"));
  ASSERT_NE(h.get(), nullptr);
  EXPECT_FALSE(re2::IsEmptyOp(h.get())) << "Repetition should not be an empty op.";
}
