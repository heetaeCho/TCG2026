#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util/coding.h"

#include "leveldb/slice.h"



namespace leveldb {



class GetVarint32Test_447 : public ::testing::Test {

protected:

    Slice input;

    uint32_t value;



    void SetUp() override {

        value = 0;

    }

};



TEST_F(GetVarint32Test_447, NormalOperation_SingleByte_447) {

    const char data[] = {0x01};

    input = Slice(data, sizeof(data));

    EXPECT_TRUE(GetVarint32(&input, &value));

    EXPECT_EQ(value, 1);

}



TEST_F(GetVarint32Test_447, NormalOperation_TwoBytes_447) {

    const char data[] = {0x81, 0x01};

    input = Slice(data, sizeof(data));

    EXPECT_TRUE(GetVarint32(&input, &value));

    EXPECT_EQ(value, 129);

}



TEST_F(GetVarint32Test_447, NormalOperation_FiveBytes_447) {

    const char data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x0F};

    input = Slice(data, sizeof(data));

    EXPECT_TRUE(GetVarint32(&input, &value));

    EXPECT_EQ(value, 0xFFFFFFFF);

}



TEST_F(GetVarint32Test_447, BoundaryCondition_EmptySlice_447) {

    const char data[] = {};

    input = Slice(data, sizeof(data));

    EXPECT_FALSE(GetVarint32(&input, &value));

}



TEST_F(GetVarint32Test_447, BoundaryCondition_IncompleteVarint_447) {

    const char data[] = {0x81};

    input = Slice(data, sizeof(data));

    EXPECT_FALSE(GetVarint32(&input, &value));

}



TEST_F(GetVarint32Test_447, BoundaryCondition_ZeroValue_447) {

    const char data[] = {0x00};

    input = Slice(data, sizeof(data));

    EXPECT_TRUE(GetVarint32(&input, &value));

    EXPECT_EQ(value, 0);

}



TEST_F(GetVarint32Test_447, BoundaryCondition_MaxValue_447) {

    const char data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x0F};

    input = Slice(data, sizeof(data));

    EXPECT_TRUE(GetVarint32(&input, &value));

    EXPECT_EQ(value, 0xFFFFFFFF);

}



TEST_F(GetVarint32Test_447, BoundaryCondition_MaxSingleByteValue_447) {

    const char data[] = {0x7F};

    input = Slice(data, sizeof(data));

    EXPECT_TRUE(GetVarint32(&input, &value));

    EXPECT_EQ(value, 127);

}



TEST_F(GetVarint32Test_447, BoundaryCondition_MaxTwoBytesValue_447) {

    const char data[] = {0xFF, 0x01};

    input = Slice(data, sizeof(data));

    EXPECT_TRUE(GetVarint32(&input, &value));

    EXPECT_EQ(value, 16383);

}



TEST_F(GetVarint32Test_447, BoundaryCondition_MaxThreeBytesValue_447) {

    const char data[] = {0xFF, 0xFF, 0x01};

    input = Slice(data, sizeof(data));

    EXPECT_TRUE(GetVarint32(&input, &value));

    EXPECT_EQ(value, 2097151);

}



TEST_F(GetVarint32Test_447, BoundaryCondition_MaxFourBytesValue_447) {

    const char data[] = {0xFF, 0xFF, 0xFF, 0x01};

    input = Slice(data, sizeof(data));

    EXPECT_TRUE(GetVarint32(&input, &value));

    EXPECT_EQ(value, 268435455);

}



} // namespace leveldb
