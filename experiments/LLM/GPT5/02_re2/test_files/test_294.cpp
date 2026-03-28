// File: compiler_plus_test_294.cc
#include <gtest/gtest.h>
#include "re2/compile.cc"   // Adjust include path if your build expects a header instead.
#include "re2/prog.h"

using namespace re2;

class CompilerPlusTest_294 : public ::testing::Test {
protected:
    Compiler comp_;  // Default-constructed; tests only call Plus() as a black box.

    // Helper to make a safe input Frag whose end patch list is "null" (so Patch() is a no-op).
    // We rely on Frag() default ctor setting end to a null patch list.
    static Frag MakeInputFrag(uint32_t begin, bool nullable) {
        Frag a;               // end is kNullPatchList by default (no observable patching)
        a.begin = begin;      // public field per provided interface
        a.nullable = nullable;
        return a;
    }
};

// Normal behavior (nongreedy = true): begin preserved, nullable preserved,
// and returned patch list encodes an even pointer (LSB = 0) per Mk(id<<1).
TEST_F(CompilerPlusTest_294, Plus_NonGreedy_EvenPatchBit_294) {
    Frag in = MakeInputFrag(/*begin=*/42, /*nullable=*/false);

    Frag out = comp_.Plus(in, /*nongreedy=*/true);

    // Observable: begin and nullable are preserved.
    EXPECT_EQ(out.begin, in.begin);
    EXPECT_EQ(out.nullable, in.nullable);

    // Observable from returned PatchList: bit 0 indicates branch (even for nongreedy path).
    // We do NOT assume actual id value; only that nongreedy chooses the even branch.
    EXPECT_EQ(out.end.head & 1u, 0u);
}

// Normal behavior (nongreedy = false): begin preserved, nullable preserved,
// and returned patch list encodes an odd pointer (LSB = 1) per Mk((id<<1)|1).
TEST_F(CompilerPlusTest_294, Plus_Greedy_OddPatchBit_294) {
    Frag in = MakeInputFrag(/*begin=*/7, /*nullable=*/true);

    Frag out = comp_.Plus(in, /*nongreedy=*/false);

    EXPECT_EQ(out.begin, in.begin);
    EXPECT_EQ(out.nullable, in.nullable);
    EXPECT_EQ(out.end.head & 1u, 1u);
}

// Boundary: begin==0 should still be preserved, with correct even/odd selection by nongreedy flag.
TEST_F(CompilerPlusTest_294, Plus_BeginZeroPreserved_294) {
    Frag in = MakeInputFrag(/*begin=*/0, /*nullable=*/true);

    Frag out_ng = comp_.Plus(in, /*nongreedy=*/true);
    EXPECT_EQ(out_ng.begin, 0u);
    EXPECT_EQ(out_ng.nullable, true);
    EXPECT_EQ(out_ng.end.head & 1u, 0u);

    Frag out_g = comp_.Plus(in, /*nongreedy=*/false);
    EXPECT_EQ(out_g.begin, 0u);
    EXPECT_EQ(out_g.nullable, true);
    EXPECT_EQ(out_g.end.head & 1u, 1u);
}

// Sanity: the returned PatchList should be non-null (some implementation-dependent value),
// but we only assert that Mk(...) produced a consistent, self-contained list representation.
// We avoid any assumptions about internal storage beyond the exposed head/tail fields.
TEST_F(CompilerPlusTest_294, Plus_ReturnsValidPatchListShape_294) {
    Frag in = MakeInputFrag(/*begin=*/123, /*nullable=*/false);

    Frag out = comp_.Plus(in, /*nongreedy=*/true);

    // We can't (and won't) inspect internal inst_ or the patched program.
    // The only observable fields are head/tail, which must hold a consistent encoding.
    // At minimum, head should change based on Plus() creating a new inst id.
    // We just verify it's not the "null" patch list shape we passed in.
    Frag in_default; // has kNullPatchList
    // Compare shapes: if head/tail are both zero for null lists in your implementation,
    // this ensures Plus() produced a different shape (typical in RE2 PatchList::Mk).
    bool shape_changed = (out.end.head != in_default.end.head) || (out.end.tail != in_default.end.tail);
    EXPECT_TRUE(shape_changed);
}
