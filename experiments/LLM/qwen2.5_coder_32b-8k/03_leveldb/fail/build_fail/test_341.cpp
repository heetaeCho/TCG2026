#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_edit.cc"

#include "leveldb/slice.h"



namespace leveldb {



class GetLevelTest_341 : public ::testing::Test {

protected:

    Slice input;

    int level;



    bool CallGetLevel(const std::string& data) {

        input = Slice(data);

        return GetLevel(&input, &level);

    }

};



TEST_F(GetLevelTest_341, ValidInputWithinRange_341) {

    EXPECT_TRUE(CallGetLevel("\x02"));  // Example of valid varint encoding for level 2

    EXPECT_EQ(level, 2);

}



TEST_F(GetLevelTest_341, ValidInputAtLowerBoundary_341) {

    EXPECT_TRUE(CallGetLevel("\x00"));  // Example of valid varint encoding for level 0

    EXPECT_EQ(level, 0);

}



TEST_F(GetLevelTest_341, ValidInputAtUpperBoundary_341) {

    EXPECT_TRUE(CallGetLevel("\x06"));  // Example of valid varint encoding for level 6 (kNumLevels - 1)

    EXPECT_EQ(level, 6);

}



TEST_F(GetLevelTest_341, InputExceedsUpperBoundary_341) {

    EXPECT_FALSE(CallGetLevel("\x07"));  // Example of invalid varint encoding for level 7

}



TEST_F(GetLevelTest_341, EmptyInput_341) {

    EXPECT_FALSE(CallGetLevel(""));  // No data to decode

}



TEST_F(GetLevelTest_341, InvalidVarintEncoding_341) {

    EXPECT_FALSE(CallGetLevel("\x80\x80\x80\x80\x07"));  // Malformed varint encoding

}



TEST_F(GetLevelTest_341, PartialVarintInput_341) {

    EXPECT_FALSE(CallGetLevel("\x80\x01"));  // Incomplete varint sequence

}



}  // namespace leveldb
