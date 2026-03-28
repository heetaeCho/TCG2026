#include "gtest/gtest.h"
#include "port/port_stdcxx.h"

#include <cstring>
#include <string>

// Test fixture for Snappy_GetUncompressedLength
class SnappyGetUncompressedLengthTest_37 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test with null-like empty input and zero length
TEST_F(SnappyGetUncompressedLengthTest_37, EmptyInput_37) {
  size_t result = 0;
  const char* input = "";
  bool success = leveldb::port::Snappy_GetUncompressedLength(input, 0, &result);
#if HAVE_SNAPPY
  // With zero-length input, snappy may or may not succeed depending on
  // implementation, but it should not crash.
  (void)success;
#else
  EXPECT_FALSE(success);
#endif
}

// Test with non-empty but invalid (non-snappy) data
TEST_F(SnappyGetUncompressedLengthTest_37, InvalidData_37) {
  size_t result = 42;
  const char data[] = "This is not snappy compressed data at all";
  bool success = leveldb::port::Snappy_GetUncompressedLength(
      data, strlen(data), &result);
#if HAVE_SNAPPY
  // Invalid snappy data should likely return false or some error indication
  // We cannot guarantee the exact behavior, but it should not crash.
  (void)success;
#else
  EXPECT_FALSE(success);
  // When snappy is not available, result should remain unchanged or be
  // irrelevant, but the function must return false.
#endif
}

// Test with nullptr input and zero length - should not crash
TEST_F(SnappyGetUncompressedLengthTest_37, NullInputZeroLength_37) {
  size_t result = 0;
  bool success = leveldb::port::Snappy_GetUncompressedLength(nullptr, 0, &result);
#if HAVE_SNAPPY
  // Behavior with nullptr is implementation-defined for snappy
  (void)success;
#else
  EXPECT_FALSE(success);
#endif
}

// Test return value is bool
TEST_F(SnappyGetUncompressedLengthTest_37, ReturnTypeIsBool_37) {
  size_t result = 0;
  const char data[] = "test";
  auto ret = leveldb::port::Snappy_GetUncompressedLength(data, sizeof(data), &result);
  // Verify it is convertible to bool (it should be bool)
  bool b = ret;
  (void)b;
#if !HAVE_SNAPPY
  EXPECT_FALSE(ret);
#endif
}

#if HAVE_SNAPPY
#include "snappy.h"

// Test with valid snappy-compressed data
TEST_F(SnappyGetUncompressedLengthTest_37, ValidSnappyData_37) {
  std::string original = "Hello, this is a test string for snappy compression!";
  std::string compressed;
  snappy::Compress(original.data(), original.size(), &compressed);

  size_t uncompressed_length = 0;
  bool success = leveldb::port::Snappy_GetUncompressedLength(
      compressed.data(), compressed.size(), &uncompressed_length);
  EXPECT_TRUE(success);
  EXPECT_EQ(uncompressed_length, original.size());
}

// Test with valid snappy-compressed empty string
TEST_F(SnappyGetUncompressedLengthTest_37, ValidSnappyEmptyString_37) {
  std::string original = "";
  std::string compressed;
  snappy::Compress(original.data(), original.size(), &compressed);

  size_t uncompressed_length = 999;
  bool success = leveldb::port::Snappy_GetUncompressedLength(
      compressed.data(), compressed.size(), &uncompressed_length);
  EXPECT_TRUE(success);
  EXPECT_EQ(uncompressed_length, 0u);
}

// Test with valid snappy-compressed large data
TEST_F(SnappyGetUncompressedLengthTest_37, ValidSnappyLargeData_37) {
  std::string original(100000, 'A');
  std::string compressed;
  snappy::Compress(original.data(), original.size(), &compressed);

  size_t uncompressed_length = 0;
  bool success = leveldb::port::Snappy_GetUncompressedLength(
      compressed.data(), compressed.size(), &uncompressed_length);
  EXPECT_TRUE(success);
  EXPECT_EQ(uncompressed_length, original.size());
}

// Test with truncated snappy data
TEST_F(SnappyGetUncompressedLengthTest_37, TruncatedSnappyData_37) {
  std::string original = "Some data to compress for truncation test";
  std::string compressed;
  snappy::Compress(original.data(), original.size(), &compressed);

  // Truncate the compressed data to just 1 byte (if possible)
  if (compressed.size() > 1) {
    size_t uncompressed_length = 0;
    // GetUncompressedLength only needs the header, so even 1 byte might work
    // for the length varint. We test with partial data.
    bool success = leveldb::port::Snappy_GetUncompressedLength(
        compressed.data(), 1, &uncompressed_length);
    // May or may not succeed depending on varint encoding, but should not crash.
    (void)success;
  }
}

// Test with single byte data
TEST_F(SnappyGetUncompressedLengthTest_37, ValidSnappySingleByte_37) {
  std::string original = "X";
  std::string compressed;
  snappy::Compress(original.data(), original.size(), &compressed);

  size_t uncompressed_length = 0;
  bool success = leveldb::port::Snappy_GetUncompressedLength(
      compressed.data(), compressed.size(), &uncompressed_length);
  EXPECT_TRUE(success);
  EXPECT_EQ(uncompressed_length, 1u);
}

#endif  // HAVE_SNAPPY

// Test that without snappy, arbitrary data always returns false
TEST_F(SnappyGetUncompressedLengthTest_37, ArbitraryDataReturnsFalseWithoutSnappy_37) {
  const char data[] = {0x00, 0x01, 0x02, 0x03, 0x04};
  size_t result = 12345;
  bool success = leveldb::port::Snappy_GetUncompressedLength(
      data, sizeof(data), &result);
#if !HAVE_SNAPPY
  EXPECT_FALSE(success);
#else
  // With snappy, the result depends on whether data is valid snappy
  (void)success;
#endif
}
