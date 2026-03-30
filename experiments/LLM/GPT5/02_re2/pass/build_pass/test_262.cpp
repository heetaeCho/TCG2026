// File: re2_match_test_262.cc
#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"          // Public RE2 interface
#include "absl/strings/string_view.h"

using re2::RE2;

// Test fixture kept minimal; we only use the public interface.
class RE2MatchTest_262 : public ::testing::Test {};

// --- Error / validation paths that do not depend on internal engine state ---

// If the regex is invalid (ok() == false), Match must return false immediately.
TEST_F(RE2MatchTest_262, InvalidPatternReturnsFalse_262) {
  RE2 re("(");  // Typically invalid; ok() should be false.
  absl::string_view* submatches = nullptr;  // nsubmatch = 0 → ignored
  const bool ok = re.Match("anything", /*startpos=*/0, /*endpos=*/0,
                           RE2::UNANCHORED, submatches, /*nsubmatch=*/0);
  EXPECT_FALSE(ok);
}

// startpos > endpos is invalid and should return false.
TEST_F(RE2MatchTest_262, StartGreaterThanEndReturnsFalse_262) {
  RE2 re("a");
  absl::string_view* submatches = nullptr;  // nsubmatch = 0 → ignored
  const std::string text = "a";
  const bool ok = re.Match(text, /*startpos=*/2, /*endpos=*/1,
                           RE2::UNANCHORED, submatches, /*nsubmatch=*/0);
  EXPECT_FALSE(ok);
}

// endpos > text.size() is invalid and should return false.
TEST_F(RE2MatchTest_262, EndBeyondTextReturnsFalse_262) {
  RE2 re("a");
  absl::string_view* submatches = nullptr;  // nsubmatch = 0 → ignored
  const std::string text = "a";
  const bool ok = re.Match(text, /*startpos=*/0, /*endpos=*/text.size() + 1,
                           RE2::UNANCHORED, submatches, /*nsubmatch=*/0);
  EXPECT_FALSE(ok);
}

// --- Normal operation paths (observable via return values and submatch outputs) ---

// Simple anchored full match with one submatch slot: expect success and submatch[0] = full match.
TEST_F(RE2MatchTest_262, AnchoredFullMatchCapturesWholeText_262) {
  RE2 re("a");
  const std::string text = "a";
  absl::string_view subs[1];
  const bool ok = re.Match(text, /*startpos=*/0, /*endpos=*/text.size(),
                           RE2::ANCHOR_BOTH, subs, /*nsubmatch=*/1);
  ASSERT_TRUE(ok);
  EXPECT_EQ(subs[0], "a");
}

// Same match with nsubmatch = 0: should still succeed; we just don't request captures.
TEST_F(RE2MatchTest_262, NsubmatchZeroStillAllowsSuccessfulMatch_262) {
  RE2 re("a");
  const std::string text = "a";
  const bool ok = re.Match(text, /*startpos=*/0, /*endpos=*/text.size(),
                           RE2::ANCHOR_BOTH, /*submatch=*/nullptr, /*nsubmatch=*/0);
  EXPECT_TRUE(ok);
}

// When nsubmatch exceeds the number of captures+1, trailing entries must be set to empty.
TEST_F(RE2MatchTest_262, ExcessSubmatchSlotsAreClearedToEmpty_262) {
  // Pattern with two capturing groups.
  RE2 re("(a)(b)");
  const std::string text = "ab";

  // Request more submatch slots than available (full match + 2 groups = 3).
  absl::string_view subs[5];
  // Initialize to non-empty to ensure the function actively clears them.
  for (auto& s : subs) s = "pre-filled";

  const bool ok = re.Match(text, /*startpos=*/0, /*endpos=*/text.size(),
                           RE2::ANCHOR_BOTH, subs, /*nsubmatch=*/5);
  ASSERT_TRUE(ok);

  // We don't assert exact contents of the actual matches beyond observable contract,
  // but we can assert the *extra* slots are cleared to empty views.
  EXPECT_TRUE(subs[3].empty());
  EXPECT_TRUE(subs[4].empty());
}
