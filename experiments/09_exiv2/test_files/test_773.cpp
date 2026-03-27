#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class MockExifdatum : public Exifdatum {

public:

    MOCK_METHOD(int, setDataArea, (const byte* buf, size_t len), (override));

};



class MockExifData : public ExifData {

public:

    using ExifData::operator[];

    MOCK_METHOD(Exifdatum&, operator[], (const std::string& key), (override));

};



class ExifThumbTest_773 : public ::testing::Test {

protected:

    MockExifData mockExifData;

    ExifThumb exifThumb{mockExifData};

};



TEST_F(ExifThumbTest_773, SetJpegThumbnail_NonEmptyBuffer_773) {

    const byte buf[] = {0xFF, 0xD8, 0xFF, 0xE0};

    size_t size = sizeof(buf);

    

    EXPECT_CALL(mockExifData, operator[]("Exif.Thumbnail.Compression")).WillOnce(::testing::ReturnRef(mockExifdatum));

    EXPECT_CALL(mockExifdatum, setDataArea(::testing::_ , ::testing::_)).Times(1);



    exifThumb.setJpegThumbnail(buf, size);

}



TEST_F(ExifThumbTest_773, SetJpegThumbnail_EmptyBuffer_773) {

    const byte buf[] = {};

    size_t size = sizeof(buf);

    

    EXPECT_CALL(mockExifData, operator[]("Exif.Thumbnail.Compression")).WillOnce(::testing::ReturnRef(mockExifdatum));

    EXPECT_CALL(mockExifdatum, setDataArea(::testing::_ , ::testing::_)).Times(1);



    exifThumb.setJpegThumbnail(buf, size);

}



TEST_F(ExifThumbTest_773, SetJpegThumbnail_SingleByteBuffer_773) {

    const byte buf[] = {0xFF};

    size_t size = sizeof(buf);

    

    EXPECT_CALL(mockExifData, operator[]("Exif.Thumbnail.Compression")).WillOnce(::testing::ReturnRef(mockExifdatum));

    EXPECT_CALL(mockExifdatum, setDataArea(::testing::_ , ::testing::_)).Times(1);



    exifThumb.setJpegThumbnail(buf, size);

}



TEST_F(ExifThumbTest_773, SetJpegThumbnail_MaxSizeBuffer_773) {

    const byte buf[1024] = {};

    size_t size = sizeof(buf);

    

    EXPECT_CALL(mockExifData, operator[]("Exif.Thumbnail.Compression")).WillOnce(::testing::ReturnRef(mockExifdatum));

    EXPECT_CALL(mockExifdatum, setDataArea(::testing::_ , ::testing::_)).Times(1);



    exifThumb.setJpegThumbnail(buf, size);

}
