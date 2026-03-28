#include <gtest/gtest.h>
#include <exiv2/rw2image.hpp>
#include <exiv2/error.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <sstream>
#include <memory>

namespace {

// Helper to create an Rw2Image with a MemIo (empty or with data)
std::unique_ptr<Exiv2::Rw2Image> createRw2ImageWithEmptyIo() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::Rw2Image>(std::move(io));
}

// Helper to create an Rw2Image from a file path (using FileIo)
std::unique_ptr<Exiv2::Rw2Image> createRw2ImageWithMemIo(const std::string& data) {
    auto io = std::make_unique<Exiv2::MemIo>(
        reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    return std::make_unique<Exiv2::Rw2Image>(std::move(io));
}

class Rw2ImageTest_1580 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createRw2ImageWithEmptyIo();
    }

    std::unique_ptr<Exiv2::Rw2Image> image_;
};

// Test that writeMetadata throws an exception with kerWritingImageFormatUnsupported
TEST_F(Rw2ImageTest_1580, WriteMetadataThrowsUnsupportedError_1580) {
    ASSERT_NE(image_, nullptr);
    try {
        image_->writeMetadata();
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerWritingImageFormatUnsupported);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but got a different exception";
    }
}

// Test that mimeType returns the expected MIME type for RW2
TEST_F(Rw2ImageTest_1580, MimeTypeReturnsCorrectValue_1580) {
    ASSERT_NE(image_, nullptr);
    std::string mime = image_->mimeType();
    EXPECT_EQ(mime, "image/x-panasonic-rw2");
}

// Test that setExifData does not throw (it's a no-op for RW2 based on typical behavior)
TEST_F(Rw2ImageTest_1580, SetExifDataDoesNotThrow_1580) {
    ASSERT_NE(image_, nullptr);
    Exiv2::ExifData exifData;
    EXPECT_NO_THROW(image_->setExifData(exifData));
}

// Test that setIptcData does not throw (it's a no-op for RW2 based on typical behavior)
TEST_F(Rw2ImageTest_1580, SetIptcDataDoesNotThrow_1580) {
    ASSERT_NE(image_, nullptr);
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(image_->setIptcData(iptcData));
}

// Test that setComment does not throw (it's a no-op for RW2 based on typical behavior)
TEST_F(Rw2ImageTest_1580, SetCommentDoesNotThrow_1580) {
    ASSERT_NE(image_, nullptr);
    EXPECT_NO_THROW(image_->setComment("test comment"));
}

// Test that setComment with empty string does not throw
TEST_F(Rw2ImageTest_1580, SetCommentEmptyStringDoesNotThrow_1580) {
    ASSERT_NE(image_, nullptr);
    EXPECT_NO_THROW(image_->setComment(""));
}

// Test readMetadata on empty IO - should throw or handle gracefully
TEST_F(Rw2ImageTest_1580, ReadMetadataOnEmptyIoThrows_1580) {
    ASSERT_NE(image_, nullptr);
    EXPECT_THROW(image_->readMetadata(), Exiv2::Error);
}

// Test pixelWidth returns a value (likely 0 for no data)
TEST_F(Rw2ImageTest_1580, PixelWidthDefaultValue_1580) {
    ASSERT_NE(image_, nullptr);
    // For an image with no valid data loaded, pixelWidth should return 0
    uint32_t width = image_->pixelWidth();
    EXPECT_EQ(width, 0u);
}

// Test pixelHeight returns a value (likely 0 for no data)
TEST_F(Rw2ImageTest_1580, PixelHeightDefaultValue_1580) {
    ASSERT_NE(image_, nullptr);
    uint32_t height = image_->pixelHeight();
    EXPECT_EQ(height, 0u);
}

// Test that writeMetadata exception message contains "RW2"
TEST_F(Rw2ImageTest_1580, WriteMetadataErrorMessageContainsRW2_1580) {
    ASSERT_NE(image_, nullptr);
    try {
        image_->writeMetadata();
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        std::string msg(e.what());
        EXPECT_NE(msg.find("RW2"), std::string::npos)
            << "Error message should contain 'RW2', but got: " << msg;
    }
}

// Test printStructure on empty IO
TEST_F(Rw2ImageTest_1580, PrintStructureOnEmptyIo_1580) {
    ASSERT_NE(image_, nullptr);
    std::ostringstream oss;
    // PrintStructureOption::kpsNone should be a safe option
    EXPECT_NO_THROW(image_->printStructure(oss, Exiv2::kpsNone, 0));
}

// Test creation with MemIo containing garbage data and readMetadata
TEST(Rw2ImageStandaloneTest_1580, ReadMetadataWithInvalidDataThrows_1580) {
    std::string garbage = "This is not a valid RW2 file content at all";
    auto io = std::make_unique<Exiv2::MemIo>(
        reinterpret_cast<const Exiv2::byte*>(garbage.data()), garbage.size());
    Exiv2::Rw2Image image(std::move(io));
    EXPECT_THROW(image.readMetadata(), Exiv2::Error);
}

// Test that writeMetadata always throws regardless of state
TEST(Rw2ImageStandaloneTest_1580, WriteMetadataAlwaysThrows_1580) {
    std::string garbage = "Some random data for testing";
    auto io = std::make_unique<Exiv2::MemIo>(
        reinterpret_cast<const Exiv2::byte*>(garbage.data()), garbage.size());
    Exiv2::Rw2Image image(std::move(io));
    EXPECT_THROW(image.writeMetadata(), Exiv2::Error);
}

// Test that multiple calls to writeMetadata all throw
TEST_F(Rw2ImageTest_1580, WriteMetadataMultipleCallsAllThrow_1580) {
    ASSERT_NE(image_, nullptr);
    EXPECT_THROW(image_->writeMetadata(), Exiv2::Error);
    EXPECT_THROW(image_->writeMetadata(), Exiv2::Error);
    EXPECT_THROW(image_->writeMetadata(), Exiv2::Error);
}

// Test that setExifData followed by writeMetadata still throws
TEST_F(Rw2ImageTest_1580, SetExifThenWriteStillThrows_1580) {
    ASSERT_NE(image_, nullptr);
    Exiv2::ExifData exifData;
    image_->setExifData(exifData);
    EXPECT_THROW(image_->writeMetadata(), Exiv2::Error);
}

// Test that setIptcData followed by writeMetadata still throws
TEST_F(Rw2ImageTest_1580, SetIptcThenWriteStillThrows_1580) {
    ASSERT_NE(image_, nullptr);
    Exiv2::IptcData iptcData;
    image_->setIptcData(iptcData);
    EXPECT_THROW(image_->writeMetadata(), Exiv2::Error);
}

// Test error code specifically
TEST_F(Rw2ImageTest_1580, WriteMetadataErrorCodeIsKerWritingImageFormatUnsupported_1580) {
    ASSERT_NE(image_, nullptr);
    bool caught = false;
    try {
        image_->writeMetadata();
    } catch (const Exiv2::Error& e) {
        caught = true;
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerWritingImageFormatUnsupported);
    }
    EXPECT_TRUE(caught);
}

}  // namespace
