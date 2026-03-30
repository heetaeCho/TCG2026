// util/coding_test_decodefixed32_44.cc
#include "util/coding.h"
#include <gtest/gtest.h>
#include <cstdint>

using leveldb::DecodeFixed32;

TEST(DecodeFixed32Test_44, DecodesLittleEndianPattern_44) {
  // 0x12345678 encoded as little-endian bytes
  const uint8_t bytes[4] = {0x78, 0x56, 0x34, 0x12};
  const char* ptr = reinterpret_cast<const char*>(bytes);

  EXPECT_EQ(0x12345678u, DecodeFixed32(ptr));
}

TEST(DecodeFixed32Test_44, DecodesZero_44) {
  const uint8_t bytes[4] = {0x00, 0x00, 0x00, 0x00};
  const char* ptr = reinterpret_cast<const char*>(bytes);

  EXPECT_EQ(0u, DecodeFixed32(ptr));
}

TEST(DecodeFixed32Test_44, DecodesMaxUint32_44) {
  // Ensure bytes with high-bit set are handled (independent of char signedness)
  const uint8_t bytes[4] = {0xFF, 0xFF, 0xFF, 0xFF};
  const char* ptr = reinterpret_cast<const char*>(bytes);

  EXPECT_EQ(0xFFFFFFFFu, DecodeFixed32(ptr));
}

TEST(DecodeFixed32Test_44, DecodesSingleHighBit_44) {
  // Only the top bit set: 0x80000000
  const uint8_t bytes[4] = {0x00, 0x00, 0x00, 0x80};
  const char* ptr = reinterpret_cast<const char*>(bytes);

  EXPECT_EQ(0x80000000u, DecodeFixed32(ptr));
}

TEST(DecodeFixed32Test_44, DecodesWithOffsetPointer_44) {
  // Buffer with padding to ensure pointer arithmetic works and
  // the function correctly reads starting at the given pointer.
  const uint8_t buf[8] = {
      0xAA, 0xBB,            // padding (should be ignored)
      0xEF, 0xBE, 0xAD, 0xDE, // little-endian for 0xDEADBEEF
      0xCC, 0xDD             // padding
  };
  const char* ptr = reinterpret_cast<const char*>(buf + 2);

  EXPECT_EQ(0xDEADBEEFu, DecodeFixed32(ptr));
}

TEST(DecodeFixed32Test_44, DecodesMixedBytes_44) {
  // Random mix to guard general correctness
  const uint8_t bytes[4] = {0x01, 0x80, 0x00, 0x7F}; // 0x7F008001
  const char* ptr = reinterpret_cast<const char*>(bytes);

  EXPECT_EQ(0x7F008001u, DecodeFixed32(ptr));
}
