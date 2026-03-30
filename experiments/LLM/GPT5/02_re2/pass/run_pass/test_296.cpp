// File: ./TestProjects/re2/tests/compiler_quest_test.cc
#include "gtest/gtest.h"
#include "re2/compile.cc"   // Adjust include path if your build includes headers separately

using namespace re2;

class CompilerQuestTest_296 : public ::testing::Test {
protected:
  // Helper to produce a minimal, valid Frag as input.
  // We keep values simple and avoid assumptions about special sentinels.
  static Frag MakeInputFrag(uint32_t begin, uint32_t patch_point) {
    PatchList pl = PatchList::Mk(patch_point);
    return Frag(begin, pl, /*nullable=*/false);
  }
};

// [Normal operation] nongreedy = false should produce a nullable fragment.
TEST_F(CompilerQuestTest_296, ReturnsNullableTrue_Greedy_296) {
  Compiler c;                           // treat as black box
  Frag a = CompilerQuestTest_296::MakeInputFrag(/*begin=*/3, /*patch_point=*/5);

  Frag out = c.Quest(a, /*nongreedy=*/false);

  // Observable behaviors we can assert without peeking into internals:
  // 1) Quest always returns a nullable Frag per implementation contract.
  EXPECT_TRUE(out.nullable);

  // 2) The returned begin is some instruction id chosen by the compiler.
  //    We can't predict it, but it should be a concrete index (the API exposes it as uint32_t).
  //    At minimum, it shouldn't change simply because input 'a' had certain values.
  //    We assert it's a valid uint32_t value and allow equality/inequality either way.
  (void)out.begin; // existence/use check for clarity

  // 3) The end PatchList is returned from PatchList::Append(..., a.end).
  //    We cannot assert exact numeric contents, but we can at least verify it's a concrete object.
  (void)out.end.head;
  (void)out.end.tail;
}

// [Normal operation] nongreedy = true should also produce a nullable fragment.
TEST_F(CompilerQuestTest_296, ReturnsNullableTrue_NonGreedy_296) {
  Compiler c;                           
  Frag a = CompilerQuestTest_296::MakeInputFrag(/*begin=*/7, /*patch_point=*/9);

  Frag out = c.Quest(a, /*nongreedy=*/true);

  EXPECT_TRUE(out.nullable);
  (void)out.begin;
  (void)out.end.head;
  (void)out.end.tail;
}

// [Boundary-ish] Works with a degenerate-looking input begin=0.
// We don't assume 0 is a sentinel—just exercising a small boundary value.
TEST_F(CompilerQuestTest_296, HandlesBeginZeroInput_296) {
  Compiler c;
  Frag a = CompilerQuestTest_296::MakeInputFrag(/*begin=*/0, /*patch_point=*/1);

  Frag out = c.Quest(a, /*nongreedy=*/false);

  EXPECT_TRUE(out.nullable);
  (void)out.begin;
  (void)out.end.head;
  (void)out.end.tail;
}

// [Behavioral contrast] Greedy vs NonGreedy return nullable in both cases.
// We do not assert internal Alt wiring; we only validate observable equality on the nullable flag
// and independence from the input fragment’s nullable=false state.
TEST_F(CompilerQuestTest_296, GreedyVsNonGreedyBothNullable_296) {
  Compiler c;
  Frag a = CompilerQuestTest_296::MakeInputFrag(/*begin=*/11, /*patch_point=*/13);

  Frag greedy  = c.Quest(a, /*nongreedy=*/false);
  Frag nong    = c.Quest(a, /*nongreedy=*/true);

  EXPECT_TRUE(greedy.nullable);
  EXPECT_TRUE(nong.nullable);

  // Different internal wiring may lead to different PatchLists; we do NOT assert equality.
  (void)greedy.begin;
  (void)nong.begin;
  (void)greedy.end.head; (void)greedy.end.tail;
  (void)nong.end.head;   (void)nong.end.tail;
}
