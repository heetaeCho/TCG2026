#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstring>
#include <memory>
#include <vector>

#include "exiv2/rafimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/image.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;

// Helper to build a minimal valid RAF file in memory
static std::vector<byte> buildMinimalRafFile() {
    // RAF file structure:
    // Offset 0:  16 bytes magic "FUJIFILMCCD-RAW "
    // Offset 16: 4 bytes data1
    // Offset 20: 8 bytes data2
    // Offset 28: 32 bytes camera name
    // Offset 60: 4 bytes dir_version
    // Offset 64: 20 bytes unknown
    // Offset 84: 4 bytes jpg_img_offset
    // Offset 88: 4 bytes jpg_img_length
    // Offset 92: 4 bytes meta_off[0]
    // Offset 96: 4 bytes meta_len[0]
    // Offset 100: 4 bytes cfa_off[0]
    // Offset 104: 4 bytes cfa_len[0]
    // Offset 108: 4 bytes comp[0]
    // Offset 112: 4 bytes cfa_size[0]
    // Offset 116: 4 bytes cfa_data[0]
    // Offset 120: 4 bytes meta_off[1]
    // Offset 124: 4 bytes meta_len[1]
    // Offset 128: 4 bytes cfa_off[1]
    // Offset 132: 4 bytes cfa_len[1]
    // Offset 136: 4 bytes comp[1]
    // Offset 140: 4 bytes cfa_size[1]
    // Offset 144: 4 bytes cfa_data[1]
    // Then actual data sections...

    // We'll place JPEG data at offset 256, meta1 at 512, cfa1 at 768
    // Each section needs at least 16 bytes for payload read
    const size_t fileSize = 1024;
    std::vector<byte> buf(fileSize, 0);

    // Magic (16 bytes)
    const char* magic = "FUJIFILMCCD-RAW ";
    std::memcpy(buf.data(), magic, 16);

    // data1 (4 bytes at offset 16)
    buf[16] = '0'; buf[17] = '2'; buf[18] = '0'; buf[19] = '0';

    // data2 (8 bytes at offset 20)
    std::memcpy(buf.data() + 20, "12345678", 8);

    // camera (32 bytes at offset 28)
    std::memcpy(buf.data() + 28, "FujiTestCamera", 14);

    // dir_version (4 bytes at offset 60)
    buf[60] = '0'; buf[61] = '1'; buf[62] = '0'; buf[63] = '0';

    // unknown (20 bytes at offset 64) - just zeros

    // Helper lambda to write big-endian uint32
    auto writeU32BE = [&](size_t offset, uint32_t val) {
        buf[offset + 0] = static_cast<byte>((val >> 24) & 0xFF);
        buf[offset + 1] = static_cast<byte>((val >> 16) & 0xFF);
        buf[offset + 2] = static_cast<byte>((val >> 8) & 0xFF);
        buf[offset + 3] = static_cast<byte>(val & 0xFF);
    };

    // jpg_img_offset at offset 84, jpg_img_length at offset 88
    uint32_t jpgOff = 256;
    uint32_t jpgLen = 64;
    writeU32BE(84, jpgOff);
    writeU32BE(88, jpgLen);

    // meta_off[0] at 92, meta_len[0] at 96
    uint32_t metaOff0 = 512;
    uint32_t metaLen0 = 64;
    writeU32BE(92, metaOff0);
    writeU32BE(96, metaLen0);

    // cfa_off[0] at 100, cfa_len[0] at 104
    uint32_t cfaOff0 = 768;
    uint32_t cfaLen0 = 64;
    writeU32BE(100, cfaOff0);
    writeU32BE(104, cfaLen0);

    // comp[0] at 108
    writeU32BE(108, 0);
    // cfa_size[0] at 112
    writeU32BE(112, 0);
    // cfa_data[0] at 116
    writeU32BE(116, 0);

    // meta_off[1] at 120, meta_len[1] at 124 (set to 0 to skip)
    writeU32BE(120, 0);
    writeU32BE(124, 0);

    // cfa_off[1] at 128, cfa_len[1] at 132 (set to 0 to skip)
    writeU32BE(128, 0);
    writeU32BE(132, 0);

    // comp[1] at 136
    writeU32BE(136, 0);
    // cfa_size[1] at 140
    writeU32BE(140, 0);
    // cfa_data[1] at 144
    writeU32BE(144, 0);

    // Write some JPEG-like data at offset 256
    // Start with JPEG SOI marker
    buf[256] = 0xFF; buf[257] = 0xD8;
    std::memcpy(buf.data() + 258, "JPEG_TEST_DATA", 14);

    // Write some meta data at offset 512
    std::memcpy(buf.data() + 512, "META_DATA_BLOCK1", 16);

    // Write some CFA data at offset 768
    std::memcpy(buf.data() + 768, "CFA__DATA_BLOCK1", 16);

    return buf;
}

