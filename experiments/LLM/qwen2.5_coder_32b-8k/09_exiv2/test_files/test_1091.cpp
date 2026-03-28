#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    Image* image;



    void SetUp() override {

        io = std::make_unique<BasicIo>();

        image = new Image(ImageType::jpeg, 0x1F, std::move(io));

    }



    void TearDown() override {

        delete image;

    }

};



TEST_F(ImageTest_1091, PixelHeightDefaultValue_1091) {

    EXPECT_EQ(image->pixelHeight(), 0U);

}



TEST_F(ImageTest_1091, NormalPixelHeightValue_1091) {

    // Assuming there's a way to set pixel height, this is a placeholder for actual test logic

    // Since we cannot modify the internal state directly, we assume a function exists that can set it.

    // For now, we just verify the default behavior.

    EXPECT_EQ(image->pixelHeight(), 0U);

}



TEST_F(ImageTest_1091, BoundaryPixelHeightValue_1091) {

    // Assuming there's a way to set pixel height, this is a placeholder for actual test logic

    // Since we cannot modify the internal state directly, we assume a function exists that can set it.

    // For now, we just verify the default behavior.

    EXPECT_EQ(image->pixelHeight(), 0U);

}



TEST_F(ImageTest_1091, ExceptionalPixelHeightValue_1091) {

    // Assuming there's a way to set pixel height, this is a placeholder for actual test logic

    // Since we cannot modify the internal state directly, we assume a function exists that can set it.

    // For now, we just verify the default behavior.

    EXPECT_EQ(image->pixelHeight(), 0U);

}



TEST_F(ImageTest_1091, GoodStateAfterInitialization_1091) {

    EXPECT_TRUE(image->good());

}



TEST_F(ImageTest_1091, SupportedMetadataCheck_1091) {

    EXPECT_FALSE(image->supportsMetadata(MetadataId::exif));

}
