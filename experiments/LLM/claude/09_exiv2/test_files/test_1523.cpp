#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewPentaxMnTest_1523 : public ::testing::Test {
 protected:
  static constexpr uint16_t testTag = 0x927c;
  static constexpr uint16_t dngTag = 0xc634;
  static constexpr IfdId testGroup = IfdId::exifId;
  static constexpr IfdId testMnGroup = IfdId::mnId;
};

// Test: nullptr returned when data is too small to match any signature
TEST_F(NewPentaxMnTest_1523, NullptrForEmptyData_1523) {
  const byte data[] = {0x00};
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data, 0, littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: nullptr when data is smaller than 4 bytes (can't match AOC or PENTAX)
TEST_F(NewPentaxMnTest_1523, NullptrForTinyData_1523) {
  const byte data[] = {0x41, 0x4F, 0x43};  // "AOC" only 3 bytes
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data, 3, littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: nullptr when data is exactly 4 bytes with AOC\0 but size <= 4 fails "> 4" check
TEST_F(NewPentaxMnTest_1523, NullptrForAOCExactly4Bytes_1523) {
  const byte data[] = {'A', 'O', 'C', 0x00};
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data, 4, littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: nullptr when data starts with AOC\0 but size is too small for header + 18
TEST_F(NewPentaxMnTest_1523, NullptrForAOCTooSmallForHeader_1523) {
  // AOC\0 + a few bytes, but not enough for PentaxMnHeader::sizeOfSignature() + 18
  std::vector<byte> data(10, 0);
  data[0] = 'A';
  data[1] = 'O';
  data[2] = 'C';
  data[3] = 0x00;
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: Valid AOC\0 signature with sufficient data returns non-null
TEST_F(NewPentaxMnTest_1523, ValidAOCSignatureReturnsNonNull_1523) {
  // PentaxMnHeader signature is "AOC\0" (4 bytes), so sizeOfSignature() is likely 4
  // We need at least sizeOfSignature() + 18 bytes
  // Use a generous buffer
  std::vector<byte> data(256, 0);
  data[0] = 'A';
  data[1] = 'O';
  data[2] = 'C';
  data[3] = 0x00;
  // Fill with some plausible TIFF data after signature
  // Put byte order marker
  data[4] = 'I';  // little endian marker
  data[5] = 'I';
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_NE(result, nullptr);
}

// Test: nullptr when data is exactly 8 bytes with PENTAX \0 but size <= 8 fails "> 8" check
TEST_F(NewPentaxMnTest_1523, NullptrForPentaxExactly8Bytes_1523) {
  const byte data[] = {'P', 'E', 'N', 'T', 'A', 'X', ' ', 0x00};
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data, 8, littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: PENTAX \0 signature but size too small for PentaxDngMnHeader::sizeOfSignature() + 18
TEST_F(NewPentaxMnTest_1523, NullptrForPentaxDngTooSmallForHeader_1523) {
  // 9 bytes is > 8 but likely not enough for sizeOfSignature() + 18
  std::vector<byte> data(12, 0);
  data[0] = 'P';
  data[1] = 'E';
  data[2] = 'N';
  data[3] = 'T';
  data[4] = 'A';
  data[5] = 'X';
  data[6] = ' ';
  data[7] = 0x00;
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: Valid PENTAX \0 signature with sufficient data and non-DNG tag returns non-null
TEST_F(NewPentaxMnTest_1523, ValidPentaxSignatureNonDngTagReturnsNonNull_1523) {
  std::vector<byte> data(256, 0);
  data[0] = 'P';
  data[1] = 'E';
  data[2] = 'N';
  data[3] = 'T';
  data[4] = 'A';
  data[5] = 'X';
  data[6] = ' ';
  data[7] = 0x00;
  // Fill some data after signature
  data[8] = 'I';
  data[9] = 'I';
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_NE(result, nullptr);
}

// Test: Valid PENTAX \0 signature with DNG tag (0xc634) returns non-null
TEST_F(NewPentaxMnTest_1523, ValidPentaxSignatureDngTagReturnsNonNull_1523) {
  std::vector<byte> data(256, 0);
  data[0] = 'P';
  data[1] = 'E';
  data[2] = 'N';
  data[3] = 'T';
  data[4] = 'A';
  data[5] = 'X';
  data[6] = ' ';
  data[7] = 0x00;
  data[8] = 'I';
  data[9] = 'I';
  auto result = newPentaxMn(dngTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_NE(result, nullptr);
}

// Test: Data doesn't match any known signature returns nullptr
TEST_F(NewPentaxMnTest_1523, NullptrForUnknownSignature_1523) {
  std::vector<byte> data(256, 0);
  data[0] = 'N';
  data[1] = 'I';
  data[2] = 'K';
  data[3] = 'O';
  data[4] = 'N';
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: Null data pointer with zero size
TEST_F(NewPentaxMnTest_1523, NullptrDataWithZeroSize_1523) {
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, nullptr, 0, littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: PENTAX signature takes precedence over AOC since it's checked first (size > 8)
TEST_F(NewPentaxMnTest_1523, PentaxSignatureCheckedBeforeAOC_1523) {
  // Data starts with "PENTAX \0" - should match PENTAX branch, not AOC
  std::vector<byte> data(256, 0);
  data[0] = 'P';
  data[1] = 'E';
  data[2] = 'N';
  data[3] = 'T';
  data[4] = 'A';
  data[5] = 'X';
  data[6] = ' ';
  data[7] = 0x00;
  data[8] = 'M';
  data[9] = 'M';
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data.data(), data.size(), bigEndian);
  EXPECT_NE(result, nullptr);
}

// Test: Big endian byte order parameter
TEST_F(NewPentaxMnTest_1523, BigEndianAOCReturnsNonNull_1523) {
  std::vector<byte> data(256, 0);
  data[0] = 'A';
  data[1] = 'O';
  data[2] = 'C';
  data[3] = 0x00;
  data[4] = 'M';
  data[5] = 'M';
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data.data(), data.size(), bigEndian);
  EXPECT_NE(result, nullptr);
}

// Test: Data with size exactly 5 and AOC\0 prefix - just above threshold for "> 4"
// but likely below PentaxMnHeader::sizeOfSignature() + 18
TEST_F(NewPentaxMnTest_1523, AOCMinimalSizeAboveThresholdButBelowRequired_1523) {
  std::vector<byte> data(5, 0);
  data[0] = 'A';
  data[1] = 'O';
  data[2] = 'C';
  data[3] = 0x00;
  data[4] = 0x01;
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: Data with size exactly 9 and PENTAX \0 prefix - just above threshold for "> 8"
// but likely below PentaxDngMnHeader::sizeOfSignature() + 18
TEST_F(NewPentaxMnTest_1523, PentaxMinimalSizeAboveThresholdButBelowRequired_1523) {
  std::vector<byte> data(9, 0);
  data[0] = 'P';
  data[1] = 'E';
  data[2] = 'N';
  data[3] = 'T';
  data[4] = 'A';
  data[5] = 'X';
  data[6] = ' ';
  data[7] = 0x00;
  data[8] = 0x01;
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: All zeros in data - should not match any signature
TEST_F(NewPentaxMnTest_1523, AllZerosReturnsNullptr_1523) {
  std::vector<byte> data(256, 0);
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_EQ(result, nullptr);
}

// Test: Data that partially matches "PENTAX" but not fully
TEST_F(NewPentaxMnTest_1523, PartialPentaxMatchReturnsNullptr_1523) {
  std::vector<byte> data(256, 0);
  data[0] = 'P';
  data[1] = 'E';
  data[2] = 'N';
  data[3] = 'T';
  data[4] = 'A';
  data[5] = 'X';
  data[6] = 'X';  // Wrong - should be space
  data[7] = 0x00;
  // Also doesn't match AOC\0
  auto result = newPentaxMn(testTag, testGroup, testMnGroup, data.data(), data.size(), littleEndian);
  EXPECT_EQ(result, nullptr);
}
