#include <gtest/gtest.h>

// RE2 headers (as provided in the project stubs)
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

namespace re2 {

// Forward-declare RegexpStatus since we only pass a pointer (no need for definition).
class RegexpStatus;

class PushLiteralTest_489 : public ::testing::Test {
 protected:
  // Helper to build a fresh ParseState.
  Regexp::ParseState MakeState(Regexp::ParseFlags flags) {
    absl::string_view empty;
    RegexpStatus* status = nullptr;
    return Regexp::ParseState(flags, empty, status);
  }
};

// FoldCase + Latin1 with an ASCII letter should create a CharClass and fold to include both cases.
TEST_F(PushLiteralTest_489, FoldCaseLatin1_BuildsCharClassAndFoldsASCII_489) {
  Regexp::ParseState ps(static_cast<Regexp::ParseFlags>(Regexp::FoldCase | Regexp::Latin1),
                        absl::string_view(), /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('A'));

  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);

  // Expect a character class node was produced.
  // (We rely on the public opcode accessor and public ccb_ pointer from the provided stubs.)
  // kRegexpCharClass is the observable op for this path.
  EXPECT_EQ(re->op(), kRegexpCharClass);

  ASSERT_NE(re->ccb_, nullptr);
  // Observable behavior: folded ASCII should include both 'A' and 'a'.
  EXPECT_TRUE(re->ccb_->Contains('A'));
  EXPECT_TRUE(re->ccb_->Contains('a'));
}

// FoldCase without Latin1 (Unicode folding path) for an ASCII letter should also yield a CharClass
// that contains both cases.
TEST_F(PushLiteralTest_489, FoldCaseUnicode_BuildsCharClassAndFoldsASCII_489) {
  Regexp::ParseState ps(Regexp::FoldCase, absl::string_view(), /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('Z'));

  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpCharClass);

  ASSERT_NE(re->ccb_, nullptr);
  EXPECT_TRUE(re->ccb_->Contains('Z'));
  EXPECT_TRUE(re->ccb_->Contains('z'));
}

// NeverNL + '\n' must compile to a NoMatch node (observable via opcode).
TEST_F(PushLiteralTest_489, NeverNL_NewlineYieldsNoMatch_489) {
  Regexp::ParseState ps(Regexp::NeverNL, absl::string_view(), /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('\n'));

  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
  // For sanity: a NoMatch node is not a char class.
  EXPECT_EQ(re->ccb_, nullptr);
}

// With FoldCase + Latin1, a non-letter (e.g., '1') should NOT build a CharClass;
// it should be represented as a literal (or literal-string), but definitely not CharClass.
TEST_F(PushLiteralTest_489, FoldCaseLatin1_NonLetterIsNotCharClass_489) {
  Regexp::ParseState ps(static_cast<Regexp::ParseFlags>(Regexp::FoldCase | Regexp::Latin1),
                        absl::string_view(), /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('1'));

  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  // We only assert what the interface guarantees here: it should not be a char class.
  EXPECT_NE(re->op(), kRegexpCharClass);
  // (It may be kRegexpLiteral or kRegexpLiteralString depending on internal concatenation;
  //  we don't assume which one.)
}

// Even when FoldCase is present, NeverNL must still take precedence for '\n' and yield NoMatch.
TEST_F(PushLiteralTest_489, FoldCaseAndNeverNL_NewlineStillNoMatch_489) {
  Regexp::ParseState ps(static_cast<Regexp::ParseFlags>(Regexp::FoldCase | Regexp::NeverNL),
                        absl::string_view(), /*status=*/nullptr);

  ASSERT_TRUE(ps.PushLiteral('\n'));

  Regexp* re = ps.DoFinish();
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpNoMatch);
}

}  // namespace re2
