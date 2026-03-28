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

class NewCasioMnTest_1533 : public ::testing::Test {
 protected:
  static constexpr uint16_t testTag = 0x927c;
  static constexpr IfdId testGroup = IfdId::exifId;
  static constexpr IfdId testMnGroup = IfdId::ifd0Id;
  static constexpr ByteOrder testByteOrder = littleEndian;
};

// Test: When data starts with "QVC\0\0\0" (Casio2 marker), should return a valid makernote
TEST_F(NewCasioMnTest_1533, Casio2MakernoteWithQVCHeader_1533) {
  // "QVC\0\0\0" followed by additional data (size > 6)
  std::vector<byte> data = {'Q', 'V', 'C', 0x00, 0x00, 0x00, 0x01, 0x02};
  auto result = newCasioMn(testTag, testGroup, testMnGroup, data.data(), data.size(), testByteOrder);
  EXPECT_NE(result, nullptr);
}

// Test: When data starts with "QVC\0\0\0" and size is exactly 7 (> 6), should return Casio2 makernote
TEST_F(NewCasioMnTest_1533, Casio2MakernoteMinimalSizeAbove6_1533) {
  std::vector<byte> data = {'Q', 'V', 'C', 0x00, 0x00, 0x00, 0xFF};
  auto result = newCasioMn(testTag, testGroup, testMnGroup, data.data(), data.size(), testByteOrder);
  EXPECT_NE(result, nullptr);
}

// Test: When data starts with "QVC\0\0\0" but size is exactly 6 (not > 6), should NOT match QVC branch
// and since size < 14, should return nullptr
TEST_F(NewCasioMnTest_1533, QVCHeaderExactly6BytesReturnsNull_1533) {
  std::vector<byte> data = {'Q', 'V', 'C', 0x00, 0x00, 0x00};
  auto result = newCasioMn(testTag, testGroup, testMnGroup, data.data(), data.size(), testByteOrder);
  EXPECT_EQ(result, nullptr);
}

// Test: When size < 14 and no QVC header, should return nullptr
TEST_F(NewCasioMnTest_1533, SmallSizeNoQVCReturnsNull_1533) {
  std::vector<byte> data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D};
  ASSERT_EQ(data.size(), 13u);  // < 14
  auto result = newCasioMn(testTag, testGroup, testMnGroup, data.data(), data.size(), testByteOrder);
  EXPECT_EQ(result, nullptr);
}

// Test: When size == 14 and no QVC header, should return a Casio IFD makernote (not nullptr)
TEST_F(NewCasioMnTest_1533, Size14NoQVCReturnsCasioMakernote_1533) {
  std::vector<byte> data(14, 0x42);  // 14 bytes of arbitrary non-QVC data
  auto result = newCasioMn(testTag, testGroup, testMnGroup, data.data(), data.size(), testByteOrder);
  EXPECT_NE(result, nullptr);
}

// Test: When size > 14 and no QVC header, should return a Casio IFD makernote
TEST_F(NewCasioMnTest_1533, LargeSizeNoQVCReturnsCasioMakernote_1533) {
  std::vector<byte> data(100, 0xAB);
  auto result = newCasioMn(testTag, testGroup, testMnGroup, data.data(), data.size(), testByteOrder);
  EXPECT_NE(result, nullptr);
}

// Test: Size 0 should return nullptr (size < 14 and not > 6 for QVC check)
TEST_F(NewCasioMnTest_1533, ZeroSizeReturnsNull_1533) {
  auto result = newCasioMn(testTag, testGroup, testMnGroup, nullptr, 0, testByteOrder);
  EXPECT_EQ(result, nullptr);
}

// Test: Data that starts with "QVC" but doesn't have null bytes should not match QVC branch
TEST_F(NewCasioMnTest_1533, QVCWithoutNullBytesNoMatch_1533) {
  // "QVCABC" + extra data - this won't match "QVC\0\0\0"
  std::vector<byte> data = {'Q', 'V', 'C', 'A', 'B', 'C', 'D', 'E',
                             'F', 'G', 'H', 'I', 'J', 'K'};
  ASSERT_EQ(data.size(), 14u);
  auto result = newCasioMn(testTag, testGroup, testMnGroup, data.data(), data.size(), testByteOrder);
  // Not QVC match, size >= 14 -> returns Casio IFD makernote
  EXPECT_NE(result, nullptr);
}

// Test: Partial QVC match should not be treated as Casio2
TEST_F(NewCasioMnTest_1533, PartialQVCMatchNoQVCBranch_1533) {
  // "QV\0\0\0\0" - starts with QV but not QVC
  std::vector<byte> data = {'Q', 'V', 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
                             0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  auto result = newCasioMn(testTag, testGroup, testMnGroup, data.data(), data.size(), testByteOrder);
  // Not a QVC match, but size >= 14, so should return Casio IFD makernote
  EXPECT_NE(result, nullptr);
}

// Test: Size exactly 13 (boundary: one less than 14) with no QVC header returns nullptr
TEST_F(NewCasioMnTest_1533, BoundarySize13ReturnsNull_1533) {
  std::vector<byte> data(13, 0x00);
  auto result = newCasioMn(testTag, testGroup, testMnGroup, data.data(), data.size(), testByteOrder);
  EXPECT_EQ(result, nullptr);
}

// Test: QVC header with size exactly 7 (boundary > 6) returns Casio2 makernote
TEST_F(NewCasioMnTest_1533, QVCBoundarySize7ReturnsCasio2_1533) {
  std::vector<byte> data = {'Q', 'V', 'C', 0x00, 0x00, 0x00, 0x00};
  ASSERT_EQ(data.size(), 7u);
  auto result = newCasioMn(testTag, testGroup, testMnGroup, data.data(), data.size(), testByteOrder);
  EXPECT_NE(result, nullptr);
}

// Test: BigEndian byte order should also work (QVC path)
TEST_F(NewCasioMnTest_1533, QVCWithBigEndian_1533) {
  std::vector<byte> data = {'Q', 'V', 'C', 0x00, 0x00, 0x00, 0x01, 0x02};
  auto result = newCasioMn(testTag, testGroup, testMnGroup, data.data(), data.size(), bigEndian);
  EXPECT_NE(result, nullptr);
}

// Test: BigEndian byte order for standard Casio makernote (non-QVC, size >= 14)
TEST_F(NewCasioMnTest_1533, NonQVCBigEndian_1533) {
  std::vector<byte> data(20, 0x55);
  auto result = newCasioMn(testTag, testGroup, testMnGroup, data.data(), data.size(), bigEndian);
  EXPECT_NE(result, nullptr);
}

// Test: Size 1 returns nullptr
TEST_F(NewCasioMnTest_1533, Size1ReturnsNull_1533) {
  byte data = 0x42;
  auto result = newCasioMn(testTag, testGroup, testMnGroup, &data, 1, testByteOrder);
  EXPECT_EQ(result, nullptr);
}

// Test: QVC header with large buffer should return Casio2 makernote (QVC takes priority over size >= 14)
TEST_F(NewCasioMnTest_1533, QVCWithLargeBufferReturnsCasio2_1533) {
  std::vector<byte> data(1000, 0x00);
  data[0] = 'Q';
  data[1] = 'V';
  data[2] = 'C';
  // data[3..5] are already 0x00
  auto result = newCasioMn(testTag, testGroup, testMnGroup, data.data(), data.size(), testByteOrder);
  EXPECT_NE(result, nullptr);
}
