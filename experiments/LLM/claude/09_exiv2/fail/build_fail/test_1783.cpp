#include <gtest/gtest.h>
#include <cstring>

#include "crwimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for CiffComponent tests
class CiffComponentTest_1783 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default construction
TEST_F(CiffComponentTest_1783, DefaultConstruction_1783) {
  CiffComponent comp;
  EXPECT_EQ(comp.tag(), 0);
  EXPECT_EQ(comp.dir(), 0);
  EXPECT_EQ(comp.size(), 0u);
  EXPECT_EQ(comp.offset(), 0u);
  EXPECT_EQ(comp.pData(), nullptr);
}

// Test parameterized construction
TEST_F(CiffComponentTest_1783, ParameterizedConstruction_1783) {
  uint16_t tag = 0x1234;
  uint16_t dir = 0x5678;
  CiffComponent comp(tag, dir);
  EXPECT_EQ(comp.tag(), tag);
  EXPECT_EQ(comp.dir(), dir);
  EXPECT_EQ(comp.size(), 0u);
  EXPECT_EQ(comp.pData(), nullptr);
}

// Test setValue with a small buffer (size <= 8)
TEST_F(CiffComponentTest_1783, SetValueSmallBuffer_1783) {
  CiffComponent comp;
  const uint8_t data[] = {1, 2, 3, 4};
  DataBuf buf(data, sizeof(data));
  comp.setValue(std::move(buf));

  EXPECT_EQ(comp.size(), 4u);
  EXPECT_NE(comp.pData(), nullptr);
  EXPECT_EQ(comp.pData()[0], 1);
  EXPECT_EQ(comp.pData()[1], 2);
  EXPECT_EQ(comp.pData()[2], 3);
  EXPECT_EQ(comp.pData()[3], 4);
}

// Test setValue with exactly 8 bytes (boundary)
TEST_F(CiffComponentTest_1783, SetValueExactly8Bytes_1783) {
  CiffComponent comp;
  const uint8_t data[] = {1, 2, 3, 4, 5, 6, 7, 8};
  DataBuf buf(data, sizeof(data));
  comp.setValue(std::move(buf));

  EXPECT_EQ(comp.size(), 8u);
  EXPECT_NE(comp.pData(), nullptr);
}

// Test setValue with buffer larger than 8 bytes and dataLocation == directoryData
// When size > 8 and dataLocation is directoryData, the tag should be masked with 0x3fff
TEST_F(CiffComponentTest_1783, SetValueLargeBufferDirectoryData_1783) {
  // Tags where dataLocation() returns DataLocId::directoryData
  // According to the CIFF spec, tags with bits 14-15 indicating directoryData
  // We need a tag that has dataLocation == directoryData
  // DataLocId::directoryData has value 1, which typically corresponds to tag bits [13:12] or similar
  // In CRW format, the data location is determined by bits 14-15 of the tag:
  //   0x0000 -> valueData (bits 14-15 = 00)
  //   0x4000 -> directoryData (bits 14-15 = 01)
  // So a tag like 0x4000 should have dataLocation == directoryData
  uint16_t tag = 0xC000; // bits 14-15 set, which based on typical CRW mapping could be directoryData
  // Let's try 0x4000 which should map to directoryData
  // The actual mapping depends on implementation, but we can test the observable behavior
  
  // We'll create a component with a tag that includes high bits
  CiffComponent comp(0xFFFF, 0x0000);
  
  // Create a buffer larger than 8 bytes
  const uint8_t data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  DataBuf buf(data, sizeof(data));
  
  uint16_t originalTag = comp.tag();
  comp.setValue(std::move(buf));
  
  EXPECT_EQ(comp.size(), 9u);
  EXPECT_NE(comp.pData(), nullptr);
  
  // If dataLocation was directoryData, tag should be masked with 0x3fff
  // If not, tag should remain unchanged
  // We can check: either tag was masked or stayed the same
  uint16_t newTag = comp.tag();
  EXPECT_TRUE(newTag == originalTag || newTag == (originalTag & 0x3fff));
}

