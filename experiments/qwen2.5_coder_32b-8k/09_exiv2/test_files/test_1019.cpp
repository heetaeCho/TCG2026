#include <gtest/gtest.h>

#include "ExifParser/ExifData.hpp"

#include "ExifParser/ExifValue.hpp"



using namespace ExifParser;



TEST(ExifDataTest, TestLensModelLookup) {

    ExifData exifData;

    

    // Lens Model: Minolta AF 50mm F1.4

    uint32_t lensId1 = 26150;

    exifData.add(makeExifEntry("Minolta", "MinoltaCameraSettings", "LensIDNumber", &lensId1, 1));

    EXPECT_EQ(exifData.getLensModel(), "Minolta AF 50mm F1.4");



    // Lens Model: Minolta/Sony AF 85mm F1.4

    uint32_t lensId2 = 26291;

    exifData.add(makeExifEntry("Minolta", "MinoltaCameraSettings", "LensIDNumber", &lensId2, 1));

    EXPECT_EQ(exifData.getLensModel(), "Minolta/Sony AF 85mm F1.4");



    // Lens Model: Tamron SP AF 90mm F2.8 Di Macro

    uint32_t lensId3 = 25671;

    exifData.add(makeExifEntry("Minolta", "MinoltaCameraSettings", "LensIDNumber", &lensId3, 1));

    EXPECT_EQ(exifData.getLensModel(), "Tamron SP AF 90mm F2.8 Di Macro");



    // Lens Model: Manual lens

    uint32_t lensId4 = 65535;

    exifData.add(makeExifEntry("Minolta", "MinoltaCameraSettings", "LensIDNumber", &lensId4, 1));

    EXPECT_EQ(exifData.getLensModel(), "Manual lens");



    // Lens Model: Unknown

    uint32_t lensId5 = 9999;

    exifData.add(makeExifEntry("Minolta", "MinoltaCameraSettings", "LensIDNumber", &lensId5, 1));

    EXPECT_EQ(exifData.getLensModel(), "Unknown");

}



TEST(ExifDataTest, TestAddAndRetrieveTags) {

    ExifData exifData;



    // Add some EXIF tags

    uint32_t width = 4096;

    exifData.add(makeExifEntry("Image", "ImageWidth", &width, 1));

    EXPECT_EQ(exifData["ImageWidth"]->toLong(), 4096);



    uint32_t height = 3072;

    exifData.add(makeExifEntry("Image", "ImageHeight", &height, 1));

    EXPECT_EQ(exifData["ImageHeight"]->toLong(), 3072);

}



TEST(ExifValueTest, TestToStringConversion) {

    ExifValue value;



    // Test string conversion for Ascii

    value = makeExifEntry("AsciiTag", "AsciiTagDescription", "Hello World");

    EXPECT_EQ(value.toString(), "Hello World");



    // Test string conversion for Short

    uint16_t shortValue = 42;

    value = makeExifEntry("ShortTag", "ShortTagDescription", &shortValue, 1);

    EXPECT_EQ(value.toString(), "42");



    // Test string conversion for Long

    uint32_t longValue = 1024;

    value = makeExifEntry("LongTag", "LongTagDescription", &longValue, 1);

    EXPECT_EQ(value.toString(), "1024");

}



TEST(ExifValueTest, TestToDoubleConversion) {

    ExifValue value;



    // Test double conversion for Rational

    uint32_t numerator = 5;

    uint32_t denominator = 2;

    Rational rationalValue(numerator, denominator);

    value = makeExifEntry("RationalTag", "RationalTagDescription", &rationalValue, 1);

    EXPECT_DOUBLE_EQ(value.toDouble(), 2.5);



    // Test double conversion for Short

    uint16_t shortValue = 42;

    value = makeExifEntry("ShortTag", "ShortTagDescription", &shortValue, 1);

    EXPECT_DOUBLE_EQ(value.toDouble(), 42.0);



    // Test double conversion for Long

    uint32_t longValue = 1024;

    value = makeExifEntry("LongTag", "LongTagDescription", &longValue, 1);

    EXPECT_DOUBLE_EQ(value.toDouble(), 1024.0);

}

```
