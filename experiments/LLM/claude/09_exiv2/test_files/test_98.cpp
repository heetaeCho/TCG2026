#include <gtest/gtest.h>
#include <memory>
#include <cstring>

#include "exiv2/matroskavideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a MatroskaVideo instance with a dummy IO
class MatroskaVideoTest_98 : public ::testing::Test {
protected:
    std::unique_ptr<MatroskaVideo> mkv;

    void SetUp() override {
        auto io = std::make_unique<MemIo>();
        mkv = std::make_unique<MatroskaVideo>(std::move(io));
    }

    // Helper to encode a uint64_t value as big-endian bytes
    void encodeUInt64BE(byte* buf, uint64_t value) {
        for (int i = 7; i >= 0; --i) {
            buf[i] = static_cast<byte>(value & 0xFF);
            value >>= 8;
        }
    }
};

// Test: VideoScanType with Progressive (key=0 should return early, key=1 for Interlaced)
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_VideoScanType_Interlaced_98) {
    MatroskaTag tag(Xmp_video_VideoScanTpye, "Xmp.video.VideoScanType",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 1); // Interlaced
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.VideoScanType"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Interlaced");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_VideoScanType_Progressive_98) {
    MatroskaTag tag(Xmp_video_VideoScanTpye, "Xmp.video.VideoScanType",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    // Progressive has key=0 but getULongLong returns 0 which causes early return
    // So we should not find the tag set
    byte buf[8];
    encodeUInt64BE(buf, 0);
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.VideoScanType"));
    EXPECT_EQ(it, xmp.end());
}

// Test: AudioChannels with known values
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_AudioChannels_Mono_98) {
    MatroskaTag tag(Xmp_audio_ChannelType, "Xmp.audio.ChannelType",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 1); // Mono
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.audio.ChannelType"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Mono");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_AudioChannels_Stereo_98) {
    MatroskaTag tag(Xmp_audio_ChannelType, "Xmp.audio.ChannelType",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 2); // Stereo
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.audio.ChannelType"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Stereo");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_AudioChannels_Surround51_98) {
    MatroskaTag tag(Xmp_audio_ChannelType, "Xmp.audio.ChannelType",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 5); // 5.1 Surround Sound
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.audio.ChannelType"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "5.1 Surround Sound");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_AudioChannels_Surround71_98) {
    MatroskaTag tag(Xmp_audio_ChannelType, "Xmp.audio.ChannelType",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 7); // 7.1 Surround Sound
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.audio.ChannelType"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "7.1 Surround Sound");
}

// Test: AudioChannels with unknown key - should store numeric value
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_AudioChannels_Unknown_98) {
    MatroskaTag tag(Xmp_audio_ChannelType, "Xmp.audio.ChannelType",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 99); // Unknown channel count
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.audio.ChannelType"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "99");
}

// Test: Compression Algorithm
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_CompressionAlgo_Zlib_98) {
    MatroskaTag tag(Xmp_video_ContentCompressAlgo, "Xmp.video.ContentCompressAlgo",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    // Note: key=0 causes early return. So we can't test zlib (key=0) this way.
    // Test key=1 (bzlib) instead
    byte buf[8];
    encodeUInt64BE(buf, 1); // bzlib
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentCompressAlgo"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "bzlib");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_CompressionAlgo_Lzo_98) {
    MatroskaTag tag(Xmp_video_ContentCompressAlgo, "Xmp.video.ContentCompressAlgo",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 2); // lzo1x
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentCompressAlgo"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "lzo1x");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_CompressionAlgo_HeaderStripping_98) {
    MatroskaTag tag(Xmp_video_ContentCompressAlgo, "Xmp.video.ContentCompressAlgo",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 3); // Header Stripping
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentCompressAlgo"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Header Stripping");
}

