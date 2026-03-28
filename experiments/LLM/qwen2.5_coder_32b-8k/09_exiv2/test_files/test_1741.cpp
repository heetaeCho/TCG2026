#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/cr2image.hpp"

#include "exiv2/exif.hpp"



using namespace Exiv2;

using testing::Return;



class Cr2ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::createMemIo();

    Cr2Image cr2Image{std::move(io), false};

};



TEST_F(Cr2ImageTest_1741, PixelHeight_ReturnsStoredValue_1741) {

    Exifdatum exifDatum(ExifKey("Exif.Photo.PixelYDimension"), new ULongValue);

    exifDatum.setValue(static_cast<uint32_t>(1080));

    cr2Image.exifData().add(exifDatum);



    EXPECT_EQ(cr2Image.pixelHeight(), 1080U);

}



TEST_F(Cr2ImageTest_1741, PixelHeight_ReturnsZeroIfKeyNotFound_1741) {

    EXPECT_EQ(cr2Image.pixelHeight(), 0U);

}



TEST_F(Cr2ImageTest_1741, PixelHeight_ReturnsZeroIfCountIsZero_1741) {

    Exifdatum exifDatum(ExifKey("Exif.Photo.PixelYDimension"), new ULongValue);

    cr2Image.exifData().add(exifDatum);



    EXPECT_EQ(cr2Image.pixelHeight(), 0U);

}
