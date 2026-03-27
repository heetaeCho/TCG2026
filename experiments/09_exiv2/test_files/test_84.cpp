#include <gtest/gtest.h>

#include "exiv2/jp2image.hpp"

#include "exiv2/basicio.hpp"



namespace {



class Jp2ImageTest_84 : public ::testing::Test {

protected:

    void SetUp() override {

        io = Exiv2::BasicIo::createMemIo();

        jp2Image = std::make_unique<Exiv2::Jp2Image>(std::move(io), false);

    }



    void TearDown() override {

        jp2Image.reset();

        io.reset();

    }



    std::unique_ptr<Exiv2::BasicIo> io;

    std::unique_ptr<Exiv2::Jp2Image> jp2Image;

};



TEST_F(Jp2ImageTest_84, MimeTypeDefault_84) {

    EXPECT_EQ(jp2Image->mimeType(), "image/jp2");

}



TEST_F(Jp2ImageTest_84, MimeTypeBrandJph_84) {

    jp2Image->brand_ = Exiv2::Internal::brandJph;

    EXPECT_EQ(jp2Image->mimeType(), "image/jph");

}



}  // namespace
