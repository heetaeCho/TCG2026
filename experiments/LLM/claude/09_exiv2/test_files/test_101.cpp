#include <gtest/gtest.h>
#include <exiv2/matroskavideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper class to access protected members
class TestableMatroskaVideo : public MatroskaVideo {
public:
    TestableMatroskaVideo() : MatroskaVideo(std::make_unique<MemIo>()) {}

    void callDecodeBooleanTags(const MatroskaTag* tag, const byte* buf) {
        decodeBooleanTags(tag, buf);
    }

    XmpData& getXmpData() {
        return xmpData();
    }

    uint64_t getStream() const {
        return stream_;
    }
};

// Helper to create big-endian buffer for a uint64_t value
static void setBigEndian64(byte* buf, uint64_t value) {
    for (int i = 7; i >= 0; --i) {
        buf[i] = static_cast<byte>(value & 0xFF);
        value >>= 8;
    }
}

class MatroskaVideoBooleanTest_101 : public ::testing::Test {
protected:
    TestableMatroskaVideo video;
    byte buf[8];

    void SetUp() override {
        std::memset(buf, 0, sizeof(buf));
    }
};

// Test: key == 0 should cause early return, no xmpData changes
TEST_F(MatroskaVideoBooleanTest_101, ZeroKeyReturnsEarly_101) {
    setBigEndian64(buf, 0);
    MatroskaTag tag(TrackUsed, "Xmp.video.Enabled");
    video.callDecodeBooleanTags(&tag, buf);
    EXPECT_TRUE(video.getXmpData().empty());
}

// Test: TrackType with known key=1 should set stream_ to Video (1)
TEST_F(MatroskaVideoBooleanTest_101, TrackTypeVideo_101) {
    setBigEndian64(buf, 1); // Video
    MatroskaTag tag(TrackType, "someLabel");
    video.callDecodeBooleanTags(&tag, buf);
    // TrackType doesn't set xmpData, it sets stream_
    EXPECT_TRUE(video.getXmpData().empty());
}

// Test: TrackType with known key=2 should set stream_ to Audio (2)
TEST_F(MatroskaVideoBooleanTest_101, TrackTypeAudio_101) {
    setBigEndian64(buf, 2); // Audio
    MatroskaTag tag(TrackType, "someLabel");
    video.callDecodeBooleanTags(&tag, buf);
    EXPECT_TRUE(video.getXmpData().empty());
}

// Test: TrackType with unknown key should not crash and not set xmpData
TEST_F(MatroskaVideoBooleanTest_101, TrackTypeUnknownKey_101) {
    setBigEndian64(buf, 999);
    MatroskaTag tag(TrackType, "someLabel");
    video.callDecodeBooleanTags(&tag, buf);
    EXPECT_TRUE(video.getXmpData().empty());
}

// Test: TrackUsed with key=1 should set "Xmp.video.Enabled" = "Yes"
TEST_F(MatroskaVideoBooleanTest_101, TrackUsedVideoEnabled_101) {
    // First set stream_ to 1 (Video) via TrackType
    setBigEndian64(buf, 1);
    MatroskaTag trackTypeTag(TrackType, "");
    video.callDecodeBooleanTags(&trackTypeTag, buf);

    setBigEndian64(buf, 1); // key=1 in trackEnable -> "Xmp.video.Enabled"
    MatroskaTag tag(TrackUsed, "");
    video.callDecodeBooleanTags(&tag, buf);

    auto& xmp = video.getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.Enabled"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Yes");
}

// Test: TrackUsed with key=2 should set "Xmp.audio.Enabled" = "Yes"
TEST_F(MatroskaVideoBooleanTest_101, TrackUsedAudioEnabled_101) {
    setBigEndian64(buf, 2); // key=2 in trackEnable -> "Xmp.audio.Enabled"
    MatroskaTag tag(TrackUsed, "");
    video.callDecodeBooleanTags(&tag, buf);

    auto& xmp = video.getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.audio.Enabled"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Yes");
}

// Test: TrackUsed with key=17 should set "Xmp.video.SubTEnabled" = "Yes"
TEST_F(MatroskaVideoBooleanTest_101, TrackUsedSubtitleEnabled_101) {
    setBigEndian64(buf, 17); // key=17 in trackEnable -> "Xmp.video.SubTEnabled"
    MatroskaTag tag(TrackUsed, "");
    video.callDecodeBooleanTags(&tag, buf);

    auto& xmp = video.getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.SubTEnabled"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Yes");
}

// Test: TrackUsed with unknown key should not set xmpData
TEST_F(MatroskaVideoBooleanTest_101, TrackUsedUnknownKey_101) {
    setBigEndian64(buf, 999);
    MatroskaTag tag(TrackUsed, "");
    video.callDecodeBooleanTags(&tag, buf);
    EXPECT_TRUE(video.getXmpData().empty());
}

