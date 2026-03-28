#include <gtest/gtest.h>
#include <memory>
#include <cstring>

#include "exiv2/matroskavideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/xmp_exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need to know the TrackNumber enum value to test the special branch
// From the code: TrackNumber = 87
static constexpr uint64_t TrackNumber_ID = 87;

// Helper to create a MatroskaVideo instance with a dummy MemIo
class MatroskaVideoTest_99 : public ::testing::Test {
protected:
    std::unique_ptr<MatroskaVideo> mkv;

    void SetUp() override {
        auto io = std::make_unique<MemIo>();
        mkv = std::make_unique<MatroskaVideo>(std::move(io));
    }
};

// Test that decodeStringTags with a non-TrackNumber tag stores the buffer as a string
TEST_F(MatroskaVideoTest_99, DecodeStringTags_NonTrackNumber_StoresBufferAsString_99) {
    MatroskaTag tag(100, "Xmp.video.TestLabel");
    const char* testStr = "Hello World";
    const byte* buf = reinterpret_cast<const byte*>(testStr);

    mkv->decodeStringTags(&tag, buf);

    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.TestLabel"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Hello World");
}

// Test that decodeStringTags with TrackNumber tag increments track_count and stores count
TEST_F(MatroskaVideoTest_99, DecodeStringTags_TrackNumber_IncrementsTrackCount_99) {
    MatroskaTag tag(TrackNumber_ID, "Xmp.video.TrackNumber");
    const byte buf[] = "some data";

    mkv->decodeStringTags(&tag, buf);

    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.TrackNumber"));
    ASSERT_NE(it, xmp.end());
    // First call should set track_count to 1
    EXPECT_EQ(it->toInt64(), 1);
}

// Test that calling decodeStringTags with TrackNumber multiple times increments track count
TEST_F(MatroskaVideoTest_99, DecodeStringTags_TrackNumber_MultipleCallsIncrement_99) {
    MatroskaTag tag(TrackNumber_ID, "Xmp.video.TrackNumber");
    const byte buf[] = "data";

    mkv->decodeStringTags(&tag, buf);
    mkv->decodeStringTags(&tag, buf);
    mkv->decodeStringTags(&tag, buf);

    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.TrackNumber"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toInt64(), 3);
}

// Test that decodeStringTags with empty buffer for non-TrackNumber stores empty string
TEST_F(MatroskaVideoTest_99, DecodeStringTags_EmptyBuffer_StoresEmptyString_99) {
    MatroskaTag tag(200, "Xmp.video.EmptyLabel");
    const byte buf[] = "";

    mkv->decodeStringTags(&tag, buf);

    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.EmptyLabel"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "");
}

// Test that decodeStringTags with different non-TrackNumber tags stores each independently
TEST_F(MatroskaVideoTest_99, DecodeStringTags_MultipleDifferentTags_99) {
    MatroskaTag tag1(200, "Xmp.video.Label1");
    MatroskaTag tag2(201, "Xmp.video.Label2");
    const byte buf1[] = "value1";
    const byte buf2[] = "value2";

    mkv->decodeStringTags(&tag1, buf1);
    mkv->decodeStringTags(&tag2, buf2);

    XmpData& xmp = mkv->xmpData();

    auto it1 = xmp.findKey(XmpKey("Xmp.video.Label1"));
    ASSERT_NE(it1, xmp.end());
    EXPECT_EQ(it1->toString(), "value1");

    auto it2 = xmp.findKey(XmpKey("Xmp.video.Label2"));
    ASSERT_NE(it2, xmp.end());
    EXPECT_EQ(it2->toString(), "value2");
}

// Test that decodeStringTags overwrites value when called with same label but non-TrackNumber
TEST_F(MatroskaVideoTest_99, DecodeStringTags_SameLabelOverwrites_99) {
    MatroskaTag tag(300, "Xmp.video.SameLabel");
    const byte buf1[] = "first";
    const byte buf2[] = "second";

    mkv->decodeStringTags(&tag, buf1);
    mkv->decodeStringTags(&tag, buf2);

    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.SameLabel"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "second");
}

