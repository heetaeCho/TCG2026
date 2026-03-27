#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "types.cpp"  // Assuming the implementation is in the same file or linked



namespace Exiv2 {

    uint32_t parseUint32(const std::string& s, bool& ok);

}



class ParseUint32Test_1158 : public ::testing::Test {

protected:

    bool status;

};



TEST_F(ParseUint32Test_1158, ValidInputWithinRange_1158) {

    std::string input = "12345";

    uint32_t result = Exiv2::parseUint32(input, status);

    EXPECT_TRUE(status);

    EXPECT_EQ(result, 12345U);

}



TEST_F(ParseUint32Test_1158, ValidInputMaxValue_1158) {

    std::string input = "4294967295";

    uint32_t result = Exiv2::parseUint32(input, status);

    EXPECT_TRUE(status);

    EXPECT_EQ(result, 4294967295U);

}



TEST_F(ParseUint32Test_1158, ValidInputMinValue_1158) {

    std::string input = "0";

    uint32_t result = Exiv2::parseUint32(input, status);

    EXPECT_TRUE(status);

    EXPECT_EQ(result, 0U);

}



TEST_F(ParseUint32Test_1158, InvalidInputNegativeNumber_1158) {

    std::string input = "-1";

    uint32_t result = Exiv2::parseUint32(input, status);

    EXPECT_FALSE(status);

    EXPECT_EQ(result, 0U);

}



TEST_F(ParseUint32Test_1158, InvalidInputExceedingMaxValue_1158) {

    std::string input = "4294967296";

    uint32_t result = Exiv2::parseUint32(input, status);

    EXPECT_FALSE(status);

    EXPECT_EQ(result, 0U);

}



TEST_F(ParseUint32Test_1158, InvalidInputNonNumeric_1158) {

    std::string input = "abc";

    uint32_t result = Exiv2::parseUint32(input, status);

    EXPECT_FALSE(status);

    EXPECT_EQ(result, 0U);

}



TEST_F(ParseUint32Test_1158, InvalidInputEmptyString_1158) {

    std::string input = "";

    uint32_t result = Exiv2::parseUint32(input, status);

    EXPECT_FALSE(status);

    EXPECT_EQ(result, 0U);

}
