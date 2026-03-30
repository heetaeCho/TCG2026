#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"

#include <optional>

#include <string>



using namespace testing;



class ASCIIHexEncoderTest_211 : public ::testing::Test {

protected:

    std::unique_ptr<ASCIIHexEncoder> encoder;



    void SetUp() override {

        encoder = std::make_unique<ASCIIHexEncoder>();

    }

};



TEST_F(ASCIIHexEncoderTest_211, GetPSFilter_ReturnsEmptyOptional_211) {

    int psLevel = 0;

    const char* indent = "";



    auto result = encoder->getPSFilter(psLevel, indent);



    EXPECT_FALSE(result.has_value());

}



TEST_F(ASCIIHexEncoderTest_211, GetPSFilter_BoundaryConditionPsLevelZero_211) {

    int psLevel = 0;

    const char* indent = "  ";



    auto result = encoder->getPSFilter(psLevel, indent);



    EXPECT_FALSE(result.has_value());

}



TEST_F(ASCIIHexEncoderTest_211, GetPSFilter_BoundaryConditionPsLevelPositive_211) {

    int psLevel = 3;

    const char* indent = "";



    auto result = encoder->getPSFilter(psLevel, indent);



    EXPECT_FALSE(result.has_value());

}



TEST_F(ASCIIHexEncoderTest_211, GetPSFilter_BoundaryConditionNullIndent_211) {

    int psLevel = 0;

    const char* indent = nullptr;



    auto result = encoder->getPSFilter(psLevel, indent);



    EXPECT_FALSE(result.has_value());

}
