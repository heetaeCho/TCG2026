#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/convert.cpp"



using namespace Exiv2;



class ConverterTest_1849 : public ::testing::Test {

protected:

    XmpData xmp_data_;

    ExifData exif_data_;

    Converter converter_{exif_data_, xmp_data_};



    void SetUp() override {

        // Prepare some XMP data for testing

        xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:Fired"), new UShortValue(1));

        xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:Return"), new UShortValue(3));

        xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:Mode"), new UShortValue(2));

        xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:Function"), new UShortValue(1));

        xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:RedEyeMode"), new UShortValue(0));

    }

};



TEST_F(ConverterTest_1849, CnvXmpFlash_NormalOperation_1849) {

    converter_.cnvXmpFlash("Xmp.Exif.Flash", "Exif.Photo.Flash");



    // Verify that the converted value is correctly set in exif_data_

    EXPECT_EQ(exif_data_["Exif.Photo.Flash"].toUint32(), 0b101001);

}



TEST_F(ConverterTest_1849, CnvXmpFlash_AllZeros_1849) {

    // Set all XMP values to zero

    xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:Fired"), new UShortValue(0));

    xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:Return"), new UShortValue(0));

    xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:Mode"), new UShortValue(0));

    xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:Function"), new UShortValue(0));

    xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:RedEyeMode"), new UShortValue(0));



    converter_.cnvXmpFlash("Xmp.Exif.Flash", "Exif.Photo.Flash");



    // Verify that the converted value is correctly set in exif_data_

    EXPECT_EQ(exif_data_["Exif.Photo.Flash"].toUint32(), 0b0);

}



TEST_F(ConverterTest_1849, CnvXmpFlash_AllOnes_1849) {

    // Set all XMP values to one where applicable

    xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:Fired"), new UShortValue(1));

    xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:Return"), new UShortValue(3)); // 0b11 for Return

    xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:Mode"), new UShortValue(3));   // 0b11 for Mode

    xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:Function"), new UShortValue(1));

    xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:RedEyeMode"), new UShortValue(1));



    converter_.cnvXmpFlash("Xmp.Exif.Flash", "Exif.Photo.Flash");



    // Verify that the converted value is correctly set in exif_data_

    EXPECT_EQ(exif_data_["Exif.Photo.Flash"].toUint32(), 0b111111);

}



TEST_F(ConverterTest_1849, CnvXmpFlash_MissingKeys_1849) {

    // Remove some keys to test missing data handling

    xmp_data_.erase(xmp_data_.findKey(XmpKey("Xmp.Exif.Flash/exif:Fired")));

    xmp_data_.erase(xmp_data_.findKey(XmpKey("Xmp.Exif.Flash/exif:Return")));

    xmp_data_.erase(xmp_data_.findKey(XmpKey("Xmp.Exif.Flash/exif:Mode")));

    xmp_data_.erase(xmp_data_.findKey(XmpKey("Xmp.Exif.Flash/exif:Function")));



    converter_.cnvXmpFlash("Xmp.Exif.Flash", "Exif.Photo.Flash");



    // Verify that the converted value is correctly set in exif_data_

    EXPECT_EQ(exif_data_["Exif.Photo.Flash"].toUint32(), 0b1); // Only RedEyeMode was present

}



TEST_F(ConverterTest_1849, CnvXmpFlash_EraseFlagSet_1849) {

    converter_.setErase(true);

    converter_.cnvXmpFlash("Xmp.Exif.Flash", "Exif.Photo.Flash");



    // Verify that the XMP keys were erased

    EXPECT_EQ(xmp_data_.findKey(XmpKey("Xmp.Exif.Flash/exif:Fired")), xmp_data_.end());

    EXPECT_EQ(xmp_data_.findKey(XmpKey("Xmp.Exif.Flash/exif:Return")), xmp_data_.end());

    EXPECT_EQ(xmp_data_.findKey(XmpKey("Xmp.Exif.Flash/exif:Mode")), xmp_data_.end());

    EXPECT_EQ(xmp_data_.findKey(XmpKey("Xmp.Exif.Flash/exif:Function")), xmp_data_.end());



    // Verify that the RedEyeMode key is still present

    EXPECT_NE(xmp_data_.findKey(XmpKey("Xmp.Exif.Flash/exif:RedEyeMode")), xmp_data_.end());

}



TEST_F(ConverterTest_1849, CnvXmpFlash_ValueConversionFailure_1849) {

    // Mock a failure in value conversion by setting invalid data

    xmp_data_.add(XmpKey("Xmp.Exif.Flash/exif:Fired"), new UShortValue(2)); // Invalid value



    converter_.cnvXmpFlash("Xmp.Exif.Flash", "Exif.Photo.Flash");



    // Verify that the converted value is not set in exif_data_

    EXPECT_EQ(exif_data_["Exif.Photo.Flash"].toUint32(), 0);

}
