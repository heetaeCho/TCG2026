#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::NiceMock;



class MockExifData : public ExifData {

public:

    MOCK_METHOD1(findKey, iterator(const ExifKey& key));

    MOCK_METHOD1(erase, iterator(iterator pos));

};



class MockXmpData : public XmpData {

public:

    MOCK_METHOD2(add, int(const XmpKey &key, const Value *value));

};



class ConverterTest_1841 : public ::testing::Test {

protected:

    NiceMock<MockExifData> mockExifData;

    NiceMock<MockXmpData> mockXmpData;

    Converter converter{mockExifData, mockXmpData};



    void SetUp() override {

        // Setup default behavior

        ON_CALL(mockExifData, findKey(_)).WillByDefault([](const ExifKey& key) { return mockExifData.end(); });

        ON_CALL(mockXmpData, add(_, _)).WillByDefault(::testing::Return(0));

    }

};



TEST_F(ConverterTest_1841, cnvExifFlash_ValueNotFound_1841) {

    ExifKey key("Exif.Image.Flash");

    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(::testing::Return(mockExifData.end()));



    converter.cnvExifFlash("Exif.Image.Flash", "Xmp.exif.Flash");



    // No expectations for mockXmpData since no data should be added.

}



TEST_F(ConverterTest_1841, cnvExifFlash_ValueCountZero_1841) {

    ExifKey key("Exif.Image.Flash");

    auto exifDatum = new Exifdatum(key, nullptr);

    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(::testing::Return(exifData_.insert({key, *exifDatum}).first));

    ON_CALL(*exifDatum, count()).WillByDefault(::testing::Return(0));



    converter.cnvExifFlash("Exif.Image.Flash", "Xmp.exif.Flash");



    // No expectations for mockXmpData since no data should be added.

}



TEST_F(ConverterTest_1841, cnvExifFlash_ValueInvalid_1841) {

    ExifKey key("Exif.Image.Flash");

    auto value = new Value(Exiv2::unsignedLong);

    value->ok_ = false;

    auto exifDatum = new Exifdatum(key, value);

    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(::testing::Return(exifData_.insert({key, *exifDatum}).first));

    ON_CALL(*exifDatum, count()).WillByDefault(::testing::Return(1));

    ON_CALL(*value, ok()).WillByDefault(::testing::Return(false));



    converter.cnvExifFlash("Exif.Image.Flash", "Xmp.exif.Flash");



    // No expectations for mockXmpData since no data should be added.

}



TEST_F(ConverterTest_1841, cnvExifFlash_NormalOperation_1841) {

    ExifKey key("Exif.Image.Flash");

    auto value = new Value(Exiv2::unsignedLong);

    value->ok_ = true;

    *value << 0b101001; // Example value

    auto exifDatum = new Exifdatum(key, value);

    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(::testing::Return(exifData_.insert({key, *exifDatum}).first));

    ON_CALL(*exifDatum, count()).WillByDefault(::testing::Return(1));

    ON_CALL(*value, ok()).WillByDefault(::testing::Return(true));



    EXPECT_CALL(mockXmpData, add(XmpKey("Xmp.exif.Flash/exif:Fired"), _)).Times(1);

    EXPECT_CALL(mockXmpData, add(XmpKey("Xmp.exif.Flash/exif:Return"), _)).Times(1);

    EXPECT_CALL(mockXmpData, add(XmpKey("Xmp.exif.Flash/exif:Mode"), _)).Times(1);

    EXPECT_CALL(mockXmpData, add(XmpKey("Xmp.exif.Flash/exif:Function"), _)).Times(1);

    EXPECT_CALL(mockXmpData, add(XmpKey("Xmp.exif.Flash/exif:RedEyeMode"), _)).Times(1);



    converter.cnvExifFlash("Exif.Image.Flash", "Xmp.exif.Flash");

}



TEST_F(ConverterTest_1841, cnvExifFlash_EraseEnabled_1841) {

    ExifKey key("Exif.Image.Flash");

    auto value = new Value(Exiv2::unsignedLong);

    value->ok_ = true;

    *value << 0b101001; // Example value

    auto exifDatum = new Exifdatum(key, value);

    EXPECT_CALL(mockExifData, findKey(key)).WillOnce(::testing::Return(exifData_.insert({key, *exifDatum}).first));

    ON_CALL(*exifDatum, count()).WillByDefault(::testing::Return(1));

    ON_CALL(*value, ok()).WillByDefault(::testing::Return(true));



    converter.setErase(true);



    EXPECT_CALL(mockExifData, erase(_)).Times(1);

    EXPECT_CALL(mockXmpData, add(_, _)).Times(5);



    converter.cnvExifFlash("Exif.Image.Flash", "Xmp.exif.Flash");

}
