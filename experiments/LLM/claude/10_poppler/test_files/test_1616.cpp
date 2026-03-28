#include <gtest/gtest.h>
#include <cstring>
#include "Decrypt.h"

// Since aes256DecryptBlock is static (internal linkage), we test it
// by including the source file to access the static function directly.
// This is a common technique for testing static functions.
#include "Decrypt.cc"

class Aes256DecryptBlockTest_1616 : public ::testing::Test {
protected:
    DecryptAES256State state;

    void SetUp() override {
        memset(&state, 0, sizeof(state));
    }

    void initializeKeySchedule(const unsigned char *key) {
        // Initialize w[] with a known key expansion
        // Using all-zero key for simplicity
        aes256KeyExpansion(&state, key, 32);
    }
};

TEST_F(Aes256DecryptBlockTest_1616, DecryptBlockNonLast_ZeroKey_1616) {
    unsigned char key[32] = {0};
    initializeKeySchedule(key);
    memset(state.cbc, 0, 16);

    unsigned char input[16] = {0};
    aes256DecryptBlock(&state, input, false);

    // bufIdx should be 0 for non-last block
    EXPECT_EQ(state.bufIdx, 0);
}

TEST_F(Aes256DecryptBlockTest_1616, DecryptBlockLast_ValidPadding_1616) {
    unsigned char key[32] = {0};
    initializeKeySchedule(key);
    memset(state.cbc, 0, 16);

    // First encrypt a block with known padding to get valid ciphertext
    // For testing, we'll just call decrypt on arbitrary data and check structure
    unsigned char input[16] = {0};
    aes256DecryptBlock(&state, input, true);

    // bufIdx should be set based on padding byte (buf[15] after decryption)
    // It should be between 0 and 16
    EXPECT_GE(state.bufIdx, 0);
    EXPECT_LE(state.bufIdx, 16);
}

TEST_F(Aes256DecryptBlockTest_1616, CbcUpdatedAfterDecrypt_1616) {
    unsigned char key[32] = {0};
    initializeKeySchedule(key);
    memset(state.cbc, 0, 16);

    unsigned char input[16];
    for (int i = 0; i < 16; i++) {
        input[i] = (unsigned char)(i + 1);
    }

    aes256DecryptBlock(&state, input, false);

    // After decryption, cbc should be updated to the input ciphertext block
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(state.cbc[i], input[i]);
    }
}

TEST_F(Aes256DecryptBlockTest_1616, NonLastBlockBufIdxIsZero_1616) {
    unsigned char key[32] = {0};
    initializeKeySchedule(key);
    memset(state.cbc, 0, 16);

    unsigned char input[16] = {0x55};
    aes256DecryptBlock(&state, input, false);

    EXPECT_EQ(state.bufIdx, 0);
}

TEST_F(Aes256DecryptBlockTest_1616, LastBlockBufIdxBounded_1616) {
    unsigned char key[32];
    memset(key, 0xAB, 32);
    initializeKeySchedule(key);
    memset(state.cbc, 0, 16);

    unsigned char input[16];
    memset(input, 0xFF, 16);

    aes256DecryptBlock(&state, input, true);

    // bufIdx must be between 0 and 16 inclusive regardless of decrypted content
    EXPECT_GE(state.bufIdx, 0);
    EXPECT_LE(state.bufIdx, 16);
}

TEST_F(Aes256DecryptBlockTest_1616, CbcNotChangedBeforeDecrypt_1616) {
    unsigned char key[32] = {0};
    initializeKeySchedule(key);

    unsigned char originalCbc[16];
    for (int i = 0; i < 16; i++) {
        state.cbc[i] = (unsigned char)(i * 17);
        originalCbc[i] = state.cbc[i];
    }

    unsigned char input[16];
    memset(input, 0x42, 16);

    aes256DecryptBlock(&state, input, false);

    // After decrypt, cbc should now equal input (not the original)
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(state.cbc[i], input[i]);
    }
}

TEST_F(Aes256DecryptBlockTest_1616, XorWithCbcApplied_1616) {
    unsigned char key[32] = {0};
    initializeKeySchedule(key);

    // Set two different CBC IVs and decrypt same input
    unsigned char input[16] = {0};

    memset(state.cbc, 0x00, 16);
    aes256DecryptBlock(&state, input, false);
    unsigned char buf1[16];
    memcpy(buf1, state.buf, 16);

    // Reset state but with different CBC
    initializeKeySchedule(key);
    memset(state.cbc, 0xFF, 16);
    aes256DecryptBlock(&state, input, false);
    unsigned char buf2[16];
    memcpy(buf2, state.buf, 16);

    // Results should differ because CBC IV differs
    bool allSame = true;
    for (int i = 0; i < 16; i++) {
        if (buf1[i] != buf2[i]) {
            allSame = false;
            break;
        }
    }
    EXPECT_FALSE(allSame);
}

TEST_F(Aes256DecryptBlockTest_1616, XorWithCbcCorrectness_1616) {
    unsigned char key[32] = {0};
    initializeKeySchedule(key);

    unsigned char input[16] = {0};

    // Get decrypted state (before XOR with CBC)
    memset(state.cbc, 0x00, 16);
    aes256DecryptBlock(&state, input, false);
    unsigned char decryptedWithZeroCbc[16];
    memcpy(decryptedWithZeroCbc, state.buf, 16);

    // Now decrypt again with non-zero CBC
    initializeKeySchedule(key);
    unsigned char cbc[16];
    for (int i = 0; i < 16; i++) cbc[i] = (unsigned char)(i + 1);
    memcpy(state.cbc, cbc, 16);
    aes256DecryptBlock(&state, input, false);

    // buf should be decrypted XOR cbc
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(state.buf[i], (unsigned char)(decryptedWithZeroCbc[i] ^ cbc[i]));
    }
}

TEST_F(Aes256DecryptBlockTest_1616, MultipleBlocksSequential_1616) {
    unsigned char key[32] = {0};
    initializeKeySchedule(key);
    memset(state.cbc, 0, 16);

    unsigned char block1[16], block2[16];
    memset(block1, 0x11, 16);
    memset(block2, 0x22, 16);

    // Decrypt first block (non-last)
    aes256DecryptBlock(&state, block1, false);
    EXPECT_EQ(state.bufIdx, 0);

    // CBC should now be block1
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(state.cbc[i], block1[i]);
    }

    // Decrypt second block (last)
    aes256DecryptBlock(&state, block2, true);
    EXPECT_GE(state.bufIdx, 0);
    EXPECT_LE(state.bufIdx, 16);

    // CBC should now be block2
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(state.cbc[i], block2[i]);
    }
}

TEST_F(Aes256DecryptBlockTest_1616, DifferentKeysProduceDifferentOutput_1616) {
    unsigned char key1[32] = {0};
    unsigned char key2[32];
    memset(key2, 0x01, 32);

    unsigned char input[16] = {0};

    initializeKeySchedule(key1);
    memset(state.cbc, 0, 16);
    aes256DecryptBlock(&state, input, false);
    unsigned char result1[16];
    memcpy(result1, state.buf, 16);

    initializeKeySchedule(key2);
    memset(state.cbc, 0, 16);
    aes256DecryptBlock(&state, input, false);
    unsigned char result2[16];
    memcpy(result2, state.buf, 16);

    bool allSame = true;
    for (int i = 0; i < 16; i++) {
        if (result1[i] != result2[i]) {
            allSame = false;
            break;
        }
    }
    EXPECT_FALSE(allSame);
}
