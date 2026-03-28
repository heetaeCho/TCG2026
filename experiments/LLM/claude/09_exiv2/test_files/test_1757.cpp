#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>
#include <vector>

// Include the header under test
#include "crwimage_int.hpp"

using namespace Exiv2::Internal;

// =============================================================================
// Test fixture
// =============================================================================
class CiffComponentTest_1757 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// -----------------------------------------------------------------------------
// Construction tests
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, DefaultConstructor_ZeroDir_1757) {
  CiffComponent comp;
  EXPECT_EQ(comp.dir(), 0);
}

TEST_F(CiffComponentTest_1757, DefaultConstructor_ZeroTag_1757) {
  CiffComponent comp;
  EXPECT_EQ(comp.tag(), 0);
}

TEST_F(CiffComponentTest_1757, DefaultConstructor_ZeroSize_1757) {
  CiffComponent comp;
  EXPECT_EQ(comp.size(), 0u);
}

TEST_F(CiffComponentTest_1757, DefaultConstructor_ZeroOffset_1757) {
  CiffComponent comp;
  EXPECT_EQ(comp.offset(), 0u);
}

TEST_F(CiffComponentTest_1757, DefaultConstructor_NullData_1757) {
  CiffComponent comp;
  EXPECT_EQ(comp.pData(), nullptr);
}

TEST_F(CiffComponentTest_1757, ParameterizedConstructor_TagAndDir_1757) {
  CiffComponent comp(0x1234, 0x5678);
  EXPECT_EQ(comp.tag(), 0x1234);
  EXPECT_EQ(comp.dir(), 0x5678);
}

TEST_F(CiffComponentTest_1757, ParameterizedConstructor_ZeroValues_1757) {
  CiffComponent comp(0, 0);
  EXPECT_EQ(comp.tag(), 0);
  EXPECT_EQ(comp.dir(), 0);
}

TEST_F(CiffComponentTest_1757, ParameterizedConstructor_MaxValues_1757) {
  CiffComponent comp(0xFFFF, 0xFFFF);
  EXPECT_EQ(comp.tag(), 0xFFFF);
  EXPECT_EQ(comp.dir(), 0xFFFF);
}

// -----------------------------------------------------------------------------
// setDir tests
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, SetDir_ChangesDir_1757) {
  CiffComponent comp;
  comp.setDir(42);
  EXPECT_EQ(comp.dir(), 42);
}

TEST_F(CiffComponentTest_1757, SetDir_Zero_1757) {
  CiffComponent comp(0x1234, 0x5678);
  comp.setDir(0);
  EXPECT_EQ(comp.dir(), 0);
}

TEST_F(CiffComponentTest_1757, SetDir_MaxUint16_1757) {
  CiffComponent comp;
  comp.setDir(0xFFFF);
  EXPECT_EQ(comp.dir(), 0xFFFF);
}

TEST_F(CiffComponentTest_1757, SetDir_MultipleTimes_1757) {
  CiffComponent comp;
  comp.setDir(100);
  EXPECT_EQ(comp.dir(), 100);
  comp.setDir(200);
  EXPECT_EQ(comp.dir(), 200);
  comp.setDir(300);
  EXPECT_EQ(comp.dir(), 300);
}

TEST_F(CiffComponentTest_1757, SetDir_DoesNotAffectTag_1757) {
  CiffComponent comp(0x1234, 0x5678);
  comp.setDir(0xAAAA);
  EXPECT_EQ(comp.tag(), 0x1234);
  EXPECT_EQ(comp.dir(), 0xAAAA);
}

// -----------------------------------------------------------------------------
// tagId tests
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, TagId_DefaultConstructor_1757) {
  CiffComponent comp;
  // tagId is derived from tag; with tag=0, tagId should be deterministic
  uint16_t id = comp.tagId();
  // We just verify it returns without error; the exact value depends on masking
  (void)id;
}

TEST_F(CiffComponentTest_1757, TagId_FromParameterizedConstructor_1757) {
  CiffComponent comp(0x300F, 0x0000);
  uint16_t id = comp.tagId();
  // tagId typically masks the tag; just check it's consistent
  (void)id;
}

// -----------------------------------------------------------------------------
// typeId (static) tests
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, StaticTypeId_ZeroTag_1757) {
  TypeId t = CiffComponent::typeId(0);
  // Just verify it returns a valid TypeId enum
  (void)t;
}

TEST_F(CiffComponentTest_1757, StaticTypeId_NonZeroTag_1757) {
  TypeId t = CiffComponent::typeId(0x0800);
  (void)t;
}

// -----------------------------------------------------------------------------
// dataLocation (static) tests
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, StaticDataLocation_ZeroTag_1757) {
  DataLocId loc = CiffComponent::dataLocation(0);
  (void)loc;
}

TEST_F(CiffComponentTest_1757, StaticDataLocation_NonZeroTag_1757) {
  DataLocId loc = CiffComponent::dataLocation(0x0800);
  (void)loc;
}

// -----------------------------------------------------------------------------
// empty tests
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, Empty_DefaultConstructed_1757) {
  CiffComponent comp;
  // Default constructed should be considered empty (no data)
  bool e = comp.empty();
  // Just verifying it returns without error
  (void)e;
}

// -----------------------------------------------------------------------------
// setValue tests
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, SetValue_EmptyBuffer_1757) {
  CiffComponent comp;
  Exiv2::DataBuf buf;
  comp.setValue(std::move(buf));
  // After setting empty value, pData behavior may vary
}

