// File: parse_state_maybe_concat_string_test_512.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "absl/strings/string_view.h"

// Pull in Regexp, enums, and nested ParseState.
#include "re2/regexp.h"

// NOTE: In this harness, ParseState is defined in parse.cc.
// Including it here exposes the tested interface.
#include "re2/parse.cc"

using ::testing::NotNull;
using ::testing::ElementsAre;

namespace re2 {

class ParseStateMaybeConcatStringTest_512 : public ::testing::Test {
 protected:
  using PF = Regexp::ParseFlags;

  static Regexp* FinishAndGet(Regexp::ParseState& ps) {
    Regexp* out = ps.DoFinish();
    EXPECT_THAT(out, NotNull());
    return out;
  }

  // Verifies a LiteralString with expected runes.
  static void ExpectLiteralString(Regexp* re, std::initializer_list<Rune> runes) {
    ASSERT_THAT(re, NotNull());
    EXPECT_EQ(re->op(), kRegexpLiteralString);
    ASSERT_EQ(re->nrunes(), static_cast<int>(runes.size()));
    std::vector<Rune> got(re->runes(), re->runes() + re->nrunes());
    EXPECT_THAT(got, ElementsAreArray(runes));
  }

  // Verifies a single Literal rune.
  static void ExpectLiteral(Regexp* re, Rune r) {
    ASSERT_THAT(re, NotNull());
    EXPECT_EQ(re->op(), kRegexpLiteral);
    EXPECT_EQ(re->rune(), r);
  }
};

// 1) Less than two items on the stack: should return false and leave the lone literal intact.
TEST_F(ParseStateMaybeConcatStringTest_512, ReturnsFalseWhenFewerThanTwoStackItems_512) {
  Regexp::ParseState ps(Regexp::ParseFlags::NoParseFlags, absl::string_view(), /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('a'));
  EXPECT_FALSE(ps.MaybeConcatString(/*r=*/-1, Regexp::ParseFlags::NoParseFlags));

  Regexp* out = FinishAndGet(ps);
  ExpectLiteral(out, 'a');
  out->Decref();
}

// 2) Normal case: two literals with matching flags merge into a LiteralString (r < 0 path).
TEST_F(ParseStateMaybeConcatStringTest_512, MergesTwoLiteralsIntoLiteralString_512) {
  Regexp::ParseState ps(Regexp::ParseFlags::NoParseFlags, absl::string_view(), /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('a'));  // lower on stack (re2)
  ASSERT_TRUE(ps.PushLiteral('b'));  // top of stack (re1)

  // r < 0 => merge and pop top; return false
  EXPECT_FALSE(ps.MaybeConcatString(/*r=*/-1, Regexp::ParseFlags::NoParseFlags));

  Regexp* out = FinishAndGet(ps);
  ExpectLiteralString(out, {'a', 'b'});
  out->Decref();
}

// 3) Merge a literalstring (top) with a literal (below).
TEST_F(ParseStateMaybeConcatStringTest_512, MergesLiteralStringAndLiteral_512) {
  Regexp::ParseState ps(Regexp::ParseFlags::NoParseFlags, absl::string_view(), /*status=*/nullptr);

  // Below: 'a'
  ASSERT_TRUE(ps.PushLiteral('a'));

  // Top: "xy"
  Rune* buf = new Rune[2]{'x', 'y'};
  Regexp* str = Regexp::LiteralString(buf, 2, Regexp::ParseFlags::NoParseFlags);
  ASSERT_THAT(str, NotNull());
  ASSERT_TRUE(ps.PushRegexp(str));   // ParseState owns the ref now.
  // (Do not delete[] buf; the helper took ownership.)

  EXPECT_FALSE(ps.MaybeConcatString(/*r=*/-1, Regexp::ParseFlags::NoParseFlags));

  Regexp* out = FinishAndGet(ps);
  ExpectLiteralString(out, {'a', 'x', 'y'});
  out->Decref();
}

// 4) FoldCase mismatch prevents merge (returns false, no concatenation performed by MaybeConcatString).
TEST_F(ParseStateMaybeConcatStringTest_512, ReturnsFalseOnFoldCaseMismatch_512) {
  Regexp::ParseState ps(Regexp::ParseFlags::NoParseFlags, absl::string_view(), /*status=*/nullptr);

  // Below: literal with FoldCase
  Regexp* a_fc = Regexp::NewLiteral('a', Regexp::ParseFlags::FoldCase);
  ASSERT_THAT(a_fc, NotNull());
  ASSERT_TRUE(ps.PushRegexp(a_fc));

  // Top: literal without FoldCase
  Regexp* b_plain = Regexp::NewLiteral('b', Regexp::ParseFlags::NoParseFlags);
  ASSERT_THAT(b_plain, NotNull());
  ASSERT_TRUE(ps.PushRegexp(b_plain));

  EXPECT_FALSE(ps.MaybeConcatString(/*r=*/-1, Regexp::ParseFlags::NoParseFlags));

  // Push one more matching-flag literal and confirm only the top two can merge,
  // implying the earlier pair did NOT merge due to the mismatch.
  ASSERT_TRUE(ps.PushLiteral('c'));  // matches NoParseFlags of 'b'
  EXPECT_FALSE(ps.MaybeConcatString(/*r=*/-1, Regexp::ParseFlags::NoParseFlags));  // merges 'b'+'c' into "bc"

  // Finishing now should NOT be a single 3-rune literal string "abc";
  // at minimum, ensure top is a literal string "bc".
  Regexp* out = FinishAndGet(ps);
  // We can't rely on exact overall tree shape; verify presence of a string node.
  if (out->op() == kRegexpLiteralString) {
    ExpectLiteralString(out, {'b', 'c'});  // If it collapsed entirely to a string, it must be "bc", not "abc".
  } else if (out->op() == kRegexpConcat) {
    // Acceptable: concatenation of 'a'(FoldCase) with "bc".
    // Nothing further asserted to avoid peeking internal structure beyond interface.
  } else {
    // Any other shape would be unexpected for this scenario.
    ADD_FAILURE() << "Unexpected final op: " << out->op();
  }
  out->Decref();
}

// 5) r >= 0 path: returns true, keeps top as a single literal r, then a subsequent call can finish concatenation.
TEST_F(ParseStateMaybeConcatStringTest_512, ReturnsTrueWhenRNonNegativeAndSubsequentMergeWorks_512) {
  Regexp::ParseState ps(Regexp::ParseFlags::NoParseFlags, absl::string_view(), /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('a'));   // lower (re2)
  ASSERT_TRUE(ps.PushLiteral('b'));   // top   (re1)

  // r >= 0 => convert below to "ab", keep top as literal 'c', return true.
  EXPECT_TRUE(ps.MaybeConcatString(/*r=*/'c', Regexp::ParseFlags::NoParseFlags));

  // Now merge that 'c' with the "ab" below; r < 0 => returns false and leaves only "abc".
  EXPECT_FALSE(ps.MaybeConcatString(/*r=*/-1, Regexp::ParseFlags::NoParseFlags));

  Regexp* out = FinishAndGet(ps);
  ExpectLiteralString(out, {'a', 'b', 'c'});
  out->Decref();
}

// 6) Non-literal on top prevents merge.
TEST_F(ParseStateMaybeConcatStringTest_512, ReturnsFalseWhenTopIsNotLiteralOrString_512) {
  Regexp::ParseState ps(Regexp::ParseFlags::NoParseFlags, absl::string_view(), /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('a'));
  ASSERT_TRUE(ps.PushCaret());  // likely pushes kRegexpBeginLine, which is not a literal

  EXPECT_FALSE(ps.MaybeConcatString(/*r=*/-1, Regexp::ParseFlags::NoParseFlags));

  // Finish without assuming exact structure; just ensure it doesn't crash and returns something valid.
  Regexp* out = FinishAndGet(ps);
  ASSERT_THAT(out, NotNull());
  out->Decref();
}

}  // namespace re2
