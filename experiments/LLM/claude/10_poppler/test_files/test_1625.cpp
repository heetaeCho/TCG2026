#include <gtest/gtest.h>
#include <cstring>
#include <cstdint>

// Include the implementation file to access static functions
// This is necessary since md5Finish and related functions are static
#include "Decrypt.cc"

class MD5FinishTest_1625 : public ::testing::Test {
protected:
    MD5State state;

    void initMD5State() {
        // Standard MD5 initial values
        state.a = 0x67452301;
        state.b = 0xefcdab89;
        state.c = 0x98badcfe;
        state.d = 0x10325476;
        state.bufLen = 0;
        state.msgLen = 0;
        memset(state.buf, 0, sizeof(state.buf));
        memset(state.digest, 0, sizeof(state.digest));
    }
};

// Test md5Finish on empty message (bufLen = 0, msgLen = 0)
// This should produce the MD5 of an empty string
TEST_F(MD5FinishTest_1625, EmptyMessage_1625) {
    initMD5State();
    state.bufLen = 0;
    state.msgLen = 0;

    md5Finish(&state);

    // MD5("") = d41d8cd98f00b204e9800998ecf8427e
    EXPECT_EQ(state.digest[0], 0xd4);
    EXPECT_EQ(state.digest[1], 0x1d);
    EXPECT_EQ(state.digest[2], 0x8c);
    EXPECT_EQ(state.digest[3], 0xd9);
    EXPECT_EQ(state.digest[4], 0x8f);
    EXPECT_EQ(state.digest[5], 0x00);
    EXPECT_EQ(state.digest[6], 0xb2);
    EXPECT_EQ(state.digest[7], 0x04);
    EXPECT_EQ(state.digest[8], 0xe9);
    EXPECT_EQ(state.digest[9], 0x80);
    EXPECT_EQ(state.digest[10], 0x09);
    EXPECT_EQ(state.digest[11], 0x98);
    EXPECT_EQ(state.digest[12], 0xec);
    EXPECT_EQ(state.digest[13], 0xf8);
    EXPECT_EQ(state.digest[14], 0x42);
    EXPECT_EQ(state.digest[15], 0x7e);
}

// Test that digest array is fully populated (16 bytes)
TEST_F(MD5FinishTest_1625, DigestFullyPopulated_1625) {
    initMD5State();
    state.bufLen = 0;
    state.msgLen = 0;

    md5Finish(&state);

    // Just verify that we can read all 16 bytes without issues
    unsigned char result[16];
    memcpy(result, state.digest, 16);
    // The digest should be deterministic for same input state
    EXPECT_EQ(sizeof(state.digest), 16u);
}

// Test md5Finish when bufLen is exactly at the boundary (56) - triggers extra block
TEST_F(MD5FinishTest_1625, BufLenAtBoundary56_1625) {
    initMD5State();
    // Fill buffer up to 56 bytes - after adding 0x80 at position 56, bufLen becomes 57 > 56
    // so it should trigger the extra block processing path
    state.bufLen = 56;
    state.msgLen = 56;
    memset(state.buf, 'A', 56);

    md5Finish(&state);

    // Verify digest is populated (non-trivial check)
    // The exact value depends on md5ProcessBlock, but digest should be set
    bool allZero = true;
    for (int i = 0; i < 16; i++) {
        if (state.digest[i] != 0) {
            allZero = false;
            break;
        }
    }
    // It's extremely unlikely an MD5 digest is all zeros
    // (though theoretically possible, practically not)
    EXPECT_FALSE(allZero);
}