// Test: Encryption Algorithm
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_EncryptionAlgo_DES_98) {
    MatroskaTag tag(Xmp_video_ContentEncryptAlgo, "Xmp.video.ContentEncryptAlgo",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 1); // DES
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentEncryptAlgo"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "DES");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_EncryptionAlgo_AES_98) {
    MatroskaTag tag(Xmp_video_ContentEncryptAlgo, "Xmp.video.ContentEncryptAlgo",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 5); // AES
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentEncryptAlgo"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "AES");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_EncryptionAlgo_Unknown_98) {
    MatroskaTag tag(Xmp_video_ContentEncryptAlgo, "Xmp.video.ContentEncryptAlgo",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 42); // Unknown
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentEncryptAlgo"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "42");
}

// Test: Content Signature Algorithm (both _1 and _2 variants)
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_ContentSignAlgo1_RSA_98) {
    MatroskaTag tag(Xmp_video_ContentSignAlgo_1, "Xmp.video.ContentSignAlgo",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 1); // RSA
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentSignAlgo"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "RSA");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_ContentSignAlgo2_RSA_98) {
    MatroskaTag tag(Xmp_video_ContentSignAlgo_2, "Xmp.video.ContentSignAlgo2",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 1); // RSA
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentSignAlgo2"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "RSA");
}

// Test: Content Signature Hash Algorithm
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_ContentSignHashAlgo1_SHA1_98) {
    MatroskaTag tag(Xmp_video_ContentSignHashAlgo_1, "Xmp.video.ContentSignHashAlgo",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 1); // SHA1-160
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentSignHashAlgo"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "SHA1-160");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_ContentSignHashAlgo2_MD5_98) {
    MatroskaTag tag(Xmp_video_ContentSignHashAlgo_2, "Xmp.video.ContentSignHashAlgo2",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 2); // MD5
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentSignHashAlgo2"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "MD5");
}

// Test: Encoding Type
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_EncodingType_Encryption_98) {
    MatroskaTag tag(Xmp_video_ContentEncodingType, "Xmp.video.ContentEncodingType",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 1); // Encryption
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentEncodingType"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Encryption");
}

// Test: Display Unit
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_DisplayUnit_Cm_98) {
    MatroskaTag tag(Xmp_video_DisplayUnit, "Xmp.video.DisplayUnit",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 1); // cm
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.DisplayUnit"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "cm");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_DisplayUnit_Inches_98) {
    MatroskaTag tag(Xmp_video_DisplayUnit, "Xmp.video.DisplayUnit",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 2); // inches
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.DisplayUnit"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "inches");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_DisplayUnit_AspectRatio_98) {
    MatroskaTag tag(Xmp_video_DisplayUnit, "Xmp.video.DisplayUnit",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 3); // display aspect ratio
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.DisplayUnit"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "display aspect ratio");
}

// Test: Aspect Ratio Type
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_AspectRatioType_KeepAspect_98) {
    MatroskaTag tag(Xmp_video_AspectRatioType, "Xmp.video.AspectRatioType",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 1); // Keep Aspect Ratio
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.AspectRatioType"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Keep Aspect Ratio");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_AspectRatioType_Fixed_98) {
    MatroskaTag tag(Xmp_video_AspectRatioType, "Xmp.video.AspectRatioType",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 2); // Fixed
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.AspectRatioType"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Fixed");
}

// Test: Chapter Physical Equivalent
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_PhysicalEquivalent_Track_98) {
    MatroskaTag tag(Xmp_video_PhysicalEquivalent, "Xmp.video.PhysicalEquivalent",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 20); // Track
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.PhysicalEquivalent"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Track");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_PhysicalEquivalent_CD_98) {
    MatroskaTag tag(Xmp_video_PhysicalEquivalent, "Xmp.video.PhysicalEquivalent",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 60); // CD / DVD
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.PhysicalEquivalent"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "CD / DVD");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_PhysicalEquivalent_SetPackage_98) {
    MatroskaTag tag(Xmp_video_PhysicalEquivalent, "Xmp.video.PhysicalEquivalent",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 70); // Set / Package
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.PhysicalEquivalent"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Set / Package");
}

// Test: Translate Codec
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_TranslateCodec_DVDMenu_98) {
    MatroskaTag tag(Xmp_video_TranslateCodec, "Xmp.video.TranslateCodec",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 1); // DVD Menu
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.TranslateCodec"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "DVD Menu");
}

