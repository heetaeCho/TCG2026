// -----------------------------------------------------------------------------
// TEST_ID 1565
// Unit tests for Exiv2::AsfVideo::extendedStreamProperties()
// File: ./TestProjects/exiv2/src/asfvideo.cpp
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/memio.hpp>
#include <exiv2/xmp_exiv2.hpp>

namespace {

using Exiv2::AsfVideo;
using Exiv2::BasicIo;
using Exiv2::XmpData;

// Expose protected method for testing (black-box via public wrapper).
class TestableAsfVideo_1565 : public AsfVideo {
 public:
  explicit TestableAsfVideo_1565(std::unique_ptr<BasicIo> io) : AsfVideo(std::move(io)) {}
  void CallExtendedStreamProperties() { extendedStreamProperties(); }
};

// Helpers to build little-endian buffers for BasicIo-backed parsing.
// (We are NOT re-implementing AsfVideo logic; only preparing deterministic I/O input.)
static void AppendLE16(std::vector<Exiv2::byte>& out, uint16_t v) {
  out.push_back(static_cast<Exiv2::byte>(v & 0xFF));
  out.push_back(static_cast<Exiv2::byte>((v >> 8) & 0xFF));
}
static void AppendLE64(std::vector<Exiv2::byte>& out, uint64_t v) {
  for (int i = 0; i < 8; ++i) {
    out.push_back(static_cast<Exiv2::byte>((v >> (8 * i)) & 0xFF));
  }
}
static void AppendZeros(std::vector<Exiv2::byte>& out, size_t n) {
  out.insert(out.end(), n, static_cast<Exiv2::byte>(0));
}

static const Exiv2::Xmpdatum* FindXmpDatumByKey(const XmpData& xd, const std::string& key) {
  for (auto it = xd.begin(); it != xd.end(); ++it) {
    if (it->key() == key) return &(*it);
  }
  return nullptr;
}

class AsfVideoExtendedStreamPropertiesTest_1565 : public ::testing::Test {
 protected:
  static std::unique_ptr<BasicIo> MakeMemIo(const std::vector<Exiv2::byte>& bytes) {
    // MemIo holds a copy of the buffer.
    return std::unique_ptr<BasicIo>(new Exiv2::MemIo(bytes.data(), bytes.size()));
  }
};

TEST_F(AsfVideoExtendedStreamPropertiesTest_1565, SetsStartEndFrameRateAndSkipsZeroCounts_1565) {
  // Layout:
  // QWORD StartTimecode
  // WORD  EndTimecode
  // skip 8*DWORD + 2*WORD
  // WORD  FrameRate
  // WORD  stream_name_count
  // WORD  payload_ext_sys_count
  std::vector<Exiv2::byte> buf;
  const uint64_t kStart = 0x0102030405060708ULL;
  const uint16_t kEnd = 0x1122;
  const uint16_t kFrameRate = 0x0033;

  AppendLE64(buf, kStart);              // Start
  AppendLE16(buf, kEnd);                // End

  AppendZeros(buf, Exiv2::DWORD * 8);   // ignore 8 DWORD fields
  AppendZeros(buf, Exiv2::WORD * 2);    // ignore 2 WORD fields

  AppendLE16(buf, kFrameRate);          // FrameRate (Average Time Per Frame)
  AppendLE16(buf, 0);                   // stream_name_count
  AppendLE16(buf, 0);                   // payload_ext_sys_count

  TestableAsfVideo_1565 video(MakeMemIo(buf));
  ASSERT_NO_THROW(video.CallExtendedStreamProperties());

  const XmpData& xd = video.xmpData();

  const auto* start = FindXmpDatumByKey(xd, "Xmp.video.StartTimecode");
  const auto* end = FindXmpDatumByKey(xd, "Xmp.video.EndTimecode");
  const auto* fr = FindXmpDatumByKey(xd, "Xmp.video.FrameRate");

  ASSERT_NE(start, nullptr);
  ASSERT_NE(end, nullptr);
  ASSERT_NE(fr, nullptr);

  // Verify values are present and convertible to integers.
  EXPECT_EQ(start->toInt64(0), static_cast<int64_t>(kStart));
  EXPECT_EQ(end->toInt64(0), static_cast<int64_t>(kEnd));
  EXPECT_EQ(fr->toInt64(0), static_cast<int64_t>(kFrameRate));
}

TEST_F(AsfVideoExtendedStreamPropertiesTest_1565, Boundary_ZeroLengthsInLoops_DoNotConsumeExtraBytes_1565) {
  // stream_name_count=1 with stream_length=0
  // payload_ext_sys_count=1 with ext_sys_info_length=0
  std::vector<Exiv2::byte> buf;

  AppendLE64(buf, 1);                   // Start
  AppendLE16(buf, 2);                   // End

  AppendZeros(buf, Exiv2::DWORD * 8);   // ignore 8 DWORD
  AppendZeros(buf, Exiv2::WORD * 2);    // ignore 2 WORD

  AppendLE16(buf, 3);                   // FrameRate
  AppendLE16(buf, 1);                   // stream_name_count
  AppendLE16(buf, 1);                   // payload_ext_sys_count

  // stream name entry:
  AppendZeros(buf, Exiv2::WORD);        // ignore Language ID Index (seek +WORD)
  AppendLE16(buf, 0);                   // stream_length=0 (no seek)

  // payload ext system entry:
  AppendZeros(buf, Exiv2::GUID);        // ignore Extension System ID (seek +GUID)
  AppendZeros(buf, Exiv2::WORD);        // ignore Extension Data Size (seek +WORD)
  AppendLE16(buf, 0);                   // ext_sys_info_length=0 (no seek)

  auto io = MakeMemIo(buf);
  auto* ioRaw = io.get();               // for tell() after execution
  TestableAsfVideo_1565 video(std::move(io));

  ASSERT_NO_THROW(video.CallExtendedStreamProperties());

  // Final position should match total bytes in our buffer when parsing consumes/seeks exactly.
  // (This checks an observable I/O effect without inspecting any private state.)
  EXPECT_EQ(ioRaw->tell(), buf.size());
}

TEST_F(AsfVideoExtendedStreamPropertiesTest_1565, Normal_NonZeroLengths_AreSkippedAndPositionAdvances_1565) {
  // stream_name_count=2: lengths 3 and 1
  // payload_ext_sys_count=1: ext_sys_info_length=5
  std::vector<Exiv2::byte> buf;

  AppendLE64(buf, 10);                  // Start
  AppendLE16(buf, 20);                  // End

  AppendZeros(buf, Exiv2::DWORD * 8);
  AppendZeros(buf, Exiv2::WORD * 2);

  AppendLE16(buf, 30);                  // FrameRate
  AppendLE16(buf, 2);                   // stream_name_count
  AppendLE16(buf, 1);                   // payload_ext_sys_count

  // stream name entry #1:
  AppendZeros(buf, Exiv2::WORD);        // ignore Language ID Index
  AppendLE16(buf, 3);                   // stream_length=3
  AppendZeros(buf, 3);                  // stream name bytes

  // stream name entry #2:
  AppendZeros(buf, Exiv2::WORD);
  AppendLE16(buf, 1);
  AppendZeros(buf, 1);

  // payload ext system entry #1:
  AppendZeros(buf, Exiv2::GUID);
  AppendZeros(buf, Exiv2::WORD);
  AppendLE16(buf, 5);                   // ext_sys_info_length=5
  AppendZeros(buf, 5);

  auto io = MakeMemIo(buf);
  auto* ioRaw = io.get();
  TestableAsfVideo_1565 video(std::move(io));

  ASSERT_NO_THROW(video.CallExtendedStreamProperties());
  EXPECT_EQ(ioRaw->tell(), buf.size());

  // Also ensure the main XMP fields are still set.
  const XmpData& xd = video.xmpData();
  EXPECT_NE(FindXmpDatumByKey(xd, "Xmp.video.StartTimecode"), nullptr);
  EXPECT_NE(FindXmpDatumByKey(xd, "Xmp.video.EndTimecode"), nullptr);
  EXPECT_NE(FindXmpDatumByKey(xd, "Xmp.video.FrameRate"), nullptr);
}

TEST_F(AsfVideoExtendedStreamPropertiesTest_1565, Error_InsufficientData_Throws_1565) {
  // Not enough bytes even for StartTimecode QWORD.
  std::vector<Exiv2::byte> buf;
  AppendZeros(buf, 3);

  TestableAsfVideo_1565 video(MakeMemIo(buf));
  EXPECT_ANY_THROW(video.CallExtendedStreamProperties());
}

}  // namespace