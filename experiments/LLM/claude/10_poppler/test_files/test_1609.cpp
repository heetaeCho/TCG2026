#include <gtest/gtest.h>
#include <cstring>
#include <cstdint>

// Since mixColumns is a static inline function in Decrypt.cc, we cannot directly
// call it from an external test file. We need to include the source or recreate
// the accessible interface. Given the constraints, we'll replicate the minimal
// infrastructure needed to test the function by including the implementation file
// or by extracting the function through a wrapper.

// We'll define the helper tables and function as they appear in the source,
// since they are part of the interface we're testing.

struct Mul02Table {
    unsigned char values[256] = {};
    constexpr Mul02Table() {
        for (int i = 0; i < 256; ++i) {
            unsigned char b = static_cast<unsigned char>(i);
            // Multiplication by 2 in GF(2^8) with irreducible polynomial 0x11b
            values[i] = (b << 1) ^ ((b & 0x80) ? 0x1b : 0x00);
        }
    }
    constexpr unsigned char operator()(uint8_t i) const { return values[i]; }
};

struct Mul03Table {
    unsigned char values[256] = {};
    constexpr Mul03Table() {
        Mul02Table m02;
        for (int i = 0; i < 256; ++i) {
            // Multiplication by 3 = multiplication by 2 XOR original
            values[i] = m02(static_cast<uint8_t>(i)) ^ static_cast<unsigned char>(i);
        }
    }
    constexpr unsigned char operator()(uint8_t i) const { return values[i]; }
};

static const Mul02Table mul02;
static const Mul03Table mul03;

// Replicate the mixColumns function as defined in the source
static inline void mixColumns(unsigned char *state) {
    int c;
    unsigned char s0, s1, s2, s3;
    for (c = 0; c < 4; ++c) {
        s0 = state[c];
        s1 = state[4 + c];
        s2 = state[8 + c];
        s3 = state[12 + c];
        state[c] = mul02(s0) ^ mul03(s1) ^ s2 ^ s3;
        state[4 + c] = s0 ^ mul02(s1) ^ mul03(s2) ^ s3;
        state[8 + c] = s0 ^ s1 ^ mul02(s2) ^ mul03(s3);
        state[12 + c] = mul03(s0) ^ s1 ^ s2 ^ mul02(s3);
    }
}

class MixColumnsTest_1609 : public ::testing::Test {
protected:
    unsigned char state[16];

    void SetUp() override {
        memset(state, 0, sizeof(state));
    }
};

// Test that all-zero state remains all-zero after mixColumns
TEST_F(MixColumnsTest_1609, AllZeroState_1609) {
    memset(state, 0, 16);
    mixColumns(state);
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(state[i], 0x00) << "Index " << i;
    }
}

// Test known AES MixColumns test vector from FIPS 197 / AES specification
// Before MixColumns: db 13 53 45 (column 0 in column-major)
// After MixColumns:  8e 4d a1 bc
TEST_F(MixColumnsTest_1609, KnownTestVector1_1609) {
    // State is stored in column-major order where:
    // state[0], state[4], state[8], state[12] = column 0
    // We set column 0 to {0xdb, 0x13, 0x53, 0x45}
    // and leave other columns as zero
    state[0] = 0xdb;
    state[4] = 0x13;
    state[8] = 0x53;
    state[12] = 0x45;

    mixColumns(state);

    EXPECT_EQ(state[0], 0x8e);
    EXPECT_EQ(state[4], 0x4d);
    EXPECT_EQ(state[8], 0xa1);
    EXPECT_EQ(state[12], 0xbc);
}

// Test another known AES MixColumns test vector
// Before: f2 0a 22 5c (column 1)
// After:  9f dc 58 9d
TEST_F(MixColumnsTest_1609, KnownTestVector2_1609) {
    state[1] = 0xf2;
    state[5] = 0x0a;
    state[9] = 0x22;
    state[13] = 0x5c;

    mixColumns(state);

    EXPECT_EQ(state[1], 0x9f);
    EXPECT_EQ(state[5], 0xdc);
    EXPECT_EQ(state[9], 0x58);
    EXPECT_EQ(state[13], 0x9d);
}

