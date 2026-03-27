#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include <string>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1597 : public ::testing::Test {

protected:

    std::ostringstream os_;

    Value value_;

    ExifData metadata_;



    SonyMakerNoteTest_1597() : value_(unsignedByte) {}

};



TEST_F(SonyMakerNoteTest_1597, InvalidTypeId_ReturnsParenthesizedValue_1597) {

    value_.ok_ = true;

    value_ = Value(signedByte);

    metadata_.clear();

    std::ostringstream os;

    SonyMakerNote::printAFPointsUsed(os, value_, &metadata_);

    EXPECT_EQ("(Exiv2::Value)", os.str());

}



TEST_F(SonyMakerNoteTest_1597, NullMetadata_ReturnsParenthesizedValue_1597) {

    value_.ok_ = true;

    metadata_.clear();

    std::ostringstream os;

    SonyMakerNote::printAFPointsUsed(os, value_, nullptr);

    EXPECT_EQ("(Exiv2::Value)", os.str());

}



TEST_F(SonyMakerNoteTest_1597, NonSonyModel_ReturnsBitlistAllLeSet1_1597) {

    value_.ok_ = true;

    metadata_.clear();

    Exifdatum& exifDatum = metadata_["Exif.Image.Model"];

    exifDatum.setValue("UnknownModel");

    std::ostringstream os;

    SonyMakerNote::printAFPointsUsed(os, value_, &metadata_);

    EXPECT_EQ("(Exiv2::Value)", os.str());

}



TEST_F(SonyMakerNoteTest_1597, ILCA68Model_ReturnsBitlistAllLeSet2_1597) {

    value_.ok_ = true;

    metadata_.clear();

    Exifdatum& exifDatum = metadata_["Exif.Image.Model"];

    exifDatum.setValue("ILCA-68");

    std::ostringstream os;

    SonyMakerNote::printAFPointsUsed(os, value_, &metadata_);

    EXPECT_EQ("(Exiv2::Value)", os.str());

}



TEST_F(SonyMakerNoteTest_1597, ILCA77M2Model_ReturnsBitlistAllLeSet2_1597) {

    value_.ok_ = true;

    metadata_.clear();

    Exifdatum& exifDatum = metadata_["Exif.Image.Model"];

    exifDatum.setValue("ILCA-77M2");

    std::ostringstream os;

    SonyMakerNote::printAFPointsUsed(os, value_, &metadata_);

    EXPECT_EQ("(Exiv2::Value)", os.str());

}



TEST_F(SonyMakerNoteTest_1597, OtherSonyModel_ReturnsN_A_1597) {

    value_.ok_ = true;

    metadata_.clear();

    Exifdatum& exifDatum = metadata_["Exif.Image.Model"];

    exifDatum.setValue("ILCA-Other");

    std::ostringstream os;

    SonyMakerNote::printAFPointsUsed(os, value_, &metadata_);

    EXPECT_EQ("n/a", os.str());

}