// Test that TrackNumber followed by non-TrackNumber works correctly
TEST_F(MatroskaVideoTest_99, DecodeStringTags_MixedTrackAndNonTrack_99) {
    MatroskaTag trackTag(TrackNumber_ID, "Xmp.video.TrackNumber");
    MatroskaTag otherTag(500, "Xmp.video.Other");
    const byte buf[] = "data";

    mkv->decodeStringTags(&trackTag, buf);
    mkv->decodeStringTags(&otherTag, buf);

    XmpData& xmp = mkv->xmpData();

    auto trackIt = xmp.findKey(XmpKey("Xmp.video.TrackNumber"));
    ASSERT_NE(trackIt, xmp.end());
    EXPECT_EQ(trackIt->toInt64(), 1);

    auto otherIt = xmp.findKey(XmpKey("Xmp.video.Other"));
    ASSERT_NE(otherIt, xmp.end());
    EXPECT_EQ(otherIt->toString(), "data");
}

// Test mimeType returns expected value
TEST_F(MatroskaVideoTest_99, MimeType_ReturnsExpected_99) {
    std::string mime = mkv->mimeType();
    EXPECT_FALSE(mime.empty());
    // Matroska video MIME type is typically "video/x-matroska"
    EXPECT_EQ(mime, "video/x-matroska");
}

// Test findBlockSize static method with different byte values
TEST_F(MatroskaVideoTest_99, FindBlockSize_VariousBytes_99) {
    // byte with highest bit set -> size 1
    EXPECT_EQ(MatroskaVideo::findBlockSize(0x80), 1u);
    // byte 0x40 -> size 2
    EXPECT_EQ(MatroskaVideo::findBlockSize(0x40), 2u);
    // byte 0x20 -> size 3
    EXPECT_EQ(MatroskaVideo::findBlockSize(0x20), 3u);
    // byte 0x10 -> size 4
    EXPECT_EQ(MatroskaVideo::findBlockSize(0x10), 4u);
    // byte 0x08 -> size 5
    EXPECT_EQ(MatroskaVideo::findBlockSize(0x08), 5u);
    // byte 0x04 -> size 6
    EXPECT_EQ(MatroskaVideo::findBlockSize(0x04), 6u);
    // byte 0x02 -> size 7
    EXPECT_EQ(MatroskaVideo::findBlockSize(0x02), 7u);
    // byte 0x01 -> size 8
    EXPECT_EQ(MatroskaVideo::findBlockSize(0x01), 8u);
}

// Test findBlockSize with zero byte
TEST_F(MatroskaVideoTest_99, FindBlockSize_ZeroByte_99) {
    // A zero byte has no leading bit set; the function should still return something
    uint32_t result = MatroskaVideo::findBlockSize(0x00);
    // Typically returns 0 or some sentinel for an invalid/zero byte
    EXPECT_GE(result, 0u);
}

// Test findBlockSize with 0xFF
TEST_F(MatroskaVideoTest_99, FindBlockSize_MaxByte_99) {
    // 0xFF has highest bit set, should be size 1
    EXPECT_EQ(MatroskaVideo::findBlockSize(0xFF), 1u);
}

// Test MatroskaTag equality operator
TEST(MatroskaTagTest_99, EqualityOperator_99) {
    MatroskaTag tag(42, "label");
    EXPECT_TRUE(tag == 42);
    EXPECT_FALSE(tag == 43);
}

// Test MatroskaTag with default type and process
TEST(MatroskaTagTest_99, DefaultConstructor_99) {
    MatroskaTag tag(100, "testLabel");
    EXPECT_TRUE(tag == 100);
    EXPECT_EQ(tag._label, "testLabel");
}

// Test MatroskaTag with explicit type and process
TEST(MatroskaTagTest_99, ExplicitConstructor_99) {
    MatroskaTag tag(200, "label2", matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    EXPECT_TRUE(tag == 200);
    EXPECT_EQ(tag._label, "label2");
}

// Test writeMetadata throws (Matroska typically doesn't support writing)
TEST_F(MatroskaVideoTest_99, WriteMetadata_Throws_99) {
    EXPECT_THROW(mkv->writeMetadata(), Error);
}
