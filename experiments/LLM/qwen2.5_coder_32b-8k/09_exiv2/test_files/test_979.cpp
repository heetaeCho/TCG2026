#include <gtest/gtest.h>

#include "exiv2/mrwimage.hpp"

#include "exiv2/exif.hpp"



namespace Exiv2 {

    class MrwImageTest_979 : public ::testing::Test {

    protected:

        void SetUp() override {

            // Create a BasicIo object (mock or real, as needed)

            auto io = std::make_unique<BasicIo>();

            mrwImage = std::make_unique<MrwImage>(std::move(io), false);

        }



        std::unique_ptr<MrwImage> mrwImage;

    };



    TEST_F(MrwImageTest_979, PixelWidth_ReturnsZeroWhenKeyNotFound_979) {

        EXPECT_EQ(mrwImage->pixelWidth(), 0U);

    }



    TEST_F(MrwImageTest_979, PixelWidth_ReturnsCorrectValueWhenKeyExists_979) {

        // Manually add the Exif.Image.ImageWidth tag to the exifData

        Metadatum* imageWidth = new Exifdatum(ExifKey("Exif.Image.ImageWidth"), Value::create(TypeId::unsignedLong));

        dynamic_cast<Exifdatum*>(imageWidth)->setValue(static_cast<uint32_t>(1920));

        mrwImage->exifData().add(*dynamic_cast<Exifdatum*>(imageWidth));



        EXPECT_EQ(mrwImage->pixelWidth(), 1920U);

    }



    TEST_F(MrwImageTest_979, PixelWidth_ReturnsZeroWhenCountIsZero_979) {

        // Manually add the Exif.Image.ImageWidth tag with count 0 to the exifData

        Metadatum* imageWidth = new Exifdatum(ExifKey("Exif.Image.ImageWidth"), Value::create(TypeId::unsignedLong));

        mrwImage->exifData().add(*dynamic_cast<Exifdatum*>(imageWidth));



        EXPECT_EQ(mrwImage->pixelWidth(), 0U);

    }

}
