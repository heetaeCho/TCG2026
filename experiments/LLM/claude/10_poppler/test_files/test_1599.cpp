#include <gtest/gtest.h>
#include <cstring>

// We need to test the static function rc4DecryptByte. Since it's static in a .cc file,
// we'll replicate its signature here for testing purposes. The function is a standard
// RC4 stream cipher byte decryption operation.

// Extern declaration or direct inclusion won't work for static functions.
// We replicate the function exactly as given to test its interface behavior.
static unsigned char rc4DecryptByte(unsigned char *state, unsigned char *x, unsigned char *y, unsigned char c) {
    unsigned char x1, y1, tx, ty;
    x1 = *x = (*x + 1) % 256;
    y1 = *y = (state[*x] + *y) % 256;
    tx = state[x1];
    ty = state[y1];
    state[x1] = ty;
    state[y1] = tx;
    return c ^ state[(tx + ty) % 256];
}

class Rc4DecryptByteTest_1599 : public ::testing::Test {
protected:
    unsigned char state[256];
    unsigned char x, y;

    void SetUp() override {
        // Initialize state as identity permutation (standard RC4 initial state before KSA)
        for (int i = 0; i < 256; i++) {
            state[i] = static_cast<unsigned char>(i);
        }
        x = 0;
        y = 0;
    }
};

// Test that x is incremented by 1 after a single call
TEST_F(Rc4DecryptByteTest_1599, XIncrementsByOne_1599) {
    unsigned char origX = x;
    rc4DecryptByte(state, &x, &y, 0x00);
    EXPECT_EQ(x, (origX + 1) % 256);
}

// Test that y is updated based on state[x] + old y
TEST_F(Rc4DecryptByteTest_1599, YIsUpdatedCorrectly_1599) {
    // With identity state, x goes to 1, y = (state[1] + 0) % 256 = 1
    rc4DecryptByte(state, &x, &y, 0x00);
    EXPECT_EQ(y, 1);
}

// Test that state is swapped after the call
TEST_F(Rc4DecryptByteTest_1599, StateIsSwapped_1599) {
    // Before: state[1] = 1, state[1] = 1 (x1=1, y1=1 with identity state)
    // Actually x1 = 1, y1 = (state[1] + 0) % 256 = 1, so x1 == y1, swap is no-op
    rc4DecryptByte(state, &x, &y, 0x00);
    // x1=1, y1=1, swap state[1] and state[1] -> no change
    EXPECT_EQ(state[1], 1);
}

// Test decrypting zero byte with identity permutation
TEST_F(Rc4DecryptByteTest_1599, DecryptZeroByte_1599) {
    // x1=1, y1=1, tx=state[1]=1, ty=state[1]=1
    // return 0x00 ^ state[(1+1)%256] = state[2] = 2
    unsigned char result = rc4DecryptByte(state, &x, &y, 0x00);
    EXPECT_EQ(result, 2);
}

// Test decrypting a non-zero byte
TEST_F(Rc4DecryptByteTest_1599, DecryptNonZeroByte_1599) {
    // Same as above but XOR with input byte
    // result = 0xFF ^ state[2] = 0xFF ^ 2 = 0xFD
    unsigned char result = rc4DecryptByte(state, &x, &y, 0xFF);
    EXPECT_EQ(result, 0xFF ^ 2);
}

// Test two consecutive calls produce different outputs for same input
TEST_F(Rc4DecryptByteTest_1599, ConsecutiveCallsProduceDifferentResults_1599) {
    unsigned char r1 = rc4DecryptByte(state, &x, &y, 0x00);
    unsigned char r2 = rc4DecryptByte(state, &x, &y, 0x00);
    // They should generally differ due to state evolution
    // Not guaranteed in all cases but with identity permutation they will differ
    EXPECT_NE(r1, r2);
}

// Test that encrypting then "decrypting" (applying twice) recovers original
TEST_F(Rc4DecryptByteTest_1599, EncryptDecryptRoundTrip_1599) {
    unsigned char state2[256];
    memcpy(state2, state, 256);
    unsigned char x2 = 0, y2 = 0;

    unsigned char plaintext = 0x42;
    unsigned char ciphertext = rc4DecryptByte(state, &x, &y, plaintext);
    unsigned char recovered = rc4DecryptByte(state2, &x2, &y2, ciphertext);
    EXPECT_EQ(recovered, plaintext);
}

// Test boundary: x wraps around from 255 to 0
TEST_F(Rc4DecryptByteTest_1599, XWrapsAround_1599) {
    x = 255;
    rc4DecryptByte(state, &x, &y, 0x00);
    EXPECT_EQ(x, 0);
}

