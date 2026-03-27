#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class LightSourceTest_535 : public ::testing::Test {

protected:

    ExifData ed;

};



TEST_F(LightSourceTest_535, NormalOperation_ExifPhotoLightSourceFound_535) {

    // Arrange

    ExifKey key("Exif.Photo.LightSource");

    Value* value = new LongValue(1);

    Exifdatum datum(key, value);

    ed.add(datum);



    // Act & Assert

    EXPECT_NE(lightSource(ed), ed.end());

}



TEST_F(LightSourceTest_535, NormalOperation_ExifImageLightSourceFound_535) {

    // Arrange

    ExifKey key("Exif.Image.LightSource");

    Value* value = new LongValue(2);

    Exifdatum datum(key, value);

    ed.add(datum);



    // Act & Assert

    EXPECT_NE(lightSource(ed), ed.end());

}



TEST_F(LightSourceTest_535, NormalOperation_NoLightSourcesFound_535) {

    // Arrange - No LightSource keys added



    // Act & Assert

    EXPECT_EQ(lightSource(ed), ed.end());

}



TEST_F(LightSourceTest_535, BoundaryCondition_EmptyExifData_535) {

    // Arrange - ExifData is empty



    // Act & Assert

    EXPECT_EQ(lightSource(ed), ed.end());

}
