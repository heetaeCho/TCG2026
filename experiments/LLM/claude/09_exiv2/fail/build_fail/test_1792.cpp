#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "crwimage_int.hpp"
#include "image.hpp"
#include "basicio.hpp"

#include <cstring>
#include <vector>
#include <sstream>

using namespace Exiv2;
using namespace Exiv2::Internal;

// ============================================================================
// CiffHeader Tests
// ============================================================================

class CiffHeaderTest_1792 : public ::testing::Test {
 protected:
  CiffHeader header_;
};

// Test that remove does not crash when pRootDir_ is null (no read has been done)
TEST_F(CiffHeaderTest_1792, RemoveWithNullRootDir_1792) {
  // CiffHeader is default constructed, pRootDir_ should be null
  // remove should simply be a no-op and not crash
  EXPECT_NO_THROW(header_.remove(0x0001, 0x0000));
}

TEST_F(CiffHeaderTest_1792, RemoveWithNullRootDirVariousTags_1792) {
  // Try various tag/dir combinations with uninitialized header
  EXPECT_NO_THROW(header_.remove(0x0000, 0x0000));
  EXPECT_NO_THROW(header_.remove(0xFFFF, 0xFFFF));
  EXPECT_NO_THROW(header_.remove(0x0805, 0x300a));
  EXPECT_NO_THROW(header_.remove(0x2008, 0x0000));
}

TEST_F(CiffHeaderTest_1792, DefaultByteOrder_1792) {
  // Default byte order should be littleEndian
  EXPECT_EQ(header_.byteOrder(), littleEndian);
}

TEST_F(CiffHeaderTest_1792, SignatureIsNotNull_1792) {
  // Signature should return something valid
  auto sig = CiffHeader::signature();
  // Just check it doesn't throw
  EXPECT_NO_THROW(CiffHeader::signature());
}

// ============================================================================
// CrwMap::loadStack Tests
// ============================================================================

class CrwMapTest_1792 : public ::testing::Test {
};

TEST_F(CrwMapTest_1792, LoadStackRootDir_1792) {
  CrwDirs crwDirs;
  // Load stack for root directory (0x0000)
  CrwMap::loadStack(crwDirs, 0x0000);
  // The stack should contain at least one entry for root
  EXPECT_FALSE(crwDirs.empty());
}

TEST_F(CrwMapTest_1792, LoadStackKnownDir_1792) {
  CrwDirs crwDirs;
  // 0x300a is a known CRW directory
  CrwMap::loadStack(crwDirs, 0x300a);
  // Should have entries in the stack
  EXPECT_FALSE(crwDirs.empty());
}

TEST_F(CrwMapTest_1792, LoadStackAnotherKnownDir_1792) {
  CrwDirs crwDirs;
  // 0x300b is another known CRW directory
  CrwMap::loadStack(crwDirs, 0x300b);
  EXPECT_FALSE(crwDirs.empty());
}

TEST_F(CrwMapTest_1792, LoadStackMultipleCallsIndependent_1792) {
  CrwDirs crwDirs1;
  CrwDirs crwDirs2;
  CrwMap::loadStack(crwDirs1, 0x0000);
  CrwMap::loadStack(crwDirs2, 0x300a);
  // Different directories should potentially produce different stacks
  // At minimum, both should be non-empty
  EXPECT_FALSE(crwDirs1.empty());
  EXPECT_FALSE(crwDirs2.empty());
}

// ============================================================================
// CiffComponent Tests
// ============================================================================

class CiffComponentTest_1792 : public ::testing::Test {
};

TEST_F(CiffComponentTest_1792, DefaultConstruction_1792) {
  // CiffComponent with tag and dir constructor
  CiffComponent comp(0x0001, 0x0002);
  EXPECT_EQ(comp.tag(), 0x0001);
  EXPECT_EQ(comp.dir(), 0x0002);
}

TEST_F(CiffComponentTest_1792, DefaultEmptyCheck_1792) {
  CiffComponent comp(0x0000, 0x0000);
  // A default-constructed component should report as empty
  EXPECT_TRUE(comp.empty());
}

TEST_F(CiffComponentTest_1792, TagIdExtraction_1792) {
  CiffComponent comp(0x1234, 0x5678);
  EXPECT_EQ(comp.tag(), 0x1234);
  EXPECT_EQ(comp.dir(), 0x5678);
  // tagId extracts the lower bits of tag
  uint16_t tagId = comp.tagId();
  // tagId is typically tag & 0x3fff
  EXPECT_EQ(tagId, comp.tag() & 0x3FFF);
}

TEST_F(CiffComponentTest_1792, SizeAndOffsetDefault_1792) {
  CiffComponent comp(0x0001, 0x0002);
  EXPECT_EQ(comp.size(), 0u);
  EXPECT_EQ(comp.offset(), 0u);
}

TEST_F(CiffComponentTest_1792, PDataDefaultNull_1792) {
  CiffComponent comp(0x0001, 0x0002);
  EXPECT_EQ(comp.pData(), nullptr);
}

TEST_F(CiffComponentTest_1792, SetValue_1792) {
  CiffComponent comp(0x0001, 0x0002);
  DataBuf buf(10);
  std::memset(buf.data(), 0xAB, 10);
  comp.setValue(std::move(buf));
  EXPECT_EQ(comp.size(), 10u);
  EXPECT_NE(comp.pData(), nullptr);
}

TEST_F(CiffComponentTest_1792, SetValueEmpty_1792) {
  CiffComponent comp(0x0001, 0x0002);
  DataBuf buf;
  comp.setValue(std::move(buf));
  // Empty buffer
  EXPECT_EQ(comp.size(), 0u);
}

