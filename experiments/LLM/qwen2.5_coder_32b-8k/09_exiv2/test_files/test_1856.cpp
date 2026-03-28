#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class MoveExifToXmpTest_1856 : public ::testing::Test {

protected:

    ExifData exifData;

    XmpData xmpData;

};



TEST_F(MoveExifToXmpTest_1856, NormalOperation_1856) {

    // Arrange

    Exifdatum exifDatum(ExifKey("Exif.Image.Artist"), Value::create(Exiv2::asciiString));

    exifDatum.setValue("Test Artist");

    exifData.add(exifDatum);



    // Act

    moveExifToXmp(exifData, xmpData);



    // Assert

    EXPECT_EQ(xmpData.count(), 1);

}



TEST_F(MoveExifToXmpTest_1856, BoundaryCondition_EmptyExifData_1856) {

    // Arrange - exifData is already empty



    // Act

    moveExifToXmp(exifData, xmpData);



    // Assert

    EXPECT_EQ(xmpData.count(), 0);

}



TEST_F(MoveExifToXmpTest_1856, BoundaryCondition_LargeExifData_1856) {

    // Arrange - Add multiple entries to exifData

    for (int i = 0; i < 100; ++i) {

        Exifdatum exifDatum(ExifKey("Exif.Image.Artist" + std::to_string(i)), Value::create(Exiv2::asciiString));

        exifDatum.setValue("Test Artist " + std::to_string(i));

        exifData.add(exifDatum);

    }



    // Act

    moveExifToXmp(exifData, xmpData);



    // Assert

    EXPECT_EQ(xmpData.count(), 100);

}



TEST_F(MoveExifToXmpTest_1856, EraseAfterConversion_1856) {

    // Arrange

    Exifdatum exifDatum(ExifKey("Exif.Image.Artist"), Value::create(Exiv2::asciiString));

    exifDatum.setValue("Test Artist");

    exifData.add(exifDatum);



    // Act

    moveExifToXmp(exifData, xmpData);



    // Assert - XMP data should contain the entry

    EXPECT_EQ(xmpData.count(), 1);

    

    // Additional check to ensure Exif data is cleared after conversion

    EXPECT_TRUE(exifData.empty());

}
