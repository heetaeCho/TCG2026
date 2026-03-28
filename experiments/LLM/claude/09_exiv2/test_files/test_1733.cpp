#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include <exiv2/tiffimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>

#include <fstream>
#include <cstring>
#include <memory>
#include <vector>

namespace {

// Helper to create a minimal valid TIFF file in memory (little-endian)
std::vector<Exiv2::byte> createMinimalTiffLE() {
    std::vector<Exiv2::byte> tiff;
    // TIFF header: byte order (II = little endian), magic 42, offset to first IFD
    // II
    tiff.push_back('I');
    tiff.push_back('I');
    // Magic number 42 (little-endian)
    tiff.push_back(0x2A);
    tiff.push_back(0x00);
    // Offset to first IFD (8)
    tiff.push_back(0x08);
    tiff.push_back(0x00);
    tiff.push_back(0x00);
    tiff.push_back(0x00);
    // IFD with 0 entries
    tiff.push_back(0x00);
    tiff.push_back(0x00);
    // Next IFD offset = 0 (no more IFDs)
    tiff.push_back(0x00);
    tiff.push_back(0x00);
    tiff.push_back(0x00);
    tiff.push_back(0x00);
    return tiff;
}

// Helper to create a minimal valid TIFF file in memory (big-endian)
std::vector<Exiv2::byte> createMinimalTiffBE() {
    std::vector<Exiv2::byte> tiff;
    // MM
    tiff.push_back('M');
    tiff.push_back('M');
    // Magic number 42 (big-endian)
    tiff.push_back(0x00);
    tiff.push_back(0x2A);
    // Offset to first IFD (8)
    tiff.push_back(0x00);
    tiff.push_back(0x00);
    tiff.push_back(0x00);
    tiff.push_back(0x08);
    // IFD with 0 entries
    tiff.push_back(0x00);
    tiff.push_back(0x00);
    // Next IFD offset = 0
    tiff.push_back(0x00);
    tiff.push_back(0x00);
    tiff.push_back(0x00);
    tiff.push_back(0x00);
    return tiff;
}

// Write bytes to a temporary file and return the path
std::string writeTempFile(const std::vector<Exiv2::byte>& data, const std::string& suffix = ".tif") {
    std::string path = std::tmpnam(nullptr);
    path += suffix;
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    ofs.close();
    return path;
}

void removeTempFile(const std::string& path) {
    std::remove(path.c_str());
}

} // anonymous namespace

class TiffImageTest_1733 : public ::testing::Test {
protected:
    void TearDown() override {
        for (auto& f : tempFiles_) {
            removeTempFile(f);
        }
    }

    std::string createTempTiffLE() {
        auto data = createMinimalTiffLE();
        std::string path = writeTempFile(data);
        tempFiles_.push_back(path);
        return path;
    }

    std::string createTempTiffBE() {
        auto data = createMinimalTiffBE();
        std::string path = writeTempFile(data);
        tempFiles_.push_back(path);
        return path;
    }

    std::vector<std::string> tempFiles_;
};

// Test: TiffImage can be created with a valid file IO
TEST_F(TiffImageTest_1733, ConstructionWithValidIO_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    ASSERT_NO_THROW(Exiv2::TiffImage img(std::move(io), false));
}

// Test: mimeType returns correct TIFF MIME type
TEST_F(TiffImageTest_1733, MimeTypeReturnsTiff_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    std::string mime = img.mimeType();
    EXPECT_EQ(mime, "image/tiff");
}

// Test: setComment throws or is a no-op for TIFF images
TEST_F(TiffImageTest_1733, SetCommentNoOp_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    // setComment is expected to throw for TIFF
    EXPECT_THROW(img.setComment("test comment"), Exiv2::Error);
}

// Test: readMetadata on a minimal TIFF doesn't crash
TEST_F(TiffImageTest_1733, ReadMetadataMinimalTiff_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    ASSERT_NO_THROW(img.readMetadata());
}

// Test: readMetadata on a big-endian TIFF
TEST_F(TiffImageTest_1733, ReadMetadataBigEndianTiff_1733) {
    std::string path = createTempTiffBE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    ASSERT_NO_THROW(img.readMetadata());
}

