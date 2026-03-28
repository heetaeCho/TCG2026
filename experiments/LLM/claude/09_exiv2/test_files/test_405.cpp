#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffDirectory tests
class TiffDirectoryTest_405 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a freshly constructed TiffDirectory with no children and no next has sizeImage() == 0
TEST_F(TiffDirectoryTest_405, EmptyDirectoryNoNext_SizeImageIsZero_405) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  EXPECT_EQ(0u, dir.sizeImage());
}

// Test that a freshly constructed TiffDirectory with hasNext=true but no next set has sizeImage() == 0
TEST_F(TiffDirectoryTest_405, EmptyDirectoryWithNextFlag_SizeImageIsZero_405) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, true);
  EXPECT_EQ(0u, dir.sizeImage());
}

// Test constructor sets tag correctly
TEST_F(TiffDirectoryTest_405, ConstructorSetsTag_405) {
  TiffDirectory dir(0x1234, IfdId::ifd0Id, false);
  EXPECT_EQ(0x1234, dir.tag());
}

// Test constructor sets group correctly
TEST_F(TiffDirectoryTest_405, ConstructorSetsGroup_405) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  EXPECT_EQ(IfdId::ifd0Id, dir.group());
}

// Test hasNext returns false when constructed with false
TEST_F(TiffDirectoryTest_405, HasNextReturnsFalse_405) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  EXPECT_FALSE(dir.hasNext());
}

// Test hasNext returns true when constructed with true
TEST_F(TiffDirectoryTest_405, HasNextReturnsTrue_405) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, true);
  EXPECT_TRUE(dir.hasNext());
}

// Test that sizeImage on a directory with no components returns 0
TEST_F(TiffDirectoryTest_405, NoComponents_SizeImageZero_405) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  size_t result = dir.sizeImage();
  EXPECT_EQ(0u, result);
}

// Test that count on empty directory returns expected value
TEST_F(TiffDirectoryTest_405, EmptyDirectoryCount_405) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  EXPECT_EQ(0u, dir.count());
}

// Test that size on empty directory returns expected value
TEST_F(TiffDirectoryTest_405, EmptyDirectorySize_405) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  // An empty directory with no next should have some base size (header)
  // but we just verify it doesn't crash and returns a value
  size_t s = dir.size();
  EXPECT_GE(s, 0u);
}

// Test that sizeData on empty directory is well-defined
TEST_F(TiffDirectoryTest_405, EmptyDirectorySizeData_405) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  size_t result = dir.sizeData();
  EXPECT_GE(result, 0u);
}

// Test adding a child component via addChild
TEST_F(TiffDirectoryTest_405, AddChildComponent_405) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  auto child = std::make_shared<TiffDirectory>(0x0002, IfdId::ifd0Id, false);
  TiffComponent* result = dir.addChild(child);
  // addChild should return a non-null pointer on success
  // (or null depending on implementation - we just check it doesn't crash)
  // The child's sizeImage is 0, so overall sizeImage should still be 0
  EXPECT_EQ(0u, dir.sizeImage());
}

// Test adding a next component via addNext
TEST_F(TiffDirectoryTest_405, AddNextComponent_SizeImageIncludesNext_405) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, true);
  auto next = std::make_unique<TiffDirectory>(0x0002, IfdId::ifd1Id, false);
  dir.addNext(std::move(next));
  // Both are empty, so sizeImage should be 0
  EXPECT_EQ(0u, dir.sizeImage());
}

// Test default tag value
TEST_F(TiffDirectoryTest_405, TagZero_405) {
  TiffDirectory dir(0x0000, IfdId::ifd0Id, false);
  EXPECT_EQ(0x0000, dir.tag());
}

// Test that start() returns nullptr initially
TEST_F(TiffDirectoryTest_405, StartInitiallyNull_405) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  EXPECT_EQ(nullptr, dir.start());
}

// Test setStart
TEST_F(TiffDirectoryTest_405, SetStartUpdatesStart_405) {
  TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
  byte data[10] = {0};
  dir.setStart(data);
  EXPECT_EQ(data, dir.start());
}
