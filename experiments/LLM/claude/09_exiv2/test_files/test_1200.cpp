#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/bmffimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/error.hpp>

#include <cstring>
#include <fstream>
#include <sstream>

using namespace Exiv2;

// Helper to create a minimal valid HEIF/BMFF file in memory
// A minimal BMFF file has an 'ftyp' box
static std::vector<uint8_t> createMinimalBmffData() {
    // ftyp box: size(4) + type(4) + major_brand(4) + minor_version(4) = 16 bytes minimum
    std::vector<uint8_t> data;
    // Box size = 20 (big-endian)
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x14); // 20
    // Box type = 'ftyp'
    data.push_back('f');
    data.push_back('t');
    data.push_back('y');
    data.push_back('p');
    // Major brand = 'heic'
    data.push_back('h');
    data.push_back('e');
    data.push_back('i');
    data.push_back('c');
    // Minor version = 0
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    // Compatible brand = 'heic'
    data.push_back('h');
    data.push_back('e');
    data.push_back('i');
    data.push_back('c');
    return data;
}

// Helper to write data to a temp file and return path
static std::string writeTempFile(const std::vector<uint8_t>& data, const std::string& suffix = ".heic") {
    std::string path = "/tmp/bmff_test_1200" + suffix;
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    ofs.close();
    return path;
}

class BmffImageTest_1200 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Creating a BmffImage with a valid MemIo
TEST_F(BmffImageTest_1200, ConstructWithMemIo_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    ASSERT_NO_THROW(BmffImage img(std::move(io), false, 1000));
}

// Test: good() returns true for valid io
TEST_F(BmffImageTest_1200, GoodReturnsTrueForValidIo_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    EXPECT_TRUE(img.good());
}

// Test: mimeType returns a non-empty string
TEST_F(BmffImageTest_1200, MimeTypeNotEmpty_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    // Before readMetadata, mimeType should still return something
    std::string mime = img.mimeType();
    EXPECT_FALSE(mime.empty());
}

// Test: readMetadata on a minimal ftyp-only BMFF file doesn't crash
TEST_F(BmffImageTest_1200, ReadMetadataMinimalFtyp_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    ASSERT_NO_THROW(img.readMetadata());
}

