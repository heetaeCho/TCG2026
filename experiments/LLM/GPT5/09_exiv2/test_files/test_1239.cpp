#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <string_view>
#include "pngchunk_int.hpp"  // Assuming this includes the PngChunk definition
#include "types.hpp"         // Assuming this includes the MetadataId enum

namespace Exiv2 {
namespace Internal {

// Mocking dependencies (if needed)
class MockImage : public Image {
    // Mock methods for Image, if necessary
};

}  // namespace Internal
}  // namespace Exiv2

using ::testing::Eq;

// Test for normal operation of makeMetadataChunk with mdComment
TEST_F(PngChunkTest_1239, MakeMetadataChunk_Comment_1239) {
    Exiv2::Internal::PngChunk pngChunk;
    std::string metadata = "This is a comment";
    Exiv2::MetadataId type = Exiv2::mdComment;

    std::string result = pngChunk.makeMetadataChunk(metadata, type);

    // Assuming makeUtf8TxtChunk is expected to be called for mdComment
    std::string expected = "DescriptionThis is a comment";
    EXPECT_EQ(result, expected);
}

// Test for normal operation of makeMetadataChunk with mdIptc
TEST_F(PngChunkTest_1240, MakeMetadataChunk_Iptc_1240) {
    Exiv2::Internal::PngChunk pngChunk;
    std::string metadata = "This is IPTC data";
    Exiv2::MetadataId type = Exiv2::mdIptc;

    std::string result = pngChunk.makeMetadataChunk(metadata, type);

    // Assuming writeRawProfile and makeAsciiTxtChunk are involved
    std::string expected = "Raw profile type iptc" + std::string(2, '\0') + "This is IPTC data";  // Placeholder for the expected format
    EXPECT_EQ(result, expected);
}

// Test for normal operation of makeMetadataChunk with mdXmp
TEST_F(PngChunkTest_1241, MakeMetadataChunk_Xmp_1241) {
    Exiv2::Internal::PngChunk pngChunk;
    std::string metadata = "This is XMP data";
    Exiv2::MetadataId type = Exiv2::mdXmp;

    std::string result = pngChunk.makeMetadataChunk(metadata, type);

    // Assuming makeUtf8TxtChunk is expected to be called for mdXmp
    std::string expected = "XML:com.adobe.xmpThis is XMP data";
    EXPECT_EQ(result, expected);
}

// Test for boundary condition when metadata is empty (for all types)
TEST_F(PngChunkTest_1242, MakeMetadataChunk_EmptyMetadata_1242) {
    Exiv2::Internal::PngChunk pngChunk;
    std::string metadata = "";
    Exiv2::MetadataId type = Exiv2::mdComment;

    std::string result = pngChunk.makeMetadataChunk(metadata, type);

    std::string expected = "Description";
    EXPECT_EQ(result, expected);
}

// Test for boundary condition with invalid MetadataId (e.g., mdNone)
TEST_F(PngChunkTest_1243, MakeMetadataChunk_InvalidMetadataId_1243) {
    Exiv2::Internal::PngChunk pngChunk;
    std::string metadata = "Invalid metadata";
    Exiv2::MetadataId type = Exiv2::mdNone;

    std::string result = pngChunk.makeMetadataChunk(metadata, type);

    std::string expected = "";
    EXPECT_EQ(result, expected);
}

// Test for exceptional case: handle unexpected metadata type gracefully
TEST_F(PngChunkTest_1244, MakeMetadataChunk_UnexpectedMetadataType_1244) {
    Exiv2::Internal::PngChunk pngChunk;
    std::string metadata = "Invalid type metadata";
    Exiv2::MetadataId type = static_cast<Exiv2::MetadataId>(999);  // Assuming 999 is invalid

    std::string result = pngChunk.makeMetadataChunk(metadata, type);

    std::string expected = "";
    EXPECT_EQ(result, expected);
}

// Test for boundary condition with large metadata string
TEST_F(PngChunkTest_1245, MakeMetadataChunk_LargeMetadata_1245) {
    Exiv2::Internal::PngChunk pngChunk;
    std::string metadata(10000, 'A');  // Large string with 10,000 'A's
    Exiv2::MetadataId type = Exiv2::mdComment;

    std::string result = pngChunk.makeMetadataChunk(metadata, type);

    std::string expected = "Description" + std::string(10000, 'A');
    EXPECT_EQ(result, expected);
}