#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1594 : public ::testing::Test {

protected:

    Value value;

    ExifData metadata;



    SonyMakerNoteTest_1594() : value(unsignedByte) {}

};



TEST_F(SonyMakerNoteTest_1594, InvalidValueCount_ReturnsFormattedString_1594) {

    std::ostringstream os;

    value = Value(unsignedByte);

    EXPECT_EQ("(0)", printAFAreaModeSetting(os, value, &metadata).str());

}



TEST_F(SonyMakerNoteTest_1594, InvalidValueType_ReturnsFormattedString_1594) {

    std::ostringstream os;

    value = Value(signedLong);  // Different type from unsignedByte

    EXPECT_EQ("(0)", printAFAreaModeSetting(os, value, &metadata).str());

}



TEST_F(SonyMakerNoteTest_1594, NullMetadata_ReturnsFormattedString_1594) {

    std::ostringstream os;

    EXPECT_EQ("(0)", printAFAreaModeSetting(os, value, nullptr).str());

}



TEST_F(SonyMakerNoteTest_1594, UnknownModel_ReturnsN_A_1594) {

    std::ostringstream os;

    metadata.add(ExifKey("Make"), Value::create(string));

    metadata["Make"].setValue("UnknownCamera");

    EXPECT_EQ("n/a", printAFAreaModeSetting(os, value, &metadata).str());

}



TEST_F(SonyMakerNoteTest_1594, SLT_Model_ReturnsWide_1594) {

    std::ostringstream os;

    metadata.add(ExifKey("Make"), Value::create(string));

    metadata["Make"].setValue("SLT-A6000");

    value.setDataArea(reinterpret_cast<const byte*>(&value_), 1);

    EXPECT_EQ("Wide", printAFAreaModeSetting(os, value, &metadata).str());

}



TEST_F(SonyMakerNoteTest_1594, HV_Model_ReturnsLocal_1594) {

    std::ostringstream os;

    metadata.add(ExifKey("Make"), Value::create(string));

    metadata["Make"].setValue("HV-1");

    value.setDataArea(reinterpret_cast<const byte*>(&value_), 1);

    value_ = 4; // Local

    EXPECT_EQ("Local", printAFAreaModeSetting(os, value, &metadata).str());

}



TEST_F(SonyMakerNoteTest_1594, NEX_Model_ReturnsWide_1594) {

    std::ostringstream os;

    metadata.add(ExifKey("Make"), Value::create(string));

    metadata["Make"].setValue("NEX-7");

    value.setDataArea(reinterpret_cast<const byte*>(&value_), 1);

    EXPECT_EQ("Wide", printAFAreaModeSetting(os, value, &metadata).str());

}



TEST_F(SonyMakerNoteTest_1594, ILCE_Model_ReturnsZone_1594) {

    std::ostringstream os;

    metadata.add(ExifKey("Make"), Value::create(string));

    metadata["Make"].setValue("ILCE-6000");

    value.setDataArea(reinterpret_cast<const byte*>(&value_), 1);

    value_ = 8; // Zone

    EXPECT_EQ("Zone", printAFAreaModeSetting(os, value, &metadata).str());

}



TEST_F(SonyMakerNoteTest_1594, ILCA_Model_ReturnsCenter_1594) {

    std::ostringstream os;

    metadata.add(ExifKey("Make"), Value::create(string));

    metadata["Make"].setValue("ILCA-7RM3");

    value.setDataArea(reinterpret_cast<const byte*>(&value_), 1);

    value_ = 9; // Center

    EXPECT_EQ("Center", printAFAreaModeSetting(os, value, &metadata).str());

}



TEST_F(SonyMakerNoteTest_1594, InvalidValue_ReturnsFormattedString_1594) {

    std::ostringstream os;

    metadata.add(ExifKey("Make"), Value::create(string));

    metadata["Make"].setValue("NEX-7");

    value.setDataArea(reinterpret_cast<const byte*>(&value_), 1);

    value_ = 2; // Invalid value

    EXPECT_EQ("(2)", printAFAreaModeSetting(os, value, &metadata).str());

}



uint8_t SonyMakerNoteTest_1594::value_;
