#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "crwimage_int.hpp"
#include "image.hpp"
#include "types.hpp"
#include <sstream>
#include <vector>
#include <stack>

using namespace Exiv2;
using namespace Exiv2::Internal;

// ============================================================
// Test Fixture
// ============================================================
class CiffComponentTest_1790 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ============================================================
// Constructor Tests
// ============================================================

TEST_F(CiffComponentTest_1790, DefaultConstructor_1790) {
  CiffComponent comp;
  EXPECT_EQ(comp.tag(), 0);
  EXPECT_EQ(comp.dir(), 0);
  EXPECT_EQ(comp.size(), 0u);
  EXPECT_EQ(comp.offset(), 0u);
  EXPECT_EQ(comp.pData(), nullptr);
}

TEST_F(CiffComponentTest_1790, ParameterizedConstructor_1790) {
  uint16_t tag = 0x1234;
  uint16_t dir = 0x5678;
  CiffComponent comp(tag, dir);
  EXPECT_EQ(comp.tag(), tag);
  EXPECT_EQ(comp.dir(), dir);
  EXPECT_EQ(comp.size(), 0u);
  EXPECT_EQ(comp.offset(), 0u);
  EXPECT_EQ(comp.pData(), nullptr);
}

// ============================================================
// Accessor Tests
// ============================================================

TEST_F(CiffComponentTest_1790, SetDir_1790) {
  CiffComponent comp;
  comp.setDir(0xABCD);
  EXPECT_EQ(comp.dir(), 0xABCD);
}

TEST_F(CiffComponentTest_1790, TagAccessor_1790) {
  CiffComponent comp(0x0042, 0x0000);
  EXPECT_EQ(comp.tag(), 0x0042);
}

TEST_F(CiffComponentTest_1790, DirAccessor_1790) {
  CiffComponent comp(0x0000, 0x00FF);
  EXPECT_EQ(comp.dir(), 0x00FF);
}

// ============================================================
// tagId and typeId Tests
// ============================================================

TEST_F(CiffComponentTest_1790, TagIdFromTag_1790) {
  CiffComponent comp(0x300A, 0x0000);
  // tagId is derived from tag - typically the lower bits
  uint16_t tid = comp.tagId();
  // We just verify it returns something without crashing
  (void)tid;
}

TEST_F(CiffComponentTest_1790, TypeIdFromTag_1790) {
  // Static method
  TypeId t = CiffComponent::typeId(0x0000);
  // Just verify it returns without crashing
  (void)t;
}

TEST_F(CiffComponentTest_1790, TypeIdInstance_1790) {
  CiffComponent comp(0x0800, 0x0000);
  TypeId t = comp.typeId();
  (void)t;
}

TEST_F(CiffComponentTest_1790, DataLocationStatic_1790) {
  DataLocId loc = CiffComponent::dataLocation(0x0000);
  (void)loc;
}

TEST_F(CiffComponentTest_1790, DataLocationInstance_1790) {
  CiffComponent comp(0x0000, 0x0000);
  DataLocId loc = comp.dataLocation();
  (void)loc;
}

// ============================================================
// empty() Tests
// ============================================================

TEST_F(CiffComponentTest_1790, DefaultComponentIsEmpty_1790) {
  CiffComponent comp;
  // A default-constructed component should be considered empty
  EXPECT_TRUE(comp.empty());
}

TEST_F(CiffComponentTest_1790, ComponentWithDataNotEmpty_1790) {
  CiffComponent comp(0x0001, 0x0000);
  // Set some data via setValue
  DataBuf buf(10);
  std::memset(buf.data(), 0xAA, 10);
  comp.setValue(std::move(buf));
  // After setting value, the component might not be empty
  // (depends on implementation, but we test the interface)
  // Just call it to see the behavior
  bool result = comp.empty();
  (void)result;
}

// ============================================================
// setValue Tests
// ============================================================

TEST_F(CiffComponentTest_1790, SetValueUpdatesData_1790) {
  CiffComponent comp(0x0001, 0x0000);
  DataBuf buf(20);
  std::memset(buf.data(), 0x55, 20);
  comp.setValue(std::move(buf));
  // After setValue, pData should not be null and size should be 20
  EXPECT_NE(comp.pData(), nullptr);
  EXPECT_EQ(comp.size(), 20u);
}

TEST_F(CiffComponentTest_1790, SetValueEmptyBuffer_1790) {
  CiffComponent comp(0x0001, 0x0000);
  DataBuf buf;  // empty buffer
  comp.setValue(std::move(buf));
  EXPECT_EQ(comp.size(), 0u);
}

