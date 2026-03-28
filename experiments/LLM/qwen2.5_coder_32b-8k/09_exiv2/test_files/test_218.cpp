#include <gtest/gtest.h>

#include "exiv2/rafimage.hpp"

#include "exiv2/exifdata.hpp"



using namespace Exiv2;



class RafImageTest_218 : public ::testing::Test {

protected:

    void SetUp() override {

        io = std::make_unique<BasicIo>(nullptr);

        rafImage = new RafImage(std::move(io), false);

    }



    void TearDown() override {

        delete rafImage;

    }



    BasicIo::UniquePtr io;

    RafImage* rafImage;

};



TEST_F(RafImageTest_218, PixelWidth_ReturnsPredefinedValue_218) {

    uint32_t predefinedWidth = 4096;

    rafImage->pixelWidth_ = predefinedWidth;

    EXPECT_EQ(predefinedWidth, rafImage->pixelWidth());

}



TEST_F(RafImageTest_218, PixelWidth_ReturnsExifValue_218) {

    uint32_t exifWidth = 4096;

    ExivKey key("Exif.Fujifilm.RawImageFullWidth");

    Value::AutoPtr value = Value::create(Exifdatum::tagType(key));

    value->read(&exifWidth, 1);

    rafImage->exifData_.add(key, value.get());

    EXPECT_EQ(exifWidth, rafImage->pixelWidth());

}



TEST_F(RafImageTest_218, PixelWidth_ReturnsZeroWhenExifKeyNotFound_218) {

    rafImage->exifData_.clear();

    EXPECT_EQ(0U, rafImage->pixelWidth());

}



TEST_F(RafImageTest_218, PixelWidth_ReturnsZeroWhenExifValueCountIsZero_218) {

    ExivKey key("Exif.Fujifilm.RawImageFullWidth");

    Value::AutoPtr value = Value::create(Exifdatum::tagType(key));

    rafImage->exifData_.add(key, value.get());

    EXPECT_EQ(0U, rafImage->pixelWidth());

}
