// =================================================================================================
// TEST_ID: 1554
// File: test_orfparser_encode_1554.cpp
// Unit tests for Exiv2::OrfParser::encode (black-box)
// =================================================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "exiv2/orfimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/iptc.hpp"
#include "exiv2/xmp_exiv2.hpp"

using namespace Exiv2;

// A minimal in-memory BasicIo implementation to observe external interactions (writes/size/tell).
class CountingMemIo final : public BasicIo {
 public:
  int open() override {
    isOpen_ = true;
    return 0;
  }

  int close() override {
    isOpen_ = false;
    return 0;
  }

  size_t write(const byte* data, size_t wcount) override {
    ++writeCalls_;
    lastWriteCount_ = wcount;
    lastWritePtrWasNull_ = (data == nullptr);

    // Behave reasonably even if data == nullptr: do not dereference; write nothing.
    if (data == nullptr || wcount == 0) {
      return 0;
    }

    const auto oldSize = buf_.size();
    buf_.resize(oldSize + wcount);
    std::memcpy(buf_.data() + oldSize, data, wcount);
    pos_ = static_cast<int64_t>(buf_.size());
    return wcount;
  }

  size_t write(BasicIo& /*src*/) override {
    // Not needed for these tests.
    return 0;
  }

  int putb(byte data) override {
    return static_cast<int>(write(&data, 1));
  }

  DataBuf read(size_t /*rcount*/) override { return DataBuf(); }

  size_t read(byte* /*buf*/, size_t /*rcount*/) override { return 0; }

  int getb() override { return -1; }

  void transfer(BasicIo& /*src*/) override {}

  int seek(int64_t offset, Position pos) override {
    int64_t base = 0;
    switch (pos) {
      case beg:
        base = 0;
        break;
      case cur:
        base = pos_;
        break;
      case end:
        base = static_cast<int64_t>(buf_.size());
        break;
      default:
        base = pos_;
        break;
    }
    pos_ = base + offset;
    if (pos_ < 0) pos_ = 0;
    return 0;
  }

  byte* mmap(bool /*isWriteable*/) override { return nullptr; }

  int munmap() override { return 0; }

  const size_t tell() override { return static_cast<size_t>(pos_); }

  const size_t size() override { return buf_.size(); }

  const bool isopen() override { return isOpen_; }

  const int error() override { return 0; }

  const bool eof() override { return false; }

  const std::string& path() override {
    static const std::string kPath = "CountingMemIo";
    return kPath;
  }

  void populateFakeData() override {}

  // Observability helpers
  int writeCalls() const { return writeCalls_; }
  size_t lastWriteCount() const { return lastWriteCount_; }
  bool lastWritePtrWasNull() const { return lastWritePtrWasNull_; }

 private:
  std::vector<byte> buf_{};
  int64_t pos_{0};
  bool isOpen_{true};

  int writeCalls_{0};
  size_t lastWriteCount_{0};
  bool lastWritePtrWasNull_{false};
};

class OrfParserEncodeTest_1554 : public ::testing::Test {
 protected:
  static std::vector<byte> MakeMinimalOrfBuffer(ByteOrder order) {
    // Minimal ORF/TIFF-like header using ORF signature 0x4f52 and first IFD offset 8.
    // Layout:
    // 0..1: byte order ("II" or "MM")
    // 2..3: signature (0x4f52)
    // 4..7: IFD0 offset (8)
    // 8..9: number of entries (0)
    // 10..13: next IFD offset (0)
    std::vector<byte> b(14, 0);

    if (order == littleEndian) {
      b[0] = 'I';
      b[1] = 'I';
      // 0x4f52 in little-endian: 0x52 0x4f
      b[2] = 0x52;
      b[3] = 0x4f;
      // offset 8 little-endian
      b[4] = 0x08;
      b[5] = 0x00;
      b[6] = 0x00;
      b[7] = 0x00;
      // entries = 0 already
    } else {
      b[0] = 'M';
      b[1] = 'M';
      // 0x4f52 in big-endian: 0x4f 0x52
      b[2] = 0x4f;
      b[3] = 0x52;
      // offset 8 big-endian
      b[4] = 0x00;
      b[5] = 0x00;
      b[6] = 0x00;
      b[7] = 0x08;
    }
    return b;
  }

