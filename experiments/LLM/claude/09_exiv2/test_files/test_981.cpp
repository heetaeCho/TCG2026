#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/mrwimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>

#include <cstring>
#include <memory>
#include <vector>

using namespace Exiv2;

// Helper to build a minimal MRW file in memory
// MRW format:
//   Bytes 0-3: 0x00 'M' 'R' 'M' (magic)
//   Bytes 4-7: offset to pixel data (big-endian uint32), also serves as end of header area
//   Then blocks of 8-byte headers + data:
//     byte 0: padding
//     bytes 1-3: 3-char tag name
//     bytes 4-7: size of data following (big-endian uint32)
//     then 'size' bytes of data
//   A TTW block contains TIFF data

static std::vector<byte> buildMrwData(bool valid = true, bool includeTTW = true,
                                       bool truncateBeforeTTW = false,
                                       bool badMagic = false,
                                       bool emptyFile = false) {
    if (emptyFile) {
        return {};
    }

    std::vector<byte> data;

    // Helper to push big-endian uint32
    auto pushU32BE = [&](uint32_t val) {
        data.push_back(static_cast<byte>((val >> 24) & 0xFF));
        data.push_back(static_cast<byte>((val >> 16) & 0xFF));
        data.push_back(static_cast<byte>((val >> 8) & 0xFF));
        data.push_back(static_cast<byte>(val & 0xFF));
    };

    // MRW magic: 0x00 'M' 'R' 'M'
    if (badMagic) {
        data.push_back(0x00);
        data.push_back('X');
        data.push_back('Y');
        data.push_back('Z');
    } else {
        data.push_back(0x00);
        data.push_back('M');
        data.push_back('R');
        data.push_back('M');
    }

    // We'll compute total header size later; placeholder
    size_t offsetPos = data.size();
    pushU32BE(0); // placeholder for end offset

    if (!includeTTW) {
        // Just set end offset to current position and stop
        uint32_t endOff = static_cast<uint32_t>(data.size());
        data[offsetPos] = static_cast<byte>((endOff >> 24) & 0xFF);
        data[offsetPos + 1] = static_cast<byte>((endOff >> 16) & 0xFF);
        data[offsetPos + 2] = static_cast<byte>((endOff >> 8) & 0xFF);
        data[offsetPos + 3] = static_cast<byte>(endOff & 0xFF);
        return data;
    }

    // Add a dummy PRD block first
    {
        data.push_back(0x00); // padding
        data.push_back('P');
        data.push_back('R');
        data.push_back('D');
        uint32_t prdSize = 4;
        pushU32BE(prdSize);
        // PRD data (dummy)
        for (uint32_t i = 0; i < prdSize; i++)
            data.push_back(0x00);
    }

    if (truncateBeforeTTW) {
        uint32_t endOff = static_cast<uint32_t>(data.size());
        data[offsetPos] = static_cast<byte>((endOff >> 24) & 0xFF);
        data[offsetPos + 1] = static_cast<byte>((endOff >> 16) & 0xFF);
        data[offsetPos + 2] = static_cast<byte>((endOff >> 8) & 0xFF);
        data[offsetPos + 3] = static_cast<byte>(endOff & 0xFF);
        return data;
    }

    // Add TTW block with minimal TIFF data
    {
        data.push_back(0x00); // padding
        data.push_back('T');
        data.push_back('T');
        data.push_back('W');

        // Build minimal TIFF data (little-endian)
        std::vector<byte> tiffData;
        // TIFF header: byte order
        tiffData.push_back('I');
        tiffData.push_back('I');
        // Magic 42
        tiffData.push_back(42);
        tiffData.push_back(0);
        // Offset to first IFD (8)
        tiffData.push_back(8);
        tiffData.push_back(0);
        tiffData.push_back(0);
        tiffData.push_back(0);
        // IFD with 0 entries
        tiffData.push_back(0);
        tiffData.push_back(0);
        // Next IFD offset = 0
        tiffData.push_back(0);
        tiffData.push_back(0);
        tiffData.push_back(0);
        tiffData.push_back(0);

        uint32_t ttwSize = static_cast<uint32_t>(tiffData.size());
        pushU32BE(ttwSize);
        data.insert(data.end(), tiffData.begin(), tiffData.end());
    }

    // Update end offset
    uint32_t endOff = static_cast<uint32_t>(data.size());
    data[offsetPos] = static_cast<byte>((endOff >> 24) & 0xFF);
    data[offsetPos + 1] = static_cast<byte>((endOff >> 16) & 0xFF);
    data[offsetPos + 2] = static_cast<byte>((endOff >> 8) & 0xFF);
    data[offsetPos + 3] = static_cast<byte>(endOff & 0xFF);

    return data;
}

class MrwImageTest_981 : public ::testing::Test {
protected:
    std::unique_ptr<MrwImage> createMrwImage(const std::vector<byte>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        return std::make_unique<MrwImage>(std::move(io), false);
    }
};

// Test that mimeType returns the correct MIME type for MRW
TEST_F(MrwImageTest_981, MimeType_981) {
    auto data = buildMrwData(true, true);
    auto img = createMrwImage(data);
    EXPECT_EQ(img->mimeType(), "image/x-minolta-mrw");
}

// Test reading metadata from a valid MRW file with TTW block
TEST_F(MrwImageTest_981, ReadMetadataValidFile_981) {
    auto data = buildMrwData(true, true);
    auto img = createMrwImage(data);
    EXPECT_NO_THROW(img->readMetadata());
}

// Test reading metadata from an empty file throws
TEST_F(MrwImageTest_981, ReadMetadataEmptyFile_981) {
    auto data = buildMrwData(true, true, false, false, true);
    auto img = createMrwImage(data);
    EXPECT_THROW(img->readMetadata(), Error);
}

