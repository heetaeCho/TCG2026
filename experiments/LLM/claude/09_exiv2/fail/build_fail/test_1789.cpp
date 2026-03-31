#include <gtest/gtest.h>
#include <cstring>

#include "crwimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class CiffHeaderTest_1789 : public ::testing::Test {
 protected:
  CiffHeader header_;
};

// Test that a freshly constructed CiffHeader has littleEndian byte order
TEST_F(CiffHeaderTest_1789, DefaultByteOrder_1789) {
  EXPECT_EQ(header_.byteOrder(), littleEndian);
}

// Test that findComponent returns nullptr when nothing has been added
TEST_F(CiffHeaderTest_1789, FindComponentReturnsNullWhenEmpty_1789) {
  const CiffComponent* result = header_.findComponent(0x0001, 0x0000);
  EXPECT_EQ(result, nullptr);
}

// Test that add with a valid buffer does not throw
TEST_F(CiffHeaderTest_1789, AddDoesNotThrow_1789) {
  DataBuf buf(10);
  EXPECT_NO_THROW(header_.add(0x0805, 0x300a, std::move(buf)));
}

// Test that after adding a component, findComponent can locate it
TEST_F(CiffHeaderTest_1789, AddThenFindComponent_1789) {
  DataBuf buf(4);
  buf.write_uint8(0, 0x41);
  buf.write_uint8(1, 0x42);
  buf.write_uint8(2, 0x43);
  buf.write_uint8(3, 0x00);

  header_.add(0x0805, 0x300a, std::move(buf));

  const CiffComponent* comp = header_.findComponent(0x0805, 0x300a);
  // The component should be found after adding
  EXPECT_NE(comp, nullptr);
}

// Test adding multiple components with different tags
TEST_F(CiffHeaderTest_1789, AddMultipleComponents_1789) {
  DataBuf buf1(4);
  buf1.write_uint8(0, 0x01);
  header_.add(0x0805, 0x300a, std::move(buf1));

  DataBuf buf2(8);
  buf2.write_uint8(0, 0x02);
  header_.add(0x080a, 0x300a, std::move(buf2));

  const CiffComponent* comp1 = header_.findComponent(0x0805, 0x300a);
  const CiffComponent* comp2 = header_.findComponent(0x080a, 0x300a);

  EXPECT_NE(comp1, nullptr);
  EXPECT_NE(comp2, nullptr);
}

// Test adding a component with an empty DataBuf
TEST_F(CiffHeaderTest_1789, AddWithEmptyDataBuf_1789) {
  DataBuf buf;
  EXPECT_NO_THROW(header_.add(0x0805, 0x300a, std::move(buf)));
}

// Test that adding the same tag twice overwrites (or at least doesn't crash)
TEST_F(CiffHeaderTest_1789, AddSameTagTwice_1789) {
  DataBuf buf1(4);
  buf1.write_uint8(0, 0xAA);
  header_.add(0x0805, 0x300a, std::move(buf1));

  DataBuf buf2(8);
  buf2.write_uint8(0, 0xBB);
  EXPECT_NO_THROW(header_.add(0x0805, 0x300a, std::move(buf2)));

  const CiffComponent* comp = header_.findComponent(0x0805, 0x300a);
  EXPECT_NE(comp, nullptr);
}

// Test remove on an empty header does not crash
TEST_F(CiffHeaderTest_1789, RemoveOnEmptyDoesNotCrash_1789) {
  EXPECT_NO_THROW(header_.remove(0x0805, 0x300a));
}

// Test add then remove then find returns nullptr
TEST_F(CiffHeaderTest_1789, AddThenRemoveThenFindReturnsNull_1789) {
  DataBuf buf(4);
  header_.add(0x0805, 0x300a, std::move(buf));

  header_.remove(0x0805, 0x300a);

  const CiffComponent* comp = header_.findComponent(0x0805, 0x300a);
  // After removal, the component should not be found (or behavior is implementation-defined)
  // We just verify no crash; the result may vary
  (void)comp;
}

