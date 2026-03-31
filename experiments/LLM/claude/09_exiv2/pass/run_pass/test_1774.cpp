#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "crwimage_int.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

#include <cstring>
#include <vector>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to write a uint16_t in little-endian
static void putUShortLE(byte* buf, uint16_t val) {
  buf[0] = static_cast<byte>(val & 0xFF);
  buf[1] = static_cast<byte>((val >> 8) & 0xFF);
}

// Helper to write a uint32_t in little-endian
static void putULongLE(byte* buf, uint32_t val) {
  buf[0] = static_cast<byte>(val & 0xFF);
  buf[1] = static_cast<byte>((val >> 8) & 0xFF);
  buf[2] = static_cast<byte>((val >> 16) & 0xFF);
  buf[3] = static_cast<byte>((val >> 24) & 0xFF);
}

// Helper to write a uint16_t in big-endian
static void putUShortBE(byte* buf, uint16_t val) {
  buf[0] = static_cast<byte>((val >> 8) & 0xFF);
  buf[1] = static_cast<byte>(val & 0xFF);
}

// Helper to write a uint32_t in big-endian
static void putULongBE(byte* buf, uint32_t val) {
  buf[0] = static_cast<byte>((val >> 24) & 0xFF);
  buf[1] = static_cast<byte>((val >> 16) & 0xFF);
  buf[2] = static_cast<byte>((val >> 8) & 0xFF);
  buf[3] = static_cast<byte>(val & 0xFF);
}

class CiffDirectoryTest_1774 : public ::testing::Test {
 protected:
  CiffDirectory dir_;
};

// Test that size < 4 throws kerCorruptedMetadata
TEST_F(CiffDirectoryTest_1774, ReadDirectorySizeLessThan4Throws_1774) {
  byte data[3] = {0, 0, 0};
  EXPECT_THROW(dir_.readDirectory(data, 0, littleEndian), Error);
  EXPECT_THROW(dir_.readDirectory(data, 1, littleEndian), Error);
  EXPECT_THROW(dir_.readDirectory(data, 2, littleEndian), Error);
  EXPECT_THROW(dir_.readDirectory(data, 3, littleEndian), Error);
}

// Test that offset pointing beyond valid range throws
TEST_F(CiffDirectoryTest_1774, ReadDirectoryOffsetOutOfRangeThrows_1774) {
  // Create a buffer of size 6:
  // Last 4 bytes hold the offset to directory.
  // If offset > size - 2 = 4, should throw.
  byte data[6];
  memset(data, 0, sizeof(data));
  // Set offset at end (bytes 2..5) to value 5, which is > 6-2=4
  putULongLE(data + 2, 5);
  EXPECT_THROW(dir_.readDirectory(data, 6, littleEndian), Error);
}

// Test that zero entries directory does not throw
TEST_F(CiffDirectoryTest_1774, ReadDirectoryZeroEntriesNoThrow_1774) {
  // We need: last 4 bytes = offset to count
  // At that offset: uint16 count = 0
  // Minimum: offset = 0, count at byte 0..1 = 0, then last 4 bytes at positions 2..5 = 0
  // Total size = 6
  byte data[6];
  memset(data, 0, sizeof(data));
  // count = 0 at offset 0
  putUShortLE(data, 0);
  // directory offset stored at last 4 bytes = 0
  putULongLE(data + 2, 0);

  EXPECT_NO_THROW(dir_.readDirectory(data, 6, littleEndian));
}

// Test that count * 10 > remaining space throws
TEST_F(CiffDirectoryTest_1774, ReadDirectoryCountTooLargeThrows_1774) {
  // Size = 10, last 4 bytes at offset 6..9 hold the directory offset
  // Directory offset = 0, count at offset 0..1
  // After count (offset 2), remaining = size - offset - 2 = 10 - 0 - 2 = 8
  // If count = 1, then count*10 = 10 > 8, should throw
  byte data[10];
  memset(data, 0, sizeof(data));
  putUShortLE(data, 1); // count = 1
  putULongLE(data + 6, 0); // directory offset = 0

  EXPECT_THROW(dir_.readDirectory(data, 10, littleEndian), Error);
}

