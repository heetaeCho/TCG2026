#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/FlateEncoder.h"

#include <optional>



class FlateEncoderTest_1652 : public ::testing::Test {

protected:

    FlateEncoder encoder;

};



TEST_F(FlateEncoderTest_1652, GetPSFilter_ReturnsEmptyOptional_1652) {

    int psLevel = 0; // Example value for psLevel

    const char* indent = ""; // Example value for indent



    std::optional<std::string> result = encoder.getPSFilter(psLevel, indent);



    EXPECT_FALSE(result.has_value());

}



TEST_F(FlateEncoderTest_1652, GetPSFilter_BoundaryCondition_PsLevelZero_1652) {

    int psLevel = 0;

    const char* indent = "";



    std::optional<std::string> result = encoder.getPSFilter(psLevel, indent);



    EXPECT_FALSE(result.has_value());

}



TEST_F(FlateEncoderTest_1652, GetPSFilter_BoundaryCondition_PsLevelNegative_1652) {

    int psLevel = -1;

    const char* indent = "";



    std::optional<std::string> result = encoder.getPSFilter(psLevel, indent);



    EXPECT_FALSE(result.has_value());

}



TEST_F(FlateEncoderTest_1652, GetPSFilter_BoundaryCondition_PsLevelPositive_1652) {

    int psLevel = 1;

    const char* indent = "";



    std::optional<std::string> result = encoder.getPSFilter(psLevel, indent);



    EXPECT_FALSE(result.has_value());

}



TEST_F(FlateEncoderTest_1652, GetPSFilter_BoundaryCondition_EmptyIndent_1652) {

    int psLevel = 0;

    const char* indent = "";



    std::optional<std::string> result = encoder.getPSFilter(psLevel, indent);



    EXPECT_FALSE(result.has_value());

}



TEST_F(FlateEncoderTest_1652, GetPSFilter_BoundaryCondition_NonEmptyIndent_1652) {

    int psLevel = 0;

    const char* indent = "  ";



    std::optional<std::string> result = encoder.getPSFilter(psLevel, indent);



    EXPECT_FALSE(result.has_value());

}