// Test: Track Codec (Video_Audio_CodecID)
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_TrackCodec_Video_98) {
    MatroskaTag tag(Video_Audio_CodecID, "Xmp.video.Codec",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 1); // Xmp.video.Codec
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.Codec"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Xmp.video.Codec");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_TrackCodec_Audio_98) {
    MatroskaTag tag(Video_Audio_CodecID, "Xmp.audio.Compressor",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 2); // Xmp.audio.Compressor
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.audio.Compressor"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Xmp.audio.Compressor");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_TrackCodec_SubT_98) {
    MatroskaTag tag(Video_Audio_CodecID, "Xmp.video.SubTCodec",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 17); // Xmp.video.SubTCodec
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.SubTCodec"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Xmp.video.SubTCodec");
}

// Test: Codec Name (Video_Audio_CodecName)
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_CodecInfo_Video_98) {
    MatroskaTag tag(Video_Audio_CodecName, "Xmp.video.CodecInfo",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 1); // Xmp.video.CodecInfo
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.CodecInfo"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Xmp.video.CodecInfo");
}

// Test: CodecDownloadURL
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_CodecDownloadURL_Video_98) {
    MatroskaTag tag(CodecDownloadURL, "Xmp.video.CodecDownloadUrl",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 1); // Xmp.video.CodecDownloadUrl
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.CodecDownloadUrl"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Xmp.video.CodecDownloadUrl");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_CodecInfoURL_Audio_98) {
    MatroskaTag tag(CodecInfoURL, "Xmp.audio.CodecDownloadUrl",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 2); // Xmp.audio.CodecDownloadUrl
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.audio.CodecDownloadUrl"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Xmp.audio.CodecDownloadUrl");
}

// Test: Key is zero - should return early without setting xmpData
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_ZeroKey_NoEffect_98) {
    MatroskaTag tag(Xmp_video_DisplayUnit, "Xmp.video.DisplayUnit",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 0); // Zero key
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.DisplayUnit"));
    EXPECT_EQ(it, xmp.end());
}

// Test: Unknown tag ID - internalMt lambda returns nullptr, stores numeric key
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_UnknownTagId_StoresNumeric_98) {
    // Use an ID that doesn't match any case in the switch
    MatroskaTag tag(999999, "Xmp.video.SomeUnknown",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 42);
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.SomeUnknown"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "42");
}

// Test: Internal table lookup fails - stores numeric value
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_DisplayUnit_UnknownValue_StoresNumeric_98) {
    MatroskaTag tag(Xmp_video_DisplayUnit, "Xmp.video.DisplayUnit",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 999); // No such display unit
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.DisplayUnit"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "999");
}

// Test: Encryption algorithm with various known keys
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_EncryptionAlgo_3DES_98) {
    MatroskaTag tag(Xmp_video_ContentEncryptAlgo, "Xmp.video.ContentEncryptAlgo",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 2); // 3DES
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentEncryptAlgo"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "3DES");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_EncryptionAlgo_Twofish_98) {
    MatroskaTag tag(Xmp_video_ContentEncryptAlgo, "Xmp.video.ContentEncryptAlgo",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 3); // Twofish
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentEncryptAlgo"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Twofish");
}

TEST_F(MatroskaVideoTest_98, DecodeInternalTags_EncryptionAlgo_Blowfish_98) {
    MatroskaTag tag(Xmp_video_ContentEncryptAlgo, "Xmp.video.ContentEncryptAlgo",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 4); // Blowfish
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentEncryptAlgo"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Blowfish");
}

// Test: Physical equivalent with Index (key=10)
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_PhysicalEquivalent_Index_98) {
    MatroskaTag tag(Xmp_video_PhysicalEquivalent, "Xmp.video.PhysicalEquivalent",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 10); // Index
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.PhysicalEquivalent"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Index");
}