// Test boundary: y wraps around
TEST_F(Rc4DecryptByteTest_1599, YWrapsAroundCorrectly_1599) {
    y = 255;
    // x becomes 1, y = (state[1] + 255) % 256 = (1 + 255) % 256 = 0
    rc4DecryptByte(state, &x, &y, 0x00);
    EXPECT_EQ(y, 0);
}

// Test with non-identity state
TEST_F(Rc4DecryptByteTest_1599, NonIdentityState_1599) {
    // Reverse the state array
    for (int i = 0; i < 256; i++) {
        state[i] = static_cast<unsigned char>(255 - i);
    }
    x = 0;
    y = 0;

    // x1 = 1, state[1] = 254, y1 = (254 + 0) % 256 = 254
    // tx = state[1] = 254, ty = state[254] = 1
    // swap: state[1] = 1, state[254] = 254
    // return 0x00 ^ state[(254 + 1) % 256] = state[255] = 0
    unsigned char result = rc4DecryptByte(state, &x, &y, 0x00);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, 254);
    EXPECT_EQ(state[1], 1);
    EXPECT_EQ(state[254], 254);
}

// Test multiple bytes in sequence maintain consistent state
TEST_F(Rc4DecryptByteTest_1599, MultipleByteSequence_1599) {
    unsigned char results[10];
    for (int i = 0; i < 10; i++) {
        results[i] = rc4DecryptByte(state, &x, &y, static_cast<unsigned char>(i));
    }
    // Verify x advanced 10 times
    EXPECT_EQ(x, 10);

    // Verify results are deterministic by running again with same initial state
    unsigned char state2[256];
    for (int i = 0; i < 256; i++) {
        state2[i] = static_cast<unsigned char>(i);
    }
    unsigned char x2 = 0, y2 = 0;
    for (int i = 0; i < 10; i++) {
        unsigned char r = rc4DecryptByte(state2, &x2, &y2, static_cast<unsigned char>(i));
        EXPECT_EQ(r, results[i]) << "Mismatch at index " << i;
    }
}

// Test all zero state
TEST_F(Rc4DecryptByteTest_1599, AllZeroState_1599) {
    memset(state, 0, 256);
    x = 0;
    y = 0;

    // x1 = 1, y1 = (state[1] + 0) % 256 = 0
    // tx = state[1] = 0, ty = state[0] = 0
    // swap is no-op (both zero)
    // return c ^ state[(0+0)%256] = c ^ state[0] = c ^ 0 = c
    unsigned char result = rc4DecryptByte(state, &x, &y, 0x42);
    EXPECT_EQ(result, 0x42);
}

// Test XOR property: decrypt(c1) ^ decrypt(c2) for same keystream position
TEST_F(Rc4DecryptByteTest_1599, XorProperty_1599) {
    unsigned char state2[256];
    memcpy(state2, state, 256);
    unsigned char x2 = 0, y2 = 0;

    unsigned char r1 = rc4DecryptByte(state, &x, &y, 0x00);
    unsigned char r2 = rc4DecryptByte(state2, &x2, &y2, 0xFF);

    // r1 = 0x00 ^ K, r2 = 0xFF ^ K, so r1 ^ r2 = 0xFF
    EXPECT_EQ(r1 ^ r2, 0xFF);
}

// Test that state[x1] and state[y1] are properly swapped
TEST_F(Rc4DecryptByteTest_1599, SwapVerification_1599) {
    // Set up state where swap is observable
    // x=0 -> x1=1, state[1]=1, y=0 -> y1=(1+0)%256=1
    // Since x1==y1, swap is no-op with identity. Let's use different initial conditions.
    x = 1;
    y = 0;
    // x1 = 2, state[2] = 2, y1 = (2+0)%256 = 2
    // Again x1==y1. Let's set y=5.
    y = 5;
    // x1 = 2, state[2] = 2, y1 = (2+5)%256 = 7
    // tx = state[2] = 2, ty = state[7] = 7
    // After swap: state[2] = 7, state[7] = 2
    unsigned char before_2 = state[2];
    unsigned char before_7 = state[7];
    rc4DecryptByte(state, &x, &y, 0x00);
    EXPECT_EQ(state[2], before_7);
    EXPECT_EQ(state[7], before_2);
}

// Test return value computation: c ^ state[(tx+ty)%256]
TEST_F(Rc4DecryptByteTest_1599, ReturnValueComputation_1599) {
    x = 1;
    y = 5;
    // x1=2, y1=(state[2]+5)%256=(2+5)%256=7
    // tx=state[2]=2, ty=state[7]=7
    // result = c ^ state[(2+7)%256] = c ^ state[9] = c ^ 9
    unsigned char result = rc4DecryptByte(state, &x, &y, 0x00);
    EXPECT_EQ(result, 9);  // 0x00 ^ 9 = 9
}
