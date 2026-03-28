#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/crwimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>

#include <fstream>
#include <vector>
#include <cstring>

namespace {

// Helper to create a CrwImage with a MemIo
std::unique_ptr<Exiv2::CrwImage> createCrwImage(bool create = false) {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::CrwImage>(std::move(io), create);
}

} // anonymous namespace

class CrwImageTest_1816 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that CrwImage returns the correct MIME type
TEST_F(CrwImageTest_1816, MimeType_1816) {
    auto crwImage = createCrwImage();
    EXPECT_EQ(crwImage->mimeType(), "image/x-canon-crw");
}

// Test that pixelWidth returns 0 initially
TEST_F(CrwImageTest_1816, PixelWidthInitiallyZero_1816) {
    auto crwImage = createCrwImage();
    EXPECT_EQ(crwImage->pixelWidth(), 0u);
}

// Test that pixelHeight returns 0 initially
TEST_F(CrwImageTest_1816, PixelHeightInitiallyZero_1816) {
    auto crwImage = createCrwImage();
    EXPECT_EQ(crwImage->pixelHeight(), 0u);
}

// Test that exifData is initially empty
TEST_F(CrwImageTest_1816, ExifDataInitiallyEmpty_1816) {
    auto crwImage = createCrwImage();
    EXPECT_TRUE(crwImage->exifData().empty());
}

// Test that setIptcData does nothing (IPTC not supported for CRW)
TEST_F(CrwImageTest_1816, SetIptcDataIsNoOp_1816) {
    auto crwImage = createCrwImage();
    Exiv2::IptcData iptcData;
    // Should not throw, but should be a no-op
    EXPECT_NO_THROW(crwImage->setIptcData(iptcData));
}

// Test that reading metadata from empty io throws
TEST_F(CrwImageTest_1816, ReadMetadataFromEmptyIoThrows_1816) {
    auto crwImage = createCrwImage();
    EXPECT_THROW(crwImage->readMetadata(), Exiv2::Error);
}

// Test that writing metadata to empty io throws or handles gracefully
TEST_F(CrwImageTest_1816, WriteMetadataEmptyThrows_1816) {
    auto crwImage = createCrwImage();
    EXPECT_THROW(crwImage->writeMetadata(), Exiv2::Error);
}

// Test good() on a newly created CrwImage with empty MemIo
TEST_F(CrwImageTest_1816, GoodOnEmptyIo_1816) {
    auto crwImage = createCrwImage();
    // MemIo with no data - good() behavior depends on io state
    // Just verify it doesn't crash
    bool result = crwImage->good();
    (void)result; // We just check it doesn't crash
}

// Test CrwParser::decode with null pointer
TEST_F(CrwImageTest_1816, DecodeWithNullDataThrows_1816) {
    auto crwImage = createCrwImage();
    EXPECT_THROW(Exiv2::CrwParser::decode(crwImage.get(), nullptr, 0), Exiv2::Error);
}

// Test CrwParser::decode with empty data
TEST_F(CrwImageTest_1816, DecodeWithEmptyDataThrows_1816) {
    auto crwImage = createCrwImage();
    Exiv2::byte data[1] = {0};
    EXPECT_THROW(Exiv2::CrwParser::decode(crwImage.get(), data, 0), Exiv2::Error);
}

// Test CrwParser::decode with too small data (not a valid CIFF header)
TEST_F(CrwImageTest_1816, DecodeWithTooSmallDataThrows_1816) {
    auto crwImage = createCrwImage();
    std::vector<Exiv2::byte> smallData(10, 0);
    EXPECT_THROW(Exiv2::CrwParser::decode(crwImage.get(), smallData.data(), smallData.size()), Exiv2::Error);
}

// Test CrwParser::decode with garbage data that doesn't match CRW signature
TEST_F(CrwImageTest_1816, DecodeWithGarbageDataThrows_1816) {
    auto crwImage = createCrwImage();
    std::vector<Exiv2::byte> garbageData(1024, 0xFF);
    EXPECT_THROW(Exiv2::CrwParser::decode(crwImage.get(), garbageData.data(), garbageData.size()), Exiv2::Error);
}

// Test that clearExifData works on CrwImage
TEST_F(CrwImageTest_1816, ClearExifData_1816) {
    auto crwImage = createCrwImage();
    crwImage->exifData()["Exif.Image.Make"] = "Canon";
    EXPECT_FALSE(crwImage->exifData().empty());
    crwImage->clearExifData();
    EXPECT_TRUE(crwImage->exifData().empty());
}

