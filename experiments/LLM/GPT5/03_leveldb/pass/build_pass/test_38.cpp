// File: port_snappy_uncompress_test_38.cc

#include <gtest/gtest.h>
#include "port/port_stdcxx.h"

#if HAVE_SNAPPY
  #include <snappy.h>
#endif

using leveldb::port::Snappy_Uncompress;

class PortSnappyUncompressTest_38 : public ::testing::Test {};

// ------------------------------
// Error / boundary behaviors
// ------------------------------

// Invalid compressed data should return false in all builds.
TEST_F(PortSnappyUncompressTest_38, UncompressInvalidData_ReturnsFalse_38) {
  const char* bogus = "this is not snappy data";
  char output[64] = {};
  const bool ok = Snappy_Uncompress(bogus, strlen(bogus), output);
  EXPECT_FALSE(ok);
}

// Empty input should return false in all builds (no valid compressed payload).
TEST_F(PortSnappyUncompressTest_38, EmptyInput_ReturnsFalse_38) {
  const char* empty = "";
  char output[1] = {};  // any pointer; should not be used on failure
  const bool ok = Snappy_Uncompress(empty, 0, output);
  EXPECT_FALSE(ok);
}

#if HAVE_SNAPPY
// ------------------------------
// Normal operation (with Snappy)
// ------------------------------

// Round-trip: snappy::Compress -> Snappy_Uncompress restores original bytes.
TEST_F(PortSnappyUncompressTest_38, ValidRoundTrip_ReturnsTrueAndRestoresOriginal_38) {
  // Arrange: make some representative data
  const std::string original = "LevelDB Snappy test — quick brown fox 1234567890";

  // Compress with snappy
  std::string compressed;
  snappy::Compress(original.data(), original.size(), &compressed);

  // Prepare output buffer sized to original
  std::string out(original.size(), '\0');

  // Act
  const bool ok = Snappy_Uncompress(compressed.data(), compressed.size(), out.data());

  // Assert
  EXPECT_TRUE(ok);
  EXPECT_EQ(out, original);
}

// Binary payload with embedded nulls should be restored exactly.
TEST_F(PortSnappyUncompressTest_38, HandlesEmbeddedNulls_ExactRestore_38) {
  // Include zeros and high bytes to verify raw/binary integrity.
  const char raw_bytes[] = {'\x00','A','\x00','B','\xFF','C','\x7F','\x00'};
  const std::string original(raw_bytes, raw_bytes + sizeof(raw_bytes));

  std::string compressed;
  snappy::Compress(original.data(), original.size(), &compressed);

  std::string out(original.size(), '\0');
  const bool ok = Snappy_Uncompress(compressed.data(), compressed.size(), out.data());

  EXPECT_TRUE(ok);
  ASSERT_EQ(out.size(), original.size());
  EXPECT_EQ(out, original);
}
#endif  // HAVE_SNAPPY