// Test reading metadata from a file with bad magic throws
TEST_F(MrwImageTest_981, ReadMetadataBadMagic_981) {
    auto data = buildMrwData(true, true, false, true);
    auto img = createMrwImage(data);
    EXPECT_THROW(img->readMetadata(), Error);
}

// Test reading metadata when TTW block is missing (truncated) throws
TEST_F(MrwImageTest_981, ReadMetadataNoTTWBlock_981) {
    auto data = buildMrwData(true, false);
    auto img = createMrwImage(data);
    EXPECT_THROW(img->readMetadata(), Error);
}

// Test reading metadata from truncated file before TTW throws
TEST_F(MrwImageTest_981, ReadMetadataTruncatedBeforeTTW_981) {
    auto data = buildMrwData(true, true, true);
    auto img = createMrwImage(data);
    EXPECT_THROW(img->readMetadata(), Error);
}

// Test that setExifData does not throw (it's a no-op for MRW)
TEST_F(MrwImageTest_981, SetExifDataNoOp_981) {
    auto data = buildMrwData(true, true);
    auto img = createMrwImage(data);
    ExifData exifData;
    EXPECT_NO_THROW(img->setExifData(exifData));
}

// Test that setIptcData does not throw (it's a no-op for MRW)
TEST_F(MrwImageTest_981, SetIptcDataNoOp_981) {
    auto data = buildMrwData(true, true);
    auto img = createMrwImage(data);
    IptcData iptcData;
    EXPECT_NO_THROW(img->setIptcData(iptcData));
}

// Test that setComment does not throw (it's a no-op for MRW)
TEST_F(MrwImageTest_981, SetCommentNoOp_981) {
    auto data = buildMrwData(true, true);
    auto img = createMrwImage(data);
    EXPECT_NO_THROW(img->setComment("test comment"));
}

// Test that writeMetadata throws (MRW writing not supported)
TEST_F(MrwImageTest_981, WriteMetadataThrows_981) {
    auto data = buildMrwData(true, true);
    auto img = createMrwImage(data);
    EXPECT_THROW(img->writeMetadata(), Error);
}

// Test good() returns true for valid data
TEST_F(MrwImageTest_981, GoodReturnsTrueForValidData_981) {
    auto data = buildMrwData(true, true);
    auto img = createMrwImage(data);
    EXPECT_TRUE(img->good());
}

// Test pixelWidth and pixelHeight default to 0 before readMetadata
TEST_F(MrwImageTest_981, PixelDimensionsDefaultZero_981) {
    auto data = buildMrwData(true, true);
    auto img = createMrwImage(data);
    EXPECT_EQ(img->pixelWidth(), 0u);
    EXPECT_EQ(img->pixelHeight(), 0u);
}

// Test that after readMetadata, exifData is accessible
TEST_F(MrwImageTest_981, ExifDataAccessibleAfterRead_981) {
    auto data = buildMrwData(true, true);
    auto img = createMrwImage(data);
    img->readMetadata();
    // Should not crash; exifData may be empty for minimal TIFF
    EXPECT_NO_THROW(img->exifData());
}

// Test that after readMetadata, iptcData is accessible
TEST_F(MrwImageTest_981, IptcDataAccessibleAfterRead_981) {
    auto data = buildMrwData(true, true);
    auto img = createMrwImage(data);
    img->readMetadata();
    EXPECT_NO_THROW(img->iptcData());
}

// Test that after readMetadata, xmpData is accessible
TEST_F(MrwImageTest_981, XmpDataAccessibleAfterRead_981) {
    auto data = buildMrwData(true, true);
    auto img = createMrwImage(data);
    img->readMetadata();
    EXPECT_NO_THROW(img->xmpData());
}

// Test with a file that is just the 8-byte header but with end offset pointing beyond
TEST_F(MrwImageTest_981, ReadMetadataHeaderOnlyEndOffsetTooLarge_981) {
    std::vector<byte> data;
    data.push_back(0x00);
    data.push_back('M');
    data.push_back('R');
    data.push_back('M');
    // End offset pointing far beyond the file
    data.push_back(0x00);
    data.push_back(0x01);
    data.push_back(0x00);
    data.push_back(0x00);

    auto img = createMrwImage(data);
    EXPECT_THROW(img->readMetadata(), Error);
}

// Test with corrupted block size in a non-TTW block
TEST_F(MrwImageTest_981, ReadMetadataCorruptedBlockSize_981) {
    std::vector<byte> data;
    // Magic
    data.push_back(0x00);
    data.push_back('M');
    data.push_back('R');
    data.push_back('M');
    // End offset = 0x00000100 (256)
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x01);
    data.push_back(0x00);
    // Block header: non-TTW
    data.push_back(0x00);
    data.push_back('P');
    data.push_back('R');
    data.push_back('D');
    // Block size = very large (larger than end - pos)
    data.push_back(0xFF);
    data.push_back(0xFF);
    data.push_back(0xFF);
    data.push_back(0xFF);

    auto img = createMrwImage(data);
    EXPECT_THROW(img->readMetadata(), Error);
}

// Test reading the same image twice (re-reading metadata)
TEST_F(MrwImageTest_981, ReadMetadataTwice_981) {
    auto data = buildMrwData(true, true);
    auto img = createMrwImage(data);
    EXPECT_NO_THROW(img->readMetadata());
    EXPECT_NO_THROW(img->readMetadata());
}

// Test with only 4 bytes (too small to be MRW)
TEST_F(MrwImageTest_981, ReadMetadataTooSmallFile_981) {
    std::vector<byte> data = {0x00, 'M', 'R', 'M'};
    auto img = createMrwImage(data);
    EXPECT_THROW(img->readMetadata(), Error);
}
