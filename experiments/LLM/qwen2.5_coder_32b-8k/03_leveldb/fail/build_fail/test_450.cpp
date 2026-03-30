#include <gtest/gtest.h>

#include "leveldb/slice.h"

#include "util/coding.cc"



namespace {



class GetLengthPrefixedSliceTest : public ::testing::Test {

protected:

    leveldb::Slice input;

    leveldb::Slice result;



    void SetUp() override {

        // Common setup code if needed

    }

};



TEST_F(GetLengthPrefixedSliceTest_450, NormalOperation_450) {

    const char data[] = "\x03foo";

    input = leveldb::Slice(data, sizeof(data));

    bool success = leveldb::GetLengthPrefixedSlice(&input, &result);

    EXPECT_TRUE(success);

    EXPECT_EQ("foo", result.ToString());

    EXPECT_EQ(0, input.size());

}



TEST_F(GetLengthPrefixedSliceTest_450, EmptyInput_450) {

    const char data[] = "";

    input = leveldb::Slice(data, sizeof(data) - 1);

    bool success = leveldb::GetLengthPrefixedSlice(&input, &result);

    EXPECT_FALSE(success);

}



TEST_F(GetLengthPrefixedSliceTest_450, InsufficientData_450) {

    const char data[] = "\x03fo";

    input = leveldb::Slice(data, sizeof(data));

    bool success = leveldb::GetLengthPrefixedSlice(&input, &result);

    EXPECT_FALSE(success);

}



TEST_F(GetLengthPrefixedSliceTest_450, ZeroLengthPrefix_450) {

    const char data[] = "\x00";

    input = leveldb::Slice(data, sizeof(data));

    bool success = leveldb::GetLengthPrefixedSlice(&input, &result);

    EXPECT_TRUE(success);

    EXPECT_EQ("", result.ToString());

    EXPECT_EQ(0, input.size());

}



TEST_F(GetLengthPrefixedSliceTest_450, LargeLengthPrefix_450) {

    const char data[] = "\x83\x01foo";  // Varint for 259

    input = leveldb::Slice(data, sizeof(data));

    bool success = leveldb::GetLengthPrefixedSlice(&input, &result);

    EXPECT_FALSE(success);  // Assuming the input buffer is not large enough to hold 259 bytes of data

}



}  // namespace
