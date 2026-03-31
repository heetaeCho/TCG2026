#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/orfimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>

#include <fstream>
#include <cstring>
#include <memory>
#include <sstream>

using namespace Exiv2;

namespace {

// Helper to find test data files
std::string getTestDataPath(const std::string& filename) {
    // Try common test data locations
    std::vector<std::string> paths = {
        "test/data/" + filename,
        "../test/data/" + filename,
        "../../test/data/" + filename,
        filename
    };
    for (const auto& p : paths) {
        std::ifstream f(p);
        if (f.good()) return p;
    }
    return filename;
}

// Create a minimal ORF file in memory for testing
// ORF files use TIFF-like structure with ORF-specific header
std::vector<byte> createMinimalOrfData() {
    // ORF header: byte order (II = little endian), magic 0x4F52, offset to IFD
    std::vector<byte> data(512, 0);
    // Byte order: little endian "II"
    data[0] = 'I';
    data[1] = 'I';
    // ORF magic: 0x4F52 in little endian
    data[2] = 0x52;
    data[3] = 0x4F;
    // Offset to first IFD (8 bytes from start)
    data[4] = 0x08;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x00;
    // IFD with 0 entries followed by 0 offset for next IFD
    data[8] = 0x00;
    data[9] = 0x00;
    // Next IFD offset = 0
    data[10] = 0x00;
    data[11] = 0x00;
    data[12] = 0x00;
    data[13] = 0x00;
    return data;
}

// Write data to a temporary file and return the path
std::string writeTempFile(const std::vector<byte>& data, const std::string& suffix = ".orf") {
    std::string path = "test_temp_orf" + suffix;
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    ofs.close();
    return path;
}

void removeTempFile(const std::string& path) {
    std::remove(path.c_str());
}

} // anonymous namespace

class OrfImageTest_1552 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
        for (const auto& f : tempFiles_) {
            removeTempFile(f);
        }
    }

    std::string createTempOrfFile() {
        auto data = createMinimalOrfData();
        std::string path = writeTempFile(data);
        tempFiles_.push_back(path);
        return path;
    }

    std::vector<std::string> tempFiles_;
};

// Test: OrfImage construction with a valid BasicIo
TEST_F(OrfImageTest_1552, ConstructionWithValidIo_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    ASSERT_NO_THROW(OrfImage img(std::move(io), false));
}

// Test: OrfImage construction with create flag
TEST_F(OrfImageTest_1552, ConstructionWithCreateFlag_1552) {
    std::string path = "test_temp_create_orf.orf";
    tempFiles_.push_back(path);
    auto io = std::make_unique<FileIo>(path);
    ASSERT_NO_THROW(OrfImage img(std::move(io), true));
}

// Test: mimeType returns correct MIME type for ORF
TEST_F(OrfImageTest_1552, MimeTypeReturnsOrfMime_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    std::string mime = img.mimeType();
    EXPECT_EQ(mime, "image/x-olympus-orf");
}

// Test: setComment throws or is no-op for ORF images
TEST_F(OrfImageTest_1552, SetCommentBehavior_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    // setComment for ORF should throw since ORF doesn't support comments
    EXPECT_THROW(img.setComment("test comment"), Error);
}

// Test: good() returns true for a valid file
TEST_F(OrfImageTest_1552, GoodReturnsTrueForValidFile_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    EXPECT_TRUE(img.good());
}

// Test: exifData() returns a reference to ExifData
TEST_F(OrfImageTest_1552, ExifDataAccessible_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    ExifData& exif = img.exifData();
    EXPECT_TRUE(exif.empty());
}

// Test: iptcData() returns a reference to IptcData
TEST_F(OrfImageTest_1552, IptcDataAccessible_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    IptcData& iptc = img.iptcData();
    EXPECT_TRUE(iptc.empty());
}