// Test valid single entry directory (little-endian) with a non-directory tag
TEST_F(CiffDirectoryTest_1774, ReadDirectorySingleEntryLittleEndian_1774) {
  // Layout:
  // We need space for: entry data (value area) + entry descriptors + count + offset
  // 
  // Let's make a buffer:
  // Bytes 0..9: value data area (unused, just padding)
  // Byte 10: start of directory entries
  //   - First entry: 10 bytes (tag[2] + size_or_offset[4] + offset_or_data[4])
  // Byte 20: count (uint16)
  // Byte 22..25: directory offset (uint32) pointing to byte 20
  // Total size = 26
  //
  // Actually the format is:
  // At the directory offset we have: count (2 bytes), then count entries of 10 bytes each
  // Then at size-4 we have the uint32 offset to the directory.
  //
  // Let's place directory at offset 0:
  // Byte 0..1: count = 1
  // Byte 2..11: entry (10 bytes) - tag + data
  // Then we need the last 4 bytes to point to offset 0
  // So total: 2 + 10 + 4 = 16
  // Last 4 bytes (12..15) = 0
  
  const size_t totalSize = 16;
  byte data[totalSize];
  memset(data, 0, sizeof(data));
  
  // count = 1 at offset 0
  putUShortLE(data, 1);
  
  // Entry at offset 2: tag (2 bytes) + size (4 bytes) + offset (4 bytes)
  // Use a simple non-directory tag. Tag 0x0000 should be fine as a non-directory type.
  putUShortLE(data + 2, 0x0000); // tag
  putULongLE(data + 4, 0);       // size
  putULongLE(data + 8, 0);       // offset
  
  // Directory offset at last 4 bytes
  putULongLE(data + 12, 0);
  
  EXPECT_NO_THROW(dir_.readDirectory(data, totalSize, littleEndian));
}

// Test valid single entry directory (big-endian)
TEST_F(CiffDirectoryTest_1774, ReadDirectorySingleEntryBigEndian_1774) {
  const size_t totalSize = 16;
  byte data[totalSize];
  memset(data, 0, sizeof(data));
  
  // count = 1 at offset 0 in big-endian
  putUShortBE(data, 1);
  
  // Entry at offset 2
  putUShortBE(data + 2, 0x0000); // tag
  putULongBE(data + 4, 0);       // size
  putULongBE(data + 8, 0);       // offset
  
  // Directory offset at last 4 bytes
  putULongBE(data + 12, 0);
  
  EXPECT_NO_THROW(dir_.readDirectory(data, totalSize, bigEndian));
}

// Test exactly size == 4 with offset that would be valid (offset = 0, then count needs 2 bytes but we only have 4 total... offset 0 means count at byte 0, and size-4=0 offset in data+0)
// Actually with size=4: last 4 bytes = whole buffer. offset stored there.
// For offset to be valid: o <= size - 2 = 2
// If o = 0, count at offset 0, then o becomes 2. count*10 must be <= size - o = 4 - 2 = 2
// So count must be 0.
TEST_F(CiffDirectoryTest_1774, ReadDirectoryMinimalValidSize4_1774) {
  byte data[4];
  memset(data, 0, sizeof(data));
  // offset = 0 (last 4 bytes)
  putULongLE(data, 0);
  // count at offset 0 = first 2 bytes of data = 0 (since the uint32 0 in LE is 00 00 00 00)
  // count = 0, which is fine
  EXPECT_NO_THROW(dir_.readDirectory(data, 4, littleEndian));
}

// Test with nullptr data and size < 4
TEST_F(CiffDirectoryTest_1774, ReadDirectoryNullptrSmallSizeThrows_1774) {
  // size < 4 should throw before accessing pData
  EXPECT_THROW(dir_.readDirectory(nullptr, 0, littleEndian), Error);
}

