// File: runelen_test_206.cc
#include <gtest/gtest.h>
#include <limits>

// ---- Public interface forward-decls (no internal logic inferred) ----
namespace re2 {
  // Use a minimal, interface-compatible stand-in for the Rune type.
  // (In many codebases, Rune is a 32-bit int.)
  using Rune = int;
  int runelen(Rune rune);  // Provided by the production object under test
}

// ---- Link-time seam for external collaborator: runetochar ----
// We provide a test double for the free function `runetochar` so we can
// (1) control its return value and (2) observe the arguments it receives.
// This fulfills the “external interaction verification” requirement.
namespace {
  // Observability & control knobs for the fake:
  static int g_next_return = 0;
  static char* g_last_buf = nullptr;
  static bool g_last_rune_ptr_was_null = true;
  static re2::Rune g_last_rune_value = 0;
  static int g_call_count = 0;

  // Reset between tests
  void ResetRunetocharProbe() {
    g_next_return = 0;
    g_last_buf = nullptr;
    g_last_rune_ptr_was_null = true;
    g_last_rune_value = 0;
    g_call_count = 0;
  }
}

// NOTE: The production code calls `runetochar(str, &rune)` unqualified.
// Define a function with the same signature so the test binary links to this
// version and we can verify interactions without re-implementing internals.
int runetochar(char* s, const re2::Rune* r) {
  ++g_call_count;
  g_last_buf = s;
  g_last_rune_ptr_was_null = (r == nullptr);
  if (r) g_last_rune_value = *r;

  // Do not simulate any internal behavior beyond returning a controlled value.
  return g_next_return;
}

// ---- Test fixture ----
class RunelenTest_206 : public ::testing::Test {
protected:
  void SetUp() override { ResetRunetocharProbe(); }
};

// ========================= Test Cases =========================

// [Normal operation] runelen returns whatever runetochar returns.
TEST_F(RunelenTest_206, ReturnsValueFromRunetochar_206) {
  g_next_return = 3;  // Control collaborator’s return

  const re2::Rune input = 0x61; // 'a'
  int out = re2::runelen(input);

  EXPECT_EQ(out, 3);
  EXPECT_EQ(g_call_count, 1);
  // External interaction verification:
  EXPECT_FALSE(g_last_rune_ptr_was_null) << "runetochar should get a valid Rune*";
  EXPECT_EQ(g_last_rune_value, input) << "runelen must forward the correct Rune value";
  EXPECT_NE(g_last_buf, nullptr) << "runetochar should get a non-null buffer";
}

// [Boundary condition] Minimum Rune value is forwarded; return is propagated.
TEST_F(RunelenTest_206, ForwardsMinRuneAndPropagatesReturn_206) {
  g_next_return = 1;

  const re2::Rune min_r = std::numeric_limits<re2::Rune>::min();
  int out = re2::runelen(min_r);

  EXPECT_EQ(out, 1);
  EXPECT_EQ(g_call_count, 1);
  EXPECT_FALSE(g_last_rune_ptr_was_null);
  EXPECT_EQ(g_last_rune_value, min_r);
  EXPECT_NE(g_last_buf, nullptr);
}

// [Boundary condition] Maximum Rune value is forwarded; return is propagated.
TEST_F(RunelenTest_206, ForwardsMaxRuneAndPropagatesReturn_206) {
  g_next_return = 4;

  const re2::Rune max_r = std::numeric_limits<re2::Rune>::max();
  int out = re2::runelen(max_r);

  EXPECT_EQ(out, 4);
  EXPECT_EQ(g_call_count, 1);
  EXPECT_FALSE(g_last_rune_ptr_was_null);
  EXPECT_EQ(g_last_rune_value, max_r);
  EXPECT_NE(g_last_buf, nullptr);
}

// [Exceptional/error case] Negative return from runetochar is propagated unchanged.
TEST_F(RunelenTest_206, PropagatesNegativeReturn_206) {
  g_next_return = -1;  // Simulate an error from the collaborator

  const re2::Rune input = 0x20AC; // Some arbitrary value
  int out = re2::runelen(input);

  EXPECT_EQ(out, -1);
  EXPECT_EQ(g_call_count, 1);
  EXPECT_FALSE(g_last_rune_ptr_was_null);
  EXPECT_EQ(g_last_rune_value, input);
  EXPECT_NE(g_last_buf, nullptr);
}

// [Interaction] Multiple calls each invoke runetochar once and forward the right value.
TEST_F(RunelenTest_206, MultipleCallsForwardArgsEachTime_206) {
  g_next_return = 2;

  const re2::Rune r1 = 0x41;   // 'A'
  const re2::Rune r2 = 0x1F60A; // 🙂 (just a distinct value; we don't rely on encoding)

  int out1 = re2::runelen(r1);
  EXPECT_EQ(out1, 2);
  EXPECT_EQ(g_call_count, 1);
  EXPECT_EQ(g_last_rune_value, r1);
  EXPECT_NE(g_last_buf, nullptr);

  int out2 = re2::runelen(r2);
  EXPECT_EQ(out2, 2);
  EXPECT_EQ(g_call_count, 2);
  EXPECT_EQ(g_last_rune_value, r2);
  EXPECT_NE(g_last_buf, nullptr);
}