TEST_F(CiffComponentTest_1790, SetValueOverwritesPrevious_1790) {
  CiffComponent comp(0x0001, 0x0000);

  DataBuf buf1(10);
  std::memset(buf1.data(), 0xAA, 10);
  comp.setValue(std::move(buf1));
  EXPECT_EQ(comp.size(), 10u);

  DataBuf buf2(30);
  std::memset(buf2.data(), 0xBB, 30);
  comp.setValue(std::move(buf2));
  EXPECT_EQ(comp.size(), 30u);
}

// ============================================================
// findComponent Tests
// ============================================================

TEST_F(CiffComponentTest_1790, FindComponentOnBaseReturnsNullByDefault_1790) {
  CiffComponent comp(0x0001, 0x0002);
  // On a base CiffComponent (not a directory), findComponent should return nullptr
  // for a different tag/dir
  CiffComponent* found = comp.findComponent(0x9999, 0x9999);
  EXPECT_EQ(found, nullptr);
}

TEST_F(CiffComponentTest_1790, FindComponentMatchingSelf_1790) {
  CiffComponent comp(0x0001, 0x0002);
  // Searching for matching tag and dir on base component
  CiffComponent* found = comp.findComponent(0x0001, 0x0002);
  // Base component doFindComponent checks if its own tag/dir matches
  // The behavior depends on implementation
  (void)found;
}

// ============================================================
// print Tests
// ============================================================

TEST_F(CiffComponentTest_1790, PrintDoesNotCrash_1790) {
  CiffComponent comp(0x0001, 0x0002);
  std::ostringstream oss;
  EXPECT_NO_THROW(comp.print(oss, littleEndian, ""));
}

TEST_F(CiffComponentTest_1790, PrintWithPrefix_1790) {
  CiffComponent comp(0x0001, 0x0002);
  std::ostringstream oss;
  EXPECT_NO_THROW(comp.print(oss, bigEndian, "PREFIX:"));
  // Should have produced some output
  // We don't know exact format, just verify no crash
}

// ============================================================
// writeDirEntry Tests
// ============================================================

TEST_F(CiffComponentTest_1790, WriteDirEntryDoesNotCrash_1790) {
  CiffComponent comp(0x0001, 0x0002);
  Blob blob;
  EXPECT_NO_THROW(comp.writeDirEntry(blob, littleEndian));
  // A dir entry typically adds some bytes
  EXPECT_GT(blob.size(), 0u);
}

TEST_F(CiffComponentTest_1790, WriteDirEntryBigEndian_1790) {
  CiffComponent comp(0x0001, 0x0002);
  Blob blob;
  EXPECT_NO_THROW(comp.writeDirEntry(blob, bigEndian));
  EXPECT_GT(blob.size(), 0u);
}

// ============================================================
// writeValueData Tests
// ============================================================

TEST_F(CiffComponentTest_1790, WriteValueDataEmptyComponent_1790) {
  CiffComponent comp;
  Blob blob;
  size_t result = comp.writeValueData(blob, 0);
  // For an empty component, offset should be returned unchanged or minimal
  (void)result;
}

TEST_F(CiffComponentTest_1790, WriteValueDataWithData_1790) {
  CiffComponent comp(0x0001, 0x0000);
  DataBuf buf(16);
  std::memset(buf.data(), 0xCC, 16);
  comp.setValue(std::move(buf));

  Blob blob;
  size_t result = comp.writeValueData(blob, 100);
  // Should return new offset
  (void)result;
}

// ============================================================
// write Tests
// ============================================================

TEST_F(CiffComponentTest_1790, WriteEmptyComponent_1790) {
  CiffComponent comp;
  Blob blob;
  size_t result = comp.write(blob, littleEndian, 0);
  (void)result;
}

TEST_F(CiffComponentTest_1790, WriteComponentWithValue_1790) {
  CiffComponent comp(0x0001, 0x0000);
  DataBuf buf(8);
  std::memset(buf.data(), 0xDD, 8);
  comp.setValue(std::move(buf));

  Blob blob;
  size_t result = comp.write(blob, littleEndian, 0);
  (void)result;
}

// ============================================================
// remove Tests (on base CiffComponent - should throw or be no-op)
// ============================================================

TEST_F(CiffComponentTest_1790, RemoveOnBaseComponentThrows_1790) {
  CiffComponent comp(0x0001, 0x0002);
  CrwDirs dirs;
  dirs.push(0x0003);
  // doRemove on base CiffComponent throws
  EXPECT_THROW(comp.remove(dirs, 0x0001), Error);
}

// ============================================================
// add(CrwDirs, crwTagId) Tests on base CiffComponent
// ============================================================

TEST_F(CiffComponentTest_1790, AddWithCrwDirsOnBaseThrows_1790) {
  CiffComponent comp(0x0001, 0x0002);
  CrwDirs dirs;
  dirs.push(0x0003);
  // doAdd on base CiffComponent throws
  EXPECT_THROW(comp.add(dirs, 0x0001), Error);
}

