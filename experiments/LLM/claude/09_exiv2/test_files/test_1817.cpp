#include <gtest/gtest.h>
#include <exiv2/crwimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <memory>
#include <vector>
#include <cstring>

using namespace Exiv2;

// Helper to create a CrwImage with a MemIo
static std::unique_ptr<CrwImage> createCrwImage(bool create = true) {
    auto io = std::make_unique<MemIo>();
    return std::make_unique<CrwImage>(std::move(io), create);
}

// ============================================================
// Tests for CrwImage
// ============================================================

class CrwImageTest_1817 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createCrwImage(true);
    }
    std::unique_ptr<CrwImage> image_;
};

TEST_F(CrwImageTest_1817, MimeType_1817) {
    EXPECT_EQ(image_->mimeType(), "image/x-canon-crw");
}

TEST_F(CrwImageTest_1817, PixelWidthDefault_1817) {
    // Without reading metadata, pixel width should be 0
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(CrwImageTest_1817, PixelHeightDefault_1817) {
    // Without reading metadata, pixel height should be 0
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

TEST_F(CrwImageTest_1817, SetIptcDataDoesNotThrow_1817) {
    IptcData iptcData;
    // CRW doesn't support IPTC; setIptcData should be a no-op or ignore
    EXPECT_NO_THROW(image_->setIptcData(iptcData));
}

TEST_F(CrwImageTest_1817, ReadMetadataOnEmptyIo_1817) {
    // Reading metadata from an empty IO should throw
    EXPECT_THROW(image_->readMetadata(), Error);
}

TEST_F(CrwImageTest_1817, WriteMetadataOnEmptyIo_1817) {
    // Writing metadata when no data has been read should throw or handle gracefully
    EXPECT_THROW(image_->writeMetadata(), Error);
}

// ============================================================
// Tests for CrwParser::encode
// ============================================================

class CrwParserTest_1817 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createCrwImage(true);
    }
    std::unique_ptr<CrwImage> image_;
};

TEST_F(CrwParserTest_1817, EncodeWithZeroSizeProducesOutput_1817) {
    // When size is 0, a fresh CiffHeader should be created and written
    Blob blob;
    CrwParser::encode(blob, nullptr, 0, image_.get());
    // The blob should contain at least some header data
    EXPECT_FALSE(blob.empty());
}

TEST_F(CrwParserTest_1817, EncodeWithNullDataAndZeroSize_1817) {
    Blob blob;
    EXPECT_NO_THROW(CrwParser::encode(blob, nullptr, 0, image_.get()));
    // Should produce valid output (at minimum the CIFF header signature)
    EXPECT_GT(blob.size(), 0u);
}

TEST_F(CrwParserTest_1817, EncodeWithInvalidDataThrows_1817) {
    // Passing garbage data with non-zero size should cause header.read to fail
    Blob blob;
    std::vector<byte> garbage(100, 0xFF);
    EXPECT_THROW(CrwParser::encode(blob, garbage.data(), garbage.size(), image_.get()), Error);
}

TEST_F(CrwParserTest_1817, EncodeWithTooSmallDataThrows_1817) {
    // Very small data that can't form a valid CRW header
    Blob blob;
    std::vector<byte> tinyData(2, 0x00);
    EXPECT_THROW(CrwParser::encode(blob, tinyData.data(), tinyData.size(), image_.get()), Error);
}

TEST_F(CrwParserTest_1817, EncodeWithSingleByteDataThrows_1817) {
    Blob blob;
    byte singleByte = 0x42;
    EXPECT_THROW(CrwParser::encode(blob, &singleByte, 1, image_.get()), Error);
}

// ============================================================
// Tests for CrwParser::decode
// ============================================================

class CrwParserDecodeTest_1817 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createCrwImage(true);
    }
    std::unique_ptr<CrwImage> image_;
};

TEST_F(CrwParserDecodeTest_1817, DecodeWithInvalidDataThrows_1817) {
    std::vector<byte> garbage(100, 0xAB);
    EXPECT_THROW(CrwParser::decode(image_.get(), garbage.data(), garbage.size()), Error);
}

