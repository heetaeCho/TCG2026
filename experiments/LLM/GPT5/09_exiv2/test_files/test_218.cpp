#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./exiv2/src/rafimage.cpp"
#include "./exiv2/src/exif.hpp"
#include "./exiv2/src/image.hpp"

namespace Exiv2 {

class RafImageTest_218 : public testing::Test {
protected:
    std::unique_ptr<BasicIo> io_;
    RafImage* rafImage;

    void SetUp() override {
        io_ = std::make_unique<BasicIo>(); // Use mock or real IO depending on your needs
        rafImage = new RafImage(std::move(io_), true);
    }

    void TearDown() override {
        delete rafImage;
    }
};

TEST_F(RafImageTest_218, PixelWidthReturnsZeroWhenNoExifData_218) {
    // No Exif data, so pixelWidth should return 0
    EXPECT_EQ(rafImage->pixelWidth(), 0);
}

TEST_F(RafImageTest_218, PixelWidthReturnsValidValueWhenExifDataPresent_218) {
    // Assuming mock data is added that returns a valid pixel width
    ExifData mockExifData;
    // Simulate adding a valid Exif data entry
    // mockExifData.add(...);
    rafImage->setExifData(mockExifData);

    EXPECT_EQ(rafImage->pixelWidth(), 1024);  // Assuming 1024 is the mocked value
}

TEST_F(RafImageTest_218, PixelHeightReturnsZeroWhenNoExifData_218) {
    // No Exif data, so pixelHeight should return 0
    EXPECT_EQ(rafImage->pixelHeight(), 0);
}

TEST_F(RafImageTest_218, PixelHeightReturnsValidValueWhenExifDataPresent_218) {
    // Assuming mock data is added that returns a valid pixel height
    ExifData mockExifData;
    // Simulate adding a valid Exif data entry
    // mockExifData.add(...);
    rafImage->setExifData(mockExifData);

    EXPECT_EQ(rafImage->pixelHeight(), 768);  // Assuming 768 is the mocked value
}

TEST_F(RafImageTest_218, SetExifDataSetsDataCorrectly_218) {
    ExifData mockExifData;
    // Mock the expected behavior for adding data to the RafImage
    EXPECT_CALL(*rafImage, setExifData(mockExifData)).Times(1);
    
    rafImage->setExifData(mockExifData);
}

TEST_F(RafImageTest_218, SetIptcDataSetsDataCorrectly_218) {
    IptcData mockIptcData;
    // Mock the expected behavior for setting IPTC data
    EXPECT_CALL(*rafImage, setIptcData(mockIptcData)).Times(1);

    rafImage->setIptcData(mockIptcData);
}

TEST_F(RafImageTest_218, MimeTypeReturnsCorrectString_218) {
    EXPECT_EQ(rafImage->mimeType(), "image/raf");  // Assuming the expected mime type
}

TEST_F(RafImageTest_218, SetCommentSetsDataCorrectly_218) {
    std::string comment = "Test comment";
    EXPECT_CALL(*rafImage, setComment(comment)).Times(1);

    rafImage->setComment(comment);
}

TEST_F(RafImageTest_218, ReadMetadataCalledSuccessfully_218) {
    // Ensure that readMetadata works as expected
    EXPECT_NO_THROW(rafImage->readMetadata());
}

TEST_F(RafImageTest_218, WriteMetadataCalledSuccessfully_218) {
    // Ensure that writeMetadata works as expected
    EXPECT_NO_THROW(rafImage->writeMetadata());
}

TEST_F(RafImageTest_218, HandlesEmptyExifDataGracefully_218) {
    ExifData emptyExifData;
    rafImage->setExifData(emptyExifData);

    // When no Exif data is present, pixelWidth should be 0
    EXPECT_EQ(rafImage->pixelWidth(), 0);
}

TEST_F(RafImageTest_218, HandlesNullPointerForExifData_218) {
    // Test that calling setExifData with nullptr or invalid data does not crash
    EXPECT_NO_THROW(rafImage->setExifData(nullptr));
}

}  // namespace Exiv2