#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2/re2.h"

#include "_re2.cc"



using namespace re2;

using namespace re2_python;



class RE2ProgramFanoutShimTest_56 : public ::testing::Test {

protected:

    RE2 validRegex;

    RE2 invalidRegex;



    RE2ProgramFanoutShimTest_56() 

        : validRegex("a*"), invalidRegex("(") {}

};



TEST_F(RE2ProgramFanoutShimTest_56, ValidPattern_NormalOperation_56) {

    std::vector<int> histogram = RE2ProgramFanoutShim(validRegex);

    EXPECT_FALSE(histogram.empty());

}



TEST_F(RE2ProgramFanoutShimTest_56, InvalidPattern_ErrorHandling_56) {

    std::vector<int> histogram = RE2ProgramFanoutShim(invalidRegex);

    EXPECT_TRUE(histogram.empty());

}



TEST_F(RE2ProgramFanoutShimTest_56, BoundaryCondition_EmptyString_56) {

    RE2 emptyRegex("");

    std::vector<int> histogram = RE2ProgramFanoutShim(emptyRegex);

    EXPECT_FALSE(histogram.empty());

}



TEST_F(RE2ProgramFanoutShimTest_56, BoundaryCondition_SingleCharacter_56) {

    RE2 singleCharRegex("a");

    std::vector<int> histogram = RE2ProgramFanoutShim(singleCharRegex);

    EXPECT_FALSE(histogram.empty());

}



TEST_F(RE2ProgramFanoutShimTest_56, BoundaryCondition_MultipleCharacters_56) {

    RE2 multipleCharsRegex("abc");

    std::vector<int> histogram = RE2ProgramFanoutShim(multipleCharsRegex);

    EXPECT_FALSE(histogram.empty());

}



TEST_F(RE2ProgramFanoutShimTest_56, BoundaryCondition_SpecialCharacters_56) {

    RE2 specialCharsRegex("[a-z]+");

    std::vector<int> histogram = RE2ProgramFanoutShim(specialCharsRegex);

    EXPECT_FALSE(histogram.empty());

}