// Test that clearMetadata works
TEST_F(CrwImageTest_1816, ClearMetadata_1816) {
    auto crwImage = createCrwImage();
    crwImage->exifData()["Exif.Image.Make"] = "Canon";
    crwImage->clearMetadata();
    EXPECT_TRUE(crwImage->exifData().empty());
}

// Test that comment is initially empty
TEST_F(CrwImageTest_1816, CommentInitiallyEmpty_1816) {
    auto crwImage = createCrwImage();
    EXPECT_TRUE(crwImage->comment().empty());
}

// Test setComment and clearComment
TEST_F(CrwImageTest_1816, SetAndClearComment_1816) {
    auto crwImage = createCrwImage();
    crwImage->setComment("Test comment");
    EXPECT_EQ(crwImage->comment(), "Test comment");
    crwImage->clearComment();
    EXPECT_TRUE(crwImage->comment().empty());
}

// Test CrwParser::encode with empty blob and null data
TEST_F(CrwImageTest_1816, EncodeWithNullDataThrows_1816) {
    auto crwImage = createCrwImage();
    Exiv2::Blob blob;
    EXPECT_THROW(Exiv2::CrwParser::encode(blob, nullptr, 0, crwImage.get()), Exiv2::Error);
}

// Test CrwParser::encode with garbage data
TEST_F(CrwImageTest_1816, EncodeWithGarbageDataThrows_1816) {
    auto crwImage = createCrwImage();
    Exiv2::Blob blob;
    std::vector<Exiv2::byte> garbageData(1024, 0xAB);
    EXPECT_THROW(Exiv2::CrwParser::encode(blob, garbageData.data(), garbageData.size(), crwImage.get()), Exiv2::Error);
}

// Test that setExifData works on CrwImage
TEST_F(CrwImageTest_1816, SetExifData_1816) {
    auto crwImage = createCrwImage();
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    crwImage->setExifData(exifData);
    EXPECT_FALSE(crwImage->exifData().empty());
    auto it = crwImage->exifData().findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_NE(it, crwImage->exifData().end());
    EXPECT_EQ(it->toString(), "Canon");
}

// Test that exifData operator[] creates entries
TEST_F(CrwImageTest_1816, ExifDataOperatorBracketCreatesEntry_1816) {
    auto crwImage = createCrwImage();
    crwImage->exifData()["Exif.Image2.JPEGInterchangeFormat"] = static_cast<uint32_t>(100);
    crwImage->exifData()["Exif.Image2.JPEGInterchangeFormatLength"] = static_cast<uint32_t>(200);
    
    EXPECT_EQ(crwImage->exifData().count(), 2u);
    
    auto it1 = crwImage->exifData().findKey(Exiv2::ExifKey("Exif.Image2.JPEGInterchangeFormat"));
    EXPECT_NE(it1, crwImage->exifData().end());
    EXPECT_EQ(it1->toInt64(), 100);
    
    auto it2 = crwImage->exifData().findKey(Exiv2::ExifKey("Exif.Image2.JPEGInterchangeFormatLength"));
    EXPECT_NE(it2, crwImage->exifData().end());
    EXPECT_EQ(it2->toInt64(), 200);
}

// Test CrwParser::decode with data that has invalid CIFF signature but correct size
TEST_F(CrwImageTest_1816, DecodeWithInvalidSignatureThrows_1816) {
    auto crwImage = createCrwImage();
    // Create data that is large enough but has wrong signature
    std::vector<Exiv2::byte> data(2048, 0);
    // Fill with something that might look like a header but isn't valid CIFF
    data[0] = 'I'; data[1] = 'I'; // little endian byte order
    // But wrong signature
    EXPECT_THROW(Exiv2::CrwParser::decode(crwImage.get(), data.data(), data.size()), Exiv2::Error);
}

// Test that CrwImage supports exif metadata
TEST_F(CrwImageTest_1816, SupportsExifMetadata_1816) {
    auto crwImage = createCrwImage();
    EXPECT_TRUE(crwImage->supportsMetadata(Exiv2::MetadataId::mdExif));
}

// Test that CrwImage supports comment metadata
TEST_F(CrwImageTest_1816, SupportsCommentMetadata_1816) {
    auto crwImage = createCrwImage();
    EXPECT_TRUE(crwImage->supportsMetadata(Exiv2::MetadataId::mdComment));
}

// Test that io() returns a reference
TEST_F(CrwImageTest_1816, IoReturnsReference_1816) {
    auto crwImage = createCrwImage();
    EXPECT_NO_THROW(crwImage->io());
}
