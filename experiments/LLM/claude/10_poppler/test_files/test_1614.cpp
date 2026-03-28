#include <gtest/gtest.h>
#include <cstring>
#include <cstdint>

// We need to access the static function, so we include the .cc file
// First, include necessary headers that Decrypt.cc would need
#include "poppler/Decrypt.h"

// Include the implementation to access static functions
#include "poppler/Decrypt.cc"

class Aes256KeyExpansionTest_1614 : public ::testing::Test {
protected:
    DecryptAES256State state;
    
    void SetUp() override {
        memset(&state, 0, sizeof(state));
    }
};

// Test that key expansion with a zero key produces non-zero expanded key words
TEST_F(Aes256KeyExpansionTest_1614, ZeroKeyEncrypt_1614) {
    unsigned char key[32];
    memset(key, 0, sizeof(key));
    
    aes256KeyExpansion(&state, key, false);
    
    // First 8 words should be zero (derived directly from zero key)
    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(state.w[i], 0u);
    }
    
    // The expanded schedule should have some non-zero values due to rcon
    bool hasNonZero = false;
    for (int i = 8; i < 60; ++i) {
        if (state.w[i] != 0) {
            hasNonZero = true;
            break;
        }
    }
    EXPECT_TRUE(hasNonZero);
}

// Test that key expansion correctly loads the first 8 words from the key
TEST_F(Aes256KeyExpansionTest_1614, KeyLoadedCorrectly_1614) {
    unsigned char key[32];
    for (int i = 0; i < 32; ++i) {
        key[i] = static_cast<unsigned char>(i);
    }
    
    aes256KeyExpansion(&state, key, false);
    
    // Verify first 8 words are correctly constructed from key bytes
    for (int i = 0; i < 8; ++i) {
        unsigned int expected = (key[4*i] << 24) | (key[4*i+1] << 16) | (key[4*i+2] << 8) | key[4*i+3];
        EXPECT_EQ(state.w[i], expected) << "Mismatch at word " << i;
    }
}

// Test that encryption and decryption key schedules differ
TEST_F(Aes256KeyExpansionTest_1614, EncryptDecryptDiffer_1614) {
    unsigned char key[32];
    for (int i = 0; i < 32; ++i) {
        key[i] = static_cast<unsigned char>(i + 0x10);
    }
    
    DecryptAES256State encState, decState;
    aes256KeyExpansion(&encState, key, false);
    aes256KeyExpansion(&decState, key, true);
    
    // First 4 words (round 0) should be the same
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(encState.w[i], decState.w[i]);
    }
    
    // Last 4 words (round 14) should be the same
    for (int i = 56; i < 60; ++i) {
        EXPECT_EQ(encState.w[i], decState.w[i]);
    }
    
    // Middle rounds (1-13) should differ due to invMixColumns
    bool anyDifference = false;
    for (int round = 1; round <= 13; ++round) {
        for (int j = 0; j < 4; ++j) {
            if (encState.w[round * 4 + j] != decState.w[round * 4 + j]) {
                anyDifference = true;
                break;
            }
        }
        if (anyDifference) break;
    }
    EXPECT_TRUE(anyDifference);
}

// Test that the same key produces the same expansion (deterministic)
TEST_F(Aes256KeyExpansionTest_1614, DeterministicExpansion_1614) {
    unsigned char key[32];
    for (int i = 0; i < 32; ++i) {
        key[i] = static_cast<unsigned char>(0xAB ^ i);
    }
    
    DecryptAES256State state1, state2;
    aes256KeyExpansion(&state1, key, false);
    aes256KeyExpansion(&state2, key, false);
    
    for (int i = 0; i < 60; ++i) {
        EXPECT_EQ(state1.w[i], state2.w[i]) << "Mismatch at index " << i;
    }
}

// Test with all-0xFF key
TEST_F(Aes256KeyExpansionTest_1614, AllOnesKey_1614) {
    unsigned char key[32];
    memset(key, 0xFF, sizeof(key));
    
    aes256KeyExpansion(&state, key, false);
    
    // First 8 words should all be 0xFFFFFFFF
    for (int i = 0; i < 8; ++i) {
        EXPECT_EQ(state.w[i], 0xFFFFFFFFu);
    }
    
    // All 60 words should be populated
    // Just verify the expansion completed by checking total word count is accessible
    // Word at index 59 should be set
    // (We can't predict the exact value without reimplementing, but it should be deterministic)
    DecryptAES256State state2;
    memset(key, 0xFF, sizeof(key));
    aes256KeyExpansion(&state2, key, false);
    EXPECT_EQ(state.w[59], state2.w[59]);
}

// Test different keys produce different expansions
TEST_F(Aes256KeyExpansionTest_1614, DifferentKeysProduceDifferentSchedules_1614) {
    unsigned char key1[32], key2[32];
    memset(key1, 0x00, sizeof(key1));
    memset(key2, 0x01, sizeof(key2));
    
    DecryptAES256State state1, state2;
    aes256KeyExpansion(&state1, key1, false);
    aes256KeyExpansion(&state2, key2, false);
    
    bool anyDifference = false;
    for (int i = 0; i < 60; ++i) {
        if (state1.w[i] != state2.w[i]) {
            anyDifference = true;
            break;
        }
    }
    EXPECT_TRUE(anyDifference);
}

// Test that decrypt mode invMixColumns modifies rounds 1-13 but not round 0 and round 14
TEST_F(Aes256KeyExpansionTest_1614, DecryptModePreservesFirstAndLastRound_1614) {
    unsigned char key[32];
    for (int i = 0; i < 32; ++i) {
        key[i] = static_cast<unsigned char>(i * 7 + 3);
    }
    
    DecryptAES256State encState, decState;
    aes256KeyExpansion(&encState, key, false);
    aes256KeyExpansion(&decState, key, true);
    
    // Round 0 (words 0-3) should be identical
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(encState.w[i], decState.w[i]) << "Round 0, word " << i;
    }
    
    // Round 14 (words 56-59) should be identical
    for (int i = 56; i < 60; ++i) {
        EXPECT_EQ(encState.w[i], decState.w[i]) << "Round 14, word " << i;
    }
}

// Test with a known key pattern - single bit set
TEST_F(Aes256KeyExpansionTest_1614, SingleBitKey_1614) {
    unsigned char key[32];
    memset(key, 0, sizeof(key));
    key[0] = 0x80; // Only MSB of first byte set
    
    aes256KeyExpansion(&state, key, false);
    
    // First word should have the MSB set
    EXPECT_EQ(state.w[0], 0x80000000u);
    
    // Words 1-7 should be zero
    for (int i = 1; i < 8; ++i) {
        EXPECT_EQ(state.w[i], 0u);
    }
}
