#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

#include "exiv2/value.hpp"

#include "exiv2/exif.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_461 : public ::testing::Test {

protected:

    Value value_;

    ExifData metadata_;

    std::ostringstream os_;



    void SetUp() override {

        // Initialize the Value object with a default type

        value_ = Value(TypeId::unsignedLong);

    }

};



TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ContrastDetectAFOff_461) {

    metadata_.clear();

    Nikon3MakerNote::printAf2AreaMode(os_, value_, &metadata_);

    EXPECT_EQ("Single-point AF", os_.str());

}



TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ContrastDetectAFOn_461) {

    Exifdatum exifDatum(ExifKey("Exif.NikonAf2.ContrastDetectAF"), &value_);

    value_.setValue(1);

    metadata_.add(exifDatum);



    Nikon3MakerNote::printAf2AreaMode(os_, value_, &metadata_);

    EXPECT_EQ("Normal-area AF", os_.str());

}



TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_MetadataNotFound_461) {

    metadata_.clear();

    Nikon3MakerNote::printAf2AreaMode(os_, value_, nullptr);

    EXPECT_EQ("Single-point AF", os_.str());

}



TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ValueCountZero_461) {

    Exifdatum exifDatum(ExifKey("Exif.NikonAf2.ContrastDetectAF"), &value_);

    value_.setValue(1);

    metadata_.add(exifDatum);



    auto pos = metadata_.findKey(ExifKey("Exif.NikonAf2.ContrastDetectAF"));

    pos->setValue(reinterpret_cast<const Value*>(nullptr));



    Nikon3MakerNote::printAf2AreaMode(os_, *pos->getValue(), &metadata_);

    EXPECT_EQ("Single-point AF", os_.str());

}



TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_OutOfBoundsValue_461) {

    Exifdatum exifDatum(ExifKey("Exif.NikonAf2.ContrastDetectAF"), &value_);

    value_.setValue(100);

    metadata_.add(exifDatum);



    Nikon3MakerNote::printAf2AreaMode(os_, value_, &metadata_);

    EXPECT_EQ("", os_.str());

}



TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ContrastDetectAFOn_LowerBoundary_461) {

    Exifdatum exifDatum(ExifKey("Exif.NikonAf2.ContrastDetectAF"), &value_);

    value_.setValue(0);

    metadata_.add(exifDatum);



    Nikon3MakerNote::printAf2AreaMode(os_, value_, &metadata_);

    EXPECT_EQ("Contrast AF", os_.str());

}



TEST_F(Nikon3MakerNoteTest_461, PrintAf2AreaMode_ContrastDetectAFOn_UpperBoundary_461) {

    Exifdatum exifDatum(ExifKey("Exif.NikonAf2.ContrastDetectAF"), &value_);

    value_.setValue(5);

    metadata_.add(exifDatum);



    Nikon3MakerNote::printAf2AreaMode(os_, value_, &metadata_);

    EXPECT_EQ("Pinpoint AF", os_.str());

}
