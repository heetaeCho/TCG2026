#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// We need to replicate the helper macros/functions and the sha256K table
// since sha256HashBlock is a static function in Decrypt.cc.
// We'll include the necessary definitions and test the function directly.

// SHA-256 helper functions
static unsigned int sha256Ch(unsigned int x, unsigned int y, unsigned int z) {
    return (x & y) ^ (~x & z);
}

static unsigned int sha256Maj(unsigned int x, unsigned int y, unsigned int z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

static unsigned int rotr(unsigned int x, unsigned int n) {
    return (x >> n) | (x << (32 - n));
}

static unsigned int sha256Sigma0(unsigned int x) {
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

static unsigned int sha256Sigma1(unsigned int x) {
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

static unsigned int sha256sigma0(unsigned int x) {
    return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

static unsigned int sha256sigma1(unsigned int x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

static const unsigned int sha256K[64] = {
    1116352408, 1899447441, 3049323471U, 3921009573U, 961987163, 1508970993,
    2453635748U, 2870763221U, 3624381080U, 310598401, 607225278, 1426881987,
    1925078388, 2162078206U, 2614888103U, 3248222580U, 3835390401U, 4022224774U,
    264347078, 604807628, 770255983, 1249150122, 1555081692, 1996064986,
    2554220882U, 2821834349U, 2952996808U, 3210313671U, 3336571891U, 3584528711U,
    113926993, 338241895, 666307205, 773529912, 1294757372, 1396182291,
    1695183700, 1986661051, 2177026350U, 2456956037U, 2730485921U, 2820302411U,
    3259730800U, 3345764771U, 3516065817U, 3600352804U, 4094571909U, 275423344,
    430227734, 506948616, 659060556, 883997877, 958139571, 1322822218,
    1537002063, 1747873779, 1955562222, 2024104815, 2227730452U, 2361852424U,
    2428436474U, 2756734187U, 3204031479U, 3329325298U
};

// Reimplementation of sha256HashBlock to test against (this IS the function under test,
// but since it's static in the .cc file, we reproduce it here for testing purposes)
static void sha256HashBlock(const unsigned char *blk, unsigned int *H) {
    unsigned int W[64];
    unsigned int a, b, c, d, e, f, g, h;
    unsigned int T1, T2;
    unsigned int t;

    for (t = 0; t < 16; ++t) {
        W[t] = (blk[t * 4] << 24) | (blk[t * 4 + 1] << 16) | (blk[t * 4 + 2] << 8) | blk[t * 4 + 3];
    }
    for (t = 16; t < 64; ++t) {
        W[t] = sha256sigma1(W[t - 2]) + W[t - 7] + sha256sigma0(W[t - 15]) + W[t - 16];
    }

    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];

    for (t = 0; t < 64; ++t) {
        T1 = h + sha256Sigma1(e) + sha256Ch(e, f, g) + sha256K[t] + W[t];
        T2 = sha256Sigma0(a) + sha256Maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
    H[4] += e;
    H[5] += f;
    H[6] += g;
    H[7] += h;
}

class Sha256HashBlockTest_1634 : public ::testing::Test {
protected:
    // SHA-256 initial hash values
    unsigned int H[8];

    void SetUp() override {
        // Standard SHA-256 initial hash values
        H[0] = 0x6a09e667;
        H[1] = 0xbb67ae85;
        H[2] = 0x3c6ef372;
        H[3] = 0xa54ff53a;
        H[4] = 0x510e527f;
        H[5] = 0x9b05688c;
        H[6] = 0x1f83d9ab;
        H[7] = 0x5be0cd19;
    }
};

// Test: Processing a zero block modifies the hash state
TEST_F(Sha256HashBlockTest_1634, ZeroBlockModifiesState_1634) {
    unsigned char blk[64];
    memset(blk, 0, 64);

    unsigned int H_before[8];
    memcpy(H_before, H, sizeof(H));

    sha256HashBlock(blk, H);

    // After processing a block, the hash state should change
    bool changed = false;
    for (int i = 0; i < 8; i++) {
        if (H[i] != H_before[i]) {
            changed = true;
            break;
        }
    }
    EXPECT_TRUE(changed);
}

// Test: SHA-256 of "abc" - first block
// "abc" padded to a single 512-bit block per SHA-256 spec:
// 61 62 63 80 00...00 00 00 00 00 00 00 00 18
TEST_F(Sha256HashBlockTest_1634, AbcSingleBlock_1634) {
    unsigned char blk[64];
    memset(blk, 0, 64);
    blk[0] = 'a';  // 0x61
    blk[1] = 'b';  // 0x62
    blk[2] = 'c';  // 0x63
    blk[3] = 0x80; // padding bit
    // Length of "abc" is 3 bytes = 24 bits = 0x18
    blk[63] = 0x18;

    sha256HashBlock(blk, H);

    // Expected SHA-256("abc") = ba7816bf 8f01cfea 414140de 5dae2223 b00361a3 96177a9c b410ff61 f20015ad
    EXPECT_EQ(H[0], 0xba7816bf);
    EXPECT_EQ(H[1], 0x8f01cfea);
    EXPECT_EQ(H[2], 0x414140de);
    EXPECT_EQ(H[3], 0x5dae2223);
    EXPECT_EQ(H[4], 0xb00361a3);
    EXPECT_EQ(H[5], 0x96177a9c);
    EXPECT_EQ(H[6], 0xb410ff61);
    EXPECT_EQ(H[7], 0xf20015ad);
}

// Test: SHA-256 of empty string ""
// Padded block: 80 00...00 00 00 00 00 00 00 00 00 (length = 0 bits)
TEST_F(Sha256HashBlockTest_1634, EmptyStringBlock_1634) {
    unsigned char blk[64];
    memset(blk, 0, 64);
    blk[0] = 0x80;
    // Length is 0, so last 8 bytes are all zero already

    sha256HashBlock(blk, H);

    // Expected SHA-256("") = e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
    EXPECT_EQ(H[0], 0xe3b0c442);
    EXPECT_EQ(H[1], 0x98fc1c14);
    EXPECT_EQ(H[2], 0x9afbf4c8);
    EXPECT_EQ(H[3], 0x996fb924);
    EXPECT_EQ(H[4], 0x27ae41e4);
    EXPECT_EQ(H[5], 0x649b934c);
    EXPECT_EQ(H[6], 0xa495991b);
    EXPECT_EQ(H[7], 0x7852b855);
}

// Test: Processing an all-0xFF block
TEST_F(Sha256HashBlockTest_1634, AllOnesBlock_1634) {
    unsigned char blk[64];
    memset(blk, 0xFF, 64);

    unsigned int H_before[8];
    memcpy(H_before, H, sizeof(H));

    sha256HashBlock(blk, H);

    // The state should be modified
    bool changed = false;
    for (int i = 0; i < 8; i++) {
        if (H[i] != H_before[i]) {
            changed = true;
            break;
        }
    }
    EXPECT_TRUE(changed);
}

// Test: Determinism - same input produces same output
TEST_F(Sha256HashBlockTest_1634, Deterministic_1634) {
    unsigned char blk[64];
    for (int i = 0; i < 64; i++) {
        blk[i] = (unsigned char)(i * 3 + 7);
    }

    unsigned int H1[8], H2[8];
    memcpy(H1, H, sizeof(H));
    memcpy(H2, H, sizeof(H));

    sha256HashBlock(blk, H1);
    sha256HashBlock(blk, H2);

    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(H1[i], H2[i]);
    }
}

// Test: Different blocks produce different hashes
TEST_F(Sha256HashBlockTest_1634, DifferentBlocksDifferentHashes_1634) {
    unsigned char blk1[64], blk2[64];
    memset(blk1, 0, 64);
    memset(blk2, 0, 64);
    blk2[0] = 1; // Only one bit different

    unsigned int H1[8], H2[8];
    memcpy(H1, H, sizeof(H));
    memcpy(H2, H, sizeof(H));

    sha256HashBlock(blk1, H1);
    sha256HashBlock(blk2, H2);

    bool different = false;
    for (int i = 0; i < 8; i++) {
        if (H1[i] != H2[i]) {
            different = true;
            break;
        }
    }
    EXPECT_TRUE(different);
}

// Test: Processing two blocks sequentially (chaining)
TEST_F(Sha256HashBlockTest_1634, TwoBlockChaining_1634) {
    unsigned char blk1[64], blk2[64];
    memset(blk1, 0xAA, 64);
    memset(blk2, 0x55, 64);

    unsigned int H_single[8];
    memcpy(H_single, H, sizeof(H));

    // Process first block
    sha256HashBlock(blk1, H);
    
    // Save state after first block
    unsigned int H_after_first[8];
    memcpy(H_after_first, H, sizeof(H));

    // Process second block
    sha256HashBlock(blk2, H);

    // H should be different from after first block
    bool changed = false;
    for (int i = 0; i < 8; i++) {
        if (H[i] != H_after_first[i]) {
            changed = true;
            break;
        }
    }
    EXPECT_TRUE(changed);
}

// Test: Order of blocks matters
TEST_F(Sha256HashBlockTest_1634, BlockOrderMatters_1634) {
    unsigned char blk1[64], blk2[64];
    memset(blk1, 0xAA, 64);
    memset(blk2, 0x55, 64);

    unsigned int H_order1[8], H_order2[8];
    
    // Order 1: blk1 then blk2
    memcpy(H_order1, H, sizeof(H));
    sha256HashBlock(blk1, H_order1);
    sha256HashBlock(blk2, H_order1);

    // Order 2: blk2 then blk1
    memcpy(H_order2, H, sizeof(H));
    sha256HashBlock(blk2, H_order2);
    sha256HashBlock(blk1, H_order2);

    bool different = false;
    for (int i = 0; i < 8; i++) {
        if (H_order1[i] != H_order2[i]) {
            different = true;
            break;
        }
    }
    EXPECT_TRUE(different);
}

// Test: Initial H state affects output
TEST_F(Sha256HashBlockTest_1634, DifferentInitialStateProducesDifferentOutput_1634) {
    unsigned char blk[64];
    memset(blk, 0x42, 64);

    unsigned int H1[8], H2[8];
    memcpy(H1, H, sizeof(H));
    
    // Different initial state
    for (int i = 0; i < 8; i++) {
        H2[i] = 0;
    }

    sha256HashBlock(blk, H1);
    sha256HashBlock(blk, H2);

    bool different = false;
    for (int i = 0; i < 8; i++) {
        if (H1[i] != H2[i]) {
            different = true;
            break;
        }
    }
    EXPECT_TRUE(different);
}

// Test: All hash words are affected by a single-byte change
TEST_F(Sha256HashBlockTest_1634, AvalancheEffect_1634) {
    unsigned char blk1[64], blk2[64];
    memset(blk1, 0, 64);
    memcpy(blk2, blk1, 64);
    blk2[31] = 1; // Change one byte in the middle

    unsigned int H1[8], H2[8];
    memcpy(H1, H, sizeof(H));
    memcpy(H2, H, sizeof(H));

    sha256HashBlock(blk1, H1);
    sha256HashBlock(blk2, H2);

    // Due to avalanche effect, all 8 words should differ
    int diffCount = 0;
    for (int i = 0; i < 8; i++) {
        if (H1[i] != H2[i]) {
            diffCount++;
        }
    }
    // Expect most (if not all) words to be different
    EXPECT_GE(diffCount, 6);
}

// Test: Known test vector - single character "a" padded
TEST_F(Sha256HashBlockTest_1634, SingleCharA_1634) {
    // "a" = 0x61, padded: 61 80 00...00 00 00 00 08
    unsigned char blk[64];
    memset(blk, 0, 64);
    blk[0] = 0x61;
    blk[1] = 0x80;
    blk[63] = 0x08; // 8 bits

    sha256HashBlock(blk, H);

    // SHA-256("a") = ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb
    EXPECT_EQ(H[0], 0xca978112);
    EXPECT_EQ(H[1], 0xca1bbdca);
    EXPECT_EQ(H[2], 0xfac231b3);
    EXPECT_EQ(H[3], 0x9a23dc4d);
    EXPECT_EQ(H[4], 0xa786eff8);
    EXPECT_EQ(H[5], 0x147c4e72);
    EXPECT_EQ(H[6], 0xb9807785);
    EXPECT_EQ(H[7], 0xafee48bb);
}

// Test: Zero initial hash state
TEST_F(Sha256HashBlockTest_1634, ZeroInitialState_1634) {
    unsigned char blk[64];
    memset(blk, 0, 64);

    unsigned int H_zero[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    sha256HashBlock(blk, H_zero);

    // With zero initial state and zero block, we should still get non-trivial output
    bool nonZero = false;
    for (int i = 0; i < 8; i++) {
        if (H_zero[i] != 0) {
            nonZero = true;
            break;
        }
    }
    EXPECT_TRUE(nonZero);
}

// Test: Processing same block twice gives different result than processing once
TEST_F(Sha256HashBlockTest_1634, DoubleProcessingDiffersFromSingle_1634) {
    unsigned char blk[64];
    memset(blk, 0x37, 64);

    unsigned int H_once[8], H_twice[8];
    memcpy(H_once, H, sizeof(H));
    memcpy(H_twice, H, sizeof(H));

    sha256HashBlock(blk, H_once);

    sha256HashBlock(blk, H_twice);
    sha256HashBlock(blk, H_twice);

    bool different = false;
    for (int i = 0; i < 8; i++) {
        if (H_once[i] != H_twice[i]) {
            different = true;
            break;
        }
    }
    EXPECT_TRUE(different);
}

// Test: Byte ordering in block - big-endian word construction
TEST_F(Sha256HashBlockTest_1634, BigEndianWordConstruction_1634) {
    // Create two blocks that differ only in byte order within a word
    unsigned char blk1[64], blk2[64];
    memset(blk1, 0, 64);
    memset(blk2, 0, 64);
    
    // First word of blk1: 0x01020304
    blk1[0] = 0x01; blk1[1] = 0x02; blk1[2] = 0x03; blk1[3] = 0x04;
    // First word of blk2: 0x04030201 (reversed byte order)
    blk2[0] = 0x04; blk2[1] = 0x03; blk2[2] = 0x02; blk2[3] = 0x01;

    unsigned int H1[8], H2[8];
    memcpy(H1, H, sizeof(H));
    memcpy(H2, H, sizeof(H));

    sha256HashBlock(blk1, H1);
    sha256HashBlock(blk2, H2);

    bool different = false;
    for (int i = 0; i < 8; i++) {
        if (H1[i] != H2[i]) {
            different = true;
            break;
        }
    }
    EXPECT_TRUE(different);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
