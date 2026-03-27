#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exif.hpp>

#include <exiv2/value.hpp>

#include "tags_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Print0xa406Test_1416 : public ::testing::Test {

protected:

    Value value;

    ExifData metadata;



    Print0xa406Test_1416() : value(TypeId::unsignedShort) {}

};



TEST_F(Print0xa406Test_1416, StandardSceneCaptureType_1416) {

    unsigned short standardValue = 0;

    value.setDataArea(reinterpret_cast<const byte*>(&standardValue), sizeof(standardValue));

    std::ostringstream os;

    print0xa406(os, value, &metadata);

    EXPECT_EQ("Standard\n", os.str());

}



TEST_F(Print0xa406Test_1416, LandscapeSceneCaptureType_1416) {

    unsigned short landscapeValue = 1;

    value.setDataArea(reinterpret_cast<const byte*>(&landscapeValue), sizeof(landscapeValue));

    std::ostringstream os;

    print0xa406(os, value, &metadata);

    EXPECT_EQ("Landscape\n", os.str());

}



TEST_F(Print0xa406Test_1416, PortraitSceneCaptureType_1416) {

    unsigned short portraitValue = 2;

    value.setDataArea(reinterpret_cast<const byte*>(&portraitValue), sizeof(portraitValue));

    std::ostringstream os;

    print0xa406(os, value, &metadata);

    EXPECT_EQ("Portrait\n", os.str());

}



TEST_F(Print0xa406Test_1416, NightSceneCaptureType_1416) {

    unsigned short nightValue = 3;

    value.setDataArea(reinterpret_cast<const byte*>(&nightValue), sizeof(nightValue));

    std::ostringstream os;

    print0xa406(os, value, &metadata);

    EXPECT_EQ("Night scene\n", os.str());

}



TEST_F(Print0xa406Test_1416, UnknownSceneCaptureType_1416) {

    unsigned short unknownValue = 99; // Assuming 99 is not a valid Scene Capture Type

    value.setDataArea(reinterpret_cast<const byte*>(&unknownValue), sizeof(unknownValue));

    std::ostringstream os;

    print0xa406(os, value, &metadata);

    EXPECT_EQ("Unknown scene capture type (99)\n", os.str());

}



TEST_F(Print0xa406Test_1416, InvalidDataSize_1416) {

    unsigned short validValue = 0;

    value.setDataArea(reinterpret_cast<const byte*>(&validValue), sizeof(validValue) - 1); // Simulate invalid size

    std::ostringstream os;

    print0xa406(os, value, &metadata);

    EXPECT_EQ("(Invalid data)\n", os.str());

}
