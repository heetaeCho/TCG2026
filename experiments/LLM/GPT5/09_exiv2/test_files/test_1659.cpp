// =================================================================================================
// TEST_ID: 1659
// File: test_tiffdecoder_decodeiptc_1659.cpp
// =================================================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

namespace {

using ::testing::HasSubstr;

using Exiv2::byte;

struct LogCapture1659 {
  static void Handler(int level, const char* s) {
    lastLevel() = level;
    lastMsg() = (s ? std::string(s) : std::string());
    callCount()++;
  }

  static int& lastLevel() {
    static int lvl = -1;
    return lvl;
  }
  static std::string& lastMsg() {
    static std::string msg;
    return msg;
  }
  static int& callCount() {
    static int n = 0;
    return n;
  }

  static void Reset() {
    lastLevel() = -1;
    lastMsg().clear();
    callCount() = 0;
  }
};

static std::shared_ptr<Exiv2::DataBuf> MakeBuf1659(const std::vector<byte>& bytes) {
  auto buf = std::make_shared<Exiv2::DataBuf>(bytes.size());
  if (bytes.size() > 0) {
    std::memcpy(buf->pData_, bytes.data(), bytes.size());
  }
  return buf;
}

static Exiv2::Internal::TiffEntryBase MakeEntryWithData1659(uint16_t tag,
                                                           Exiv2::IfdId group,
                                                           const std::vector<byte>& bytes) {
  // TiffType is an Exiv2 internal enum; tests should not assume semantics beyond compilation.
  Exiv2::Internal::TiffEntryBase entry(tag, group, Exiv2::Internal::ttUndefined);
  entry.setData(MakeBuf1659(bytes));
  return entry;
}

static Exiv2::Internal::TiffEntryBase MakeEntryWithoutData1659(uint16_t tag, Exiv2::IfdId group) {
  Exiv2::Internal::TiffEntryBase entry(tag, group, Exiv2::Internal::ttUndefined);
  // Intentionally do not call setData() -> leave entry without storage/pData.
  return entry;
}

class TiffDecoderDecodeIptcTest_1659 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure a known log level/handler state for each test.
    LogCapture1659::Reset();
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    Exiv2::LogMsg::setHandler(nullptr);
  }

  void TearDown() override {
    // Restore default handler to avoid cross-test interference.
    Exiv2::LogMsg::setHandler(nullptr);
  }

  Exiv2::ExifData exif_;
  Exiv2::IptcData iptc_;
  Exiv2::XmpData xmp_;
};

// A tiny (commonly valid) IPTC dataset: 0x1c 0x02 0x05 len=3 "abc"
static std::vector<byte> MinimalValidIptcBlock1659() {
  return std::vector<byte>{
      0x1c, 0x02, 0x05, 0x00, 0x03, 'a', 'b', 'c',
  };
}

}  // namespace

TEST_F(TiffDecoderDecodeIptcTest_1659, NoRelevantDataDoesNotPopulateIptc_1659) {
  Exiv2::Internal::FindDecoderFct findDecoder;  // default / empty
  Exiv2::Internal::TiffDecoder decoder(exif_, iptc_, xmp_, /*pRoot=*/nullptr, findDecoder);

  // Tag/group not relevant to IPTC paths used by decodeIptc (0x83bb / 0x8649 in ifd0).
  auto entry = MakeEntryWithoutData1659(/*tag=*/0x0100, Exiv2::IfdId::ifd0Id);

  EXPECT_TRUE(iptc_.empty());
  decoder.decodeIptc(&entry);
  EXPECT_TRUE(iptc_.empty());
}

TEST_F(TiffDecoderDecodeIptcTest_1659, IptcIn83bbPopulatesIptcData_1659) {
  Exiv2::Internal::FindDecoderFct findDecoder;  // default / empty
  Exiv2::Internal::TiffDecoder decoder(exif_, iptc_, xmp_, /*pRoot=*/nullptr, findDecoder);

  auto entry = MakeEntryWithData1659(/*tag=*/0x83bb, Exiv2::IfdId::ifd0Id, MinimalValidIptcBlock1659());

  EXPECT_TRUE(iptc_.empty());
  decoder.decodeIptc(&entry);

  // Observable behavior through public IptcData container.
  EXPECT_FALSE(iptc_.empty());
}