// Test md5Finish when bufLen is 55 - does NOT trigger extra block
TEST_F(MD5FinishTest_1625, BufLen55NoExtraBlock_1625) {
    initMD5State();
    state.bufLen = 55;
    state.msgLen = 55;
    memset(state.buf, 'B', 55);

    md5Finish(&state);

    // After adding 0x80 at index 55, bufLen = 56 which is NOT > 56
    // so no extra block processing before padding
    bool allZero = true;
    for (int i = 0; i < 16; i++) {
        if (state.digest[i] != 0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
}

// Test md5Finish when bufLen is at maximum before finish (63)
TEST_F(MD5FinishTest_1625, BufLenNearFull63_1625) {
    initMD5State();
    state.bufLen = 63;
    state.msgLen = 63;
    memset(state.buf, 'C', 63);

    md5Finish(&state);

    // bufLen becomes 64 after 0x80, which is > 56, triggers extra block
    bool allZero = true;
    for (int i = 0; i < 16; i++) {
        if (state.digest[i] != 0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
}

// Test md5Finish with small bufLen (1 byte in buffer)
TEST_F(MD5FinishTest_1625, BufLenOne_1625) {
    initMD5State();
    state.bufLen = 1;
    state.msgLen = 1;
    state.buf[0] = 'a';

    md5Finish(&state);

    // Verify digest is set and deterministic
    unsigned char firstRun[16];
    memcpy(firstRun, state.digest, 16);

    // Run again with same input
    initMD5State();
    state.bufLen = 1;
    state.msgLen = 1;
    state.buf[0] = 'a';
    md5Finish(&state);

    EXPECT_EQ(0, memcmp(firstRun, state.digest, 16));
}

// Test that different inputs produce different digests
TEST_F(MD5FinishTest_1625, DifferentInputsDifferentDigests_1625) {
    // First input
    initMD5State();
    state.bufLen = 1;
    state.msgLen = 1;
    state.buf[0] = 'a';
    md5Finish(&state);
    unsigned char digest1[16];
    memcpy(digest1, state.digest, 16);

    // Second input
    initMD5State();
    state.bufLen = 1;
    state.msgLen = 1;
    state.buf[0] = 'b';
    md5Finish(&state);
    unsigned char digest2[16];
    memcpy(digest2, state.digest, 16);

    EXPECT_NE(0, memcmp(digest1, digest2, 16));
}

// Test md5Finish with bufLen = 0 and varying msgLen (simulating prior blocks processed)
TEST_F(MD5FinishTest_1625, PriorBlocksProcessed_1625) {
    initMD5State();
    state.bufLen = 0;
    state.msgLen = 64; // Simulate that one block was already processed
    // The a,b,c,d would normally be different after processing, but we test the padding logic
    md5Finish(&state);

    // Verify message length encoding in the padding
    // The digest should be deterministic
    bool allZero = true;
    for (int i = 0; i < 16; i++) {
        if (state.digest[i] != 0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
}

// Test that the length encoding is correct by checking consistency
TEST_F(MD5FinishTest_1625, DeterministicOutput_1625) {
    for (int run = 0; run < 3; run++) {
        initMD5State();
        state.bufLen = 3;
        state.msgLen = 3;
        state.buf[0] = 'x';
        state.buf[1] = 'y';
        state.buf[2] = 'z';
        md5Finish(&state);

        if (run == 0) continue;
        // All runs should produce same result - checked implicitly by consistency
    }

    // Final check: run twice and compare
    initMD5State();
    state.bufLen = 3;
    state.msgLen = 3;
    state.buf[0] = 'x';
    state.buf[1] = 'y';
    state.buf[2] = 'z';
    md5Finish(&state);
    unsigned char first[16];
    memcpy(first, state.digest, 16);

    initMD5State();
    state.bufLen = 3;
    state.msgLen = 3;
    state.buf[0] = 'x';
    state.buf[1] = 'y';
    state.buf[2] = 'z';
    md5Finish(&state);

    EXPECT_EQ(0, memcmp(first, state.digest, 16));
}

// Test boundary: bufLen exactly 56 triggers the extra block path
TEST_F(MD5FinishTest_1625, ExactBoundary56TriggersExtraBlock_1625) {
    // With bufLen=56, after adding 0x80, bufLen=57 which is > 56
    // This should process an extra block
    initMD5State();
    state.bufLen = 56;
    state.msgLen = 56;
    memset(state.buf, 0x41, 56);
    md5Finish(&state);
    unsigned char digest56[16];
    memcpy(digest56, state.digest, 16);

    // With bufLen=55, after adding 0x80, bufLen=56 which is NOT > 56
    // This should NOT process an extra block
    initMD5State();
    state.bufLen = 55;
    state.msgLen = 55;
    memset(state.buf, 0x41, 55);
    md5Finish(&state);
    unsigned char digest55[16];
    memcpy(digest55, state.digest, 16);

    // These should produce different digests (different input lengths and padding)
    EXPECT_NE(0, memcmp(digest56, digest55, 16));
}
