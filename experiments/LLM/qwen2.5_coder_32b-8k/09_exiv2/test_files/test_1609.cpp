#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/sonymn_int.hpp"

#include "exiv2/value.hpp"

#include "exiv2/exif.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1609 : public ::testing::Test {

protected:

    Value value;

    ExifData metadata;

    std::ostringstream os;



    SonyMakerNoteTest_1609() : value(unsignedShort) {}



    void SetUp() override {

        value.ok_ = true;  // Ensure the value is marked as valid

    }

};



TEST_F(SonyMakerNoteTest_1609, NormalOperation_AF_S_1609) {

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t(1)), sizeof(uint16_t));

    SonyMakerNote::printFocusMode(os, value, &metadata);

    EXPECT_EQ(os.str(), "AF-S");

}



TEST_F(SonyMakerNoteTest_1609, NormalOperation_AF_C_1609) {

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t(2)), sizeof(uint16_t));

    SonyMakerNote::printFocusMode(os, value, &metadata);

    EXPECT_EQ(os.str(), "AF-C");

}



TEST_F(SonyMakerNoteTest_1609, NormalOperation_Permanent_AF_1609) {

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t(4)), sizeof(uint16_t));

    SonyMakerNote::printFocusMode(os, value, &metadata);

    EXPECT_EQ(os.str(), "Permanent-AF");

}



TEST_F(SonyMakerNoteTest_1609, BoundaryCondition_MaxValue_1609) {

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t(65535)), sizeof(uint16_t));

    SonyMakerNote::printFocusMode(os, value, &metadata);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(SonyMakerNoteTest_1609, BoundaryCondition_ZeroValue_1609) {

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t(0)), sizeof(uint16_t));

    SonyMakerNote::printFocusMode(os, value, &metadata);

    EXPECT_EQ(os.str(), "(0)");

}



TEST_F(SonyMakerNoteTest_1609, BoundaryCondition_OneByteValue_1609) {

    uint8_t smallValue = 1;

    value.setDataArea(reinterpret_cast<const byte*>(&smallValue), sizeof(uint8_t));

    SonyMakerNote::printFocusMode(os, value, &metadata);

    EXPECT_EQ(os.str(), "(1)");

}



TEST_F(SonyMakerNoteTest_1609, BoundaryCondition_OutOfRangeValue_1609) {

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t(5)), sizeof(uint16_t));

    SonyMakerNote::printFocusMode(os, value, &metadata);

    EXPECT_EQ(os.str(), "(5)");

}



TEST_F(SonyMakerNoteTest_1609, InvalidValueType_1609) {

    Value invalidValue(unsignedByte);  // Different type

    invalidValue.setDataArea(reinterpret_cast<const byte*>(&uint8_t(1)), sizeof(uint8_t));

    SonyMakerNote::printFocusMode(os, invalidValue, &metadata);

    EXPECT_EQ(os.str(), "(1)");

}



TEST_F(SonyMakerNoteTest_1609, NullMetadataPointer_1609) {

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t(1)), sizeof(uint16_t));

    SonyMakerNote::printFocusMode(os, value, nullptr);

    EXPECT_EQ(os.str(), "(1)");

}



TEST_F(SonyMakerNoteTest_1609, InvalidMetaVersion_1609) {

    metadata["Exif.Sony.MakerNote.Version"] = Value::create(string);

    metadata["Exif.Sony.MakerNote.Version"]->setValue(std::string("INVALID"));

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t(1)), sizeof(uint16_t));

    SonyMakerNote::printFocusMode(os, value, &metadata);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(SonyMakerNoteTest_1609, ValidMetaVersion_1609) {

    metadata["Exif.Sony.MakerNote.Version"] = Value::create(string);

    metadata["Exif.Sony.MakerNote.Version"]->setValue(std::string("DC7303320222000"));

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t(1)), sizeof(uint16_t));

    SonyMakerNote::printFocusMode(os, value, &metadata);

    EXPECT_EQ(os.str(), "AF-S");

}
