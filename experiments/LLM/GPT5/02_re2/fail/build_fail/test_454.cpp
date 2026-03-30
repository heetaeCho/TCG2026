// File: ./TestProjects/re2/tests/prog_searchdfa_454_test.cc
#include "gtest/gtest.h"
#include "re2/prog.h"
#include "absl/strings/string_view.h"

using re2::Prog;

class ProgSearchDFATest_454 : public ::testing::Test {
protected:
  Prog prog_;  // Treat as a black box. Only use public setters/getters.
};

// Verifies: If anchor_start() is true and the context does not begin at the
// same address as text, SearchDFA returns false without touching match0.
TEST_F(ProgSearchDFATest_454, AnchorStart_MismatchedContextStartReturnsFalse_454) {
  // Arrange
  prog_.set_anchor_start(true);
  const std::string s = "hello";
  absl::string_view text(s.data(), s.size());
  // Context begins at s.data()+1 => different begin pointer than text
  absl::string_view context(s.data() + 1, s.size() - 1);

  bool failed = true;  // should be set to false by SearchDFA at entry
  absl::string_view match0 = "unchanged";

  // Act
  const bool ok = prog_.SearchDFA(
      text,
      context,
      /*anchor=*/static_cast<re2::Anchor>(0), // value is irrelevant to this early check
      /*kind=*/Prog::kFirstMatch,
      /*match0=*/&match0,
      /*failed=*/&failed,
      /*matches=*/nullptr);

  // Assert
  EXPECT_FALSE(ok);
  EXPECT_FALSE(failed);                // explicitly cleared at function start
  EXPECT_EQ(match0, "unchanged");      // not modified on early-return false
}

// Verifies: If anchor_end() is true and the context does not end at the same
// address as text, SearchDFA returns false early.
TEST_F(ProgSearchDFATest_454, AnchorEnd_MismatchedContextEndReturnsFalse_454) {
  prog_.set_anchor_end(true);
  const std::string s = "world";
  absl::string_view text(s.data(), s.size());
  // Context ends before the end of text => different end pointer
  absl::string_view context(s.data(), s.size() - 1);

  bool failed = true;
  // Pass nullptr for match0 to also cover that branch safely.
  const bool ok = prog_.SearchDFA(
      text,
      context,
      /*anchor=*/static_cast<re2::Anchor>(0),
      /*kind=*/Prog::kFirstMatch,
      /*match0=*/nullptr,
      /*failed=*/&failed,
      /*matches=*/nullptr);

  EXPECT_FALSE(ok);
  EXPECT_FALSE(failed);
}

// Verifies: When reversed() is true, caret/dollar are swapped.
// Setting anchor_end(true) should trigger the *start* mismatch check after swap.
TEST_F(ProgSearchDFATest_454, Reversed_SwapsAnchors_EndActsLikeStartMismatch_454) {
  prog_.set_reversed(true);
  prog_.set_anchor_end(true);  // Will act like anchor_start() after swap

  const std::string s = "abcdef";
  absl::string_view text(s.data(), s.size());
  // Start mismatch: context starts at +2
  absl::string_view context(s.data() + 2, s.size() - 2);

  bool failed = true;
  absl::string_view match0("keep");

  const bool ok = prog_.SearchDFA(
      text,
      context,
      /*anchor=*/static_cast<re2::Anchor>(0),
      /*kind=*/Prog::kFirstMatch,
      /*match0=*/&match0,
      /*failed=*/&failed,
      /*matches=*/nullptr);

  EXPECT_FALSE(ok);
  EXPECT_FALSE(failed);
  EXPECT_EQ(match0, "keep");
}

// Verifies: When reversed() is true, caret/dollar are swapped.
// Setting anchor_start(true) should trigger the *end* mismatch check after swap.
TEST_F(ProgSearchDFATest_454, Reversed_SwapsAnchors_StartActsLikeEndMismatch_454) {
  prog_.set_reversed(true);
  prog_.set_anchor_start(true);  // Will act like anchor_end() after swap

  const std::string s = "abcdef";
  absl::string_view text(s.data(), s.size());
  // End mismatch: context ends before text's end
  absl::string_view context(s.data(), s.size() - 1);

  bool failed = true;

  const bool ok = prog_.SearchDFA(
      text,
      context,
      /*anchor=*/static_cast<re2::Anchor>(0),
      /*kind=*/Prog::kFirstMatch,
      /*match0=*/nullptr,
      /*failed=*/&failed,
      /*matches=*/nullptr);

  EXPECT_FALSE(ok);
  EXPECT_FALSE(failed);
}
