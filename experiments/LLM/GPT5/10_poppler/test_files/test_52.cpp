// FoFiIdentifier_identifyCFF_test_52.cc
// Unit tests for identifyCFF(Reader*, int) in FoFiIdentifier.cc
//
// NOTE: identifyCFF is a static function in the .cc file (internal linkage).
// These tests include the implementation file so the function is available in
// this translation unit, without re-implementing its logic.

#include <gtest/gtest.h>
#include <climits>
#include <cstdint>
#include <vector>
#include <string>

// Public enum type
#include "FoFiIdentifier.h"

// Include the implementation so we can call the static identifyCFF().
#include "FoFiIdentifier.cc"

namespace {

class ByteArrayReader final : public Reader {
public:
  explicit ByteArrayReader(std::vector<uint8_t> data) : data_(std::move(data)) {}

  int getByte(int pos) override {
    if (pos < 0 || static_cast<size_t>(pos) >= data_.size()) {
      return -1;
    }
    return static_cast<int>(data_[static_cast<size_t>(pos)]);
  }

  bool getU16BE(int pos, int *val) override {
    if (!val) return false;
    if (pos < 0 || static_cast<size_t>(pos + 1) >= data_.size()) return false;
    const uint16_t hi = data_[static_cast<size_t>(pos)];
    const uint16_t lo = data_[static_cast<size_t>(pos + 1)];
    *val = static_cast<int>((hi << 8) | lo);
    return true;
  }

  bool getU32BE(int pos, unsigned int *val) override {
    if (!val) return false;
    if (pos < 0 || static_cast<size_t>(pos + 3) >= data_.size()) return false;
    const uint32_t b0 = data_[static_cast<size_t>(pos)];
    const uint32_t b1 = data_[static_cast<size_t>(pos + 1)];
    const uint32_t b2 = data_[static_cast<size_t>(pos + 2)];
    const uint32_t b3 = data_[static_cast<size_t>(pos + 3)];
    *val = static_cast<unsigned int>((b0 << 24) | (b1 << 16) | (b2 << 8) | b3);
    return true;
  }

  bool getU32LE(int pos, unsigned int *val) override {
    if (!val) return false;
    if (pos < 0 || static_cast<size_t>(pos + 3) >= data_.size()) return false;
    const uint32_t b0 = data_[static_cast<size_t>(pos)];
    const uint32_t b1 = data_[static_cast<size_t>(pos + 1)];
    const uint32_t b2 = data_[static_cast<size_t>(pos + 2)];
    const uint32_t b3 = data_[static_cast<size_t>(pos + 3)];
    *val = static_cast<unsigned int>((b3 << 24) | (b2 << 16) | (b1 << 8) | b0);
    return true;
  }

  bool getUVarBE(int pos, int size, unsigned int *val) override {
    if (!val) return false;
    if (size < 1 || size > 4) return false;
    if (pos < 0 || static_cast<size_t>(pos + size - 1) >= data_.size()) return false;

    unsigned int out = 0;
    for (int i = 0; i < size; ++i) {
      out = (out << 8) | static_cast<unsigned int>(data_[static_cast<size_t>(pos + i)]);
    }
    *val = out;
    return true;
  }

  bool cmp(int pos, const char *s) override {
    if (!s) return false;
    if (pos < 0) return false;
    const size_t start = static_cast<size_t>(pos);
    size_t i = 0;
    for (; s[i] != '\0'; ++i) {
      if (start + i >= data_.size()) return false;
      if (data_[start + i] != static_cast<uint8_t>(s[i])) return false;
    }
    return true;
  }

private:
  std::vector<uint8_t> data_;
};

class FaultyU16Reader final : public ByteArrayReader {
public:
  FaultyU16Reader(std::vector<uint8_t> data, int fail_pos)
      : ByteArrayReader(std::move(data)), fail_pos_(fail_pos) {}

