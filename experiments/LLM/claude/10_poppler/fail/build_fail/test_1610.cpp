#include <gtest/gtest.h>
#include <cstring>
#include <cstdint>

// Include the implementation file to access the static function
#include "Decrypt.cc"

class InvMixColumnsTest_1610 : public ::testing::Test {
protected:
    unsigned char state[16];
};

// Test that invMixColumns on an all-zero state produces all zeros
TEST_F(InvMixColumnsTest_1610, AllZerosState_1610) {
    memset(state, 0, 16);
    invMixColumns(state);
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(state[i], 0) << "Byte " << i << " should be 0";
    }
}

// Test invMixColumns with a known AES test vector
// The AES state is stored column-major: state[row + 4*col] but here
// the layout is state[4*row + col] based on the indexing pattern:
// state[c], state[4+c], state[8+c], state[12+c] for column c
TEST_F(InvMixColumnsTest_1610, KnownTestVector_1610) {
    // After MixColumns in AES, applying invMixColumns should reverse it.
    // Using a known AES round state from FIPS 197 test vectors.
    // State after MixColumns (from FIPS 197 Appendix B):
    // Column-major: the state array layout is:
    // state[0..3] = row 0, state[4..7] = row 1, etc.
    
    // Input to invMixColumns (result of MixColumns):
    // Row 0: 04 e0 48 28
    // Row 1: 66 cb f8 06
    // Row 2: 81 19 d3 26
    // Row 3: e5 9a 7a 4c
    unsigned char input[16] = {
        0x04, 0xe0, 0x48, 0x28,
        0x66, 0xcb, 0xf8, 0x06,
        0x81, 0x19, 0xd3, 0x26,
        0xe5, 0x9a, 0x7a, 0x4c
    };
    
    // Expected output (before MixColumns):
    // Row 0: d4 e0 b8 1e
    // Row 1: bf b4 41 27
    // Row 2: 5d 52 11 98
    // Row 3: 30 ae f1 e5
    unsigned char expected[16] = {
        0xd4, 0xe0, 0xb8, 0x1e,
        0xbf, 0xb4, 0x41, 0x27,
        0x5d, 0x52, 0x11, 0x98,
        0x30, 0xae, 0xf1, 0xe5
    };
    
    memcpy(state, input, 16);
    invMixColumns(state);
    
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(state[i], expected[i]) << "Mismatch at byte " << i;
    }
}

// Test with identity-like single column input
TEST_F(InvMixColumnsTest_1610, SingleColumnNonZero_1610) {
    // Set only column 0 to non-zero, rest zero
    memset(state, 0, 16);
    state[0] = 0x01;  // row 0, col 0
    state[4] = 0x00;  // row 1, col 0
    state[8] = 0x00;  // row 2, col 0
    state[12] = 0x00; // row 3, col 0
    
    invMixColumns(state);
    
    // invMixColumns of [01, 00, 00, 00] should give [0e, 09, 0d, 0b]
    EXPECT_EQ(state[0], 0x0e);
    EXPECT_EQ(state[4], 0x09);
    EXPECT_EQ(state[8], 0x0d);
    EXPECT_EQ(state[12], 0x0b);
    
    // Other columns should remain zero
    for (int c = 1; c < 4; c++) {
        EXPECT_EQ(state[c], 0);
        EXPECT_EQ(state[4 + c], 0);
        EXPECT_EQ(state[8 + c], 0);
        EXPECT_EQ(state[12 + c], 0);
    }
}

// Test with all 0xFF bytes
TEST_F(InvMixColumnsTest_1610, AllOnesState_1610) {
    memset(state, 0xFF, 16);
    invMixColumns(state);
    
    // invMixColumns of [ff, ff, ff, ff] = ff*(0e ^ 0b ^ 0d ^ 09) for each
    // 0e ^ 0b ^ 0d ^ 09 = 0e ^ 0b = 05, 0d ^ 09 = 04, 05 ^ 04 = 01
    // So each byte should be ff * 01 = ff
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(state[i], 0xFF) << "Byte " << i << " should be 0xFF";
    }
}

