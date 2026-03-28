#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from exiv2
#include "tiffcomposite_int.hpp"
#include "types.hpp"
#include "tags_int.hpp"

namespace Exiv2 {
namespace Internal {

// Test fixture for TiffDirectory and newTiffDirectory tests
class TiffDirectoryTest_258 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that newTiffDirectory returns a non-null unique_ptr
TEST_F(TiffDirectoryTest_258, ReturnsNonNull_258) {
  auto result = newTiffDirectory<IfdId::ifd0Id>(0x0100, IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
}

// Test that newTiffDirectory creates a TiffDirectory with the correct tag
TEST_F(TiffDirectoryTest_258, CorrectTag_258) {
  const uint16_t testTag = 0x0110;
  auto result = newTiffDirectory<IfdId::ifd0Id>(testTag, IfdId::ifd1Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), testTag);
}

// Test that newTiffDirectory creates a TiffDirectory with the new group (template parameter)
TEST_F(TiffDirectoryTest_258, CorrectGroup_258) {
  auto result = newTiffDirectory<IfdId::exifId>(0x8769, IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  // The group should be the template parameter (newGroup), not the function parameter
  EXPECT_EQ(result->group(), IfdId::exifId);
}

// Test with tag value of 0 (boundary)
TEST_F(TiffDirectoryTest_258, ZeroTag_258) {
  auto result = newTiffDirectory<IfdId::ifd0Id>(0x0000, IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), 0x0000);
}

// Test with maximum tag value (boundary)
TEST_F(TiffDirectoryTest_258, MaxTag_258) {
  auto result = newTiffDirectory<IfdId::ifd0Id>(0xFFFF, IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), 0xFFFF);
}

// Test that the group parameter is ignored (newGroup template param is used instead)
TEST_F(TiffDirectoryTest_258, GroupParameterIgnored_258) {
  auto result1 = newTiffDirectory<IfdId::exifId>(0x0100, IfdId::ifd0Id);
  auto result2 = newTiffDirectory<IfdId::exifId>(0x0100, IfdId::gpsId);
  ASSERT_NE(result1, nullptr);
  ASSERT_NE(result2, nullptr);
  // Both should have the same group (the template parameter), regardless of the function parameter
  EXPECT_EQ(result1->group(), result2->group());
  EXPECT_EQ(result1->group(), IfdId::exifId);
}

// Test with different template group parameters
TEST_F(TiffDirectoryTest_258, DifferentTemplateGroups_258) {
  auto resultIfd0 = newTiffDirectory<IfdId::ifd0Id>(0x0100, IfdId::ifd0Id);
  auto resultExif = newTiffDirectory<IfdId::exifId>(0x0100, IfdId::ifd0Id);
  auto resultGps = newTiffDirectory<IfdId::gpsId>(0x0100, IfdId::ifd0Id);

  ASSERT_NE(resultIfd0, nullptr);
  ASSERT_NE(resultExif, nullptr);
  ASSERT_NE(resultGps, nullptr);

  EXPECT_EQ(resultIfd0->group(), IfdId::ifd0Id);
  EXPECT_EQ(resultExif->group(), IfdId::exifId);
  EXPECT_EQ(resultGps->group(), IfdId::gpsId);
}

// Test with ifd1Id template parameter
TEST_F(TiffDirectoryTest_258, Ifd1Group_258) {
  auto result = newTiffDirectory<IfdId::ifd1Id>(0x0201, IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), 0x0201);
  EXPECT_EQ(result->group(), IfdId::ifd1Id);
}

// Test that each call returns a distinct object (unique ownership)
TEST_F(TiffDirectoryTest_258, UniqueOwnership_258) {
  auto result1 = newTiffDirectory<IfdId::ifd0Id>(0x0100, IfdId::ifd0Id);
  auto result2 = newTiffDirectory<IfdId::ifd0Id>(0x0100, IfdId::ifd0Id);
  ASSERT_NE(result1, nullptr);
  ASSERT_NE(result2, nullptr);
  EXPECT_NE(result1.get(), result2.get());
}

// Test TiffDirectory direct construction
TEST_F(TiffDirectoryTest_258, DirectConstruction_258) {
  TiffDirectory dir(0x0100, IfdId::ifd0Id);
  EXPECT_EQ(dir.tag(), 0x0100);
  EXPECT_EQ(dir.group(), IfdId::ifd0Id);
}

// Test TiffDirectory with different tags
TEST_F(TiffDirectoryTest_258, DirectConstructionDifferentTags_258) {
  TiffDirectory dir1(0x0001, IfdId::ifd0Id);
  TiffDirectory dir2(0x0002, IfdId::ifd0Id);
  EXPECT_EQ(dir1.tag(), 0x0001);
  EXPECT_EQ(dir2.tag(), 0x0002);
  EXPECT_NE(dir1.tag(), dir2.tag());
}

}  // namespace Internal
}  // namespace Exiv2
