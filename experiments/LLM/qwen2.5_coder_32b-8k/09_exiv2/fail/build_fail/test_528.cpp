#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"



namespace Exiv2 {

    class ExifData;

    ExifData::const_iterator fNumber(const ExifData& ed);

}



using namespace Exiv2;



class FNumberTest_528 : public ::testing::Test {

protected:

    ExifData exifData;

};



TEST_F(FNumberTest_528, FindFNumberWithValidKey_528) {

    // Arrange

    std::string validKey = "Exif.Photo.FNumber";

    Value* value = new UShortValue;  // Assuming UShortValue is a type that can be used for FNumber

    ExifKey exifKey(validKey);

    exifData.add(exifKey, value);



    // Act

    ExifData::const_iterator result = fNumber(exifData);



    // Assert

    EXPECT_NE(result, exifData.end());

    EXPECT_EQ(result->key(), validKey);



    delete value;

}



TEST_F(FNumberTest_528, FindFNumberWithNonExistentKey_528) {

    // Arrange & Act

    ExifData::const_iterator result = fNumber(exifData);



    // Assert

    EXPECT_EQ(result, exifData.end());

}



TEST_F(FNumberTest_528, FindFNumberWithMultiplePossibleKeys_528) {

    // Arrange

    std::string validKey1 = "Exif.Photo.FNumber";

    std::string validKey2 = "Exif.Image.FNumber";

    Value* value1 = new UShortValue;

    Value* value2 = new UShortValue;

    ExifKey exifKey1(validKey1);

    ExifKey exifKey2(validKey2);

    exifData.add(exifKey1, value1);

    exifData.add(exifKey2, value2);



    // Act

    ExifData::const_iterator result = fNumber(exifData);



    // Assert

    EXPECT_NE(result, exifData.end());

    EXPECT_TRUE(result->key() == validKey1 || result->key() == validKey2);



    delete value1;

    delete value2;

}



TEST_F(FNumberTest_528, FindFNumberWithEmptyExifData_528) {

    // Arrange & Act

    ExifData::const_iterator result = fNumber(exifData);



    // Assert

    EXPECT_EQ(result, exifData.end());

}
