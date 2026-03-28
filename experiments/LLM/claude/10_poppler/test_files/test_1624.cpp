#include <gtest/gtest.h>
#include <cstring>
#include <string>

// Include the implementation to access the static function
// We need the MD5State structure and the static functions
#include "poppler/Decrypt.h"

// If md5 functions are not in the header, we may need to include the .cc
// For testing static functions, include the source directly
#include "poppler/Decrypt.cc"

class MD5AppendTest_1624 : public ::testing::Test {
protected:
    MD5State state;

    void SetUp() override {
        // Initialize MD5 state to known values
        md5Start(&state);
    }
};

// Test that appending empty data doesn't change message length
TEST_F(MD5AppendTest_1624, AppendEmptyData_1624) {
    int initialMsgLen = state.msgLen;
    md5Append(&state, nullptr, 0);
    EXPECT_EQ(state.msgLen, initialMsgLen);
}

// Test that appending data increases msgLen correctly
TEST_F(MD5AppendTest_1624, AppendIncreasesMessageLength_1624) {
    unsigned char data[] = "Hello";
    md5Append(&state, data, 5);
    EXPECT_EQ(state.msgLen, 5);
}

// Test appending data shorter than 64 bytes (buffer not full)
TEST_F(MD5AppendTest_1624, AppendShortData_1624) {
    unsigned char data[10];
    memset(data, 0xAB, 10);
    md5Append(&state, data, 10);
    EXPECT_EQ(state.msgLen, 10);
    EXPECT_EQ(state.bufLen, 10);
}

// Test appending exactly 64 bytes triggers processing
TEST_F(MD5AppendTest_1624, AppendExactBlockSize_1624) {
    unsigned char data[64];
    memset(data, 0x42, 64);
    md5Append(&state, data, 64);
    EXPECT_EQ(state.msgLen, 64);
    EXPECT_EQ(state.bufLen, 0);
}

// Test appending more than 64 bytes
TEST_F(MD5AppendTest_1624, AppendMoreThanOneBlock_1624) {
    unsigned char data[100];
    memset(data, 0x33, 100);
    md5Append(&state, data, 100);
    EXPECT_EQ(state.msgLen, 100);
    EXPECT_EQ(state.bufLen, 36); // 100 - 64 = 36
}

// Test appending exactly 128 bytes (two blocks)
TEST_F(MD5AppendTest_1624, AppendTwoBlocks_1624) {
    unsigned char data[128];
    memset(data, 0x55, 128);
    md5Append(&state, data, 128);
    EXPECT_EQ(state.msgLen, 128);
    EXPECT_EQ(state.bufLen, 0);
}

// Test multiple sequential appends
TEST_F(MD5AppendTest_1624, MultipleAppends_1624) {
    unsigned char data1[30];
    unsigned char data2[40];
    memset(data1, 0x11, 30);
    memset(data2, 0x22, 40);
    md5Append(&state, data1, 30);
    EXPECT_EQ(state.msgLen, 30);
    EXPECT_EQ(state.bufLen, 30);
    md5Append(&state, data2, 40);
    EXPECT_EQ(state.msgLen, 70);
    EXPECT_EQ(state.bufLen, 6); // 70 - 64 = 6
}

// Test multiple small appends that eventually fill a block
TEST_F(MD5AppendTest_1624, ManySmallAppends_1624) {
    unsigned char data[1] = {0xAA};
    for (int i = 0; i < 65; i++) {
        md5Append(&state, data, 1);
    }
    EXPECT_EQ(state.msgLen, 65);
    EXPECT_EQ(state.bufLen, 1);
}

// Test appending large data spanning multiple blocks
TEST_F(MD5AppendTest_1624, AppendLargeData_1624) {
    unsigned char data[300];
    memset(data, 0x77, 300);
    md5Append(&state, data, 300);
    EXPECT_EQ(state.msgLen, 300);
    EXPECT_EQ(state.bufLen, 300 % 64); // 300 = 4*64 + 44
}

// Test full MD5 computation produces correct digest for known input
TEST_F(MD5AppendTest_1624, FullMD5EmptyString_1624) {
    md5Finish(&state);
    // MD5("") = d41d8cd98f00b204e9800998ecf8427e
    EXPECT_EQ(state.digest[0], 0xd4);
    EXPECT_EQ(state.digest[1], 0x1d);
    EXPECT_EQ(state.digest[2], 0x8c);
    EXPECT_EQ(state.digest[3], 0xd9);
}

// Test full MD5 for "abc"
TEST_F(MD5AppendTest_1624, FullMD5Abc_1624) {
    unsigned char data[] = "abc";
    md5Append(&state, data, 3);
    md5Finish(&state);
    // MD5("abc") = 900150983cd24fb0d6963f7d28e17f72
    EXPECT_EQ(state.digest[0], 0x90);
    EXPECT_EQ(state.digest[1], 0x01);
    EXPECT_EQ(state.digest[2], 0x50);
    EXPECT_EQ(state.digest[3], 0x98);
}