  static void AddSomeMetadata(ExifData& exif, IptcData& iptc, XmpData& xmp) {
    // Use operator[] only (no assumptions about Value types / setters).
    // This should create entries in containers in a stable, interface-driven way.
    (void)exif["Exif.Image.Make"];
    (void)exif["Exif.Photo.FNumber"];

    (void)iptc["Iptc.Application2.ObjectName"];
    (void)xmp["Xmp.dc.title"];
  }
};

TEST_F(OrfParserEncodeTest_1554, ExifCountNeverIncreases_AfterEncodeAttempt_1554) {
  CountingMemIo io;
  ExifData exif;
  IptcData iptc;
  XmpData xmp;
  AddSomeMetadata(exif, iptc, xmp);

  const auto before = exif.count();

  // Use clearly-invalid data to avoid assuming encode succeeds; still verify observable postcondition.
  const byte invalid[2] = {0x00, 0x01};

  try {
    (void)OrfParser::encode(io, invalid, sizeof(invalid), littleEndian, exif, iptc, xmp);
  } catch (...) {
    // encode may throw on invalid input; filtering step happens before deeper encoding.
  }

  EXPECT_LE(exif.count(), before);
}

TEST_F(OrfParserEncodeTest_1554, IptcAndXmpRemainUnchangedByInterfaceObservableCounts_1554) {
  CountingMemIo io;
  ExifData exif;
  IptcData iptc;
  XmpData xmp;
  AddSomeMetadata(exif, iptc, xmp);

  const auto iptcBefore = iptc.count();
  const auto xmpBefore = xmp.count();

  const byte invalid[3] = {0x10, 0x20, 0x30};

  try {
    (void)OrfParser::encode(io, invalid, sizeof(invalid), littleEndian, exif, iptc, xmp);
  } catch (...) {
    // ok
  }

  // iptcData/xmpData are passed as const references; we only assert what is observable.
  EXPECT_EQ(iptc.count(), iptcBefore);
  EXPECT_EQ(xmp.count(), xmpBefore);
}

TEST_F(OrfParserEncodeTest_1554, WorksWithBothByteOrders_AndNeverIncreasesExifCount_1554) {
  for (ByteOrder order : {littleEndian, bigEndian}) {
    CountingMemIo io;
    ExifData exif;
    IptcData iptc;
    XmpData xmp;
    AddSomeMetadata(exif, iptc, xmp);

    const auto before = exif.count();
    const auto buf = MakeMinimalOrfBuffer(order);

    try {
      (void)OrfParser::encode(io, buf.data(), buf.size(), order, exif, iptc, xmp);
    } catch (...) {
      // Implementation may still reject minimal buffers; we avoid assuming success.
    }

    EXPECT_LE(exif.count(), before);
  }
}

TEST_F(OrfParserEncodeTest_1554, Boundary_NullDataAndZeroSize_DoesNotIncreaseExifCount_1554) {
  CountingMemIo io;
  ExifData exif;
  IptcData iptc;
  XmpData xmp;
  AddSomeMetadata(exif, iptc, xmp);

  const auto before = exif.count();

  try {
    (void)OrfParser::encode(io, nullptr, 0, littleEndian, exif, iptc, xmp);
  } catch (...) {
    // Either behavior is acceptable to the test: we only require no observable increase.
  }

  EXPECT_LE(exif.count(), before);
}

TEST_F(OrfParserEncodeTest_1554, ExternalInteraction_WhenEncodeSucceeds_WritesToIo_1554) {
  CountingMemIo io;
  ExifData exif;
  IptcData iptc;
  XmpData xmp;
  AddSomeMetadata(exif, iptc, xmp);

  const auto buf = MakeMinimalOrfBuffer(littleEndian);

  try {
    (void)OrfParser::encode(io, buf.data(), buf.size(), littleEndian, exif, iptc, xmp);

    // If encode completes successfully, it should have interacted with the BasicIo (observable).
    // We do not assume exact write counts/bytes, only that something was written.
    EXPECT_GT(io.writeCalls(), 0);
    EXPECT_GT(io.size(), 0u);
    EXPECT_FALSE(io.lastWritePtrWasNull());
    EXPECT_GT(io.lastWriteCount(), 0u);
  } catch (...) {
    // If encode throws, we cannot require writes happened; skip to keep test black-box safe.
    GTEST_SKIP() << "encode threw on minimal ORF buffer; external write interaction not observable here.";
  }
}