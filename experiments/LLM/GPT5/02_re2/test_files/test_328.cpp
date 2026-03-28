// File: re2_compile_to_reverse_prog_test.cc

#include "gtest/gtest.h"
#include "re2/regexp.h"   // Regexp and Parse/flags/status
#include "re2/prog.h"     // Prog (returned type of CompileToReverseProg)
#include <memory>

using re2::Regexp;
using re2::Prog;

// Helper to create a simple Regexp from pattern text.
static Regexp* ParseOrNull(const std::string& pat) {
  re2::RegexpStatus status;
  // Use no special flags to keep behavior fully black-box and default.
  auto* re = Regexp::Parse(pat, static_cast<Regexp::ParseFlags>(0), &status);
  return re;
}

// ------------------------------
// TESTS (TEST_ID = 328)
// ------------------------------

class CompileToReverseProgTest_328 : public ::testing::Test {
protected:
  void TearDown() override {
    // Nothing to clean up at fixture level.
  }
};

// Normal operation: with reasonable max_mem, should return a non-null Prog*.
TEST_F(CompileToReverseProgTest_328, ParsesAndCompilesSimpleLiteral_328) {
  std::unique_ptr<Regexp, void(*)(Regexp*)> re(ParseOrNull("abc"),
                                               [](Regexp* r){ if (r) r->Decref(); });
  ASSERT_NE(re.get(), nullptr) << "Regexp::Parse should succeed for a simple literal";

  // Choose a generous but not excessive limit (black-box friendly).
  const int64_t kMaxMem = 1LL << 20; // 1 MiB
  Prog* prog = re->CompileToReverseProg(kMaxMem);

  // Observable behavior: returns a program instance on success.
  ASSERT_NE(prog, nullptr) << "Expected non-null reverse program for simple literal within memory limit";

  // We don't assume ownership model beyond black-box; avoid peeking internal state.
  // If Prog exposes reference counting in your build (common in RE2), you may call prog->Decref().
  // To keep this test strictly interface-safe across variants, we don't do that here.
}

// Boundary condition: zero max_mem should fail cleanly and return nullptr.
TEST_F(CompileToReverseProgTest_328, ZeroMaxMemReturnsNull_328) {
  std::unique_ptr<Regexp, void(*)(Regexp*)> re(ParseOrNull("a"),
                                               [](Regexp* r){ if (r) r->Decref(); });
  ASSERT_NE(re.get(), nullptr) << "Regexp::Parse should succeed for a simple literal";

  const int64_t kMaxMemZero = 0;
  Prog* prog = re->CompileToReverseProg(kMaxMemZero);

  // Observable behavior: with no memory budget, compilation cannot proceed.
  EXPECT_EQ(prog, nullptr) << "Expected nullptr when max_mem is 0";
}

// Sanity difference check: reverse compilation should generally be possible
// even for patterns with anchors; we only check successful creation, not internals.
TEST_F(CompileToReverseProgTest_328, CompilesAnchoredPattern_WithinReasonableBudget_328) {
  std::unique_ptr<Regexp, void(*)(Regexp*)> re(ParseOrNull("^hello$"),
                                               [](Regexp* r){ if (r) r->Decref(); });
  ASSERT_NE(re.get(), nullptr) << "Regexp::Parse should succeed for anchored literal";

  const int64_t kMaxMem = 1LL << 20; // 1 MiB
  Prog* prog = re->CompileToReverseProg(kMaxMem);

  ASSERT_NE(prog, nullptr) << "Expected reverse program for anchored pattern within memory limit";
}
