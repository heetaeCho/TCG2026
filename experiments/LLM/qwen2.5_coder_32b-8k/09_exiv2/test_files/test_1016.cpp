#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/minoltamn_int.cpp"

#include <vector>

#include <string>



using namespace Exiv2::Internal;



TEST(SplitFunctionTest_1016, NormalOperation_SingleDelimiter_1016) {

    std::string str = "apple,banana,cherry";

    std::string delim = ",";

    std::vector<std::string> expected = {"apple", "banana", "cherry"};

    EXPECT_EQ(split(str, delim), expected);

}



TEST(SplitFunctionTest_1016, NormalOperation_MultipleDelimiters_1016) {

    std::string str = "one,two,,three";

    std::string delim = ",";

    std::vector<std::string> expected = {"one", "two", "three"};

    EXPECT_EQ(split(str, delim), expected);

}



TEST(SplitFunctionTest_1016, BoundaryCondition_EmptyString_1016) {

    std::string str = "";

    std::string delim = ",";

    std::vector<std::string> expected = {};

    EXPECT_EQ(split(str, delim), expected);

}



TEST(SplitFunctionTest_1016, BoundaryCondition_StringWithoutDelimiter_1016) {

    std::string str = "abcdef";

    std::string delim = ",";

    std::vector<std::string> expected = {"abcdef"};

    EXPECT_EQ(split(str, delim), expected);

}



TEST(SplitFunctionTest_1016, BoundaryCondition_DelimiterOnlyString_1016) {

    std::string str = ",,,,";

    std::string delim = ",";

    std::vector<std::string> expected = {};

    EXPECT_EQ(split(str, delim), expected);

}



TEST(SplitFunctionTest_1016, ExceptionalCase_EmptyDelimiter_1016) {

    std::string str = "a,b,c,d";

    std::string delim = "";

    // This case is undefined behavior in the provided function as it will enter an infinite loop.

    // For testing purposes, we assume that an empty delimiter is not valid and should return the original string.

    std::vector<std::string> expected = {"a,b,c,d"};

    EXPECT_EQ(split(str, delim), expected);

}
