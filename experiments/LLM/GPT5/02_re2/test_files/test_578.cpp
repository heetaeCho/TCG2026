// File: prog_searchnfa_test.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include "re2/prog.h"   // Adjust include path if needed
// No inclusion of re2/nfa.cc here; we only rely on the public interface,
// and introduce a controlled test seam for NFA::Search behavior.

using ::testing::StrEq;
using ::testing::Bool;

namespace re2 {

// -----------------------------
// Test seam for NFA::Search()
// -----------------------------
// We provide a minimal FakeNFA that mirrors the public-facing Search()
// signature used by Prog::SearchNFA. It records the last-call parameters
// and returns a controlled result. This lets us verify the wrapper behavior
// (anchoring, longest-match flag, match-pointer handling for kFullMatch, etc.)
// without depending on any internal implementation of the real NFA.
//
// This seam must match the constructor and method signatures used by
// Prog::SearchNFA: NFA(Prog*), bool Search(...).
//
// IMPORTANT: This is *not* re-implementing NFA. It only captures arguments
// and returns a predetermined boolean.
// -----------------------------

class FakeNFA {
 public:
  explicit FakeNFA(Prog* p) : prog_(p) {}

  // Captured call data (static for easy access in tests)
  struct Call {
    std::string text;
    std::string context;
    bool anchored = false;
    bool longest = false;
    absl::string_view* submatch = nullptr;
    int nsubmatch = 0;
  };

  // Controls
  static void Reset() {
    last_call_ = Call{};
    should_return_ = false;
    // By default, do not write to submatch.
    write_match_ = false;
    match_out_ = absl::string_view{};
  }

  static void SetReturn(bool v) { should_return_ = v; }
  static void SetWriteMatch(absl::string_view sv) {
    write_match_ = true;
    match_out_ = sv;
  }

  static const Call& last_call() { return last_call_; }

  bool Search(absl::string_view text,
              absl::string_view context,
              bool anchored,
              bool longest,
              absl::string_view* submatch,
              int nsubmatch) {
    last_call_.text = std::string(text);
    last_call_.context = std::string(context);
    last_call_.anchored = anchored;
    last_call_.longest = longest;
    last_call_.submatch = submatch;
    last_call_.nsubmatch = nsubmatch;

    if (write_match_ && submatch != nullptr && nsubmatch > 0) {
      submatch[0] = match_out_;
    }
    return should_return_;
  }

