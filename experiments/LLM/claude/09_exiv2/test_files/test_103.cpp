#include <gtest/gtest.h>
#include <exiv2/matroskavideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <cmath>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper class to access protected members
class TestableMatroskaVideo : public MatroskaVideo {
public:
    TestableMatroskaVideo() : MatroskaVideo(std::make_unique<MemIo>()) {}

    void callDecodeFloatTags(const MatroskaTag* tag, const byte* buf) {
        decodeFloatTags(tag, buf);
    }

    XmpData& getXmpData() {
        return xmpData();
    }

    void setStream(uint64_t s) {
        // We need to set stream_ which is private. Since we can't directly,
        // we'll work around this limitation.
        // stream_ is a member of MatroskaVideo at a known offset
        // Actually, let's use a different approach - access through the class layout
        // This is fragile but necessary for testing protected methods
        auto* base = reinterpret_cast<byte*>(this);
        // We need to find stream_ offset - it's declared after other members
        // Let's try using a derived class trick
    }

    // Expose stream_ for testing - we need to set it
    // stream_ is protected/private in MatroskaVideo
    // We'll use pointer arithmetic or a helper
    uint64_t& streamRef() {
        // stream_ is the last uint64_t member
        return *reinterpret_cast<uint64_t*>(
            reinterpret_cast<char*>(this) + offsetof(TestableMatroskaVideo, stream_hack_));
    }

    // Alternative: just make a version that works
    uint64_t stream_hack_ = 0; // This won't work directly

    void setStreamValue(uint64_t val);
};

// Since stream_ is private, we use a compilation trick
#define private public
#define protected public
#include <exiv2/matroskavideo.hpp>
#undef private
#undef protected

class MatroskaVideoDecodeFloatTest_103 : public ::testing::Test {
protected:
    std::unique_ptr<MatroskaVideo> video_;

    void SetUp() override {
        video_ = std::make_unique<MatroskaVideo>(std::make_unique<MemIo>());
    }

    // Helper to create big-endian float bytes
    void floatToBigEndianBytes(float val, byte* buf) {
        uint32_t raw;
        std::memcpy(&raw, &val, sizeof(float));
        buf[0] = (raw >> 24) & 0xFF;
        buf[1] = (raw >> 16) & 0xFF;
        buf[2] = (raw >> 8) & 0xFF;
        buf[3] = raw & 0xFF;
    }

    // Helper to create big-endian uint64 bytes
    void uint64ToBigEndianBytes(uint64_t val, byte* buf) {
        for (int i = 7; i >= 0; --i) {
            buf[7 - i] = (val >> (i * 8)) & 0xFF;
        }
    }
};

TEST_F(MatroskaVideoDecodeFloatTest_103, DefaultTagSetsFloat_103) {
    MatroskaTag tag(999, "Xmp.video.TestLabel", matroskaTypeEnum::Float, matroskaProcessEnum::Undefined);
    byte buf[4];
    floatToBigEndianBytes(3.14f, buf);

    video_->decodeFloatTags(&tag, buf);

    auto& xmp = video_->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.TestLabel"));
    ASSERT_NE(it, xmp.end());
}

TEST_F(MatroskaVideoDecodeFloatTest_103, SampleRateTag_103) {
    MatroskaTag tag(Xmp_audio_SampleRate, "Xmp.audio.SampleRate", matroskaTypeEnum::Float, matroskaProcessEnum::Undefined);
    byte buf[4];
    floatToBigEndianBytes(44100.0f, buf);

    video_->decodeFloatTags(&tag, buf);

    auto& xmp = video_->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.audio.SampleRate"));
    ASSERT_NE(it, xmp.end());
}

TEST_F(MatroskaVideoDecodeFloatTest_103, OutputSampleRateTag_103) {
    MatroskaTag tag(Xmp_audio_OutputSampleRate, "Xmp.audio.OutputSampleRate", matroskaTypeEnum::Float, matroskaProcessEnum::Undefined);
    byte buf[4];
    floatToBigEndianBytes(48000.0f, buf);

    video_->decodeFloatTags(&tag, buf);

    auto& xmp = video_->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.audio.OutputSampleRate"));
    ASSERT_NE(it, xmp.end());
}

TEST_F(MatroskaVideoDecodeFloatTest_103, FrameRateZeroKeyReturnsEarly_103) {
    MatroskaTag tag(Xmp_video_FrameRate, "Xmp.video.FrameRate", matroskaTypeEnum::Float, matroskaProcessEnum::Undefined);
    byte buf[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // zero key

    video_->decodeFloatTags(&tag, buf);

    // With zero key, the function returns early after setting the initial float
    auto& xmp = video_->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.FrameRate"));
    ASSERT_NE(it, xmp.end());
}

TEST_F(MatroskaVideoDecodeFloatTest_103, MimeTypeIsCorrect_103) {
    EXPECT_EQ(video_->mimeType(), "video/matroska");
}
#include <gtest/gtest.h>
#include <exiv2/matroskavideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

class MatroskaVideoTest_103 : public ::testing::Test {
protected:
    void SetUp() override {
        video_ = std::make_unique<MatroskaVideo>(std::make_unique<MemIo>());
    }

    std::unique_ptr<MatroskaVideo> video_;
};

TEST_F(MatroskaVideoTest_103, MimeType_103) {
    EXPECT_EQ(video_->mimeType(), "video/matroska");
}

TEST_F(MatroskaVideoTest_103, WriteMetadataThrows_103) {
    EXPECT_THROW(video_->writeMetadata(), Error);
}

TEST_F(MatroskaVideoTest_103, XmpDataInitiallyEmpty_103) {
    EXPECT_TRUE(video_->xmpData().empty());
}

TEST_F(MatroskaVideoTest_103, FindBlockSizeForZero_103) {
    EXPECT_EQ(MatroskaVideo::findBlockSize(0), 1u);
}

TEST_F(MatroskaVideoTest_103, FindBlockSizeFor0x80_103) {
    EXPECT_EQ(MatroskaVideo::findBlockSize(0x80), 1u);
}

TEST_F(MatroskaVideoTest_103, FindBlockSizeFor0x40_103) {
    EXPECT_EQ(MatroskaVideo::findBlockSize(0x40), 2u);
}

TEST_F(MatroskaVideoTest_103, FindBlockSizeFor0x20_103) {
    EXPECT_EQ(MatroskaVideo::findBlockSize(0x20), 3u);
}

TEST_F(MatroskaVideoTest_103, FindBlockSizeFor0x10_103) {
    EXPECT_EQ(MatroskaVideo::findBlockSize(0x10), 4u);
}

TEST_F(MatroskaVideoTest_103, FindBlockSizeFor0x01_103) {
    EXPECT_EQ(MatroskaVideo::findBlockSize(0x01), 8u);
}
