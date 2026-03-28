#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/rafimage.hpp"

#include "exiv2/exif.hpp"



using namespace Exiv2;



class RafImageTest_219 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io;

    std::unique_ptr<RafImage> rafImage;



    void SetUp() override {

        io = BasicIo::createMemIo();

        rafImage = std::make_unique<RafImage>(std::move(io), false);

    }

};



TEST_F(RafImageTest_219, PixelHeight_ReturnsStoredValue_219) {

    rafImage->pixelHeight_ = 4032;

    EXPECT_EQ(rafImage->pixelHeight(), 4032);

}



TEST_F(RafImageTest_219, PixelHeight_ReturnsDefaultValueWhenNotSetAndKeyNotFound_219) {

    auto heightIter = rafImage->exifData_.findKey(ExifKey("Exif.Fujifilm.RawImageFullHeight"));

    if (heightIter != rafImage->exifData_.end()) {

        rafImage->exifData_.erase(heightIter);

    }

    EXPECT_EQ(rafImage->pixelHeight(), 0);

}



TEST_F(RafImageTest_219, PixelHeight_ReturnsValueFromExifKeyWhenNotSet_219) {

    Exifdatum exifDatum("Exif.Fujifilm.RawImageFullHeight", new Value(uint32_t(4032)));

    rafImage->exifData_.add(exifDatum);

    EXPECT_EQ(rafImage->pixelHeight(), 4032);

}



TEST_F(RafImageTest_219, PixelHeight_ReturnsZeroWhenKeyCountIsZero_219) {

    Exifdatum exifDatum("Exif.Fujifilm.RawImageFullHeight", new Value(uint32_t(4032)));

    exifDatum.setValue("");

    rafImage->exifData_.add(exifDatum);

    EXPECT_EQ(rafImage->pixelHeight(), 0);

}



TEST_F(RafImageTest_219, PixelHeight_ReturnsZeroWhenKeyNotFoundInExifData_219) {

    auto heightIter = rafImage->exifData_.findKey(ExifKey("Exif.Fujifilm.RawImageFullHeight"));

    if (heightIter != rafImage->exifData_.end()) {

        rafImage->exifData_.erase(heightIter);

    }

    EXPECT_EQ(rafImage->pixelHeight(), 0);

}
