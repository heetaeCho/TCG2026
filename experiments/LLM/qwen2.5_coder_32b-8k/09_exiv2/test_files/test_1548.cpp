#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/orfimage.hpp"

#include "exiv2/exif.hpp"



namespace Exiv2 {

    class MockBasicIo : public BasicIo {

    public:

        MOCK_METHOD(void, open, (OpenMode mode), (override));

        MOCK_METHOD(void, close, (), (override));

        MOCK_METHOD(bool, good, (), (const, override));

        MOCK_METHOD(size_t, read, (byte* buf, size_t nbytes), (override));

        MOCK_METHOD(size_t, write, (const byte* buf, size_t nbytes), (override));

        MOCK_METHOD(void, seek, (long offset, Position pos), (override));

        MOCK_METHOD(long, tell, (), (const, override));

        MOCK_METHOD(void, invalidate, (), (override));

        MOCK_METHOD(void, flush, (), (override));

        MOCK_METHOD(size_t, size, (), (const, override));

    };



    class OrfImageTest : public ::testing::Test {

    protected:

        void SetUp() override {

            io = std::make_unique<MockBasicIo>();

            orfImage = new OrfImage(std::move(io), false);

        }



        void TearDown() override {

            delete orfImage;

        }



        BasicIo::UniquePtr io;

        OrfImage* orfImage;

    };



    TEST_F(OrfImageTest_1548, PixelWidth_ReturnsZeroWhenKeyNotFound_1548) {

        EXPECT_EQ(orfImage->pixelWidth(), 0u);

    }



    TEST_F(OrfImageTest_1548, PixelWidth_ReturnsCorrectValueWhenKeyExists_1548) {

        ExifData exifData;

        Exiv2::Exifdatum datum(Exiv2::ExifKey("Exif.Image.ImageWidth"), nullptr);

        datum.setValue(uint32_t(1920));

        exifData.add(datum);

        orfImage->setExifData(exifData);



        EXPECT_EQ(orfImage->pixelWidth(), 1920u);

    }



    TEST_F(OrfImageTest_1548, PixelWidth_ReturnsZeroWhenCountIsZero_1548) {

        ExifData exifData;

        Exiv2::Exifdatum datum(Exiv2::ExifKey("Exif.Image.ImageWidth"), nullptr);

        exifData.add(datum); // count will be 0 as no value is set

        orfImage->setExifData(exifData);



        EXPECT_EQ(orfImage->pixelWidth(), 0u);

    }



    TEST_F(OrfImageTest_1548, PixelWidth_ReturnsZeroWhenKeyHasNoValue_1548) {

        ExifData exifData;

        Exiv2::Exifdatum datum(Exiv2::ExifKey("Exif.Image.ImageWidth"), nullptr);

        exifData.add(datum); // count will be 0 as no value is set

        orfImage->setExifData(exifData);



        EXPECT_EQ(orfImage->pixelWidth(), 0u);

    }



} // namespace Exiv2
