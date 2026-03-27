#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::createMemIo();

    Image* image = new Image(imageTypeNone, 0, std::move(io));



    ~ImageTest() override {

        delete image;

    }

};



TEST_F(ImageTest_1048, IsShortType_ReturnsTrueForUnsignedShort_1048) {

    EXPECT_TRUE(image->isShortType(unsignedShort));

}



TEST_F(ImageTest_1048, IsShortType_ReturnsTrueForSignedShort_1048) {

    EXPECT_TRUE(image->isShortType(signedShort));

}



TEST_F(ImageTest_1048, IsShortType_ReturnsFalseForOtherTypes_1048) {

    EXPECT_FALSE(image->isShortType(unsignedByte));

    EXPECT_FALSE(image->isShortType(asciiString));

    EXPECT_FALSE(image->isShortType(unsignedLong));

    // Add more types as needed to cover other cases

}



TEST_F(ImageTest_1048, IsShortType_BoundaryConditionWithMinValue_1048) {

    EXPECT_FALSE(image->isShortType(static_cast<uint16_t>(0)));

}



TEST_F(ImageTest_1048, IsShortType_BoundaryConditionWithMaxValue_1048) {

    EXPECT_FALSE(image->isShortType(static_cast<uint16_t>(65535)));

}
