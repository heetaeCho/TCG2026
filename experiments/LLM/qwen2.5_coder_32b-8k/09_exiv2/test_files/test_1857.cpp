#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class CopyXmpToExifTest_1857 : public ::testing::Test {

protected:

    XmpData xmpData;

    ExifData exifData;

};



TEST_F(CopyXmpToExifTest_1857, NormalOperation_1857) {

    // Arrange

    Xmpdatum xmpDatum(XmpKey("Xmp.dc.title"), new StringValue("Sample Title"));

    xmpData.add(xmpDatum);



    // Act

    copyXmpToExif(xmpData, exifData);



    // Assert

    ASSERT_EQ(exifData.count(), 1);

    Exifdatum exifDatum = exifData.findKey(ExifKey("Exif.Image.DocumentName"))->value();

    EXPECT_EQ(exifDatum.toString(), "Sample Title");

}



TEST_F(CopyXmpToExifTest_1857, BoundaryConditions_EmptyXmp_1857) {

    // Arrange

    xmpData.clear();



    // Act

    copyXmpToExif(xmpData, exifData);



    // Assert

    EXPECT_EQ(exifData.count(), 0);

}



TEST_F(CopyXmpToExifTest_1857, ExceptionalCase_NoMatchingConversion_1857) {

    // Arrange

    Xmpdatum xmpDatum(XmpKey("Xmp.dc.nonexistent"), new StringValue("Nonexistent Value"));

    xmpData.add(xmpDatum);



    // Act

    copyXmpToExif(xmpData, exifData);



    // Assert

    EXPECT_EQ(exifData.count(), 0);

}



TEST_F(CopyXmpToExifTest_1857, BoundaryConditions_LargeXmp_1857) {

    // Arrange

    for (int i = 0; i < 10; ++i) {

        Xmpdatum xmpDatum(XmpKey("Xmp.dc.title" + std::to_string(i)), new StringValue("Sample Title " + std::to_string(i)));

        xmpData.add(xmpDatum);

    }



    // Act

    copyXmpToExif(xmpData, exifData);



    // Assert

    EXPECT_EQ(exifData.count(), 1); // Only one matching conversion is expected

}



TEST_F(CopyXmpToExifTest_1857, ExternalInteractions_ConverterCalled_1857) {

    // Arrange

    Xmpdatum xmpDatum(XmpKey("Xmp.dc.title"), new StringValue("Sample Title"));

    xmpData.add(xmpDatum);



    // Act

    copyXmpToExif(xmpData, exifData);



    // Assert

    // This test implicitly checks that Converter::cnvFromXmp() is called,

    // but we cannot directly verify it without mocking internal behavior.

    EXPECT_EQ(exifData.count(), 1);

}



TEST_F(CopyXmpToExifTest_1857, BoundaryConditions_MultipleSameKeysInXmp_1857) {

    // Arrange

    Xmpdatum xmpDatum1(XmpKey("Xmp.dc.title"), new StringValue("Title 1"));

    Xmpdatum xmpDatum2(XmpKey("Xmp.dc.title"), new StringValue("Title 2"));

    xmpData.add(xmpDatum1);

    xmpData.add(xmpDatum2);



    // Act

    copyXmpToExif(xmpData, exifData);



    // Assert

    EXPECT_EQ(exifData.count(), 1); // Only one key should be added to ExifData

}
