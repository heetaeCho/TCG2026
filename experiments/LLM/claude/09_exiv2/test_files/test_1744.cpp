#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/cr2image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/exif.hpp>

#include <fstream>
#include <cstdio>
#include <memory>
#include <sstream>

using namespace Exiv2;

namespace {

// Helper to create a temporary file with given content
class TempFile {
public:
    explicit TempFile(const std::string& suffix = ".cr2") {
        path_ = std::tmpnam(nullptr) + suffix;
    }
    ~TempFile() {
        std::remove(path_.c_str());
    }
    const std::string& path() const { return path_; }

    void write(const byte* data, size_t size) {
        std::ofstream ofs(path_, std::ios::binary);
        ofs.write(reinterpret_cast<const char*>(data), size);
    }

    void writeEmpty() {
        std::ofstream ofs(path_, std::ios::binary);
        // Write nothing
    }

private:
    std::string path_;
};

// Minimal CR2 header bytes (little endian)
// CR2 files start with a TIFF header: byte order (II=LE or MM=BE), magic 42, offset to IFD0
// followed by CR2-specific magic: "CR" and version
std::vector<byte> createMinimalCr2Header() {
    std::vector<byte> data(16, 0);
    // Little endian byte order mark
    data[0] = 'I';
    data[1] = 'I';
    // TIFF magic number 42 (little endian)
    data[2] = 42;
    data[3] = 0;
    // Offset to IFD0 (16 bytes)
    data[4] = 0x10;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x00;
    // CR2 magic: "CR"
    data[8] = 'C';
    data[9] = 'R';
    // CR2 version: major 2, minor 0
    data[10] = 2;
    data[11] = 0;
    // Offset to RAW IFD (can be 0 for testing)
    data[12] = 0x00;
    data[13] = 0x00;
    data[14] = 0x00;
    data[15] = 0x00;
    return data;
}

} // anonymous namespace

class Cr2ImageTest_1744 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that Cr2Image can be constructed with a MemIo
TEST_F(Cr2ImageTest_1744, ConstructWithMemIo_1744) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NO_THROW(Cr2Image img(std::move(io), false));
}

// Test that Cr2Image can be constructed with create=true
TEST_F(Cr2ImageTest_1744, ConstructWithCreateTrue_1744) {
    auto io = std::make_unique<MemIo>();
    ASSERT_NO_THROW(Cr2Image img(std::move(io), true));
}

// Test mimeType returns "image/x-canon-cr2"
TEST_F(Cr2ImageTest_1744, MimeType_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_EQ(img.mimeType(), "image/x-canon-cr2");
}

// Test that good() returns false for empty MemIo
TEST_F(Cr2ImageTest_1744, GoodReturnsFalseForEmptyIo_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    // An empty IO won't have valid CR2 data
    EXPECT_FALSE(img.good());
}

// Test that setComment throws (CR2 doesn't support comments typically)
TEST_F(Cr2ImageTest_1744, SetCommentThrows_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.setComment("test comment"), Error);
}

// Test readMetadata on empty data throws
TEST_F(Cr2ImageTest_1744, ReadMetadataEmptyThrows_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test readMetadata on garbage data throws
TEST_F(Cr2ImageTest_1744, ReadMetadataGarbageDataThrows_1744) {
    byte garbage[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    auto io = std::make_unique<MemIo>(garbage, sizeof(garbage));
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test that exifData returns a reference (initially empty)
TEST_F(Cr2ImageTest_1744, ExifDataInitiallyEmpty_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.exifData().empty());
}

// Test that iptcData returns a reference (initially empty)
TEST_F(Cr2ImageTest_1744, IptcDataInitiallyEmpty_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.iptcData().empty());
}

// Test that xmpData returns a reference (initially empty)
TEST_F(Cr2ImageTest_1744, XmpDataInitiallyEmpty_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.xmpData().empty());
}

// Test pixelWidth returns 0 for uninitialized image
TEST_F(Cr2ImageTest_1744, PixelWidthDefaultZero_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_EQ(img.pixelWidth(), 0u);
}

