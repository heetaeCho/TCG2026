#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifKeyTest_1342 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Cleanup if needed

    }

};



TEST_F(ExifKeyTest_1342, DefaultTypeId_ReturnsUnknownTag_1342) {

    ExifKey key("unknown");

    EXPECT_EQ(key.defaultTypeId(), unknownTag.typeId_);

}



TEST_F(ExifKeyTest_1342, DefaultTypeId_ReturnsCorrectTypeId_1342) {

    TagInfo knownTag = {0x0112, "Orientation", "Image Orientation", "The orientation of the image.", IfdId::exifIfd, SectionId::sectionId1, asciiString, 1, printValue};

    ExifKey key(knownTag);

    EXPECT_EQ(key.defaultTypeId(), knownTag.typeId_);

}



TEST_F(ExifKeyTest_1342, DefaultTypeId_NullTagInfo_ReturnsUnknownTag_1342) {

    TagInfo nullTag = {};

    ExifKey key(nullTag);

    EXPECT_EQ(key.defaultTypeId(), unknownTag.typeId_);

}
