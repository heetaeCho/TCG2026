#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>
#include <cstring>

#include <exiv2/rw2image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image_types.hpp>

using namespace Exiv2;

// Test fixture for Rw2Image tests
class Rw2ImageTest_1578 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create an Rw2Image from a memory buffer
    std::unique_ptr<Rw2Image> createRw2ImageFromMemory(const uint8_t* data, size_t size) {
        auto io = std::make_unique<MemIo>(data, size);
        return std::make_unique<Rw2Image>(std::move(io));
    }

    // Helper to create an Rw2Image with empty data
    std::unique_ptr<Rw2Image> createEmptyRw2Image() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<Rw2Image>(std::move(io));
    }
};

// Test that mimeType returns the correct MIME type for RW2
TEST_F(Rw2ImageTest_1578, MimeType_ReturnsCorrectType_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_EQ("image/x-panasonic-rw2", image->mimeType());
}

// Test that the image type is correctly set to rw2
TEST_F(Rw2ImageTest_1578, ImageType_IsRw2_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_EQ(ImageType::rw2, image->imageType());
}

// Test that setExifData does not throw (but may be a no-op for RW2)
TEST_F(Rw2ImageTest_1578, SetExifData_DoesNotThrow_1578) {
    auto image = createEmptyRw2Image();
    ExifData exifData;
    EXPECT_NO_THROW(image->setExifData(exifData));
}

// Test that setIptcData does not throw (but may be a no-op for RW2)
TEST_F(Rw2ImageTest_1578, SetIptcData_DoesNotThrow_1578) {
    auto image = createEmptyRw2Image();
    IptcData iptcData;
    EXPECT_NO_THROW(image->setIptcData(iptcData));
}

// Test that setComment does not throw (but may be a no-op for RW2)
TEST_F(Rw2ImageTest_1578, SetComment_DoesNotThrow_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_NO_THROW(image->setComment("test comment"));
}

// Test that writeMetadata throws for RW2 (typically unsupported)
TEST_F(Rw2ImageTest_1578, WriteMetadata_ThrowsError_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_THROW(image->writeMetadata(), Error);
}

