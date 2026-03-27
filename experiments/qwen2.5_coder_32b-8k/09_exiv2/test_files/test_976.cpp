#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include "exiv2/src/pngimage.cpp"



using namespace Exiv2;



class PngImageTest_976 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    Image::UniquePtr image;



    void SetUp() override {

        io = BasicIo::createMemIo();

        image = newPngInstance(std::move(io), false);

    }

};



TEST_F(PngImageTest_976, GoodReturnsTrueForValidImage_976) {

    EXPECT_TRUE(image->good());

}



TEST_F(PngImageTest_976, GoodReturnsFalseForNullIo_976) {

    io.reset();

    image = newPngInstance(std::move(io), false);

    EXPECT_FALSE(image);

}



TEST_F(PngImageTest_976, CreateFlagDoesNotAffectGoodCheck_976) {

    image = newPngInstance(BasicIo::createMemIo(), true);

    EXPECT_TRUE(image->good());

}



TEST_F(PngImageTest_976, MimeTypeReturnsCorrectType_976) {

    EXPECT_EQ(image->mimeType(), "image/png");

}



TEST_F(PngImageTest_976, PixelWidthInitiallyZero_976) {

    EXPECT_EQ(image->pixelWidth(), 0u);

}



TEST_F(PngImageTest_976, PixelHeightInitiallyZero_976) {

    EXPECT_EQ(image->pixelHeight(), 0u);

}



TEST_F(PngImageTest_976, CommentInitiallyEmpty_976) {

    EXPECT_TRUE(image->comment().empty());

}
