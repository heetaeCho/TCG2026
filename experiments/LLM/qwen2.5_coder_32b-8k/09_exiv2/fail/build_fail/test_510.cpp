#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/easyaccess.cpp"



namespace {



class ExifDataTest : public ::testing::Test {

protected:

    Exiv2::ExifData exif_data;



    void SetUp() override {

        // Set up any common state before each test

    }



    void TearDown() override {

        // Clean up after each test

        exif_data.clear();

    }

};



TEST_F(ExifDataTest_510, FindOrientation_NormalOperation_510) {

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::shortMime);

    value->read("1");

    exif_data.add(Exiv2::ExifKey("Exif.Image.Orientation"), value);



    auto it = Exiv2::orientation(exif_data);

    EXPECT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), "Exif.Image.Orientation");

}



TEST_F(ExifDataTest_510, FindOrientation_NotFound_510) {

    auto it = Exiv2::orientation(exif_data);

    EXPECT_EQ(it, exif_data.end());

}



TEST_F(ExifDataTest_510, FindOrientation_MultipleKeys_510) {

    Exiv2::Value* value1 = Exiv2::Value::create(Exiv2::shortMime);

    value1->read("1");

    exif_data.add(Exiv2::ExifKey("Exif.Panasonic.Rotation"), value1);



    Exiv2::Value* value2 = Exiv2::Value::create(Exiv2::shortMime);

    value2->read("2");

    exif_data.add(Exiv2::ExifKey("Exif.Image.Orientation"), value2);



    auto it = Exiv2::orientation(exif_data);

    EXPECT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), "Exif.Image.Orientation");

}



TEST_F(ExifDataTest_510, FindOrientation_BoundaryCondition_EmptyKey_510) {

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::shortMime);

    value->read("1");

    exif_data.add(Exiv2::ExifKey(""), value);



    auto it = Exiv2::orientation(exif_data);

    EXPECT_EQ(it, exif_data.end());

}



TEST_F(ExifDataTest_510, FindOrientation_BoundaryCondition_EmptyValue_510) {

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::shortMime);

    value->read("");

    exif_data.add(Exiv2::ExifKey("Exif.Image.Orientation"), value);



    auto it = Exiv2::orientation(exif_data);

    EXPECT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), "Exif.Image.Orientation");

}



TEST_F(ExifDataTest_510, FindOrientation_ErrorCase_InvalidValue_510) {

    Exiv2::Value* value = Exiv2::Value::create(Exiv2::shortMime);

    value->read("invalid"); // This should be handled gracefully

    exif_data.add(Exiv2::ExifKey("Exif.Image.Orientation"), value);



    auto it = Exiv2::orientation(exif_data);

    EXPECT_NE(it, exif_data.end());

    EXPECT_EQ(it->key(), "Exif.Image.Orientation");

}



}  // namespace
