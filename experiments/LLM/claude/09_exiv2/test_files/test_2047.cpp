#include <gtest/gtest.h>

// Include necessary headers
#include <cstring>
#include <cstdint>

// Forward declare or include the MD5 header
// Based on the provided interface, we need the MD5_CTX structure and MD5Init function

// Define UWORD32 if not already defined
#ifndef UWORD32
typedef uint32_t UWORD32;
#endif

struct MD5_CTX {
    UWORD32 buf[4];
    UWORD32 bytes[2];
    UWORD32 in[16];
};

extern "C" {
    void MD5Init(struct MD5_CTX *ctx);
}

class MD5InitTest_2047 : public ::testing::Test {
protected:
    MD5_CTX ctx;
    
    void SetUp() override {
        // Initialize with garbage to verify MD5Init properly sets values
        memset(&ctx, 0xFF, sizeof(ctx));
    }
};

// Test that MD5Init sets buf[0] to the correct initial value
TEST_F(MD5InitTest_2047, InitSetsBuf0Correctly_2047) {
    MD5Init(&ctx);
    EXPECT_EQ(ctx.buf[0], 0x67452301u);
}

// Test that MD5Init sets buf[1] to the correct initial value
TEST_F(MD5InitTest_2047, InitSetsBuf1Correctly_2047) {
    MD5Init(&ctx);
    EXPECT_EQ(ctx.buf[1], 0xefcdab89u);
}

// Test that MD5Init sets buf[2] to the correct initial value
TEST_F(MD5InitTest_2047, InitSetsBuf2Correctly_2047) {
    MD5Init(&ctx);
    EXPECT_EQ(ctx.buf[2], 0x98badcfeu);
}

// Test that MD5Init sets buf[3] to the correct initial value
TEST_F(MD5InitTest_2047, InitSetsBuf3Correctly_2047) {
    MD5Init(&ctx);
    EXPECT_EQ(ctx.buf[3], 0x10325476u);
}

// Test that MD5Init sets bytes[0] to zero
TEST_F(MD5InitTest_2047, InitSetsBytes0ToZero_2047) {
    MD5Init(&ctx);
    EXPECT_EQ(ctx.bytes[0], 0u);
}

// Test that MD5Init sets bytes[1] to zero
TEST_F(MD5InitTest_2047, InitSetsBytes1ToZero_2047) {
    MD5Init(&ctx);
    EXPECT_EQ(ctx.bytes[1], 0u);
}

// Test that all buf values are set correctly in one check
TEST_F(MD5InitTest_2047, InitSetsAllBufValuesCorrectly_2047) {
    MD5Init(&ctx);
    EXPECT_EQ(ctx.buf[0], 0x67452301u);
    EXPECT_EQ(ctx.buf[1], 0xefcdab89u);
    EXPECT_EQ(ctx.buf[2], 0x98badcfeu);
    EXPECT_EQ(ctx.buf[3], 0x10325476u);
}

// Test that all bytes values are zeroed
TEST_F(MD5InitTest_2047, InitSetsAllBytesValuesToZero_2047) {
    MD5Init(&ctx);
    EXPECT_EQ(ctx.bytes[0], 0u);
    EXPECT_EQ(ctx.bytes[1], 0u);
}

// Test that calling MD5Init on a previously dirty context properly resets it
TEST_F(MD5InitTest_2047, InitResetsGarbageFilledContext_2047) {
    // ctx was filled with 0xFF in SetUp
    MD5Init(&ctx);
    EXPECT_EQ(ctx.buf[0], 0x67452301u);
    EXPECT_EQ(ctx.buf[1], 0xefcdab89u);
    EXPECT_EQ(ctx.buf[2], 0x98badcfeu);
    EXPECT_EQ(ctx.buf[3], 0x10325476u);
    EXPECT_EQ(ctx.bytes[0], 0u);
    EXPECT_EQ(ctx.bytes[1], 0u);
}

// Test that calling MD5Init twice yields the same result (idempotency)
TEST_F(MD5InitTest_2047, InitIsIdempotent_2047) {
    MD5Init(&ctx);
    
    // Manually modify some fields
    ctx.buf[0] = 0xDEADBEEF;
    ctx.bytes[0] = 42;
    
    // Re-initialize
    MD5Init(&ctx);
    
    EXPECT_EQ(ctx.buf[0], 0x67452301u);
    EXPECT_EQ(ctx.buf[1], 0xefcdab89u);
    EXPECT_EQ(ctx.buf[2], 0x98badcfeu);
    EXPECT_EQ(ctx.buf[3], 0x10325476u);
    EXPECT_EQ(ctx.bytes[0], 0u);
    EXPECT_EQ(ctx.bytes[1], 0u);
}

// Test that MD5Init on a zero-initialized context works correctly
TEST_F(MD5InitTest_2047, InitOnZeroInitializedContext_2047) {
    memset(&ctx, 0, sizeof(ctx));
    MD5Init(&ctx);
    EXPECT_EQ(ctx.buf[0], 0x67452301u);
    EXPECT_EQ(ctx.buf[1], 0xefcdab89u);
    EXPECT_EQ(ctx.buf[2], 0x98badcfeu);
    EXPECT_EQ(ctx.buf[3], 0x10325476u);
    EXPECT_EQ(ctx.bytes[0], 0u);
    EXPECT_EQ(ctx.bytes[1], 0u);
}

// Test that MD5Init on a stack-allocated context works
TEST(MD5InitStackTest_2047, InitOnStackAllocatedContext_2047) {
    MD5_CTX stackCtx;
    MD5Init(&stackCtx);
    EXPECT_EQ(stackCtx.buf[0], 0x67452301u);
    EXPECT_EQ(stackCtx.buf[1], 0xefcdab89u);
    EXPECT_EQ(stackCtx.buf[2], 0x98badcfeu);
    EXPECT_EQ(stackCtx.buf[3], 0x10325476u);
    EXPECT_EQ(stackCtx.bytes[0], 0u);
    EXPECT_EQ(stackCtx.bytes[1], 0u);
}

// Test that MD5Init on a heap-allocated context works
TEST(MD5InitHeapTest_2047, InitOnHeapAllocatedContext_2047) {
    MD5_CTX *heapCtx = new MD5_CTX;
    memset(heapCtx, 0xAB, sizeof(MD5_CTX));
    MD5Init(heapCtx);
    EXPECT_EQ(heapCtx->buf[0], 0x67452301u);
    EXPECT_EQ(heapCtx->buf[1], 0xefcdab89u);
    EXPECT_EQ(heapCtx->buf[2], 0x98badcfeu);
    EXPECT_EQ(heapCtx->buf[3], 0x10325476u);
    EXPECT_EQ(heapCtx->bytes[0], 0u);
    EXPECT_EQ(heapCtx->bytes[1], 0u);
    delete heapCtx;
}

// Test the MD5 initial values match the standard RFC 1321 constants
TEST_F(MD5InitTest_2047, InitValuesMatchRFC1321Constants_2047) {
    MD5Init(&ctx);
    // These are the standard MD5 initialization constants from RFC 1321
    // (stored in little-endian word order)
    // A = 0x67452301
    // B = 0xefcdab89
    // C = 0x98badcfe
    // D = 0x10325476
    EXPECT_EQ(ctx.buf[0], 0x67452301u);
    EXPECT_EQ(ctx.buf[1], 0xefcdab89u);
    EXPECT_EQ(ctx.buf[2], 0x98badcfeu);
    EXPECT_EQ(ctx.buf[3], 0x10325476u);
}
