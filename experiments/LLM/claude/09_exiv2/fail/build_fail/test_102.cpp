#include <gtest/gtest.h>
#include <cstring>
#include <cmath>
#include <memory>

#include "exiv2/matroskavideo.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"
#include "exiv2/xmp_exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a MatroskaVideo instance with a dummy MemIo
class MatroskaVideoDecodeDateTagsTest_102 : public ::testing::Test {
 protected:
  std::unique_ptr<MatroskaVideo> mkv_;

  void SetUp() override {
    auto io = std::make_unique<MemIo>();
    mkv_ = std::make_unique<MatroskaVideo>(std::move(io));
  }

  // Helper: encode a float as big-endian bytes
  static void encodeFloatBE(float val, byte* buf) {
    uint32_t bits;
    std::memcpy(&bits, &val, sizeof(bits));
    buf[0] = static_cast<byte>((bits >> 24) & 0xFF);
    buf[1] = static_cast<byte>((bits >> 16) & 0xFF);
    buf[2] = static_cast<byte>((bits >> 8) & 0xFF);
    buf[3] = static_cast<byte>(bits & 0xFF);
  }

  // Helper: encode a double as big-endian bytes
  static void encodeDoubleBE(double val, byte* buf) {
    uint64_t bits;
    std::memcpy(&bits, &val, sizeof(bits));
    buf[0] = static_cast<byte>((bits >> 56) & 0xFF);
    buf[1] = static_cast<byte>((bits >> 48) & 0xFF);
    buf[2] = static_cast<byte>((bits >> 40) & 0xFF);
    buf[3] = static_cast<byte>((bits >> 32) & 0xFF);
    buf[4] = static_cast<byte>((bits >> 24) & 0xFF);
    buf[5] = static_cast<byte>((bits >> 16) & 0xFF);
    buf[6] = static_cast<byte>((bits >> 8) & 0xFF);
    buf[7] = static_cast<byte>(bits & 0xFF);
  }

  // Helper: encode a uint64_t as big-endian bytes (8 bytes)
  static void encodeUInt64BE(uint64_t val, byte* buf) {
    buf[0] = static_cast<byte>((val >> 56) & 0xFF);
    buf[1] = static_cast<byte>((val >> 48) & 0xFF);
    buf[2] = static_cast<byte>((val >> 40) & 0xFF);
    buf[3] = static_cast<byte>((val >> 32) & 0xFF);
    buf[4] = static_cast<byte>((val >> 24) & 0xFF);
    buf[5] = static_cast<byte>((val >> 16) & 0xFF);
    buf[6] = static_cast<byte>((val >> 8) & 0xFF);
    buf[7] = static_cast<byte>(val & 0xFF);
  }

  // Constants matching the enum values from the source
  static constexpr uint64_t Xmp_video_Duration_ID = 1161;
  static constexpr uint64_t Xmp_video_DateUTC_ID = 1121;
  static constexpr uint64_t TimecodeScale_ID = 710577;
};

