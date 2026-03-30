#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>



namespace Exiv2 { namespace Internal {

    static std::string& trim(std::string& s, const char* t = " \t\n\r\f\v");

}}



using ::testing::_;

using ::testing::Eq;



class TrimFunctionTest_1015 : public ::testing::Test {};



TEST_F(TrimFunctionTest_1015, NormalOperationSingleSpace_1015) {

    std::string input = " test ";

    Exiv2::Internal::trim(input);

    EXPECT_EQ("test", input);

}



TEST_F(TrimFunctionTest_1015, NormalOperationMultipleSpaces_1015) {

    std::string input = "   test   ";

    Exiv2::Internal::trim(input);

    EXPECT_EQ("test", input);

}



TEST_F(TrimFunctionTest_1015, BoundaryConditionEmptyString_1015) {

    std::string input = "";

    Exiv2::Internal::trim(input);

    EXPECT_EQ("", input);

}



TEST_F(TrimFunctionTest_1015, BoundaryConditionOnlySpaces_1015) {

    std::string input = "     ";

    Exiv2::Internal::trim(input);

    EXPECT_EQ("", input);

}



TEST_F(TrimFunctionTest_1015, ExceptionalCaseNoLeadingOrTrailingSpaces_1015) {

    std::string input = "test";

    Exiv2::Internal::trim(input);

    EXPECT_EQ("test", input);

}



TEST_F(TrimFunctionTest_1015, NormalOperationMixedWhitespace_1015) {

    std::string input = "\t\n test \r\f\v";

    Exiv2::Internal::trim(input);

    EXPECT_EQ("test", input);

}
