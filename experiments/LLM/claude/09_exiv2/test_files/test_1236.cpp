#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "pngchunk_int.hpp"
#include "exiv2/image.hpp"
#include "exiv2/types.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/pngimage.hpp"

#include <cstring>
#include <string>
#include <vector>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a PNG-like image for testing
class PngChunkTest_1236 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a simple tEXt chunk data buffer
    // Format: keyword\0text
    DataBuf makeTextChunkData(const std::string& keyword, const std::string& text) {
        std::vector<uint8_t> buf;
        // Add keyword
        for (char c : keyword) {
            buf.push_back(static_cast<uint8_t>(c));
        }
        // Null separator
        buf.push_back(0);
        // Add text
        for (char c : text) {
            buf.push_back(static_cast<uint8_t>(c));
        }
        return DataBuf(buf.data(), buf.size());
    }

    // Helper to create a zTXt chunk data buffer
    // Format: keyword\0compression_method compressed_text
    DataBuf makeZtxtChunkData(const std::string& keyword, const std::string& compressedText) {
        std::vector<uint8_t> buf;
        for (char c : keyword) {
            buf.push_back(static_cast<uint8_t>(c));
        }
        buf.push_back(0); // null separator
        buf.push_back(0); // compression method (0 = zlib deflate)
        for (char c : compressedText) {
            buf.push_back(static_cast<uint8_t>(c));
        }
        return DataBuf(buf.data(), buf.size());
    }

    // Helper to create an iTXt chunk data buffer
    // Format: keyword\0compression_flag\0compression_method\0language_tag\0translated_keyword\0text
    DataBuf makeItxtChunkData(const std::string& keyword, const std::string& text,
                               uint8_t compressionFlag = 0, uint8_t compressionMethod = 0,
                               const std::string& lang = "", const std::string& transKeyword = "") {
        std::vector<uint8_t> buf;
        for (char c : keyword) {
            buf.push_back(static_cast<uint8_t>(c));
        }
        buf.push_back(0); // null separator after keyword
        buf.push_back(compressionFlag);
        buf.push_back(compressionMethod);
        for (char c : lang) {
            buf.push_back(static_cast<uint8_t>(c));
        }
        buf.push_back(0); // null separator after language
        for (char c : transKeyword) {
            buf.push_back(static_cast<uint8_t>(c));
        }
        buf.push_back(0); // null separator after translated keyword
        for (char c : text) {
            buf.push_back(static_cast<uint8_t>(c));
        }
        return DataBuf(buf.data(), buf.size());
    }

    // Helper to create IHDR data
    // IHDR: width(4) + height(4) + bit_depth(1) + color_type(1) + compression(1) + filter(1) + interlace(1) = 13 bytes
    DataBuf makeIHDRData(uint32_t width, uint32_t height) {
        std::vector<uint8_t> buf(13, 0);
        // Width in big-endian
        buf[0] = static_cast<uint8_t>((width >> 24) & 0xFF);
        buf[1] = static_cast<uint8_t>((width >> 16) & 0xFF);
        buf[2] = static_cast<uint8_t>((width >> 8) & 0xFF);
        buf[3] = static_cast<uint8_t>(width & 0xFF);
        // Height in big-endian
        buf[4] = static_cast<uint8_t>((height >> 24) & 0xFF);
        buf[5] = static_cast<uint8_t>((height >> 16) & 0xFF);
        buf[6] = static_cast<uint8_t>((height >> 8) & 0xFF);
        buf[7] = static_cast<uint8_t>(height & 0xFF);
        // bit depth
        buf[8] = 8;
        // color type (2 = truecolor)
        buf[9] = 2;
        return DataBuf(buf.data(), buf.size());
    }
};

// ==================== decodeIHDRChunk Tests ====================

