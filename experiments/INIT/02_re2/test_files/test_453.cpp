// File: dfa_search_test_453.cc
#include <gtest/gtest.h>
#include <string>
#include "re2/re2/dfa.cc"     // Uses the provided partial implementation
#include "re2/re2/prog.h"
#include "re2/re2/sparse_set.h"

using namespace re2;

// ---------- Test seams (link-time shims) ----------
// These shims let us drive DFA::Search through its observable control flow
// without inspecting or re-implementing internal logic.
//
// We DO NOT assert on or read any private state; we only control whether
// helper routines report success/failure and what observable outputs
// (like params.start and params.ep) they produce.

namespace re2 {
namespace {

// Control flags for ok(), AnalyzeSearch(), FastSearchLoop()
static bool g_ok_for_search = true;

using AnalyzeHook = bool (*)(DFA::SearchParams*);
static AnalyzeHook g_analyze_hook = nullptr;

using FastHook = bool (*)(DFA::SearchParams*);
static FastHook g_fast_hook = nullptr;

}  // namespace

// Public method — provide a controllable definition for tests.
bool DFA::ok() const { return g_ok_for_search; }

// Private helpers — provide controllable definitions for tests.
// (We do NOT expose or read internals; we only set observable params.)
bool DFA::AnalyzeSearch(DFA::SearchParams* params) {
  if (g_analyze_hook) return g_analyze_hook(params);
  return true;
}
bool DFA::FastSearchLoop(DFA::SearchParams* params) {
  if (g_fast_hook) return g_fast_hook(params);
  return false;
}

}  // namespace re2

// ---------- Test fixture ----------
class DFASearchTest_453 : public ::testing::Test {
protected:
  void SetUp() override {
    // Default: DFA is "ok", AnalyzeSearch succeeds, FastSearchLoop returns false.
    re2::g_ok_for_search = true;
    re2::g_analyze_hook = [](DFA::SearchParams* params) -> bool {
      // Default start: neither DeadState nor FullMatchState — drive into FastSearchLoop.
      params->start = reinterpret_cast<decltype(params->start)>(0x1234);
      return true;
    };
    re2::g_fast_hook = [](DFA::SearchParams* params) -> bool {
      // Default: no match, place a visible ep.
      params->failed = false;
      // Point ep somewhere inside text to make it observable.
      params->ep = params->text.data();
      return false;
    };
  }

  // Helper to build a minimal DFA instance.
  // prog can be nullptr because ExtraDebug is false (per given global),
  // so Search won't try to dump via prog_.
  DFA MakeDFA(Prog::MatchKind kind = Prog::kFirstMatch) {
    return DFA(/*prog=*/nullptr, kind, /*max_mem=*/1 << 20);
  }
};

// ---------- Tests ----------

// ok() == false => Search returns false, sets *failed = true, leaves *epp == nullptr.
TEST_F(DFASearchTest_453, ReturnsFalseAndSetsFailedWhenNotOk_453) {
  re2::g_ok_for_search = false;

  DFA dfa = MakeDFA();
  const char* ep = reinterpret_cast<const char*>(0xdeadbeef); // will be nulled
  bool failed = false;

  const std::string text = "abc";
  const std::string ctx  = "abc";

  bool ret = dfa.Search(text, ctx,
                        /*anchored=*/false,
                        /*want_earliest_match=*/false,
                        /*run_forward=*/true,
                        &failed, &ep,
                        /*matches=*/nullptr);

  EXPECT_FALSE(ret);
  EXPECT_TRUE(failed);
  EXPECT_EQ(ep, nullptr);
}

// AnalyzeSearch() returns false => Search returns false, sets *failed = true, *epp stays nullptr.
TEST_F(DFASearchTest_453, AnalyzeSearchFailurePropagates_453) {
  re2::g_analyze_hook = [](DFA::SearchParams* /*params*/) -> bool {
    return false;  // Force pre-loop failure path
  };

  DFA dfa = MakeDFA();
  const char* ep = nullptr;
  bool failed = false;

  bool ret = dfa.Search("x", "x",
                        /*anchored=*/true,
                        /*want_earliest_match=*/true,
                        /*run_forward=*/true,
                        &failed, &ep,
                        /*matches=*/nullptr);

  EXPECT_FALSE(ret);
  EXPECT_TRUE(failed);
  EXPECT_EQ(ep, nullptr);
}

// params.start == DeadState => Search returns false, *failed == false, *epp remains nullptr.
TEST_F(DFASearchTest_453, DeadStartReturnsFalseWithoutFailure_453) {
  re2::g_analyze_hook = [](DFA::SearchParams* params) -> bool {
    // DeadState is reinterpret_cast<State*>(1) per provided code.
    params->start = reinterpret_cast<decltype(params->start)>(1);
    return true;
  };

  DFA dfa = MakeDFA();
  const char* ep = nullptr;
  bool failed = true;  // Should be cleared by Search before AnalyzeSearch

  bool ret = dfa.Search("hello", "hello",
                        /*anchored=*/false,
                        /*want_earliest_match=*/false,
                        /*run_forward=*/true,
                        &failed, &ep,
                        /*matches=*/nullptr);

  EXPECT_FALSE(ret);
  EXPECT_FALSE(failed);
  EXPECT_EQ(ep, nullptr);
}

