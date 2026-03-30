#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/slice.h"

#include "util/coding.h"



using namespace leveldb;



class GetVarint64Test_449 : public ::testing::Test {

protected:

    uint64_t value;

};



TEST_F(GetVarint64Test_449, NormalOperation_449) {

    char data[] = {0x81, 0x25};

    Slice input(data, sizeof(data));

    EXPECT_TRUE(GetVarint64(&input, &value));

    EXPECT_EQ(value, 321);

}



TEST_F(GetVarint64Test_449, SingleByteValue_449) {

    char data[] = {0x7F};

    Slice input(data, sizeof(data));

    EXPECT_TRUE(GetVarint64(&input, &value));

    EXPECT_EQ(value, 127);

}



TEST_F(GetVarint64Test_449, MultiByteValue_449) {

    char data[] = {0x8F, 0x92};

    Slice input(data, sizeof(data));

    EXPECT_TRUE(GetVarint64(&input, &value));

    EXPECT_EQ(value, 1543);

}



TEST_F(GetVarint64Test_449, MaxValue_449) {

    char data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F};

    Slice input(data, sizeof(data));

    EXPECT_TRUE(GetVarint64(&input, &value));

    EXPECT_EQ(value, UINT64_MAX);

}



TEST_F(GetVarint64Test_449, IncompleteInput_449) {

    char data[] = {0x81};

    Slice input(data, sizeof(data));

    EXPECT_FALSE(GetVarint64(&input, &value));

}



TEST_F(GetVarint64Test_449, EmptySlice_449) {

    Slice input;

    EXPECT_FALSE(GetVarint64(&input, &value));

}



TEST_F(GetVarint64Test_449, InputRemainsAfterParsing_449) {

    char data[] = {0x7F, 0xFF};

    Slice input(data, sizeof(data));

    EXPECT_TRUE(GetVarint64(&input, &value));

    EXPECT_EQ(value, 127);

    EXPECT_EQ(input.size(), 1);

}