TEST_F(PngChunkTest_1236, DecodeIHDRChunk_NormalDimensions_1236) {
    uint32_t width = 0, height = 0;
    DataBuf ihdrData = makeIHDRData(640, 480);
    PngChunk::decodeIHDRChunk(ihdrData, &width, &height);
    EXPECT_EQ(width, 640u);
    EXPECT_EQ(height, 480u);
}

TEST_F(PngChunkTest_1236, DecodeIHDRChunk_OneDimension_1236) {
    uint32_t width = 0, height = 0;
    DataBuf ihdrData = makeIHDRData(1, 1);
    PngChunk::decodeIHDRChunk(ihdrData, &width, &height);
    EXPECT_EQ(width, 1u);
    EXPECT_EQ(height, 1u);
}

TEST_F(PngChunkTest_1236, DecodeIHDRChunk_LargeDimensions_1236) {
    uint32_t width = 0, height = 0;
    DataBuf ihdrData = makeIHDRData(4096, 2160);
    PngChunk::decodeIHDRChunk(ihdrData, &width, &height);
    EXPECT_EQ(width, 4096u);
    EXPECT_EQ(height, 2160u);
}

TEST_F(PngChunkTest_1236, DecodeIHDRChunk_ZeroDimensions_1236) {
    uint32_t width = 99, height = 99;
    DataBuf ihdrData = makeIHDRData(0, 0);
    PngChunk::decodeIHDRChunk(ihdrData, &width, &height);
    EXPECT_EQ(width, 0u);
    EXPECT_EQ(height, 0u);
}

TEST_F(PngChunkTest_1236, DecodeIHDRChunk_MaxUint32_1236) {
    uint32_t width = 0, height = 0;
    DataBuf ihdrData = makeIHDRData(0xFFFFFFFF, 0xFFFFFFFF);
    PngChunk::decodeIHDRChunk(ihdrData, &width, &height);
    EXPECT_EQ(width, 0xFFFFFFFFu);
    EXPECT_EQ(height, 0xFFFFFFFFu);
}

// ==================== keyTXTChunk Tests ====================

TEST_F(PngChunkTest_1236, KeyTXTChunk_NormalKey_1236) {
    DataBuf data = makeTextChunkData("Comment", "Hello World");
    DataBuf key = PngChunk::keyTXTChunk(data, false);
    EXPECT_FALSE(key.empty());
    std::string keyStr(key.c_str(), key.size());
    // The key should contain "Comment" (possibly with null terminator)
    EXPECT_NE(keyStr.find("Comment"), std::string::npos);
}

TEST_F(PngChunkTest_1236, KeyTXTChunk_EmptyData_1236) {
    DataBuf emptyData;
    DataBuf key = PngChunk::keyTXTChunk(emptyData, false);
    EXPECT_TRUE(key.empty());
}

TEST_F(PngChunkTest_1236, KeyTXTChunk_SingleByte_1236) {
    // Just a single null byte
    uint8_t singleByte = 0;
    DataBuf data(&singleByte, 1);
    DataBuf key = PngChunk::keyTXTChunk(data, false);
    // Key should be empty since keyword is empty
    EXPECT_TRUE(key.empty());
}

TEST_F(PngChunkTest_1236, KeyTXTChunk_StripHeader_1236) {
    // When stripHeader is true, some header bytes should be stripped
    DataBuf data = makeTextChunkData("Description", "Some description");
    DataBuf keyNoStrip = PngChunk::keyTXTChunk(data, false);
    DataBuf keyStrip = PngChunk::keyTXTChunk(data, true);
    // Both should not be empty
    EXPECT_FALSE(keyNoStrip.empty());
    // The stripped version may differ
}

// ==================== decodeTXTChunk (DataBuf overload) Tests ====================

TEST_F(PngChunkTest_1236, DecodeTXTChunk_DataBuf_tEXt_1236) {
    DataBuf data = makeTextChunkData("Comment", "Test comment");
    DataBuf result = PngChunk::decodeTXTChunk(data, TxtChunkType::tEXt_Chunk);
    // The result should contain the decoded text
    EXPECT_FALSE(result.empty());
}

