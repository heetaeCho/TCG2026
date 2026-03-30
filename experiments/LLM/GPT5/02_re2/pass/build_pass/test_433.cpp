// File: dfa_ok_test_433.cc
#include <cstdint>
#include "gtest/gtest.h"

// We avoid including the production .cc directly and instead
// forward-declare just enough of the public interface we use.
// This keeps the test constrained to observable behavior and
// lets the linker resolve against the real implementation.
namespace re2 {

// Minimal stub of Prog with the nested MatchKind needed by DFA's ctor.
// This is a harmless stand-in for tests; we don't depend on any behavior.
class Prog {
 public:
  enum MatchKind {
    kFirstMatch = 0,
    kLongestMatch = 1
  };
};

// Public subset of DFA’s interface used by the tests.
class DFA {
 public:
  DFA(Prog* prog, Prog::MatchKind kind, int64_t max_mem);
  bool ok() const;
  // NOTE: We intentionally do NOT declare or use any other methods here.
};

}  // namespace re2

// ---------- Tests ----------

// [433] Basic construction should yield an OK DFA (observable via ok()).
TEST(DFAOkTest_433, OkIsTrueAfterConstruction_433) {
  re2::Prog* prog = nullptr;  // We don't exercise prog behavior; just pass through.
  re2::DFA dfa(prog, re2::Prog::kFirstMatch, /*max_mem=*/0);
  EXPECT_TRUE(dfa.ok());
}

// [433] ok() should remain true for various (boundary/typical) constructor arguments.
TEST(DFAOkTest_433, OkTrueForVariousConstructorArgs_433) {
  re2::Prog* prog = nullptr;

  // Zero memory budget.
  re2::DFA dfa_zero(prog, re2::Prog::kFirstMatch, /*max_mem=*/0);
  EXPECT_TRUE(dfa_zero.ok());

  // Small positive memory budget.
  re2::DFA dfa_small(prog, re2::Prog::kLongestMatch, /*max_mem=*/1);
  EXPECT_TRUE(dfa_small.ok());

  // Large memory budget.
  re2::DFA dfa_large(prog, re2::Prog::kFirstMatch, /*max_mem=*/static_cast<int64_t>(1) << 40);
  EXPECT_TRUE(dfa_large.ok());

  // Negative memory budget (if the implementation permits construction, ok() is the only observable check here).
  re2::DFA dfa_negative(prog, re2::Prog::kLongestMatch, /*max_mem=*/-1);
  EXPECT_TRUE(dfa_negative.ok());
}

// [433] Compile-time/const-correctness check: ok() is callable on const objects.
TEST(DFAOkTest_433, OkCallableOnConstObject_433) {
  re2::Prog* prog = nullptr;
  const re2::DFA dfa_const(prog, re2::Prog::kFirstMatch, /*max_mem=*/128);
  EXPECT_TRUE(dfa_const.ok());
}