// Test: exifData is accessible and initially empty after reading minimal TIFF
TEST_F(TiffImageTest_1733, ExifDataEmptyAfterRead_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    img.readMetadata();
    EXPECT_TRUE(img.exifData().empty());
}

// Test: iptcData is accessible and initially empty
TEST_F(TiffImageTest_1733, IptcDataEmptyAfterRead_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    img.readMetadata();
    EXPECT_TRUE(img.iptcData().empty());
}

// Test: xmpData is accessible and initially empty
TEST_F(TiffImageTest_1733, XmpDataEmptyAfterRead_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    img.readMetadata();
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: good() returns true for a valid TIFF
TEST_F(TiffImageTest_1733, GoodReturnsTrue_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    EXPECT_TRUE(img.good());
}

// Test: writeMetadata on a minimal TIFF doesn't crash
TEST_F(TiffImageTest_1733, WriteMetadataMinimalTiff_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    img.readMetadata();
    ASSERT_NO_THROW(img.writeMetadata());
}

// Test: writeMetadata preserves the ability to re-read
TEST_F(TiffImageTest_1733, WriteAndRereadMetadata_1733) {
    std::string path = createTempTiffLE();
    {
        auto io = std::make_unique<Exiv2::FileIo>(path);
        Exiv2::TiffImage img(std::move(io), false);
        img.readMetadata();
        // Add an exif tag
        img.exifData()["Exif.Image.Make"] = "TestMake";
        img.writeMetadata();
    }
    {
        auto io = std::make_unique<Exiv2::FileIo>(path);
        Exiv2::TiffImage img(std::move(io), false);
        img.readMetadata();
        auto pos = img.exifData().findKey(Exiv2::ExifKey("Exif.Image.Make"));
        ASSERT_NE(pos, img.exifData().end());
        EXPECT_EQ(pos->toString(), "TestMake");
    }
}

// Test: pixelWidth and pixelHeight are 0 for minimal TIFF
TEST_F(TiffImageTest_1733, PixelDimensionsMinimalTiff_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    img.readMetadata();
    // Minimal TIFF has no image dimensions set
    EXPECT_EQ(img.pixelWidth(), 0u);
    EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test: clearExifData clears the exif data
TEST_F(TiffImageTest_1733, ClearExifData_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    img.readMetadata();
    img.exifData()["Exif.Image.Make"] = "Test";
    EXPECT_FALSE(img.exifData().empty());
    img.clearExifData();
    EXPECT_TRUE(img.exifData().empty());
}

// Test: clearIptcData clears the IPTC data
TEST_F(TiffImageTest_1733, ClearIptcData_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    img.readMetadata();
    img.clearIptcData();
    EXPECT_TRUE(img.iptcData().empty());
}

// Test: clearXmpData clears the XMP data
TEST_F(TiffImageTest_1733, ClearXmpData_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    img.readMetadata();
    img.clearXmpData();
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: setByteOrder and byteOrder
TEST_F(TiffImageTest_1733, SetAndGetByteOrder_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    img.setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(img.byteOrder(), Exiv2::bigEndian);
    img.setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(img.byteOrder(), Exiv2::littleEndian);
}

// Test: readMetadata on non-TIFF file throws
TEST_F(TiffImageTest_1733, ReadMetadataInvalidFile_1733) {
    std::vector<Exiv2::byte> garbage = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    std::string path = writeTempFile(garbage, ".tif");
    tempFiles_.push_back(path);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: writeMetadata with ICC profile
TEST_F(TiffImageTest_1733, WriteMetadataWithIccProfile_1733) {
    std::string path = createTempTiffLE();
    {
        auto io = std::make_unique<Exiv2::FileIo>(path);
        Exiv2::TiffImage img(std::move(io), false);
        img.readMetadata();

        // Create a fake ICC profile (just needs some bytes)
        // A real ICC profile starts with size at offset 0, but we just test the interface
        std::vector<Exiv2::byte> iccData(128, 0);
        // Minimal ICC header: size field
        uint32_t sz = 128;
        iccData[0] = (sz >> 24) & 0xFF;
        iccData[1] = (sz >> 16) & 0xFF;
        iccData[2] = (sz >> 8) & 0xFF;
        iccData[3] = sz & 0xFF;
        // "acsp" signature at offset 36
        iccData[36] = 'a';
        iccData[37] = 'c';
        iccData[38] = 's';
        iccData[39] = 'p';

        Exiv2::DataBuf iccBuf(iccData.data(), iccData.size());
        img.setIccProfile(std::move(iccBuf), false);
        EXPECT_TRUE(img.iccProfileDefined());
        ASSERT_NO_THROW(img.writeMetadata());
    }
}

// Test: clearIccProfile removes the ICC profile
TEST_F(TiffImageTest_1733, ClearIccProfile_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    img.readMetadata();

    std::vector<Exiv2::byte> iccData(128, 0);
    uint32_t sz = 128;
    iccData[0] = (sz >> 24) & 0xFF;
    iccData[1] = (sz >> 16) & 0xFF;
    iccData[2] = (sz >> 8) & 0xFF;
    iccData[3] = sz & 0xFF;
    iccData[36] = 'a';
    iccData[37] = 'c';
    iccData[38] = 's';
    iccData[39] = 'p';

    Exiv2::DataBuf iccBuf(iccData.data(), iccData.size());
    img.setIccProfile(std::move(iccBuf), false);
    EXPECT_TRUE(img.iccProfileDefined());
    img.clearIccProfile();
    EXPECT_FALSE(img.iccProfileDefined());
}

// Test: writeXmpFromPacket flag
TEST_F(TiffImageTest_1733, WriteXmpFromPacketFlag_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    
    img.writeXmpFromPacket(true);
    EXPECT_TRUE(img.writeXmpFromPacket());
    img.writeXmpFromPacket(false);
    EXPECT_FALSE(img.writeXmpFromPacket());
}

// Test: Multiple exif tags can be added and written
TEST_F(TiffImageTest_1733, MultipleExifTagsWriteRead_1733) {
    std::string path = createTempTiffLE();
    {
        auto io = std::make_unique<Exiv2::FileIo>(path);
        Exiv2::TiffImage img(std::move(io), false);
        img.readMetadata();
        img.exifData()["Exif.Image.Make"] = "TestMake";
        img.exifData()["Exif.Image.Model"] = "TestModel";
        img.exifData()["Exif.Image.Software"] = "TestSoftware";
        img.writeMetadata();
    }
    {
        auto io = std::make_unique<Exiv2::FileIo>(path);
        Exiv2::TiffImage img(std::move(io), false);
        img.readMetadata();
        
        auto posMake = img.exifData().findKey(Exiv2::ExifKey("Exif.Image.Make"));
        ASSERT_NE(posMake, img.exifData().end());
        EXPECT_EQ(posMake->toString(), "TestMake");
        
        auto posModel = img.exifData().findKey(Exiv2::ExifKey("Exif.Image.Model"));
        ASSERT_NE(posModel, img.exifData().end());
        EXPECT_EQ(posModel->toString(), "TestModel");
        
        auto posSoftware = img.exifData().findKey(Exiv2::ExifKey("Exif.Image.Software"));
        ASSERT_NE(posSoftware, img.exifData().end());
        EXPECT_EQ(posSoftware->toString(), "TestSoftware");
    }
}

// Test: io() returns a reference to the underlying IO
TEST_F(TiffImageTest_1733, IoAccessor_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    EXPECT_EQ(img.io().path(), path);
}

// Test: TiffParser::decode with minimal data
TEST_F(TiffImageTest_1733, TiffParserDecodeMinimalLE_1733) {
    auto data = createMinimalTiffLE();
    Exiv2::ExifData exifData;
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    Exiv2::ByteOrder bo = Exiv2::TiffParser::decode(exifData, iptcData, xmpData,
                                                      data.data(), data.size());
    EXPECT_EQ(bo, Exiv2::littleEndian);
}

// Test: TiffParser::decode with big-endian minimal data
TEST_F(TiffImageTest_1733, TiffParserDecodeMinimalBE_1733) {
    auto data = createMinimalTiffBE();
    Exiv2::ExifData exifData;
    Exiv2::IptcData iptcData;
    Exiv2::XmpData xmpData;
    
    Exiv2::ByteOrder bo = Exiv2::TiffParser::decode(exifData, iptcData, xmpData,
                                                      data.data(), data.size());
    EXPECT_EQ(bo, Exiv2::bigEndian);
}

// Test: Reading an empty/zero-size file
TEST_F(TiffImageTest_1733, ReadMetadataEmptyFile_1733) {
    std::vector<Exiv2::byte> empty;
    std::string path = writeTempFile(empty, ".tif");
    tempFiles_.push_back(path);
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test: clearMetadata clears all metadata
TEST_F(TiffImageTest_1733, ClearMetadata_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    img.readMetadata();
    img.exifData()["Exif.Image.Make"] = "Test";
    img.clearMetadata();
    EXPECT_TRUE(img.exifData().empty());
    EXPECT_TRUE(img.iptcData().empty());
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: supportsMetadata returns true for expected metadata types
TEST_F(TiffImageTest_1733, SupportsMetadata_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    EXPECT_TRUE(img.supportsMetadata(Exiv2::mdExif));
    EXPECT_TRUE(img.supportsMetadata(Exiv2::mdIptc));
    EXPECT_TRUE(img.supportsMetadata(Exiv2::mdXmp));
}

// Test: writeMetadata with invalidByteOrder defaults to littleEndian
TEST_F(TiffImageTest_1733, WriteMetadataInvalidByteOrderDefaultsToLE_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    // Don't read metadata, so byteOrder might be invalid
    img.setByteOrder(Exiv2::invalidByteOrder);
    img.exifData()["Exif.Image.Make"] = "Test";
    // writeMetadata should handle invalidByteOrder gracefully
    ASSERT_NO_THROW(img.writeMetadata());
}

// Test: Erase exif tag and write
TEST_F(TiffImageTest_1733, EraseExifTagAndWrite_1733) {
    std::string path = createTempTiffLE();
    {
        auto io = std::make_unique<Exiv2::FileIo>(path);
        Exiv2::TiffImage img(std::move(io), false);
        img.readMetadata();
        img.exifData()["Exif.Image.Make"] = "TestMake";
        img.exifData()["Exif.Image.Model"] = "TestModel";
        img.writeMetadata();
    }
    {
        auto io = std::make_unique<Exiv2::FileIo>(path);
        Exiv2::TiffImage img(std::move(io), false);
        img.readMetadata();
        auto pos = img.exifData().findKey(Exiv2::ExifKey("Exif.Image.Make"));
        ASSERT_NE(pos, img.exifData().end());
        img.exifData().erase(pos);
        img.writeMetadata();
    }
    {
        auto io = std::make_unique<Exiv2::FileIo>(path);
        Exiv2::TiffImage img(std::move(io), false);
        img.readMetadata();
        auto pos = img.exifData().findKey(Exiv2::ExifKey("Exif.Image.Make"));
        EXPECT_EQ(pos, img.exifData().end());
        auto posModel = img.exifData().findKey(Exiv2::ExifKey("Exif.Image.Model"));
        ASSERT_NE(posModel, img.exifData().end());
        EXPECT_EQ(posModel->toString(), "TestModel");
    }
}

// Test: MemIo-based TiffImage creation
TEST_F(TiffImageTest_1733, ConstructionWithMemIo_1733) {
    auto data = createMinimalTiffLE();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    ASSERT_NO_THROW(Exiv2::TiffImage img(std::move(io), false));
}

// Test: Read and write metadata with MemIo
TEST_F(TiffImageTest_1733, ReadWriteWithMemIo_1733) {
    auto data = createMinimalTiffLE();
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    Exiv2::TiffImage img(std::move(io), false);
    img.readMetadata();
    img.exifData()["Exif.Image.Make"] = "MemTest";
    ASSERT_NO_THROW(img.writeMetadata());
}

// Test: printStructure doesn't crash on minimal TIFF
TEST_F(TiffImageTest_1733, PrintStructureMinimalTiff_1733) {
    std::string path = createTempTiffLE();
    auto io = std::make_unique<Exiv2::FileIo>(path);
    Exiv2::TiffImage img(std::move(io), false);
    std::ostringstream oss;
    ASSERT_NO_THROW(img.printStructure(oss, Exiv2::kpsBasic, 0));
}
