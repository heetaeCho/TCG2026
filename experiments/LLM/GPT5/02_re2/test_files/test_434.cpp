// File: ./TestProjects/re2/tests/dfa_kind_test_434.cc

#include <gtest/gtest.h>

// ---- Minimal stubs to satisfy the interface dependency (external collaborator) ----
// We do NOT reimplement DFA internals. We only provide the type used by the interface.
namespace re2 {
class Prog {
public:
  // The specific enumerator values don't matter for black-box testing;
  // we only verify round-trip behavior through DFA::kind().
  enum MatchKind {
    kFullMatch = 0,
    kLongestMatch = 1,
    kFirstMatch = 2
  };
};
}  // namespace re2

// Include the partial implementation under test.
// This file provides the class with the public method `Prog::MatchKind kind()`.
#include "re2/dfa.cc"  // path as given by the prompt

namespace {

using re2::DFA;
using re2::Prog;

// Utility to construct a DFA without relying on Prog internals.
// According to the exposed constructor signature in the prompt,
// we can pass a null Prog* safely as we do not exercise any behavior
// other than `kind()`, and the constructor (per exposed initializer list)
// only assigns fields.
static DFA* MakeDFA(Prog* prog, Prog::MatchKind kind, int64_t max_mem) {
  // Construct via new to avoid lifetime issues in tests.
  return new DFA(prog, kind, max_mem);
}

// ------------------------------------------------------------------------------------
// Tests
// ------------------------------------------------------------------------------------

// Verifies that DFA::kind() returns the exact MatchKind passed to the constructor.
TEST(DFA_KindTest_434, KindReflectsConstructorArgument_FullMatch_434) {
  std::unique_ptr<DFA> dfa(MakeDFA(/*prog=*/nullptr, Prog::kFullMatch, /*max_mem=*/0));
  EXPECT_EQ(dfa->kind(), Prog::kFullMatch);
}

TEST(DFA_KindTest_434, KindReflectsConstructorArgument_LongestMatch_434) {
  std::unique_ptr<DFA> dfa(MakeDFA(/*prog=*/nullptr, Prog::kLongestMatch, /*max_mem=*/1024));
  EXPECT_EQ(dfa->kind(), Prog::kLongestMatch);
}

TEST(DFA_KindTest_434, KindReflectsConstructorArgument_FirstMatch_434) {
  std::unique_ptr<DFA> dfa(MakeDFA(/*prog=*/nullptr, Prog::kFirstMatch, /*max_mem=*/1LL << 20));
  EXPECT_EQ(dfa->kind(), Prog::kFirstMatch);
}

// Boundary-ish construction checks for max_mem do not assert on internal effects;
// they only ensure object can be constructed and that kind() remains correct.
TEST(DFA_KindTest_434, ConstructionWithZeroMemBudget_PreservesKind_434) {
  std::unique_ptr<DFA> dfa(MakeDFA(/*prog=*/nullptr, Prog::kFullMatch, /*max_mem=*/0));
  EXPECT_EQ(dfa->kind(), Prog::kFullMatch);
}

TEST(DFA_KindTest_434, ConstructionWithLargeMemBudget_PreservesKind_434) {
  const int64_t kLarge = (int64_t)1e12;  // Large but reasonable test value
  std::unique_ptr<DFA> dfa(MakeDFA(/*prog=*/nullptr, Prog::kLongestMatch, /*max_mem=*/kLarge));
  EXPECT_EQ(dfa->kind(), Prog::kLongestMatch);
}

// Type-level check: the return type of kind() is Prog::MatchKind.
// This verifies the interface signature rather than any internal logic.
TEST(DFA_KindTest_434, KindReturnTypeIsProgMatchKind_434) {
  std::unique_ptr<DFA> dfa(MakeDFA(/*prog=*/nullptr, Prog::kFirstMatch, /*max_mem=*/64));
  // If this compiles and the static_assert holds, the signature matches the interface.
  using ReturnT = decltype(dfa->kind());
  static_assert(std::is_same<ReturnT, Prog::MatchKind>::value,
                "DFA::kind() must return re2::Prog::MatchKind");
  // Also do a runtime check for completeness.
  EXPECT_EQ(dfa->kind(), Prog::kFirstMatch);
}

}  // namespace
