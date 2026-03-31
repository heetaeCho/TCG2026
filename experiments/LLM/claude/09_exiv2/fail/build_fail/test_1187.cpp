#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/psdimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>

#include <fstream>
#include <cstring>
#include <memory>

namespace {

// Minimal valid PSD file header for testing
// PSD signature: "8BPS", version: 1, 6 reserved bytes, channels: 3,
// height: 1, width: 1, depth: 8, color mode: 3 (RGB)
// Then color mode data length: 0, image resources length: 0,
// layer and mask info length: 0, image data section: compression type 0 + pixel data
std::vector<uint8_t> createMinimalPsdFile() {
    std::vector<uint8_t> psd;

    // Signature: "8BPS"
    psd.push_back('8');
    psd.push_back('B');
    psd.push_back('P');
    psd.push_back('S');

    // Version: 1 (big-endian uint16)
    psd.push_back(0x00);
    psd.push_back(0x01);

    // Reserved: 6 bytes of zeros
    for (int i = 0; i < 6; i++)
        psd.push_back(0x00);

    // Channels: 3 (big-endian uint16)
    psd.push_back(0x00);
    psd.push_back(0x03);

    // Height: 1 (big-endian uint32)
    psd.push_back(0x00);
    psd.push_back(0x00);
    psd.push_back(0x00);
    psd.push_back(0x01);

    // Width: 1 (big-endian uint32)
    psd.push_back(0x00);
    psd.push_back(0x00);
    psd.push_back(0x00);
    psd.push_back(0x01);

    // Depth: 8 (big-endian uint16)
    psd.push_back(0x00);
    psd.push_back(0x08);

    // Color Mode: 3 = RGB (big-endian uint16)
    psd.push_back(0x00);
    psd.push_back(0x03);

    // Color Mode Data Length: 0 (big-endian uint32)
    psd.push_back(0x00);
    psd.push_back(0x00);
    psd.push_back(0x00);
    psd.push_back(0x00);

    // Image Resources Length: 0 (big-endian uint32)
    psd.push_back(0x00);
    psd.push_back(0x00);
    psd.push_back(0x00);
    psd.push_back(0x00);

    // Layer and Mask Information Length: 0 (big-endian uint32)
    psd.push_back(0x00);
    psd.push_back(0x00);
    psd.push_back(0x00);
    psd.push_back(0x00);

    // Image Data Section: compression type 0 (raw) (big-endian uint16)
    psd.push_back(0x00);
    psd.push_back(0x00);

    // Pixel data: 3 channels * 1 pixel = 3 bytes
    psd.push_back(0xFF);
    psd.push_back(0x00);
    psd.push_back(0x00);

    return psd;
}

class PsdImageTest_1187 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<Exiv2::PsdImage> createPsdImageFromData(const std::vector<uint8_t>& data) {
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        return std::make_unique<Exiv2::PsdImage>(std::move(io));
    }

    std::unique_ptr<Exiv2::PsdImage> createPsdImageFromEmptyMemIo() {
        auto io = std::make_unique<Exiv2::MemIo>();
        return std::make_unique<Exiv2::PsdImage>(std::move(io));
    }
};

// Test that PsdImage can be constructed with a MemIo
TEST_F(PsdImageTest_1187, ConstructionWithMemIo_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    ASSERT_NE(image, nullptr);
}

// Test that mimeType returns the correct PSD MIME type
TEST_F(PsdImageTest_1187, MimeTypeReturnsPsdMime_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    EXPECT_EQ(image->mimeType(), "image/vnd.adobe.photoshop");
}

// Test that setComment throws (PSD does not support comments)
TEST_F(PsdImageTest_1187, SetCommentThrows_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    EXPECT_THROW(image->setComment("test comment"), Exiv2::Error);
}