// params.start == FullMatchState and run_forward == want_earliest_match
// => returns true and *epp == text.data()
TEST_F(DFASearchTest_453, FullMatchStateEarliestEqualsDirectionSetsEpToBegin_453) {
  re2::g_analyze_hook = [](DFA::SearchParams* params) -> bool {
    // FullMatchState is reinterpret_cast<State*>(2)
    params->start = reinterpret_cast<decltype(params->start)>(2);
    return true;
  };

  DFA dfa = MakeDFA();
  const std::string text = "abcdef";
  const char* ep = nullptr;
  bool failed = false;

  bool ret = dfa.Search(text, text,
                        /*anchored=*/true,
                        /*want_earliest_match=*/true,
                        /*run_forward=*/true,  // same as want_earliest_match
                        &failed, &ep,
                        /*matches=*/nullptr);

  EXPECT_TRUE(ret);
  EXPECT_FALSE(failed);
  EXPECT_EQ(ep, text.data());
}

// params.start == FullMatchState and run_forward != want_earliest_match
// => returns true and *epp == text.data() + text.size()
TEST_F(DFASearchTest_453, FullMatchStateEarliestNotEqualDirectionSetsEpToEnd_453) {
  re2::g_analyze_hook = [](DFA::SearchParams* params) -> bool {
    params->start = reinterpret_cast<decltype(params->start)>(2);  // FullMatchState
    return true;
  };

  DFA dfa = MakeDFA();
  const std::string text = "12345";
  const char* ep = nullptr;
  bool failed = false;

  bool ret = dfa.Search(text, text,
                        /*anchored=*/false,
                        /*want_earliest_match=*/false,
                        /*run_forward=*/true,  // different from want_earliest_match
                        &failed, &ep,
                        /*matches=*/nullptr);

  EXPECT_TRUE(ret);
  EXPECT_FALSE(failed);
  EXPECT_EQ(ep, text.data() + text.size());
}

// FastSearchLoop() path: success, params.failed == false => returns true and *epp == params.ep.
TEST_F(DFASearchTest_453, FastSearchSuccessPropagatesEp_453) {
  re2::g_fast_hook = [](DFA::SearchParams* params) -> bool {
    params->failed = false;
    // Set ep to inside text (offset 2).
    params->ep = params->text.data() + 2;
    return true;  // Matched
  };

  DFA dfa = MakeDFA();
  const std::string text = "xyzzy";
  const char* ep = nullptr;
  bool failed = false;

  bool ret = dfa.Search(text, text,
                        /*anchored=*/false,
                        /*want_earliest_match=*/true,
                        /*run_forward=*/true,
                        &failed, &ep,
                        /*matches=*/nullptr);

  EXPECT_TRUE(ret);
  EXPECT_FALSE(failed);
  ASSERT_NE(ep, nullptr);
  EXPECT_EQ(ep, text.data() + 2);
}

// FastSearchLoop() path: sets params.failed == true => Search returns false and *failed == true.
TEST_F(DFASearchTest_453, FastSearchSetsFailedPropagatesFailure_453) {
  re2::g_fast_hook = [](DFA::SearchParams* params) -> bool {
    params->failed = true;  // simulate internal failure during loop
    params->ep = nullptr;   // ep is ignored on failure
    return false;
  };

  DFA dfa = MakeDFA();
  const char* ep = reinterpret_cast<const char*>(0x777); // should be ignored/left alone
  bool failed = false;

  bool ret = dfa.Search("abc", "abc",
                        /*anchored=*/false,
                        /*want_earliest_match=*/false,
                        /*run_forward=*/true,
                        &failed, &ep,
                        /*matches=*/nullptr);

  EXPECT_FALSE(ret);
  EXPECT_TRUE(failed);
  // ep is not specified on failure; Search doesn't promise to keep/clear it here.
  // We only assert failure path behavior.
}

// Passing a non-null matches pointer is allowed only when kind == kManyMatch.
// We just verify no DCHECK/UB in release; test uses kind = kManyMatch.
TEST_F(DFASearchTest_453, NonNullMatchesAllowedOnlyForManyMatch_453) {
  DFA dfa = MakeDFA(Prog::kManyMatch);

  // Keep default hooks: Analyze succeeds with non-sentinel start,
  // FastSearchLoop returns false with ep = text.data().
  SparseSet matches;  // existence only; we don't inspect its internals.

  const std::string text = "foo";
  const char* ep = nullptr;
  bool failed = false;

  bool ret = dfa.Search(text, text,
                        /*anchored=*/false,
                        /*want_earliest_match=*/false,
                        /*run_forward=*/true,
                        &failed, &ep,
                        &matches);

  EXPECT_FALSE(ret);        // default fast hook returns false
  EXPECT_FALSE(failed);     // default fast hook sets failed=false
  EXPECT_EQ(ep, text.data());
}
