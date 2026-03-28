#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "gifimage.hpp"
#include "error.hpp"

// Mocking the dependencies if necessary
// For this example, assume BasicIo and Image are properly mocked as needed

namespace Exiv2 {

class GifImageTest : public ::testing::Test {
protected:
    // Test setup for the GifImage class
    std::unique_ptr<GifImage> gifImage;
    // A mock or real BasicIo object (depending on your setup)
    BasicIo::UniquePtr mockIo;

    void SetUp() override {
        // Initialize GifImage with mock or real BasicIo
        gifImage = std::make_unique<GifImage>(std::move(mockIo));
    }
};

TEST_F(GifImageTest, WriteMetadata_ThrowsError_32) {
    // TEST_ID: 212
    // Verifies that calling writeMetadata on GifImage throws an Error with error code kerWritingImageFormatUnsupported (32)
    
    try {
        gifImage->writeMetadata();
        FAIL() << "Expected Error to be thrown";
    } catch (const Error& e) {
        EXPECT_EQ(e.code(), ErrorCode::kerWritingImageFormatUnsupported);
        EXPECT_EQ(e.what(), "GIF");
    }
}

TEST_F(GifImageTest, SetExifData_ThrowsNothing) {
    // TEST_ID: 213
    // Verifies that calling setExifData doesn't throw any error.
    ExifData exifData;
    EXPECT_NO_THROW(gifImage->setExifData(exifData));
}

TEST_F(GifImageTest, SetIptcData_ThrowsNothing) {
    // TEST_ID: 214
    // Verifies that calling setIptcData doesn't throw any error.
    IptcData iptcData;
    EXPECT_NO_THROW(gifImage->setIptcData(iptcData));
}

TEST_F(GifImageTest, SetComment_ThrowsNothing) {
    // TEST_ID: 215
    // Verifies that calling setComment doesn't throw any error.
    std::string comment = "Test comment";
    EXPECT_NO_THROW(gifImage->setComment(comment));
}

TEST_F(GifImageTest, MimeType_ReturnsCorrectMimeType) {
    // TEST_ID: 216
    // Verifies that the mimeType method returns "image/gif" for GifImage
    EXPECT_EQ(gifImage->mimeType(), "image/gif");
}

} // namespace Exiv2