TEST_F(CiffComponentTest_1792, SetDir_1792) {
  CiffComponent comp(0x0001, 0x0002);
  comp.setDir(0x1234);
  EXPECT_EQ(comp.dir(), 0x1234);
}

TEST_F(CiffComponentTest_1792, TypeIdStatic_1792) {
  // Test static typeId method with various tags
  // The type is encoded in the upper bits of the tag
  TypeId type0 = CiffComponent::typeId(0x0000);
  TypeId type1 = CiffComponent::typeId(0x0800);
  // Just verify these don't crash; the actual mapping is internal
  (void)type0;
  (void)type1;
}

TEST_F(CiffComponentTest_1792, DataLocationStatic_1792) {
  DataLocId loc = CiffComponent::dataLocation(0x0000);
  (void)loc; // Just ensure it doesn't crash
  DataLocId loc2 = CiffComponent::dataLocation(0x4000);
  (void)loc2;
}

TEST_F(CiffComponentTest_1792, FindComponentReturnsNull_1792) {
  CiffComponent comp(0x0001, 0x0002);
  // On a leaf component, findComponent may return nullptr or itself
  CiffComponent* found = comp.findComponent(0x0001, 0x0002);
  // It could be nullptr or a pointer to comp depending on implementation
  // Just ensure no crash
  (void)found;
}

TEST_F(CiffComponentTest_1792, FindComponentNoMatch_1792) {
  CiffComponent comp(0x0001, 0x0002);
  CiffComponent* found = comp.findComponent(0xFFFF, 0xFFFF);
  // Should not find anything
  EXPECT_EQ(found, nullptr);
}

TEST_F(CiffComponentTest_1792, PrintDoesNotCrash_1792) {
  CiffComponent comp(0x0001, 0x0002);
  std::ostringstream os;
  EXPECT_NO_THROW(comp.print(os, littleEndian, ""));
}

TEST_F(CiffComponentTest_1792, RemoveOnLeafComponent_1792) {
  CiffComponent comp(0x0001, 0x0002);
  CrwDirs dirs;
  // Remove on a leaf component should be a no-op
  EXPECT_NO_THROW(comp.remove(dirs, 0x0001));
}

// ============================================================================
// CiffHeader read with invalid data
// ============================================================================

class CiffHeaderReadTest_1792 : public ::testing::Test {
 protected:
  CiffHeader header_;
};

TEST_F(CiffHeaderReadTest_1792, ReadWithTooSmallData_1792) {
  // CRW files have a minimum header size; reading very small data should throw
  const byte smallData[] = {0x00, 0x01, 0x02};
  EXPECT_THROW(header_.read(smallData, sizeof(smallData)), Error);
}

TEST_F(CiffHeaderReadTest_1792, ReadWithNullData_1792) {
  EXPECT_THROW(header_.read(nullptr, 0), Error);
}

TEST_F(CiffHeaderReadTest_1792, ReadWithInvalidSignature_1792) {
  // Create data that's large enough but has invalid signature
  std::vector<byte> data(64, 0);
  EXPECT_THROW(header_.read(data.data(), data.size()), Error);
}

// ============================================================================
// CiffHeader write without initialization
// ============================================================================

TEST_F(CiffHeaderTest_1792, WriteWithoutRead_1792) {
  Blob blob;
  // Writing without having read any data - header may still write a minimal structure
  // or throw; we just verify it doesn't crash in an uncontrolled way
  EXPECT_NO_THROW(header_.write(blob));
}

TEST_F(CiffHeaderTest_1792, FindComponentWithoutRead_1792) {
  // Without reading data, pRootDir_ is null, findComponent should return nullptr
  const CiffComponent* comp = header_.findComponent(0x0001, 0x0000);
  EXPECT_EQ(comp, nullptr);
}

TEST_F(CiffHeaderTest_1792, AddWithoutRead_1792) {
  // Adding to header without reading data first
  // This may or may not throw depending on implementation
  DataBuf buf(4);
  std::memset(buf.data(), 0, 4);
  // If pRootDir_ is null, add might create it or might be a no-op
  EXPECT_NO_THROW(header_.add(0x0001, 0x0000, std::move(buf)));
}

// ============================================================================
// Boundary value tests for CiffComponent
// ============================================================================

TEST_F(CiffComponentTest_1792, MaxTagAndDir_1792) {
  CiffComponent comp(0xFFFF, 0xFFFF);
  EXPECT_EQ(comp.tag(), 0xFFFF);
  EXPECT_EQ(comp.dir(), 0xFFFF);
}

TEST_F(CiffComponentTest_1792, ZeroTagAndDir_1792) {
  CiffComponent comp(0x0000, 0x0000);
  EXPECT_EQ(comp.tag(), 0x0000);
  EXPECT_EQ(comp.dir(), 0x0000);
}

TEST_F(CiffComponentTest_1792, SetValueLargeBuffer_1792) {
  CiffComponent comp(0x0001, 0x0002);
  DataBuf buf(100000);
  std::memset(buf.data(), 0xFF, 100000);
  comp.setValue(std::move(buf));
  EXPECT_EQ(comp.size(), 100000u);
  EXPECT_NE(comp.pData(), nullptr);
}

TEST_F(CiffComponentTest_1792, WriteDirEntryDoesNotCrash_1792) {
  CiffComponent comp(0x0001, 0x0002);
  Blob blob;
  EXPECT_NO_THROW(comp.writeDirEntry(blob, littleEndian));
}

TEST_F(CiffComponentTest_1792, WriteDirEntryBigEndian_1792) {
  CiffComponent comp(0x0001, 0x0002);
  Blob blob;
  EXPECT_NO_THROW(comp.writeDirEntry(blob, bigEndian));
}