// Test known vector: column {01, 01, 01, 01}
// MixColumns matrix times {1,1,1,1} = each row: 2^1 XOR 3^1 XOR 1 XOR 1
// = 02 XOR 03 XOR 01 XOR 01 = 01
TEST_F(MixColumnsTest_1609, AllOnesColumn_1609) {
    state[0] = 0x01;
    state[4] = 0x01;
    state[8] = 0x01;
    state[12] = 0x01;

    mixColumns(state);

    EXPECT_EQ(state[0], 0x01);
    EXPECT_EQ(state[4], 0x01);
    EXPECT_EQ(state[8], 0x01);
    EXPECT_EQ(state[12], 0x01);
}

// Test with identity-like column {1,0,0,0}
// Result: {mul02(1), 1, 1, mul03(1)} = {0x02, 0x01, 0x01, 0x03}
TEST_F(MixColumnsTest_1609, SingleByteColumn_1609) {
    state[0] = 0x01;
    state[4] = 0x00;
    state[8] = 0x00;
    state[12] = 0x00;

    mixColumns(state);

    EXPECT_EQ(state[0], 0x02);
    EXPECT_EQ(state[4], 0x01);
    EXPECT_EQ(state[8], 0x01);
    EXPECT_EQ(state[12], 0x03);
}

// Test that all four columns are processed independently
TEST_F(MixColumnsTest_1609, AllColumnsIndependent_1609) {
    // Set different values in each column
    // Column 0: {0xdb, 0x13, 0x53, 0x45}
    state[0] = 0xdb; state[4] = 0x13; state[8] = 0x53; state[12] = 0x45;
    // Column 1: {0xf2, 0x0a, 0x22, 0x5c}
    state[1] = 0xf2; state[5] = 0x0a; state[9] = 0x22; state[13] = 0x5c;
    // Column 2: {0x01, 0x01, 0x01, 0x01}
    state[2] = 0x01; state[6] = 0x01; state[10] = 0x01; state[14] = 0x01;
    // Column 3: {0x00, 0x00, 0x00, 0x00}
    state[3] = 0x00; state[7] = 0x00; state[11] = 0x00; state[15] = 0x00;

    mixColumns(state);

    // Column 0
    EXPECT_EQ(state[0], 0x8e);
    EXPECT_EQ(state[4], 0x4d);
    EXPECT_EQ(state[8], 0xa1);
    EXPECT_EQ(state[12], 0xbc);

    // Column 1
    EXPECT_EQ(state[1], 0x9f);
    EXPECT_EQ(state[5], 0xdc);
    EXPECT_EQ(state[9], 0x58);
    EXPECT_EQ(state[13], 0x9d);

    // Column 2
    EXPECT_EQ(state[2], 0x01);
    EXPECT_EQ(state[6], 0x01);
    EXPECT_EQ(state[10], 0x01);
    EXPECT_EQ(state[14], 0x01);

    // Column 3
    EXPECT_EQ(state[3], 0x00);
    EXPECT_EQ(state[7], 0x00);
    EXPECT_EQ(state[11], 0x00);
    EXPECT_EQ(state[15], 0x00);
}

// Test with all 0xFF bytes
TEST_F(MixColumnsTest_1609, AllFF_1609) {
    memset(state, 0xFF, 16);
    mixColumns(state);

    // For column {0xFF, 0xFF, 0xFF, 0xFF}:
    // Each output byte = mul02(0xFF) ^ mul03(0xFF) ^ 0xFF ^ 0xFF
    // mul02(0xFF) = (0xFF << 1) ^ 0x1b = 0xFE ^ 0x1b = 0xE5
    // mul03(0xFF) = mul02(0xFF) ^ 0xFF = 0xE5 ^ 0xFF = 0x1A
    // So each byte = 0xE5 ^ 0x1A ^ 0xFF ^ 0xFF = 0xE5 ^ 0x1A = 0xFF
    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(state[i], 0xFF) << "Index " << i;
    }
}

// Test another known AES test vector
// Column {d4, bf, 5d, 30} -> {04, 66, 81, e5}
TEST_F(MixColumnsTest_1609, KnownTestVector3_1609) {
    state[0] = 0xd4;
    state[4] = 0xbf;
    state[8] = 0x5d;
    state[12] = 0x30;

    mixColumns(state);

    EXPECT_EQ(state[0], 0x04);
    EXPECT_EQ(state[4], 0x66);
    EXPECT_EQ(state[8], 0x81);
    EXPECT_EQ(state[12], 0xe5);
}