// Test that offset exactly at boundary (o == size - 2) is valid with count = 0
TEST_F(CiffDirectoryTest_1774, ReadDirectoryOffsetAtBoundary_1774) {
  // size = 8, offset = 6 (= size - 2), count at offset 6 = 0
  byte data[8];
  memset(data, 0, sizeof(data));
  // Last 4 bytes (4..7) = offset = 4 (size - 2 - 2... wait, size-2 = 6)
  // Let's set offset = 4. Then size - 2 = 6, 4 <= 6, OK.
  // count at offset 4 = data[4..5]
  putULongLE(data + 4, 4); // This is the directory offset stored in last 4 bytes
  // But wait, last 4 bytes of an 8-byte buffer are at index 4..7
  // So putULongLE(data + 4, 4) sets bytes 4..7 to value 4
  // count is at data[4..5] — but that's the same bytes as part of our offset!
  // In LE, value 4 = 04 00 00 00, so data[4]=4, data[5]=0 → count = 4
  // That's 4*10=40 > 8-4-2=2, would throw.
  
  // Let me reconsider. Let's make it simpler:
  // size = 10
  // Directory offset (last 4 bytes, index 6..9) = 4
  // count at offset 4 (index 4..5) = 0
  byte data2[10];
  memset(data2, 0, sizeof(data2));
  putUShortLE(data2 + 4, 0); // count = 0
  putULongLE(data2 + 6, 4);  // directory offset = 4
  
  EXPECT_NO_THROW(dir_.readDirectory(data2, 10, littleEndian));
}

// Test multiple entries
TEST_F(CiffDirectoryTest_1774, ReadDirectoryMultipleEntries_1774) {
  // 2 entries: need 2 + 2*10 = 22 bytes for directory, plus 4 for offset = 26
  // Place directory at offset 0
  const size_t totalSize = 26;
  byte data[totalSize];
  memset(data, 0, sizeof(data));
  
  putUShortLE(data, 2); // count = 2
  
  // Entry 1 at offset 2
  putUShortLE(data + 2, 0x0000);
  putULongLE(data + 4, 0);
  putULongLE(data + 8, 0);
  
  // Entry 2 at offset 12
  putUShortLE(data + 12, 0x0001);
  putULongLE(data + 14, 0);
  putULongLE(data + 18, 0);
  
  // Directory offset at last 4 bytes (22..25)
  putULongLE(data + 22, 0);
  
  EXPECT_NO_THROW(dir_.readDirectory(data, totalSize, littleEndian));
}

// Test that offset equal to size-1 (> size-2) throws
TEST_F(CiffDirectoryTest_1774, ReadDirectoryOffsetEqualSizeMinus1Throws_1774) {
  byte data[8];
  memset(data, 0, sizeof(data));
  // size = 8, size-2 = 6, set offset = 7 (> 6, should throw)
  // Last 4 bytes at index 4..7
  putULongLE(data + 4, 7);
  
  EXPECT_THROW(dir_.readDirectory(data, 8, littleEndian), Error);
}

// Test that a very large offset throws
TEST_F(CiffDirectoryTest_1774, ReadDirectoryVeryLargeOffsetThrows_1774) {
  byte data[8];
  memset(data, 0, sizeof(data));
  putULongLE(data + 4, 0xFFFFFFFF);
  
  EXPECT_THROW(dir_.readDirectory(data, 8, littleEndian), Error);
}

// Test that count causing overflow in count*10 is handled
TEST_F(CiffDirectoryTest_1774, ReadDirectoryLargeCountThrows_1774) {
  // size = 20, directory at offset 0
  // count = 0xFFFF (65535), count*10 would overflow or be very large
  byte data[20];
  memset(data, 0, sizeof(data));
  putUShortLE(data, 0xFFFF); // very large count
  putULongLE(data + 16, 0);  // directory offset = 0
  
  EXPECT_THROW(dir_.readDirectory(data, 20, littleEndian), Error);
}

// Test empty() on fresh directory
TEST_F(CiffDirectoryTest_1774, EmptyOnFreshDirectory_1774) {
  EXPECT_TRUE(dir_.empty());
}

// Test empty() after reading zero entries
TEST_F(CiffDirectoryTest_1774, EmptyAfterReadingZeroEntries_1774) {
  byte data[6];
  memset(data, 0, sizeof(data));
  putUShortLE(data, 0);
  putULongLE(data + 2, 0);
  
  dir_.readDirectory(data, 6, littleEndian);
  EXPECT_TRUE(dir_.empty());
}

// Test that after reading valid entries, directory is not empty
TEST_F(CiffDirectoryTest_1774, NotEmptyAfterReadingEntries_1774) {
  const size_t totalSize = 16;
  byte data[totalSize];
  memset(data, 0, sizeof(data));
  
  putUShortLE(data, 1);
  putUShortLE(data + 2, 0x0000);
  putULongLE(data + 4, 0);
  putULongLE(data + 8, 0);
  putULongLE(data + 12, 0);
  
  dir_.readDirectory(data, totalSize, littleEndian);
  EXPECT_FALSE(dir_.empty());
}
