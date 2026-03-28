#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/jp2image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>

#include <fstream>
#include <cstring>
#include <memory>

namespace {

// Minimal valid JP2 file header bytes
// JP2 signature box + file type box (minimal)
static const uint8_t kMinimalJp2Header[] = {
    // JP2 Signature box (12 bytes)
    0x00, 0x00, 0x00, 0x0C, // Box length = 12
    0x6A, 0x50, 0x20, 0x20, // Box type = 'jP  '
    0x0D, 0x0A, 0x87, 0x0A, // Signature

    // File Type box
    0x00, 0x00, 0x00, 0x14, // Box length = 20
    0x66, 0x74, 0x79, 0x70, // Box type = 'ftyp'
    0x6A, 0x70, 0x32, 0x20, // Brand = 'jp2 '
    0x00, 0x00, 0x00, 0x00, // Minor version
    0x6A, 0x70, 0x32, 0x20, // Compatibility = 'jp2 '
};

class Jp2ImageTest_87 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<Exiv2::Jp2Image> createJp2ImageFromMemory(const uint8_t* data, size_t size) {
        auto io = std::make_unique<Exiv2::MemIo>(data, size);
        return std::make_unique<Exiv2::Jp2Image>(std::move(io), false);
    }

    std::unique_ptr<Exiv2::Jp2Image> createEmptyJp2Image() {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<Exiv2::Jp2Image>(std::move(io), true);
    }
};

// Test: Construction with empty MemIo and create=true
TEST_F(Jp2ImageTest_87, ConstructWithEmptyIoCreate_87) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW(Exiv2::Jp2Image img(std::move(io), true));
}

// Test: Construction with empty MemIo and create=false
TEST_F(Jp2ImageTest_87, ConstructWithEmptyIoNoCreate_87) {
    auto io = std::make_unique<Exiv2::MemIo>();
    EXPECT_NO_THROW(Exiv2::Jp2Image img(std::move(io), false));
}

// Test: mimeType returns expected JPEG 2000 mime type
TEST_F(Jp2ImageTest_87, MimeType_87) {
    auto img = createEmptyJp2Image();
    std::string mime = img->mimeType();
    // JP2 images should return "image/jp2"
    EXPECT_FALSE(mime.empty());
    EXPECT_EQ(mime, "image/jp2");
}

// Test: setComment should not throw (it's a no-op for JP2)
TEST_F(Jp2ImageTest_87, SetCommentNoOp_87) {
    auto img = createEmptyJp2Image();
    EXPECT_NO_THROW(img->setComment("test comment"));
}

