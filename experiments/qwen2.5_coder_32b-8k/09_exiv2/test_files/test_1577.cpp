#include <gtest/gtest.h>

#include "exiv2/rw2image.hpp"

#include "exiv2/exifdata.hpp"



using namespace Exiv2;



class Rw2ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> ioMock = BasicIo::autoPtr();

    std::unique_ptr<Rw2Image> rw2Image;



    void SetUp() override {

        rw2Image = std::make_unique<Rw2Image>(std::move(ioMock));

    }



    ExifData& getExifData() {

        return rw2Image->exifData();

    }

};



TEST_F(Rw2ImageTest_1577, PixelHeight_ReturnsZeroWhenKeyNotFound_1577) {

    EXPECT_EQ(rw2Image->pixelHeight(), 0U);

}



TEST_F(Rw2ImageTest_1577, PixelHeight_ReturnsZeroWhenCountIsZero_1577) {

    ExifData& exifData = getExifData();

    Exifdatum datum(ExifKey("Exif.PanasonicRaw.SensorHeight"), static_cast<const Value*>(nullptr));

    datum.setValue(0);

    exifData.add(datum);



    EXPECT_EQ(rw2Image->pixelHeight(), 0U);

}



TEST_F(Rw2ImageTest_1577, PixelHeight_ReturnsCorrectValueWhenKeyExists_1577) {

    ExifData& exifData = getExifData();

    uint32_t expectedHeight = 4896;

    Exifdatum datum(ExifKey("Exif.PanasonicRaw.SensorHeight"), static_cast<const Value*>(nullptr));

    datum.setValue(expectedHeight);

    exifData.add(datum);



    EXPECT_EQ(rw2Image->pixelHeight(), expectedHeight);

}



TEST_F(Rw2ImageTest_1577, PixelHeight_ReturnsBoundaryValueWhenKeyExists_1577) {

    ExifData& exifData = getExifData();

    uint32_t boundaryHeight = 0xFFFFFFFF;

    Exifdatum datum(ExifKey("Exif.PanasonicRaw.SensorHeight"), static_cast<const Value*>(nullptr));

    datum.setValue(boundaryHeight);

    exifData.add(datum);



    EXPECT_EQ(rw2Image->pixelHeight(), boundaryHeight);

}



TEST_F(Rw2ImageTest_1577, PixelHeight_ReturnsZeroForInvalidKey_1577) {

    ExifData& exifData = getExifData();

    uint32_t invalidValue = 4896;

    Exifdatum datum(ExifKey("Exif.Invalid.Tag"), static_cast<const Value*>(nullptr));

    datum.setValue(invalidValue);

    exifData.add(datum);



    EXPECT_EQ(rw2Image->pixelHeight(), 0U);

}
