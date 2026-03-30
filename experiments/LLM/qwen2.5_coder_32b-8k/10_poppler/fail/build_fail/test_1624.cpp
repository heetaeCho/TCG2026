#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cstring>



// Mocking external collaborators if necessary

struct MD5State {

    unsigned long a;

    unsigned long b;

    unsigned long c;

    unsigned long d;

    unsigned char buf[64];

    int msgLen;

    unsigned char digest[16];

};



extern "C" void md5Append(MD5State *state, const unsigned char *data, int dataLen);



class MD5StateTest : public ::testing::Test {

protected:

    void SetUp() override {

        memset(&state, 0, sizeof(state));

    }



    MD5State state;

};



TEST_F(MD5StateTest_1624, AppendLessThanBlockSize_1624) {

    const unsigned char data[] = "Hello";

    int dataLen = strlen(reinterpret_cast<const char*>(data));



    md5Append(&state, data, dataLen);



    EXPECT_EQ(state.bufLen, dataLen);

    EXPECT_EQ(memcmp(state.buf, data, dataLen), 0);

    EXPECT_EQ(state.msgLen, dataLen);

}



TEST_F(MD5StateTest_1624, AppendExactBlockSize_1624) {

    unsigned char data[64];

    memset(data, 'A', sizeof(data));

    int dataLen = sizeof(data);



    md5Append(&state, data, dataLen);



    EXPECT_EQ(state.bufLen, 0);

    EXPECT_EQ(memcmp(state.buf, "", 64), 0);

    EXPECT_EQ(state.msgLen, dataLen);

}



TEST_F(MD5StateTest_1624, AppendMultipleBlocks_1624) {

    unsigned char data[128];

    memset(data, 'B', sizeof(data));

    int dataLen = sizeof(data);



    md5Append(&state, data, dataLen);



    EXPECT_EQ(state.bufLen, 0);

    EXPECT_EQ(memcmp(state.buf, "", 64), 0);

    EXPECT_EQ(state.msgLen, dataLen);

}



TEST_F(MD5StateTest_1624, AppendBoundaryCondition_1624) {

    unsigned char data[63];

    memset(data, 'C', sizeof(data));

    int dataLen = sizeof(data);



    md5Append(&state, data, dataLen);



    EXPECT_EQ(state.bufLen, dataLen);

    EXPECT_EQ(memcmp(state.buf, data, dataLen), 0);

    EXPECT_EQ(state.msgLen, dataLen);

}



TEST_F(MD5StateTest_1624, AppendEmptyData_1624) {

    unsigned char data[] = "";

    int dataLen = sizeof(data) - 1; // Empty string



    md5Append(&state, data, dataLen);



    EXPECT_EQ(state.bufLen, 0);

    EXPECT_EQ(memcmp(state.buf, "", 64), 0);

    EXPECT_EQ(state.msgLen, dataLen);

}



TEST_F(MD5StateTest_1624, AppendLargeData_1624) {

    const int largeSize = 1024;

    unsigned char* data = new unsigned char[largeSize];

    memset(data, 'D', largeSize);

    int dataLen = largeSize;



    md5Append(&state, data, dataLen);



    EXPECT_EQ(state.bufLen, (dataLen % 64));

    EXPECT_EQ(memcmp(state.buf, data + (dataLen - state.bufLen), state.bufLen), 0);

    EXPECT_EQ(state.msgLen, dataLen);



    delete[] data;

}