// Test: TrackDefault with key=1 should set "Xmp.video.DefaultOn" = "Yes"
TEST_F(MatroskaVideoBooleanTest_101, TrackDefaultVideo_101) {
    setBigEndian64(buf, 1);
    MatroskaTag tag(TrackDefault, "");
    video.callDecodeBooleanTags(&tag, buf);

    auto& xmp = video.getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.DefaultOn"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Yes");
}

// Test: TrackDefault with key=2 should set "Xmp.audio.DefaultOn" = "Yes"
TEST_F(MatroskaVideoBooleanTest_101, TrackDefaultAudio_101) {
    setBigEndian64(buf, 2);
    MatroskaTag tag(TrackDefault, "");
    video.callDecodeBooleanTags(&tag, buf);

    auto& xmp = video.getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.audio.DefaultOn"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Yes");
}

// Test: TrackForced with key=1 should set "Xmp.video.TrackForced" = "Yes"
TEST_F(MatroskaVideoBooleanTest_101, TrackForcedVideo_101) {
    setBigEndian64(buf, 1);
    MatroskaTag tag(TrackForced, "");
    video.callDecodeBooleanTags(&tag, buf);

    auto& xmp = video.getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.TrackForced"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Yes");
}

// Test: TrackLacing with key=2 should set "Xmp.audio.TrackLacing" = "Yes"
TEST_F(MatroskaVideoBooleanTest_101, TrackLacingAudio_101) {
    setBigEndian64(buf, 2);
    MatroskaTag tag(TrackLacing, "");
    video.callDecodeBooleanTags(&tag, buf);

    auto& xmp = video.getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.audio.TrackLacing"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Yes");
}

// Test: CodecDecodeAll with key=1 should set "Xmp.video.CodecDecodeAll" = "Yes"
TEST_F(MatroskaVideoBooleanTest_101, CodecDecodeAllVideo_101) {
    setBigEndian64(buf, 1);
    MatroskaTag tag(CodecDecodeAll, "");
    video.callDecodeBooleanTags(&tag, buf);

    auto& xmp = video.getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.CodecDecodeAll"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Yes");
}

// Test: CodecSettings with key=17 should set "Xmp.video.SubTCodecSettings" = "Yes"
TEST_F(MatroskaVideoBooleanTest_101, CodecSettingsSubtitle_101) {
    setBigEndian64(buf, 17);
    MatroskaTag tag(CodecSettings, "");
    video.callDecodeBooleanTags(&tag, buf);

    auto& xmp = video.getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.SubTCodecSettings"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Yes");
}

// Test: Xmp_video_TagDefault should use the tag itself as internalMt
TEST_F(MatroskaVideoBooleanTest_101, TagDefaultUsesTagLabel_101) {
    setBigEndian64(buf, 1); // any non-zero key
    MatroskaTag tag(Xmp_video_TagDefault, "Xmp.video.TagDefault");
    video.callDecodeBooleanTags(&tag, buf);

    auto& xmp = video.getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.TagDefault"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Yes");
}

// Test: Unknown tag ID should not set any xmpData
TEST_F(MatroskaVideoBooleanTest_101, UnknownTagIdNoEffect_101) {
    setBigEndian64(buf, 1);
    MatroskaTag tag(99999, "SomeLabel");
    video.callDecodeBooleanTags(&tag, buf);
    EXPECT_TRUE(video.getXmpData().empty());
}

// Test: TrackForced with key=17 should set subtitle forced
TEST_F(MatroskaVideoBooleanTest_101, TrackForcedSubtitle_101) {
    setBigEndian64(buf, 17);
    MatroskaTag tag(TrackForced, "");
    video.callDecodeBooleanTags(&tag, buf);

    auto& xmp = video.getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.SubTTrackForced"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Yes");
}

// Test: TrackLacing with unknown key should not set xmpData
TEST_F(MatroskaVideoBooleanTest_101, TrackLacingUnknownKey_101) {
    setBigEndian64(buf, 42); // not in trackLacing array
    MatroskaTag tag(TrackLacing, "");
    video.callDecodeBooleanTags(&tag, buf);
    EXPECT_TRUE(video.getXmpData().empty());
}

// Test: CodecDecodeAll with key=17 (subtitle)
TEST_F(MatroskaVideoBooleanTest_101, CodecDecodeAllSubtitle_101) {
    setBigEndian64(buf, 17);
    MatroskaTag tag(CodecDecodeAll, "");
    video.callDecodeBooleanTags(&tag, buf);

    auto& xmp = video.getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.SubTCodecDecodeAll"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Yes");
}

// Test: TrackDefault with key=17 subtitle
TEST_F(MatroskaVideoBooleanTest_101, TrackDefaultSubtitle_101) {
    setBigEndian64(buf, 17);
    MatroskaTag tag(TrackDefault, "");
    video.callDecodeBooleanTags(&tag, buf);

    auto& xmp = video.getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.SubTDefaultOn"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Yes");
}