class RafImageTest_220 : public ::testing::Test {
protected:
    std::unique_ptr<RafImage> createRafImageFromData(const std::vector<byte>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        return std::make_unique<RafImage>(std::move(io), false);
    }

    std::unique_ptr<RafImage> createRafImageFromFile(const std::string& path) {
        auto io = std::make_unique<FileIo>(path);
        return std::make_unique<RafImage>(std::move(io), false);
    }
};

// Test that printStructure with kpsBasic on a valid RAF file produces expected output
TEST_F(RafImageTest_220, PrintStructureBasic_ValidRaf_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    EXPECT_NO_THROW(img->printStructure(oss, kpsBasic, 0));

    std::string output = oss.str();
    // Should contain the RAF structure header
    EXPECT_NE(output.find("STRUCTURE OF RAF FILE"), std::string::npos);
    // Should contain the magic
    EXPECT_NE(output.find("magic"), std::string::npos);
    EXPECT_NE(output.find("FUJIFILMCCD-RAW"), std::string::npos);
    // Should contain camera info
    EXPECT_NE(output.find("camera"), std::string::npos);
    EXPECT_NE(output.find("FujiTestCamera"), std::string::npos);
    // Should contain JPEG offset/length
    EXPECT_NE(output.find("JPEG offset"), std::string::npos);
    EXPECT_NE(output.find("JPEG length"), std::string::npos);
    // Should contain meta offset
    EXPECT_NE(output.find("meta offset"), std::string::npos);
    // Should contain CFA offset
    EXPECT_NE(output.find("CFA offset"), std::string::npos);
}

// Test that printStructure with kpsRecursive also works (bPrint is true)
TEST_F(RafImageTest_220, PrintStructureRecursive_ValidRaf_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    EXPECT_NO_THROW(img->printStructure(oss, kpsRecursive, 0));

    std::string output = oss.str();
    EXPECT_NE(output.find("STRUCTURE OF RAF FILE"), std::string::npos);
}

// Test that printStructure with kpsNone does not print anything (bPrint is false)
TEST_F(RafImageTest_220, PrintStructureNone_NoPrint_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    // kpsNone should not trigger the print path
    // The function might still throw if the file isn't valid RAF, but it shouldn't print
    EXPECT_NO_THROW(img->printStructure(oss, kpsNone, 0));

    std::string output = oss.str();
    EXPECT_EQ(output.find("STRUCTURE OF RAF FILE"), std::string::npos);
}

// Test that printStructure on non-RAF data throws an error
TEST_F(RafImageTest_220, PrintStructure_NonRafData_Throws_220) {
    std::vector<byte> invalidData(512, 0x00);
    auto img = createRafImageFromData(invalidData);

    std::ostringstream oss;
    EXPECT_THROW(img->printStructure(oss, kpsBasic, 0), Error);
}

// Test that printStructure on empty data throws an error
TEST_F(RafImageTest_220, PrintStructure_EmptyData_Throws_220) {
    std::vector<byte> emptyData;
    auto io = std::make_unique<MemIo>();
    auto img = std::make_unique<RafImage>(std::move(io), false);

    std::ostringstream oss;
    EXPECT_THROW(img->printStructure(oss, kpsBasic, 0), Error);
}

