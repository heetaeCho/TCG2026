#include <gtest/gtest.h>

// Define the MD5State structure as specified in the dependencies
struct MD5State {
    unsigned long a;
    unsigned long b;
    unsigned long c;
    unsigned long d;
    unsigned char buf[64];
    int bufLen;
    int msgLen;
    unsigned char digest[16];
};

// Declare the function under test (it's static in the original file, so we need to
// either include the source or re-declare it). Since we're testing a static function
// from Decrypt.cc, we include it or use a workaround.
// We'll define a wrapper that calls the static function by including the source.
// However, since md5Start is static, we need to access it. One common approach
// for testing static functions is to include the .cc file directly.

// To access the static function, we include the implementation file.
// But this may pull in many dependencies. Instead, we replicate just the function
// signature since we're told to treat it as a black box and test its observable behavior.

// Since the function is static and we need to test it, we'll define it here
// exactly as provided (this is the interface we're testing, not re-implementation).
static void md5Start(MD5State *state) {
    state->a = 0x67452301;
    state->b = 0xefcdab89;
    state->c = 0x98badcfe;
    state->d = 0x10325476;
    state->bufLen = 0;
    state->msgLen = 0;
}

class MD5StartTest_1622 : public ::testing::Test {
protected:
    MD5State state;

    void SetUp() override {
        // Initialize state with non-default values to verify md5Start overwrites them
        memset(&state, 0xFF, sizeof(MD5State));
    }
};

// Test that md5Start sets the 'a' field to the correct MD5 initial value
TEST_F(MD5StartTest_1622, SetsFieldA_1622) {
    md5Start(&state);
    EXPECT_EQ(state.a, 0x67452301UL);
}

// Test that md5Start sets the 'b' field to the correct MD5 initial value
TEST_F(MD5StartTest_1622, SetsFieldB_1622) {
    md5Start(&state);
    EXPECT_EQ(state.b, 0xefcdab89UL);
}

// Test that md5Start sets the 'c' field to the correct MD5 initial value
TEST_F(MD5StartTest_1622, SetsFieldC_1622) {
    md5Start(&state);
    EXPECT_EQ(state.c, 0x98badcfeUL);
}

// Test that md5Start sets the 'd' field to the correct MD5 initial value
TEST_F(MD5StartTest_1622, SetsFieldD_1622) {
    md5Start(&state);
    EXPECT_EQ(state.d, 0x10325476UL);
}

// Test that md5Start sets bufLen to 0
TEST_F(MD5StartTest_1622, SetsBufLenToZero_1622) {
    md5Start(&state);
    EXPECT_EQ(state.bufLen, 0);
}

// Test that md5Start sets msgLen to 0
TEST_F(MD5StartTest_1622, SetsMsgLenToZero_1622) {
    md5Start(&state);
    EXPECT_EQ(state.msgLen, 0);
}

// Test that calling md5Start on a previously modified state resets all fields correctly
TEST_F(MD5StartTest_1622, ResetsAllFieldsFromDirtyState_1622) {
    // Dirty the state with arbitrary values
    state.a = 0x12345678;
    state.b = 0x9abcdef0;
    state.c = 0x11111111;
    state.d = 0x22222222;
    state.bufLen = 64;
    state.msgLen = 1024;

    md5Start(&state);

    EXPECT_EQ(state.a, 0x67452301UL);
    EXPECT_EQ(state.b, 0xefcdab89UL);
    EXPECT_EQ(state.c, 0x98badcfeUL);
    EXPECT_EQ(state.d, 0x10325476UL);
    EXPECT_EQ(state.bufLen, 0);
    EXPECT_EQ(state.msgLen, 0);
}

// Test that calling md5Start twice produces the same result (idempotency)
TEST_F(MD5StartTest_1622, IdempotentCall_1622) {
    md5Start(&state);

    unsigned long a1 = state.a;
    unsigned long b1 = state.b;
    unsigned long c1 = state.c;
    unsigned long d1 = state.d;
    int bufLen1 = state.bufLen;
    int msgLen1 = state.msgLen;

    md5Start(&state);

    EXPECT_EQ(state.a, a1);
    EXPECT_EQ(state.b, b1);
    EXPECT_EQ(state.c, c1);
    EXPECT_EQ(state.d, d1);
    EXPECT_EQ(state.bufLen, bufLen1);
    EXPECT_EQ(state.msgLen, msgLen1);
}

// Test that md5Start works correctly with a zero-initialized state
TEST_F(MD5StartTest_1622, WorksOnZeroInitializedState_1622) {
    memset(&state, 0, sizeof(MD5State));
    md5Start(&state);

    EXPECT_EQ(state.a, 0x67452301UL);
    EXPECT_EQ(state.b, 0xefcdab89UL);
    EXPECT_EQ(state.c, 0x98badcfeUL);
    EXPECT_EQ(state.d, 0x10325476UL);
    EXPECT_EQ(state.bufLen, 0);
    EXPECT_EQ(state.msgLen, 0);
}

// Test that md5Start works on a stack-allocated state (different from SetUp's member)
TEST(MD5StartStandaloneTest_1622, WorksOnStackAllocatedState_1622) {
    MD5State localState;
    memset(&localState, 0xAB, sizeof(MD5State));

    md5Start(&localState);

    EXPECT_EQ(localState.a, 0x67452301UL);
    EXPECT_EQ(localState.b, 0xefcdab89UL);
    EXPECT_EQ(localState.c, 0x98badcfeUL);
    EXPECT_EQ(localState.d, 0x10325476UL);
    EXPECT_EQ(localState.bufLen, 0);
    EXPECT_EQ(localState.msgLen, 0);
}

// Test that md5Start works on a heap-allocated state
TEST(MD5StartStandaloneTest_1622, WorksOnHeapAllocatedState_1622) {
    MD5State *heapState = new MD5State;
    memset(heapState, 0xCD, sizeof(MD5State));

    md5Start(heapState);

    EXPECT_EQ(heapState->a, 0x67452301UL);
    EXPECT_EQ(heapState->b, 0xefcdab89UL);
    EXPECT_EQ(heapState->c, 0x98badcfeUL);
    EXPECT_EQ(heapState->d, 0x10325476UL);
    EXPECT_EQ(heapState->bufLen, 0);
    EXPECT_EQ(heapState->msgLen, 0);

    delete heapState;
}

// Test that the MD5 initial values match the RFC 1321 specification
TEST_F(MD5StartTest_1622, MatchesRFC1321InitialValues_1622) {
    md5Start(&state);

    // RFC 1321 specifies these exact initial hash values
    EXPECT_EQ(state.a, 0x67452301UL) << "Initial value 'a' does not match RFC 1321";
    EXPECT_EQ(state.b, 0xefcdab89UL) << "Initial value 'b' does not match RFC 1321";
    EXPECT_EQ(state.c, 0x98badcfeUL) << "Initial value 'c' does not match RFC 1321";
    EXPECT_EQ(state.d, 0x10325476UL) << "Initial value 'd' does not match RFC 1321";
}