// Test: readMetadata on empty data throws
TEST_F(BmffImageTest_1200, ReadMetadataEmptyDataThrows_1200) {
    auto io = std::make_unique<MemIo>();
    BmffImage img(std::move(io), false, 1000);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: pixelWidth and pixelHeight return 0 for minimal file
TEST_F(BmffImageTest_1200, PixelDimensionsZeroForMinimalFile_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    img.readMetadata();
    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test: exifData is empty for minimal BMFF
TEST_F(BmffImageTest_1200, ExifDataEmptyForMinimalBmff_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    img.readMetadata();
    EXPECT_TRUE(img.exifData().empty());
}

// Test: iptcData is empty for minimal BMFF
TEST_F(BmffImageTest_1200, IptcDataEmptyForMinimalBmff_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    img.readMetadata();
    EXPECT_TRUE(img.iptcData().empty());
}

// Test: xmpData is empty for minimal BMFF
TEST_F(BmffImageTest_1200, XmpDataEmptyForMinimalBmff_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    img.readMetadata();
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: setComment is a no-op (BMFF doesn't support comments typically)
TEST_F(BmffImageTest_1200, SetCommentNoOp_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    ASSERT_NO_THROW(img.setComment("test comment"));
    // comment should remain empty since BMFF setComment is typically a no-op
    EXPECT_TRUE(img.comment().empty());
}

// Test: setExifData doesn't throw (may be a no-op for BMFF)
TEST_F(BmffImageTest_1200, SetExifDataNoThrow_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    ExifData exifData;
    ASSERT_NO_THROW(img.setExifData(exifData));
}

// Test: setIptcData doesn't throw
TEST_F(BmffImageTest_1200, SetIptcDataNoThrow_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    IptcData iptcData;
    ASSERT_NO_THROW(img.setIptcData(iptcData));
}

// Test: setXmpData doesn't throw
TEST_F(BmffImageTest_1200, SetXmpDataNoThrow_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    XmpData xmpData;
    ASSERT_NO_THROW(img.setXmpData(xmpData));
}

// Test: printStructure with kpsNone doesn't crash
TEST_F(BmffImageTest_1200, PrintStructureKpsNone_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    std::ostringstream oss;
    ASSERT_NO_THROW(img.printStructure(oss, kpsNone, 0));
}

// Test: printStructure with kpsBasic on minimal file
TEST_F(BmffImageTest_1200, PrintStructureKpsBasic_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    std::ostringstream oss;
    ASSERT_NO_THROW(img.printStructure(oss, kpsBasic, 0));
}

// Test: printStructure with kpsRecursive on minimal file
TEST_F(BmffImageTest_1200, PrintStructureKpsRecursive_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    std::ostringstream oss;
    ASSERT_NO_THROW(img.printStructure(oss, kpsRecursive, 0));
}

// Test: readMetadata with truncated/corrupt data
TEST_F(BmffImageTest_1200, ReadMetadataTruncatedData_1200) {
    // A box header that claims size larger than available data
    std::vector<uint8_t> data;
    // Box size = 100 (but we only have 8 bytes)
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x64); // 100
    data.push_back('f');
    data.push_back('t');
    data.push_back('y');
    data.push_back('p');
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    // May throw or handle gracefully - just ensure no undefined behavior
    try {
        img.readMetadata();
    } catch (const Error&) {
        // Expected for corrupt data
    }
}

// Test: readMetadata with a zero-size box (should not infinite loop)
TEST_F(BmffImageTest_1200, ReadMetadataZeroSizeBox_1200) {
    std::vector<uint8_t> data;
    // Box size = 0 means "extends to end of file" per ISO BMFF
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00); // size 0
    data.push_back('f');
    data.push_back('t');
    data.push_back('y');
    data.push_back('p');
    // major brand
    data.push_back('h');
    data.push_back('e');
    data.push_back('i');
    data.push_back('c');
    // minor version
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    try {
        img.readMetadata();
    } catch (const Error&) {
        // Acceptable
    }
}

// Test: io() returns a valid reference after construction
TEST_F(BmffImageTest_1200, IoReturnsValidReference_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    EXPECT_EQ(img.io().size(), data.size());
}

// Test: clearMetadata doesn't crash
TEST_F(BmffImageTest_1200, ClearMetadataNoThrow_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    img.readMetadata();
    ASSERT_NO_THROW(img.clearMetadata());
    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: readMetadata can be called multiple times
TEST_F(BmffImageTest_1200, ReadMetadataMultipleTimes_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    ASSERT_NO_THROW(img.readMetadata());
    ASSERT_NO_THROW(img.readMetadata());
    ASSERT_NO_THROW(img.readMetadata());
}

// Test: mimeType after reading metadata on minimal heic
TEST_F(BmffImageTest_1200, MimeTypeAfterReadMetadata_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    img.readMetadata();
    std::string mime = img.mimeType();
    // For heic ftyp, expected mime type should contain "heif" or "heic" or similar
    EXPECT_FALSE(mime.empty());
}

// Test: BmffImage with avif brand
TEST_F(BmffImageTest_1200, AvifBrandMimeType_1200) {
    std::vector<uint8_t> data;
    // ftyp box size = 20
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x14);
    data.push_back('f');
    data.push_back('t');
    data.push_back('y');
    data.push_back('p');
    // Major brand = 'avif'
    data.push_back('a');
    data.push_back('v');
    data.push_back('i');
    data.push_back('f');
    // Minor version
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    // Compatible brand
    data.push_back('a');
    data.push_back('v');
    data.push_back('i');
    data.push_back('f');

    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    img.readMetadata();
    std::string mime = img.mimeType();
    EXPECT_FALSE(mime.empty());
}

// Test: writeMetadata throws for BMFF (typically read-only or limited write support)
TEST_F(BmffImageTest_1200, WriteMetadataThrows_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    img.readMetadata();
    EXPECT_THROW(img.writeMetadata(), Error);
}

// Test: Very small data (less than a box header)
TEST_F(BmffImageTest_1200, ReadMetadataVerySmallData_1200) {
    std::vector<uint8_t> data = {0x00, 0x00, 0x00};
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    try {
        img.readMetadata();
    } catch (const Error&) {
        // Expected for data too small
    }
}

// Test: Single byte data
TEST_F(BmffImageTest_1200, ReadMetadataSingleByte_1200) {
    std::vector<uint8_t> data = {0x42};
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    try {
        img.readMetadata();
    } catch (const Error&) {
        // Expected
    }
}

// Test: max_box_depth parameter with very small depth
TEST_F(BmffImageTest_1200, SmallMaxBoxDepth_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1); // very shallow depth
    ASSERT_NO_THROW(img.readMetadata());
}

// Test: clearExifData, clearIptcData, clearXmpData individually
TEST_F(BmffImageTest_1200, ClearIndividualMetadata_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    img.readMetadata();
    ASSERT_NO_THROW(img.clearExifData());
    ASSERT_NO_THROW(img.clearIptcData());
    ASSERT_NO_THROW(img.clearXmpData());
    ASSERT_NO_THROW(img.clearComment());
}

// Test: xmpPacket is empty for minimal BMFF
TEST_F(BmffImageTest_1200, XmpPacketEmptyForMinimalBmff_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    img.readMetadata();
    EXPECT_TRUE(img.xmpPacket().empty());
}

// Test: Multiple ftyp boxes (unusual but shouldn't crash)
TEST_F(BmffImageTest_1200, MultipleFtypBoxes_1200) {
    auto data = createMinimalBmffData();
    auto data2 = createMinimalBmffData();
    data.insert(data.end(), data2.begin(), data2.end());
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    try {
        img.readMetadata();
    } catch (const Error&) {
        // May or may not throw
    }
}

// Test: iccProfile is not defined for minimal file
TEST_F(BmffImageTest_1200, IccProfileNotDefined_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    img.readMetadata();
    EXPECT_FALSE(img.iccProfileDefined());
}

// Test: printStructure with kpsXMP on minimal file
TEST_F(BmffImageTest_1200, PrintStructureKpsXMP_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    std::ostringstream oss;
    ASSERT_NO_THROW(img.printStructure(oss, kpsXMP, 0));
}

// Test: printStructure with kpsIccProfile on minimal file
TEST_F(BmffImageTest_1200, PrintStructureKpsIccProfile_1200) {
    auto data = createMinimalBmffData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    BmffImage img(std::move(io), false, 1000);
    std::ostringstream oss;
    ASSERT_NO_THROW(img.printStructure(oss, kpsIccProfile, 0));
}
