#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/convert.cpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockExifData : public ExifData {

public:

    MOCK_METHOD1(findKey, iterator(const ExifKey&));

    MOCK_METHOD1(erase, iterator(iterator));

};



class MockXmpData : public XmpData {

public:

    MOCK_METHOD2(add, int(const XmpKey&, const Value*));

};



class ConverterTest_1839 : public ::testing::Test {

protected:

    NiceMock<MockExifData> mockExifData;

    NiceMock<MockXmpData> mockXmpData;

    Converter converter{mockExifData, mockXmpData};

};



TEST_F(ConverterTest_1839, cnvExifVersion_KeyNotFound_1839) {

    ExifKey key("Exif.Image.ExifVersion");

    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(Return(mockExifData.end()));

    converter.cnvExifVersion("Exif.Image.ExifVersion", "Xmp.tiff:Software");

}



TEST_F(ConverterTest_1839, cnvExifVersion_PrepareXmpTargetFails_1839) {

    ExifKey key("Exif.Image.ExifVersion");

    auto exifdatum = new Exifdatum(key, nullptr);

    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(Return(ExivData::iterator{exifdatum}));

    EXPECT_CALL(mockXmpData, add(_, _)).WillOnce(Return(-1));

    converter.cnvExifVersion("Exif.Image.ExifVersion", "Xmp.tiff:Software");

}



TEST_F(ConverterTest_1839, cnvExifVersion_SuccessfulConversion_1839) {

    ExifKey key("Exif.Image.ExifVersion");

    auto exifdatum = new Exifdatum(key, nullptr);

    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(Return(ExivData::iterator{exifdatum}));

    EXPECT_CALL(*exifdatum, count()).WillOnce(Return(1));

    EXPECT_CALL(*exifdatum, toUint32(0)).WillOnce(Return('0'));

    EXPECT_CALL(mockXmpData, add("Xmp.tiff:Software", _)).WillOnce(Return(0));

    converter.cnvExifVersion("Exif.Image.ExifVersion", "Xmp.tiff:Software");

}



TEST_F(ConverterTest_1839, cnvExifVersion_EraseEnabled_ExifErased_1839) {

    converter.setErase(true);

    ExifKey key("Exif.Image.ExifVersion");

    auto exifdatum = new Exifdatum(key, nullptr);

    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(Return(ExivData::iterator{exifdatum}));

    EXPECT_CALL(*exifdatum, count()).WillOnce(Return(1));

    EXPECT_CALL(*exifdatum, toUint32(0)).WillOnce(Return('0'));

    EXPECT_CALL(mockXmpData, add("Xmp.tiff:Software", _)).WillOnce(Return(0));

    EXPECT_CALL(mockExifData, erase(_)).WillOnce(Return(mockExifData.end()));

    converter.cnvExifVersion("Exif.Image.ExifVersion", "Xmp.tiff:Software");

}



TEST_F(ConverterTest_1839, cnvExifVersion_EmptyCount_NoConversion_1839) {

    ExifKey key("Exif.Image.ExifVersion");

    auto exifdatum = new Exifdatum(key, nullptr);

    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(Return(ExivData::iterator{exifdatum}));

    EXPECT_CALL(*exifdatum, count()).WillOnce(Return(0));

    converter.cnvExifVersion("Exif.Image.ExifVersion", "Xmp.tiff:Software");

}
