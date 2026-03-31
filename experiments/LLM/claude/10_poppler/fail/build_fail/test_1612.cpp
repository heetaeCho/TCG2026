#include <gtest/gtest.h>
#include <cstring>

// Include the .cc file to access static functions
#include "Decrypt.cc"

class AesEncryptBlockTest_1612 : public ::testing::Test {
protected:
    DecryptAESState state;
    
    void SetUp() override {
        memset(&state, 0, sizeof(state));
    }
    
    void initializeKnownKey(const unsigned char key[16]) {
        // Expand the key into state.w using AES key expansion
        // We use aesKeyExpansion if available, otherwise set w manually
        aesKeyExpansion(&state, key, 16, false);
    }
};

// Test that bufIdx is set to 0 after encryption
TEST_F(AesEncryptBlockTest_1612, BufIdxResetToZero_1612) {
    unsigned char key[16] = {0};
    initializeKnownKey(key);
    
    state.bufIdx = 10; // Set to non-zero
    unsigned char in[16] = {0};
    
    aesEncryptBlock(&state, in);
    
    EXPECT_EQ(state.bufIdx, 0);
}

// Test that buf is modified after encryption
TEST_F(AesEncryptBlockTest_1612, BufIsModifiedAfterEncryption_1612) {
    unsigned char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                              0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    initializeKnownKey(key);
    
    memset(state.buf, 0, 16);
    unsigned char in[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                             0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    
    unsigned char bufBefore[16];
    memcpy(bufBefore, state.buf, 16);
    
    aesEncryptBlock(&state, in);
    
    // buf should have changed (encryption output is non-trivial)
    EXPECT_NE(memcmp(state.buf, bufBefore, 16), 0);
}

// Test with all-zero key and all-zero input (known AES test vector)
TEST_F(AesEncryptBlockTest_1612, KnownVectorAllZeros_1612) {
    unsigned char key[16] = {0};
    initializeKnownKey(key);
    memset(state.buf, 0, 16); // IV of zeros
    
    unsigned char in[16] = {0}; // plaintext of zeros
    // After XOR with zero buf, the AES input is all zeros
    // AES-128 encrypt of all-zero plaintext with all-zero key:
    // Expected: 66 e9 4b d4 ef 8a 2c 3b 88 4c fa 59 ca 34 2b 2e
    unsigned char expected[16] = {0x66, 0xe9, 0x4b, 0xd4, 0xef, 0x8a, 0x2c, 0x3b,
                                   0x88, 0x4c, 0xfa, 0x59, 0xca, 0x34, 0x2b, 0x2e};
    
    aesEncryptBlock(&state, in);
    
    EXPECT_EQ(memcmp(state.buf, expected, 16), 0);
}

// Test CBC chaining: encrypting twice should produce different outputs
TEST_F(AesEncryptBlockTest_1612, CBCChainingEffect_1612) {
    unsigned char key[16] = {0};
    initializeKnownKey(key);
    memset(state.buf, 0, 16);
    
    unsigned char in[16] = {0};
    
    aesEncryptBlock(&state, in);
    unsigned char firstOutput[16];
    memcpy(firstOutput, state.buf, 16);
    
    // Encrypt same plaintext again; buf now holds previous ciphertext (CBC mode)
    aesEncryptBlock(&state, in);
    unsigned char secondOutput[16];
    memcpy(secondOutput, state.buf, 16);
    
    // Due to CBC, outputs should differ
    EXPECT_NE(memcmp(firstOutput, secondOutput, 16), 0);
}

// Test that state array is used as intermediate (not leaked as final output directly)
TEST_F(AesEncryptBlockTest_1612, StateArrayUsedAsIntermediate_1612) {
    unsigned char key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                              0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    initializeKnownKey(key);
    memset(state.buf, 0, 16);
    
    unsigned char in[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d,
                             0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    
    aesEncryptBlock(&state, in);
    
    // bufIdx should be 0
    EXPECT_EQ(state.bufIdx, 0);
    
    // buf should contain the encryption result (non-zero for this input)
    bool allZero = true;
    for (int i = 0; i < 16; i++) {
        if (state.buf[i] != 0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
}

// NIST AES-128 known test vector
TEST_F(AesEncryptBlockTest_1612, NISTKnownTestVector_1612) {
    unsigned char key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                              0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    initializeKnownKey(key);
    memset(state.buf, 0, 16); // zero IV so XOR doesn't change plaintext
    
    unsigned char in[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d,
                             0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    
    // NIST expected output for this key/plaintext pair:
    // 39 25 84 1d 02 dc 09 fb dc 11 85 97 19 6a 0b 32
    unsigned char expected[16] = {0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb,
                                   0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32};
    
    aesEncryptBlock(&state, in);
    
    EXPECT_EQ(memcmp(state.buf, expected, 16), 0);
}

// Test determinism: same inputs produce same output
TEST_F(AesEncryptBlockTest_1612, Deterministic_1612) {
    unsigned char key[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                              0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
    unsigned char in[16] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11,
                             0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99};
    
    initializeKnownKey(key);
    memset(state.buf, 0, 16);
    aesEncryptBlock(&state, in);
    unsigned char result1[16];
    memcpy(result1, state.buf, 16);
    
    // Reset and encrypt again
    initializeKnownKey(key);
    memset(state.buf, 0, 16);
    aesEncryptBlock(&state, in);
    unsigned char result2[16];
    memcpy(result2, state.buf, 16);
    
    EXPECT_EQ(memcmp(result1, result2, 16), 0);
}
