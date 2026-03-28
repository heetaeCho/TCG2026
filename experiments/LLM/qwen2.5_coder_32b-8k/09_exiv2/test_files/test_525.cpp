#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class MakeFunctionTest_525 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(MakeFunctionTest_525, NormalOperation_ExifImageMakeFound_525) {

    ExifKey key("Exif.Image.Make");

    Value* value = new AsciiValue("Canon");

    exifData.add(key, value);

    EXPECT_NE(Exiv2::make(exifData), exifData.end());

}



TEST_F(MakeFunctionTest_525, NormalOperation_ExifPanasonicRawMakeFound_525) {

    ExifKey key("Exif.PanasonicRaw.Make");

    Value* value = new AsciiValue("Panasonic");

    exifData.add(key, value);

    EXPECT_NE(Exiv2::make(exifData), exifData.end());

}



TEST_F(MakeFunctionTest_525, BoundaryCondition_NoMatchingKeys_525) {

    ExifKey key("Exif.Image.Model");

    Value* value = new AsciiValue("Canon EOS R5");

    exifData.add(key, value);

    EXPECT_EQ(Exiv2::make(exifData), exifData.end());

}



TEST_F(MakeFunctionTest_525, BoundaryCondition_EmptyExifData_525) {

    EXPECT_EQ(Exiv2::make(exifData), exifData.end());

}
