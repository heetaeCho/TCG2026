#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    ImageTest() : image(ImageType::jpeg, 0x7FFF, nullptr) {}



    Image image;

};



TEST_F(ImageTest_1099, TagName_ReturnsKnownTag_1099) {

    uint16_t tag = 0x829A; // Example tag for ExposureTime

    EXPECT_EQ(image.tagName(tag), "ExposureTime");

}



TEST_F(ImageTest_1099, TagName_ReturnsUnknownTag_EmptyString_1099) {

    uint16_t unknownTag = 0xFFFF; // Invalid tag

    EXPECT_EQ(image.tagName(unknownTag), "");

}



TEST_F(ImageTest_1099, TagName_CalledTwice_ReturnsSameResult_1099) {

    uint16_t tag = 0x829A; // Example tag for ExposureTime

    std::string firstCall = image.tagName(tag);

    std::string secondCall = image.tagName(tag);

    EXPECT_EQ(firstCall, secondCall);

}



TEST_F(ImageTest_1099, TagName_BoundaryCondition_FirstTag_1099) {

    uint16_t firstTag = 0x010F; // Example tag for Make

    EXPECT_NE(image.tagName(firstTag), "");

}



TEST_F(ImageTest_1099, TagName_BoundaryCondition_LastTag_1099) {

    // Assuming the last tag in Nikon1MakerNote::tagList is 0xFFFF which is invalid

    uint16_t lastTag = 0x87D9; // Example tag for MakerNoteSafety

    EXPECT_NE(image.tagName(lastTag), "");

}
