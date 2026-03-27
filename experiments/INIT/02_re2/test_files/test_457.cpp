#include <string>
#include <limits>
#include "gtest/gtest.h"

// We rely on the real DFA::PossibleMatchRange implementation.
// The following internal headers/types are assumed to be available in the project.
#include "re2/dfa.h"
#include "re2/prog.h"

namespace re2 {

// ---------- Test seam (link-time stubs for collaborators) ------------------
// These stubs let us control observable behavior of DFA::PossibleMatchRange
// without touching its implementation. They simulate only what the method
// can observe (ok() result, AnalyzeSearch start state, RunStateOnByte
// return values, and the effect of PrefixSuccessor).

namespace {
  // Control knobs for stubs.
  static bool g_ok = true;
  static bool g_analyze_ok = true;
  static DFA::State* g_start = reinterpret_cast<DFA::State*>(0x1000);

  // In RunStateOnByte:
  // - If c == g_min_trigger and s == g_start, return FullMatchState (extend min)
  // - If c == g_max_trigger and s == g_start, return FullMatchState (extend max)
  // - If c is outside [0,255] and s == FullMatchState, return FullMatchState
  //   so the "end-of-text" probe is seen as a match and breaks the loop.
  // - Otherwise, return DeadState (no extension).
  static int g_min_trigger = 'a';
  static int g_max_trigger = 'z';

  // Make RunStateOnByte return NULL once when c == 0 (to simulate OOM).
  static bool g_null_on_c0 = false;

  // For the max-building loop, optionally suppress any extension.
  static bool g_force_max_no_extend = false;

  // Control the effect of PrefixSuccessor: clearing max simulates overflow case.
  static bool g_prefix_clears = false;
}  // namespace

// Provide the observable collaborators used by PossibleMatchRange.

bool DFA::ok() const {
  return g_ok;
}

bool DFA::AnalyzeSearch(DFA::SearchParams* params) {
  // The method under test only reads start and return value.
  params->start = g_start;
  return g_analyze_ok;
}

DFA::State* DFA::RunStateOnByte(DFA::State* s, int c) {
  // Simulate out-of-memory once for c == 0 if requested.
  if (g_null_on_c0 && c == 0) {
    g_null_on_c0 = false;  // only once
    return nullptr;
  }

  // Treat out-of-range bytes (end-of-text sentinels) specially when in match.
  if ((c < 0 || c > 255) && s == FullMatchState) {
    return FullMatchState;
  }

  // If the caller is trying to build max but we force "no extend", just kill it.
  if (g_force_max_no_extend && s == g_start) {
    return DeadState;
  }

  // Normal extension triggers from the start state.
  if (s == g_start && c == g_min_trigger) return FullMatchState;
  if (s == g_start && c == g_max_trigger) return FullMatchState;

  // Once we're in a full-match state, keep it sticky on regular bytes.
  if (s == FullMatchState && 0 <= c && c <= 255) return FullMatchState;

  // Otherwise, no transition worth extending.
  return DeadState;
}

// The method under test calls PrefixSuccessor(max).
// We simulate either no-op or a clearing (overflow) behavior.
void PrefixSuccessor(std::string* s) {
  if (g_prefix_clears) s->clear();
  // else no-op
}

}  // namespace re2

// ------------------------------- Tests --------------------------------------

namespace {

using re2::DFA;
using re2::Prog;

class DFAPossibleMatchRangeTest_457 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset stub controls to safe defaults for each test.
    re2::g_ok = true;
    re2::g_analyze_ok = true;
    re2::g_start = reinterpret_cast<DFA::State*>(0x1000);
    re2::g_min_trigger = 'a';
    re2::g_max_trigger = 'z';
    re2::g_null_on_c0 = false;
    re2::g_force_max_no_extend = false;
    re2::g_prefix_clears = false;
  }

  // Helper to construct a minimal DFA object.
  DFA MakeDFA() {
    // We treat the Prog* as opaque; PossibleMatchRange doesn't use it.
    return DFA(/*prog=*/nullptr,
               static_cast<Prog::MatchKind>(0),
               /*max_mem=*/1 << 20);
  }
};

// ok() == false -> returns false and does not touch outputs.
TEST_F(DFAPossibleMatchRangeTest_457, NotOkReturnsFalse_457) {
  re2::g_ok = false;

  DFA d = MakeDFA();
  std::string min = "unchanged_min";
  std::string max = "unchanged_max";
  const bool ok = d.PossibleMatchRange(&min, &max, /*maxlen=*/3);

  EXPECT_FALSE(ok);
  EXPECT_EQ(min, "unchanged_min");
  EXPECT_EQ(max, "unchanged_max");
}

