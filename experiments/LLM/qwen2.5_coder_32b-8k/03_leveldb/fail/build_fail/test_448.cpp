#include <gtest/gtest.h>

#include "util/coding.cc"  // Include the header where GetVarint64Ptr is declared



namespace leveldb {



class Varint64Test_448 : public ::testing::Test {

protected:

    uint64_t value;

};



TEST_F(Varint64Test_448, NormalOperation_SingleByte_448) {

    const char data[] = {0x7F};

    const char* result = GetVarint64Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, data + 1);

    EXPECT_EQ(value, 127U);

}



TEST_F(Varint64Test_448, NormalOperation_TwoBytes_448) {

    const char data[] = {0x80, 0x01};

    const char* result = GetVarint64Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, data + 2);

    EXPECT_EQ(value, 128U);

}



TEST_F(Varint64Test_448, NormalOperation_MaxValue_448) {

    const char data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01};

    const char* result = GetVarint64Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, data + 9);

    EXPECT_EQ(value, UINT64_MAX);

}



TEST_F(Varint64Test_448, BoundaryCondition_EmptyInput_448) {

    const char* result = GetVarint64Ptr(nullptr, nullptr, &value);

    EXPECT_EQ(result, nullptr);

}



TEST_F(Varint64Test_448, BoundaryCondition_IncompleteVarint_448) {

    const char data[] = {0x80};

    const char* result = GetVarint64Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, nullptr);

}



TEST_F(Varint64Test_448, BoundaryCondition_MaxSizeIncompleteVarint_448) {

    const char data[] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80};

    const char* result = GetVarint64Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, nullptr);

}



TEST_F(Varint64Test_448, BoundaryCondition_MaxSizeCompleteVarint_448) {

    const char data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01};

    const char* result = GetVarint64Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, data + 9);

    EXPECT_EQ(value, UINT64_MAX);

}



TEST_F(Varint64Test_448, ExceptionalCase_LimitLessThanData_448) {

    const char data[] = {0x7F};

    const char* result = GetVarint64Ptr(data, data, &value);

    EXPECT_EQ(result, nullptr);

}



TEST_F(Varint64Test_448, ExceptionalCase_NegativeValue_448) {

    // Since the function is designed for unsigned values, passing negative values as bytes is not applicable.

    // However, we can test with a byte that would represent a continuation bit in an unexpected position.

    const char data[] = {0x81};

    const char* result = GetVarint64Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, nullptr);  // Expect failure due to incomplete varint

}



}  // namespace leveldb
