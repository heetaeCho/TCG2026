#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include "exiv2/types.hpp"



namespace {



class ImageTest : public ::testing::Test {

protected:

    Exiv2::Image* image;



    ImageTest() {

        // Since we cannot instantiate Image directly due to protected constructor,

        // we would typically use a derived class or a factory method here.

        // For the sake of this exercise, we assume a mock or a test-specific subclass is available.

        // Here, we are treating it as a black box and mocking is not allowed for internal behavior.

        image = nullptr; // In practice, initialize with a valid Image object

    }



    ~ImageTest() {

        delete image;

    }

};



TEST_F(ImageTest_1050, IsLongLongType_ReturnsTrueForUnsignedLongLong_1050) {

    EXPECT_TRUE(image->isLongLongType(Exiv2::unsignedLongLong));

}



TEST_F(ImageTest_1050, IsLongLongType_ReturnsTrueForSignedLongLong_1050) {

    EXPECT_TRUE(image->isLongLongType(Exiv2::signedLongLong));

}



TEST_F(ImageTest_1050, IsLongLongType_ReturnsFalseForOtherTypes_1050) {

    EXPECT_FALSE(image->isLongLongType(Exiv2::unsignedByte));

    EXPECT_FALSE(image->isLongLongType(Exiv2::asciiString));

    EXPECT_FALSE(image->isLongLongType(Exiv2::unsignedShort));

    EXPECT_FALSE(image->isLongLongType(Exiv2::unsignedLong));

    EXPECT_FALSE(image->isLongLongType(Exiv2::unsignedRational));

    EXPECT_FALSE(image->isLongLongType(Exiv2::signedByte));

    EXPECT_FALSE(image->isLongLongType(Exiv2::undefined));

    EXPECT_FALSE(image->isLongLongType(Exiv2::signedShort));

    EXPECT_FALSE(image->isLongLongType(Exiv2::signedLong));

    EXPECT_FALSE(image->isLongLongType(Exiv2::signedRational));

    EXPECT_FALSE(image->isLongLongType(Exiv2::tiffFloat));

    EXPECT_FALSE(image->isLongLongType(Exiv2::tiffDouble));

    EXPECT_FALSE(image->isLongLongType(Exiv2::tiffIfd));

    EXPECT_FALSE(image->isLongLongType(Exiv2::string));

    EXPECT_FALSE(image->isLongLongType(Exiv2::date));

    EXPECT_FALSE(image->isLongLongType(Exiv2::time));

    EXPECT_FALSE(image->isLongLongType(Exiv2::comment));

    EXPECT_FALSE(image->isLongLongType(Exiv2::directory));

    EXPECT_FALSE(image->isLongLongType(Exiv2::xmpText));

    EXPECT_FALSE(image->isLongLongType(Exiv2::xmpAlt));

    EXPECT_FALSE(image->isLongLongType(Exiv2::xmpBag));

    EXPECT_FALSE(image->isLongLongType(Exiv2::xmpSeq));

    EXPECT_FALSE(image->isLongLongType(Exiv2::langAlt));

}



}  // namespace
