#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2::Internal;

using namespace testing;



class Nikon3MakerNoteTest : public Test {

protected:

    std::ostringstream os;

    Value mockValue;

    ExifData mockMetadata;



    void SetUp() override {

        ON_CALL(mockValue, count()).WillByDefault(Return(1));

        ON_CALL(mockValue, typeId()).WillByDefault(Return(unsignedByte));

        ON_CALL(mockValue, toUint32(_)).WillByDefault(Return(0));

    }

};



TEST_F(Nikon3MakerNoteTest_493, NormalOperation_ModeZero_493) {

    EXPECT_CALL(mockMetadata, findKey(_))

        .WillOnce(Return(Exiv2::ExifData::const_iterator()))

        .WillOnce(Return(ByRef(mockMetadata.findKey(ExifKey("Exif.NikonFl6.FlashGroupAControlData"))));



    Exifdatum controlDataDatum(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), &mockValue);

    EXPECT_CALL(mockMetadata, findKey(ExifKey("Exif.NikonFl6.FlashGroupAControlData")))

        .WillOnce(Return(Exiv2::ExifData::const_iterator(&controlDataDatum)));



    ON_CALL(controlDataDatum, toUint32(_)).WillByDefault(Return(0));



    Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_493, NormalOperation_ModeNonZero_493) {

    Exifdatum controlDataDatum(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), &mockValue);

    EXPECT_CALL(mockMetadata, findKey(_)).WillOnce(Return(ByRef(mockMetadata.findKey(ExifKey("Exif.NikonFl6.FlashGroupAControlData"))));

    EXPECT_CALL(mockMetadata, findKey(ExifKey("Exif.NikonFl6.FlashGroupAControlData")))

        .WillOnce(Return(Exiv2::ExifData::const_iterator(&controlDataDatum)));



    ON_CALL(controlDataDatum, toUint32(_)).WillByDefault(Return(0x1F)); // Mode 15



    Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "(Exiv2::Value)");

}



TEST_F(Nikon3MakerNoteTest_493, MetadataNull_493) {

    Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "(Exiv2::Value)");

}



TEST_F(Nikon3MakerNoteTest_493, ValueCountNotOne_493) {

    ON_CALL(mockValue, count()).WillByDefault(Return(2));

    Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "(Exiv2::Value)");

}



TEST_F(Nikon3MakerNoteTest_493, ValueTypeNotUnsignedByte_493) {

    ON_CALL(mockValue, typeId()).WillByDefault(Return(asciiString));

    Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "(Exiv2::Value)");

}



TEST_F(Nikon3MakerNoteTest_493, ControlDataNotFound_493) {

    EXPECT_CALL(mockMetadata, findKey(_)).WillOnce(Return(Exiv2::ExifData::const_iterator()));

    Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "(Exiv2::Value)");

}



TEST_F(Nikon3MakerNoteTest_493, ControlDataCountNotOne_493) {

    Exifdatum controlDataDatum(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), &mockValue);

    EXPECT_CALL(mockMetadata, findKey(_)).WillOnce(Return(ByRef(mockMetadata.findKey(ExifKey("Exif.NikonFl6.FlashGroupAControlData"))));

    EXPECT_CALL(mockMetadata, findKey(ExifKey("Exif.NikonFl6.FlashGroupAControlData")))

        .WillOnce(Return(Exiv2::ExifData::const_iterator(&controlDataDatum)));



    ON_CALL(controlDataDatum, count()).WillByDefault(Return(2));



    Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "(Exiv2::Value)");

}



TEST_F(Nikon3MakerNoteTest_493, ControlDataTypeNotUnsignedByte_493) {

    Exifdatum controlDataDatum(ExifKey("Exif.NikonFl6.FlashGroupAControlData"), &mockValue);

    EXPECT_CALL(mockMetadata, findKey(_)).WillOnce(Return(ByRef(mockMetadata.findKey(ExifKey("Exif.NikonFl6.FlashGroupAControlData"))));

    EXPECT_CALL(mockMetadata, findKey(ExifKey("Exif.NikonFl6.FlashGroupAControlData")))

        .WillOnce(Return(Exiv2::ExifData::const_iterator(&controlDataDatum)));



    ON_CALL(controlDataDatum, typeId()).WillByDefault(Return(asciiString));



    Nikon3MakerNote::printFlashGroupADataFl6(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "(Exiv2::Value)");

}