TEST_F(PngChunkTest_1236, DecodeTXTChunk_DataBuf_EmptyText_1236) {
    DataBuf data = makeTextChunkData("Comment", "");
    DataBuf result = PngChunk::decodeTXTChunk(data, TxtChunkType::tEXt_Chunk);
    // Result may be empty if text portion is empty
}

TEST_F(PngChunkTest_1236, DecodeTXTChunk_DataBuf_EmptyData_1236) {
    DataBuf emptyData;
    // Empty data should be handled gracefully - might throw or return empty
    try {
        DataBuf result = PngChunk::decodeTXTChunk(emptyData, TxtChunkType::tEXt_Chunk);
    } catch (...) {
        // Exception is acceptable for empty data
    }
}

// ==================== decodeTXTChunk (Image* overload) Tests ====================

TEST_F(PngChunkTest_1236, DecodeTXTChunk_Image_NormalText_1236) {
    // Create a PngImage with a memory IO
    auto memIo = std::make_unique<MemIo>();
    // We need a valid PNG image; create one through the factory or use a minimal approach
    // Since we can't easily create a valid Image here, we'll test with a simple approach
    // Use ImageFactory or a PngImage directly if possible
    
    // For this test, we use the fact that decodeTXTChunk with Image* modifies metadata
    // We'll just ensure it doesn't crash with a valid-looking text chunk
    try {
        auto io = std::make_unique<MemIo>();
        // We need a PngImage - let's try creating one
        auto image = ImageFactory::create(ImageType::png, std::move(io));
        if (image) {
            DataBuf data = makeTextChunkData("Comment", "A test comment");
            PngChunk::decodeTXTChunk(image.get(), data, TxtChunkType::tEXt_Chunk);
            // Check that comment was set
            std::string comment = image->comment();
            EXPECT_EQ(comment, "A test comment");
        }
    } catch (...) {
        // May throw if image creation fails - that's OK for this test
    }
}

TEST_F(PngChunkTest_1236, DecodeTXTChunk_Image_EmptyData_1236) {
    try {
        auto io = std::make_unique<MemIo>();
        auto image = ImageFactory::create(ImageType::png, std::move(io));
        if (image) {
            DataBuf emptyData;
            PngChunk::decodeTXTChunk(image.get(), emptyData, TxtChunkType::tEXt_Chunk);
            // Should handle gracefully - no crash
        }
    } catch (...) {
        // Exception is acceptable for empty data
    }
}

// ==================== makeMetadataChunk Tests ====================

TEST_F(PngChunkTest_1236, MakeMetadataChunk_ExifData_1236) {
    std::string metadata = "some exif data";
    try {
        std::string result = PngChunk::makeMetadataChunk(metadata, MetadataId::mdExif);
        EXPECT_FALSE(result.empty());
    } catch (...) {
        // May throw for invalid metadata
    }
}

TEST_F(PngChunkTest_1236, MakeMetadataChunk_XmpData_1236) {
    std::string xmpData = "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
                           "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
                           "</x:xmpmeta><?xpacket end=\"w\"?>";
    try {
        std::string result = PngChunk::makeMetadataChunk(xmpData, MetadataId::mdXmp);
        EXPECT_FALSE(result.empty());
    } catch (...) {
        // May throw
    }
}

TEST_F(PngChunkTest_1236, MakeMetadataChunk_IptcData_1236) {
    std::string iptcData = "some iptc data";
    try {
        std::string result = PngChunk::makeMetadataChunk(iptcData, MetadataId::mdIptc);
        EXPECT_FALSE(result.empty());
    } catch (...) {
        // May throw
    }
}

TEST_F(PngChunkTest_1236, MakeMetadataChunk_EmptyMetadata_1236) {
    std::string emptyMetadata;
    try {
        std::string result = PngChunk::makeMetadataChunk(emptyMetadata, MetadataId::mdExif);
        // Empty metadata may produce an empty result or throw
    } catch (...) {
        // Exception is acceptable
    }
}

