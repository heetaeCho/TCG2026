// File: compile_add_runerange_latin1_test.cc

#include <gtest/gtest.h>
#include "re2/compile.h"  // Adjust include path if different in your tree

using namespace re2;

class Compiler_AddRuneRangeLatin1_Test_314 : public ::testing::Test {
protected:
    Compiler c_;

    // Helper: build a range via BeginRange/Add.../EndRange
    Frag BuildRangeLatin1(Rune lo, Rune hi, bool fold) {
        c_.BeginRange();
        c_.AddRuneRangeLatin1(lo, hi, fold);
        return c_.EndRange();
    }

    // Helper: expected single-byte range using the public ByteRange factory
    Frag ExpectedByteRange(int lo, int hi, bool fold) {
        return c_.ByteRange(lo, hi, fold);
    }

    // Helper: "no change" expectation when nothing was added to range.
    Frag NoMatchFrag() {
        return c_.NoMatch();
    }
};

// Normal operation: within Latin-1 range, foldcase=false
TEST_F(Compiler_AddRuneRangeLatin1_Test_314, AddsExactRangeWithinLatin1_NoFold_314) {
    // Arrange
    const Rune lo = 0x41;   // 'A'
    const Rune hi = 0x5A;   // 'Z'

    // Act
    Frag got = BuildRangeLatin1(lo, hi, /*fold=*/false);
    Frag expected = ExpectedByteRange(static_cast<int>(lo), static_cast<int>(hi), /*fold=*/false);

    // Assert
    // We only verify via public observable result type Frag.
    // The codebase's Frag should be comparable (same shape/behavior).
    EXPECT_EQ(got.i, expected.i);
    EXPECT_EQ(got.out, expected.out);
}

// Normal operation: within Latin-1 range, foldcase=true
TEST_F(Compiler_AddRuneRangeLatin1_Test_314, AddsExactRangeWithinLatin1_Fold_314) {
    const Rune lo = 0x61;   // 'a'
    const Rune hi = 0x7A;   // 'z'
    Frag got = BuildRangeLatin1(lo, hi, /*fold=*/true);
    Frag expected = ExpectedByteRange(static_cast<int>(lo), static_cast<int>(hi), /*fold=*/true);

    EXPECT_EQ(got.i, expected.i);
    EXPECT_EQ(got.out, expected.out);
}

// Boundary: hi > 0xFF should be clamped to 0xFF (and still added)
TEST_F(Compiler_AddRuneRangeLatin1_Test_314, ClampsHiAboveLatin1_314) {
    const Rune lo = 0xF0;    // within Latin-1
    const Rune hi = 0x1FF;   // above Latin-1 -> should clamp to 0xFF

    Frag got = BuildRangeLatin1(lo, hi, /*fold=*/false);
    Frag expected = ExpectedByteRange(static_cast<int>(lo), 0xFF, /*fold=*/false);

    EXPECT_EQ(got.i, expected.i);
    EXPECT_EQ(got.out, expected.out);
}

// Early-return: lo > hi -> nothing added
TEST_F(Compiler_AddRuneRangeLatin1_Test_314, EarlyReturn_WhenLoGreaterThanHi_314) {
    const Rune lo = 0x7F;
    const Rune hi = 0x10;

    Frag got = BuildRangeLatin1(lo, hi, /*fold=*/false);
    Frag expected = NoMatchFrag();

    EXPECT_EQ(got.i, expected.i);
    EXPECT_EQ(got.out, expected.out);
}

// Early-return: lo > 0xFF -> nothing added (entirely outside Latin-1)
TEST_F(Compiler_AddRuneRangeLatin1_Test_314, EarlyReturn_WhenLoBeyondLatin1_314) {
    const Rune lo = 0x1A0;   // > 0xFF
    const Rune hi = 0x1FF;   // > 0xFF

    Frag got = BuildRangeLatin1(lo, hi, /*fold=*/true);
    Frag expected = NoMatchFrag();

    EXPECT_EQ(got.i, expected.i);
    EXPECT_EQ(got.out, expected.out);
}

// Boundary: lo == 0xFF and hi >= 0xFF -> single byte 0xFF
TEST_F(Compiler_AddRuneRangeLatin1_Test_314, SingleByte_MaxLatin1_314) {
    const Rune lo = 0xFF;
    const Rune hi = 0x1FFFF; // will clamp to 0xFF

    Frag got = BuildRangeLatin1(lo, hi, /*fold=*/false);
    Frag expected = ExpectedByteRange(0xFF, 0xFF, /*fold=*/false);

    EXPECT_EQ(got.i, expected.i);
    EXPECT_EQ(got.out, expected.out);
}

// Boundary: lo == hi within range -> single byte range
TEST_F(Compiler_AddRuneRangeLatin1_Test_314, SingleByte_ExactWithinLatin1_314) {
    const Rune ch = 0xAB;

    Frag got = BuildRangeLatin1(ch, ch, /*fold=*/true);
    Frag expected = ExpectedByteRange(static_cast<int>(ch), static_cast<int>(ch), /*fold=*/true);

    EXPECT_EQ(got.i, expected.i);
    EXPECT_EQ(got.out, expected.out);
}
