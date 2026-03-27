#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1616 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote_;

    Value mockValue_;

    ExifData mockMetadata_;

};



TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_ValueCountNotOne_1616) {

    std::ostringstream os;

    EXPECT_CALL(mockValue_, count()).WillOnce(::testing::Return(2));



    sonyMakerNote_.printSonyMisc1CameraTemperature(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "(Exiv2::Value)\n");

}



TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_MetadataNullptr_1616) {

    std::ostringstream os;

    EXPECT_CALL(mockValue_, count()).WillOnce(::testing::Return(1));



    sonyMakerNote_.printSonyMisc1CameraTemperature(os, mockValue_, nullptr);

    EXPECT_EQ(os.str(), "(Exiv2::Value)\n");

}



TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_MetadataKeyNotFound_1616) {

    std::ostringstream os;

    EXPECT_CALL(mockValue_, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockMetadata_, findKey(ExifKey("Exif.SonyMisc1.0x0004"))).WillOnce(::testing::Return(mockMetadata_.end()));



    sonyMakerNote_.printSonyMisc1CameraTemperature(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "n/a\n");

}



TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_MetadataKeyValueCountNotOne_1616) {

    std::ostringstream os;

    EXPECT_CALL(mockValue_, count()).WillOnce(::testing::Return(1));

    Exiv2::ExifData::const_iterator mockIterator = mockMetadata_.end();

    ON_CALL(mockMetadata_, findKey(ExifKey("Exif.SonyMisc1.0x0004"))).WillByDefault(::testing::Return(mockIterator));

    EXPECT_CALL(*mockIterator, count()).WillOnce(::testing::Return(2));



    sonyMakerNote_.printSonyMisc1CameraTemperature(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "n/a\n");

}



TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_MetadataKeyValueNotInRange_1616) {

    std::ostringstream os;

    EXPECT_CALL(mockValue_, count()).WillOnce(::testing::Return(1));

    Exiv2::ExifData::const_iterator mockIterator = mockMetadata_.end();

    ON_CALL(mockMetadata_, findKey(ExifKey("Exif.SonyMisc1.0x0004"))).WillByDefault(::testing::Return(mockIterator));

    EXPECT_CALL(*mockIterator, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(*mockIterator, toInt64()).WillOnce(::testing::Return(150));



    sonyMakerNote_.printSonyMisc1CameraTemperature(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "n/a\n");

}



TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_MetadataKeyValueInRange_1616) {

    std::ostringstream os;

    EXPECT_CALL(mockValue_, count()).WillOnce(::testing::Return(1));

    Exiv2::ExifData::const_iterator mockIterator = mockMetadata_.end();

    ON_CALL(mockMetadata_, findKey(ExifKey("Exif.SonyMisc1.0x0004"))).WillByDefault(::testing::Return(mockIterator));

    EXPECT_CALL(*mockIterator, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(*mockIterator, toInt64()).WillOnce(::testing::Return(35));



    sonyMakerNote_.printSonyMisc1CameraTemperature(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "Exiv2::Value °C\n");

}



TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_MetadataKeyValueZero_1616) {

    std::ostringstream os;

    EXPECT_CALL(mockValue_, count()).WillOnce(::testing::Return(1));

    Exiv2::ExifData::const_iterator mockIterator = mockMetadata_.end();

    ON_CALL(mockMetadata_, findKey(ExifKey("Exif.SonyMisc1.0x0004"))).WillByDefault(::testing::Return(mockIterator));

    EXPECT_CALL(*mockIterator, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(*mockIterator, toInt64()).WillOnce(::testing::Return(0));



    sonyMakerNote_.printSonyMisc1CameraTemperature(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "n/a\n");

}



TEST_F(SonyMakerNoteTest_1616, PrintSonyMisc1CameraTemperature_MetadataKeyValueNinetyNine_1616) {

    std::ostringstream os;

    EXPECT_CALL(mockValue_, count()).WillOnce(::testing::Return(1));

    Exiv2::ExifData::const_iterator mockIterator = mockMetadata_.end();

    ON_CALL(mockMetadata_, findKey(ExifKey("Exif.SonyMisc1.0x0004"))).WillByDefault(::testing::Return(mockIterator));

    EXPECT_CALL(*mockIterator, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(*mockIterator, toInt64()).WillOnce(::testing::Return(99));



    sonyMakerNote_.printSonyMisc1CameraTemperature(os, mockValue_, &mockMetadata_);

    EXPECT_EQ(os.str(), "Exiv2::Value °C\n");

}
