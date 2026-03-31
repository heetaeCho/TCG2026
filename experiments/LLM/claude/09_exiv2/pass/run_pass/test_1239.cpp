#include <gtest/gtest.h>
#include <string>
#include "pngchunk_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class PngChunkTest_1239 : public ::testing::Test {
protected:
    // Helper to check if a string is non-empty
    bool isNonEmpty(const std::string& s) {
        return !s.empty();
    }
};

// Test that mdComment produces a non-empty chunk
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Comment_ReturnsNonEmpty_1239) {
    std::string metadata = "This is a test comment";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdComment);
    EXPECT_FALSE(result.empty());
}

// Test that mdIptc produces a non-empty chunk
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Iptc_ReturnsNonEmpty_1239) {
    std::string metadata = "Some IPTC data";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdIptc);
    EXPECT_FALSE(result.empty());
}

// Test that mdXmp produces a non-empty chunk
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Xmp_ReturnsNonEmpty_1239) {
    std::string metadata = "<x:xmpmeta>test</x:xmpmeta>";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdXmp);
    EXPECT_FALSE(result.empty());
}

// Test that mdExif returns empty string
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Exif_ReturnsEmpty_1239) {
    std::string metadata = "Some Exif data";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdExif);
    EXPECT_TRUE(result.empty());
}

// Test that mdIccProfile returns empty string
TEST_F(PngChunkTest_1239, MakeMetadataChunk_IccProfile_ReturnsEmpty_1239) {
    std::string metadata = "Some ICC profile data";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdIccProfile);
    EXPECT_TRUE(result.empty());
}

// Test that mdNone returns empty string
TEST_F(PngChunkTest_1239, MakeMetadataChunk_None_ReturnsEmpty_1239) {
    std::string metadata = "Some data";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdNone);
    EXPECT_TRUE(result.empty());
}

// Test that mdComment with empty metadata still produces output
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Comment_EmptyMetadata_1239) {
    std::string metadata = "";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdComment);
    // Even with empty metadata, the chunk structure should exist
    // The function wraps it in a UTF-8 text chunk with keyword "Description"
    EXPECT_FALSE(result.empty());
}

// Test that mdIptc with empty metadata still produces output
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Iptc_EmptyMetadata_1239) {
    std::string metadata = "";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdIptc);
    // Even empty IPTC data gets wrapped in raw profile + ASCII text chunk
    EXPECT_FALSE(result.empty());
}

// Test that mdXmp with empty metadata still produces output
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Xmp_EmptyMetadata_1239) {
    std::string metadata = "";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdXmp);
    // XMP chunk with empty data should still have chunk structure
    EXPECT_FALSE(result.empty());
}

// Test that mdComment chunk contains the keyword "Description" somewhere
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Comment_ContainsDescriptionKeyword_1239) {
    std::string metadata = "A comment for testing";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdComment);
    EXPECT_NE(result.find("Description"), std::string::npos);
}

// Test that mdXmp chunk contains the keyword "XML:com.adobe.xmp" somewhere
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Xmp_ContainsXmpKeyword_1239) {
    std::string metadata = "<x:xmpmeta>xmp content</x:xmpmeta>";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdXmp);
    EXPECT_NE(result.find("XML:com.adobe.xmp"), std::string::npos);
}

// Test that mdIptc chunk contains the keyword related to iptc raw profile
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Iptc_ContainsIptcKeyword_1239) {
    std::string metadata = "IPTC binary data here";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdIptc);
    EXPECT_NE(result.find("Raw profile type iptc"), std::string::npos);
}

// Test with large metadata for mdComment
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Comment_LargeMetadata_1239) {
    std::string metadata(10000, 'A');
    std::string result = PngChunk::makeMetadataChunk(metadata, mdComment);
    EXPECT_FALSE(result.empty());
}

// Test with large metadata for mdIptc
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Iptc_LargeMetadata_1239) {
    std::string metadata(10000, '\xAB');
    std::string result = PngChunk::makeMetadataChunk(metadata, mdIptc);
    EXPECT_FALSE(result.empty());
}

// Test with large metadata for mdXmp
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Xmp_LargeMetadata_1239) {
    std::string metadata(10000, 'X');
    std::string result = PngChunk::makeMetadataChunk(metadata, mdXmp);
    EXPECT_FALSE(result.empty());
}

// Test that different metadata types produce different outputs for same input
TEST_F(PngChunkTest_1239, MakeMetadataChunk_DifferentTypes_ProduceDifferentResults_1239) {
    std::string metadata = "test data";
    std::string commentResult = PngChunk::makeMetadataChunk(metadata, mdComment);
    std::string iptcResult = PngChunk::makeMetadataChunk(metadata, mdIptc);
    std::string xmpResult = PngChunk::makeMetadataChunk(metadata, mdXmp);

    EXPECT_NE(commentResult, iptcResult);
    EXPECT_NE(commentResult, xmpResult);
    EXPECT_NE(iptcResult, xmpResult);
}

// Test with metadata containing null bytes
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Comment_MetadataWithNullBytes_1239) {
    std::string metadata("Hello\0World", 11);
    std::string result = PngChunk::makeMetadataChunk(metadata, mdComment);
    EXPECT_FALSE(result.empty());
}

// Test with metadata containing special characters
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Comment_SpecialCharacters_1239) {
    std::string metadata = "Ünïcödé tëxt with spëcîal çhàráctérs";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdComment);
    EXPECT_FALSE(result.empty());
}

// Test with single character metadata
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Comment_SingleChar_1239) {
    std::string metadata = "A";
    std::string result = PngChunk::makeMetadataChunk(metadata, mdComment);
    EXPECT_FALSE(result.empty());
}

// Test with binary-like data for IPTC
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Iptc_BinaryData_1239) {
    std::string metadata;
    for (int i = 0; i < 256; ++i) {
        metadata += static_cast<char>(i);
    }
    std::string result = PngChunk::makeMetadataChunk(metadata, mdIptc);
    EXPECT_FALSE(result.empty());
}

// Test consistency: same input produces same output
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Comment_Deterministic_1239) {
    std::string metadata = "Deterministic test";
    std::string result1 = PngChunk::makeMetadataChunk(metadata, mdComment);
    std::string result2 = PngChunk::makeMetadataChunk(metadata, mdComment);
    EXPECT_EQ(result1, result2);
}

TEST_F(PngChunkTest_1239, MakeMetadataChunk_Iptc_Deterministic_1239) {
    std::string metadata = "Deterministic IPTC test";
    std::string result1 = PngChunk::makeMetadataChunk(metadata, mdIptc);
    std::string result2 = PngChunk::makeMetadataChunk(metadata, mdIptc);
    EXPECT_EQ(result1, result2);
}

TEST_F(PngChunkTest_1239, MakeMetadataChunk_Xmp_Deterministic_1239) {
    std::string metadata = "Deterministic XMP test";
    std::string result1 = PngChunk::makeMetadataChunk(metadata, mdXmp);
    std::string result2 = PngChunk::makeMetadataChunk(metadata, mdXmp);
    EXPECT_EQ(result1, result2);
}