// Test with data too short (only magic, nothing else)
TEST_F(RafImageTest_220, PrintStructure_TruncatedAfterMagic_Throws_220) {
    // Only 16 bytes of magic, then nothing
    const char* magic = "FUJIFILMCCD-RAW ";
    std::vector<byte> shortData(reinterpret_cast<const byte*>(magic),
                                 reinterpret_cast<const byte*>(magic) + 16);
    auto img = createRafImageFromData(shortData);

    std::ostringstream oss;
    EXPECT_THROW(img->printStructure(oss, kpsBasic, 0), Error);
}

// Test mimeType returns the expected RAF MIME type
TEST_F(RafImageTest_220, MimeType_ReturnsRafMime_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::string mime = img->mimeType();
    EXPECT_EQ(mime, "image/x-fuji-raf");
}

// Test that setExifData does not throw (it's essentially a no-op for RAF)
TEST_F(RafImageTest_220, SetExifData_NoThrow_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    ExifData exifData;
    EXPECT_NO_THROW(img->setExifData(exifData));
}

// Test that setIptcData does not throw (it's essentially a no-op for RAF)
TEST_F(RafImageTest_220, SetIptcData_NoThrow_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    IptcData iptcData;
    EXPECT_NO_THROW(img->setIptcData(iptcData));
}

// Test that setComment does not throw (it's essentially a no-op for RAF)
TEST_F(RafImageTest_220, SetComment_NoThrow_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    EXPECT_NO_THROW(img->setComment("test comment"));
}

// Test printStructure with depth > 0 (indentation)
TEST_F(RafImageTest_220, PrintStructure_WithDepth_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    EXPECT_NO_THROW(img->printStructure(oss, kpsBasic, 1));

    std::string output = oss.str();
    // The output should still contain the structure info, just indented
    EXPECT_NE(output.find("STRUCTURE OF RAF FILE"), std::string::npos);
}

// Test that kpsXMP option does not trigger RAF structure printing
TEST_F(RafImageTest_220, PrintStructure_XmpOption_NoPrint_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    EXPECT_NO_THROW(img->printStructure(oss, kpsXMP, 0));

    std::string output = oss.str();
    // XMP option should not trigger RAF structure print
    EXPECT_EQ(output.find("STRUCTURE OF RAF FILE"), std::string::npos);
}

// Test that kpsIccProfile option does not trigger RAF structure printing
TEST_F(RafImageTest_220, PrintStructure_IccProfileOption_NoPrint_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    EXPECT_NO_THROW(img->printStructure(oss, kpsIccProfile, 0));

    std::string output = oss.str();
    EXPECT_EQ(output.find("STRUCTURE OF RAF FILE"), std::string::npos);
}

// Test with second meta/CFA blocks present
TEST_F(RafImageTest_220, PrintStructure_WithSecondMetaAndCfa_220) {
    auto data = buildMinimalRafFile();

    auto writeU32BE = [&](size_t offset, uint32_t val) {
        data[offset + 0] = static_cast<byte>((val >> 24) & 0xFF);
        data[offset + 1] = static_cast<byte>((val >> 16) & 0xFF);
        data[offset + 2] = static_cast<byte>((val >> 8) & 0xFF);
        data[offset + 3] = static_cast<byte>(val & 0xFF);
    };

    // Set meta_off[1] and meta_len[1] to valid values
    // Need to ensure there's enough data in the buffer
    // Place meta2 at offset 320, cfa2 at offset 384
    // Extend data if needed
    data.resize(2048, 0);

    writeU32BE(120, 320);   // meta_off[1]
    writeU32BE(124, 32);    // meta_len[1]
    writeU32BE(128, 384);   // cfa_off[1]
    writeU32BE(132, 32);    // cfa_len[1]

    // Write data at those offsets
    std::memcpy(data.data() + 320, "META_DATA_BLOCK2", 16);
    std::memcpy(data.data() + 384, "CFA__DATA_BLOCK2", 16);

    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    EXPECT_NO_THROW(img->printStructure(oss, kpsBasic, 0));

    std::string output = oss.str();
    EXPECT_NE(output.find("meta data2"), std::string::npos);
    EXPECT_NE(output.find("CFA data2"), std::string::npos);
}

