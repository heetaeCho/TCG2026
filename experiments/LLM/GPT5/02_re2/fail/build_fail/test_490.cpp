// File: parse_pushcaret_test_490.cc

#include "gtest/gtest.h"

// Pull in the public enums/types and Regexp API.
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

// Include the implementation unit to access the internal ParseState type.
// (This does not re-implement logic; it only exposes the public-facing methods
// of ParseState we are allowed to call.)
#include "re2/parse.cc"

namespace re2 {

using ::re2::Regexp;
using ::re2::RegexpOp;
using ::re2::Regexp::ParseFlags;

class PushCaretTest_490 : public ::testing::Test {
protected:
  // Helper to finish and validate we obtained a non-null Regexp*, then return it.
  static Regexp* FinishOrFail(Regexp::ParseState& ps) {
    Regexp* re = ps.DoFinish();
    EXPECT_NE(re, nullptr);
    return re;
  }

  // Helper to clean up a Regexp* safely (RE2 uses ref-counting).
  static void Cleanup(Regexp* re) {
    if (re != nullptr) {
      re->Decref();
    }
  }
};

// Normal operation: Without OneLine flag, PushCaret() should behave as
// beginning-of-line (kRegexpBeginLine).
TEST_F(PushCaretTest_490, BeginLineWhenOneLineNotSet_490) {
  RegexpStatus status;
  const absl::string_view whole = absl::string_view();  // not used by this test
  Regexp::ParseState ps(Regexp::NoParseFlags, whole, &status);

  ASSERT_TRUE(ps.PushCaret()) << "PushCaret should succeed under normal conditions";

  Regexp* re = FinishOrFail(ps);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpBeginLine)
      << "Without OneLine flag, '^' should map to BeginLine";
  Cleanup(re);
}

// Normal operation: With OneLine flag, PushCaret() should behave as
// beginning-of-text (kRegexpBeginText).
TEST_F(PushCaretTest_490, BeginTextWhenOneLineSet_490) {
  RegexpStatus status;
  const absl::string_view whole = absl::string_view();
  Regexp::ParseState ps(static_cast<ParseFlags>(Regexp::OneLine), whole, &status);

  ASSERT_TRUE(ps.PushCaret()) << "PushCaret should succeed under normal conditions";

  Regexp* re = FinishOrFail(ps);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpBeginText)
      << "With OneLine flag, '^' should map to BeginText";
  Cleanup(re);
}

// Bitmask behavior: OneLine combined with other flags should still yield
// beginning-of-text (kRegexpBeginText).
TEST_F(PushCaretTest_490, OneLineBitmaskWithOtherFlags_490) {
  RegexpStatus status;
  const absl::string_view whole = absl::string_view();

  // Combine some arbitrary flags with OneLine to ensure bitmask behavior.
  ParseFlags flags = static_cast<ParseFlags>(
      Regexp::OneLine | Regexp::FoldCase | Regexp::PerlX | Regexp::UnicodeGroups);

  Regexp::ParseState ps(flags, whole, &status);

  ASSERT_TRUE(ps.PushCaret()) << "PushCaret should succeed with mixed flags";

  Regexp* re = FinishOrFail(ps);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), kRegexpBeginText)
      << "When OneLine is set (even with others), '^' should map to BeginText";
  Cleanup(re);
}

// Return value surface check: PushCaret returns a bool (from PushSimpleOp).
// We validate it returns true in a normal scenario; we do NOT simulate failures
// or internal behavior.
TEST_F(PushCaretTest_490, ReturnsTrueOnSuccess_490) {
  RegexpStatus status;
  const absl::string_view whole = absl::string_view();
  Regexp::ParseState ps(Regexp::NoParseFlags, whole, &status);

  EXPECT_TRUE(ps.PushCaret()) << "Expected PushCaret to report success";
  Regexp* re = FinishOrFail(ps);
  Cleanup(re);
}

}  // namespace re2