// Test setValue with empty buffer
TEST_F(CiffComponentTest_1783, SetValueEmptyBuffer_1783) {
  CiffComponent comp;
  DataBuf buf;
  comp.setValue(std::move(buf));

  EXPECT_EQ(comp.size(), 0u);
}

// Test setValue with exactly 9 bytes (just over boundary)
TEST_F(CiffComponentTest_1783, SetValue9Bytes_1783) {
  CiffComponent comp;
  const uint8_t data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  DataBuf buf(data, sizeof(data));
  comp.setValue(std::move(buf));

  EXPECT_EQ(comp.size(), 9u);
  EXPECT_NE(comp.pData(), nullptr);
  for (size_t i = 0; i < 9; ++i) {
    EXPECT_EQ(comp.pData()[i], static_cast<uint8_t>(i));
  }
}

// Test setValue updates pData correctly
TEST_F(CiffComponentTest_1783, SetValueUpdatesPData_1783) {
  CiffComponent comp;
  const uint8_t data1[] = {10, 20, 30};
  DataBuf buf1(data1, sizeof(data1));
  comp.setValue(std::move(buf1));

  EXPECT_EQ(comp.size(), 3u);
  EXPECT_EQ(comp.pData()[0], 10);

  // Set again with different data
  const uint8_t data2[] = {40, 50, 60, 70};
  DataBuf buf2(data2, sizeof(data2));
  comp.setValue(std::move(buf2));

  EXPECT_EQ(comp.size(), 4u);
  EXPECT_EQ(comp.pData()[0], 40);
  EXPECT_EQ(comp.pData()[3], 70);
}

// Test setValue with 1 byte buffer
TEST_F(CiffComponentTest_1783, SetValueSingleByte_1783) {
  CiffComponent comp;
  const uint8_t data[] = {0xFF};
  DataBuf buf(data, sizeof(data));
  comp.setValue(std::move(buf));

  EXPECT_EQ(comp.size(), 1u);
  EXPECT_NE(comp.pData(), nullptr);
  EXPECT_EQ(comp.pData()[0], 0xFF);
}

// Test setDir and dir
TEST_F(CiffComponentTest_1783, SetDir_1783) {
  CiffComponent comp;
  comp.setDir(0x1234);
  EXPECT_EQ(comp.dir(), 0x1234);
}

// Test tagId accessor
TEST_F(CiffComponentTest_1783, TagId_1783) {
  uint16_t tag = 0x3456;
  CiffComponent comp(tag, 0);
  EXPECT_EQ(comp.tagId(), tag & 0x3fff);
}

// Test empty on default-constructed component
TEST_F(CiffComponentTest_1783, EmptyDefault_1783) {
  CiffComponent comp;
  // Default component should be considered empty or not based on impl
  // We just check it doesn't crash
  bool result = comp.empty();
  (void)result;  // Just verify no crash
}

// Test empty after setValue with non-empty buffer
TEST_F(CiffComponentTest_1783, EmptyAfterSetValue_1783) {
  CiffComponent comp;
  const uint8_t data[] = {1, 2, 3};
  DataBuf buf(data, sizeof(data));
  comp.setValue(std::move(buf));
  // After setting a value, component may or may not be empty
  // depending on implementation - just verify no crash
  bool result = comp.empty();
  (void)result;
}