// Test output contains Address and Length headers
TEST_F(RafImageTest_220, PrintStructure_ContainsHeaders_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    img->printStructure(oss, kpsBasic, 0);

    std::string output = oss.str();
    EXPECT_NE(output.find("Address"), std::string::npos);
    EXPECT_NE(output.find("Length"), std::string::npos);
    EXPECT_NE(output.find("Payload"), std::string::npos);
}

// Test output contains version field
TEST_F(RafImageTest_220, PrintStructure_ContainsVersion_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    img->printStructure(oss, kpsBasic, 0);

    std::string output = oss.str();
    EXPECT_NE(output.find("version"), std::string::npos);
}

// Test output contains data1 and data2 fields
TEST_F(RafImageTest_220, PrintStructure_ContainsDataFields_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    img->printStructure(oss, kpsBasic, 0);

    std::string output = oss.str();
    EXPECT_NE(output.find("data1"), std::string::npos);
    EXPECT_NE(output.find("data2"), std::string::npos);
}

// Test output contains compression fields
TEST_F(RafImageTest_220, PrintStructure_ContainsCompression_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    img->printStructure(oss, kpsBasic, 0);

    std::string output = oss.str();
    EXPECT_NE(output.find("compression"), std::string::npos);
}

// Test with wrong magic but correct length - should throw kerNotAnImage
TEST_F(RafImageTest_220, PrintStructure_WrongMagic_Throws_220) {
    auto data = buildMinimalRafFile();
    // Corrupt the magic
    std::memcpy(data.data(), "NOT_A_RAF_FILE!!", 16);

    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    EXPECT_THROW(img->printStructure(oss, kpsBasic, 0), Error);
}

// Test that JPEG data section is printed
TEST_F(RafImageTest_220, PrintStructure_ContainsJpegData_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    img->printStructure(oss, kpsBasic, 0);

    std::string output = oss.str();
    EXPECT_NE(output.find("JPEG data"), std::string::npos);
}

// Test that meta data1 section is printed
TEST_F(RafImageTest_220, PrintStructure_ContainsMetaData1_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    img->printStructure(oss, kpsBasic, 0);

    std::string output = oss.str();
    EXPECT_NE(output.find("meta data1"), std::string::npos);
}

// Test that CFA data1 section is printed
TEST_F(RafImageTest_220, PrintStructure_ContainsCfaData1_220) {
    auto data = buildMinimalRafFile();
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    img->printStructure(oss, kpsBasic, 0);

    std::string output = oss.str();
    EXPECT_NE(output.find("CFA data1"), std::string::npos);
}

// Test that when meta_off[1]==0 and meta_len[1]==0, meta data2 is not printed
TEST_F(RafImageTest_220, PrintStructure_NoMetaData2WhenZero_220) {
    auto data = buildMinimalRafFile();
    // meta_off[1] and meta_len[1] are already 0 in buildMinimalRafFile
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    img->printStructure(oss, kpsBasic, 0);

    std::string output = oss.str();
    EXPECT_EQ(output.find("meta data2"), std::string::npos);
}

// Test that when cfa_off[1]==0 and cfa_len[1]==0, CFA data2 is not printed
TEST_F(RafImageTest_220, PrintStructure_NoCfaData2WhenZero_220) {
    auto data = buildMinimalRafFile();
    // cfa_off[1] and cfa_len[1] are already 0 in buildMinimalRafFile
    auto img = createRafImageFromData(data);

    std::ostringstream oss;
    img->printStructure(oss, kpsBasic, 0);

    std::string output = oss.str();
    EXPECT_EQ(output.find("CFA data2"), std::string::npos);
}

// Test constructing with create=true
TEST_F(RafImageTest_220, Constructor_CreateTrue_220) {
    auto io = std::make_unique<MemIo>();
    EXPECT_NO_THROW(RafImage(std::move(io), true));
}
