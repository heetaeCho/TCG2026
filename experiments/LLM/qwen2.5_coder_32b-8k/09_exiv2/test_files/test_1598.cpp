#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1598 : public ::testing::Test {

protected:

    Value value_;

    const ExifData* metadata_;



    void SetUp() override {

        value_ = Value(unsignedByte);

        metadata_ = nullptr;

    }



    std::string printAFTrackingToString(const Value& value, const ExifData* metadata) {

        std::ostringstream oss;

        SonyMakerNote::printAFTracking(oss, value, metadata);

        return oss.str();

    }

};



TEST_F(SonyMakerNoteTest_1598, NormalOperationWithValidModel_1598) {

    Value value(unsignedByte);

    value.setDataArea(reinterpret_cast<const byte*>(new uint8_t{2}), 1);



    ExifData exifData;

    std::string model = "DSC-RX10M4";

    exifData["Exif.Image.Model"] = Value::create(string);

    exifData["Exif.Image.Model"].setString(model.c_str());

    metadata_ = &exifData;



    EXPECT_EQ(printAFTrackingToString(value, metadata_), "Lock on AF");

}



TEST_F(SonyMakerNoteTest_1598, NormalOperationWithInvalidModel_1598) {

    Value value(unsignedByte);

    value.setDataArea(reinterpret_cast<const byte*>(new uint8_t{2}), 1);



    ExifData exifData;

    std::string model = "Unknown Model";

    exifData["Exif.Image.Model"] = Value::create(string);

    exifData["Exif.Image.Model"].setString(model.c_str());

    metadata_ = &exifData;



    EXPECT_EQ(printAFTrackingToString(value, metadata_), "(2)");

}



TEST_F(SonyMakerNoteTest_1598, BoundaryConditionWithCountZero_1598) {

    Value value(unsignedByte);

    metadata_ = nullptr;

    value.setDataArea(reinterpret_cast<const byte*>(new uint8_t{2}), 0);



    EXPECT_EQ(printAFTrackingToString(value, metadata_), "(2)");

}



TEST_F(SonyMakerNoteTest_1598, BoundaryConditionWithInvalidTypeId_1598) {

    Value value(unsignedShort);

    value.setDataArea(reinterpret_cast<const byte*>(new uint16_t{2}), 1);



    EXPECT_EQ(printAFTrackingToString(value, metadata_), "(2)");

}



TEST_F(SonyMakerNoteTest_1598, ExceptionalCaseWithNullMetadata_1598) {

    Value value(unsignedByte);

    value.setDataArea(reinterpret_cast<const byte*>(new uint8_t{2}), 1);



    EXPECT_EQ(printAFTrackingToString(value, metadata_), "(2)");

}



TEST_F(SonyMakerNoteTest_1598, ExceptionalCaseWithUnknownTagValue_1598) {

    Value value(unsignedByte);

    value.setDataArea(reinterpret_cast<const byte*>(new uint8_t{99}), 1);



    ExifData exifData;

    std::string model = "DSC-RX10M4";

    exifData["Exif.Image.Model"] = Value::create(string);

    exifData["Exif.Image.Model"].setString(model.c_str());

    metadata_ = &exifData;



    EXPECT_EQ(printAFTrackingToString(value, metadata_), "(99)");

}