TEST_F(CrwParserDecodeTest_1817, DecodeWithZeroSizeThrows_1817) {
    // Decoding with no data should throw
    EXPECT_THROW(CrwParser::decode(image_.get(), nullptr, 0), Error);
}

TEST_F(CrwParserDecodeTest_1817, DecodeWithTooSmallDataThrows_1817) {
    std::vector<byte> smallData(4, 0x00);
    EXPECT_THROW(CrwParser::decode(image_.get(), smallData.data(), smallData.size()), Error);
}

// ============================================================
// Round-trip test: encode from empty, then verify output is re-parseable
// ============================================================

TEST_F(CrwParserTest_1817, RoundTripEncodeFromEmpty_1817) {
    // Encode from empty (size=0) to produce a valid CRW blob
    Blob blob;
    CrwParser::encode(blob, nullptr, 0, image_.get());
    ASSERT_FALSE(blob.empty());

    // The produced blob should be decodable without throwing
    auto image2 = createCrwImage(true);
    EXPECT_NO_THROW(CrwParser::decode(image2.get(), blob.data(), blob.size()));
}

TEST_F(CrwParserTest_1817, RoundTripEncodeReEncode_1817) {
    // First encode from empty
    Blob blob1;
    CrwParser::encode(blob1, nullptr, 0, image_.get());
    ASSERT_FALSE(blob1.empty());

    // Re-encode from the generated blob
    Blob blob2;
    auto image2 = createCrwImage(true);
    EXPECT_NO_THROW(CrwParser::encode(blob2, blob1.data(), blob1.size(), image2.get()));
    EXPECT_FALSE(blob2.empty());
}

// ============================================================
// Test CrwImage creation with different IO types
// ============================================================

TEST(CrwImageCreation_1817, CreateWithMemIo_1817) {
    auto io = std::make_unique<MemIo>();
    EXPECT_NO_THROW(CrwImage(std::move(io), true));
}

TEST(CrwImageCreation_1817, CreateWithMemIoFalse_1817) {
    auto io = std::make_unique<MemIo>();
    EXPECT_NO_THROW(CrwImage(std::move(io), false));
}

TEST(CrwImageCreation_1817, MimeTypeConsistency_1817) {
    auto io1 = std::make_unique<MemIo>();
    CrwImage img1(std::move(io1), true);

    auto io2 = std::make_unique<MemIo>();
    CrwImage img2(std::move(io2), false);

    EXPECT_EQ(img1.mimeType(), img2.mimeType());
}

// ============================================================
// Boundary: encode with various sized invalid data
// ============================================================

TEST_F(CrwParserTest_1817, EncodeWithHeaderSizedGarbageThrows_1817) {
    // CRW header is at least 14 bytes (signature + offset), garbage should still fail
    Blob blob;
    std::vector<byte> data(14, 0x00);
    EXPECT_THROW(CrwParser::encode(blob, data.data(), data.size(), image_.get()), Error);
}

TEST_F(CrwParserTest_1817, EncodeWithLargeGarbageThrows_1817) {
    Blob blob;
    std::vector<byte> data(10000, 0xCD);
    EXPECT_THROW(CrwParser::encode(blob, data.data(), data.size(), image_.get()), Error);
}

// ============================================================
// Verify blob content from empty encode has HEAPCCDR signature
// ============================================================

TEST_F(CrwParserTest_1817, EncodeFromEmptyContainsSignature_1817) {
    Blob blob;
    CrwParser::encode(blob, nullptr, 0, image_.get());
    ASSERT_GE(blob.size(), 14u);

    // CIFF files start with byte order mark and then "HEAPCCDR" at offset 6
    // Check that the blob has meaningful content
    // The first two bytes should be II (little endian) = 0x49 0x49 or MM
    bool isLittleEndian = (blob[0] == 'I' && blob[1] == 'I');
    bool isBigEndian = (blob[0] == 'M' && blob[1] == 'M');
    EXPECT_TRUE(isLittleEndian || isBigEndian);

    // Check for HEAPCCDR signature at offset 6
    std::string sig(blob.begin() + 6, blob.begin() + 14);
    EXPECT_EQ(sig, "HEAPCCDR");
}