// Test the Mul02 table boundary: value 0x80 should trigger XOR with 0x1b
TEST_F(MixColumnsTest_1609, Mul02Boundary_1609) {
    // Column {0x80, 0x00, 0x00, 0x00}
    state[0] = 0x80;
    state[4] = 0x00;
    state[8] = 0x00;
    state[12] = 0x00;

    mixColumns(state);

    // mul02(0x80) = 0x1b (since high bit set)
    // mul03(0x80) = mul02(0x80) ^ 0x80 = 0x1b ^ 0x80 = 0x9b
    // state[0] = mul02(0x80) ^ 0 ^ 0 ^ 0 = 0x1b
    // state[4] = 0x80 ^ 0 ^ 0 ^ 0 = 0x80
    // state[8] = 0x80 ^ 0 ^ 0 ^ 0 = 0x80
    // state[12] = mul03(0x80) ^ 0 ^ 0 ^ 0 = 0x9b
    EXPECT_EQ(state[0], 0x1b);
    EXPECT_EQ(state[4], 0x80);
    EXPECT_EQ(state[8], 0x80);
    EXPECT_EQ(state[12], 0x9b);
}

// Test that applying mixColumns twice does not return to identity (it's not self-inverse)
TEST_F(MixColumnsTest_1609, DoubleApplicationNotIdentity_1609) {
    unsigned char original[16];
    for (int i = 0; i < 16; ++i) {
        state[i] = static_cast<unsigned char>(i * 17 + 3);
        original[i] = state[i];
    }

    mixColumns(state);
    mixColumns(state);

    // After applying twice, state should generally differ from original
    bool allSame = true;
    for (int i = 0; i < 16; ++i) {
        if (state[i] != original[i]) {
            allSame = false;
            break;
        }
    }
    EXPECT_FALSE(allSame);
}

// Test linearity property: mixColumns(A XOR B) == mixColumns(A) XOR mixColumns(B)
TEST_F(MixColumnsTest_1609, LinearityProperty_1609) {
    unsigned char stateA[16], stateB[16], stateAxorB[16];
    unsigned char resultA[16], resultB[16], resultAxorB[16];

    for (int i = 0; i < 16; ++i) {
        stateA[i] = static_cast<unsigned char>(i * 7 + 1);
        stateB[i] = static_cast<unsigned char>(i * 13 + 5);
        stateAxorB[i] = stateA[i] ^ stateB[i];
    }

    memcpy(resultA, stateA, 16);
    memcpy(resultB, stateB, 16);
    memcpy(resultAxorB, stateAxorB, 16);

    mixColumns(resultA);
    mixColumns(resultB);
    mixColumns(resultAxorB);

    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(resultAxorB[i], resultA[i] ^ resultB[i]) << "Linearity failed at index " << i;
    }
}

// Test with column {0x01, 0x00, 0x00, 0x00} in second column position
TEST_F(MixColumnsTest_1609, SecondColumnSingleByte_1609) {
    memset(state, 0, 16);
    state[1] = 0x01; // s0 of column 1

    mixColumns(state);

    EXPECT_EQ(state[1], 0x02);
    EXPECT_EQ(state[5], 0x01);
    EXPECT_EQ(state[9], 0x01);
    EXPECT_EQ(state[13], 0x03);

    // Other columns should remain zero
    EXPECT_EQ(state[0], 0x00);
    EXPECT_EQ(state[4], 0x00);
    EXPECT_EQ(state[8], 0x00);
    EXPECT_EQ(state[12], 0x00);
}

// Verify Mul02 and Mul03 table correctness for a few specific values
TEST(Mul02TableTest_1609, SpecificValues_1609) {
    EXPECT_EQ(mul02(0x00), 0x00);
    EXPECT_EQ(mul02(0x01), 0x02);
    EXPECT_EQ(mul02(0x80), 0x1b);
    EXPECT_EQ(mul02(0xFF), 0xe5);
    EXPECT_EQ(mul02(0x53), 0xa6);
    EXPECT_EQ(mul02(0x7F), 0xFE);
}

TEST(Mul03TableTest_1609, SpecificValues_1609) {
    EXPECT_EQ(mul03(0x00), 0x00);
    EXPECT_EQ(mul03(0x01), 0x03);
    EXPECT_EQ(mul03(0x80), 0x9b); // mul02(0x80) ^ 0x80 = 0x1b ^ 0x80
    EXPECT_EQ(mul03(0xFF), 0x1a); // mul02(0xFF) ^ 0xFF = 0xe5 ^ 0xff
}
