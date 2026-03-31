#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffImageSizeTest_266 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that newTiffImageSize returns a non-null pointer
TEST_F(TiffImageSizeTest_266, ReturnsNonNullPointer_266) {
  auto result = newTiffImageSize<0x0100, IfdId::ifd0Id>(0x0101, IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
}

// Test that the returned component has the correct tag
TEST_F(TiffImageSizeTest_266, CorrectTag_266) {
  const uint16_t expectedTag = 0x0101;
  auto result = newTiffImageSize<0x0100, IfdId::ifd0Id>(expectedTag, IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), expectedTag);
}

// Test that the returned component has the correct group
TEST_F(TiffImageSizeTest_266, CorrectGroup_266) {
  const IfdId expectedGroup = IfdId::ifd0Id;
  auto result = newTiffImageSize<0x0100, IfdId::ifd0Id>(0x0101, expectedGroup);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->group(), expectedGroup);
}

// Test with different tag values
TEST_F(TiffImageSizeTest_266, DifferentTagValues_266) {
  auto result1 = newTiffImageSize<0x0100, IfdId::ifd0Id>(0x0000, IfdId::ifd0Id);
  ASSERT_NE(result1, nullptr);
  EXPECT_EQ(result1->tag(), 0x0000);

  auto result2 = newTiffImageSize<0x0100, IfdId::ifd0Id>(0xFFFF, IfdId::ifd0Id);
  ASSERT_NE(result2, nullptr);
  EXPECT_EQ(result2->tag(), 0xFFFF);
}

// Test with different group values
TEST_F(TiffImageSizeTest_266, DifferentGroupValues_266) {
  auto result1 = newTiffImageSize<0x0100, IfdId::ifd0Id>(0x0101, IfdId::exifId);
  ASSERT_NE(result1, nullptr);
  EXPECT_EQ(result1->group(), IfdId::exifId);

  auto result2 = newTiffImageSize<0x0100, IfdId::ifd0Id>(0x0101, IfdId::ifd1Id);
  ASSERT_NE(result2, nullptr);
  EXPECT_EQ(result2->group(), IfdId::ifd1Id);
}

// Test with different template parameters
TEST_F(TiffImageSizeTest_266, DifferentTemplateParams_266) {
  auto result1 = newTiffImageSize<0x0201, IfdId::ifd1Id>(0x0202, IfdId::ifd1Id);
  ASSERT_NE(result1, nullptr);
  EXPECT_EQ(result1->tag(), 0x0202);
  EXPECT_EQ(result1->group(), IfdId::ifd1Id);
}

// Test boundary: tag value 0
TEST_F(TiffImageSizeTest_266, BoundaryTagZero_266) {
  auto result = newTiffImageSize<0x0000, IfdId::ifd0Id>(0x0000, IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), 0x0000);
}

// Test boundary: max tag value
TEST_F(TiffImageSizeTest_266, BoundaryTagMax_266) {
  auto result = newTiffImageSize<0xFFFF, IfdId::ifd0Id>(0xFFFF, IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), 0xFFFF);
}

// Test that multiple calls produce independent objects
TEST_F(TiffImageSizeTest_266, IndependentObjects_266) {
  auto result1 = newTiffImageSize<0x0100, IfdId::ifd0Id>(0x0101, IfdId::ifd0Id);
  auto result2 = newTiffImageSize<0x0100, IfdId::ifd0Id>(0x0102, IfdId::ifd0Id);
  ASSERT_NE(result1, nullptr);
  ASSERT_NE(result2, nullptr);
  EXPECT_NE(result1.get(), result2.get());
  EXPECT_EQ(result1->tag(), 0x0101);
  EXPECT_EQ(result2->tag(), 0x0102);
}
