// File: ./TestProjects/re2/tests/compiler_compile_set_330_test.cc
#include <gtest/gtest.h>

#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"
#include "re2/compile.cc"  // for Compiler declaration (as provided in the prompt)

using re2::Compiler;
using re2::Prog;
using re2::Regexp;
using re2::RE2;

namespace {

class CompilerCompileSetTest_330 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Ensure DFA "bail" behavior is off by default for normal tests.
    Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
  }
  void TearDown() override {
    Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
  }

  // Creates a parsed Regexp (or returns nullptr on parse failure).
  // Uses flags = 0 based on the interface (don’t infer internal behavior).
  Regexp* MakeRegexp(const std::string& pattern) {
    return Regexp::Parse(pattern, static_cast<Regexp::ParseFlags>(0), /*status=*/nullptr);
  }
};

// --- Normal operation ---

// Verifies: returns non-null Prog; anchors are set; start and start_unanchored agree.
TEST_F(CompilerCompileSetTest_330, ReturnsProgAndSetsAnchors_330) {
  Regexp* re = MakeRegexp("a");
  ASSERT_NE(re, nullptr) << "Regexp::Parse failed for a simple pattern";

  Compiler c;
  Prog* prog = c.CompileSet(re, RE2::ANCHOR_BOTH, /*max_mem=*/1 << 20);
  ASSERT_NE(prog, nullptr);

  // Observable flags set by CompileSet:
  EXPECT_TRUE(prog->anchor_start());
  EXPECT_TRUE(prog->anchor_end());

  // CompileSet sets both starts to the same 'all.begin'.
  EXPECT_EQ(prog->start(), prog->start_unanchored());

  // Clean up: CompileSet does not own 're'.
  re->Decref();
  delete prog;
}

// UNANCHORED path: still returns a valid program and sets anchors.
// We cannot assert the internal Cat(DotStar(), ...) but we can observe the same flags.
TEST_F(CompilerCompileSetTest_330, UnanchoredStillReturnsValidProg_330) {
  Regexp* re = MakeRegexp("abc");
  ASSERT_NE(re, nullptr);

  Compiler c;
  Prog* prog = c.CompileSet(re, RE2::UNANCHORED, /*max_mem=*/1 << 20);
  ASSERT_NE(prog, nullptr);

  EXPECT_TRUE(prog->anchor_start());
  EXPECT_TRUE(prog->anchor_end());
  EXPECT_EQ(prog->start(), prog->start_unanchored());

  re->Decref();
  delete prog;
}

// Boundary: empty pattern should still compile (observable: non-null result and flags set).
TEST_F(CompilerCompileSetTest_330, EmptyPatternCompiles_330) {
  Regexp* re = MakeRegexp("");
  ASSERT_NE(re, nullptr);

  Compiler c;
  Prog* prog = c.CompileSet(re, RE2::ANCHOR_START, /*max_mem=*/1 << 20);
  ASSERT_NE(prog, nullptr);

  EXPECT_TRUE(prog->anchor_start());
  EXPECT_TRUE(prog->anchor_end());
  EXPECT_EQ(prog->start(), prog->start_unanchored());

  re->Decref();
  delete prog;
}

// --- Exceptional / error cases (observable via interface) ---

// When the compiler runs out of memory during Finish, CompileSet should return NULL.
// We simulate with a very small max_mem.
TEST_F(CompilerCompileSetTest_330, ReturnsNullWhenFinishFailsDueToMemLimit_330) {
  Regexp* re = MakeRegexp("(a|b|c|d){100}");  // something bigger than a tiny memory budget
  ASSERT_NE(re, nullptr);

  Compiler c;
  // Intentionally tiny memory budget to provoke a failure in Finish().
  Prog* prog = c.CompileSet(re, RE2::ANCHOR_BOTH, /*max_mem=*/1);
  EXPECT_EQ(prog, nullptr);

  re->Decref();
}

// If the post-Finish DFA probe "fails" (observable through TESTING_ONLY knob),
// CompileSet should delete the Prog and return NULL.
TEST_F(CompilerCompileSetTest_330, ReturnsNullWhenDFABails_330) {
  Regexp* re = MakeRegexp("hello.*world");
  ASSERT_NE(re, nullptr);

  // Force the DFA check to "bail", which CompileSet observes via the 'failed' out param.
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);

  Compiler c;
  Prog* prog = c.CompileSet(re, RE2::ANCHOR_BOTH, /*max_mem=*/1 << 20);
  EXPECT_EQ(prog, nullptr);

  // Reset knob for safety (also done in TearDown).
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);

  re->Decref();
}

// (Optional) Defensive: A very complex pattern with extremely small memory also returns NULL.
// This overlaps the memory-failure path but with UNANCHORED to exercise that branch too.
TEST_F(CompilerCompileSetTest_330, UnanchoredAndTinyMemReturnsNull_330) {
  Regexp* re = MakeRegexp("(ab|cd|ef|gh|ij|kl|mn|op|qr|st){50}");
  ASSERT_NE(re, nullptr);

  Compiler c;
  Prog* prog = c.CompileSet(re, RE2::UNANCHORED, /*max_mem=*/1);
  EXPECT_EQ(prog, nullptr);

  re->Decref();
}

}  // namespace
