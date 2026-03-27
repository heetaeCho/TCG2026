// File: onepass_search_unittest_567.cc
#include <gtest/gtest.h>
#include "re2/prog.h"
#include "absl/strings/string_view.h"

using re2::Prog;
using re2::Prog::MatchKind;

// Some RE2 builds expose Anchor via re2::RE2::Anchor; many internal
// tests typedef/using it into the re2 namespace as Anchor.
// If needed, adjust these to match your project’s Anchor enum.
using Anchor = RE2::Anchor;  // or: using Anchor = re2::Anchor;
using ::RE2::ANCHOR_START;   // kAnchored
using ::RE2::UNANCHORED;     // not kAnchored

class SearchOnePassTest_567 : public ::testing::Test {
protected:
  Prog prog_;
};

// 1) Guard: Using SearchOnePass with UNANCHORED and kind != kFullMatch returns false.
//    This path exits before any node/state access and should be safe with nmatch == 0.
TEST_F(SearchOnePassTest_567, UnanchoredAndNotFullMatch_ReturnsFalse_567) {
  const absl::string_view text("hello");
  // nmatch == 0 and match == nullptr are valid: early guard returns before use.
  const int nmatch = 0;
  absl::string_view* match = nullptr;

  const bool ok = prog_.SearchOnePass(
      text,
      /*context=*/text,
      /*anchor=*/UNANCHORED,
      /*kind=*/MatchKind::kFirstMatch,
      /*match=*/match,
      /*nmatch=*/nmatch);

  EXPECT_FALSE(ok);
}

// 2) Guard: anchor_start() causes early return if BeginPtr(context) != BeginPtr(text).
//    We set anchor_start to true and pass a *different* context buffer.
TEST_F(SearchOnePassTest_567, AnchorStart_MismatchedContextBegin_ReturnsFalse_567) {
  prog_.set_anchor_start(true);

  const std::string base = "abc";
  const std::string different_context = "xxxabc";  // different buffer -> different begin ptr
  const absl::string_view text(base);
  const absl::string_view context(different_context);

  absl::string_view captures[1];  // nmatch = 1
  const bool ok = prog_.SearchOnePass(
      text,
      context,
      /*anchor=*/ANCHOR_START,             // kAnchored
      /*kind=*/MatchKind::kFirstMatch,
      /*match=*/captures,
      /*nmatch=*/1);

  EXPECT_FALSE(ok);
  // Since the function returns early, it must not write to captures.
  EXPECT_TRUE(captures[0].empty());
}

// 3) Guard: anchor_end() causes early return if EndPtr(context) != EndPtr(text).
//    We set anchor_end to true and pass a *different* context buffer so end ptr differs.
TEST_F(SearchOnePassTest_567, AnchorEnd_MismatchedContextEnd_ReturnsFalse_567) {
  prog_.set_anchor_end(true);

  const std::string base = "abc";
  const std::string different_context = "abczzz";  // different buffer -> different end ptr
  const absl::string_view text(base);
  const absl::string_view context(different_context);

  absl::string_view captures[1];  // nmatch = 1
  const bool ok = prog_.SearchOnePass(
      text,
      context,
      /*anchor=*/ANCHOR_START,             // kAnchored
      /*kind=*/MatchKind::kFirstMatch,
      /*match=*/captures,
      /*nmatch=*/1);

  EXPECT_FALSE(ok);
  EXPECT_TRUE(captures[0].empty());
}

// 4) Coverage for kind == kFullMatch with UNANCHORED anchor:
//    The first guard allows calling when kind == kFullMatch even if anchor != kAnchored.
//    We still trigger a safe, observable early exit via anchor_end() mismatch.
TEST_F(SearchOnePassTest_567, UnanchoredButFullMatch_AnchorEndMismatch_ReturnsFalse_567) {
  prog_.set_anchor_end(true);

  const std::string base = "matchme";
  const std::string different_context = "prefix-" + base;  // different end pointer
  const absl::string_view text(base);
  const absl::string_view context(different_context);

  absl::string_view captures[1];
  const bool ok = prog_.SearchOnePass(
      text,
      context,
      /*anchor=*/UNANCHORED,               // not kAnchored, but kind == kFullMatch is allowed
      /*kind=*/MatchKind::kFullMatch,
      /*match=*/captures,
      /*nmatch=*/1);

  EXPECT_FALSE(ok);
  EXPECT_TRUE(captures[0].empty());
}