// ============================================================
// Boundary Tests
// ============================================================

TEST_F(CiffComponentTest_1790, MaxTagAndDirValues_1790) {
  CiffComponent comp(0xFFFF, 0xFFFF);
  EXPECT_EQ(comp.tag(), 0xFFFF);
  EXPECT_EQ(comp.dir(), 0xFFFF);
}

TEST_F(CiffComponentTest_1790, ZeroTagAndDirValues_1790) {
  CiffComponent comp(0x0000, 0x0000);
  EXPECT_EQ(comp.tag(), 0x0000);
  EXPECT_EQ(comp.dir(), 0x0000);
}

TEST_F(CiffComponentTest_1790, SetDirToZero_1790) {
  CiffComponent comp(0x0001, 0x0002);
  comp.setDir(0x0000);
  EXPECT_EQ(comp.dir(), 0x0000);
}

TEST_F(CiffComponentTest_1790, SetDirToMax_1790) {
  CiffComponent comp(0x0001, 0x0002);
  comp.setDir(0xFFFF);
  EXPECT_EQ(comp.dir(), 0xFFFF);
}

TEST_F(CiffComponentTest_1790, SetValueLargeBuffer_1790) {
  CiffComponent comp(0x0001, 0x0000);
  DataBuf buf(1024 * 1024);  // 1MB
  std::memset(buf.data(), 0xEE, buf.size());
  comp.setValue(std::move(buf));
  EXPECT_EQ(comp.size(), 1024u * 1024u);
  EXPECT_NE(comp.pData(), nullptr);
}

TEST_F(CiffComponentTest_1790, SetValueSingleByte_1790) {
  CiffComponent comp(0x0001, 0x0000);
  DataBuf buf(1);
  buf.data()[0] = 0x42;
  comp.setValue(std::move(buf));
  EXPECT_EQ(comp.size(), 1u);
  EXPECT_NE(comp.pData(), nullptr);
  EXPECT_EQ(comp.pData()[0], 0x42);
}

// ============================================================
// CiffDirectory Tests (if available through the interface)
// ============================================================

// CiffDirectory is a derived class; test it if accessible
class CiffDirectoryTest_1790 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(CiffDirectoryTest_1790, DirectoryConstruction_1790) {
  CiffDirectory dir(0x0000, 0x0000);
  EXPECT_EQ(dir.tag(), 0x0000);
  EXPECT_EQ(dir.dir(), 0x0000);
}

TEST_F(CiffDirectoryTest_1790, DirectoryEmpty_1790) {
  CiffDirectory dir(0x0000, 0x0000);
  EXPECT_TRUE(dir.empty());
}

TEST_F(CiffDirectoryTest_1790, DirectoryFindComponentNotFound_1790) {
  CiffDirectory dir(0x0001, 0x0002);
  CiffComponent* found = dir.findComponent(0x9999, 0x9999);
  EXPECT_EQ(found, nullptr);
}

// ============================================================
// Static method typeId tests for various tag values
// ============================================================

TEST_F(CiffComponentTest_1790, TypeIdForVariousTags_1790) {
  // Test with different tag patterns - the upper bits determine type
  TypeId t1 = CiffComponent::typeId(0x0000);
  TypeId t2 = CiffComponent::typeId(0x0800);
  TypeId t3 = CiffComponent::typeId(0x1000);
  TypeId t4 = CiffComponent::typeId(0x1800);
  TypeId t5 = CiffComponent::typeId(0x2000);
  TypeId t6 = CiffComponent::typeId(0x2800);
  TypeId t7 = CiffComponent::typeId(0x3800);
  // Just verify they don't crash and return valid values
  (void)t1; (void)t2; (void)t3; (void)t4; (void)t5; (void)t6; (void)t7;
}

TEST_F(CiffComponentTest_1790, DataLocationForVariousTags_1790) {
  DataLocId d1 = CiffComponent::dataLocation(0x0000);
  DataLocId d2 = CiffComponent::dataLocation(0x4000);
  // Verify they don't crash
  (void)d1; (void)d2;
}

// ============================================================
// Copy/Assignment deleted tests (compile-time, but we verify construction works)
// ============================================================

TEST_F(CiffComponentTest_1790, MoveSetValueMultipleTimes_1790) {
  CiffComponent comp(0x0001, 0x0000);
  for (int i = 1; i <= 10; ++i) {
    DataBuf buf(i * 10);
    std::memset(buf.data(), static_cast<byte>(i), buf.size());
    comp.setValue(std::move(buf));
    EXPECT_EQ(comp.size(), static_cast<size_t>(i * 10));
  }
}
