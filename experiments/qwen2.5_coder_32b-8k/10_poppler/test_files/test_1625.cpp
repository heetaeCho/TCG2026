#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming MD5State and md5ProcessBlock are declared in a header file.

struct MD5State {

    unsigned long a;

    unsigned long b;

    unsigned long c;

    unsigned long d;

    unsigned char buf[64];

    int msgLen;

    unsigned char digest[16];

};



extern "C" void md5Finish(MD5State *state);



class MD5StateTest : public ::testing::Test {

protected:

    MD5State state;



    void SetUp() override {

        memset(&state, 0, sizeof(state));

    }

};



TEST_F(MD5StateTest_NormalOperation_1625, FinishSetsPaddingCorrectly_1625) {

    md5Finish(&state);

    EXPECT_EQ(state.buf[56], (unsigned char)(state.msgLen << 3));

    EXPECT_EQ(state.buf[57], (unsigned char)(state.msgLen >> 5));

    EXPECT_EQ(state.buf[58], (unsigned char)(state.msgLen >> 13));

    EXPECT_EQ(state.buf[59], (unsigned char)(state.msgLen >> 21));

    EXPECT_EQ(state.buf[60], (unsigned char)(state.msgLen >> 29));

    EXPECT_EQ(state.buf[61], 0);

    EXPECT_EQ(state.buf[62], 0);

    EXPECT_EQ(state.buf[63], 0);

}



TEST_F(MD5StateTest_BoundaryCondition_1625, FinishWithBufLenLessThan56_1625) {

    state.bufLen = 55;

    md5Finish(&state);

    EXPECT_EQ(state.buf[state.bufLen - 1], 0x80);

}



TEST_F(MD5StateTest_BoundaryCondition_1625, FinishWithBufLenGreaterThan56_1625) {

    state.bufLen = 57;

    md5Finish(&state);

    EXPECT_EQ(state.buf[state.bufLen - 1], 0x80);

}



TEST_F(MD5StateTest_ExceptionalCase_1625, FinishWithMaxMessageLength_1625) {

    state.msgLen = (1LL << 34); // Simulate a very large message length

    md5Finish(&state);

    EXPECT_EQ(state.buf[56], (unsigned char)((1LL << 34) << 3));

    EXPECT_EQ(state.buf[57], (unsigned char)(((1LL << 34) >> 5)));

    EXPECT_EQ(state.buf[58], (unsigned char)(((1LL << 34) >> 13)));

    EXPECT_EQ(state.buf[59], (unsigned char)(((1LL << 34) >> 21)));

    EXPECT_EQ(state.buf[60], (unsigned char)(((1LL << 34) >> 29)));

}



TEST_F(MD5StateTest_Verification_1625, FinishCallsProcessBlockCorrectly_1625) {

    // This test assumes md5ProcessBlock is a function that can be mocked or verified.

    // Since we cannot mock internal functions, we verify the state changes expected by processBlock calls.



    // Simulate a bufLen that would cause multiple processBlock calls

    state.bufLen = 63;

    md5Finish(&state);

    EXPECT_EQ(state.bufLen, 64); // After finishing, bufLen should be reset to 64



    // Reset and simulate another scenario

    memset(&state, 0, sizeof(state));

    state.bufLen = 57;

    md5Finish(&state);

    EXPECT_EQ(state.bufLen, 64); // After finishing, bufLen should be reset to 64

}
