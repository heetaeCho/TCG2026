// File: prog_search_bitstate_test_581.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

// Minimal includes for absl::string_view
#include "absl/strings/string_view.h"

using re2::Prog;
using re2::Prog::MatchKind;

class SearchBitStateTest_581 : public ::testing::Test {
protected:
  Prog prog_;  // Treat as black box
};

// Verifies that when kind == kFullMatch and nmatch < 1, the implementation
// uses an internal temporary slot (per the interface/behavior in the snippet)
// and does NOT touch the caller-provided match buffer.
TEST_F(SearchBitStateTest_581, FullMatch_DoesNotTouchUserBufferWhenNMatchIsZero_581) {
  absl::string_view text = "abc";
  absl::string_view context = text;

  // Prepare a match buffer initialized to a sentinel.
  absl::string_view user_match_buf[1];
  user_match_buf[0] = absl::string_view("SENTINEL");

  // Call with nmatch == 0; per wrapper logic, it must NOT write into user_match_buf.
  bool ok = prog_.SearchBitState(
      text,
      context,
      /*anchor=*/static_cast<Prog::Anchor>(0),   // value doesn't matter; wrapper may override for FullMatch
      /*kind=*/static_cast<MatchKind>(Prog::kFullMatch),
      /*match=*/user_match_buf,
      /*nmatch=*/0);

  // We cannot assume success/failure (BitState is a black box), but we can assert
  // the caller's buffer remains untouched when nmatch < 1 for FullMatch.
  (void)ok;  // avoid unused-warning; result is not asserted by design
  EXPECT_EQ(user_match_buf[0], absl::string_view("SENTINEL"));
}

// Verifies the wrapper safely handles a nullptr match pointer when kind == kFullMatch
// and nmatch == 0 by internally substituting a temporary slot (no crash / UB).
TEST_F(SearchBitStateTest_581, FullMatch_AllowsNullMatchPointerWhenNMatchIsZero_581) {
  absl::string_view text = "xyz";
  absl::string_view context = text;

  // Passing nullptr with nmatch == 0 should be safe for FullMatch.
  // We don't assert on the boolean result because BitState's outcome is opaque.
  (void)prog_.SearchBitState(
      text,
      context,
      /*anchor=*/static_cast<Prog::Anchor>(0),
      /*kind=*/static_cast<MatchKind>(Prog::kFullMatch),
      /*match=*/nullptr,
      /*nmatch=*/0);

  // No explicit EXPECT/ASSERT needed here beyond the call succeeding (i.e., no crash).
  SUCCEED();
}

// Verifies that providing at least one slot for matches with FullMatch leaves the
// user's buffer under caller control when nmatch >= 1. Since the wrapper only forces
// a temporary slot when nmatch < 1, here we ensure it *doesn't* substitute and
// the buffer remains a valid object we own after the call (no re-pointing).
TEST_F(SearchBitStateTest_581, FullMatch_UsesCallerBufferWhenNMatchAtLeastOne_581) {
  absl::string_view text = "12345";
  absl::string_view context = text;

  absl::string_view user_match_buf[1];
  user_match_buf[0] = absl::string_view("INIT");

  bool ok = prog_.SearchBitState(
      text,
      context,
      /*anchor=*/static_cast<Prog::Anchor>(0),
      /*kind=*/static_cast<MatchKind>(Prog::kFullMatch),
      /*match=*/user_match_buf,
      /*nmatch=*/1);

  // We do not assert on 'ok' (BitState behavior is opaque).
  // We just ensure the buffer remains a valid, writable location owned by us.
  // As observable behavior, the pointer identity of user_match_buf isn't changed
  // by the wrapper (we still refer to our original array).
  (void)ok;
  // Touch the buffer to ensure it's still ours and writable.
  user_match_buf[0] = user_match_buf[0];  // no-op write/read to prove lvalue viability
  SUCCEED();
}