// Test readMetadata on empty data throws
TEST_F(PsdImageTest_1187, ReadMetadataEmptyDataThrows_1187) {
    auto image = createPsdImageFromEmptyMemIo();
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test readMetadata on invalid (too small) data throws
TEST_F(PsdImageTest_1187, ReadMetadataInvalidDataThrows_1187) {
    std::vector<uint8_t> tinyData = {0x00, 0x01, 0x02};
    auto image = createPsdImageFromData(tinyData);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test readMetadata on data with wrong signature throws
TEST_F(PsdImageTest_1187, ReadMetadataWrongSignatureThrows_1187) {
    auto data = createMinimalPsdFile();
    // Corrupt the signature
    data[0] = 'X';
    data[1] = 'X';
    data[2] = 'X';
    data[3] = 'X';
    auto image = createPsdImageFromData(data);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test readMetadata on a valid minimal PSD succeeds
TEST_F(PsdImageTest_1187, ReadMetadataValidPsd_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    EXPECT_NO_THROW(image->readMetadata());
}

// Test that after reading metadata, pixel dimensions are set
TEST_F(PsdImageTest_1187, ReadMetadataPixelDimensions_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    image->readMetadata();
    EXPECT_EQ(image->pixelWidth(), 1u);
    EXPECT_EQ(image->pixelHeight(), 1u);
}

// Test writeMetadata on a valid minimal PSD doesn't throw
TEST_F(PsdImageTest_1187, WriteMetadataValidPsd_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    image->readMetadata();
    EXPECT_NO_THROW(image->writeMetadata());
}

// Test writeMetadata on empty data throws
TEST_F(PsdImageTest_1187, WriteMetadataEmptyDataThrows_1187) {
    auto image = createPsdImageFromEmptyMemIo();
    EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test that exifData() returns a reference that can be accessed
TEST_F(PsdImageTest_1187, ExifDataAccessible_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    image->readMetadata();
    Exiv2::ExifData& exif = image->exifData();
    // Minimal PSD has no EXIF, so it should be empty
    EXPECT_TRUE(exif.empty());
}

// Test that iptcData() returns a reference that can be accessed
TEST_F(PsdImageTest_1187, IptcDataAccessible_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    image->readMetadata();
    Exiv2::IptcData& iptc = image->iptcData();
    EXPECT_TRUE(iptc.empty());
}

// Test that xmpData() returns a reference that can be accessed
TEST_F(PsdImageTest_1187, XmpDataAccessible_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    image->readMetadata();
    Exiv2::XmpData& xmp = image->xmpData();
    EXPECT_TRUE(xmp.empty());
}

// Test that good() returns true for a valid PSD
TEST_F(PsdImageTest_1187, GoodReturnsTrueForValidPsd_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    EXPECT_TRUE(image->good());
}

// Test that imageType returns psd
TEST_F(PsdImageTest_1187, ImageTypeIsPsd_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    EXPECT_EQ(image->imageType(), Exiv2::ImageType::psd);
}

// Test read then write then read round-trip
TEST_F(PsdImageTest_1187, ReadWriteReadRoundTrip_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    image->readMetadata();

    // Write metadata back
    EXPECT_NO_THROW(image->writeMetadata());

    // Read again
    EXPECT_NO_THROW(image->readMetadata());

    // Verify dimensions are still correct
    EXPECT_EQ(image->pixelWidth(), 1u);
    EXPECT_EQ(image->pixelHeight(), 1u);
}

// Test writeMetadata after modifying IPTC data
TEST_F(PsdImageTest_1187, WriteMetadataWithIptcData_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    image->readMetadata();

    // Add some IPTC data
    Exiv2::IptcData& iptc = image->iptcData();
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test Caption");
    iptc.add(key, value.get());

    EXPECT_NO_THROW(image->writeMetadata());

    // Read again and verify
    image->readMetadata();
    EXPECT_FALSE(image->iptcData().empty());
}

// Test writeMetadata after clearing all metadata
TEST_F(PsdImageTest_1187, WriteMetadataAfterClearMetadata_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    image->readMetadata();
    image->clearMetadata();
    EXPECT_NO_THROW(image->writeMetadata());
}

// Test that readMetadata with wrong version throws
TEST_F(PsdImageTest_1187, ReadMetadataWrongVersionThrows_1187) {
    auto data = createMinimalPsdFile();
    // Version field is at offset 4-5, set to 99
    data[4] = 0x00;
    data[5] = 0x63; // version 99
    auto image = createPsdImageFromData(data);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test clearExifData and writeMetadata
TEST_F(PsdImageTest_1187, ClearExifDataAndWrite_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    image->readMetadata();
    image->clearExifData();
    EXPECT_TRUE(image->exifData().empty());
    EXPECT_NO_THROW(image->writeMetadata());
}

// Test clearIptcData and writeMetadata
TEST_F(PsdImageTest_1187, ClearIptcDataAndWrite_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    image->readMetadata();
    image->clearIptcData();
    EXPECT_TRUE(image->iptcData().empty());
    EXPECT_NO_THROW(image->writeMetadata());
}

// Test clearXmpData and writeMetadata
TEST_F(PsdImageTest_1187, ClearXmpDataAndWrite_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    image->readMetadata();
    image->clearXmpData();
    EXPECT_TRUE(image->xmpData().empty());
    EXPECT_NO_THROW(image->writeMetadata());
}

// Test that io() returns a valid reference
TEST_F(PsdImageTest_1187, IoReturnsValidReference_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    const Exiv2::BasicIo& io = image->io();
    EXPECT_GE(io.size(), 0u);
}

// Test readMetadata with truncated file (valid header but truncated body)
TEST_F(PsdImageTest_1187, ReadMetadataTruncatedFile_1187) {
    auto data = createMinimalPsdFile();
    // Truncate after header but before image resources length
    std::vector<uint8_t> truncated(data.begin(), data.begin() + 26); // header only
    // Need to ensure it's a valid signature+version but truncated afterwards
    auto image = createPsdImageFromData(truncated);
    EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that the image supports EXIF metadata
TEST_F(PsdImageTest_1187, SupportsExifMetadata_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    EXPECT_TRUE(image->supportsMetadata(Exiv2::MetadataId::mdExif));
}

// Test that the image supports IPTC metadata
TEST_F(PsdImageTest_1187, SupportsIptcMetadata_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    EXPECT_TRUE(image->supportsMetadata(Exiv2::MetadataId::mdIptc));
}

// Test that the image supports XMP metadata
TEST_F(PsdImageTest_1187, SupportsXmpMetadata_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    EXPECT_TRUE(image->supportsMetadata(Exiv2::MetadataId::mdXmp));
}

// Test multiple writeMetadata calls don't corrupt the file
TEST_F(PsdImageTest_1187, MultipleWriteMetadataCalls_1187) {
    auto data = createMinimalPsdFile();
    auto image = createPsdImageFromData(data);
    image->readMetadata();

    EXPECT_NO_THROW(image->writeMetadata());
    EXPECT_NO_THROW(image->writeMetadata());
    EXPECT_NO_THROW(image->writeMetadata());

    // Verify can still read
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelWidth(), 1u);
    EXPECT_EQ(image->pixelHeight(), 1u);
}

} // namespace
