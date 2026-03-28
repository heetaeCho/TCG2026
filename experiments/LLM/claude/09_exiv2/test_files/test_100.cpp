#include <gtest/gtest.h>
#include <exiv2/matroskavideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test helper to access protected members
class TestableMatroskaVideo : public MatroskaVideo {
public:
    explicit TestableMatroskaVideo(BasicIo::UniquePtr io)
        : MatroskaVideo(std::move(io)) {}

    using MatroskaVideo::decodeIntegerTags;

    XmpData& getXmpData() { return xmpData(); }
    uint32_t getPixelWidth() { return pixelWidth(); }
    uint32_t getPixelHeight() { return pixelHeight(); }
};

class MatroskaVideoDecodeIntegerTagsTest_100 : public ::testing::Test {
protected:
    std::unique_ptr<TestableMatroskaVideo> video_;

    void SetUp() override {
        auto io = std::make_unique<MemIo>();
        video_ = std::make_unique<TestableMatroskaVideo>(std::move(io));
    }

    // Helper to create big-endian 8-byte buffer from uint64_t
    void toBigEndian(uint64_t val, byte* buf) {
        for (int i = 7; i >= 0; --i) {
            buf[i] = static_cast<byte>(val & 0xFF);
            val >>= 8;
        }
    }
};

// Test: Value of zero causes early return, no xmpData entry
TEST_F(MatroskaVideoDecodeIntegerTagsTest_100, ZeroValueReturnsEarly_100) {
    byte buf[8] = {0};
    MatroskaTag tag(100, "Xmp.video.TestTag");

    video_->decodeIntegerTags(&tag, buf);

    auto& xmp = video_->getXmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.TestTag"));
    EXPECT_EQ(it, xmp.end());
}

// Test: Non-zero value is stored in xmpData with correct label
TEST_F(MatroskaVideoDecodeIntegerTagsTest_100, NonZeroValueStoredInXmpData_100) {
    byte buf[8];
    toBigEndian(42, buf);
    MatroskaTag tag(100, "Xmp.video.TestTag");

    video_->decodeIntegerTags(&tag, buf);

    auto& xmp = video_->getXmpData();
    EXPECT_FALSE(xmp.empty());
    EXPECT_EQ(xmp["Xmp.video.TestTag"].toInt64(), 42);
}

// Test: Width_1 tag (id=48) sets width
TEST_F(MatroskaVideoDecodeIntegerTagsTest_100, Width1TagSetsWidth_100) {
    byte buf[8];
    toBigEndian(1920, buf);
    // Xmp_video_Width_1 = 48
    MatroskaTag tag(48, "Xmp.video.Width");

    video_->decodeIntegerTags(&tag, buf);

    auto& xmp = video_->getXmpData();
    EXPECT_EQ(xmp["Xmp.video.Width"].toInt64(), 1920);
}

// Test: Width_2 tag (id=5296) sets width
TEST_F(MatroskaVideoDecodeIntegerTagsTest_100, Width2TagSetsWidth_100) {
    byte buf[8];
    toBigEndian(3840, buf);
    // Xmp_video_Width_2 = 5296
    MatroskaTag tag(5296, "Xmp.video.DisplayWidth");

    video_->decodeIntegerTags(&tag, buf);

    auto& xmp = video_->getXmpData();
    EXPECT_EQ(xmp["Xmp.video.DisplayWidth"].toInt64(), 3840);
}

// Test: Height_1 tag (id=58) sets height
TEST_F(MatroskaVideoDecodeIntegerTagsTest_100, Height1TagSetsHeight_100) {
    byte buf[8];
    toBigEndian(1080, buf);
    // Xmp_video_Height_1 = 58
    MatroskaTag tag(58, "Xmp.video.Height");

    video_->decodeIntegerTags(&tag, buf);

    auto& xmp = video_->getXmpData();
    EXPECT_EQ(xmp["Xmp.video.Height"].toInt64(), 1080);
}

// Test: Height_2 tag (id=5306) sets height
TEST_F(MatroskaVideoDecodeIntegerTagsTest_100, Height2TagSetsHeight_100) {
    byte buf[8];
    toBigEndian(2160, buf);
    // Xmp_video_Height_2 = 5306
    MatroskaTag tag(5306, "Xmp.video.DisplayHeight");

    video_->decodeIntegerTags(&tag, buf);

    auto& xmp = video_->getXmpData();
    EXPECT_EQ(xmp["Xmp.video.DisplayHeight"].toInt64(), 2160);
}

// Test: Tag with unrelated ID does not affect width or height but still stores value
TEST_F(MatroskaVideoDecodeIntegerTagsTest_100, UnrelatedTagDoesNotSetWidthOrHeight_100) {
    byte buf[8];
    toBigEndian(999, buf);
    MatroskaTag tag(12345, "Xmp.video.SomeOther");

    video_->decodeIntegerTags(&tag, buf);

    auto& xmp = video_->getXmpData();
    EXPECT_EQ(xmp["Xmp.video.SomeOther"].toInt64(), 999);
}

// Test: Value of 1 (smallest non-zero) is stored correctly
TEST_F(MatroskaVideoDecodeIntegerTagsTest_100, ValueOneIsStored_100) {
    byte buf[8];
    toBigEndian(1, buf);
    MatroskaTag tag(200, "Xmp.video.MinVal");

    video_->decodeIntegerTags(&tag, buf);

    auto& xmp = video_->getXmpData();
    EXPECT_EQ(xmp["Xmp.video.MinVal"].toInt64(), 1);
}

// Test: Large value is stored correctly
TEST_F(MatroskaVideoDecodeIntegerTagsTest_100, LargeValueIsStored_100) {
    byte buf[8];
    uint64_t largeVal = 0x00FFFFFFFFFFFFFF; // Large but fits
    toBigEndian(largeVal, buf);
    MatroskaTag tag(300, "Xmp.video.LargeVal");

    video_->decodeIntegerTags(&tag, buf);

    auto& xmp = video_->getXmpData();
    EXPECT_FALSE(xmp.empty());
}

// Test: Multiple calls accumulate xmpData entries
TEST_F(MatroskaVideoDecodeIntegerTagsTest_100, MultipleCalls_100) {
    byte buf1[8], buf2[8];
    toBigEndian(1920, buf1);
    toBigEndian(1080, buf2);

    MatroskaTag tagW(48, "Xmp.video.Width");
    MatroskaTag tagH(58, "Xmp.video.Height");

    video_->decodeIntegerTags(&tagW, buf1);
    video_->decodeIntegerTags(&tagH, buf2);

    auto& xmp = video_->getXmpData();
    EXPECT_EQ(xmp["Xmp.video.Width"].toInt64(), 1920);
    EXPECT_EQ(xmp["Xmp.video.Height"].toInt64(), 1080);
}

// Test: Calling with same tag twice overwrites the value
TEST_F(MatroskaVideoDecodeIntegerTagsTest_100, OverwritesSameTag_100) {
    byte buf1[8], buf2[8];
    toBigEndian(100, buf1);
    toBigEndian(200, buf2);

    MatroskaTag tag(48, "Xmp.video.Width");

    video_->decodeIntegerTags(&tag, buf1);
    video_->decodeIntegerTags(&tag, buf2);

    auto& xmp = video_->getXmpData();
    EXPECT_EQ(xmp["Xmp.video.Width"].toInt64(), 200);
}
