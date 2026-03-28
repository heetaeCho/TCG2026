#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifKeyTest_1344 : public ::testing::Test {

protected:

    ExifKey key1;

    ExifKey key2;



    ExifKeyTest_1344() 

        : key1("Exif.Image.Artist"),

          key2(0x013B, "Exif.Image")

    {}

};



TEST_F(ExifKeyTest_1344, CloneReturnsNewInstance_1344) {

    auto clonedKey = key1.clone();

    EXPECT_NE(&key1, clonedKey.get());

}



TEST_F(ExifKeyTest_1344, KeyMethodReturnsCorrectString_1344) {

    EXPECT_EQ("Exif.Image.Artist", key1.key());

    EXPECT_EQ("0x013b", key2.key()); // Assuming key() returns tag in hex for numeric tags

}



TEST_F(ExifKeyTest_1344, GroupNameMethodReturnsCorrectString_1344) {

    EXPECT_EQ("Exif.Image", key1.groupName());

    EXPECT_EQ("Exif.Image", key2.groupName());

}



TEST_F(ExifKeyTest_1344, SetIdxAndGetIdxWorkProperly_1344) {

    key1.setIdx(5);

    EXPECT_EQ(5, key1.idx());



    key2.setIdx(-1);

    EXPECT_EQ(-1, key2.idx());

}



TEST_F(ExifKeyTest_1344, TagMethodReturnsCorrectValue_1344) {

    EXPECT_NE(0x013B, key1.tag()); // Assuming tag() returns the numeric tag for string keys

    EXPECT_EQ(0x013B, key2.tag());

}



TEST_F(ExifKeyTest_1344, BoundaryConditionsWithEmptyString_1344) {

    ExifKey emptyKey("");

    EXPECT_NE("", emptyKey.key()); // Assuming it doesn't throw and returns a default or error string

}



TEST_F(ExifKeyTest_1344, BoundaryConditionsWithInvalidTag_1344) {

    ExifKey invalidKey(0xFFFF, "Invalid.Group");

    EXPECT_EQ("0xffff", invalidKey.key()); // Assuming it doesn't throw and returns the tag in hex

}
