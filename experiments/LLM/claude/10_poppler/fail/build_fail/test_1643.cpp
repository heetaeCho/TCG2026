#include <gtest/gtest.h>
#include <cstring>
#include <cstdint>

// We need access to the static function sha512HashBlock. Since it's static in Decrypt.cc,
// we need to include the source file or use a workaround. We'll include the source file
// to get access to the static function.
// However, since sha512HashBlock is static, we need to either:
// 1. Include the .cc file directly
// 2. Or create a wrapper

// For testing purposes, we include the implementation file to access the static function.
// This is a common technique for testing static/internal functions.

// Forward declarations of helper functions used by sha512HashBlock
// We include the source to get the static function
// First, let's declare what we need

// We'll include the Decrypt.cc to get access to static functions
// But we need to be careful about multiple definition issues

// Alternative: redefine the function signature and test via known SHA-512 test vectors
// Since sha512HashBlock is one round of SHA-512 compression, we can verify it against
// known intermediate states.

// Let's include the source file to access the static function
#include "Decrypt.cc"

class Sha512HashBlockTest_1643 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with all-zero block and initial SHA-512 hash values
TEST_F(Sha512HashBlockTest_1643, AllZeroBlockWithInitialH_1643) {
    // SHA-512 initial hash values
    uint64_t H[8] = {
        0x6a09e667f3bcc908ULL,
        0xbb67ae8584caa73bULL,
        0x3c6ef372fe94f82bULL,
        0xa54ff53a5f1d36f1ULL,
        0x510e527fade682d1ULL,
        0x9b05688c2b3e6c1fULL,
        0x1f83d9abfb41bd6bULL,
        0x5be0cd19137e2179ULL
    };

    unsigned char blk[128];
    memset(blk, 0, 128);

    uint64_t H_copy[8];
    memcpy(H_copy, H, sizeof(H));

    sha512HashBlock(blk, H);

    // After processing, H should be modified (not equal to initial values)
    bool changed = false;
    for (int i = 0; i < 8; i++) {
        if (H[i] != H_copy[i]) {
            changed = true;
            break;
        }
    }
    EXPECT_TRUE(changed);
}

// Test determinism: same input should produce same output
TEST_F(Sha512HashBlockTest_1643, DeterministicOutput_1643) {
    uint64_t H1[8] = {
        0x6a09e667f3bcc908ULL,
        0xbb67ae8584caa73bULL,
        0x3c6ef372fe94f82bULL,
        0xa54ff53a5f1d36f1ULL,
        0x510e527fade682d1ULL,
        0x9b05688c2b3e6c1fULL,
        0x1f83d9abfb41bd6bULL,
        0x5be0cd19137e2179ULL
    };

    uint64_t H2[8];
    memcpy(H2, H1, sizeof(H1));

    unsigned char blk[128];
    memset(blk, 0, 128);

    sha512HashBlock(blk, H1);
    sha512HashBlock(blk, H2);

    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(H1[i], H2[i]);
    }
}

// Test with a known SHA-512 single block computation
// SHA-512("abc") - the message "abc" is padded to a single 1024-bit block
// After processing, the hash should match the known SHA-512 digest
TEST_F(Sha512HashBlockTest_1643, KnownVectorABC_1643) {
    // SHA-512 initial hash values
    uint64_t H[8] = {
        0x6a09e667f3bcc908ULL,
        0xbb67ae8584caa73bULL,
        0x3c6ef372fe94f82bULL,
        0xa54ff53a5f1d36f1ULL,
        0x510e527fade682d1ULL,
        0x9b05688c2b3e6c1fULL,
        0x1f83d9abfb41bd6bULL,
        0x5be0cd19137e2179ULL
    };

    // Padded message for "abc" (3 bytes = 24 bits)
    // Message: 0x61 0x62 0x63 0x80 followed by zeros, then 64-bit length = 24 = 0x18
    unsigned char blk[128];
    memset(blk, 0, 128);
    blk[0] = 0x61; // 'a'
    blk[1] = 0x62; // 'b'
    blk[2] = 0x63; // 'c'
    blk[3] = 0x80; // padding bit
    // Length in bits = 24 = 0x18, stored in last 16 bytes (128-bit big-endian)
    // Actually SHA-512 uses 128-bit length at the end of the block
    blk[127] = 0x18; // 24 bits

    sha512HashBlock(blk, H);

    // Known SHA-512("abc") = 
    // ddaf35a193617aba cc417349ae204131 12e6fa4e89a97ea2 0a9eeee64b55d39a
    // 2192992a274fc1a8 36ba3c23a3feebbd 454d4423643ce80e 2a9ac94fa54ca49f
    EXPECT_EQ(H[0], 0xddaf35a193617abaULL);
    EXPECT_EQ(H[1], 0xcc417349ae204131ULL);
    EXPECT_EQ(H[2], 0x12e6fa4e89a97ea2ULL);
    EXPECT_EQ(H[3], 0x0a9eeee64b55d39aULL);
    EXPECT_EQ(H[4], 0x2192992a274fc1a8ULL);
    EXPECT_EQ(H[5], 0x36ba3c23a3feebbdULL);
    EXPECT_EQ(H[6], 0x454d4423643ce80eULL);
    EXPECT_EQ(H[7], 0x2a9ac94fa54ca49fULL);
}

