#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/rafimage.hpp>
#include <exiv2/error.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

#include <memory>
#include <sstream>
#include <cstring>

namespace {

// Minimal valid RAF file header for testing
// RAF files start with "FUJIFILMCCD-RAW " (16 bytes)
std::vector<unsigned char> createMinimalRafHeader() {
    std::vector<unsigned char> data(256, 0);
    const char* magic = "FUJIFILMCCD-RAW ";
    std::memcpy(data.data(), magic, 16);
    return data;
}

class RafImageTest_222 : public ::testing::Test {
protected:
    std::unique_ptr<Exiv2::RafImage> createRafImageFromMemory(const std::vector<unsigned char>& data) {
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        return std::make_unique<Exiv2::RafImage>(std::move(io), false);
    }

    std::unique_ptr<Exiv2::RafImage> createEmptyRafImage() {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<Exiv2::RafImage>(std::move(io), false);
    }
};

// Test that writeMetadata throws an exception indicating writing is unsupported
TEST_F(RafImageTest_222, WriteMetadataThrowsUnsupported_222) {
    auto data = createMinimalRafHeader();
    auto img = createRafImageFromMemory(data);

    try {
        img->writeMetadata();
        FAIL() << "Expected Exiv2::Error to be thrown";
    } catch (const Exiv2::Error& e) {
        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerWritingImageFormatUnsupported);
    } catch (...) {
        FAIL() << "Expected Exiv2::Error but got different exception";
    }
}

// Test that mimeType returns the correct MIME type for RAF images
TEST_F(RafImageTest_222, MimeTypeIsCorrect_222) {
    auto data = createMinimalRafHeader();
    auto img = createRafImageFromMemory(data);

    EXPECT_EQ(img->mimeType(), "image/x-fuji-raf");
}

// Test that setExifData throws (writing not supported for RAF)
TEST_F(RafImageTest_222, SetExifDataThrows_222) {
    auto data = createMinimalRafHeader();
    auto img = createRafImageFromMemory(data);

    Exiv2::ExifData exifData;
    EXPECT_THROW(img->setExifData(exifData), Exiv2::Error);
}

// Test that setIptcData throws (writing not supported for RAF)
TEST_F(RafImageTest_222, SetIptcDataThrows_222) {
    auto data = createMinimalRafHeader();
    auto img = createRafImageFromMemory(data);

    Exiv2::IptcData iptcData;
    EXPECT_THROW(img->setIptcData(iptcData), Exiv2::Error);
}

// Test that setComment throws (writing not supported for RAF)
TEST_F(RafImageTest_222, SetCommentThrows_222) {
    auto data = createMinimalRafHeader();
    auto img = createRafImageFromMemory(data);

    EXPECT_THROW(img->setComment("test comment"), Exiv2::Error);
}

// Test readMetadata on empty/invalid data
TEST_F(RafImageTest_222, ReadMetadataOnEmptyDataThrows_222) {
    auto img = createEmptyRafImage();

    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test readMetadata on data too small to be a valid RAF
TEST_F(RafImageTest_222, ReadMetadataOnTooSmallDataThrows_222) {
    std::vector<unsigned char> smallData(10, 0);
    auto img = createRafImageFromMemory(smallData);

    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test readMetadata on invalid RAF data (wrong magic)
TEST_F(RafImageTest_222, ReadMetadataOnInvalidMagicThrows_222) {
    std::vector<unsigned char> data(256, 0);
    const char* wrongMagic = "NOTARAFFILE_____";
    std::memcpy(data.data(), wrongMagic, 16);

    auto img = createRafImageFromMemory(data);
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test that pixelWidth returns 0 before metadata is read
TEST_F(RafImageTest_222, PixelWidthDefaultsToZero_222) {
    auto data = createMinimalRafHeader();
    auto img = createRafImageFromMemory(data);

    EXPECT_EQ(img->pixelWidth(), 0u);
}

// Test that pixelHeight returns 0 before metadata is read
TEST_F(RafImageTest_222, PixelHeightDefaultsToZero_222) {
    auto data = createMinimalRafHeader();
    auto img = createRafImageFromMemory(data);

    EXPECT_EQ(img->pixelHeight(), 0u);
}

// Test printStructure with kpsNone doesn't crash on minimal data
TEST_F(RafImageTest_222, PrintStructureKpsNoneDoesNotCrash_222) {
    auto data = createMinimalRafHeader();
    auto img = createRafImageFromMemory(data);

    std::ostringstream oss;
    // kpsNone typically does nothing, should not throw
    EXPECT_NO_THROW(img->printStructure(oss, Exiv2::kpsNone, 0));
}

// Test that construction with create=true works
TEST_F(RafImageTest_222, ConstructWithCreateTrue_222) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW(Exiv2::RafImage(std::move(io), true));
}

// Test that construction with create=false works
TEST_F(RafImageTest_222, ConstructWithCreateFalse_222) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW(Exiv2::RafImage(std::move(io), false));
}

// Test writeMetadata exception contains RAF reference
TEST_F(RafImageTest_222, WriteMetadataErrorContainsRAF_222) {
    auto data = createMinimalRafHeader();
    auto img = createRafImageFromMemory(data);

    try {
        img->writeMetadata();
        FAIL() << "Expected exception";
    } catch (const Exiv2::Error& e) {
        std::string what = e.what();
        EXPECT_TRUE(what.find("RAF") != std::string::npos)
            << "Error message should mention RAF, got: " << what;
    }
}

// Test that after failed readMetadata, exif data is empty
TEST_F(RafImageTest_222, ExifDataEmptyAfterFailedRead_222) {
    auto data = createMinimalRafHeader();
    auto img = createRafImageFromMemory(data);

    // readMetadata may throw on minimal/invalid data
    try {
        img->readMetadata();
    } catch (...) {
        // Expected
    }

    EXPECT_TRUE(img->exifData().empty());
}

// Test that after failed readMetadata, IPTC data is empty
TEST_F(RafImageTest_222, IptcDataEmptyAfterFailedRead_222) {
    auto data = createMinimalRafHeader();
    auto img = createRafImageFromMemory(data);

    try {
        img->readMetadata();
    } catch (...) {
        // Expected
    }

    EXPECT_TRUE(img->iptcData().empty());
}

}  // namespace