// Test pixelHeight returns 0 for uninitialized image
TEST_F(Cr2ImageTest_1744, PixelHeightDefaultZero_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test byteOrder returns invalidByteOrder initially
TEST_F(Cr2ImageTest_1744, ByteOrderInitiallyInvalid_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_EQ(img.byteOrder(), invalidByteOrder);
}

// Test setByteOrder and byteOrder
TEST_F(Cr2ImageTest_1744, SetAndGetByteOrder_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    img.setByteOrder(littleEndian);
    EXPECT_EQ(img.byteOrder(), littleEndian);
    img.setByteOrder(bigEndian);
    EXPECT_EQ(img.byteOrder(), bigEndian);
}

// Test clearExifData
TEST_F(Cr2ImageTest_1744, ClearExifData_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    img.exifData()["Exif.Image.Make"] = "Canon";
    EXPECT_FALSE(img.exifData().empty());
    img.clearExifData();
    EXPECT_TRUE(img.exifData().empty());
}

// Test clearIptcData
TEST_F(Cr2ImageTest_1744, ClearIptcData_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    img.clearIptcData();
    EXPECT_TRUE(img.iptcData().empty());
}

// Test clearXmpData
TEST_F(Cr2ImageTest_1744, ClearXmpData_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    img.clearXmpData();
    EXPECT_TRUE(img.xmpData().empty());
}

// Test clearMetadata clears all metadata
TEST_F(Cr2ImageTest_1744, ClearMetadata_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    img.exifData()["Exif.Image.Make"] = "Canon";
    img.clearMetadata();
    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test writeMetadata on empty image (no valid CR2 data)
// Should still attempt to write, may use littleEndian as default
TEST_F(Cr2ImageTest_1744, WriteMetadataEmptyIo_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    // writeMetadata on empty io - the behavior depends on implementation
    // but it should not crash; it may throw
    try {
        img.writeMetadata();
    } catch (const Error&) {
        // Expected - writing to empty/invalid CR2 may throw
    }
}

// Test setExifData and verify it persists
TEST_F(Cr2ImageTest_1744, SetExifData_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    ExifData exifData;
    exifData["Exif.Image.Make"] = "Canon";
    img.setExifData(exifData);
    EXPECT_FALSE(img.exifData().empty());
    auto it = img.exifData().findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, img.exifData().end());
    EXPECT_EQ(it->toString(), "Canon");
}

// Test setIptcData
TEST_F(Cr2ImageTest_1744, SetIptcData_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    IptcData iptcData;
    img.setIptcData(iptcData);
    EXPECT_TRUE(img.iptcData().empty());
}

// Test setXmpData
TEST_F(Cr2ImageTest_1744, SetXmpData_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    XmpData xmpData;
    img.setXmpData(xmpData);
    EXPECT_TRUE(img.xmpData().empty());
}

// Test io() accessor returns a reference
TEST_F(Cr2ImageTest_1744, IoAccessor_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_NO_THROW(img.io());
}

// Test readMetadata with only the CR2 header but no IFD data
TEST_F(Cr2ImageTest_1744, ReadMetadataMinimalHeader_1744) {
    auto headerData = createMinimalCr2Header();
    auto io = std::make_unique<MemIo>(headerData.data(), headerData.size());
    Cr2Image img(std::move(io), false);
    // Minimal header without proper IFD data should throw or handle gracefully
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test that readMetadata with too-short data throws
TEST_F(Cr2ImageTest_1744, ReadMetadataTooShortData_1744) {
    byte shortData[] = {'I', 'I'};
    auto io = std::make_unique<MemIo>(shortData, sizeof(shortData));
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test Cr2Parser::decode with null data
TEST_F(Cr2ImageTest_1744, Cr2ParserDecodeNullData_1744) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    // Decoding null/empty data
    EXPECT_THROW(Cr2Parser::decode(exifData, iptcData, xmpData, nullptr, 0), std::exception);
}

// Test printStructure doesn't crash (basic smoke test)
TEST_F(Cr2ImageTest_1744, PrintStructureSmoke_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    std::ostringstream oss;
    // Printing structure on empty image - may throw but shouldn't crash
    try {
        img.printStructure(oss, kpsNone, 0);
    } catch (const Error&) {
        // Acceptable
    }
}

// Test writeXmpFromPacket flag
TEST_F(Cr2ImageTest_1744, WriteXmpFromPacketFlag_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_FALSE(img.writeXmpFromPacket());
    img.writeXmpFromPacket(true);
    EXPECT_TRUE(img.writeXmpFromPacket());
    img.writeXmpFromPacket(false);
    EXPECT_FALSE(img.writeXmpFromPacket());
}

// Test iccProfile initially not defined
TEST_F(Cr2ImageTest_1744, IccProfileNotDefined_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_FALSE(img.iccProfileDefined());
}

// Test clearIccProfile
TEST_F(Cr2ImageTest_1744, ClearIccProfile_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    img.clearIccProfile();
    EXPECT_FALSE(img.iccProfileDefined());
}

// Test nativePreviews initially empty
TEST_F(Cr2ImageTest_1744, NativePreviewsEmpty_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.nativePreviews().empty());
}

// Test with FileIo on non-existent file
TEST_F(Cr2ImageTest_1744, ReadMetadataNonExistentFile_1744) {
    auto io = std::make_unique<FileIo>("/non/existent/path/fake.cr2");
    Cr2Image img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test writing metadata to MemIo with some exif data set
TEST_F(Cr2ImageTest_1744, WriteMetadataWithExifData_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    img.exifData()["Exif.Image.Make"] = "Canon";
    // Writing without valid underlying CR2 data - implementation specific behavior
    try {
        img.writeMetadata();
    } catch (const Error&) {
        // May throw, which is acceptable
    }
}

// Test that supportsMetadata returns correct values for CR2
TEST_F(Cr2ImageTest_1744, SupportsMetadata_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.supportsMetadata(mdExif));
    EXPECT_TRUE(img.supportsMetadata(mdIptc));
    EXPECT_TRUE(img.supportsMetadata(mdXmp));
}

// Test comment is empty by default
TEST_F(Cr2ImageTest_1744, CommentEmptyByDefault_1744) {
    auto io = std::make_unique<MemIo>();
    Cr2Image img(std::move(io), false);
    EXPECT_TRUE(img.comment().empty());
}

// Test Cr2Parser::decode with garbage data
TEST_F(Cr2ImageTest_1744, Cr2ParserDecodeGarbageData_1744) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    byte garbage[] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8,
                      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    // Decoding garbage data - should handle gracefully
    try {
        Cr2Parser::decode(exifData, iptcData, xmpData, garbage, sizeof(garbage));
    } catch (const std::exception&) {
        // Acceptable - garbage data should be rejected
    }
}
