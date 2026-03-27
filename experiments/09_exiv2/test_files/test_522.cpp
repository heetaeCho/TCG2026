#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/easyaccess.cpp"



namespace Exiv2 {



class ContrastFunctionTest : public ::testing::Test {

protected:

    ExifData ed;



    void SetUp() override {

        // Initialize with some known data if needed

    }

};



TEST_F(ContrastFunctionTest_522, FindExistingKey_522) {

    ExifKey key("Exif.Photo.Contrast");

    Value* value = new ShortValue();

    ed.add(key, value);



    auto it = contrast(ed);

    ASSERT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Photo.Contrast");

}



TEST_F(ContrastFunctionTest_522, FindNonExistingKey_522) {

    auto it = contrast(ed);

    EXPECT_EQ(it, ed.end());

}



TEST_F(ContrastFunctionTest_522, MultiplePossibleKeysFound_522) {

    ExifKey key1("Exif.Photo.Contrast");

    Value* value1 = new ShortValue();

    ed.add(key1, value1);



    ExifKey key2("Exif.CanonCs.Contrast");

    Value* value2 = new ShortValue();

    ed.add(key2, value2);



    auto it = contrast(ed);

    ASSERT_NE(it, ed.end());

    EXPECT_TRUE(it->key() == "Exif.Photo.Contrast" || it->key() == "Exif.CanonCs.Contrast");

}



TEST_F(ContrastFunctionTest_522, EmptyExifData_522) {

    auto it = contrast(ed);

    EXPECT_EQ(it, ed.end());

}



TEST_F(ContrastFunctionTest_522, KeyAtDifferentPosition_522) {

    ExifKey key("Exif.Sony1.Contrast");

    Value* value = new ShortValue();

    ed.add(key, value);



    auto it = contrast(ed);

    ASSERT_NE(it, ed.end());

    EXPECT_EQ(it->key(), "Exif.Sony1.Contrast");

}



}  // namespace Exiv2
