#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pngchunk_int.hpp"



using namespace Exiv2::Internal;



class PngChunkTest : public ::testing::Test {

protected:

    PngChunk chunk;

};



TEST_F(PngChunkTest_1239, MakeMetadataChunk_Comment_ReturnsUtf8TxtChunk_1239) {

    std::string_view metadata = "This is a comment.";

    MetadataId type = mdComment;

    EXPECT_EQ(chunk.makeMetadataChunk(metadata, type), chunk.makeUtf8TxtChunk("Description", metadata, true));

}



TEST_F(PngChunkTest_1239, MakeMetadataChunk_Iptc_ReturnsAsciiTxtChunkWithRawProfile_1239) {

    std::string_view metadata = "IPTC Data";

    MetadataId type = mdIptc;

    std::string expected = chunk.makeAsciiTxtChunk("Raw profile type iptc", chunk.writeRawProfile(metadata, "iptc"), true);

    EXPECT_EQ(chunk.makeMetadataChunk(metadata, type), expected);

}



TEST_F(PngChunkTest_1239, MakeMetadataChunk_Xmp_ReturnsUtf8TxtChunkWithXmpKey_1239) {

    std::string_view metadata = "<x:xmpmeta></x:xmpmeta>";

    MetadataId type = mdXmp;

    EXPECT_EQ(chunk.makeMetadataChunk(metadata, type), chunk.makeUtf8TxtChunk("XML:com.adobe.xmp", metadata, false));

}



TEST_F(PngChunkTest_1239, MakeMetadataChunk_Exif_ReturnsEmptyString_1239) {

    std::string_view metadata = "Exif Data";

    MetadataId type = mdExif;

    EXPECT_EQ(chunk.makeMetadataChunk(metadata, type), "");

}



TEST_F(PngChunkTest_1239, MakeMetadataChunk_IccProfile_ReturnsEmptyString_1239) {

    std::string_view metadata = "ICC Profile Data";

    MetadataId type = mdIccProfile;

    EXPECT_EQ(chunk.makeMetadataChunk(metadata, type), "");

}



TEST_F(PngChunkTest_1239, MakeMetadataChunk_None_ReturnsEmptyString_1239) {

    std::string_view metadata = "None Data";

    MetadataId type = mdNone;

    EXPECT_EQ(chunk.makeMetadataChunk(metadata, type), "");

}



TEST_F(PngChunkTest_1239, MakeMetadataChunk_EmptyMetadata_ReturnsEmptyString_1239) {

    std::string_view metadata = "";

    MetadataId type = mdComment;

    EXPECT_EQ(chunk.makeMetadataChunk(metadata, type), "");

}



TEST_F(PngChunkTest_1239, MakeMetadataChunk_DefaultCase_ReturnsEmptyString_1239) {

    std::string_view metadata = "Default Data";

    MetadataId type = static_cast<MetadataId>(42); // Invalid case

    EXPECT_EQ(chunk.makeMetadataChunk(metadata, type), "");

}
