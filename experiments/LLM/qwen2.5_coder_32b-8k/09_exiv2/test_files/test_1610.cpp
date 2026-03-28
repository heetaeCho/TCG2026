#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exif.hpp>

#include <exiv2/value.hpp>

#include "sonymn_int.hpp"

#include <sstream>



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1610 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote_;

    std::ostringstream os_;

    Value value_;

    ExifData metadata_;



    void SetUp() override {

        // Initialize common objects for tests

        value_.ok_ = true;

        value_.type_ = unsignedShort; // Default to unsignedShort type

    }

};



TEST_F(SonyMakerNoteTest_1610, PrintAFMode_NormalOperation_1610) {

    value_.count_ = 1;

    EXPECT_CALL(value_, toUint32(0)).WillRepeatedly(testing::Return(0)); // Assuming tag 0 maps to "Default" in sonyAFModeSet1



    std::string metaVersion = "DC7303320222000";

    metadata_.add(ExifKey("Exif.SonyMakerNote.Version"), Value::create(string));

    metadata_["Exif.SonyMakerNote.Version"].setValue(metaVersion);



    sonyMakerNote_.printAFMode(os_, value_, &metadata_);



    EXPECT_EQ(os_.str(), "Default");

}



TEST_F(SonyMakerNoteTest_1610, PrintAFMode_MetadataNull_1610) {

    sonyMakerNote_.printAFMode(os_, value_, nullptr);



    EXPECT_EQ(os_.str(), "(Exiv2::Value())");

}



TEST_F(SonyMakerNoteTest_1610, PrintAFMode_MetadataVersionMismatch_1610) {

    std::string metaVersion = "WRONG_VERSION";

    metadata_.add(ExifKey("Exif.SonyMakerNote.Version"), Value::create(string));

    metadata_["Exif.SonyMakerNote.Version"].setValue(metaVersion);



    sonyMakerNote_.printAFMode(os_, value_, &metadata_);



    EXPECT_EQ(os_.str(), "(Exiv2::Value())");

}



TEST_F(SonyMakerNoteTest_1610, PrintAFMode_ValueCountMismatch_1610) {

    value_.count_ = 0; // Invalid count



    sonyMakerNote_.printAFMode(os_, value_, &metadata_);



    EXPECT_EQ(os_.str(), "(Exiv2::Value())");

}



TEST_F(SonyMakerNoteTest_1610, PrintAFMode_ValueTypeMismatch_1610) {

    value_.type_ = asciiString; // Invalid type



    sonyMakerNote_.printAFMode(os_, value_, &metadata_);



    EXPECT_EQ(os_.str(), "(Exiv2::Value())");

}



TEST_F(SonyMakerNoteTest_1610, PrintAFMode_FocusMode2Set_1610) {

    value_.count_ = 1;

    EXPECT_CALL(value_, toUint32(0)).WillRepeatedly(testing::Return(0)); // Assuming tag 0 maps to "Multi" in sonyAFModeSet2



    std::string metaVersion = "DC7303320222000";

    metadata_.add(ExifKey("Exif.SonyMakerNote.Version"), Value::create(string));

    metadata_["Exif.SonyMakerNote.Version"].setValue(metaVersion);



    uint32_t focusMode2 = 1;

    metadata_.add(ExifKey("Exif.SonyMakerNote.FocusMode2"), Value::create(unsignedLong));

    metadata_["Exif.SonyMakerNote.FocusMode2"].setValue(focusMode2);



    sonyMakerNote_.printAFMode(os_, value_, &metadata_);



    EXPECT_EQ(os_.str(), "Multi");

}



TEST_F(SonyMakerNoteTest_1610, PrintAFMode_DefaultCase_1610) {

    value_.count_ = 1;

    EXPECT_CALL(value_, toUint32(0)).WillRepeatedly(testing::Return(99)); // Invalid tag, should default



    std::string metaVersion = "DC7303320222000";

    metadata_.add(ExifKey("Exif.SonyMakerNote.Version"), Value::create(string));

    metadata_["Exif.SonyMakerNote.Version"].setValue(metaVersion);



    sonyMakerNote_.printAFMode(os_, value_, &metadata_);



    EXPECT_EQ(os_.str(), "n/a");

}