// Test: readMetadata on empty data should throw
TEST_F(Jp2ImageTest_87, ReadMetadataEmptyThrows_87) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto img = std::make_unique<Exiv2::Jp2Image>(std::move(io), false);
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test: readMetadata on garbage data should throw
TEST_F(Jp2ImageTest_87, ReadMetadataGarbageDataThrows_87) {
    uint8_t garbage[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    auto img = createJp2ImageFromMemory(garbage, sizeof(garbage));
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test: readMetadata with minimal JP2 header (incomplete but valid signature)
TEST_F(Jp2ImageTest_87, ReadMetadataMinimalHeader_87) {
    auto img = createJp2ImageFromMemory(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    // This may throw because the file is incomplete (no JP2 header box, no codestream)
    // but it should at least recognize the signature
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test: writeMetadata on empty/uninitialized image should throw
TEST_F(Jp2ImageTest_87, WriteMetadataEmptyThrows_87) {
    auto io = std::make_unique<Exiv2::MemIo>();
    auto img = std::make_unique<Exiv2::Jp2Image>(std::move(io), false);
    EXPECT_THROW(img->writeMetadata(), Exiv2::Error);
}

// Test: writeMetadata with only minimal header (no valid JP2 content) should throw
TEST_F(Jp2ImageTest_87, WriteMetadataMinimalHeaderThrows_87) {
    auto img = createJp2ImageFromMemory(kMinimalJp2Header, sizeof(kMinimalJp2Header));
    EXPECT_THROW(img->writeMetadata(), Exiv2::Error);
}

// Test: exifData accessor returns reference
TEST_F(Jp2ImageTest_87, ExifDataAccessor_87) {
    auto img = createEmptyJp2Image();
    Exiv2::ExifData& exif = img->exifData();
    EXPECT_TRUE(exif.empty());
}

// Test: iptcData accessor returns reference
TEST_F(Jp2ImageTest_87, IptcDataAccessor_87) {
    auto img = createEmptyJp2Image();
    Exiv2::IptcData& iptc = img->iptcData();
    EXPECT_TRUE(iptc.empty());
}

// Test: xmpData accessor returns reference
TEST_F(Jp2ImageTest_87, XmpDataAccessor_87) {
    auto img = createEmptyJp2Image();
    Exiv2::XmpData& xmp = img->xmpData();
    EXPECT_TRUE(xmp.empty());
}

// Test: good() on empty MemIo
TEST_F(Jp2ImageTest_87, GoodOnEmptyIo_87) {
    auto img = createEmptyJp2Image();
    // good() checks if the io is in a good state
    // For an empty MemIo, it should still be "good" in principle
    bool result = img->good();
    // We just verify it doesn't crash - the actual value depends on implementation
    (void)result;
}

// Test: io() accessor returns a reference to the underlying BasicIo
TEST_F(Jp2ImageTest_87, IoAccessor_87) {
    auto img = createEmptyJp2Image();
    const Exiv2::BasicIo& io = img->io();
    EXPECT_EQ(io.size(), 0u);
}

// Test: pixelWidth and pixelHeight default to 0
TEST_F(Jp2ImageTest_87, DefaultPixelDimensions_87) {
    auto img = createEmptyJp2Image();
    EXPECT_EQ(img->pixelWidth(), 0u);
    EXPECT_EQ(img->pixelHeight(), 0u);
}

// Test: clearExifData on fresh image
TEST_F(Jp2ImageTest_87, ClearExifData_87) {
    auto img = createEmptyJp2Image();
    EXPECT_NO_THROW(img->clearExifData());
    EXPECT_TRUE(img->exifData().empty());
}

// Test: clearIptcData on fresh image
TEST_F(Jp2ImageTest_87, ClearIptcData_87) {
    auto img = createEmptyJp2Image();
    EXPECT_NO_THROW(img->clearIptcData());
    EXPECT_TRUE(img->iptcData().empty());
}

// Test: clearXmpData on fresh image
TEST_F(Jp2ImageTest_87, ClearXmpData_87) {
    auto img = createEmptyJp2Image();
    EXPECT_NO_THROW(img->clearXmpData());
    EXPECT_TRUE(img->xmpData().empty());
}

// Test: setExifData and verify it's set
TEST_F(Jp2ImageTest_87, SetExifData_87) {
    auto img = createEmptyJp2Image();
    Exiv2::ExifData exifData;
    EXPECT_NO_THROW(img->setExifData(exifData));
}

// Test: setIptcData and verify it's set
TEST_F(Jp2ImageTest_87, SetIptcData_87) {
    auto img = createEmptyJp2Image();
    Exiv2::IptcData iptcData;
    EXPECT_NO_THROW(img->setIptcData(iptcData));
}

// Test: setXmpData and verify it's set
TEST_F(Jp2ImageTest_87, SetXmpData_87) {
    auto img = createEmptyJp2Image();
    Exiv2::XmpData xmpData;
    EXPECT_NO_THROW(img->setXmpData(xmpData));
}

// Test: clearMetadata clears all metadata
TEST_F(Jp2ImageTest_87, ClearMetadata_87) {
    auto img = createEmptyJp2Image();
    EXPECT_NO_THROW(img->clearMetadata());
    EXPECT_TRUE(img->exifData().empty());
    EXPECT_TRUE(img->iptcData().empty());
    EXPECT_TRUE(img->xmpData().empty());
}

// Test: comment returns empty string by default
TEST_F(Jp2ImageTest_87, DefaultCommentEmpty_87) {
    auto img = createEmptyJp2Image();
    EXPECT_TRUE(img->comment().empty());
}

// Test: printStructure with empty data
TEST_F(Jp2ImageTest_87, PrintStructureEmpty_87) {
    auto img = createEmptyJp2Image();
    std::ostringstream oss;
    // Printing structure of empty data - behavior depends on implementation
    // It might throw or produce empty output
    try {
        img->printStructure(oss, Exiv2::kpsNone, 0);
    } catch (const Exiv2::Error&) {
        // Expected for empty/invalid JP2
    }
}

// Test: readMetadata with data that has correct signature but truncated content
TEST_F(Jp2ImageTest_87, ReadMetadataTruncatedAfterSignature_87) {
    // Only the signature box, no ftyp box
    uint8_t truncated[] = {
        0x00, 0x00, 0x00, 0x0C,
        0x6A, 0x50, 0x20, 0x20,
        0x0D, 0x0A, 0x87, 0x0A,
    };
    auto img = createJp2ImageFromMemory(truncated, sizeof(truncated));
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test: Single byte data should fail readMetadata
TEST_F(Jp2ImageTest_87, ReadMetadataSingleByte_87) {
    uint8_t single = 0xFF;
    auto img = createJp2ImageFromMemory(&single, 1);
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test: imageType returns jp2
TEST_F(Jp2ImageTest_87, ImageType_87) {
    auto img = createEmptyJp2Image();
    EXPECT_EQ(img->imageType(), Exiv2::ImageType::jp2);
}

// Test: supportsMetadata for various metadata types
TEST_F(Jp2ImageTest_87, SupportsMetadata_87) {
    auto img = createEmptyJp2Image();
    // JP2 is created with mdExif | mdIptc | mdXmp
    EXPECT_TRUE(img->supportsMetadata(Exiv2::MetadataId::mdExif));
    EXPECT_TRUE(img->supportsMetadata(Exiv2::MetadataId::mdIptc));
    EXPECT_TRUE(img->supportsMetadata(Exiv2::MetadataId::mdXmp));
}

// Test: xmpPacket accessor
TEST_F(Jp2ImageTest_87, XmpPacketAccessor_87) {
    auto img = createEmptyJp2Image();
    std::string& xmpPacket = img->xmpPacket();
    EXPECT_TRUE(xmpPacket.empty());
}

// Test: setXmpPacket
TEST_F(Jp2ImageTest_87, SetXmpPacket_87) {
    auto img = createEmptyJp2Image();
    std::string packet = "<x:xmpmeta></x:xmpmeta>";
    EXPECT_NO_THROW(img->setXmpPacket(packet));
}

// Test: clearXmpPacket
TEST_F(Jp2ImageTest_87, ClearXmpPacket_87) {
    auto img = createEmptyJp2Image();
    img->setXmpPacket("<x:xmpmeta></x:xmpmeta>");
    img->clearXmpPacket();
    EXPECT_TRUE(img->xmpPacket().empty());
}

// Test: iccProfileDefined returns false by default
TEST_F(Jp2ImageTest_87, IccProfileNotDefined_87) {
    auto img = createEmptyJp2Image();
    EXPECT_FALSE(img->iccProfileDefined());
}

// Test: clearIccProfile on fresh image
TEST_F(Jp2ImageTest_87, ClearIccProfile_87) {
    auto img = createEmptyJp2Image();
    EXPECT_NO_THROW(img->clearIccProfile());
    EXPECT_FALSE(img->iccProfileDefined());
}

// Test: clearComment
TEST_F(Jp2ImageTest_87, ClearComment_87) {
    auto img = createEmptyJp2Image();
    EXPECT_NO_THROW(img->clearComment());
    EXPECT_TRUE(img->comment().empty());
}

// Test: writeXmpFromPacket flag
TEST_F(Jp2ImageTest_87, WriteXmpFromPacketFlag_87) {
    auto img = createEmptyJp2Image();
    EXPECT_FALSE(img->writeXmpFromPacket());
    img->writeXmpFromPacket(true);
    EXPECT_TRUE(img->writeXmpFromPacket());
    img->writeXmpFromPacket(false);
    EXPECT_FALSE(img->writeXmpFromPacket());
}

// Test: setByteOrder and byteOrder
TEST_F(Jp2ImageTest_87, ByteOrder_87) {
    auto img = createEmptyJp2Image();
    img->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(img->byteOrder(), Exiv2::bigEndian);
    img->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(img->byteOrder(), Exiv2::littleEndian);
}

// Test: nativePreviews returns empty list by default
TEST_F(Jp2ImageTest_87, NativePreviewsEmpty_87) {
    auto img = createEmptyJp2Image();
    EXPECT_TRUE(img->nativePreviews().empty());
}

}  // namespace