// AnalyzeSearch() == false -> returns false and does not touch outputs.
TEST_F(DFAPossibleMatchRangeTest_457, AnalyzeSearchFailure_457) {
  re2::g_analyze_ok = false;

  DFA d = MakeDFA();
  std::string min = "m";
  std::string max = "x";
  const bool ok = d.PossibleMatchRange(&min, &max, /*maxlen=*/3);

  EXPECT_FALSE(ok);
  EXPECT_EQ(min, "m");
  EXPECT_EQ(max, "x");
}

// params.start == DeadState -> returns true and sets min/max to empty.
TEST_F(DFAPossibleMatchRangeTest_457, StartIsDeadState_NoMatchingStrings_457) {
  re2::g_start = DeadState;

  DFA d = MakeDFA();
  std::string min = "foo";
  std::string max = "bar";
  const bool ok = d.PossibleMatchRange(&min, &max, /*maxlen=*/5);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(min.empty());
  EXPECT_TRUE(max.empty());
}

// params.start == FullMatchState -> returns false (every string matches: no max).
TEST_F(DFAPossibleMatchRangeTest_457, StartIsFullMatchState_EverythingMatches_457) {
  re2::g_start = FullMatchState;

  DFA d = MakeDFA();
  std::string min = "foo";
  std::string max = "bar";
  const bool ok = d.PossibleMatchRange(&min, &max, /*maxlen=*/5);

  EXPECT_FALSE(ok);
  // The function returns immediately; outputs remain unchanged.
  EXPECT_EQ(min, "foo");
  EXPECT_EQ(max, "bar");
}

// Normal case: extends min ('a') and max ('z'); PrefixSuccessor is a no-op; returns true.
TEST_F(DFAPossibleMatchRangeTest_457, BuildsMinAndMax_Simple_457) {
  // Use defaults: min trigger 'a', max trigger 'z'.
  DFA d = MakeDFA();
  std::string min, max;
  const bool ok = d.PossibleMatchRange(&min, &max, /*maxlen=*/3);

  EXPECT_TRUE(ok);
  // With our stub transitions, min extends once with 'a'.
  EXPECT_EQ(min, std::string("a"));
  // And max extends once with 'z'.
  EXPECT_EQ(max, std::string("z"));
}

// If RunStateOnByte returns NULL mid-way (OOM), the function returns false.
TEST_F(DFAPossibleMatchRangeTest_457, ReturnsFalseOnOutOfMemoryTransition_457) {
  re2::g_null_on_c0 = true;  // first byte tried (j == 0) will simulate OOM

  DFA d = MakeDFA();
  std::string min, max;
  const bool ok = d.PossibleMatchRange(&min, &max, /*maxlen=*/5);

  EXPECT_FALSE(ok);
}

// If the max loop cannot extend at all, the function returns true early with empty max.
TEST_F(DFAPossibleMatchRangeTest_457, EarlyTrueWhenMaxCannotExtend_457) {
  re2::g_force_max_no_extend = true;

  DFA d = MakeDFA();
  std::string min, max;
  const bool ok = d.PossibleMatchRange(&min, &max, /*maxlen=*/5);

  EXPECT_TRUE(ok);
  // min may or may not be extended; max must be empty on early return.
  EXPECT_TRUE(max.empty());
}

// maxlen == 0: skips loops, PrefixSuccessor runs; if it doesn't change empty,
// method returns false.
TEST_F(DFAPossibleMatchRangeTest_457, ZeroMaxLenReturnsFalse_457) {
  DFA d = MakeDFA();
  std::string min = "x", max = "y";
  const bool ok = d.PossibleMatchRange(&min, &max, /*maxlen=*/0);

  EXPECT_FALSE(ok);
  // min/max are cleared inside the method; with maxlen == 0, max stays empty.
  EXPECT_TRUE(max.empty());
}

// PrefixSuccessor empties the built max -> method returns false.
TEST_F(DFAPossibleMatchRangeTest_457, PrefixSuccessorEmptiesMax_457) {
  re2::g_prefix_clears = true;

  DFA d = MakeDFA();
  std::string min, max;
  const bool ok = d.PossibleMatchRange(&min, &max, /*maxlen=*/3);

  EXPECT_FALSE(ok);
  EXPECT_TRUE(max.empty());
}

}  // namespace
