#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "explanations.h"



using ::testing::_;

using ::testing::ElementsAre;



class ExplanationsTest : public ::testing::Test {

protected:

    Explanations explanations;

};



TEST_F(ExplanationsTest_13, RecordSingleArgument_13) {

    const void* item = reinterpret_cast<const void*>(0x1);

    explanations.Record(item, "test %d", 42);



    std::vector<std::string> result;

    explanations.LookupAndAppend(item, &result);



    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], "test 42");

}



TEST_F(ExplanationsTest_13, RecordMultipleArguments_13) {

    const void* item = reinterpret_cast<const void*>(0x2);

    explanations.Record(item, "value %d - %s", 100, "example");



    std::vector<std::string> result;

    explanations.LookupAndAppend(item, &result);



    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], "value 100 - example");

}



TEST_F(ExplanationsTest_13, RecordMultipleCallsSameItem_13) {

    const void* item = reinterpret_cast<const void*>(0x3);

    explanations.Record(item, "first call");

    explanations.Record(item, "second call");



    std::vector<std::string> result;

    explanations.LookupAndAppend(item, &result);



    ASSERT_EQ(result.size(), 2);

    EXPECT_THAT(result, ElementsAre("first call", "second call"));

}



TEST_F(ExplanationsTest_13, RecordMultipleItems_13) {

    const void* item1 = reinterpret_cast<const void*>(0x4);

    const void* item2 = reinterpret_cast<const void*>(0x5);



    explanations.Record(item1, "item1");

    explanations.Record(item2, "item2");



    std::vector<std::string> result1;

    explanations.LookupAndAppend(item1, &result1);

    ASSERT_EQ(result1.size(), 1);

    EXPECT_EQ(result1[0], "item1");



    std::vector<std::string> result2;

    explanations.LookupAndAppend(item2, &result2);

    ASSERT_EQ(result2.size(), 1);

    EXPECT_EQ(result2[0], "item2");

}



TEST_F(ExplanationsTest_13, LookupNonExistingItem_13) {

    const void* item = reinterpret_cast<const void*>(0x6);



    std::vector<std::string> result;

    explanations.LookupAndAppend(item, &result);



    EXPECT_TRUE(result.empty());

}



TEST_F(ExplanationsTest_13, RecordEmptyString_13) {

    const void* item = reinterpret_cast<const void*>(0x7);

    explanations.Record(item, "");



    std::vector<std::string> result;

    explanations.LookupAndAppend(item, &result);



    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], "");

}



TEST_F(ExplanationsTest_13, RecordLargeString_13) {

    const void* item = reinterpret_cast<const void*>(0x8);

    std::string large_string(512, 'a'); // Large string that fits within buffer

    explanations.Record(item, "%s", large_string.c_str());



    std::vector<std::string> result;

    explanations.LookupAndAppend(item, &result);



    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], large_string);

}



TEST_F(ExplanationsTest_13, RecordStringLongerThanBuffer_13) {

    const void* item = reinterpret_cast<const void*>(0x9);

    std::string long_string(2048, 'b'); // String longer than buffer

    explanations.Record(item, "%s", long_string.c_str());



    std::vector<std::string> result;

    explanations.LookupAndAppend(item, &result);



    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], std::string(1023, 'b')); // Truncated to buffer size minus null terminator

}
