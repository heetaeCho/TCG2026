#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/convert.cpp"



namespace {



class ConverterTest_1835 : public ::testing::Test {

protected:

    Exiv2::ExifData exifData_;

    Exiv2::XmpData xmpData_;

    Exiv2::Converter converter_;



    ConverterTest_1835() : converter_(exifData_, xmpData_) {}

};



TEST_F(ConverterTest_1835, CnvExifValue_ExifKeyNotFound_1835) {

    exifData_.clear();

    xmpData_.clear();



    converter_.cnvExifValue("NonExistentKey", "XmpKey");



    EXPECT_TRUE(xmpData_.findKey(Exiv2::XmpKey("XmpKey")) == xmpData_.end());

}



TEST_F(ConverterTest_1835, CnvExifValue_ValueNotOk_1835) {

    Exiv2::Exifdatum exifDatum(Exiv2::ExifKey("Exif.Image.Artist"), new Exiv2::StringValue);

    exifDatum.setValue(new Exiv2::StringValue)->read("\x00\x00", 2, Exiv2::bigEndian); // Invalid string

    exifData_.add(exifDatum);



    converter_.cnvExifValue("Exif.Image.Artist", "XmpKey");



    EXPECT_TRUE(xmpData_.findKey(Exiv2::XmpKey("XmpKey")) == xmpData_.end());

}



TEST_F(ConverterTest_1835, CnvExifValue_PrepareXmpTargetFails_1835) {

    Exiv2::Exifdatum exifDatum(Exiv2::ExifKey("Exif.Image.Artist"), new Exiv2::StringValue);

    exifDatum.setValue(new Exiv2::StringValue)->read("Artist", 6, Exiv2::bigEndian);

    exifData_.add(exifDatum);



    EXPECT_CALL(*reinterpret_cast<testing::NiceMock<Exiv2::XmpData>*>(&xmpData_), findKey(testing::_))

        .WillOnce(testing::Return(xmpData_.end()));



    converter_.cnvExifValue("Exif.Image.Artist", "XmpKey");



    EXPECT_TRUE(xmpData_.findKey(Exiv2::XmpKey("XmpKey")) == xmpData_.end());

}



TEST_F(ConverterTest_1835, CnvExifValue_SuccessfulConversionAndErase_1835) {

    Exiv2::Exifdatum exifDatum(Exiv2::ExifKey("Exif.Image.Artist"), new Exiv2::StringValue);

    exifDatum.setValue(new Exiv2::StringValue)->read("Artist", 6, Exiv2::bigEndian);

    exifData_.add(exifDatum);



    converter_.setErase(true);

    converter_.cnvExifValue("Exif.Image.Artist", "XmpKey");



    EXPECT_NE(xmpData_.findKey(Exiv2::XmpKey("XmpKey")), xmpData_.end());

    EXPECT_EQ(exifData_.findKey(Exiv2::ExifKey("Exif.Image.Artist")), exifData_.end());

}



TEST_F(ConverterTest_1835, CnvExifValue_SuccessfulConversionWithoutErase_1835) {

    Exiv2::Exifdatum exifDatum(Exiv2::ExifKey("Exif.Image.Artist"), new Exiv2::StringValue);

    exifDatum.setValue(new Exiv2::StringValue)->read("Artist", 6, Exiv2::bigEndian);

    exifData_.add(exifDatum);



    converter_.setErase(false);

    converter_.cnvExifValue("Exif.Image.Artist", "XmpKey");



    EXPECT_NE(xmpData_.findKey(Exiv2::XmpKey("XmpKey")), xmpData_.end());

    EXPECT_NE(exifData_.findKey(Exiv2::ExifKey("Exif.Image.Artist")), exifData_.end());

}



}  // namespace