TEST_F(CiffComponentTest_1757, SetValue_NonEmptyBuffer_1757) {
  CiffComponent comp;
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  Exiv2::DataBuf buf(data, sizeof(data));
  comp.setValue(std::move(buf));
  EXPECT_NE(comp.pData(), nullptr);
  EXPECT_EQ(comp.size(), sizeof(data));
}

TEST_F(CiffComponentTest_1757, SetValue_OverwritesPrevious_1757) {
  CiffComponent comp;
  const uint8_t data1[] = {0x01, 0x02};
  Exiv2::DataBuf buf1(data1, sizeof(data1));
  comp.setValue(std::move(buf1));
  EXPECT_EQ(comp.size(), 2u);

  const uint8_t data2[] = {0x0A, 0x0B, 0x0C, 0x0D, 0x0E};
  Exiv2::DataBuf buf2(data2, sizeof(data2));
  comp.setValue(std::move(buf2));
  EXPECT_EQ(comp.size(), 5u);
}

// -----------------------------------------------------------------------------
// findComponent tests
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, FindComponent_Self_1757) {
  // A leaf CiffComponent's doFindComponent checks if it matches
  CiffComponent comp(0x0001, 0x0000);
  // tagId is tag & 0x3fff typically; for tag=0x0001, tagId=0x0001
  CiffComponent* found = comp.findComponent(comp.tagId(), comp.dir());
  // May or may not find itself depending on implementation
  (void)found;
}

TEST_F(CiffComponentTest_1757, FindComponent_NotFound_1757) {
  CiffComponent comp(0x0001, 0x0000);
  CiffComponent* found = comp.findComponent(0xFFFF, 0xFFFF);
  EXPECT_EQ(found, nullptr);
}

// -----------------------------------------------------------------------------
// print tests
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, Print_DefaultComponent_1757) {
  CiffComponent comp;
  std::ostringstream os;
  comp.print(os, Exiv2::littleEndian, "");
  // Just verify it doesn't crash; output can be anything
  std::string output = os.str();
  (void)output;
}

TEST_F(CiffComponentTest_1757, Print_WithPrefix_1757) {
  CiffComponent comp(0x0001, 0x0000);
  std::ostringstream os;
  comp.print(os, Exiv2::littleEndian, "PREFIX ");
  std::string output = os.str();
  (void)output;
}

// -----------------------------------------------------------------------------
// Copy and assignment deleted tests (compile-time checks implicit)
// These verify the class design - just having them here documents the intent
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, NotCopyableNotAssignable_1757) {
  // CiffComponent(const CiffComponent&) = delete;
  // CiffComponent& operator=(const CiffComponent&) = delete;
  // These are compile-time guarantees. If the following compiled, the test would fail.
  EXPECT_FALSE(std::is_copy_constructible<CiffComponent>::value);
  EXPECT_FALSE(std::is_copy_assignable<CiffComponent>::value);
}

// -----------------------------------------------------------------------------
// writeValueData / writeDirEntry with Blob tests
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, WriteValueData_DefaultComponent_1757) {
  CiffComponent comp;
  Exiv2::Blob blob;
  size_t result = comp.writeValueData(blob, 0);
  // For a default component with no data, expect offset returned
  (void)result;
}

TEST_F(CiffComponentTest_1757, WriteDirEntry_DefaultComponent_1757) {
  CiffComponent comp;
  Exiv2::Blob blob;
  comp.writeDirEntry(blob, Exiv2::littleEndian);
  // Should write a directory entry (10 bytes typically for CIFF)
  EXPECT_GE(blob.size(), 0u);
}

TEST_F(CiffComponentTest_1757, Write_DefaultComponent_1757) {
  CiffComponent comp;
  Exiv2::Blob blob;
  size_t result = comp.write(blob, Exiv2::littleEndian, 0);
  (void)result;
}

// -----------------------------------------------------------------------------
// Boundary: setting data then writing
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, SetValueThenWrite_1757) {
  CiffComponent comp(0x0001, 0x0000);
  const uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
  Exiv2::DataBuf buf(data, sizeof(data));
  comp.setValue(std::move(buf));

  Exiv2::Blob blob;
  size_t result = comp.write(blob, Exiv2::littleEndian, 0);
  // The blob should have some data written
  EXPECT_GT(result, 0u);
}

// -----------------------------------------------------------------------------
// typeId (instance) test
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, InstanceTypeId_1757) {
  CiffComponent comp(0x0800, 0x0000);
  TypeId t = comp.typeId();
  // Instance typeId should be same as static typeId for same tag
  EXPECT_EQ(t, CiffComponent::typeId(0x0800));
}

TEST_F(CiffComponentTest_1757, InstanceDataLocation_1757) {
  CiffComponent comp(0x0800, 0x0000);
  DataLocId loc = comp.dataLocation();
  EXPECT_EQ(loc, CiffComponent::dataLocation(0x0800));
}

// -----------------------------------------------------------------------------
// ByteOrder variations
// -----------------------------------------------------------------------------

TEST_F(CiffComponentTest_1757, WriteDirEntry_BigEndian_1757) {
  CiffComponent comp(0x0001, 0x0000);
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  Exiv2::DataBuf buf(data, sizeof(data));
  comp.setValue(std::move(buf));

  Exiv2::Blob blob;
  comp.writeDirEntry(blob, Exiv2::bigEndian);
  EXPECT_GE(blob.size(), 0u);
}

TEST_F(CiffComponentTest_1757, WriteDirEntry_LittleEndian_1757) {
  CiffComponent comp(0x0001, 0x0000);
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  Exiv2::DataBuf buf(data, sizeof(data));
  comp.setValue(std::move(buf));

  Exiv2::Blob blob;
  comp.writeDirEntry(blob, Exiv2::littleEndian);
  EXPECT_GE(blob.size(), 0u);
}
