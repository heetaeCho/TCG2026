#include <gtest/gtest.h>
#include "poppler/UnicodeTypeTable.h"

// We need access to the static function decomp_compat.
// Since it's defined as static in a .cc file, we need to include the source
// or declare it extern. For testing purposes, we'll include the source file
// or use a wrapper. Since the function is static, we'll need to test it
// through whatever public interface exposes it.
// 
// Looking at the poppler codebase, unicodeNormalizeNFKC or similar functions
// typically call decomp_compat. However, since we're told to test the
// interface provided, and decomp_compat is the function shown, let's assume
// we can access it (perhaps through a test helper or by making it non-static
// for testing).

// For this test, we assume decomp_compat is accessible.
// In practice, you may need to #include the .cc file or use a build system trick.

typedef unsigned int Unicode;

// Forward declaration - in real code this would be properly linked
extern int decomp_compat(Unicode u, Unicode *buf, bool reverseRTL);

class DecompCompatTest_1875 : public ::testing::Test {
protected:
    Unicode buf[32];
    
    void SetUp() override {
        memset(buf, 0, sizeof(buf));
    }
};

// Test: Character not in decomposition table returns 1 and copies itself to buf
TEST_F(DecompCompatTest_1875, CharNotInTable_ReturnsItself_1875) {
    // ASCII 'A' (65) is not in the decomp table (table starts at 160)
    int len = decomp_compat(65, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(65u, buf[0]);
}

// Test: Character below table range returns 1 and copies itself
TEST_F(DecompCompatTest_1875, CharBelowRange_ReturnsItself_1875) {
    int len = decomp_compat(0, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(0u, buf[0]);
}

// Test: Character 160 (NBSP) decomposes to space (length 1, offset 0)
TEST_F(DecompCompatTest_1875, NBSP_DecomposesToSpace_1875) {
    int len = decomp_compat(160, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(32u, buf[0]); // space
}

// Test: Character 168 decomposes to length 2 (space + diaeresis)
TEST_F(DecompCompatTest_1875, Char168_DecomposesToLen2_1875) {
    int len = decomp_compat(168, buf, false);
    EXPECT_EQ(2, len);
    EXPECT_EQ(32u, buf[0]);  // space
    EXPECT_EQ(776u, buf[1]); // combining diaeresis
}

// Test: Character 192 (À) decomposes to A + grave
TEST_F(DecompCompatTest_1875, CharAGrave_Decomposition_1875) {
    int len = decomp_compat(192, buf, false);
    EXPECT_EQ(2, len);
    EXPECT_EQ(65u, buf[0]);  // A
    EXPECT_EQ(768u, buf[1]); // combining grave
}

// Test: Character 188 (¼) decomposes to 3 characters: 1, fraction slash, 4
TEST_F(DecompCompatTest_1875, CharOneFourth_DecomposesToThree_1875) {
    int len = decomp_compat(188, buf, false);
    EXPECT_EQ(3, len);
    EXPECT_EQ(49u, buf[0]);    // '1'
    EXPECT_EQ(8260u, buf[1]);  // fraction slash
    EXPECT_EQ(52u, buf[2]);    // '4'
}

// Test: Character 178 (²) decomposes to '2' (superscript 2)
TEST_F(DecompCompatTest_1875, CharSuperscript2_1875) {
    int len = decomp_compat(178, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(50u, buf[0]); // '2'
}

// Test: Null buffer - just returns length without writing
TEST_F(DecompCompatTest_1875, NullBuffer_ReturnsLength_1875) {
    int len = decomp_compat(192, nullptr, false);
    EXPECT_EQ(2, len);
}

// Test: Null buffer for character not in table
TEST_F(DecompCompatTest_1875, NullBuffer_NotInTable_ReturnsOne_1875) {
    int len = decomp_compat(65, nullptr, false);
    EXPECT_EQ(1, len);
}

// Test: Character 452 (DZ with caron) decomposes to 3 chars
TEST_F(DecompCompatTest_1875, CharDZCaron_DecomposesToThree_1875) {
    int len = decomp_compat(452, buf, false);
    EXPECT_EQ(3, len);
    // DZ + caron: D, Z, caron
}

// Test: Character way above table range returns 1
TEST_F(DecompCompatTest_1875, CharAboveRange_ReturnsItself_1875) {
    int len = decomp_compat(0x3FFFFF, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(0x3FFFFFu, buf[0]);
}

// Test: First character in table (160)
TEST_F(DecompCompatTest_1875, FirstCharInTable_1875) {
    int len = decomp_compat(160, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(32u, buf[0]);
}

// Test: Character 383 (long s) decomposes to 's'
TEST_F(DecompCompatTest_1875, LongS_DecomposesToS_1875) {
    int len = decomp_compat(383, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(115u, buf[0]); // 's' at offset 356
}

// Test: Character in gap (not in table, e.g., 161 is not listed)
TEST_F(DecompCompatTest_1875, CharInGap_ReturnsItself_1875) {
    // 161 is not in the decomp table
    int len = decomp_compat(161, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(161u, buf[0]);
}

// Test: Character 8230 (…) decomposes to three periods
TEST_F(DecompCompatTest_1875, Ellipsis_DecomposesToThreeDots_1875) {
    int len = decomp_compat(8230, buf, false);
    EXPECT_EQ(3, len);
    EXPECT_EQ(46u, buf[0]); // '.'
    EXPECT_EQ(46u, buf[1]); // '.'
    EXPECT_EQ(46u, buf[2]); // '.'
}

// Test: Character 8192 (en quad) decomposes to space
TEST_F(DecompCompatTest_1875, EnQuad_DecomposesToSpace_1875) {
    int len = decomp_compat(8192, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(32u, buf[0]);
}

// Test: Character 12288 (ideographic space) decomposes to space
TEST_F(DecompCompatTest_1875, IdeographicSpace_DecomposesToSpace_1875) {
    int len = decomp_compat(12288, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(32u, buf[0]);
}

// Test: reverseRTL parameter with false
TEST_F(DecompCompatTest_1875, ReverseRTL_False_1875) {
    int len = decomp_compat(192, buf, false);
    EXPECT_EQ(2, len);
    EXPECT_EQ(65u, buf[0]);
    EXPECT_EQ(768u, buf[1]);
}

// Test: Character 65296 (fullwidth 0) decomposes to '0'
TEST_F(DecompCompatTest_1875, FullwidthZero_DecomposesToZero_1875) {
    int len = decomp_compat(65296, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(48u, buf[0]); // '0'
}

// Test: Character 65313 (fullwidth A) decomposes to 'A'
TEST_F(DecompCompatTest_1875, FullwidthA_DecomposesToA_1875) {
    int len = decomp_compat(65313, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(65u, buf[0]); // 'A'
}

// Test: Character 65345 (fullwidth a) decomposes to 'a'
TEST_F(DecompCompatTest_1875, FullwidthLowerA_DecomposesToa_1875) {
    int len = decomp_compat(65345, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(97u, buf[0]); // 'a'
}

// Test: Last character in table area (check a CJK compatibility character)
TEST_F(DecompCompatTest_1875, CJKCompatChar_1875) {
    // 195101 is the last entry with character value in the table
    int len = decomp_compat(195101, buf, false);
    EXPECT_EQ(1, len);
    // Should decompose to some CJK character
}

// Test: Character 170 (ª) decomposes to 'a'
TEST_F(DecompCompatTest_1875, FeminineOrdinal_DecomposesToA_1875) {
    int len = decomp_compat(170, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(97u, buf[0]); // 'a'
}

// Test: Character 185 (¹) decomposes to '1'
TEST_F(DecompCompatTest_1875, Superscript1_DecomposesTo1_1875) {
    int len = decomp_compat(185, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(49u, buf[0]); // '1'
}

// Test: Character 186 (º) decomposes to 'o'
TEST_F(DecompCompatTest_1875, MasculineOrdinal_DecomposesToO_1875) {
    int len = decomp_compat(186, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(111u, buf[0]); // 'o'
}

// Test: Character just after table range
TEST_F(DecompCompatTest_1875, CharJustAfterTable_ReturnsItself_1875) {
    // The last character in the table is 195101
    // A character after that should return itself
    int len = decomp_compat(200000, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(200000u, buf[0]);
}

// Test: Multiple decompositions don't interfere
TEST_F(DecompCompatTest_1875, MultipleDecompositions_Independent_1875) {
    Unicode buf1[32], buf2[32];
    int len1 = decomp_compat(192, buf1, false); // À -> A + grave
    int len2 = decomp_compat(193, buf2, false); // Á -> A + acute
    
    EXPECT_EQ(2, len1);
    EXPECT_EQ(2, len2);
    EXPECT_EQ(65u, buf1[0]);
    EXPECT_EQ(768u, buf1[1]); // grave
    EXPECT_EQ(65u, buf2[0]);
    EXPECT_EQ(769u, buf2[1]); // acute
}

// Test: Character 179 (³) decomposes to '3'
TEST_F(DecompCompatTest_1875, Superscript3_DecomposesTo3_1875) {
    int len = decomp_compat(179, buf, false);
    EXPECT_EQ(1, len);
    EXPECT_EQ(51u, buf[0]); // '3'
}

// Test: Character 8279 decomposes to 4 primes
TEST_F(DecompCompatTest_1875, QuadruplePrime_1875) {
    int len = decomp_compat(8279, buf, false);
    EXPECT_EQ(4, len);
    EXPECT_EQ(8242u, buf[0]);
    EXPECT_EQ(8242u, buf[1]);
    EXPECT_EQ(8242u, buf[2]);
    EXPECT_EQ(8242u, buf[3]);
}

// Test: Character 64256 (ff ligature) decomposes to f, f
TEST_F(DecompCompatTest_1875, FFLigature_DecomposesToFF_1875) {
    int len = decomp_compat(64256, buf, false);
    EXPECT_EQ(2, len);
    EXPECT_EQ(102u, buf[0]); // 'f'
    EXPECT_EQ(102u, buf[1]); // 'f'
}

// Test: Character 64257 (fi ligature) decomposes to f, i
TEST_F(DecompCompatTest_1875, FILigature_DecomposesToFI_1875) {
    int len = decomp_compat(64257, buf, false);
    EXPECT_EQ(2, len);
    EXPECT_EQ(102u, buf[0]); // 'f'
    EXPECT_EQ(105u, buf[1]); // 'i'
}

// Test: Character 64259 (ffi ligature) decomposes to f, f, i
TEST_F(DecompCompatTest_1875, FFILigature_DecomposesToFFI_1875) {
    int len = decomp_compat(64259, buf, false);
    EXPECT_EQ(3, len);
    EXPECT_EQ(102u, buf[0]); // 'f'
    EXPECT_EQ(102u, buf[1]); // 'f'
    EXPECT_EQ(105u, buf[2]); // 'i'
}