TEST_F(TiffDecoderDecodeIptcTest_1659, FirstCallMarksDecoded_PreventsLaterDecoding_1659) {
  Exiv2::Internal::FindDecoderFct findDecoder;  // default / empty
  Exiv2::Internal::TiffDecoder decoder(exif_, iptc_, xmp_, /*pRoot=*/nullptr, findDecoder);

  // 1) First call with no relevant data: should still "complete" decoding pass and mark decoded.
  auto nonIptcEntry = MakeEntryWithoutData1659(/*tag=*/0x0100, Exiv2::IfdId::ifd0Id);
  decoder.decodeIptc(&nonIptcEntry);
  EXPECT_TRUE(iptc_.empty());

  // 2) Second call with valid IPTC data: should not decode again if the decoded flag is honored.
  auto iptcEntry = MakeEntryWithData1659(/*tag=*/0x83bb, Exiv2::IfdId::ifd0Id, MinimalValidIptcBlock1659());
  decoder.decodeIptc(&iptcEntry);

  // If decodeIptc is a one-shot operation, iptc_ remains unchanged (empty).
  EXPECT_TRUE(iptc_.empty());
}

TEST_F(TiffDecoderDecodeIptcTest_1659, InvalidIptcIn83bbEmitsWarningAndDoesNotPopulate_1659) {
#ifndef SUPPRESS_WARNINGS
  Exiv2::Internal::FindDecoderFct findDecoder;  // default / empty
  Exiv2::Internal::TiffDecoder decoder(exif_, iptc_, xmp_, /*pRoot=*/nullptr, findDecoder);

  // Capture warnings.
  LogCapture1659::Reset();
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
  Exiv2::LogMsg::setHandler(&LogCapture1659::Handler);

  // Provide clearly invalid / too-short IPTC-like data.
  const std::vector<byte> invalidIptc{0x1c, 0x02, 0x05, 0x00};
  auto entry = MakeEntryWithData1659(/*tag=*/0x83bb, Exiv2::IfdId::ifd0Id, invalidIptc);

  EXPECT_TRUE(iptc_.empty());
  decoder.decodeIptc(&entry);

  EXPECT_TRUE(iptc_.empty());
  EXPECT_GE(LogCapture1659::callCount(), 1);
  // Message content is observable through log handler callback.
  EXPECT_THAT(LogCapture1659::lastMsg(), HasSubstr("0x83bb"));
#else
  GTEST_SKIP() << "Warnings are suppressed (SUPPRESS_WARNINGS defined).";
#endif
}

TEST_F(TiffDecoderDecodeIptcTest_1659, Photoshop8649LocateFailureReturnsWithoutWarning_1659) {
#ifndef SUPPRESS_WARNINGS
  Exiv2::Internal::FindDecoderFct findDecoder;  // default / empty
  Exiv2::Internal::TiffDecoder decoder(exif_, iptc_, xmp_, /*pRoot=*/nullptr, findDecoder);

  // Capture warnings: this path should early-return on locate failure without warning.
  LogCapture1659::Reset();
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
  Exiv2::LogMsg::setHandler(&LogCapture1659::Handler);

  // Provide some bytes that are unlikely to be a valid Photoshop IRB block.
  const std::vector<byte> notAnIrb{0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
  auto entry = MakeEntryWithData1659(/*tag=*/0x8649, Exiv2::IfdId::ifd0Id, notAnIrb);

  EXPECT_TRUE(iptc_.empty());
  decoder.decodeIptc(&entry);

  EXPECT_TRUE(iptc_.empty());
  EXPECT_EQ(LogCapture1659::callCount(), 0) << "Expected no warning when Photoshop::locateIptcIrb fails.";
#else
  GTEST_SKIP() << "Warnings are suppressed (SUPPRESS_WARNINGS defined).";
#endif
}