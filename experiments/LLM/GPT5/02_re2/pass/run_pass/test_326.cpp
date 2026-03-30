// File: ./TestProjects/re2/re2/tests/compiler_finish_test_326.cc

#include <gtest/gtest.h>

#include "re2/regexp.h"
#include "re2/prog.h"
#include "re2/compile.cc"  // Header provides declarations; include path as appropriate in your tree

using namespace re2;

class CompilerFinishTest_326 : public ::testing::Test {
protected:
  // Helper to parse a simple pattern into a Regexp*
  Regexp* ParseRegexp(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, static_cast<Regexp::ParseFlags>(0), &status);
    // Treat parse as black-box; only check observable success (non-null)
    return re;
  }

  // Clean up a Regexp* using its public interface
  void DestroyRegexp(Regexp* re) {
    if (re) re->Decref();
  }
};

// [Normal operation] Produces a valid Prog* and uses default DFA budget when max_mem <= 0.
TEST_F(CompilerFinishTest_326, CompileSetsDefaultDfaMemWhenMaxMemLEZero_326) {
  Regexp* re = ParseRegexp("a");  // Simple, valid pattern; do not assume any internals
  ASSERT_NE(re, nullptr) << "Failed to parse test pattern";

  // Use the public compile entry that invokes Compiler::Finish internally.
  // Choose reversed=true to avoid any prefix-accel path (Finish checks !reversed()).
  Prog* prog = Compiler::Compile(re, /*reversed=*/true, /*max_mem=*/0);
  ASSERT_NE(prog, nullptr) << "Compile returned null program";

  // Observable behavior from Finish(): default DFA budget
  EXPECT_EQ(prog->dfa_mem(), 1 << 20) << "dfa_mem should default to 1<<20 when max_mem <= 0";

  delete prog;  // Use public destructor
  DestroyRegexp(re);
}

// [Boundary / error-like budgeting] Tiny positive max_mem clamps DFA budget to 0.
TEST_F(CompilerFinishTest_326, CompileClampsDfaMemToZeroWhenBudgetTooSmall_326) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr) << "Failed to parse test pattern";

  // Any tiny positive budget should underflow after accounting for required structures
  Prog* prog = Compiler::Compile(re, /*reversed=*/true, /*max_mem=*/1);
  ASSERT_NE(prog, nullptr) << "Compile returned null program even for tiny budget";

  // Observable behavior from Finish(): clamp negative m to 0
  EXPECT_EQ(prog->dfa_mem(), 0) << "dfa_mem should clamp to 0 when effective budget goes negative";

  delete prog;
  DestroyRegexp(re);
}

// [Sanity of Finish path] Successful compile returns a non-null Prog*.
TEST_F(CompilerFinishTest_326, CompileReturnsNonNullProg_326) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr) << "Failed to parse test pattern";

  // Reasonable max_mem to avoid clamping; reversed can be either.
  Prog* prog = Compiler::Compile(re, /*reversed=*/true, /*max_mem=*/(1<<20));
  EXPECT_NE(prog, nullptr);

  delete prog;
  DestroyRegexp(re);
}
