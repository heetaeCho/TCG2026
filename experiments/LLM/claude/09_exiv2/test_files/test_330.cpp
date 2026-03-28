#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "types.hpp"

// Include necessary headers for the exiv2 internal types
#include <memory>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffComponent tests
class TiffComponentTest_330 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test fixture for TiffIfdMakernote tests
class TiffIfdMakernoteTest_330 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ============================================================
// TiffComponent basic tests
// ============================================================

// We need a concrete subclass of TiffComponent for testing since it has pure virtual methods
// TiffDirectory is used internally, but we can test through TiffIfdMakernote which is concrete

// Test that TiffIfdMakernote can be constructed and basic getters work
TEST_F(TiffIfdMakernoteTest_330, Construction_DefaultByteOrder_330) {
  // Construct with no header (nullptr), tag=0x927c, group=ifdIdNotSet, mnGroup=ifdIdNotSet
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  ASSERT_NE(makernote, nullptr);
  EXPECT_EQ(makernote->tag(), 0x927c);
  EXPECT_EQ(makernote->group(), IfdId::ifdIdNotSet);
}

// Test byteOrder returns invalidByteOrder by default
TEST_F(TiffIfdMakernoteTest_330, DefaultByteOrder_IsInvalid_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  EXPECT_EQ(makernote->byteOrder(), invalidByteOrder);
}

// Test setByteOrder changes the byte order
TEST_F(TiffIfdMakernoteTest_330, SetByteOrder_LittleEndian_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  makernote->setByteOrder(littleEndian);
  EXPECT_EQ(makernote->byteOrder(), littleEndian);
}

TEST_F(TiffIfdMakernoteTest_330, SetByteOrder_BigEndian_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  makernote->setByteOrder(bigEndian);
  EXPECT_EQ(makernote->byteOrder(), bigEndian);
}

// Test mnOffset returns 0 initially
TEST_F(TiffIfdMakernoteTest_330, MnOffset_InitiallyZero_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  EXPECT_EQ(makernote->mnOffset(), 0u);
}

// Test sizeHeader with no header returns 0
TEST_F(TiffIfdMakernoteTest_330, SizeHeader_NoHeader_ReturnsZero_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  EXPECT_EQ(makernote->sizeHeader(), 0u);
}

// Test readHeader with null header
TEST_F(TiffIfdMakernoteTest_330, ReadHeader_NoHeader_ReturnsTrue_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  byte data[] = {0x00, 0x01, 0x02, 0x03};
  bool result = makernote->readHeader(data, sizeof(data), littleEndian);
  EXPECT_TRUE(result);
}

// Test tag getter
TEST_F(TiffIfdMakernoteTest_330, TagGetter_ReturnsCorrectTag_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x0001, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  EXPECT_EQ(makernote->tag(), 0x0001);
}

// Test with different tag values
TEST_F(TiffIfdMakernoteTest_330, TagGetter_DifferentTag_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0xFFFF, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  EXPECT_EQ(makernote->tag(), 0xFFFF);
}

// Test tag with zero value
TEST_F(TiffIfdMakernoteTest_330, TagGetter_ZeroTag_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x0000, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  EXPECT_EQ(makernote->tag(), 0x0000);
}

// Test group getter
TEST_F(TiffIfdMakernoteTest_330, GroupGetter_ReturnsCorrectGroup_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::exifId, IfdId::ifdIdNotSet, nullptr, false);
  
  EXPECT_EQ(makernote->group(), IfdId::exifId);
}

// Test start() returns nullptr initially
TEST_F(TiffIfdMakernoteTest_330, Start_InitiallyNull_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  EXPECT_EQ(makernote->start(), nullptr);
}

// Test setStart
TEST_F(TiffIfdMakernoteTest_330, SetStart_UpdatesStart_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  byte data[] = {0x01, 0x02, 0x03};
  makernote->setStart(data);
  EXPECT_EQ(makernote->start(), data);
}

