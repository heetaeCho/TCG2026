// dfa_tests_448.cc
#include <gtest/gtest.h>

// Provide the minimal stub for re2::Prog that the DFA interface expects.
// We only declare what's necessary for construction & kind() observation.
// This avoids any inference of DFA internals.
namespace re2 {
struct Prog {
  enum MatchKind {
    kStubMatchKind = 0  // Arbitrary tag value for tests
  };
};
}  // namespace re2

// Include the production implementation so tests can instantiate DFA.
// We rely only on DFA's public API in these tests.
#include "re2/dfa.cc"  // Path per prompt: ./TestProjects/re2/re2/dfa.cc

namespace {

using re2::DFA;
using re2::Prog;

class DFATest_448 : public ::testing::Test {
protected:
  // Helper to build a DFA with minimal, valid inputs.
  static DFA* MakeDFA(Prog* prog = nullptr,
                      Prog::MatchKind kind = Prog::kStubMatchKind,
                      int64_t max_mem = 1024) {
    return new DFA(prog, kind, max_mem);
  }
};

// --- Tests ---

// Verifies that a freshly constructed DFA reports itself as OK.
// This checks the observable success state via ok().
TEST_F(DFATest_448, OkByDefault_448) {
  std::unique_ptr<DFA> dfa(MakeDFA());
  EXPECT_TRUE(dfa->ok());
}

// Verifies that kind() reports the same MatchKind value that was provided
// at construction time (observable behavior through the public API).
TEST_F(DFATest_448, KindIsPropagated_448) {
  std::unique_ptr<DFA> dfa(MakeDFA(nullptr, Prog::kStubMatchKind, 2048));
  EXPECT_EQ(dfa->kind(), Prog::kStubMatchKind);
}

// Basic lifecycle test: constructing and destroying a DFA should not crash.
// This indirectly exercises the destructor path that cleans up resources.
TEST_F(DFATest_448, ConstructAndDestroy_NoCrash_448) {
  DFA* dfa = MakeDFA();
  // Scope exit (delete) exercises ~DFA(); no assertions needed beyond no-crash.
  delete dfa;
}

}  // namespace
