#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifKeyTest_1341 : public ::testing::Test {

protected:

    TagInfo tagInfo;

};



TEST_F(ExifKeyTest_1341, TagDesc_NormalOperation_1341) {

    tagInfo.tag_ = 0x0100;

    tagInfo.desc_ = "Sample Description";

    ExifKey key(tagInfo);

    EXPECT_EQ(key.tagDesc(), "Sample Description");

}



TEST_F(ExifKeyTest_1341, TagDesc_TagNotSet_1341) {

    ExifKey key(tagInfo); // Assuming tagInfo is initialized with default values where tag_ = 0xffff

    EXPECT_EQ(key.tagDesc(), "");

}



TEST_F(ExifKeyTest_1341, TagDesc_TagZeroFFFF_1341) {

    tagInfo.tag_ = 0xFFFF;

    ExifKey key(tagInfo);

    EXPECT_EQ(key.tagDesc(), "");

}
