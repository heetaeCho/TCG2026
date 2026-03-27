// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 784
//
// Unit tests for Exiv2::ExifParser::decode (black-box behavioral tests)

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tiffimage.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace {

class ExifParserTest_784 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Capture current global logging configuration so we can restore it.
    oldHandler_ = Exiv2::LogMsg::handler();
    oldLevel_ = Exiv2::LogMsg::level();

    ResetLogCapture();
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::debug);
    Exiv2::LogMsg::setHandler(&ExifParserTest_784::CaptureHandler);
  }

  void TearDown() override {
    // Restore global logging configuration.
    Exiv2::LogMsg::setHandler(oldHandler_);
    Exiv2::LogMsg::setLevel(oldLevel_);
    ResetLogCapture();
  }

  static std::vector<Exiv2::byte> MakeMinimalTiff(bool littleEndian) {
    // Minimal TIFF:
    // Header (8 bytes): "II*\0" or "MM\0*" + offset to IFD0 = 8
    // IFD0 at offset 8: entryCount = 0 (2 bytes), nextIFD = 0 (4 bytes)
    std::vector<Exiv2::byte> buf;
    buf.reserve(14);

    if (littleEndian) {
      buf.push_back(static_cast<Exiv2::byte>('I'));
      buf.push_back(static_cast<Exiv2::byte>('I'));
      buf.push_back(static_cast<Exiv2::byte>(0x2A));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      // 4-byte offset = 8 (little)
      buf.push_back(static_cast<Exiv2::byte>(0x08));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      // IFD0: 0 entries
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      // next IFD offset = 0
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
    } else {
      buf.push_back(static_cast<Exiv2::byte>('M'));
      buf.push_back(static_cast<Exiv2::byte>('M'));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x2A));
      // 4-byte offset = 8 (big)
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x08));
      // IFD0: 0 entries
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      // next IFD offset = 0
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
      buf.push_back(static_cast<Exiv2::byte>(0x00));
    }

    return buf;
  }

  struct DecodeOutcome {
    bool threw = false;
    Exiv2::ByteOrder bo{};
    std::string exceptionWhat;
  };

  static DecodeOutcome RunExifParserDecode(Exiv2::ExifParser& parser,
                                          Exiv2::ExifData& exif,
                                          const Exiv2::byte* p,
                                          size_t n) {
    DecodeOutcome out;
    try {
      out.bo = parser.decode(exif, p, n);
    } catch (const std::exception& e) {
      out.threw = true;
      out.exceptionWhat = e.what();
    } catch (...) {
      out.threw = true;
      out.exceptionWhat = "<non-std-exception>";
    }
    return out;
  }

  static DecodeOutcome RunTiffParserDecode(Exiv2::ExifData& exif,
                                          const Exiv2::byte* p,
                                          size_t n) {
    DecodeOutcome out;
    try {
      Exiv2::IptcData iptc;
      Exiv2::XmpData xmp;
      out.bo = Exiv2::TiffParser::decode(exif, iptc, xmp, p, n);
    } catch (const std::exception& e) {
      out.threw = true;
      out.exceptionWhat = e.what();
    } catch (...) {
      out.threw = true;
      out.exceptionWhat = "<non-std-exception>";
    }
    return out;
  }

  static void ResetLogCapture() {
    logCalls_ = 0;
    lastLevel_ = -1;
    lastMsg_.clear();
  }

  static int logCalls_;
  static int lastLevel_;
  static std::string lastMsg_;

 private:
  static void CaptureHandler(int level, const char* s) {
    ++logCalls_;
    lastLevel_ = level;
    lastMsg_ = (s ? std::string(s) : std::string());
  }

  Exiv2::LogMsg::Handler oldHandler_{};
  Exiv2::LogMsg::Level oldLevel_{};
};

int ExifParserTest_784::logCalls_ = 0;
int ExifParserTest_784::lastLevel_ = -1;
std::string ExifParserTest_784::lastMsg_;

