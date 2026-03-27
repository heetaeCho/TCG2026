#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "explanations.h"

#include <vector>

#include <string>



using ::testing::_;

using ::testing::ElementsAre;



class ExplanationsTest : public ::testing::Test {

protected:

    Explanations explanations;

};



TEST_F(ExplanationsTest_14, LookupAndAppend_EmptyMap_NoOutput_14) {

    std::vector<std::string> output;

    const void* item = reinterpret_cast<const void*>(0x123);

    explanations.LookupAndAppend(item, &output);

    EXPECT_TRUE(output.empty());

}



TEST_F(ExplanationsTest_14, LookupAndAppend_ItemNotFound_NoOutput_14) {

    std::vector<std::string> output;

    const void* item = reinterpret_cast<const void*>(0x123);

    explanations.Record(item, "Explanation for 0x123");

    explanations.LookupAndAppend(reinterpret_cast<const void*>(0x456), &output);

    EXPECT_TRUE(output.empty());

}



TEST_F(ExplanationsTest_14, LookupAndAppend_ItemFound_SingleExplanation_OutputContainsExplanation_14) {

    std::vector<std::string> output;

    const void* item = reinterpret_cast<const void*>(0x123);

    explanations.Record(item, "Explanation for 0x123");

    explanations.LookupAndAppend(item, &output);

    EXPECT_THAT(output, ElementsAre("Explanation for 0x123"));

}



TEST_F(ExplanationsTest_14, LookupAndAppend_ItemFound_MultipleExplanations_OutputContainsAllExplanations_14) {

    std::vector<std::string> output;

    const void* item = reinterpret_cast<const void*>(0x123);

    explanations.Record(item, "Explanation 1 for 0x123");

    explanations.Record(item, "Explanation 2 for 0x123");

    explanations.LookupAndAppend(item, &output);

    EXPECT_THAT(output, ElementsAre("Explanation 1 for 0x123", "Explanation 2 for 0x123"));

}



TEST_F(ExplanationsTest_14, LookupAndAppend_ItemFound_EmptyStringExplanation_OutputContainsEmptyString_14) {

    std::vector<std::string> output;

    const void* item = reinterpret_cast<const void*>(0x123);

    explanations.Record(item, "");

    explanations.LookupAndAppend(item, &output);

    EXPECT_THAT(output, ElementsAre(""));

}
