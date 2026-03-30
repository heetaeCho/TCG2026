#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



namespace Exiv2 {

    struct TagInfo {};

}



using namespace Exiv2;



class ExifKeyTest_1339 : public ::testing::Test {

protected:

    ExifKey exifKey;

};



TEST_F(ExifKeyTest_1339, DefaultConstructor_1339) {

    EXPECT_EQ(exifKey.tagName(), "");

}



TEST_F(ExifKeyTest_1339, ConstructorWithString_1339) {

    ExifKey key("Exif.Image.Artist");

    EXPECT_NE(key.tagName(), "");

}



TEST_F(ExifKeyTest_1339, ConstructorWithUint16AndGroupName_1339) {

    ExifKey key(0x132, "ExifIFD");

    EXPECT_NE(key.tagName(), "");

}



TEST_F(ExifKeyTest_1339, CopyConstructor_1339) {

    ExifKey original("Exif.Image.Artist");

    ExifKey copy(original);

    EXPECT_EQ(copy.tagName(), original.tagName());

}



TEST_F(ExifKeyTest_1339, AssignmentOperator_1339) {

    ExifKey original("Exif.Image.Artist");

    ExifKey assigned;

    assigned = original;

    EXPECT_EQ(assigned.tagName(), original.tagName());

}



TEST_F(ExifKeyTest_1339, SetIdxAndGetIdx_1339) {

    exifKey.setIdx(5);

    EXPECT_EQ(exifKey.idx(), 5);

}



TEST_F(ExifKeyTest_1339, TagName_ReturnsExpectedValue_1339) {

    ExifKey key("Exif.Image.Artist");

    EXPECT_NE(key.tagName(), "");

}
