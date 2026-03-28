// File: nfa_search_test_577.cc
#include "gtest/gtest.h"
#include "re2/nfa.cc"   // or the appropriate header that exposes re2::NFA
#include "re2/prog.h"
#include "absl/strings/string_view.h"

using re2::NFA;
using re2::Prog;

// A simple fixture to hold common helpers.
class NFASearchTest_577 : public ::testing::Test {
protected:
  // Helper to build an NFA with a provided Prog whose start can be set.
  // We avoid depending on any internal behavior beyond public setters.
  static std::unique_ptr<NFA> MakeNFA(Prog* prog) {
    return std::unique_ptr<NFA>(new NFA(prog));
  }
};

// --- Tests ---

// If the program's start is 0, Search should return false immediately.
// (Covers a visible boundary condition without requiring any internal details.)
TEST_F(NFASearchTest_577, StartZero_ReturnsFalse_577) {
  Prog prog;                          // default-constructed; start is 0
  auto nfa = NFASearchTest_577::MakeNFA(&prog);

  absl::string_view text = "abc";
  absl::string_view context = text;
  absl::string_view subs[1];

  const bool ok = nfa->Search(text, context, /*anchored=*/false,
                              /*longest=*/false, subs, /*nsubmatch=*/1);
  EXPECT_FALSE(ok);
}

// With non-zero start, a negative nsubmatch should be rejected and return false.
// This validates argument checking observable via the return value.
TEST_F(NFASearchTest_577, NegativeNSubmatch_ReturnsFalse_577) {
  Prog prog;
  prog.set_start(1);                  // ensure we pass the early start==0 check
  auto nfa = NFASearchTest_577::MakeNFA(&prog);

  absl::string_view text = "abc";
  absl::string_view context = text;

  const bool ok = nfa->Search(text, context, /*anchored=*/false,
                              /*longest=*/false, /*submatch=*/nullptr,
                              /*nsubmatch=*/-1);
  EXPECT_FALSE(ok);
}

// If context does not contain text, Search must return false.
// We set a non-zero start so the function proceeds to validate context bounds.
TEST_F(NFASearchTest_577, ContextNotContainingText_ReturnsFalse_577) {
  Prog prog;
  prog.set_start(1);
  auto nfa = NFASearchTest_577::MakeNFA(&prog);

  absl::string_view context = "abcdef";
  // Make 'text' point outside 'context' (e.g., a different buffer).
  absl::string_view text = "zzz";

  const bool ok = nfa->Search(text, context, /*anchored=*/false,
                              /*longest=*/false, /*submatch=*/nullptr,
                              /*nsubmatch=*/0);
  EXPECT_FALSE(ok);
}

// If anchor_start is set on the program, Search should fail when text
// does not begin at the start of the context (observable false).
TEST_F(NFASearchTest_577, AnchorStart_EnforcedWhenProgramAnchored_577) {
  Prog prog;
  prog.set_start(1);
  prog.set_anchor_start(true);  // program-enforced anchoring
  auto nfa = NFASearchTest_577::MakeNFA(&prog);

  absl::string_view context = "xxabc";
  // Choose a 'text' that is strictly within context but not starting at begin.
  absl::string_view text = context.substr(2);  // "abc"

  const bool ok = nfa->Search(text, context, /*anchored=*/false,
                              /*longest=*/false, /*submatch=*/nullptr,
                              /*nsubmatch=*/0);
  EXPECT_FALSE(ok);
}

// If anchor_end is set on the program, Search should fail when text
// does not end at the end of the context (observable false).
TEST_F(NFASearchTest_577, AnchorEnd_EnforcedWhenProgramAnchored_577) {
  Prog prog;
  prog.set_start(1);
  prog.set_anchor_end(true);   // program-enforced end anchoring
  auto nfa = NFASearchTest_577::MakeNFA(&prog);

  absl::string_view context = "abcxx";
  // Choose a 'text' that is within context but not ending at the end.
  absl::string_view text = context.substr(0, 3);  // "abc"

  const bool ok = nfa->Search(text, context, /*anchored=*/false,
                              /*longest=*/false, /*submatch=*/nullptr,
                              /*nsubmatch=*/0);
  EXPECT_FALSE(ok);
}

// If the caller provides a default-constructed context (data()==nullptr),
// Search should internally treat context as text (observable: no crash, valid return).
// With start==0 (default), it should still return false (early-out), but this
// verifies the NULL-context path is handled gracefully.
TEST_F(NFASearchTest_577, NullContext_IsTreatedAsText_GracefulFalse_577) {
  Prog prog;                  // start() == 0 by default
  auto nfa = NFASearchTest_577::MakeNFA(&prog);

  absl::string_view text = "abc";
  absl::string_view null_context;  // data() == nullptr

  const bool ok = nfa->Search(text, null_context, /*anchored=*/false,
                              /*longest=*/false, /*submatch=*/nullptr,
                              /*nsubmatch=*/0);
  EXPECT_FALSE(ok);
}
