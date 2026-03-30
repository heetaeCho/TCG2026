// File: compile_compile_tests_325.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/prog.h"
#include "re2/re2.h"

using namespace re2;

namespace {

// Small helper to parse a pattern into a Regexp*
static Regexp* ParseRegexp(const std::string& pattern,
                           Regexp::ParseFlags flags = Regexp::LikePerl) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, flags, &status);
  return re;
}

// For all tests: we compile from the public Regexp interface,
// which (per the provided partials) routes through Compiler::Compile.
// We only assert on Prog’s public getters (anchor flags, reversed flag,
// and the relationship between start and start_unanchored).

// Unanchored pattern: expect no anchors, and DotStar() prepended so
// start_unanchored != start.
TEST(CompilerCompileTest_325, UnanchoredPattern_SetsFlagsAndDotStar_325) {
  Regexp* re = ParseRegexp("a");
  ASSERT_NE(re, nullptr);

  // Forward compile
  Prog* prog = re->CompileToProg(/*max_mem=*/1 << 20);
  ASSERT_NE(prog, nullptr);

  EXPECT_FALSE(prog->reversed());
  EXPECT_FALSE(prog->anchor_start());
  EXPECT_FALSE(prog->anchor_end());

  // Because anchor_start() is false, Compile() prepends DotStar() before
  // setting start_unanchored, so the two starts should differ.
  EXPECT_NE(prog->start_unanchored(), prog->start());

  delete prog;
  re->Decref();
}

// ^a : anchored at start only.
// Forward: start=true, end=false, no DotStar() (so starts equal).
// Reversed: flags are swapped (start=false, end=true).
TEST(CompilerCompileTest_325, AnchorStart_ForwardAndReversedSwap_325) {
  Regexp* re = ParseRegexp("^a");
  ASSERT_NE(re, nullptr);

  // Forward compile
  Prog* fwd = re->CompileToProg(/*max_mem=*/1 << 20);
  ASSERT_NE(fwd, nullptr);
  EXPECT_FALSE(fwd->reversed());
  EXPECT_TRUE(fwd->anchor_start());
  EXPECT_FALSE(fwd->anchor_end());
  // With anchor_start==true, no DotStar() is inserted.
  EXPECT_EQ(fwd->start_unanchored(), fwd->start());

  delete fwd;

  // Reversed compile
  Prog* rev = re->CompileToReverseProg(/*max_mem=*/1 << 20);
  ASSERT_NE(rev, nullptr);
  EXPECT_TRUE(rev->reversed());
  // In reversed mode, Compile() swaps the anchor flags.
  EXPECT_FALSE(rev->anchor_start());  // swapped from start->end
  EXPECT_TRUE(rev->anchor_end());

  // Since anchor_start() is false in reversed, DotStar() is prepended.
  EXPECT_NE(rev->start_unanchored(), rev->start());

  delete rev;
  re->Decref();
}

// a$ : anchored at end only.
// Forward: start=false, end=true (DotStar() inserted -> starts differ).
// Reversed: flags are swapped (start=true, end=false) and starts equal.
TEST(CompilerCompileTest_325, AnchorEnd_ForwardAndReversedSwap_325) {
  Regexp* re = ParseRegexp("a$");
  ASSERT_NE(re, nullptr);

  // Forward compile
  Prog* fwd = re->CompileToProg(/*max_mem=*/1 << 20);
  ASSERT_NE(fwd, nullptr);
  EXPECT_FALSE(fwd->reversed());
  EXPECT_FALSE(fwd->anchor_start());
  EXPECT_TRUE(fwd->anchor_end());
  // No start anchor => DotStar() prepended
  EXPECT_NE(fwd->start_unanchored(), fwd->start());
  delete fwd;

  // Reversed compile
  Prog* rev = re->CompileToReverseProg(/*max_mem=*/1 << 20);
  ASSERT_NE(rev, nullptr);
  EXPECT_TRUE(rev->reversed());
  EXPECT_TRUE(rev->anchor_start());   // swapped
  EXPECT_FALSE(rev->anchor_end());
  // With start anchor true (after swap), no DotStar()
  EXPECT_EQ(rev->start_unanchored(), rev->start());

  delete rev;
  re->Decref();
}

// ^a$ : anchored at both ends.
// Forward and reversed should both report start=true, end=true,
// and no DotStar() (starts equal).
TEST(CompilerCompileTest_325, AnchorBoth_NoDotStar_ForwardAndReversed_325) {
  Regexp* re = ParseRegexp("^a$");
  ASSERT_NE(re, nullptr);

  // Forward compile
  Prog* fwd = re->CompileToProg(/*max_mem=*/1 << 20);
  ASSERT_NE(fwd, nullptr);
  EXPECT_FALSE(fwd->reversed());
  EXPECT_TRUE(fwd->anchor_start());
  EXPECT_TRUE(fwd->anchor_end());
  EXPECT_EQ(fwd->start_unanchored(), fwd->start());
  delete fwd;

  // Reversed compile
  Prog* rev = re->CompileToReverseProg(/*max_mem=*/1 << 20);
  ASSERT_NE(rev, nullptr);
  EXPECT_TRUE(rev->reversed());
  // Swapping both-true remains both-true.
  EXPECT_TRUE(rev->anchor_start());
  EXPECT_TRUE(rev->anchor_end());
  EXPECT_EQ(rev->start_unanchored(), rev->start());
  delete rev;

  re->Decref();
}

}  // namespace