// Test that readMetadata throws with empty/invalid data
TEST_F(Rw2ImageTest_1578, ReadMetadata_EmptyData_ThrowsError_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test that printStructure outputs "RW2 IMAGE" header
TEST_F(Rw2ImageTest_1578, PrintStructure_OutputsHeader_1578) {
    // Create a minimal buffer that will at least allow open() to succeed
    // but will likely fail type checking
    auto image = createEmptyRw2Image();
    std::ostringstream oss;
    // printStructure should output "RW2 IMAGE" and then may throw
    // due to invalid data
    try {
        image->printStructure(oss, kpsNone, 0);
    } catch (const Error&) {
        // Expected - invalid data
    }
    // The header "RW2 IMAGE" should have been written before any error
    std::string output = oss.str();
    EXPECT_NE(std::string::npos, output.find("RW2 IMAGE"));
}

// Test that pixelWidth returns 0 for uninitialized image
TEST_F(Rw2ImageTest_1578, PixelWidth_DefaultIsZero_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_EQ(0u, image->pixelWidth());
}

// Test that pixelHeight returns 0 for uninitialized image
TEST_F(Rw2ImageTest_1578, PixelHeight_DefaultIsZero_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_EQ(0u, image->pixelHeight());
}

// Test that good() returns false for empty image (no valid data read)
TEST_F(Rw2ImageTest_1578, Good_EmptyImage_1578) {
    auto image = createEmptyRw2Image();
    // good() should reflect whether the image has valid metadata
    // For an empty image, it's typically false since no metadata was read
    // This depends on implementation, but we test the observable behavior
    bool result = image->good();
    // Just verify it doesn't crash - the result depends on implementation
    (void)result;
}

// Test that io() returns a valid reference
TEST_F(Rw2ImageTest_1578, IoReference_IsValid_1578) {
    auto image = createEmptyRw2Image();
    const BasicIo& io = image->io();
    // The io path should be accessible
    EXPECT_NO_THROW(io.path());
}

// Test that exifData() returns a reference (empty by default)
TEST_F(Rw2ImageTest_1578, ExifData_IsAccessible_1578) {
    auto image = createEmptyRw2Image();
    ExifData& data = image->exifData();
    EXPECT_TRUE(data.empty());
}

// Test that iptcData() returns a reference (empty by default)
TEST_F(Rw2ImageTest_1578, IptcData_IsAccessible_1578) {
    auto image = createEmptyRw2Image();
    IptcData& data = image->iptcData();
    EXPECT_TRUE(data.empty());
}

// Test that xmpData() returns a reference (empty by default)
TEST_F(Rw2ImageTest_1578, XmpData_IsAccessible_1578) {
    auto image = createEmptyRw2Image();
    XmpData& data = image->xmpData();
    EXPECT_TRUE(data.empty());
}

// Test readMetadata with invalid (random) data throws
TEST_F(Rw2ImageTest_1578, ReadMetadata_InvalidData_ThrowsError_1578) {
    uint8_t invalidData[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    auto image = createRw2ImageFromMemory(invalidData, sizeof(invalidData));
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test printStructure with invalid data throws after writing header
TEST_F(Rw2ImageTest_1578, PrintStructure_InvalidData_ThrowsAfterHeader_1578) {
    uint8_t invalidData[] = {0xFF, 0xFE, 0xFD, 0xFC};
    auto image = createRw2ImageFromMemory(invalidData, sizeof(invalidData));
    std::ostringstream oss;
    try {
        image->printStructure(oss, kpsNone, 0);
    } catch (const Error&) {
        // Expected
    }
    std::string output = oss.str();
    EXPECT_NE(std::string::npos, output.find("RW2 IMAGE"));
}

// Test clearMetadata on RW2 image
TEST_F(Rw2ImageTest_1578, ClearMetadata_DoesNotThrow_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_NO_THROW(image->clearMetadata());
}

// Test clearExifData
TEST_F(Rw2ImageTest_1578, ClearExifData_DoesNotThrow_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_NO_THROW(image->clearExifData());
}

// Test clearIptcData
TEST_F(Rw2ImageTest_1578, ClearIptcData_DoesNotThrow_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_NO_THROW(image->clearIptcData());
}

// Test clearXmpData
TEST_F(Rw2ImageTest_1578, ClearXmpData_DoesNotThrow_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_NO_THROW(image->clearXmpData());
}

// Test clearComment
TEST_F(Rw2ImageTest_1578, ClearComment_DoesNotThrow_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_NO_THROW(image->clearComment());
}

// Test that comment returns empty string by default
TEST_F(Rw2ImageTest_1578, Comment_DefaultIsEmpty_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_TRUE(image->comment().empty());
}

// Test printStructure with kpsBasic option
TEST_F(Rw2ImageTest_1578, PrintStructure_BasicOption_OutputsHeader_1578) {
    auto image = createEmptyRw2Image();
    std::ostringstream oss;
    try {
        image->printStructure(oss, kpsBasic, 0);
    } catch (const Error&) {
        // May throw due to invalid data
    }
    std::string output = oss.str();
    EXPECT_NE(std::string::npos, output.find("RW2 IMAGE"));
}

// Test printStructure with depth parameter
TEST_F(Rw2ImageTest_1578, PrintStructure_WithDepth_OutputsHeader_1578) {
    auto image = createEmptyRw2Image();
    std::ostringstream oss;
    try {
        image->printStructure(oss, kpsNone, 5);
    } catch (const Error&) {
        // May throw due to invalid data
    }
    std::string output = oss.str();
    EXPECT_NE(std::string::npos, output.find("RW2 IMAGE"));
}

// Test that byteOrder can be set and retrieved
TEST_F(Rw2ImageTest_1578, ByteOrder_SetAndGet_1578) {
    auto image = createEmptyRw2Image();
    image->setByteOrder(littleEndian);
    EXPECT_EQ(littleEndian, image->byteOrder());

    image->setByteOrder(bigEndian);
    EXPECT_EQ(bigEndian, image->byteOrder());
}

// Test that xmpPacket is accessible and empty by default
TEST_F(Rw2ImageTest_1578, XmpPacket_DefaultIsEmpty_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_TRUE(image->xmpPacket().empty());
}

// Test ICC profile is not defined by default
TEST_F(Rw2ImageTest_1578, IccProfile_NotDefinedByDefault_1578) {
    auto image = createEmptyRw2Image();
    EXPECT_FALSE(image->iccProfileDefined());
}
