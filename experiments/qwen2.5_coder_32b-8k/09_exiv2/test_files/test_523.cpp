#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/easyaccess.cpp"



using namespace Exiv2;



class SceneCaptureTypeTest_523 : public ::testing::Test {

protected:

    ExifData ed;

};



TEST_F(SceneCaptureTypeTest_523, NormalOperation_ExifPhotoSceneCaptureTypePresent_523) {

    ExifKey key("Exif.Photo.SceneCaptureType");

    Value* value = new ShortValue();

    static_cast<ShortValue*>(value)->setValue(1);

    ed.add(key, value);



    auto result = sceneCaptureType(ed);

    EXPECT_NE(result, ed.end());

    EXPECT_EQ((*result).key(), "Exif.Photo.SceneCaptureType");

}



TEST_F(SceneCaptureTypeTest_523, NormalOperation_ExifOlympusSpecialModePresent_523) {

    ExifKey key("Exif.Olympus.SpecialMode");

    Value* value = new ShortValue();

    static_cast<ShortValue*>(value)->setValue(1);

    ed.add(key, value);



    auto result = sceneCaptureType(ed);

    EXPECT_NE(result, ed.end());

    EXPECT_EQ((*result).key(), "Exif.Olympus.SpecialMode");

}



TEST_F(SceneCaptureTypeTest_523, Boundary_NoKeysPresent_523) {

    auto result = sceneCaptureType(ed);

    EXPECT_EQ(result, ed.end());

}



TEST_F(SceneCaptureTypeTest_523, Boundary_EmptyExifData_523) {

    ed.clear();

    auto result = sceneCaptureType(ed);

    EXPECT_EQ(result, ed.end());

}
