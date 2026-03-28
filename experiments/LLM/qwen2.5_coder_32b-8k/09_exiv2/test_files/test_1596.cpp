#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



namespace {



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest : public ::testing::Test {

protected:

    Value value;

    ExifData metadata;

    std::ostringstream os;



    void SetUp() override {

        // Initialize the value with a default type and data

        value = Value(unsignedByte);

        value.setDataArea(reinterpret_cast<const byte*>("\x01"), 1); // Example data

    }

};



TEST_F(SonyMakerNoteTest_1596, NormalOperation_SLT_Model_1596) {

    metadata["Exif.Image.Model"] = "SLT-A7";

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "Center");

}



TEST_F(SonyMakerNoteTest_1596, NormalOperation_HV_Model_1596) {

    metadata["Exif.Image.Model"] = "HV-1";

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "Center");

}



TEST_F(SonyMakerNoteTest_1596, NormalOperation_ILCE_Model_AFModeSetting4_1596) {

    metadata["Exif.Image.Model"] = "ILCE-7";

    metadata["Exif.Sony.AFAreaModeSetting"] = Value(unsignedLong);

    metadata["Exif.Sony.AFAreaModeSetting"].setDataArea(reinterpret_cast<const byte*>("\x04"), 1); // AF Mode Setting = 4

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "Center");

}



TEST_F(SonyMakerNoteTest_1596, NormalOperation_ILME_Model_AFModeSetting4_1596) {

    metadata["Exif.Image.Model"] = "ILME-7";

    metadata["Exif.Sony.AFAreaModeSetting"] = Value(unsignedLong);

    metadata["Exif.Sony.AFAreaModeSetting"].setDataArea(reinterpret_cast<const byte*>("\x04"), 1); // AF Mode Setting = 4

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "Center");

}



TEST_F(SonyMakerNoteTest_1596, NormalOperation_ILCA_Model_AFModeSettingNot8_1596) {

    metadata["Exif.Image.Model"] = "ILCA-68";

    metadata["Exif.Sony.AFAreaModeSetting"] = Value(unsignedLong);

    metadata["Exif.Sony.AFAreaModeSetting"].setDataArea(reinterpret_cast<const byte*>("\x02"), 1); // AF Mode Setting != 8

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "A6");

}



TEST_F(SonyMakerNoteTest_1596, NormalOperation_ILCA_Model_AFModeSettingNot8_SpecificModel_1596) {

    metadata["Exif.Image.Model"] = "ILCA-77M2";

    metadata["Exif.Sony.AFAreaModeSetting"] = Value(unsignedLong);

    metadata["Exif.Sony.AFAreaModeSetting"].setDataArea(reinterpret_cast<const byte*>("\x03"), 1); // AF Mode Setting != 8

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "A7");

}



TEST_F(SonyMakerNoteTest_1596, NormalOperation_ILCA_Model_AFModeSettingNot8_AnotherSpecificModel_1596) {

    metadata["Exif.Image.Model"] = "ILCA-99M2";

    metadata["Exif.Sony.AFAreaModeSetting"] = Value(unsignedLong);

    metadata["Exif.Sony.AFAreaModeSetting"].setDataArea(reinterpret_cast<const byte*>("\x04"), 1); // AF Mode Setting != 8

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "A5");

}



TEST_F(SonyMakerNoteTest_1596, NormalOperation_ILCA_Model_AFModeSetting8_1596) {

    metadata["Exif.Image.Model"] = "ILCA-7R";

    metadata["Exif.Sony.AFAreaModeSetting"] = Value(unsignedLong);

    metadata["Exif.Sony.AFAreaModeSetting"].setDataArea(reinterpret_cast<const byte*>("\x08"), 1); // AF Mode Setting == 8

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "Center Zone");

}



TEST_F(SonyMakerNoteTest_1596, NormalOperation_NEX_Model_1596) {

    metadata["Exif.Image.Model"] = "NEX-7";

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "Center");

}



TEST_F(SonyMakerNoteTest_1596, NormalOperation_ILCE_Model_1596) {

    metadata["Exif.Image.Model"] = "ILCE-7";

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "Center");

}



TEST_F(SonyMakerNoteTest_1596, NormalOperation_ILME_Model_1596) {

    metadata["Exif.Image.Model"] = "ILME-7";

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "Center");

}



TEST_F(SonyMakerNoteTest_1596, InvalidModel_1596) {

    metadata["Exif.Image.Model"] = "UnknownModel";

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "(1)");

}



TEST_F(SonyMakerNoteTest_1596, InvalidValueCount_1596) {

    metadata["Exif.Image.Model"] = "SLT-A7";

    value.setDataArea(reinterpret_cast<const byte*>("\x01\x02"), 2); // Two bytes instead of one

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "(1 2)");

}



TEST_F(SonyMakerNoteTest_1596, InvalidValueType_1596) {

    metadata["Exif.Image.Model"] = "SLT-A7";

    value = Value(asciiString); // Wrong type

    value.setDataArea(reinterpret_cast<const byte*>("A"), 1);

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "(A)");

}



TEST_F(SonyMakerNoteTest_1596, NullMetadata_1596) {

    metadata["Exif.Image.Model"] = "SLT-A7";

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, nullptr);

    EXPECT_EQ(os.str(), "(1)");

}



TEST_F(SonyMakerNoteTest_1596, MissingModelKey_1596) {

    os.str("");

    SonyMakerNote::printAFPointSelected(os, value, &metadata);

    EXPECT_EQ(os.str(), "(1)");

}



} // namespace
