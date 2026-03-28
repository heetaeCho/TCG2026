// File: table/format_decodefrom_footer_test_399.cc

#include "table/format.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include <gtest/gtest.h>
#include <cstdint>
#include <string>

using leveldb::Footer;
using leveldb::Slice;
using leveldb::Status;

namespace {

// NOTE: Footer::kEncodedLength is not exposed in the snippet.
// In upstream LevelDB it is 48 bytes. We use that here solely to craft inputs
// for black-box testing of observable behavior.
static constexpr size_t kEncodedLength_Assumed = 48;

// Little-endian encoder for 32-bit, to craft the footer's magic bytes.
void PutFixed32LE(char* dst, uint32_t v) {
  dst[0] = static_cast<char>(v & 0xFF);
  dst[1] = static_cast<char>((v >> 8) & 0xFF);
  dst[2] = static_cast<char>((v >> 16) & 0xFF);
  dst[3] = static_cast<char>((v >> 24) & 0xFF);
}

}  // namespace

class FooterDecodeFromTest_399 : public ::testing::Test {};

// [399] Too-short input should return Corruption and not modify input
TEST_F(FooterDecodeFromTest_399, TooShortReturnsCorruption_399) {
  // Input shorter than kEncodedLength
  std::string raw(8, '\0');  // definitely < 48
  Slice input(raw);
  const size_t original_size = input.size();
  const char* original_data = input.data();

  Footer f;
  Status st = f.DecodeFrom(&input);

  EXPECT_TRUE(st.IsCorruption()) << "Expected corruption for too-short footer";
  // input should remain unchanged on failure
  EXPECT_EQ(input.size(), original_size);
  EXPECT_EQ(input.data(), original_data);
  // Optional: error message should mention 'footer too short'
  EXPECT_NE(st.ToString().find("footer too short"), std::string::npos);
}

// [399] Long enough input but bad magic should return Corruption and not modify input
TEST_F(FooterDecodeFromTest_399, BadMagicReturnsCorruption_399) {
  // Create a buffer >= kEncodedLength filled with zeros, so magic != kTableMagicNumber.
  std::string raw(kEncodedLength_Assumed, '\0');
  Slice input(raw);
  const size_t original_size = input.size();
  const char* original_data = input.data();

  Footer f;
  Status st = f.DecodeFrom(&input);

  EXPECT_TRUE(st.IsCorruption()) << "Expected corruption for bad magic";
  EXPECT_EQ(input.size(), original_size);
  EXPECT_EQ(input.data(), original_data);
  // Optional: error message should mention 'bad magic number'
  EXPECT_NE(st.ToString().find("bad magic number"), std::string::npos);
}

// [399] Correct magic but invalid handles before it -> DecodeFrom should fail (corruption) and not modify input
TEST_F(FooterDecodeFromTest_399, CorrectMagicButInvalidHandlesStillFail_399) {
  // Craft a footer-sized buffer with correct magic at the expected position,
  // but leave the handle region as zeros (so handle decoding should fail).
  std::string raw(kEncodedLength_Assumed, '\0');

  // Place magic at the last 8 bytes of the *encoded footer* region.
  // Footer reads magic from (data + kEncodedLength - 8).
  const uint64_t magic = leveldb::kTableMagicNumber;
  const uint32_t magic_lo = static_cast<uint32_t>(magic & 0xFFFFFFFFull);
  const uint32_t magic_hi = static_cast<uint32_t>((magic >> 32) & 0xFFFFFFFFull);
  const size_t magic_pos = kEncodedLength_Assumed - 8;
  PutFixed32LE(&raw[magic_pos], magic_lo);
  PutFixed32LE(&raw[magic_pos + 4], magic_hi);

  Slice input(raw);
  const size_t original_size = input.size();
  const char* original_data = input.data();

  Footer f;
  Status st = f.DecodeFrom(&input);

  // We expect failure because the two BlockHandles preceding magic are invalid (zeros).
  EXPECT_TRUE(!st.ok());
  EXPECT_TRUE(st.IsCorruption()) << "Expected corruption when handles are invalid despite correct magic";

  // Since result is not ok, input should not be rewritten/advanced.
  EXPECT_EQ(input.size(), original_size);
  EXPECT_EQ(input.data(), original_data);
}