// Test that each column is processed independently
TEST_F(InvMixColumnsTest_1610, ColumnsAreIndependent_1610) {
    // Set column 0 to some values and column 1 to different values
    memset(state, 0, 16);
    
    // Column 0
    state[0] = 0xdb;
    state[4] = 0x13;
    state[8] = 0x53;
    state[12] = 0x45;
    
    unsigned char state_copy[16];
    memcpy(state_copy, state, 16);
    
    invMixColumns(state);
    
    // Columns 1, 2, 3 should still be zero (since input was zero)
    for (int c = 1; c < 4; c++) {
        EXPECT_EQ(state[c], 0);
        EXPECT_EQ(state[4 + c], 0);
        EXPECT_EQ(state[8 + c], 0);
        EXPECT_EQ(state[12 + c], 0);
    }
}

// Test with second column only
TEST_F(InvMixColumnsTest_1610, SecondColumnOnly_1610) {
    memset(state, 0, 16);
    state[1] = 0x01;
    state[5] = 0x00;
    state[9] = 0x00;
    state[13] = 0x00;
    
    invMixColumns(state);
    
    // Column 1 should have [0e, 09, 0d, 0b]
    EXPECT_EQ(state[1], 0x0e);
    EXPECT_EQ(state[5], 0x09);
    EXPECT_EQ(state[9], 0x0d);
    EXPECT_EQ(state[13], 0x0b);
    
    // Column 0 should be zero
    EXPECT_EQ(state[0], 0);
    EXPECT_EQ(state[4], 0);
    EXPECT_EQ(state[8], 0);
    EXPECT_EQ(state[12], 0);
}

// Test with unit vector in row 1
TEST_F(InvMixColumnsTest_1610, UnitVectorRow1_1610) {
    memset(state, 0, 16);
    state[0] = 0x00;
    state[4] = 0x01;  // row 1, col 0
    state[8] = 0x00;
    state[12] = 0x00;
    
    invMixColumns(state);
    
    // invMixColumns of [00, 01, 00, 00] should give [0b, 0e, 09, 0d]
    EXPECT_EQ(state[0], 0x0b);
    EXPECT_EQ(state[4], 0x0e);
    EXPECT_EQ(state[8], 0x09);
    EXPECT_EQ(state[12], 0x0d);
}

// Test with unit vector in row 2
TEST_F(InvMixColumnsTest_1610, UnitVectorRow2_1610) {
    memset(state, 0, 16);
    state[0] = 0x00;
    state[4] = 0x00;
    state[8] = 0x01;  // row 2, col 0
    state[12] = 0x00;
    
    invMixColumns(state);
    
    // invMixColumns of [00, 00, 01, 00] should give [0d, 0b, 0e, 09]
    EXPECT_EQ(state[0], 0x0d);
    EXPECT_EQ(state[4], 0x0b);
    EXPECT_EQ(state[8], 0x0e);
    EXPECT_EQ(state[12], 0x09);
}

// Test with unit vector in row 3
TEST_F(InvMixColumnsTest_1610, UnitVectorRow3_1610) {
    memset(state, 0, 16);
    state[0] = 0x00;
    state[4] = 0x00;
    state[8] = 0x00;
    state[12] = 0x01;  // row 3, col 0
    
    invMixColumns(state);
    
    // invMixColumns of [00, 00, 00, 01] should give [09, 0d, 0b, 0e]
    EXPECT_EQ(state[0], 0x09);
    EXPECT_EQ(state[4], 0x0d);
    EXPECT_EQ(state[8], 0x0b);
    EXPECT_EQ(state[12], 0x0e);
}

// Test linearity: invMixColumns(a XOR b) == invMixColumns(a) XOR invMixColumns(b)
TEST_F(InvMixColumnsTest_1610, LinearityProperty_1610) {
    unsigned char a[16], b[16], a_xor_b[16];
    unsigned char result_a[16], result_b[16], result_axorb[16];
    
    // Set up two arbitrary states
    for (int i = 0; i < 16; i++) {
        a[i] = (unsigned char)(i * 17 + 3);
        b[i] = (unsigned char)(i * 31 + 7);
        a_xor_b[i] = a[i] ^ b[i];
    }
    
    memcpy(result_a, a, 16);
    invMixColumns(result_a);
    
    memcpy(result_b, b, 16);
    invMixColumns(result_b);
    
    memcpy(result_axorb, a_xor_b, 16);
    invMixColumns(result_axorb);
    
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(result_axorb[i], (unsigned char)(result_a[i] ^ result_b[i]))
            << "Linearity failed at byte " << i;
    }
}
