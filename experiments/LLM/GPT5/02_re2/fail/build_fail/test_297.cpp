// File: compile_byterange_test_297.cc

#include <gtest/gtest.h>

// Bring in the minimal interfaces/types shown in the prompt.
// (We assume your build/test environment exposes these as in the repo layout.)
#include "re2/compile.cc"
#include "re2/prog.h"

using namespace re2;

class CompilerByteRangeTest_297 : public ::testing::Test {
protected:
    Compiler c_; // Default-construct the compiler; we treat it as a black box.
};

// [Normal] Calling ByteRange should return a non-nullable fragment with a valid begin id.
// Also verify PatchList head/tail are constructed via PatchList::Mk(id << 1).
TEST_F(CompilerByteRangeTest_297, ByteRange_ReturnsNonNullableFrag_297) {
    Frag f = c_.ByteRange(0, 255, /*foldcase=*/false);

    // Observable/structural checks only (no peeking into internal state):
    ASSERT_GE(f.begin, 0) << "begin should be a non-negative instruction id";
    EXPECT_FALSE(f.nullable) << "ByteRange fragments are not nullable by construction";

    // PatchList::Mk(id<<1) is used when returning the Frag; validate that structure.
    const uint32_t expected = static_cast<uint32_t>(f.begin) << 1;
    EXPECT_EQ(f.out.head, expected);
    EXPECT_EQ(f.out.tail, expected);
}

// [Boundary] Single-value range: lo == hi should still produce a valid fragment.
TEST_F(CompilerByteRangeTest_297, ByteRange_SingleByteBoundary_297) {
    Frag f = c_.ByteRange(42, 42, /*foldcase=*/false);

    ASSERT_GE(f.begin, 0);
    EXPECT_FALSE(f.nullable);

    const uint32_t expected = static_cast<uint32_t>(f.begin) << 1;
    EXPECT_EQ(f.out.head, expected);
    EXPECT_EQ(f.out.tail, expected);
}

// [Normal] Two successive ByteRange calls should allocate distinct begin ids (observable via Frag.begin).
TEST_F(CompilerByteRangeTest_297, ByteRange_AllocatesDistinctBeginIds_297) {
    Frag a = c_.ByteRange(0, 10, /*foldcase=*/false);
    Frag b = c_.ByteRange(20, 30, /*foldcase=*/false);

    ASSERT_GE(a.begin, 0);
    ASSERT_GE(b.begin, 0);
    EXPECT_NE(a.begin, b.begin) << "Separate ByteRange calls should yield distinct instruction ids";
}

// [Normal] Foldcase flag path should also produce a valid, non-nullable fragment.
TEST_F(CompilerByteRangeTest_297, ByteRange_FoldcaseTrue_297) {
    Frag f = c_.ByteRange('A', 'Z', /*foldcase=*/true);

    ASSERT_GE(f.begin, 0);
    EXPECT_FALSE(f.nullable);

    const uint32_t expected = static_cast<uint32_t>(f.begin) << 1;
    EXPECT_EQ(f.out.head, expected);
    EXPECT_EQ(f.out.tail, expected);
}

// [Boundary] Extremal byte-range inputs around typical Latin-1 limits should behave consistently.
TEST_F(CompilerByteRangeTest_297, ByteRange_Latin1Extremes_297) {
    Frag f1 = c_.ByteRange(0, 0, /*foldcase=*/false);
    Frag f2 = c_.ByteRange(255, 255, /*foldcase=*/false);

    ASSERT_GE(f1.begin, 0);
    ASSERT_GE(f2.begin, 0);
    EXPECT_FALSE(f1.nullable);
    EXPECT_FALSE(f2.nullable);

    uint32_t e1 = static_cast<uint32_t>(f1.begin) << 1;
    uint32_t e2 = static_cast<uint32_t>(f2.begin) << 1;
    EXPECT_EQ(f1.out.head, e1);
    EXPECT_EQ(f1.out.tail, e1);
    EXPECT_EQ(f2.out.head, e2);
    EXPECT_EQ(f2.out.tail, e2);
}
