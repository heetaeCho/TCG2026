#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_reporter_spec_parser.cpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using namespace Catch::Detail;



class StringRefToStringConverterTest : public ::testing::Test {

protected:

    Optional<ColourMode> result;

};



TEST_F(StringRefToStringConverterTest_NormalOperation_689, ConvertsDefaultToPlatformDefault_689) {

    result = stringToColourMode("default");

    ASSERT_TRUE(result);

    EXPECT_EQ(*result, ColourMode::PlatformDefault);

}



TEST_F(StringRefToStringConverterTest_NormalOperation_689, ConvertsAnsiToANSI_689) {

    result = stringToColourMode("ansi");

    ASSERT_TRUE(result);

    EXPECT_EQ(*result, ColourMode::ANSI);

}



TEST_F(StringRefToStringConverterTest_NormalOperation_689, ConvertsWin32ToWin32_689) {

    result = stringToColourMode("win32");

    ASSERT_TRUE(result);

    EXPECT_EQ(*result, ColourMode::Win32);

}



TEST_F(StringRefToStringConverterTest_NormalOperation_689, ConvertsNoneToNone_689) {

    result = stringToColourMode("none");

    ASSERT_TRUE(result);

    EXPECT_EQ(*result, ColourMode::None);

}



TEST_F(StringRefToStringConverterTest_BoundaryConditions_689, EmptyStringReturnsEmptyOptional_689) {

    result = stringToColourMode("");

    EXPECT_FALSE(result);

}



TEST_F(StringRefToStringConverterTest_ErrorCases_689, InvalidStringReturnsEmptyOptional_689) {

    result = stringToColourMode("invalid");

    EXPECT_FALSE(result);

}