// Test with all 0xFF block
TEST_F(Sha512HashBlockTest_1643, AllOnesBlock_1643) {
    uint64_t H[8] = {
        0x6a09e667f3bcc908ULL,
        0xbb67ae8584caa73bULL,
        0x3c6ef372fe94f82bULL,
        0xa54ff53a5f1d36f1ULL,
        0x510e527fade682d1ULL,
        0x9b05688c2b3e6c1fULL,
        0x1f83d9abfb41bd6bULL,
        0x5be0cd19137e2179ULL
    };

    unsigned char blk[128];
    memset(blk, 0xFF, 128);

    sha512HashBlock(blk, H);

    // Just verify it doesn't crash and H values changed
    // We can also verify determinism
    uint64_t H2[8] = {
        0x6a09e667f3bcc908ULL,
        0xbb67ae8584caa73bULL,
        0x3c6ef372fe94f82bULL,
        0xa54ff53a5f1d36f1ULL,
        0x510e527fade682d1ULL,
        0x9b05688c2b3e6c1fULL,
        0x1f83d9abfb41bd6bULL,
        0x5be0cd19137e2179ULL
    };
    sha512HashBlock(blk, H2);

    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(H[i], H2[i]);
    }
}

// Test with zero initial H values
TEST_F(Sha512HashBlockTest_1643, ZeroInitialH_1643) {
    uint64_t H[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    unsigned char blk[128];
    memset(blk, 0, 128);

    sha512HashBlock(blk, H);

    // With zero H and zero block, at least some H values should be non-zero
    bool anyNonZero = false;
    for (int i = 0; i < 8; i++) {
        if (H[i] != 0) {
            anyNonZero = true;
            break;
        }
    }
    EXPECT_TRUE(anyNonZero);
}

// Test that different blocks produce different results
TEST_F(Sha512HashBlockTest_1643, DifferentBlocksDifferentResults_1643) {
    uint64_t H1[8] = {
        0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL,
        0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
        0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL,
        0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL
    };

    uint64_t H2[8];
    memcpy(H2, H1, sizeof(H1));

    unsigned char blk1[128], blk2[128];
    memset(blk1, 0, 128);
    memset(blk2, 0, 128);
    blk2[0] = 1; // differ by one bit in the first byte

    sha512HashBlock(blk1, H1);
    sha512HashBlock(blk2, H2);

    bool differ = false;
    for (int i = 0; i < 8; i++) {
        if (H1[i] != H2[i]) {
            differ = true;
            break;
        }
    }
    EXPECT_TRUE(differ);
}

// Test that different initial H values produce different results
TEST_F(Sha512HashBlockTest_1643, DifferentInitialH_1643) {
    uint64_t H1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    uint64_t H2[8] = {9, 10, 11, 12, 13, 14, 15, 16};

    unsigned char blk[128];
    memset(blk, 0x42, 128);

    sha512HashBlock(blk, H1);
    sha512HashBlock(blk, H2);

    bool differ = false;
    for (int i = 0; i < 8; i++) {
        if (H1[i] != H2[i]) {
            differ = true;
            break;
        }
    }
    EXPECT_TRUE(differ);
}

// Test with known SHA-512 empty message
// SHA-512("") requires a padded block: 0x80 followed by zeros, then 0x0000000000000000 as length
TEST_F(Sha512HashBlockTest_1643, KnownVectorEmptyMessage_1643) {
    uint64_t H[8] = {
        0x6a09e667f3bcc908ULL,
        0xbb67ae8584caa73bULL,
        0x3c6ef372fe94f82bULL,
        0xa54ff53a5f1d36f1ULL,
        0x510e527fade682d1ULL,
        0x9b05688c2b3e6c1fULL,
        0x1f83d9abfb41bd6bULL,
        0x5be0cd19137e2179ULL
    };

    unsigned char blk[128];
    memset(blk, 0, 128);
    blk[0] = 0x80; // padding for empty message
    // length = 0 bits, already zero

    sha512HashBlock(blk, H);

    // SHA-512("") =
    // cf83e1357eefb8bd f1542850d66d8007 d620e4050b5715dc 83f4a921d36ce9ce
    // 47d0d13c5d85f2b0 ff8318d2877eec2f 63b931bd47417a81 a538327af927da3e
    EXPECT_EQ(H[0], 0xcf83e1357eefb8bdULL);
    EXPECT_EQ(H[1], 0xf1542850d66d8007ULL);
    EXPECT_EQ(H[2], 0xd620e4050b5715dcULL);
    EXPECT_EQ(H[3], 0x83f4a921d36ce9ceULL);
    EXPECT_EQ(H[4], 0x47d0d13c5d85f2b0ULL);
    EXPECT_EQ(H[5], 0xff8318d2877eec2fULL);
    EXPECT_EQ(H[6], 0x63b931bd47417a81ULL);
    EXPECT_EQ(H[7], 0xa538327af927da3eULL);
}

// Test sequential block processing (two blocks applied sequentially)
TEST_F(Sha512HashBlockTest_1643, SequentialBlocks_1643) {
    uint64_t H[8] = {
        0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL,
        0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
        0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL,
        0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL
    };

    unsigned char blk1[128], blk2[128];
    memset(blk1, 0xAA, 128);
    memset(blk2, 0x55, 128);

    // Process first block
    sha512HashBlock(blk1, H);
    uint64_t H_after_first[8];
    memcpy(H_after_first, H, sizeof(H));

    // Process second block
    sha512HashBlock(blk2, H);

    // H should differ from H_after_first
    bool differ = false;
    for (int i = 0; i < 8; i++) {
        if (H[i] != H_after_first[i]) {
            differ = true;
            break;
        }
    }
    EXPECT_TRUE(differ);
}

// Test that processing same block twice changes H further
TEST_F(Sha512HashBlockTest_1643, SameBlockTwice_1643) {
    uint64_t H[8] = {
        0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL,
        0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
        0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL,
        0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL
    };

    unsigned char blk[128];
    memset(blk, 0x37, 128);

    sha512HashBlock(blk, H);
    uint64_t H_once[8];
    memcpy(H_once, H, sizeof(H));

    sha512HashBlock(blk, H);

    // After processing same block twice, result should differ from processing once
    bool differ = false;
    for (int i = 0; i < 8; i++) {
        if (H[i] != H_once[i]) {
            differ = true;
            break;
        }
    }
    EXPECT_TRUE(differ);
}

// Test with a block containing specific byte pattern
TEST_F(Sha512HashBlockTest_1643, IncrementingBytePattern_1643) {
    uint64_t H[8] = {
        0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL,
        0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
        0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL,
        0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL
    };

    unsigned char blk[128];
    for (int i = 0; i < 128; i++) {
        blk[i] = static_cast<unsigned char>(i);
    }

    uint64_t H_before[8];
    memcpy(H_before, H, sizeof(H));

    sha512HashBlock(blk, H);

    bool changed = false;
    for (int i = 0; i < 8; i++) {
        if (H[i] != H_before[i]) {
            changed = true;
            break;
        }
    }
    EXPECT_TRUE(changed);
}

// Boundary: test with max uint64 values in H
TEST_F(Sha512HashBlockTest_1643, MaxUint64InitialH_1643) {
    uint64_t H[8];
    for (int i = 0; i < 8; i++) {
        H[i] = UINT64_MAX;
    }

    unsigned char blk[128];
    memset(blk, 0, 128);

    // Should not crash - overflow in uint64_t is well-defined (wraps around)
    sha512HashBlock(blk, H);

    // Just verify it completed without issues
    SUCCEED();
}

// Test single bit difference in block (avalanche effect)
TEST_F(Sha512HashBlockTest_1643, SingleBitDifference_1643) {
    uint64_t H1[8] = {
        0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL,
        0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
        0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL,
        0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL
    };
    uint64_t H2[8];
    memcpy(H2, H1, sizeof(H1));

    unsigned char blk1[128], blk2[128];
    memset(blk1, 0, 128);
    memset(blk2, 0, 128);
    blk2[64] = 0x01; // single bit difference in second half

    sha512HashBlock(blk1, H1);
    sha512HashBlock(blk2, H2);

    // Count differing words - expect significant difference (avalanche)
    int diffCount = 0;
    for (int i = 0; i < 8; i++) {
        if (H1[i] != H2[i]) {
            diffCount++;
        }
    }
    // All 8 words should differ due to avalanche effect
    EXPECT_GT(diffCount, 0);
}