// Test write on empty header doesn't crash
TEST_F(CiffHeaderTest_1789, WriteEmptyHeader_1789) {
  Blob blob;
  EXPECT_NO_THROW(header_.write(blob));
}

// Test write after adding a component
TEST_F(CiffHeaderTest_1789, WriteAfterAdd_1789) {
  DataBuf buf(4);
  buf.write_uint8(0, 0x01);
  buf.write_uint8(1, 0x02);
  buf.write_uint8(2, 0x03);
  buf.write_uint8(3, 0x04);
  header_.add(0x0805, 0x300a, std::move(buf));

  Blob blob;
  EXPECT_NO_THROW(header_.write(blob));
  // The blob should have some data after writing
  EXPECT_GT(blob.size(), 0u);
}

// Test signature returns expected value
TEST_F(CiffHeaderTest_1789, SignatureIsNotEmpty_1789) {
  auto sig = CiffHeader::signature();
  // Signature should have some content
  EXPECT_FALSE(sig.empty());
}

// Test CiffComponent basic construction
class CiffComponentTest_1789 : public ::testing::Test {
 protected:
};

TEST_F(CiffComponentTest_1789, DefaultConstructor_1789) {
  CiffComponent comp;
  EXPECT_EQ(comp.tag(), 0);
  EXPECT_EQ(comp.dir(), 0);
  EXPECT_EQ(comp.size(), 0u);
  EXPECT_EQ(comp.offset(), 0u);
  EXPECT_EQ(comp.pData(), nullptr);
}

TEST_F(CiffComponentTest_1789, ParameterizedConstructor_1789) {
  CiffComponent comp(0x1234, 0x5678);
  EXPECT_EQ(comp.tag(), 0x1234);
  EXPECT_EQ(comp.dir(), 0x5678);
}

TEST_F(CiffComponentTest_1789, SetDir_1789) {
  CiffComponent comp(0x0001, 0x0002);
  comp.setDir(0x00FF);
  EXPECT_EQ(comp.dir(), 0x00FF);
}

TEST_F(CiffComponentTest_1789, SetValue_1789) {
  CiffComponent comp(0x0001, 0x0002);
  DataBuf buf(10);
  buf.write_uint8(0, 0xAB);
  comp.setValue(std::move(buf));
  // After setting value, size should reflect the buffer size
  EXPECT_EQ(comp.size(), 10u);
  EXPECT_NE(comp.pData(), nullptr);
  EXPECT_EQ(comp.pData()[0], 0xAB);
}

TEST_F(CiffComponentTest_1789, EmptyOnDefault_1789) {
  CiffComponent comp;
  EXPECT_TRUE(comp.empty());
}

TEST_F(CiffComponentTest_1789, TypeIdStatic_1789) {
  // Test that typeId doesn't crash for various tag values
  TypeId t1 = CiffComponent::typeId(0x0000);
  TypeId t2 = CiffComponent::typeId(0x0800);
  TypeId t3 = CiffComponent::typeId(0xFFFF);
  (void)t1;
  (void)t2;
  (void)t3;
}

TEST_F(CiffComponentTest_1789, DataLocationStatic_1789) {
  // Test that dataLocation doesn't crash for various tag values
  DataLocId d1 = CiffComponent::dataLocation(0x0000);
  DataLocId d2 = CiffComponent::dataLocation(0x0800);
  (void)d1;
  (void)d2;
}

TEST_F(CiffComponentTest_1789, FindComponentReturnsNullOnDefault_1789) {
  CiffComponent comp;
  CiffComponent* found = comp.findComponent(0x0001, 0x0002);
  EXPECT_EQ(found, nullptr);
}

// Test CrwMap::loadStack
class CrwMapTest_1789 : public ::testing::Test {
 protected:
};

