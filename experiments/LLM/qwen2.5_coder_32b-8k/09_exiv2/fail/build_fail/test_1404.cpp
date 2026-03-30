#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace testing;



class Print0x9207Test_1404 : public ::testing::Test {

protected:

    Internal::TagDetails exifMeteringMode[8] = {{0, "Unknown"}, {1, "Average"}, {2, "Center weighted average"},

                                              {3, "Spot"}, {4, "Multi-spot"}, {5, "Multi-segment"},

                                              {6, "Partial"}, {255, "Other"}};

    ExifData metadata;

    Value value;



    Print0x9207Test_1404() : value(TypeId::asciiString) {}

};



TEST_F(Print0x9207Test_1404, NormalOperation_1404) {

    std::ostringstream os;

    EXPECT_CALL(value, toString()).WillOnce(Return("Average"));

    Internal::print0x9207(os, value, &metadata);

    EXPECT_EQ(os.str(), "Average");

}



TEST_F(Print0x9207Test_1404, BoundaryCondition_EmptyValue_1404) {

    std::ostringstream os;

    EXPECT_CALL(value, toString()).WillOnce(Return(""));

    Internal::print0x9207(os, value, &metadata);

    EXPECT_EQ(os.str(), "");

}



TEST_F(Print0x9207Test_1404, BoundaryCondition_UnknownValue_1404) {

    std::ostringstream os;

    EXPECT_CALL(value, toString()).WillOnce(Return("Unknown"));

    Internal::print0x9207(os, value, &metadata);

    EXPECT_EQ(os.str(), "Unknown");

}



TEST_F(Print0x9207Test_1404, ExceptionalCase_ValueNotSet_1404) {

    std::ostringstream os;

    EXPECT_CALL(value, toString()).WillOnce(Return("Invalid"));

    Internal::print0x9207(os, value, &metadata);

    EXPECT_EQ(os.str(), "Invalid");

}



TEST_F(Print0x9207Test_1404, ExternalInteraction_MetadataPassed_1404) {

    std::ostringstream os;

    EXPECT_CALL(value, toString()).WillOnce(Return("Average"));

    Internal::print0x9207(os, value, &metadata);

    EXPECT_EQ(os.str(), "Average");

}