TEST_F(ExifParserTest_784, Decode_MinimalLittleEndian_MatchesTiffParserAndNoWarnings_784) {
  const auto data = MakeMinimalTiff(true);

  Exiv2::ExifParser parser;
  Exiv2::ExifData exifA;
  Exiv2::ExifData exifB;

  ResetLogCapture();
  const auto outA = RunExifParserDecode(parser, exifA, data.data(), data.size());
  const int callsAfterExif = logCalls_;

  ResetLogCapture();
  const auto outB = RunTiffParserDecode(exifB, data.data(), data.size());

  ASSERT_EQ(outA.threw, outB.threw);
  if (!outA.threw) {
    EXPECT_EQ(outA.bo, outB.bo);
    EXPECT_EQ(exifA.count(), exifB.count());
  }

#ifndef SUPPRESS_WARNINGS
  // For a minimal TIFF that shouldn't contain IPTC/XMP, ExifParser should not emit warnings.
  EXPECT_EQ(callsAfterExif, 0) << "Unexpected log output: level=" << lastLevel_ << " msg=" << lastMsg_;
#else
  (void)callsAfterExif;
#endif
}

TEST_F(ExifParserTest_784, Decode_MinimalBigEndian_MatchesTiffParserAndNoWarnings_784) {
  const auto data = MakeMinimalTiff(false);

  Exiv2::ExifParser parser;
  Exiv2::ExifData exifA;
  Exiv2::ExifData exifB;

  ResetLogCapture();
  const auto outA = RunExifParserDecode(parser, exifA, data.data(), data.size());
  const int callsAfterExif = logCalls_;

  ResetLogCapture();
  const auto outB = RunTiffParserDecode(exifB, data.data(), data.size());

  ASSERT_EQ(outA.threw, outB.threw);
  if (!outA.threw) {
    EXPECT_EQ(outA.bo, outB.bo);
    EXPECT_EQ(exifA.count(), exifB.count());
  }

#ifndef SUPPRESS_WARNINGS
  EXPECT_EQ(callsAfterExif, 0) << "Unexpected log output: level=" << lastLevel_ << " msg=" << lastMsg_;
#else
  (void)callsAfterExif;
#endif
}

TEST_F(ExifParserTest_784, Decode_TruncatedInputs_BehavesSameAsTiffParser_784) {
  const auto full = MakeMinimalTiff(true);

  // Exercise boundary sizes smaller than a complete minimal TIFF.
  for (size_t n = 0; n < full.size(); ++n) {
    Exiv2::ExifParser parser;
    Exiv2::ExifData exifA;
    Exiv2::ExifData exifB;

    const Exiv2::byte* p = (n == 0) ? nullptr : full.data();

    ResetLogCapture();
    const auto outA = RunExifParserDecode(parser, exifA, p, n);

    ResetLogCapture();
    const auto outB = RunTiffParserDecode(exifB, p, n);

    ASSERT_EQ(outA.threw, outB.threw) << "Size=" << n;
    if (!outA.threw) {
      EXPECT_EQ(outA.bo, outB.bo) << "Size=" << n;
      EXPECT_EQ(exifA.count(), exifB.count()) << "Size=" << n;
    }
  }
}

TEST_F(ExifParserTest_784, Decode_NullptrZeroSize_BehavesSameAsTiffParser_784) {
  Exiv2::ExifParser parser;
  Exiv2::ExifData exifA;
  Exiv2::ExifData exifB;

  ResetLogCapture();
  const auto outA = RunExifParserDecode(parser, exifA, nullptr, 0);

  ResetLogCapture();
  const auto outB = RunTiffParserDecode(exifB, nullptr, 0);

  ASSERT_EQ(outA.threw, outB.threw);
  if (!outA.threw) {
    EXPECT_EQ(outA.bo, outB.bo);
    EXPECT_EQ(exifA.count(), exifB.count());
  }
}

}  // namespace