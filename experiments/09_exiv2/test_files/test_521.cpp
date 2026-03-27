#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/easyaccess.cpp"



using namespace Exiv2;



class SharpnessFunctionTest : public ::testing::Test {

protected:

    ExifData ed;

};



TEST_F(SharpnessFunctionTest_NormalOperation_521, FoundKey_ReturnsIteratorToKey_521) {

    const std::string key = "Exif.Photo.Sharpness";

    uint16_t sharpnessValue = 10;

    Value* value = new UShortValue(&sharpnessValue);

    Exifdatum exifDatum(key, value);

    ed.add(exifDatum);



    ExifData::const_iterator it = sharpness(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), key);

}



TEST_F(SharpnessFunctionTest_BoundaryConditions_521, EmptyExifData_ReturnsEndIterator_521) {

    ExifData::const_iterator it = sharpness(ed);

    EXPECT_EQ(it, ed.end());

}



TEST_F(SharpnessFunctionTest_NormalOperation_521, MultiplePossibleKeys_ReturnsFirstMatchingKey_521) {

    const std::string key1 = "Exif.Photo.Sharpness";

    const std::string key2 = "Exif.CanonCs.Sharpness";

    uint16_t sharpnessValue1 = 10;

    uint16_t sharpnessValue2 = 20;

    Value* value1 = new UShortValue(&sharpnessValue1);

    Value* value2 = new UShortValue(&sharpnessValue2);

    Exifdatum exifDatum1(key1, value1);

    Exifdatum exifDatum2(key2, value2);

    ed.add(exifDatum1);

    ed.add(exifDatum2);



    ExifData::const_iterator it = sharpness(ed);

    EXPECT_NE(it, ed.end());

    EXPECT_EQ(it->key(), key1);

}



TEST_F(SharpnessFunctionTest_NormalOperation_521, NonMatchingKeys_ReturnsEndIterator_521) {

    const std::string key = "Exif.Photo.SomeOtherTag";

    uint16_t someValue = 10;

    Value* value = new UShortValue(&someValue);

    Exifdatum exifDatum(key, value);

    ed.add(exifDatum);



    ExifData::const_iterator it = sharpness(ed);

    EXPECT_EQ(it, ed.end());

}
