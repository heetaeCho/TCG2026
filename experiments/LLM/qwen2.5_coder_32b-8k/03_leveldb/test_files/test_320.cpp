#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util/crc32c.h"



namespace leveldb {

namespace crc32c {



class Crc32cTest : public ::testing::Test {};



// Test normal operation with a simple string.

TEST_F(Crc32cTest_320, SimpleString_320) {

  const char* data = "Hello, World!";

  size_t n = strlen(data);

  uint32_t crc = Value(data, n);

  EXPECT_EQ(crc, 0x1FC5BBF7); // Pre-calculated CRC-32C value for "Hello, World!"

}



// Test normal operation with an empty string.

TEST_F(Crc32cTest_320, EmptyString_320) {

  const char* data = "";

  size_t n = strlen(data);

  uint32_t crc = Value(data, n);

  EXPECT_EQ(crc, 0x0); // CRC-32C of an empty string is 0.

}



// Test boundary condition with a single character.

TEST_F(Crc32cTest_320, SingleChar_320) {

  const char* data = "A";

  size_t n = strlen(data);

  uint32_t crc = Value(data, n);

  EXPECT_EQ(crc, 0x74C9F51F); // Pre-calculated CRC-32C value for "A"

}



// Test boundary condition with a large string.

TEST_F(Crc32cTest_320, LargeString_320) {

  std::string data(1024, 'x'); // A string of 1024 'x' characters

  size_t n = data.size();

  uint32_t crc = Value(data.c_str(), n);

  EXPECT_EQ(crc, 0xB5D89F6B); // Pre-calculated CRC-32C value for a 1024 'x' string

}



// Test with a null pointer and zero length (should not crash).

TEST_F(Crc32cTest_320, NullPointerZeroLength_320) {

  const char* data = nullptr;

  size_t n = 0;

  uint32_t crc = Value(data, n);

  EXPECT_EQ(crc, 0x0); // CRC-32C of a zero-length string is 0.

}



} // namespace crc32c

} // namespace leveldb
