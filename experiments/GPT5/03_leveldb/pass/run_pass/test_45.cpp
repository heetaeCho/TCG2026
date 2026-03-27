// File: util/coding_decodefixed64_test.cc
#include "util/coding.h"

#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>

using leveldb::DecodeFixed64;

TEST(DecodeFixed64Test_45, DecodesZero_45) {
  const char buf[8] = {0,0,0,0,0,0,0,0};
  EXPECT_EQ(0u, DecodeFixed64(buf));
}

TEST(DecodeFixed64Test_45, DecodesMaxUint64_45) {
  const char buf[8] = {
      static_cast<char>(0xFF), static_cast<char>(0xFF), static_cast<char>(0xFF),
      static_cast<char>(0xFF), static_cast<char>(0xFF), static_cast<char>(0xFF),
      static_cast<char>(0xFF), static_cast<char>(0xFF)};
  EXPECT_EQ(UINT64_MAX, DecodeFixed64(buf));
}

TEST(DecodeFixed64Test_45, DecodesKnownPattern_45) {
  // Value: 0x0123456789ABCDEF (little-endian bytes shown below)
  const char buf[8] = {
      static_cast<char>(0xEF), static_cast<char>(0xCD), static_cast<char>(0xAB),
      static_cast<char>(0x89), static_cast<char>(0x67), static_cast<char>(0x45),
      static_cast<char>(0x23), static_cast<char>(0x01)};
  EXPECT_EQ(0x0123456789ABCDEFULL, DecodeFixed64(buf));
}

TEST(DecodeFixed64Test_45, WorksWithUnalignedPointer_45) {
  // Embed the 8 bytes starting at offset 1 to simulate an unaligned pointer.
  const char raw[10] = {
      0x00,
      static_cast<char>(0x88), static_cast<char>(0x77), static_cast<char>(0x66),
      static_cast<char>(0x55), static_cast<char>(0x44), static_cast<char>(0x33),
      static_cast<char>(0x22), static_cast<char>(0x11),
      0x00};
  const char* ptr = raw + 1;
  EXPECT_EQ(0x1122334455667788ULL, DecodeFixed64(ptr));
}

TEST(DecodeFixed64Test_45, HandlesSignedCharBytes_45) {
  // Use bytes >= 0x80 to ensure behavior is correct regardless of char signedness.
  const char buf[8] = {
      static_cast<char>(0x80), static_cast<char>(0x81), static_cast<char>(0x82),
      static_cast<char>(0x83), static_cast<char>(0x84), static_cast<char>(0x85),
      static_cast<char>(0x86), static_cast<char>(0x87)};
  // Little-endian interpretation of the above bytes:
  const uint64_t expected = 0x8786858483828180ULL;
  EXPECT_EQ(expected, DecodeFixed64(buf));
}

TEST(DecodeFixed64Test_45, MultipleSequentialDecodes_45) {
  // Two consecutive 64-bit values in a single buffer.
  const char buf[16] = {
      // 0x1122334455667788
      static_cast<char>(0x88), static_cast<char>(0x77), static_cast<char>(0x66),
      static_cast<char>(0x55), static_cast<char>(0x44), static_cast<char>(0x33),
      static_cast<char>(0x22), static_cast<char>(0x11),
      // 0xFFEEDDCCBBAA0099
      static_cast<char>(0x99), static_cast<char>(0x00), static_cast<char>(0xAA),
      static_cast<char>(0xBB), static_cast<char>(0xCC), static_cast<char>(0xDD),
      static_cast<char>(0xEE), static_cast<char>(0xFF)};
  EXPECT_EQ(0x1122334455667788ULL, DecodeFixed64(buf + 0));
  EXPECT_EQ(0xFFEEDDCCBBAA0099ULL, DecodeFixed64(buf + 8));
}
