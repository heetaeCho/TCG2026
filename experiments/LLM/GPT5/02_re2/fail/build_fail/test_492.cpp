// File: parse_pushdollar_test_492.cc

#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/parse.h"              // Declares re2::Regexp::ParseState
#include "absl/strings/string_view.h"

using re2::Regexp;
using re2::RegexpOp;
using re2::RegexpStatus;

class ParseStateTest_492 : public ::testing::Test {
protected:
  // Helper to build a ParseState with given flags.
  Regexp::ParseState MakeState(Regexp::ParseFlags flags) {
    RegexpStatus status;
    absl::string_view whole("");
    return Regexp::ParseState(flags, whole, &status);
  }

  // Finish and return the built Regexp* for observation.
  Regexp* Finish(Regexp::ParseState& ps) {
    return ps.DoFinish();
  }
};

// Normal operation: Without OneLine flag, $ should behave as EndLine.
TEST_F(ParseStateTest_492, PushDollar_Default_PushesEndLine_492) {
  auto ps = MakeState(Regexp::NoParseFlags);
  ASSERT_TRUE(ps.PushDollar());                  // Observable: returns bool

  Regexp* re = Finish(ps);                       // Observable: resulting AST root
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), re2::kRegexpEndLine);      // Observable: opcode only
}

// Normal operation: With OneLine flag, $ should behave as EndText.
TEST_F(ParseStateTest_492, PushDollar_OneLine_PushesEndText_492) {
  auto ps = MakeState(static_cast<Regexp::ParseFlags>(Regexp::OneLine));
  ASSERT_TRUE(ps.PushDollar());

  Regexp* re = Finish(ps);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), re2::kRegexpEndText);
}

// Boundary/flag interaction: If WasDollar is already present with OneLine,
// behavior should still produce EndText and not leak altered flags externally.
TEST_F(ParseStateTest_492, PushDollar_OneLineWithWasDollar_PushesEndText_492) {
  auto ps = MakeState(static_cast<Regexp::ParseFlags>(Regexp::OneLine | Regexp::WasDollar));
  ASSERT_TRUE(ps.PushDollar());

  Regexp* re = Finish(ps);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), re2::kRegexpEndText);
}
