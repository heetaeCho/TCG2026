#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;



class ImageTest_1051 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::createMemIo();

    Image* image = new Image(imageTypeJpeg, 0x0FFF, std::move(io));



    ~ImageTest_1051() override {

        delete image;

    }

};



TEST_F(ImageTest_1051, IsRationalType_UnsignedRational_ReturnsTrue_1051) {

    EXPECT_TRUE(image->isRationalType(unsignedRational));

}



TEST_F(ImageTest_1051, IsRationalType_SignedRational_ReturnsTrue_1051) {

    EXPECT_TRUE(image->isRationalType(signedRational));

}



TEST_F(ImageTest_1051, IsRationalType_OtherType_ReturnsFalse_1051) {

    EXPECT_FALSE(image->isRationalType(unsignedByte));

}



TEST_F(ImageTest_1051, IsRationalType_InvalidTypeId_ReturnsFalse_1051) {

    EXPECT_FALSE(image->isRationalType(invalidTypeId));

}



TEST_F(ImageTest_1051, IsRationalType_Zero_ReturnsFalse_1051) {

    EXPECT_FALSE(image->isRationalType(0));

}



TEST_F(ImageTest_1051, IsRationalType_LastTypeId_ReturnsFalse_1051) {

    EXPECT_FALSE(image->isRationalType(lastTypeId));

}
