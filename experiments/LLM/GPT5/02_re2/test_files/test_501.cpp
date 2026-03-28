// File: parse_do_left_paren_test_501.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"           // for re2::Regexp (public fields used by tests)
#include "re2/parse.cc"           // for re2::Regexp::ParseState
#include "absl/strings/string_view.h"

using re2::Regexp;

// NOTE: We treat ParseState as a black box and only use its public methods.
// We do not re-implement or infer internal logic; we only assert on effects
// visible through public APIs (DoLeftParen return value and the Regexp*
// returned by DoFinish()).

class DoLeftParenTest_501 : public ::testing::Test {
protected:
  // Utility that builds a fresh ParseState with minimal inputs.
  // We don't assert anything about flags/whole/status values;
  // they are just placeholders to satisfy the ctor.
  Regexp::ParseState MakeState() {
    // Using zero-y ParseFlags and empty whole_regexp/status pointer is fine
    // for black-box tests as long as the interface accepts them.
    // If your build expects concrete enums, use a default-constructed value.
    re2::Regexp::ParseFlags flags{};                 // default-initialize
    absl::string_view whole;                         // empty
    re2::RegexpStatus* status = nullptr;            // nullptr is allowed by ctor
    return Regexp::ParseState(flags, whole, status);
  }

  // Helper to finish and return the top-level Regexp* for observation.
  // We do not assume ownership semantics beyond what DoFinish() returns;
  // tests only read the observable fields exposed as public in this harness.
  Regexp* Finish(Regexp::ParseState& s) {
    return s.DoFinish();
  }
};

// Normal case: non-empty capture name -> name_ set, cap_ starts at 1
TEST_F(DoLeftParenTest_501, NamedCapture_SetsNameAndCapTo1_501) {
  auto state = MakeState();

  const absl::string_view name = "groupA";
  ASSERT_TRUE(state.DoLeftParen(name));  // should delegate to PushRegexp and succeed

  Regexp* re = Finish(state);
  ASSERT_NE(re, nullptr);                // observable result is a Regexp*

  // Observable public fields (per provided test harness headers)
  EXPECT_EQ(re->cap_, 1);
  ASSERT_NE(re->name_, nullptr);
  EXPECT_EQ(*re->name_, "groupA");
}

// Boundary: default-constructed string_view (data()==nullptr) -> name_ should remain nullptr
TEST_F(DoLeftParenTest_501, DefaultStringView_LeavesNameNullAndSetsCap_501) {
  auto state = MakeState();

  absl::string_view null_name;           // data() == nullptr by default
  ASSERT_TRUE(state.DoLeftParen(null_name));

  Regexp* re = Finish(state);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->cap_, 1);
  EXPECT_EQ(re->name_, nullptr);         // since data()==nullptr, name_ must not be allocated
}

// Boundary: empty but non-null string_view (e.g., "") -> name_ allocated to empty string
TEST_F(DoLeftParenTest_501, EmptyButNonNullName_AllocatesEmptyNameString_501) {
  auto state = MakeState();

  const absl::string_view empty_nonnull = "";  // data()!=nullptr, size()==0
  ASSERT_TRUE(state.DoLeftParen(empty_nonnull));

  Regexp* re = Finish(state);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->cap_, 1);
  ASSERT_NE(re->name_, nullptr);
  EXPECT_TRUE(re->name_->empty());
}

// Sequencing: multiple left-parens increment cap across calls (1 then 2)
TEST_F(DoLeftParenTest_501, MultipleCalls_IncrementCap_501) {
  auto state = MakeState();

  ASSERT_TRUE(state.DoLeftParen("first"));
  Regexp* re1 = Finish(state);
  ASSERT_NE(re1, nullptr);
  EXPECT_EQ(re1->cap_, 1);
  ASSERT_NE(re1->name_, nullptr);
  EXPECT_EQ(*re1->name_, "first");

  // Do a second left-paren on a fresh state to observe the next cap value.
  // If your environment retains state across Finish(), this checks that
  // cap increments for subsequent DoLeftParen calls.
  // (We keep using the same state to reflect observable sequencing.)
  ASSERT_TRUE(state.DoLeftParen("second"));
  Regexp* re2 = Finish(state);
  ASSERT_NE(re2, nullptr);
  EXPECT_EQ(re2->cap_, 2);
  ASSERT_NE(re2->name_, nullptr);
  EXPECT_EQ(*re2->name_, "second");
}

// Return value propagation: DoLeftParen returns the same boolean as PushRegexp.
// We assert success path is true (observable).
TEST_F(DoLeftParenTest_501, ReturnValue_SuccessPathTrue_501) {
  auto state = MakeState();
  EXPECT_TRUE(state.DoLeftParen("ok"));
  // We still call DoFinish to keep state consistent for the class.
  Regexp* re = Finish(state);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->cap_, 1);
}
