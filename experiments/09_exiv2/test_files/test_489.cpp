#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_489 : public ::testing::Test {

protected:

    std::ostringstream os_;

    Value value_;

    ExifData metadata_;



    void SetUp() override {

        value_.typeId_ = unsignedByte;  // Set default type to unsignedByte

        metadata_.clear();

    }

};



TEST_F(Nikon3MakerNoteTest_489, InvalidCount_ReturnsValueInParens_489) {

    value_.count_ = 2;

    Nikon3MakerNote::printFlashMasterDataFl6(os_, value_, &metadata_);

    EXPECT_EQ(os_.str(), "(unsignedByte(2))");

}



TEST_F(Nikon3MakerNoteTest_489, InvalidTypeId_ReturnsValueInParens_489) {

    value_.typeId_ = asciiString;

    Nikon3MakerNote::printFlashMasterDataFl6(os_, value_, &metadata_);

    EXPECT_EQ(os_.str(), "(asciiString(0))");

}



TEST_F(Nikon3MakerNoteTest_489, NullMetadata_ReturnsValueInParens_489) {

    Nikon3MakerNote::printFlashMasterDataFl6(os_, value_, nullptr);

    EXPECT_EQ(os_.str(), "(unsignedByte(0))");

}



TEST_F(Nikon3MakerNoteTest_489, ExternalFlashData1NotFound_ReturnsValueInParens_489) {

    Nikon3MakerNote::printFlashMasterDataFl6(os_, value_, &metadata_);

    EXPECT_EQ(os_.str(), "(unsignedByte(0))");

}



TEST_F(Nikon3MakerNoteTest_489, ExternalFlashData1InvalidCount_ReturnsValueInParens_489) {

    Exifdatum exifdatum(ExifKey("Exif.NikonFl6.ExternalFlashData1"), &value_);

    metadata_.add(exifdatum);

    Nikon3MakerNote::printFlashMasterDataFl6(os_, value_, &metadata_);

    EXPECT_EQ(os_.str(), "(unsignedByte(0))");

}



TEST_F(Nikon3MakerNoteTest_489, ExternalFlashData1InvalidTypeId_ReturnsValueInParens_489) {

    Exifdatum exifdatum(ExifKey("Exif.NikonFl6.ExternalFlashData1"), &value_);

    exifdatum.typeId_ = asciiString;

    metadata_.add(exifdatum);

    Nikon3MakerNote::printFlashMasterDataFl6(os_, value_, &metadata_);

    EXPECT_EQ(os_.str(), "(unsignedByte(0))");

}



TEST_F(Nikon3MakerNoteTest_489, FlashModeZero_ReturnsNAn_489) {

    Exifdatum exifdatum1(ExifKey("Exif.NikonFl6.ExternalFlashData1"), &value_);

    metadata_.add(exifdatum1);



    value_.toUint32_ = 0x0;

    Nikon3MakerNote::printFlashMasterDataFl6(os_, value_, &metadata_);

    EXPECT_EQ(os_.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_489, FlashModeNonZero_ReturnsFlashCompensationValue_489) {

    Exifdatum exifdatum1(ExifKey("Exif.NikonFl6.ExternalFlashData1"), &value_);

    metadata_.add(exifdatum1);



    value_.toUint32_ = 0x1F; // Mode is 0xF

    Nikon3MakerNote::printFlashMasterDataFl6(os_, value_, &metadata_);

    EXPECT_EQ(os_.str(), "0"); // Assuming flashCompensationValue returns "0" for test purpose

}