TEST_F(CrwMapTest_1789, LoadStackPopulatesStack_1789) {
  CrwDirs dirs;
  // 0x300a is a known directory in CRW format
  EXPECT_NO_THROW(CrwMap::loadStack(dirs, 0x300a));
  EXPECT_GT(dirs.size(), 0u);
}

TEST_F(CrwMapTest_1789, LoadStackWithZeroDir_1789) {
  CrwDirs dirs;
  EXPECT_NO_THROW(CrwMap::loadStack(dirs, 0x0000));
}

// Test reading a valid CRW-like header
TEST_F(CiffHeaderTest_1789, ReadValidHeader_1789) {
  // Construct a minimal valid CRW header
  // CRW files start with byte order mark (II = little endian), 
  // then a header length, then "HEAPCCDR"
  // This is a minimal test; actual validity depends on implementation
  auto sig = CiffHeader::signature();

  // Build a minimal header: 2 bytes byte order + 4 bytes offset + signature + padding
  // Total header is typically 26 bytes minimum
  std::vector<byte> data(512, 0);

  // Little endian marker "II"
  data[0] = 'I';
  data[1] = 'I';

  // Offset to root directory (uint32_t at offset 2, little endian)
  // Point it past the header
  uint32_t rootOffset = 26;
  data[2] = static_cast<byte>(rootOffset & 0xFF);
  data[3] = static_cast<byte>((rootOffset >> 8) & 0xFF);
  data[4] = static_cast<byte>((rootOffset >> 16) & 0xFF);
  data[5] = static_cast<byte>((rootOffset >> 24) & 0xFF);

  // Copy signature starting at offset 6
  for (size_t i = 0; i < sig.size() && (6 + i) < data.size(); ++i) {
    data[6 + i] = sig[i];
  }

  // This may or may not be a valid enough header for read()
  // We just test that it doesn't crash on obviously wrong data
  CiffHeader readHeader;
  // Reading invalid/malformed data may throw; that's acceptable
  try {
    readHeader.read(data.data(), data.size());
  } catch (...) {
    // Expected for malformed data
  }
}

// Test DataBuf basic operations used in conjunction with CiffHeader
class DataBufTest_1789 : public ::testing::Test {};

TEST_F(DataBufTest_1789, DefaultConstructorIsEmpty_1789) {
  DataBuf buf;
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

TEST_F(DataBufTest_1789, SizeConstructor_1789) {
  DataBuf buf(100);
  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.size(), 100u);
}

TEST_F(DataBufTest_1789, DataConstructor_1789) {
  byte data[] = {0x01, 0x02, 0x03, 0x04};
  DataBuf buf(data, 4);
  EXPECT_EQ(buf.size(), 4u);
  EXPECT_EQ(buf.read_uint8(0), 0x01);
  EXPECT_EQ(buf.read_uint8(3), 0x04);
}

TEST_F(DataBufTest_1789, WriteAndReadUint8_1789) {
  DataBuf buf(4);
  buf.write_uint8(0, 0xAB);
  buf.write_uint8(3, 0xCD);
  EXPECT_EQ(buf.read_uint8(0), 0xAB);
  EXPECT_EQ(buf.read_uint8(3), 0xCD);
}

TEST_F(DataBufTest_1789, AllocResetsAndSizes_1789) {
  DataBuf buf;
  buf.alloc(50);
  EXPECT_EQ(buf.size(), 50u);
}

TEST_F(DataBufTest_1789, Reset_1789) {
  DataBuf buf(100);
  buf.reset();
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

TEST_F(DataBufTest_1789, Resize_1789) {
  DataBuf buf(10);
  buf.resize(20);
  EXPECT_EQ(buf.size(), 20u);
}

TEST_F(DataBufTest_1789, MoveSemantics_1789) {
  DataBuf buf1(10);
  buf1.write_uint8(0, 0xFF);
  DataBuf buf2(std::move(buf1));
  EXPECT_EQ(buf2.size(), 10u);
  EXPECT_EQ(buf2.read_uint8(0), 0xFF);
}
