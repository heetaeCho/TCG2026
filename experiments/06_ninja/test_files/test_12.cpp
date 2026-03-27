#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "explanations.h"



class ExplanationsTest : public ::testing::Test {

protected:

    Explanations explanations_;

};



TEST_F(ExplanationsTest_12, RecordNormalOperation_12) {

    const void* item = reinterpret_cast<const void*>(0x1);

    explanations_.Record(item, "Explanation for %d", 42);



    std::vector<std::string> result;

    explanations_.LookupAndAppend(item, &result);



    EXPECT_EQ(result.size(), 1);

    EXPECT_THAT(result[0], ::testing::HasSubstr("Explanation for 42"));

}



TEST_F(ExplanationsTest_12, RecordMultipleTimes_12) {

    const void* item = reinterpret_cast<const void*>(0x1);

    explanations_.Record(item, "First explanation");

    explanations_.Record(item, "Second explanation");



    std::vector<std::string> result;

    explanations_.LookupAndAppend(item, &result);



    EXPECT_EQ(result.size(), 2);

    EXPECT_EQ(result[0], "First explanation");

    EXPECT_EQ(result[1], "Second explanation");

}



TEST_F(ExplanationsTest_12, RecordBoundaryConditionEmptyString_12) {

    const void* item = reinterpret_cast<const void*>(0x1);

    explanations_.Record(item, "");



    std::vector<std::string> result;

    explanations_.LookupAndAppend(item, &result);



    EXPECT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], "");

}



TEST_F(ExplanationsTest_12, RecordBoundaryConditionNullPointer_12) {

    const void* item = nullptr;

    explanations_.Record(item, "Explanation for null");



    std::vector<std::string> result;

    explanations_.LookupAndAppend(item, &result);



    EXPECT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], "Explanation for null");

}



TEST_F(ExplanationsTest_12, RecordBoundaryConditionLongString_12) {

    const void* item = reinterpret_cast<const void*>(0x1);

    explanations_.Record(item, "A very long explanation that goes on and on to test the boundary conditions of the Record function in the Explanations class.");



    std::vector<std::string> result;

    explanations_.LookupAndAppend(item, &result);



    EXPECT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], "A very long explanation that goes on and on to test the boundary conditions of the Record function in the Explanations class.");

}