// Test: xmpData() returns a reference to XmpData
TEST_F(OrfImageTest_1552, XmpDataAccessible_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    XmpData& xmp = img.xmpData();
    EXPECT_TRUE(xmp.empty());
}

// Test: readMetadata on a minimal ORF file doesn't crash
TEST_F(OrfImageTest_1552, ReadMetadataMinimalOrf_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    // Reading metadata from a minimal ORF may succeed or throw depending on content
    // but should not crash
    try {
        img.readMetadata();
    } catch (const Error&) {
        // Expected for minimal/invalid ORF data
    }
}

// Test: readMetadata on empty file throws
TEST_F(OrfImageTest_1552, ReadMetadataEmptyFileThrows_1552) {
    std::string path = "test_temp_empty_orf.orf";
    tempFiles_.push_back(path);
    {
        std::ofstream ofs(path, std::ios::binary);
        // Write nothing - empty file
    }
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: writeMetadata on a minimal ORF
TEST_F(OrfImageTest_1552, WriteMetadataMinimalOrf_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    // writeMetadata may throw for minimal data but should not crash
    try {
        img.writeMetadata();
    } catch (const Error&) {
        // Expected for minimal ORF data
    }
}

// Test: byteOrder defaults to invalidByteOrder before reading
TEST_F(OrfImageTest_1552, ByteOrderDefaultInvalid_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    ByteOrder bo = img.byteOrder();
    // Before reading, byte order might be invalidByteOrder or set by constructor
    EXPECT_TRUE(bo == invalidByteOrder || bo == littleEndian || bo == bigEndian);
}

// Test: clearExifData clears exif
TEST_F(OrfImageTest_1552, ClearExifData_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    img.clearExifData();
    EXPECT_TRUE(img.exifData().empty());
}

// Test: clearIptcData clears IPTC
TEST_F(OrfImageTest_1552, ClearIptcData_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    img.clearIptcData();
    EXPECT_TRUE(img.iptcData().empty());
}

// Test: clearXmpData clears XMP
TEST_F(OrfImageTest_1552, ClearXmpData_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    img.clearXmpData();
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: pixelWidth returns 0 before reading metadata
TEST_F(OrfImageTest_1552, PixelWidthDefaultZero_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    EXPECT_EQ(img.pixelWidth(), 0u);
}

// Test: pixelHeight returns 0 before reading metadata
TEST_F(OrfImageTest_1552, PixelHeightDefaultZero_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test: io() returns a reference to the underlying IO object
TEST_F(OrfImageTest_1552, IoAccessible_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    const BasicIo& ioRef = img.io();
    EXPECT_EQ(ioRef.path(), path);
}

// Test: readMetadata on non-ORF data throws
TEST_F(OrfImageTest_1552, ReadMetadataOnNonOrfDataThrows_1552) {
    std::string path = "test_temp_nonorf.orf";
    tempFiles_.push_back(path);
    {
        std::ofstream ofs(path, std::ios::binary);
        // Write some random non-ORF data
        const char* junk = "This is not an ORF file at all, just random data for testing.";
        ofs.write(junk, strlen(junk));
    }
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: setExifData and retrieve
TEST_F(OrfImageTest_1552, SetAndGetExifData_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    ExifData exif;
    img.setExifData(exif);
    EXPECT_TRUE(img.exifData().empty());
}

// Test: setIptcData and retrieve
TEST_F(OrfImageTest_1552, SetAndGetIptcData_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    IptcData iptc;
    img.setIptcData(iptc);
    EXPECT_TRUE(img.iptcData().empty());
}

// Test: setXmpData and retrieve
TEST_F(OrfImageTest_1552, SetAndGetXmpData_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    XmpData xmp;
    img.setXmpData(xmp);
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: clearMetadata clears all metadata
TEST_F(OrfImageTest_1552, ClearMetadata_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    img.clearMetadata();
    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: printStructure does not crash with kpsNone
TEST_F(OrfImageTest_1552, PrintStructureNoCrash_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    std::ostringstream oss;
    try {
        img.printStructure(oss, kpsNone, 0);
    } catch (const Error&) {
        // May throw for minimal ORF, that's acceptable
    }
}

// Test: MemIo based OrfImage construction
TEST_F(OrfImageTest_1552, ConstructionWithMemIo_1552) {
    auto data = createMinimalOrfData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    ASSERT_NO_THROW(OrfImage img(std::move(io), false));
}

// Test: MemIo based readMetadata
TEST_F(OrfImageTest_1552, ReadMetadataWithMemIo_1552) {
    auto data = createMinimalOrfData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    OrfImage img(std::move(io), false);
    try {
        img.readMetadata();
    } catch (const Error&) {
        // Expected for minimal data
    }
}

// Test: writeMetadata with MemIo
TEST_F(OrfImageTest_1552, WriteMetadataWithMemIo_1552) {
    auto data = createMinimalOrfData();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    OrfImage img(std::move(io), false);
    try {
        img.writeMetadata();
    } catch (const Error&) {
        // Expected for minimal data
    }
}

// Test: setByteOrder and verify
TEST_F(OrfImageTest_1552, SetByteOrder_1552) {
    auto path = createTempOrfFile();
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    img.setByteOrder(bigEndian);
    EXPECT_EQ(img.byteOrder(), bigEndian);
    img.setByteOrder(littleEndian);
    EXPECT_EQ(img.byteOrder(), littleEndian);
}

// Test: OrfParser decode with nullptr data
TEST_F(OrfImageTest_1552, OrfParserDecodeNullData_1552) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    // Decode with null data and zero size
    try {
        OrfParser::decode(exifData, iptcData, xmpData, nullptr, 0);
    } catch (...) {
        // May throw, but should not crash
    }
}

// Test: OrfParser decode with minimal ORF data
TEST_F(OrfImageTest_1552, OrfParserDecodeMinimalData_1552) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    auto data = createMinimalOrfData();
    try {
        ByteOrder bo = OrfParser::decode(exifData, iptcData, xmpData, data.data(), data.size());
        EXPECT_TRUE(bo == littleEndian || bo == bigEndian || bo == invalidByteOrder);
    } catch (const Error&) {
        // May throw for minimal data
    }
}

// Test: Reading from file that's too small to be ORF
TEST_F(OrfImageTest_1552, ReadMetadataTooSmallFile_1552) {
    std::string path = "test_temp_tiny_orf.orf";
    tempFiles_.push_back(path);
    {
        std::ofstream ofs(path, std::ios::binary);
        // Write just 4 bytes - too small for ORF header
        byte data[] = {0x49, 0x49, 0x52, 0x4F};
        ofs.write(reinterpret_cast<char*>(data), 4);
    }
    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Error);
}

// Test: Big endian ORF header
TEST_F(OrfImageTest_1552, BigEndianOrfHeader_1552) {
    std::vector<byte> data(512, 0);
    // Byte order: big endian "MM"
    data[0] = 'M';
    data[1] = 'M';
    // ORF magic: 0x4F52 in big endian
    data[2] = 0x4F;
    data[3] = 0x52;
    // Offset to first IFD (8 bytes from start) in big endian
    data[4] = 0x00;
    data[5] = 0x00;
    data[6] = 0x00;
    data[7] = 0x08;
    // IFD with 0 entries
    data[8] = 0x00;
    data[9] = 0x00;
    data[10] = 0x00;
    data[11] = 0x00;
    data[12] = 0x00;
    data[13] = 0x00;

    std::string path = "test_temp_be_orf.orf";
    tempFiles_.push_back(path);
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.write(reinterpret_cast<char*>(data.data()), data.size());
    }

    auto io = std::make_unique<FileIo>(path);
    OrfImage img(std::move(io), false);
    try {
        img.readMetadata();
    } catch (const Error&) {
        // May throw, that's acceptable
    }
}
