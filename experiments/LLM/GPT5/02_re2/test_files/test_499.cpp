// File: parse_state_pushrepetition_test_499.cc

#include "gtest/gtest.h"
#include "re2/parse.cc"          // Provides re2::Regexp::ParseState (as given)
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

using namespace re2;

class RegexpParseStateTest_499 : public ::testing::Test {
protected:
  RegexpStatus status_;
  // Use NoParseFlags and any placeholder whole-regexp string.
  Regexp::ParseState MakeState() {
    return Regexp::ParseState(Regexp::NoParseFlags, absl::string_view("whole"), &status_);
  }
  void SetUp() override {
    // Ensure a known default maximum for repeat counts across tests.
    Regexp::FUZZING_ONLY_set_maximum_repeat_count(1000);
  }
  void TearDown() override {
    Regexp::FUZZING_ONLY_set_maximum_repeat_count(1000);
  }
};

// Normal operation: with a preceding atom on the stack, min==max==1 should succeed
// and leave status OK. This path also avoids the RepetitionWalker >=2 check.
TEST_F(RegexpParseStateTest_499, PushRepetition_ValidSimple_499) {
  auto ps = MakeState();
  ASSERT_TRUE(ps.PushLiteral(static_cast<Rune>('x')));
  EXPECT_TRUE(status_.ok());

  const absl::string_view s = "{1}";
  EXPECT_TRUE(ps.PushRepetition(1, 1, s, /*nongreedy=*/false));
  EXPECT_TRUE(status_.ok());
}

// Error: max < min -> kRegexpRepeatSize and error_arg set to s.
TEST_F(RegexpParseStateTest_499, PushRepetition_InvalidSize_MaxLessThanMin_499) {
  auto ps = MakeState();
  ASSERT_TRUE(ps.PushLiteral(static_cast<Rune>('a')));
  EXPECT_TRUE(status_.ok());

  const absl::string_view s = "{3,2}";
  EXPECT_FALSE(ps.PushRepetition(3, 2, s, /*nongreedy=*/false));
  EXPECT_EQ(status_.code(), kRegexpRepeatSize);
  EXPECT_EQ(status_.error_arg(), s);
}

// Error: min exceeds maximum_repeat_count -> kRegexpRepeatSize.
TEST_F(RegexpParseStateTest_499, PushRepetition_InvalidSize_MinTooLarge_499) {
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(5);

  auto ps = MakeState();
  ASSERT_TRUE(ps.PushLiteral(static_cast<Rune>('b')));
  EXPECT_TRUE(status_.ok());

  const absl::string_view s = "{6}";
  EXPECT_FALSE(ps.PushRepetition(6, 6, s, /*nongreedy=*/false));
  EXPECT_EQ(status_.code(), kRegexpRepeatSize);
  EXPECT_EQ(status_.error_arg(), s);
}

// Error: max exceeds maximum_repeat_count -> kRegexpRepeatSize.
TEST_F(RegexpParseStateTest_499, PushRepetition_InvalidSize_MaxTooLarge_499) {
  Regexp::FUZZING_ONLY_set_maximum_repeat_count(2);

  auto ps = MakeState();
  ASSERT_TRUE(ps.PushLiteral(static_cast<Rune>('c')));
  EXPECT_TRUE(status_.ok());

  const absl::string_view s = "{1,3}";
  EXPECT_FALSE(ps.PushRepetition(1, 3, s, /*nongreedy=*/false));
  EXPECT_EQ(status_.code(), kRegexpRepeatSize);
  EXPECT_EQ(status_.error_arg(), s);
}

// Error: no preceding atom on the stack -> kRegexpRepeatArgument.
TEST_F(RegexpParseStateTest_499, PushRepetition_ErrorWhenNoPreviousAtom_499) {
  auto ps = MakeState();

  const absl::string_view s = "{1}";
  EXPECT_FALSE(ps.PushRepetition(1, 1, s, /*nongreedy=*/false));
  EXPECT_EQ(status_.code(), kRegexpRepeatArgument);
  EXPECT_EQ(status_.error_arg(), s);
}

// Normal operation: min=0, max=-1 (unbounded) should be allowed and succeed with a prior atom.
// This also avoids the >=2 RepetitionWalker path.
TEST_F(RegexpParseStateTest_499, PushRepetition_ZeroToInfinity_Succeeds_499) {
  auto ps = MakeState();
  ASSERT_TRUE(ps.PushLiteral(static_cast<Rune>('z')));
  EXPECT_TRUE(status_.ok());

  const absl::string_view s = "{0,}";
  EXPECT_TRUE(ps.PushRepetition(0, -1, s, /*nongreedy=*/true));
  EXPECT_TRUE(status_.ok());
}