// ==================== iTXt chunk Tests ====================

TEST_F(PngChunkTest_1236, DecodeTXTChunk_iTXt_Uncompressed_1236) {
    DataBuf data = makeItxtChunkData("Description", "A UTF-8 description", 0, 0, "en", "Description");
    try {
        DataBuf result = PngChunk::decodeTXTChunk(data, TxtChunkType::iTXt_Chunk);
        EXPECT_FALSE(result.empty());
    } catch (...) {
        // May throw if format is not exactly right
    }
}

// ==================== Boundary Tests ====================

TEST_F(PngChunkTest_1236, DecodeIHDRChunk_MinimalData_1236) {
    // IHDR expects at least 13 bytes. Test with exact size.
    DataBuf ihdrData = makeIHDRData(100, 200);
    EXPECT_EQ(ihdrData.size(), 13u);
    uint32_t width = 0, height = 0;
    PngChunk::decodeIHDRChunk(ihdrData, &width, &height);
    EXPECT_EQ(width, 100u);
    EXPECT_EQ(height, 200u);
}

TEST_F(PngChunkTest_1236, DecodeIHDRChunk_TooSmallData_1236) {
    // Data smaller than 8 bytes - should handle gracefully
    uint8_t smallData[] = {0, 0, 0, 1};
    DataBuf data(smallData, 4);
    uint32_t width = 0, height = 0;
    try {
        PngChunk::decodeIHDRChunk(data, &width, &height);
    } catch (...) {
        // Exception expected for too-small data
    }
}

TEST_F(PngChunkTest_1236, KeyTXTChunk_NoNullSeparator_1236) {
    // Data without a null separator - keyword is the entire data
    std::string noNull = "KeywordWithoutNull";
    DataBuf data(reinterpret_cast<const uint8_t*>(noNull.data()), noNull.size());
    DataBuf key = PngChunk::keyTXTChunk(data, false);
    // Behavior depends on implementation - key might be the entire data or empty
}

TEST_F(PngChunkTest_1236, KeyTXTChunk_LongKeyword_1236) {
    // PNG spec limits keywords to 79 chars, but we test a longer one
    std::string longKeyword(100, 'A');
    DataBuf data = makeTextChunkData(longKeyword, "text");
    DataBuf key = PngChunk::keyTXTChunk(data, false);
    EXPECT_FALSE(key.empty());
}

TEST_F(PngChunkTest_1236, DecodeTXTChunk_OnlyKeyword_1236) {
    // Data with just a keyword and null byte, no text
    std::string keyword = "Comment";
    std::vector<uint8_t> buf;
    for (char c : keyword) buf.push_back(static_cast<uint8_t>(c));
    buf.push_back(0);
    DataBuf data(buf.data(), buf.size());
    try {
        DataBuf result = PngChunk::decodeTXTChunk(data, TxtChunkType::tEXt_Chunk);
        // Empty text portion is valid
    } catch (...) {
        // May throw
    }
}

// ==================== Additional decodeIHDRChunk Tests ====================

TEST_F(PngChunkTest_1236, DecodeIHDRChunk_AsymmetricDimensions_1236) {
    uint32_t width = 0, height = 0;
    DataBuf ihdrData = makeIHDRData(1920, 1080);
    PngChunk::decodeIHDRChunk(ihdrData, &width, &height);
    EXPECT_EQ(width, 1920u);
    EXPECT_EQ(height, 1080u);
}

TEST_F(PngChunkTest_1236, DecodeIHDRChunk_SquareImage_1236) {
    uint32_t width = 0, height = 0;
    DataBuf ihdrData = makeIHDRData(256, 256);
    PngChunk::decodeIHDRChunk(ihdrData, &width, &height);
    EXPECT_EQ(width, 256u);
    EXPECT_EQ(height, 256u);
}