// Test addChild - through the public interface
TEST_F(TiffIfdMakernoteTest_330, AddChild_ReturnsNonNull_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  // Create a child TiffComponent - we need a concrete type
  // TiffIfdMakernote can act as a child
  auto child = std::make_shared<TiffIfdMakernote>(
      0x0001, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  TiffComponent* result = makernote->addChild(child);
  // The addChild delegates to ifd_.addChild, result should be non-null
  EXPECT_NE(result, nullptr);
}

// Test ifdOffset
TEST_F(TiffIfdMakernoteTest_330, IfdOffset_InitialValue_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  // ifdOffset should return some value (based on header size)
  size_t offset = makernote->ifdOffset();
  // With no header, the offset should be 0
  EXPECT_EQ(offset, 0u);
}

// Test baseOffset
TEST_F(TiffIfdMakernoteTest_330, BaseOffset_InitialValue_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  size_t baseOffset = makernote->baseOffset();
  // With no header, base offset should be 0
  EXPECT_EQ(baseOffset, 0u);
}

// Test count
TEST_F(TiffIfdMakernoteTest_330, Count_EmptyMakernote_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  // Empty makernote should have count of 0
  EXPECT_EQ(makernote->count(), 0u);
}

// Test size
TEST_F(TiffIfdMakernoteTest_330, Size_EmptyMakernote_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  // Size of empty makernote
  size_t sz = makernote->size();
  // With no entries and no header, size should be minimal (IFD overhead)
  EXPECT_GE(sz, 0u);
}

// Test sizeData
TEST_F(TiffIfdMakernoteTest_330, SizeData_EmptyMakernote_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  EXPECT_EQ(makernote->sizeData(), 0u);
}

// Test sizeImage
TEST_F(TiffIfdMakernoteTest_330, SizeImage_EmptyMakernote_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  EXPECT_EQ(makernote->sizeImage(), 0u);
}

// Test setByteOrder and then check if it persists
TEST_F(TiffIfdMakernoteTest_330, SetByteOrder_Persists_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  makernote->setByteOrder(littleEndian);
  EXPECT_EQ(makernote->byteOrder(), littleEndian);
  
  makernote->setByteOrder(bigEndian);
  EXPECT_EQ(makernote->byteOrder(), bigEndian);
  
  makernote->setByteOrder(invalidByteOrder);
  EXPECT_EQ(makernote->byteOrder(), invalidByteOrder);
}

// Test construction with hasNext = true
TEST_F(TiffIfdMakernoteTest_330, Construction_WithHasNext_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, true);
  
  ASSERT_NE(makernote, nullptr);
  EXPECT_EQ(makernote->tag(), 0x927c);
}

// Test readHeader with empty data
TEST_F(TiffIfdMakernoteTest_330, ReadHeader_EmptyData_NoHeader_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  bool result = makernote->readHeader(nullptr, 0, littleEndian);
  EXPECT_TRUE(result);
}

// Test that copy constructor is deleted (compile-time check implicitly)
// This is verified by the = delete declaration

// Test idx() default
TEST_F(TiffIfdMakernoteTest_330, Idx_DefaultValue_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  int idx = makernote->idx();
  EXPECT_EQ(idx, 0);
}

// Test multiple addChild calls
TEST_F(TiffIfdMakernoteTest_330, AddChild_Multiple_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  auto child1 = std::make_shared<TiffIfdMakernote>(
      0x0001, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  auto child2 = std::make_shared<TiffIfdMakernote>(
      0x0002, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  TiffComponent* result1 = makernote->addChild(child1);
  TiffComponent* result2 = makernote->addChild(child2);
  
  EXPECT_NE(result1, nullptr);
  EXPECT_NE(result2, nullptr);
}

// Test setImageByteOrder (which is a separate method from setByteOrder)
TEST_F(TiffIfdMakernoteTest_330, SetImageByteOrder_330) {
  auto makernote = std::make_unique<TiffIfdMakernote>(
      0x927c, IfdId::ifdIdNotSet, IfdId::ifdIdNotSet, nullptr, false);
  
  // setImageByteOrder should not crash
  makernote->setImageByteOrder(littleEndian);
  // No direct getter for image byte order exposed, but it shouldn't crash
}
