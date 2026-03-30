#include <gtest/gtest.h>

#include "exiv2/mrwimage.hpp"

#include "exiv2/exifdata.hpp"

#include "exiv2/exifdatum.hpp"



namespace Exiv2 {

    class MrwImageTest_980 : public ::testing::Test {

    protected:

        void SetUp() override {

            io = std::make_unique<BasicIo>(nullptr); // Assuming BasicIo can be constructed with nullptr for testing

            mrwImage = std::make_unique<MrwImage>(std::move(io), false);

        }



        std::unique_ptr<BasicIo> io;

        std::unique_ptr<MrwImage> mrwImage;

    };



    TEST_F(MrwImageTest_980, PixelHeight_ReturnsZeroWhenExifDataEmpty_980) {

        EXPECT_EQ(mrwImage->pixelHeight(), 0u);

    }



    TEST_F(MrwImageTest_980, PixelHeight_ReturnsValueFromExifData_980) {

        Exifdatum exifDatum(ExifKey("Exif.Image.ImageLength"), nullptr);

        exifDatum.setValue(42u);

        mrwImage->exifData().add(exifDatum);



        EXPECT_EQ(mrwImage->pixelHeight(), 42u);

    }



    TEST_F(MrwImageTest_980, PixelHeight_ReturnsZeroWhenExifKeyNotFound_980) {

        Exifdatum exifDatum(ExifKey("Some.Other.Key"), nullptr);

        exifDatum.setValue(42u);

        mrwImage->exifData().add(exifDatum);



        EXPECT_EQ(mrwImage->pixelHeight(), 0u);

    }



    TEST_F(MrwImageTest_980, PixelHeight_ReturnsZeroWhenExifKeyCountIsZero_980) {

        Exifdatum exifDatum(ExifKey("Exif.Image.ImageLength"), nullptr);

        mrwImage->exifData().add(exifDatum);



        EXPECT_EQ(mrwImage->pixelHeight(), 0u);

    }



    TEST_F(MrwImageTest_980, PixelHeight_ReturnsValidValueWhenExifKeyCountIsOne_980) {

        Exifdatum exifDatum(ExifKey("Exif.Image.ImageLength"), nullptr);

        exifDatum.setValue(42u);

        mrwImage->exifData().add(exifDatum);



        EXPECT_EQ(mrwImage->pixelHeight(), 42u);

    }

}
