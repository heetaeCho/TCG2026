#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1622 : public ::testing::Test {

protected:

    Value value_;

    ExifData metadata_;



    void SetUp() override {

        // Initialize with a default value and type

        value_ = Value(unsignedShort);

    }



    bool getModel(const ExifData* metadata, std::string& model) {

        auto it = metadata->findKey("Exif.Image.Model");

        if (it != metadata->end()) {

            model = it->value().toString();

            return true;

        }

        return false;

    }

};



TEST_F(SonyMakerNoteTest_1622, NormalOperationWithValidModel_1622) {

    std::ostringstream os;

    value_.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint16_t>(10)), sizeof(uint16_t));

    metadata_.add(ExifKey("Exif.Image.Model"), Value::create(unsignedByte)->setValue("ILCE-7M4"));

    EXPECT_EQ("(n/a)", SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value_, &metadata_).str());

}



TEST_F(SonyMakerNoteTest_1622, NormalOperationWithInvalidModel_1622) {

    std::ostringstream os;

    value_.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint16_t>(10)), sizeof(uint16_t));

    metadata_.add(ExifKey("Exif.Image.Model"), Value::create(unsignedByte)->setValue("Unknown Model"));

    EXPECT_EQ("80", SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value_, &metadata_).str());

}



TEST_F(SonyMakerNoteTest_1622, ValueCountNotOne_1622) {

    std::ostringstream os;

    value_.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint16_t>(10)), 2 * sizeof(uint16_t));

    EXPECT_EQ("()", SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value_, &metadata_).str());

}



TEST_F(SonyMakerNoteTest_1622, ValueTypeNotUnsignedShort_1622) {

    std::ostringstream os;

    value_ = Value(unsignedByte);

    value_.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint8_t>(10)), sizeof(uint8_t));

    EXPECT_EQ("()", SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value_, &metadata_).str());

}



TEST_F(SonyMakerNoteTest_1622, MetadataIsNull_1622) {

    std::ostringstream os;

    value_.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint16_t>(10)), sizeof(uint16_t));

    EXPECT_EQ("()", SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value_, nullptr).str());

}



TEST_F(SonyMakerNoteTest_1622, ModelNotFoundInMetadata_1622) {

    std::ostringstream os;

    value_.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint16_t>(10)), sizeof(uint16_t));

    EXPECT_EQ("()", SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value_, &metadata_).str());

}



TEST_F(SonyMakerNoteTest_1622, ValueIsZero_1622) {

    std::ostringstream os;

    value_.setDataArea(reinterpret_cast<const byte*>(&static_cast<uint16_t>(0)), sizeof(uint16_t));

    metadata_.add(ExifKey("Exif.Image.Model"), Value::create(unsignedByte)->setValue("Unknown Model"));

    EXPECT_EQ("(n/a)", SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value_, &metadata_).str());

}



TEST_F(SonyMakerNoteTest_1622, ValueIsNegative_1622) {

    std::ostringstream os;

    uint16_t negativeValue = static_cast<uint16_t>(-10); // This will wrap around to a large positive number

    value_.setDataArea(reinterpret_cast<const byte*>(&negativeValue), sizeof(uint16_t));

    metadata_.add(ExifKey("Exif.Image.Model"), Value::create(unsignedByte)->setValue("Unknown Model"));

    EXPECT_EQ("(n/a)", SonyMakerNote::printSonyMisc3cSonyImageHeight(os, value_, &metadata_).str());

}