// Test: Physical equivalent unknown value
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_PhysicalEquivalent_Unknown_98) {
    MatroskaTag tag(Xmp_video_PhysicalEquivalent, "Xmp.video.PhysicalEquivalent",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 99); // Unknown
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.PhysicalEquivalent"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "99");
}

// Test: MimeType
TEST_F(MatroskaVideoTest_98, MimeType_98) {
    EXPECT_EQ(mkv->mimeType(), "video/x-matroska");
}

// Test: findBlockSize
TEST_F(MatroskaVideoTest_98, FindBlockSize_HighBit_98) {
    // When the high bit is set, block size should be 1
    uint32_t result = MatroskaVideo::findBlockSize(0x80);
    EXPECT_EQ(result, 1u);
}

TEST_F(MatroskaVideoTest_98, FindBlockSize_SecondBit_98) {
    uint32_t result = MatroskaVideo::findBlockSize(0x40);
    EXPECT_EQ(result, 2u);
}

TEST_F(MatroskaVideoTest_98, FindBlockSize_ThirdBit_98) {
    uint32_t result = MatroskaVideo::findBlockSize(0x20);
    EXPECT_EQ(result, 3u);
}

TEST_F(MatroskaVideoTest_98, FindBlockSize_FourthBit_98) {
    uint32_t result = MatroskaVideo::findBlockSize(0x10);
    EXPECT_EQ(result, 4u);
}

TEST_F(MatroskaVideoTest_98, FindBlockSize_ZeroByte_98) {
    // No bits set - should return max or a specific value
    uint32_t result = MatroskaVideo::findBlockSize(0x00);
    // Based on EBML VINT encoding, 0 means all 8 bits checked, returns some value
    EXPECT_GE(result, 1u);
}

TEST_F(MatroskaVideoTest_98, FindBlockSize_AllBitsSet_98) {
    uint32_t result = MatroskaVideo::findBlockSize(0xFF);
    EXPECT_EQ(result, 1u);
}

// Test: Overwriting same key with different values
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_OverwritesSameLabel_98) {
    MatroskaTag tag(Xmp_video_DisplayUnit, "Xmp.video.DisplayUnit",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];

    // First call with cm
    encodeUInt64BE(buf, 1);
    mkv->decodeInternalTags(&tag, buf);

    // Second call with inches
    encodeUInt64BE(buf, 2);
    mkv->decodeInternalTags(&tag, buf);

    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.DisplayUnit"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "inches");
}

// Test: Large key value that doesn't match any lookup table entry
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_LargeKey_StoresNumeric_98) {
    MatroskaTag tag(Xmp_video_ContentEncodingType, "Xmp.video.ContentEncodingType",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 0xFFFFFFFF);
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentEncodingType"));
    ASSERT_NE(it, xmp.end());
    // Should store the numeric value since lookup fails
    EXPECT_EQ(it->toString(), std::to_string(0xFFFFFFFF));
}

// Test: Aspect ratio type unknown value
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_AspectRatioType_Unknown_98) {
    MatroskaTag tag(Xmp_video_AspectRatioType, "Xmp.video.AspectRatioType",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 100);
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.AspectRatioType"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "100");
}

// Test: Codec download URL with SubT (key=17)
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_CodecDownloadURL_SubT_98) {
    MatroskaTag tag(CodecDownloadURL, "Xmp.video.SubTCodecDownloadUrl",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 17);
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.SubTCodecDownloadUrl"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "Xmp.video.SubTCodecDownloadUrl");
}

// Test: Content signature hash algorithm unknown value
TEST_F(MatroskaVideoTest_98, DecodeInternalTags_ContentSignHashAlgo_Unknown_98) {
    MatroskaTag tag(Xmp_video_ContentSignHashAlgo_1, "Xmp.video.ContentSignHashAlgo",
                    matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    byte buf[8];
    encodeUInt64BE(buf, 50);
    mkv->decodeInternalTags(&tag, buf);
    XmpData& xmp = mkv->xmpData();
    auto it = xmp.findKey(XmpKey("Xmp.video.ContentSignHashAlgo"));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(it->toString(), "50");
}
