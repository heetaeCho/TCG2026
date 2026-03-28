// File: parse_push_simple_op_test_494.cc

#include <gtest/gtest.h>
#include "absl/strings/string_view.h"

// NOTE: ParseState is defined in parse.cc as an internal nested class.
// To test its public interface without re-implementing logic or touching private state,
// we include the TU that defines it. This pattern keeps us within a black-box boundary
// for behavior while giving us access to the public methods we need to call.
#include "re2/parse.cc"

using re2::Regexp;
using re2::RegexpStatus;

// RE2 op enum lives in the same TU; we rely on the public names used by the implementation.
namespace {

class PushSimpleOpTest_494 : public ::testing::Test {
protected:
  // Helper to build a fresh ParseState for each test.
  // We keep flags at 0 unless a test requires something else, to avoid inferring internals.
  Regexp::ParseState MakeState(absl::string_view whole = absl::string_view()) {
    // flags = 0 (no assumptions), status non-null, whole pattern optional
    return Regexp::ParseState(/*flags=*/0, whole, &status_);
  }

  // Simple guard to finish and clean up any constructed regexps.
  // DoFinish() returns ownership; we must delete to prevent leaks.
  void FinishAndDelete(Regexp::ParseState& ps) {
    Regexp* re = ps.DoFinish();
    delete re;  // re may be nullptr; delete nullptr is safe
  }

  RegexpStatus status_;
};

// [Normal] For a "dot" token, PushDot() and PushSimpleOp(kRegexpAnyChar)
// should exhibit the same observable result (bool return).
TEST_F(PushSimpleOpTest_494, DotMatchesSimpleOpAnyChar_494) {
  auto ps = MakeState(".");
  // Compare observable return values only.
  bool via_dot = ps.PushDot();
  bool via_simple = ps.PushSimpleOp(re2::kRegexpAnyChar);
  EXPECT_EQ(via_dot, via_simple);

  // Finishing is part of observable behavior: should not crash; may return nullptr or non-null.
  FinishAndDelete(ps);
}

// [Normal] For line-start anchor, PushCaret() and PushSimpleOp(kRegexpBeginLine)
// should behave equivalently at the interface level.
TEST_F(PushSimpleOpTest_494, CaretMatchesSimpleOpBeginLine_494) {
  auto ps = MakeState("^");
  bool via_caret = ps.PushCaret();
  bool via_simple = ps.PushSimpleOp(re2::kRegexpBeginLine);
  EXPECT_EQ(via_caret, via_simple);
  FinishAndDelete(ps);
}

// [Normal] For line-end anchor, PushDollar() and PushSimpleOp(kRegexpEndLine)
// should behave equivalently at the interface level.
TEST_F(PushSimpleOpTest_494, DollarMatchesSimpleOpEndLine_494) {
  auto ps = MakeState("$");
  bool via_dollar = ps.PushDollar();
  bool via_simple = ps.PushSimpleOp(re2::kRegexpEndLine);
  EXPECT_EQ(via_dollar, via_simple);
  FinishAndDelete(ps);
}

// [Boundary] Calling PushSimpleOp with a “simple” op on an empty pattern context
// should still return a deterministic bool and allow DoFinish() to be invoked safely.
// We don’t assert internal structure, only that it’s safe to complete.
TEST_F(PushSimpleOpTest_494, SimpleOpOnEmptyInputIsFinishable_494) {
  auto ps = MakeState("");  // empty input
  bool ok = ps.PushSimpleOp(re2::kRegexpAnyChar);
  // The exact truth value is implementation-defined; just assert it’s a bool and
  // that finishing doesn’t crash. We still record it to avoid unused-warning style issues.
  (void)ok;
  FinishAndDelete(ps);
}

}  // namespace