  bool getU16BE(int pos, int *val) override {
    if (pos == fail_pos_) return false;
    return ByteArrayReader::getU16BE(pos, val);
  }

private:
  int fail_pos_;
};

class IdentifyCFFTest_52 : public ::testing::Test {
protected:
  // Build a minimal CFF-like buffer that reaches the final return path.
  // If cid == true, places the two bytes {12, 30} at the probe position.
  // If shortDict == true, makes the DICT range tight enough that the loop
  // hits the "pos >= endPos" boundary check and returns 8-bit.
  static std::vector<uint8_t> MakeMinimalCffBuffer(bool cid, bool shortDict) {
    // Layout (start=0):
    // 0..3: CFF header bytes
    // 4..5: Name INDEX count (U16BE) = 0
    // 6.. : Next INDEX count (U16BE) = 1
    //      offSize (1 byte) = 1
    //      offsets (2 bytes): offset0=1, offset1=6 (or 4 if shortDict)
    //      DICT bytes begin at base=11; DICT span is [11, endPos)
    //
    // We keep the total buffer reasonably sized.
    std::vector<uint8_t> buf(20, 0x00);

    buf[0] = 0x01;
    buf[1] = 0x00;
    buf[2] = 0x04; // hdrSize
    buf[3] = 0x01; // offSize0

    // Name INDEX count = 0 at pos=4
    buf[4] = 0x00;
    buf[5] = 0x00;

    // Next INDEX count = 1 at pos=6
    buf[6] = 0x00;
    buf[7] = 0x01;

    // offSize1 at pos+2 (8)
    buf[8] = 0x01;

    // offsets at pos+3 (9) and (10)
    buf[9]  = 0x01;                      // offset0
    buf[10] = shortDict ? 0x04 : 0x06;   // offset1

    // DICT bytes start at base=11
    // Provide three bytes in the allowed "number" range used by the parser.
    buf[11] = 0x20;
    buf[12] = 0x20;
    buf[13] = 0x20;

    // Probe position after consuming 3 bytes is 14.
    if (!shortDict) {
      if (cid) {
        buf[14] = 0x0c; // 12
        buf[15] = 0x1e; // 30
      } else {
        buf[14] = 0x00;
        buf[15] = 0x00;
      }
    }

    return buf;
  }
};

TEST_F(IdentifyCFFTest_52, WrongMagicReturnsUnknown_52) {
  std::vector<uint8_t> buf(8, 0x00);
  buf[0] = 0x00; // wrong
  buf[1] = 0x00;
  ByteArrayReader reader(buf);

  EXPECT_EQ(fofiIdUnknown, identifyCFF(&reader, 0));
}

TEST_F(IdentifyCFFTest_52, NegativeHeaderSizeReturnsUnknown_52) {
  // getByte(start+2) < 0 -> unknown
  std::vector<uint8_t> buf(8, 0x00);
  buf[0] = 0x01;
  buf[1] = 0x00;
  // Make buffer too small so getByte(2) returns -1 in our Reader.
  buf.resize(2);
  ByteArrayReader reader(buf);

  EXPECT_EQ(fofiIdUnknown, identifyCFF(&reader, 0));
}

TEST_F(IdentifyCFFTest_52, OffSize0OutOfRangeReturnsUnknown_52) {
  std::vector<uint8_t> buf(8, 0x00);
  buf[0] = 0x01;
  buf[1] = 0x00;
  buf[2] = 0x04; // hdrSize
  buf[3] = 0x00; // offSize0 invalid (<1)
  ByteArrayReader reader(buf);

  EXPECT_EQ(fofiIdUnknown, identifyCFF(&reader, 0));
}

TEST_F(IdentifyCFFTest_52, U16ReadFailureReturnsUnknown_52) {
  // Arrange a buffer that would otherwise proceed, but force getU16BE(pos=4) to fail.
  auto buf = MakeMinimalCffBuffer(/*cid=*/false, /*shortDict=*/false);
  FaultyU16Reader reader(buf, /*fail_pos=*/4);

  EXPECT_EQ(fofiIdUnknown, identifyCFF(&reader, 0));
}

TEST_F(IdentifyCFFTest_52, MinimalValidNonCidReturnsCff8Bit_52) {
  auto buf = MakeMinimalCffBuffer(/*cid=*/false, /*shortDict=*/false);
  ByteArrayReader reader(buf);

  EXPECT_EQ(fofiIdCFF8Bit, identifyCFF(&reader, 0));
}

TEST_F(IdentifyCFFTest_52, MinimalValidCidProbeReturnsCffCid_52) {
  auto buf = MakeMinimalCffBuffer(/*cid=*/true, /*shortDict=*/false);
  ByteArrayReader reader(buf);

  EXPECT_EQ(fofiIdCFFCID, identifyCFF(&reader, 0));
}

TEST_F(IdentifyCFFTest_52, DictRangeTooShortTriggersBoundaryReturnCff8Bit_52) {
  // Tight DICT range causes the parser to hit its internal boundary check during the loop.
  auto buf = MakeMinimalCffBuffer(/*cid=*/false, /*shortDict=*/true);
  ByteArrayReader reader(buf);

  EXPECT_EQ(fofiIdCFF8Bit, identifyCFF(&reader, 0));
}

TEST_F(IdentifyCFFTest_52, Offset0GreaterThanOffset1ReturnsUnknown_52) {
  // Start from a valid-ish buffer and then flip the two offsets so offset0 > offset1.
  auto buf = MakeMinimalCffBuffer(/*cid=*/false, /*shortDict=*/false);
  // offsets are at [9]=offset0 and [10]=offset1 (size=1)
  buf[9] = 0x06;
  buf[10] = 0x01;

  ByteArrayReader reader(buf);
  EXPECT_EQ(fofiIdUnknown, identifyCFF(&reader, 0));
}

} // namespace