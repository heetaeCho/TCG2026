#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include <memory>



using namespace Exiv2;



class ImageTest_56 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    Image* image;



    void SetUp() override {

        io = std::make_unique<BasicIo>();

        image = new Image(imageJpeg, 0x1F, std::move(io));

    }



    void TearDown() override {

        delete image;

    }

};



TEST_F(ImageTest_56, setTypeSupported_SetsImageTypeAndMetadata_56) {

    image->setTypeSupported(imageTiff, 0xFF);

    EXPECT_EQ(image->imageType(), imageTiff);

}



TEST_F(ImageTest_56, supportsMetadata_ReturnsTrueForSupported_56) {

    image->setTypeSupported(imageJpeg, 0x1F);

    EXPECT_TRUE(image->supportsMetadata(mdExif));

}



TEST_F(ImageTest_56, supportsMetadata_ReturnsFalseForUnsupported_56) {

    image->setTypeSupported(imageJpeg, 0x1F);

    EXPECT_FALSE(image->supportsMetadata(mdXmp));

}



TEST_F(ImageTest_56, byteOrder_DefaultsToInvalidByteOrder_56) {

    EXPECT_EQ(image->byteOrder(), invalidByteOrder);

}



TEST_F(ImageTest_56, setByteOrder_ChangesByteOrder_56) {

    image->setByteOrder(bigEndian);

    EXPECT_EQ(image->byteOrder(), bigEndian);

}



TEST_F(ImageTest_56, pixelWidth_DefaultsToZero_56) {

    EXPECT_EQ(image->pixelWidth(), 0u);

}



TEST_F(ImageTest_56, pixelHeight_DefaultsToZero_56) {

    EXPECT_EQ(image->pixelHeight(), 0u);

}



TEST_F(ImageTest_56, comment_DefaultsToEmptyString_56) {

    EXPECT_EQ(image->comment(), "");

}



TEST_F(ImageTest_56, good_ReturnsTrueInitially_56) {

    EXPECT_TRUE(image->good());

}
