#include <gtest/gtest.h>
#include <memory>
#include <cstdint>
#include <string>

#include "makernote_int.hpp"
#include "types.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffMnCreatorTest_1431 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test that creating a makernote with a known manufacturer (e.g., "Canon") returns non-null
TEST_F(TiffMnCreatorTest_1431, CreateWithKnownMake_ReturnsNonNull_1431) {
  const uint16_t tag = 0x927c;  // MakerNote tag
  const IfdId group = IfdId::exifId;
  const std::string make = "Canon";
  const byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t size = sizeof(data);
  const ByteOrder byteOrder = littleEndian;

  auto result = TiffMnCreator::create(tag, group, make, data, size, byteOrder);
  // Canon is a well-known manufacturer; should create a valid makernote
  EXPECT_NE(result, nullptr);
}

// Test that creating a makernote with an unknown manufacturer returns nullptr
TEST_F(TiffMnCreatorTest_1431, CreateWithUnknownMake_ReturnsNull_1431) {
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const std::string make = "UnknownManufacturerXYZ123456";
  const byte data[] = {0x00, 0x00, 0x00, 0x00};
  const size_t size = sizeof(data);
  const ByteOrder byteOrder = littleEndian;

  auto result = TiffMnCreator::create(tag, group, make, data, size, byteOrder);
  EXPECT_EQ(result, nullptr);
}

// Test that creating a makernote with an empty make string returns nullptr
TEST_F(TiffMnCreatorTest_1431, CreateWithEmptyMake_ReturnsNull_1431) {
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const std::string make = "";
  const byte data[] = {0x00, 0x00, 0x00, 0x00};
  const size_t size = sizeof(data);
  const ByteOrder byteOrder = littleEndian;

  auto result = TiffMnCreator::create(tag, group, make, data, size, byteOrder);
  EXPECT_EQ(result, nullptr);
}