// Test: Duration with float (size <= 4), default time_code_scale_ = 1.0
TEST_F(MatroskaVideoDecodeDateTagsTest_102, DurationFloat_DefaultScale_102) {
  MatroskaTag tag(Xmp_video_Duration_ID, "Xmp.video.Duration",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  float duration_val = 5000.0f;  // 5000 ms equivalent
  byte buf[4];
  encodeFloatBE(duration_val, buf);

  mkv_->decodeDateTags(&tag, buf, 4);

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.Duration"));
  ASSERT_NE(it, xmp.end());

  // With default time_code_scale_ = 1.0, result = round(5000.0 * 1.0 * 1000.0) = 5000000
  int64_t expected = std::llround(duration_val * 1.0 * 1000.0);
  EXPECT_EQ(it->toInt64(), expected);
}

// Test: Duration with double (size > 4), default time_code_scale_ = 1.0
TEST_F(MatroskaVideoDecodeDateTagsTest_102, DurationDouble_DefaultScale_102) {
  MatroskaTag tag(Xmp_video_Duration_ID, "Xmp.video.Duration",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  double duration_val = 12345.6789;
  byte buf[8];
  encodeDoubleBE(duration_val, buf);

  mkv_->decodeDateTags(&tag, buf, 8);

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.Duration"));
  ASSERT_NE(it, xmp.end());

  int64_t expected = std::llround(duration_val * 1.0 * 1000.0);
  EXPECT_EQ(it->toInt64(), expected);
}

// Test: TimecodeScale sets scale and stores it in xmpData
TEST_F(MatroskaVideoDecodeDateTagsTest_102, TimecodeScale_Normal_102) {
  MatroskaTag tag(TimecodeScale_ID, "Xmp.video.TimecodeScale",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  // TimecodeScale typically 1000000 (1ms)
  uint64_t scale_ns = 1000000ULL;
  byte buf[8];
  encodeUInt64BE(scale_ns, buf);

  mkv_->decodeDateTags(&tag, buf, 8);

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.TimecodeScale"));
  ASSERT_NE(it, xmp.end());

  double expected_scale = static_cast<double>(scale_ns) / 1000000000.0;
  EXPECT_NEAR(it->toFloat(), static_cast<float>(expected_scale), 1e-6);
}

// Test: TimecodeScale with value 0 should return early and not set xmpData
TEST_F(MatroskaVideoDecodeDateTagsTest_102, TimecodeScale_ZeroValue_102) {
  MatroskaTag tag(TimecodeScale_ID, "Xmp.video.TimecodeScale",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  uint64_t scale_ns = 0;
  byte buf[8];
  encodeUInt64BE(scale_ns, buf);

  mkv_->decodeDateTags(&tag, buf, 8);

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.TimecodeScale"));
  EXPECT_EQ(it, xmp.end());
}

// Test: DateUTC with a normal value
TEST_F(MatroskaVideoDecodeDateTagsTest_102, DateUTC_Normal_102) {
  MatroskaTag tag(Xmp_video_DateUTC_ID, "Xmp.video.DateUTC",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  // Value in nanoseconds since 2001-01-01
  uint64_t nanos = 5000000000ULL;  // 5 seconds in nanoseconds
  byte buf[8];
  encodeUInt64BE(nanos, buf);

  mkv_->decodeDateTags(&tag, buf, 8);

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.DateUTC"));
  ASSERT_NE(it, xmp.end());

  int64_t expected = nanos / 1000000000;
  EXPECT_EQ(it->toInt64(), expected);
}

// Test: DateUTC with zero value should return early and not set xmpData
TEST_F(MatroskaVideoDecodeDateTagsTest_102, DateUTC_ZeroValue_102) {
  MatroskaTag tag(Xmp_video_DateUTC_ID, "Xmp.video.DateUTC",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  uint64_t nanos = 0;
  byte buf[8];
  encodeUInt64BE(nanos, buf);

  mkv_->decodeDateTags(&tag, buf, 8);

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.DateUTC"));
  EXPECT_EQ(it, xmp.end());
}

// Test: Unknown tag ID should not modify xmpData
TEST_F(MatroskaVideoDecodeDateTagsTest_102, UnknownTagId_NoEffect_102) {
  MatroskaTag tag(99999, "Xmp.video.Unknown",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  byte buf[8] = {0, 0, 0, 0, 0, 0, 0, 1};

  mkv_->decodeDateTags(&tag, buf, 8);

  XmpData& xmp = mkv_->xmpData();
  EXPECT_TRUE(xmp.empty());
}

// Test: Duration with modified TimecodeScale
TEST_F(MatroskaVideoDecodeDateTagsTest_102, DurationAfterTimecodeScaleChange_102) {
  // First set TimecodeScale to 1ms (1000000 ns)
  {
    MatroskaTag scaleTag(TimecodeScale_ID, "Xmp.video.TimecodeScale",
                         matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    uint64_t scale_ns = 1000000ULL;
    byte buf[8];
    encodeUInt64BE(scale_ns, buf);
    mkv_->decodeDateTags(&scaleTag, buf, 8);
  }

  // Now decode Duration as double
  {
    MatroskaTag durTag(Xmp_video_Duration_ID, "Xmp.video.Duration",
                       matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);
    double duration_val = 10000.0;
    byte buf[8];
    encodeDoubleBE(duration_val, buf);
    mkv_->decodeDateTags(&durTag, buf, 8);
  }

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.Duration"));
  ASSERT_NE(it, xmp.end());

  double expected_scale = 1000000.0 / 1000000000.0;  // 0.001
  int64_t expected = std::llround(10000.0 * expected_scale * 1000.0);
  EXPECT_EQ(it->toInt64(), expected);
}

// Test: Duration float with size exactly 4 (boundary)
TEST_F(MatroskaVideoDecodeDateTagsTest_102, DurationFloat_SizeExactly4_102) {
  MatroskaTag tag(Xmp_video_Duration_ID, "Xmp.video.Duration",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  float val = 1.0f;
  byte buf[4];
  encodeFloatBE(val, buf);

  mkv_->decodeDateTags(&tag, buf, 4);

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.Duration"));
  ASSERT_NE(it, xmp.end());

  int64_t expected = std::llround(1.0f * 1.0 * 1000.0);
  EXPECT_EQ(it->toInt64(), expected);
}

// Test: Duration with size 3 (< 4, uses float path)
TEST_F(MatroskaVideoDecodeDateTagsTest_102, DurationFloat_SizeLessThan4_102) {
  MatroskaTag tag(Xmp_video_Duration_ID, "Xmp.video.Duration",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  float val = 2.5f;
  byte buf[4];
  encodeFloatBE(val, buf);

  // size = 3, still <= 4, so float path
  mkv_->decodeDateTags(&tag, buf, 3);

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.Duration"));
  ASSERT_NE(it, xmp.end());
}

// Test: Duration with size 5 (> 4, uses double path)
TEST_F(MatroskaVideoDecodeDateTagsTest_102, DurationDouble_Size5_102) {
  MatroskaTag tag(Xmp_video_Duration_ID, "Xmp.video.Duration",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  double val = 100.0;
  byte buf[8];
  encodeDoubleBE(val, buf);

  mkv_->decodeDateTags(&tag, buf, 5);

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.Duration"));
  ASSERT_NE(it, xmp.end());

  int64_t expected = std::llround(val * 1.0 * 1000.0);
  EXPECT_EQ(it->toInt64(), expected);
}

// Test: Duration float with zero value
TEST_F(MatroskaVideoDecodeDateTagsTest_102, DurationFloat_ZeroValue_102) {
  MatroskaTag tag(Xmp_video_Duration_ID, "Xmp.video.Duration",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  float val = 0.0f;
  byte buf[4];
  encodeFloatBE(val, buf);

  mkv_->decodeDateTags(&tag, buf, 4);

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.Duration"));
  ASSERT_NE(it, xmp.end());
  EXPECT_EQ(it->toInt64(), 0);
}

// Test: DateUTC with large value
TEST_F(MatroskaVideoDecodeDateTagsTest_102, DateUTC_LargeValue_102) {
  MatroskaTag tag(Xmp_video_DateUTC_ID, "Xmp.video.DateUTC",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  // Large value: ~20 years in nanoseconds
  uint64_t nanos = 631152000000000000ULL;
  byte buf[8];
  encodeUInt64BE(nanos, buf);

  mkv_->decodeDateTags(&tag, buf, 8);

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.DateUTC"));
  ASSERT_NE(it, xmp.end());

  int64_t expected = static_cast<int64_t>(nanos / 1000000000ULL);
  EXPECT_EQ(it->toInt64(), expected);
}

// Test: TimecodeScale with standard Matroska default (1000000000 ns = 1s)
TEST_F(MatroskaVideoDecodeDateTagsTest_102, TimecodeScale_OneSecond_102) {
  MatroskaTag tag(TimecodeScale_ID, "Xmp.video.TimecodeScale",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  uint64_t scale_ns = 1000000000ULL;  // 1 second
  byte buf[8];
  encodeUInt64BE(scale_ns, buf);

  mkv_->decodeDateTags(&tag, buf, 8);

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.TimecodeScale"));
  ASSERT_NE(it, xmp.end());

  // 1000000000 / 1000000000 = 1.0
  EXPECT_NEAR(it->toFloat(), 1.0f, 1e-6);
}

// Test: Calling decodeDateTags multiple times for Duration overwrites previous value
TEST_F(MatroskaVideoDecodeDateTagsTest_102, DurationOverwrite_102) {
  MatroskaTag tag(Xmp_video_Duration_ID, "Xmp.video.Duration",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  // First call
  {
    double val = 100.0;
    byte buf[8];
    encodeDoubleBE(val, buf);
    mkv_->decodeDateTags(&tag, buf, 8);
  }

  // Second call with different value
  {
    double val = 200.0;
    byte buf[8];
    encodeDoubleBE(val, buf);
    mkv_->decodeDateTags(&tag, buf, 8);
  }

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.Duration"));
  ASSERT_NE(it, xmp.end());

  int64_t expected = std::llround(200.0 * 1.0 * 1000.0);
  EXPECT_EQ(it->toInt64(), expected);
}

// Test: Duration with negative float value
TEST_F(MatroskaVideoDecodeDateTagsTest_102, DurationFloat_NegativeValue_102) {
  MatroskaTag tag(Xmp_video_Duration_ID, "Xmp.video.Duration",
                  matroskaTypeEnum::UndefinedType, matroskaProcessEnum::Undefined);

  float val = -5000.0f;
  byte buf[4];
  encodeFloatBE(val, buf);

  mkv_->decodeDateTags(&tag, buf, 4);

  XmpData& xmp = mkv_->xmpData();
  auto it = xmp.findKey(XmpKey("Xmp.video.Duration"));
  ASSERT_NE(it, xmp.end());

  int64_t expected = std::llround(-5000.0f * 1.0 * 1000.0);
  EXPECT_EQ(it->toInt64(), expected);
}

// Test: mimeType returns expected value
TEST_F(MatroskaVideoDecodeDateTagsTest_102, MimeType_102) {
  EXPECT_EQ(mkv_->mimeType(), "video/x-matroska");
}
