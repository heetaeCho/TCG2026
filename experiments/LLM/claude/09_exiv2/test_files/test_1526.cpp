#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewSamsungMnTest_1526 : public ::testing::Test {
 protected:
  static constexpr uint16_t testTag = 0x927c;
  static constexpr IfdId testGroup = IfdId::exifId;
  static constexpr IfdId testMnGroup = IfdId::samsung2Id;
};

// Test: Data starts with "AOC\0" but size is too small for Pentax signature + 18
TEST_F(NewSamsungMnTest_1526, AOCHeaderTooSmallForPentax_1526) {
  // "AOC\0" is 4 bytes, PentaxMnHeader::sizeOfSignature() is likely 4 or more
  // We need size > 4 but < PentaxMnHeader::sizeOfSignature() + 18
  // Use a small buffer with AOC header but not enough data
  std::vector<byte> data = {'A', 'O', 'C', '\0', 0x00};
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: Data starts with "AOC\0" and size is exactly at the boundary (still too small)
TEST_F(NewSamsungMnTest_1526, AOCHeaderBoundaryTooSmall_1526) {
  // Create data with AOC header but size just below threshold
  std::vector<byte> data(10, 0);
  data[0] = 'A';
  data[1] = 'O';
  data[2] = 'C';
  data[3] = '\0';
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: Data starts with "AOC\0" and size is sufficient for Pentax makernote
TEST_F(NewSamsungMnTest_1526, AOCHeaderSufficientSize_1526) {
  // PentaxMnHeader::sizeOfSignature() + 18 should be around 22 or so
  // Make a large enough buffer with AOC header
  std::vector<byte> data(256, 0);
  data[0] = 'A';
  data[1] = 'O';
  data[2] = 'C';
  data[3] = '\0';
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  // Should return a Pentax makernote (non-null)
  EXPECT_NE(result, nullptr);
}

// Test: Non-AOC data with size < 18 returns nullptr
TEST_F(NewSamsungMnTest_1526, NonAOCDataTooSmall_1526) {
  std::vector<byte> data = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: Non-AOC data with size exactly 17 returns nullptr
TEST_F(NewSamsungMnTest_1526, NonAOCDataSize17_1526) {
  std::vector<byte> data(17, 0x42);
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: Non-AOC data with size exactly 18 returns Samsung makernote
TEST_F(NewSamsungMnTest_1526, NonAOCDataSize18_1526) {
  std::vector<byte> data(18, 0x42);
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_NE(result, nullptr);
}

// Test: Non-AOC data with size > 18 returns Samsung makernote
TEST_F(NewSamsungMnTest_1526, NonAOCDataLargeSize_1526) {
  std::vector<byte> data(1024, 0x42);
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_NE(result, nullptr);
}

// Test: Size exactly 4 (not > 4, so AOC check fails), and < 18
TEST_F(NewSamsungMnTest_1526, AOCDataSizeExactly4_1526) {
  std::vector<byte> data = {'A', 'O', 'C', '\0'};
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  // size is 4, not > 4, so AOC branch not taken; size < 18, so returns nullptr
  EXPECT_EQ(result, nullptr);
}

// Test: Size 0 returns nullptr (non-AOC path, size < 18)
TEST_F(NewSamsungMnTest_1526, EmptyData_1526) {
  byte dummy = 0;
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, &dummy, 0, littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: Data that starts with "AOC" but not null-terminated (no '\0' at position 3)
TEST_F(NewSamsungMnTest_1526, AOCWithoutNullTerminator_1526) {
  std::vector<byte> data(256, 0);
  data[0] = 'A';
  data[1] = 'O';
  data[2] = 'C';
  data[3] = 'X';  // Not '\0'
  // AOC check should fail since "AOCX" != "AOC\0"
  // Falls through to Samsung path, size >= 18, so should succeed
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_NE(result, nullptr);
}

// Test: Big endian byte order with non-AOC data
TEST_F(NewSamsungMnTest_1526, BigEndianNonAOC_1526) {
  std::vector<byte> data(64, 0x00);
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, data.data(), data.size(), bigEndian);
  EXPECT_NE(result, nullptr);
}

// Test: Big endian byte order with AOC data and sufficient size
TEST_F(NewSamsungMnTest_1526, BigEndianAOC_1526) {
  std::vector<byte> data(256, 0);
  data[0] = 'A';
  data[1] = 'O';
  data[2] = 'C';
  data[3] = '\0';
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, data.data(), data.size(), bigEndian);
  EXPECT_NE(result, nullptr);
}

// Test: Size exactly 5 with AOC header (> 4 check passes, but too small for Pentax)
TEST_F(NewSamsungMnTest_1526, AOCDataSize5_1526) {
  std::vector<byte> data = {'A', 'O', 'C', '\0', 0x00};
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: Non-AOC data, size exactly 1
TEST_F(NewSamsungMnTest_1526, NonAOCDataSize1_1526) {
  byte data = 0xFF;
  auto result = newSamsungMn(testTag, testGroup, testMnGroup, &data, 1, littleEndian);
  EXPECT_EQ(result, nullptr);
}
