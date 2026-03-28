#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_496 : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote_;

    std::ostringstream os_;

};



TEST_F(Nikon3MakerNoteTest_496, ValueCountNotOne_496) {

    Exifdatum value(Metadatum::key(), nullptr);

    ExifData metadata;



    auto result = nikonMakerNote_.printFlashGroupBDataFl7(os_, value, &metadata);



    EXPECT_EQ(result.str(), "(0)");

}



TEST_F(Nikon3MakerNoteTest_496, ValueTypeNotUnsignedByte_496) {

    Exiv2::Value::UniquePtr val(Exiv2::Value::create(unsignedShort));

    val->read("\x12\x34", 2);

    Exifdatum value(Metadatum::key(), val.get());

    ExifData metadata;



    auto result = nikonMakerNote_.printFlashGroupBDataFl7(os_, value, &metadata);



    EXPECT_EQ(result.str(), "(0)");

}



TEST_F(Nikon3MakerNoteTest_496, MetadataIsNullptr_496) {

    Exiv2::Value::UniquePtr val(Exiv2::Value::create(unsignedByte));

    val->read("\x12", 1);

    Exifdatum value(Metadatum::key(), val.get());



    auto result = nikonMakerNote_.printFlashGroupBDataFl7(os_, value, nullptr);



    EXPECT_EQ(result.str(), "(0)");

}



TEST_F(Nikon3MakerNoteTest_496, FlashGroupBCControlNotFound_496) {

    Exiv2::Value::UniquePtr val(Exiv2::Value::create(unsignedByte));

    val->read("\x12", 1);

    Exifdatum value(Metadatum::key(), val.get());

    ExifData metadata;



    auto result = nikonMakerNote_.printFlashGroupBDataFl7(os_, value, &metadata);



    EXPECT_EQ(result.str(), "(0)");

}



TEST_F(Nikon3MakerNoteTest_496, FlashGroupBCControlCountNotOne_496) {

    Exiv2::Value::UniquePtr val(Exiv2::Value::create(unsignedByte));

    val->read("\x12", 1);

    Exifdatum value(Metadatum::key(), val.get());

    ExifData metadata;

    Exiv2::Value::UniquePtr controlVal(Exiv2::Value::create(unsignedShort)); // Not unsignedByte

    Exifdatum controlDat("Exif.NikonFl7.FlashGroupBCControlData", controlVal.get());

    metadata.add(controlDat);



    auto result = nikonMakerNote_.printFlashGroupBDataFl7(os_, value, &metadata);



    EXPECT_EQ(result.str(), "(0)");

}



TEST_F(Nikon3MakerNoteTest_496, FlashGroupBCControlTypeNotUnsignedByte_496) {

    Exiv2::Value::UniquePtr val(Exiv2::Value::create(unsignedByte));

    val->read("\x12", 1);

    Exifdatum value(Metadatum::key(), val.get());

    ExifData metadata;

    Exiv2::Value::UniquePtr controlVal(Exiv2::Value::create(unsignedShort)); // Not unsignedByte

    controlVal->read("\x12\x34", 2);

    Exifdatum controlDat("Exif.NikonFl7.FlashGroupBCControlData", controlVal.get());

    metadata.add(controlDat);



    auto result = nikonMakerNote_.printFlashGroupBDataFl7(os_, value, &metadata);



    EXPECT_EQ(result.str(), "(0)");

}



TEST_F(Nikon3MakerNoteTest_496, FlashModeUsesManualScaleFalse_496) {

    Exiv2::Value::UniquePtr val(Exiv2::Value::create(unsignedByte));

    val->read("\x12", 1);

    Exifdatum value(Metadatum::key(), val.get());

    ExifData metadata;

    Exiv2::Value::UniquePtr controlVal(Exiv2::Value::create(unsignedByte));

    controlVal->read("\x01", 1); // mode = 0 (false)

    Exifdatum controlDat("Exif.NikonFl7.FlashGroupBCControlData", controlVal.get());

    metadata.add(controlDat);



    auto result = nikonMakerNote_.printFlashGroupBDataFl7(os_, value, &metadata);



    EXPECT_EQ(result.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_496, FlashModeUsesManualScaleTrue_496) {

    Exiv2::Value::UniquePtr val(Exiv2::Value::create(unsignedByte));

    val->read("\x12", 1);

    Exifdatum value(Metadatum::key(), val.get());

    ExifData metadata;

    Exiv2::Value::UniquePtr controlVal(Exiv2::Value::create(unsignedByte));

    controlVal->read("\x10", 1); // mode = 1 (true)

    Exifdatum controlDat("Exif.NikonFl7.FlashGroupBCControlData", controlVal.get());

    metadata.add(controlDat);



    auto result = nikonMakerNote_.printFlashGroupBDataFl7(os_, value, &metadata);



    EXPECT_EQ(result.str(), "n/a"); // Since we can't mock internal function printFlashCompensationValue

}