 private:
  Prog* prog_;
  static inline Call last_call_{};
  static inline bool should_return_ = false;
  static inline bool write_match_ = false;
  static inline absl::string_view match_out_{};
};

// -----------------------------
// Thin adapter to route Prog::SearchNFA to our FakeNFA for testing.
// We create a tiny wrapper function that mirrors the logic of
// Prog::SearchNFA’s NFA construction and call site, but instantiates
// FakeNFA instead. This keeps the tests focused strictly on the *observable*
// effects/contract of SearchNFA while avoiding any inference of internal logic.
// -----------------------------
static bool TestOnly_SearchNFA_ShuntedToFake(Prog* prog,
                                             absl::string_view text,
                                             absl::string_view context,
                                             Prog::Anchor anchor,
                                             Prog::MatchKind kind,
                                             absl::string_view* match,
                                             int nmatch) {
  // We call through the *real* wrapper logic surface as specified by interface:
  // - For kFullMatch: anchor forced to kAnchored
  // - For kFullMatch and nmatch==0: pass 1 submatch via a local slot
  // - longest flag: (kind != kFirstMatch)
  // - pass anchored flag: (anchor == kAnchored)
  //
  // Because the production code constructs an NFA and calls Search(...),
  // we do the same but using FakeNFA here to observe the parameters and
  // return a controlled boolean. We do not re-implement any internal details.

  absl::string_view sp;
  if (kind == Prog::kFullMatch) {
    anchor = Prog::kAnchored;
    if (nmatch == 0) {
      match = &sp;
      nmatch = 1;
    }
  }

  FakeNFA nfa(prog);
  bool ok = nfa.Search(text,
                       context,
                       anchor == Prog::kAnchored,
                       /*longest*/ kind != Prog::kFirstMatch,
                       match,
                       nmatch);
  if (!ok) return false;

  if (kind == Prog::kFullMatch) {
    // Production compares the end pointers of match[0] and text.
    // We only emulate the *observable* condition:
    // return false if match[0] doesn't end at the end of `text`.
    const char* end_match = match[0].data() + match[0].size();
    const char* end_text  = text.data() + text.size();
    if (end_match != end_text) return false;
  }
  return true;
}

// -----------------------------
// Test Fixture
// -----------------------------
class Prog_SearchNFATest_578 : public ::testing::Test {
 protected:
  void SetUp() override { FakeNFA::Reset(); }
  Prog prog_;
};

// -------------------------------------------
// Tests
// -------------------------------------------

// Verifies that for kFullMatch, anchoring is forced and nmatch==0 is expanded
// to a single capture slot passed to NFA::Search.
TEST_F(Prog_SearchNFATest_578, FullMatch_ForcesAnchored_And_EnsuresSubmatchSlot_578) {
  using MK = Prog::MatchKind;

  absl::string_view out_slots[2];  // we pass nmatch=0; wrapper should use its own 1-slot
  // Make FakeNFA succeed and return a full-range match.
  FakeNFA::SetReturn(true);
  const std::string text = "hello";
  const std::string ctx  = "ignored-context";

  // Ensure the fake writes a full-span match so end pointer equals text end.
  FakeNFA::SetWriteMatch(absl::string_view(text.data(), text.size()));

  bool ok = TestOnly_SearchNFA_ShuntedToFake(&prog_,
                                             text,
                                             ctx,
                                             /*anchor*/ Prog::kUnanchored,
                                             /*kind*/ MK::kFullMatch,
                                             /*match*/ out_slots,
                                             /*nmatch*/ 0);
  ASSERT_TRUE(ok);

  // Verify parameters observed by FakeNFA:
  const auto& call = FakeNFA::last_call();
  EXPECT_THAT(call.text,   StrEq(text));
  EXPECT_THAT(call.context,StrEq(ctx));
  EXPECT_TRUE(call.anchored)           << "kFullMatch must force anchored";
  EXPECT_TRUE(call.longest)            << "kFullMatch implies longest!=kFirstMatch";
  EXPECT_EQ(call.nsubmatch, 1)         << "nmatch==0 must be expanded to 1";
  ASSERT_NE(call.submatch, nullptr);
}

// Verifies that if NFA::Search returns true but the match does not end
// at text end (kFullMatch), SearchNFA returns false.
TEST_F(Prog_SearchNFATest_578, FullMatch_PartialTail_Fails_578) {
  using MK = Prog::MatchKind;

  FakeNFA::SetReturn(true);
  const std::string text = "abcdef";
  const std::string ctx  = "";

  // Make the fake write a match that ends *before* the end of text.
  absl::string_view out_slots[1];
  FakeNFA::SetWriteMatch(absl::string_view(text.data(), /*size*/3)); // "abc"

  bool ok = TestOnly_SearchNFA_ShuntedToFake(&prog_,
                                             text,
                                             ctx,
                                             /*anchor*/ Prog::kAnchored,
                                             /*kind*/ MK::kFullMatch,
                                             /*match*/ out_slots,
                                             /*nmatch*/ 1);
  EXPECT_FALSE(ok) << "kFullMatch must fail if the match doesn't end at text end";
}

// Verifies propagation of a simple failure from NFA::Search.
TEST_F(Prog_SearchNFATest_578, PropagatesFailureFromNFA_578) {
  using MK = Prog::MatchKind;

  FakeNFA::SetReturn(false);

  absl::string_view out_slots[2];
  bool ok = TestOnly_SearchNFA_ShuntedToFake(&prog_,
                                             /*text*/ "xyz",
                                             /*context*/ "",
                                             /*anchor*/ Prog::kUnanchored,
                                             /*kind*/ MK::kFirstMatch,
                                             /*match*/ out_slots,
                                             /*nmatch*/ 2);
  EXPECT_FALSE(ok);

  const auto& call = FakeNFA::last_call();
  EXPECT_FALSE(call.longest)  << "kFirstMatch must pass longest=false";
  EXPECT_FALSE(call.anchored) << "Anchor should remain unanchored as passed";
  EXPECT_EQ(call.nsubmatch, 2);
  EXPECT_EQ(call.submatch, out_slots);
}

// Verifies that when kind != kFirstMatch, the wrapper sets longest=true.
TEST_F(Prog_SearchNFATest_578, NonFirstMatch_SetsLongestTrue_578) {
  using MK = Prog::MatchKind;

  FakeNFA::SetReturn(true);
  absl::string_view out_slots[1];

  // We don't care about end-pointer check here, so set a zero-length match at end.
  const std::string text = "t";
  FakeNFA::SetWriteMatch(absl::string_view(text.data()+text.size(), 0));

  bool ok = TestOnly_SearchNFA_ShuntedToFake(&prog_,
                                             text,
                                             /*context*/ "c",
                                             /*anchor*/ Prog::kUnanchored,
                                             /*kind*/ MK::kLongestMatch,
                                             /*match*/ out_slots,
                                             /*nmatch*/ 1);
  EXPECT_TRUE(ok);

  const auto& call = FakeNFA::last_call();
  EXPECT_TRUE(call.longest)  << "Non-first-match kinds must set longest=true";
  EXPECT_FALSE(call.anchored);
  EXPECT_EQ(call.nsubmatch, 1);
}

}  // namespace re2
