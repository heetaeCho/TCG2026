#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/bmffimage.hpp>
#include <exiv2/error.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

#include <memory>
#include <sstream>

namespace {

// Helper to create a BmffImage with a MemIo (in-memory IO)
std::unique_ptr<Exiv2::BmffImage> createBmffImage(const std::string& data = "", size_t max_box_depth = 1000) {
    auto io = std::make_unique<Exiv2::MemIo>(
        reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    return std::make_unique<Exiv2::BmffImage>(std::move(io), false, max_box_depth);
}

// Minimal valid HEIF/BMFF ftyp box for testing
std::string createMinimalFtypBox() {
    // A minimal ftyp box: size(4) + 'ftyp'(4) + brand(4) + version(4) = 16 bytes minimum
    std::string data;
    // Box size: 20 bytes (big-endian)
    data += '\0';
    data += '\0';
    data += '\0';
    data += '\x14'; // 20
    // Box type: 'ftyp'
    data += 'f';
    data += 't';
    data += 'y';
    data += 'p';
    // Major brand: 'heic'
    data += 'h';
    data += 'e';
    data += 'i';
    data += 'c';
    // Minor version: 0
    data += '\0';
    data += '\0';
    data += '\0';
    data += '\0';
    // Compatible brand: 'heic'
    data += 'h';
    data += 'e';
    data += 'i';
    data += 'c';
    return data;
}

class BmffImageTest_1202 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that writeMetadata throws an Error with kerWritingImageFormatUnsupported
TEST_F(BmffImageTest_1202, WriteMetadataThrowsUnsupported_1202) {
    auto image = createBmffImage();
    EXPECT_THROW({
        image->writeMetadata();
    }, Exiv2::Error);
}

// Test that writeMetadata throws specifically kerWritingImageFormatUnsupported
TEST_F(BmffImageTest_1202, WriteMetadataThrowsCorrectErrorCode_1202) {
    auto image = createBmffImage();
    try {
        image->writeMetadata();
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerWritingImageFormatUnsupported);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error, got different exception";
    }
}

// Test that setComment does not throw (but likely does nothing or throws unsupported)
TEST_F(BmffImageTest_1202, SetCommentDoesNotCrash_1202) {
    auto image = createBmffImage();
    // setComment may throw or be a no-op; just verify it doesn't crash unexpectedly
    EXPECT_NO_THROW(image->setComment("test comment"));
}

// Test that setExifData does not crash
TEST_F(BmffImageTest_1202, SetExifDataDoesNotCrash_1202) {
    auto image = createBmffImage();
    Exiv2::ExifData exifData;
    EXPECT_NO_THROW(image->setExifData(exifData));
}

// Test that setIptcData does not crash
TEST_F(BmffImageTest_1202, SetIptcDataDoesNotCrash_1202) {
    auto image = createBmffImage();
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(image->setIptcData(iptcData));
}

// Test that setXmpData does not crash
TEST_F(BmffImageTest_1202, SetXmpDataDoesNotCrash_1202) {
    auto image = createBmffImage();
    Exiv2::XmpData xmpData;
    EXPECT_NO_THROW(image->setXmpData(xmpData));
}

// Test that mimeType returns a non-empty string
TEST_F(BmffImageTest_1202, MimeTypeReturnsNonEmpty_1202) {
    auto image = createBmffImage();
    std::string mime = image->mimeType();
    // BMFF images should return some mime type
    EXPECT_FALSE(mime.empty());
}

// Test pixelWidth returns 0 for empty/unread image
TEST_F(BmffImageTest_1202, PixelWidthDefaultsToZero_1202) {
    auto image = createBmffImage();
    EXPECT_EQ(image->pixelWidth(), 0u);
}

// Test pixelHeight returns 0 for empty/unread image
TEST_F(BmffImageTest_1202, PixelHeightDefaultsToZero_1202) {
    auto image = createBmffImage();
    EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test readMetadata on empty data throws or handles error
TEST_F(BmffImageTest_1202, ReadMetadataOnEmptyDataThrows_1202) {
    auto image = createBmffImage("");
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test readMetadata on garbage data throws
TEST_F(BmffImageTest_1202, ReadMetadataOnGarbageDataThrows_1202) {
    std::string garbage(100, '\xFF');
    auto image = createBmffImage(garbage);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test printStructure on empty data with kpsNone
TEST_F(BmffImageTest_1202, PrintStructureOnEmptyData_1202) {
    auto image = createBmffImage("");
    std::ostringstream oss;
    // Should throw or handle gracefully on empty data
    EXPECT_THROW(image->printStructure(oss, Exiv2::kpsNone, 0), Exiv2::Error);
}

// Test that constructing BmffImage with nullptr io fails or handles properly
TEST_F(BmffImageTest_1202, ConstructWithValidIo_1202) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW({
        Exiv2::BmffImage img(std::move(io), false, 1000);
    });
}

// Test writeMetadata always throws regardless of state
TEST_F(BmffImageTest_1202, WriteMetadataAlwaysThrows_1202) {
    // Even with some data, writeMetadata should throw
    std::string data = createMinimalFtypBox();
    auto image = createBmffImage(data);
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test that multiple calls to writeMetadata consistently throw
TEST_F(BmffImageTest_1202, WriteMetadataConsistentlyThrows_1202) {
    auto image = createBmffImage();
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test mimeType with a minimal ftyp box
TEST_F(BmffImageTest_1202, MimeTypeWithMinimalData_1202) {
    std::string data = createMinimalFtypBox();
    auto image = createBmffImage(data);
    // Without reading metadata, the mime type should still return default
    std::string mime = image->mimeType();
    EXPECT_FALSE(mime.empty());
}

// Test construction with different max_box_depth values
TEST_F(BmffImageTest_1202, ConstructWithZeroMaxBoxDepth_1202) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW({
        Exiv2::BmffImage img(std::move(io), false, 0);
    });
}

TEST_F(BmffImageTest_1202, ConstructWithLargeMaxBoxDepth_1202) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW({
        Exiv2::BmffImage img(std::move(io), false, 100000);
    });
}

// Test that the error message from writeMetadata contains "BMFF"
TEST_F(BmffImageTest_1202, WriteMetadataErrorMessageContainsBMFF_1202) {
    auto image = createBmffImage();
    try {
        image->writeMetadata();
        FAIL() << "Expected Exiv2::Error";
    } catch (const Exiv2::Error& e) {
        std::string what = e.what();
        EXPECT_THAT(what, ::testing::HasSubstr("BMFF"));
    }
}

}  // namespace