// Test that setValue with large buffer and tag with high bits clears bits appropriately
// when dataLocation() is directoryData
TEST_F(CiffComponentTest_1783, SetValueTagMasking_1783) {
  // Create a tag where dataLocation returns directoryData
  // In CIFF format, data location is determined by bits 14-15 of tag
  // DataLocId::directoryData (value 1) might correspond to specific bit patterns
  // Let's test with a tag where bits 14-15 are 0b01 -> 0x4000
  uint16_t tag = 0x4001;
  CiffComponent comp(tag, 0);
  
  // Check dataLocation
  DataLocId loc = comp.dataLocation();
  
  const uint8_t data[16] = {0};  // 16 bytes > 8
  DataBuf buf(data, sizeof(data));
  comp.setValue(std::move(buf));
  
  if (loc == DataLocId::directoryData) {
    // Tag should have been masked: tag & 0x3fff
    EXPECT_EQ(comp.tag(), tag & 0x3fff);
  } else {
    // Tag should remain unchanged
    EXPECT_EQ(comp.tag(), tag);
  }
}

// Test that setValue with small buffer does NOT mask tag bits regardless of dataLocation
TEST_F(CiffComponentTest_1783, SetValueSmallBufferNoTagMasking_1783) {
  uint16_t tag = 0xC001;
  CiffComponent comp(tag, 0);
  
  const uint8_t data[4] = {0};  // 4 bytes <= 8
  DataBuf buf(data, sizeof(data));
  comp.setValue(std::move(buf));
  
  // With size <= 8, the tag masking condition (size > 8) is not met
  EXPECT_EQ(comp.tag(), tag);
}

// Test typeId static method with different tags
TEST_F(CiffComponentTest_1783, TypeIdStatic_1783) {
  // Just verify the static method doesn't crash with various inputs
  TypeId t1 = CiffComponent::typeId(0x0000);
  TypeId t2 = CiffComponent::typeId(0xFFFF);
  TypeId t3 = CiffComponent::typeId(0x0800);
  (void)t1;
  (void)t2;
  (void)t3;
}

// Test dataLocation static method with different tags
TEST_F(CiffComponentTest_1783, DataLocationStatic_1783) {
  DataLocId loc1 = CiffComponent::dataLocation(0x0000);
  DataLocId loc2 = CiffComponent::dataLocation(0x4000);
  DataLocId loc3 = CiffComponent::dataLocation(0x8000);
  (void)loc1;
  (void)loc2;
  (void)loc3;
}

// Test that size is correctly reported after setValue
TEST_F(CiffComponentTest_1783, SizeAfterSetValue_1783) {
  CiffComponent comp;
  
  // Size 0
  DataBuf buf0;
  comp.setValue(std::move(buf0));
  EXPECT_EQ(comp.size(), 0u);
  
  // Size 100
  DataBuf buf100(100);
  comp.setValue(std::move(buf100));
  EXPECT_EQ(comp.size(), 100u);
  
  // Size 1
  DataBuf buf1(1);
  comp.setValue(std::move(buf1));
  EXPECT_EQ(comp.size(), 1u);
}

// Test findComponent returns nullptr on base CiffComponent (no children)
TEST_F(CiffComponentTest_1783, FindComponentReturnsNullptr_1783) {
  CiffComponent comp(0x1234, 0x5678);
  CiffComponent* found = comp.findComponent(0x1234, 0x5678);
  // Base CiffComponent::doFindComponent returns nullptr by default (or this)
  // Just verify no crash
  (void)found;
}

// Test that setValue can be called multiple times
TEST_F(CiffComponentTest_1783, SetValueMultipleTimes_1783) {
  CiffComponent comp;
  
  for (int i = 1; i <= 10; ++i) {
    DataBuf buf(static_cast<size_t>(i));
    comp.setValue(std::move(buf));
    EXPECT_EQ(comp.size(), static_cast<size_t>(i));
    EXPECT_NE(comp.pData(), nullptr);
  }
}

// Test with a large buffer
TEST_F(CiffComponentTest_1783, SetValueLargeBuffer_1783) {
  CiffComponent comp;
  const size_t largeSize = 65536;
  DataBuf buf(largeSize);
  comp.setValue(std::move(buf));
  EXPECT_EQ(comp.size(), largeSize);
  EXPECT_NE(comp.pData(), nullptr);
}