// Test with Nikon make and appropriate header data
TEST_F(TiffMnCreatorTest_1431, CreateWithNikonMake_1431) {
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const std::string make = "Nikon";
  // Nikon makernote header: "Nikon\0\x02\x10\0\0" followed by TIFF header
  const byte data[] = {'N', 'i', 'k', 'o', 'n', 0x00, 0x02, 0x10,
                       0x00, 0x00, 'M', 'M', 0x00, 0x2a, 0x00, 0x00,
                       0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t size = sizeof(data);
  const ByteOrder byteOrder = bigEndian;

  auto result = TiffMnCreator::create(tag, group, make, data, size, byteOrder);
  // Nikon is a known make, should produce a result (may or may not be null depending on header validation)
  // We just verify the call doesn't crash
  // Result may be non-null if the header matches
}

// Test with Sony make
TEST_F(TiffMnCreatorTest_1431, CreateWithSonyMake_1431) {
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const std::string make = "Sony";
  const byte data[] = {'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C',
                       ' ', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t size = sizeof(data);
  const ByteOrder byteOrder = littleEndian;

  auto result = TiffMnCreator::create(tag, group, make, data, size, byteOrder);
  // Sony is known; result depends on header matching
}

// Test with big endian byte order
TEST_F(TiffMnCreatorTest_1431, CreateWithBigEndianByteOrder_1431) {
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const std::string make = "Canon";
  const byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t size = sizeof(data);
  const ByteOrder byteOrder = bigEndian;

  auto result = TiffMnCreator::create(tag, group, make, data, size, byteOrder);
  EXPECT_NE(result, nullptr);
}

// Test with zero size data
TEST_F(TiffMnCreatorTest_1431, CreateWithZeroSizeData_1431) {
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const std::string make = "Canon";
  const byte* data = nullptr;
  const size_t size = 0;
  const ByteOrder byteOrder = littleEndian;

  // Should not crash, may return nullptr or valid object
  auto result = TiffMnCreator::create(tag, group, make, data, size, byteOrder);
  // With zero data, the factory may still create an object or return nullptr
}

// Test the IfdId-based overload of create
TEST_F(TiffMnCreatorTest_1431, CreateByMnGroup_1431) {
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const IfdId mnGroup = IfdId::canonId;

  auto result = TiffMnCreator::create(tag, group, mnGroup);
  // Canon maker note group should be recognized
  EXPECT_NE(result, nullptr);
}

// Test the IfdId-based overload with an unknown/invalid IfdId
TEST_F(TiffMnCreatorTest_1431, CreateByMnGroup_UnknownGroup_ReturnsNull_1431) {
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const IfdId mnGroup = IfdId::lastId;  // An invalid/last sentinel value

  auto result = TiffMnCreator::create(tag, group, mnGroup);
  EXPECT_EQ(result, nullptr);
}

// Test with different tag values
TEST_F(TiffMnCreatorTest_1431, CreateWithDifferentTag_1431) {
  const uint16_t tag = 0x0001;  // Not the standard MakerNote tag
  const IfdId group = IfdId::exifId;
  const std::string make = "Canon";
  const byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t size = sizeof(data);
  const ByteOrder byteOrder = littleEndian;

  // The tag value shouldn't prevent creation if the make is known
  auto result = TiffMnCreator::create(tag, group, make, data, size, byteOrder);
  // May or may not be null depending on implementation
}

// Test case-sensitivity of make string (if applicable)
TEST_F(TiffMnCreatorTest_1431, CreateWithLowerCaseMake_1431) {
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const std::string make = "canon";  // lowercase
  const byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t size = sizeof(data);
  const ByteOrder byteOrder = littleEndian;

  auto result = TiffMnCreator::create(tag, group, make, data, size, byteOrder);
  // Registry may do prefix matching; lowercase might not match
  // Just checking it doesn't crash
}

// Test with Fujifilm make and appropriate header
TEST_F(TiffMnCreatorTest_1431, CreateWithFujifilmMake_1431) {
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const std::string make = "Fujifilm";
  const byte data[] = {'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M',
                       0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t size = sizeof(data);
  const ByteOrder byteOrder = littleEndian;

  auto result = TiffMnCreator::create(tag, group, make, data, size, byteOrder);
  // Fujifilm is a known make
}

// Test with Olympus make
TEST_F(TiffMnCreatorTest_1431, CreateWithOlympusMake_1431) {
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const std::string make = "Olympus";
  const byte data[] = {'O', 'L', 'Y', 'M', 'P', 0x00, 'I', 'I',
                       0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t size = sizeof(data);
  const ByteOrder byteOrder = littleEndian;

  auto result = TiffMnCreator::create(tag, group, make, data, size, byteOrder);
  // Olympus is a known make
}

// Test with Panasonic make
TEST_F(TiffMnCreatorTest_1431, CreateWithPanasonicMake_1431) {
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const std::string make = "Panasonic";
  const byte data[] = {'P', 'a', 'n', 'a', 's', 'o', 'n', 'i',
                       'c', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t size = sizeof(data);
  const ByteOrder byteOrder = littleEndian;

  auto result = TiffMnCreator::create(tag, group, make, data, size, byteOrder);
  // Panasonic is a known make
}

// Test with very small data (1 byte)
TEST_F(TiffMnCreatorTest_1431, CreateWithMinimalData_1431) {
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const std::string make = "Canon";
  const byte data[] = {0x00};
  const size_t size = 1;
  const ByteOrder byteOrder = littleEndian;

  // Should not crash even with minimal data
  auto result = TiffMnCreator::create(tag, group, make, data, size, byteOrder);
}

// Test TiffMnRegistry operator== with string_view
TEST_F(TiffMnCreatorTest_1431, RegistryEqualityWithStringView_1431) {
  // This tests the basic behavior that the registry can match makes
  // We test indirectly through the create function
  const uint16_t tag = 0x927c;
  const IfdId group = IfdId::exifId;
  const byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t size = sizeof(data);

  // A make that starts with "Canon" should match
  auto result1 = TiffMnCreator::create(tag, group, "Canon EOS", data, size, littleEndian);
  // Canon is prefix-matched, so "Canon EOS" should also work
}
