#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util/coding.h"



namespace leveldb {



class CodingTest_46 : public ::testing::Test {

protected:

    uint32_t value;

};



TEST_F(CodingTest_46, GetVarint32Ptr_SingleByteValue_46) {

    const char data[] = {0x1A}; // Single byte value 26

    const char* result = GetVarint32Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, data + 1);

    EXPECT_EQ(value, 26U);

}



TEST_F(CodingTest_46, GetVarint32Ptr_TwoByteValue_46) {

    const char data[] = {0x8E, 0x02}; // Two byte value 270

    const char* result = GetVarint32Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, data + 2);

    EXPECT_EQ(value, 270U);

}



TEST_F(CodingTest_46, GetVarint32Ptr_ThreeByteValue_46) {

    const char data[] = {0xFE, 0xFF, 0x01}; // Three byte value 16382

    const char* result = GetVarint32Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, data + 3);

    EXPECT_EQ(value, 16382U);

}



TEST_F(CodingTest_46, GetVarint32Ptr_FourByteValue_46) {

    const char data[] = {0xFF, 0xFF, 0xFF, 0x01}; // Four byte value 2097151

    const char* result = GetVarint32Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, data + 4);

    EXPECT_EQ(value, 2097151U);

}



TEST_F(CodingTest_46, GetVarint32Ptr_FiveByteValue_46) {

    const char data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x0F}; // Five byte value 268435455

    const char* result = GetVarint32Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, data + 5);

    EXPECT_EQ(value, 268435455U);

}



TEST_F(CodingTest_46, GetVarint32Ptr_OutOfBoundsSingleByte_46) {

    const char data[] = {0x1A}; // Single byte value 26

    const char* result = GetVarint32Ptr(data, data, &value);

    EXPECT_EQ(result, data + 0);

}



TEST_F(CodingTest_46, GetVarint32Ptr_OutOfBoundsTwoByte_46) {

    const char data[] = {0x8E}; // Incomplete two byte value

    const char* result = GetVarint32Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, data + 1); // Should not read past the boundary

}



TEST_F(CodingTest_46, GetVarint32Ptr_OutOfBoundsThreeByte_46) {

    const char data[] = {0xFE}; // Incomplete three byte value

    const char* result = GetVarint32Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, data + 1); // Should not read past the boundary

}



TEST_F(CodingTest_46, GetVarint32Ptr_OutOfBoundsFourByte_46) {

    const char data[] = {0xFF}; // Incomplete four byte value

    const char* result = GetVarint32Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, data + 1); // Should not read past the boundary

}



TEST_F(CodingTest_46, GetVarint32Ptr_OutOfBoundsFiveByte_46) {

    const char data[] = {0xFF}; // Incomplete five byte value

    const char* result = GetVarint32Ptr(data, data + sizeof(data), &value);

    EXPECT_EQ(result, data + 1); // Should not read past the boundary

}



}  // namespace leveldb
