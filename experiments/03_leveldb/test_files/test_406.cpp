#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "table/block.cc"  // Assuming DecodeEntry is in this file or included properly



namespace leveldb {



class DecodeEntryTest_406 : public ::testing::Test {

protected:

    uint32_t shared;

    uint32_t non_shared;

    uint32_t value_length;

};



TEST_F(DecodeEntryTest_406, NormalOperation_SmallValues_406) {

    const char data[] = {1, 2, 3}; // small values for shared, non_shared, and value_length

    const char* result = DecodeEntry(data, data + sizeof(data), &shared, &non_shared, &value_length);

    EXPECT_EQ(result, data + 3);

    EXPECT_EQ(shared, 1);

    EXPECT_EQ(non_shared, 2);

    EXPECT_EQ(value_length, 3);

}



TEST_F(DecodeEntryTest_406, NormalOperation_LargeValues_406) {

    const char data[] = {128, 1, 0, 129, 2, 0, 130, 3, 0}; // varint representation for shared, non_shared, and value_length

    const char* result = DecodeEntry(data, data + sizeof(data), &shared, &non_shared, &value_length);

    EXPECT_EQ(result, data + 9);

    EXPECT_EQ(shared, 128);

    EXPECT_EQ(non_shared, 129);

    EXPECT_EQ(value_length, 130);

}



TEST_F(DecodeEntryTest_406, BoundaryCondition_MinimumSize_406) {

    const char data[] = {1, 1, 1}; // minimum size input

    const char* result = DecodeEntry(data, data + sizeof(data), &shared, &non_shared, &value_length);

    EXPECT_EQ(result, data + 3);

    EXPECT_EQ(shared, 1);

    EXPECT_EQ(non_shared, 1);

    EXPECT_EQ(value_length, 1);

}



TEST_F(DecodeEntryTest_406, BoundaryCondition_ExactlyEnoughSpace_406) {

    const char data[] = {128, 1, 0, 1, 1, 1}; // varint representation with exactly enough space

    const char* result = DecodeEntry(data, data + sizeof(data), &shared, &non_shared, &value_length);

    EXPECT_EQ(result, data + 6);

    EXPECT_EQ(shared, 128);

    EXPECT_EQ(non_shared, 1);

    EXPECT_EQ(value_length, 1);

}



TEST_F(DecodeEntryTest_406, ErrorCase_NotEnoughDataForHeader_406) {

    const char data[] = {1}; // not enough data for header

    const char* result = DecodeEntry(data, data + sizeof(data), &shared, &non_shared, &value_length);

    EXPECT_EQ(result, nullptr);

}



TEST_F(DecodeEntryTest_406, ErrorCase_NotEnoughDataForVarint_406) {

    const char data[] = {128}; // start of varint but not enough data

    const char* result = DecodeEntry(data, data + sizeof(data), &shared, &non_shared, &value_length);

    EXPECT_EQ(result, nullptr);

}



TEST_F(DecodeEntryTest_406, ErrorCase_NotEnoughDataForValues_406) {

    const char data[] = {128, 1, 0, 129, 2, 0}; // varint representation but not enough data for values

    const char* result = DecodeEntry(data, data + sizeof(data), &shared, &non_shared, &value_length);

    EXPECT_EQ(result, nullptr);

}



}  // namespace leveldb
