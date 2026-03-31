#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewTiffThumbDataTest_263 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that newTiffThumbData returns a non-null pointer
TEST_F(NewTiffThumbDataTest_263, ReturnsNonNullPointer_263) {
  auto result = newTiffThumbData<0x0201, IfdId::ifd1Id>(0x0201, IfdId::ifd1Id);
  ASSERT_NE(result, nullptr);
}

// Test that the returned object has the correct tag
TEST_F(NewTiffThumbDataTest_263, ReturnedObjectHasCorrectTag_263) {
  const uint16_t tag = 0x0201;
  auto result = newTiffThumbData<0x0117, IfdId::ifd1Id>(tag, IfdId::ifd1Id);
  EXPECT_EQ(result->tag(), tag);
}

// Test that the returned object has the correct group
TEST_F(NewTiffThumbDataTest_263, ReturnedObjectHasCorrectGroup_263) {
  const IfdId group = IfdId::ifd1Id;
  auto result = newTiffThumbData<0x0117, IfdId::ifd1Id>(0x0201, group);
  EXPECT_EQ(result->group(), group);
}

// Test with different tag and group values
TEST_F(NewTiffThumbDataTest_263, DifferentTagAndGroupValues_263) {
  const uint16_t tag = 0x0111;
  const IfdId group = IfdId::ifd0Id;
  auto result = newTiffThumbData<0x0117, IfdId::ifd0Id>(tag, group);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), tag);
  EXPECT_EQ(result->group(), group);
}

// Test with zero tag value
TEST_F(NewTiffThumbDataTest_263, ZeroTagValue_263) {
  const uint16_t tag = 0x0000;
  auto result = newTiffThumbData<0x0000, IfdId::ifd1Id>(tag, IfdId::ifd1Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), tag);
}

// Test with maximum uint16_t tag value
TEST_F(NewTiffThumbDataTest_263, MaxTagValue_263) {
  const uint16_t tag = 0xFFFF;
  auto result = newTiffThumbData<0xFFFF, IfdId::ifd1Id>(tag, IfdId::ifd1Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), tag);
}

// Test with different template parameters than runtime parameters
TEST_F(NewTiffThumbDataTest_263, DifferentTemplateAndRuntimeParams_263) {
  const uint16_t szTag = 0x0117;
  const uint16_t runtimeTag = 0x0201;
  auto result = newTiffThumbData<szTag, IfdId::ifd1Id>(runtimeTag, IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), runtimeTag);
  EXPECT_EQ(result->group(), IfdId::ifd0Id);
}

// Test that multiple calls produce independent objects
TEST_F(NewTiffThumbDataTest_263, MultipleCallsProduceIndependentObjects_263) {
  auto result1 = newTiffThumbData<0x0117, IfdId::ifd1Id>(0x0201, IfdId::ifd1Id);
  auto result2 = newTiffThumbData<0x0117, IfdId::ifd1Id>(0x0202, IfdId::ifd1Id);
  ASSERT_NE(result1, nullptr);
  ASSERT_NE(result2, nullptr);
  EXPECT_NE(result1.get(), result2.get());
  EXPECT_EQ(result1->tag(), 0x0201);
  EXPECT_EQ(result2->tag(), 0x0202);
}

// Test with exifId group
TEST_F(NewTiffThumbDataTest_263, ExifIdGroup_263) {
  auto result = newTiffThumbData<0x0201, IfdId::exifId>(0x0201, IfdId::exifId);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->group(), IfdId::exifId);
}
