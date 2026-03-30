#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class ASCII85EncoderTest : public Test {

protected:

    ASCII85Encoder encoder;

};



TEST_F(ASCII85EncoderTest_217, GetPSFilter_ReturnsEmptyOptional_217) {

    int psLevel = 0;

    const char* indent = "";

    

    auto result = encoder.getPSFilter(psLevel, indent);

    

    EXPECT_FALSE(result.has_value());

}



TEST_F(ASCII85EncoderTest_217, GetPSFilter_BoundaryCondition_PsLevelZero_217) {

    int psLevel = 0;

    const char* indent = "";

    

    auto result = encoder.getPSFilter(psLevel, indent);

    

    EXPECT_FALSE(result.has_value());

}



TEST_F(ASCII85EncoderTest_217, GetPSFilter_BoundaryCondition_PsLevelMax_217) {

    int psLevel = std::numeric_limits<int>::max();

    const char* indent = "";

    

    auto result = encoder.getPSFilter(psLevel, indent);

    

    EXPECT_FALSE(result.has_value());

}



TEST_F(ASCII85EncoderTest_217, GetPSFilter_BoundaryCondition_IndentNull_217) {

    int psLevel = 0;

    const char* indent = nullptr;

    

    auto result = encoder.getPSFilter(psLevel, indent);

    

    EXPECT_FALSE(result.has_value());

}



TEST_F(ASCII85EncoderTest_217, GetPSFilter_BoundaryCondition_IndentEmpty_217) {

    int psLevel = 0;

    const char* indent = "";

    

    auto result = encoder.getPSFilter(psLevel, indent);

    

    EXPECT_FALSE(result.has_value());

}



TEST_F(ASCII85EncoderTest_217, GetPSFilter_BoundaryCondition_IndentNonEmpty_217) {

    int psLevel = 0;

    const char* indent = "    ";

    

    auto result = encoder.getPSFilter(psLevel, indent);

    

    EXPECT_FALSE(result.has_value());

}
