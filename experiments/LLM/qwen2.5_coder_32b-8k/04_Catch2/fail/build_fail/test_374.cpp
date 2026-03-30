#include <gtest/gtest.h>

#include "catch_clara.hpp"



using namespace Catch::Clara::Detail;



TEST_F(ConvertIntoTest_374, ConvertValidStringToInt_374) {

    int target = 0;

    std::string source = "123";

    auto result = convertInto(source, target);

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_EQ(target, 123);

}



TEST_F(ConvertIntoTest_374, ConvertValidStringToDouble_374) {

    double target = 0.0;

    std::string source = "123.45";

    auto result = convertInto(source, target);

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_DOUBLE_EQ(target, 123.45);

}



TEST_F(ConvertIntoTest_374, ConvertInvalidStringToInt_374) {

    int target = 0;

    std::string source = "abc";

    auto result = convertInto(source, target);

    EXPECT_FALSE(static_cast<bool>(result));

    EXPECT_EQ(result.errorMessage(), "Unable to convert 'abc' to destination type");

}



TEST_F(ConvertIntoTest_374, ConvertEmptyStringToInt_374) {

    int target = 0;

    std::string source = "";

    auto result = convertInto(source, target);

    EXPECT_FALSE(static_cast<bool>(result));

    EXPECT_EQ(result.errorMessage(), "Unable to convert '' to destination type");

}



TEST_F(ConvertIntoTest_374, ConvertMaxIntBoundary_374) {

    int target = 0;

    std::string source = std::to_string(std::numeric_limits<int>::max());

    auto result = convertInto(source, target);

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_EQ(target, std::numeric_limits<int>::max());

}



TEST_F(ConvertIntoTest_374, ConvertMinIntBoundary_374) {

    int target = 0;

    std::string source = std::to_string(std::numeric_limits<int>::min());

    auto result = convertInto(source, target);

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_EQ(target, std::numeric_limits<int>::min());

}



TEST_F(ConvertIntoTest_374, ConvertMaxDoubleBoundary_374) {

    double target = 0.0;

    std::string source = std::to_string(std::numeric_limits<double>::max());

    auto result = convertInto(source, target);

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_DOUBLE_EQ(target, std::numeric_limits<double>::max());

}



TEST_F(ConvertIntoTest_374, ConvertMinDoubleBoundary_374) {

    double target = 0.0;

    std::string source = std::to_string(-std::numeric_limits<double>::max());

    auto result = convertInto(source, target);

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_DOUBLE_EQ(target, -std::numeric_limits<double>::max());

}
