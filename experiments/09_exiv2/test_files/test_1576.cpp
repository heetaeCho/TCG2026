#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/image.hpp"

#include "exiv2/rw2image.hpp"



using namespace Exiv2;



class Rw2ImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        io = std::make_unique<BasicIo>();

        rw2Image = std::make_unique<Rw2Image>(std::move(io));

    }



    BasicIo::UniquePtr io;

    std::unique_ptr<Rw2Image> rw2Image;

};



TEST_F(Rw2ImageTest_1576, PixelWidth_ReturnsZeroWhenKeyNotFound_1576) {

    EXPECT_EQ(rw2Image->pixelWidth(), 0u);

}



TEST_F(Rw2ImageTest_1576, PixelWidth_ReturnsCorrectValueWhenKeyFound_1576) {

    Exifdatum exifDatum(ExifKey("Exif.PanasonicRaw.SensorWidth"), static_cast<const Value*>(nullptr));

    exifDatum.setValue(1920);

    rw2Image->exifData().add(exifDatum);



    EXPECT_EQ(rw2Image->pixelWidth(), 1920u);

}



TEST_F(Rw2ImageTest_1576, PixelWidth_ReturnsZeroWhenCountIsZero_1576) {

    Exifdatum exifDatum(ExifKey("Exif.PanasonicRaw.SensorWidth"), static_cast<const Value*>(nullptr));

    rw2Image->exifData().add(exifDatum);



    EXPECT_EQ(rw2Image->pixelWidth(), 0u);

}



TEST_F(Rw2ImageTest_1576, PixelWidth_ReturnsCorrectValueForBoundaryConditions_1576) {

    Exifdatum exifDatum(ExifKey("Exif.PanasonicRaw.SensorWidth"), static_cast<const Value*>(nullptr));

    exifDatum.setValue(std::numeric_limits<uint32_t>::max());

    rw2Image->exifData().add(exifDatum);



    EXPECT_EQ(rw2Image->pixelWidth(), std::numeric_limits<uint32_t>::max());

}
