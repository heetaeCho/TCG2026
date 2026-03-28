#include <gtest/gtest.h>
#include "exiv2/basicio.hpp"

using namespace Exiv2;

// Test fixture for MemIo tests
class MemIoTest_586 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Constructor Tests ====================

TEST_F(MemIoTest_586, DefaultConstructor_CreatesEmptyMemIo_586) {
  MemIo memIo;
  EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_586, DataConstructor_CreatesMemIoWithData_586) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_586, DataConstructor_WithNullptrAndZeroSize_586) {
  MemIo memIo(nullptr, 0);
  EXPECT_EQ(memIo.size(), 0u);
}

// ==================== open() Tests ====================

TEST_F(MemIoTest_586, Open_ReturnsZero_586) {
  MemIo memIo;
  EXPECT_EQ(memIo.open(), 0);
}

TEST_F(MemIoTest_586, Open_ResetsPosition_586) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  // Read some data to advance position
  memIo.read(2);
  EXPECT_EQ(memIo.tell(), 2u);
  // Open again should reset
  memIo.open();
  EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_586, Open_ResetsEof_586) {
  const byte data[] = {0x01};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  // Read past end
  memIo.read(2);
  // Open should reset eof
  memIo.open();
  EXPECT_FALSE(memIo.eof());
}

// ==================== close() Tests ====================

TEST_F(MemIoTest_586, Close_ReturnsZero_586) {
  MemIo memIo;
  EXPECT_EQ(memIo.close(), 0);
}

// ==================== write(const byte*, size_t) Tests ====================

TEST_F(MemIoTest_586, Write_ByteArray_WritesData_586) {
  MemIo memIo;
  const byte data[] = {0x01, 0x02, 0x03};
  size_t written = memIo.write(data, sizeof(data));
  EXPECT_EQ(written, sizeof(data));
  EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_586, Write_ByteArray_ZeroBytes_586) {
  MemIo memIo;
  const byte data[] = {0x01};
  size_t written = memIo.write(data, 0);
  EXPECT_EQ(written, 0u);
  EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_586, Write_ByteArray_MultipleWrites_586) {
  MemIo memIo;
  const byte data1[] = {0x01, 0x02};
  const byte data2[] = {0x03, 0x04, 0x05};
  memIo.write(data1, sizeof(data1));
  memIo.write(data2, sizeof(data2));
  EXPECT_EQ(memIo.size(), sizeof(data1) + sizeof(data2));
}

// ==================== write(BasicIo&) Tests ====================

TEST_F(MemIoTest_586, Write_BasicIo_CopiesFromSource_586) {
  const byte data[] = {0x0A, 0x0B, 0x0C};
  MemIo src(data, sizeof(data));
  MemIo dest;
  size_t written = dest.write(src);
  EXPECT_EQ(written, sizeof(data));
  EXPECT_EQ(dest.size(), sizeof(data));
}

TEST_F(MemIoTest_586, Write_BasicIo_EmptySource_586) {
  MemIo src;
  MemIo dest;
  size_t written = dest.write(src);
  EXPECT_EQ(written, 0u);
}

// ==================== putb() Tests ====================

TEST_F(MemIoTest_586, Putb_WritesSingleByte_586) {
  MemIo memIo;
  int result = memIo.putb(0x42);
  EXPECT_EQ(result, 0x42);
  EXPECT_EQ(memIo.size(), 1u);
}

TEST_F(MemIoTest_586, Putb_MultipleBytes_586) {
  MemIo memIo;
  memIo.putb(0x01);
  memIo.putb(0x02);
  memIo.putb(0x03);
  EXPECT_EQ(memIo.size(), 3u);
}

// ==================== read(size_t) Tests ====================

TEST_F(MemIoTest_586, Read_DataBuf_ReadsCorrectAmount_586) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  DataBuf buf = memIo.read(3);
  EXPECT_EQ(buf.size(), 3u);
}

TEST_F(MemIoTest_586, Read_DataBuf_ReadMoreThanAvailable_586) {
  const byte data[] = {0x01, 0x02};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  DataBuf buf = memIo.read(10);
  EXPECT_LE(buf.size(), 10u);
}

TEST_F(MemIoTest_586, Read_DataBuf_ReadZero_586) {
  const byte data[] = {0x01, 0x02};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  DataBuf buf = memIo.read(0);
  EXPECT_EQ(buf.size(), 0u);
}

TEST_F(MemIoTest_586, Read_DataBuf_EmptyMemIo_586) {
  MemIo memIo;
  memIo.open();
  DataBuf buf = memIo.read(5);
  EXPECT_EQ(buf.size(), 0u);
}

// ==================== read(byte*, size_t) Tests ====================

TEST_F(MemIoTest_586, Read_Buffer_ReadsCorrectAmount_586) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  byte buf[5] = {};
  size_t bytesRead = memIo.read(buf, 3);
  EXPECT_EQ(bytesRead, 3u);
  EXPECT_EQ(buf[0], 0x01);
  EXPECT_EQ(buf[1], 0x02);
  EXPECT_EQ(buf[2], 0x03);
}

TEST_F(MemIoTest_586, Read_Buffer_ReadMoreThanAvailable_586) {
  const byte data[] = {0x01, 0x02};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  byte buf[10] = {};
  size_t bytesRead = memIo.read(buf, 10);
  EXPECT_EQ(bytesRead, 2u);
}

TEST_F(MemIoTest_586, Read_Buffer_SequentialReads_586) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  byte buf1[2] = {};
  byte buf2[2] = {};
  memIo.read(buf1, 2);
  memIo.read(buf2, 2);
  EXPECT_EQ(buf1[0], 0x01);
  EXPECT_EQ(buf1[1], 0x02);
  EXPECT_EQ(buf2[0], 0x03);
  EXPECT_EQ(buf2[1], 0x04);
}

// ==================== getb() Tests ====================

TEST_F(MemIoTest_586, Getb_ReadsSingleByte_586) {
  const byte data[] = {0x42};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  int result = memIo.getb();
  EXPECT_EQ(result, 0x42);
}

TEST_F(MemIoTest_586, Getb_ReturnsEofAtEnd_586) {
  MemIo memIo;
  memIo.open();
  int result = memIo.getb();
  EXPECT_EQ(result, EOF);
}

TEST_F(MemIoTest_586, Getb_SequentialReads_586) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  EXPECT_EQ(memIo.getb(), 0x01);
  EXPECT_EQ(memIo.getb(), 0x02);
  EXPECT_EQ(memIo.getb(), 0x03);
  EXPECT_EQ(memIo.getb(), EOF);
}

// ==================== seek() Tests ====================

TEST_F(MemIoTest_586, Seek_FromBeginning_586) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  int result = memIo.seek(3, BasicIo::beg);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_586, Seek_FromCurrent_586) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  memIo.seek(2, BasicIo::beg);
  int result = memIo.seek(1, BasicIo::cur);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_586, Seek_FromEnd_586) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  int result = memIo.seek(0, BasicIo::end);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(memIo.tell(), 5u);
}

TEST_F(MemIoTest_586, Seek_FromEnd_Negative_586) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  int result = memIo.seek(-2, BasicIo::end);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_586, Seek_ToBeginning_586) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  memIo.read(3);
  memIo.seek(0, BasicIo::beg);
  EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_586, Seek_InvalidNegativeFromBeginning_586) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  int result = memIo.seek(-1, BasicIo::beg);
  EXPECT_NE(result, 0);
}

// ==================== tell() Tests ====================

TEST_F(MemIoTest_586, Tell_InitialPositionAfterOpen_586) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_586, Tell_AdvancesAfterRead_586) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  memIo.read(3);
  EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_586, Tell_AdvancesAfterWrite_586) {
  MemIo memIo;
  const byte data[] = {0x01, 0x02, 0x03};
  memIo.write(data, sizeof(data));
  EXPECT_EQ(memIo.tell(), 3u);
}

// ==================== size() Tests ====================

TEST_F(MemIoTest_586, Size_EmptyMemIo_586) {
  MemIo memIo;
  EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_586, Size_AfterConstruction_586) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  EXPECT_EQ(memIo.size(), 3u);
}

TEST_F(MemIoTest_586, Size_AfterWrite_586) {
  MemIo memIo;
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  memIo.write(data, sizeof(data));
  EXPECT_EQ(memIo.size(), 5u);
}

// ==================== isopen() Tests ====================

TEST_F(MemIoTest_586, Isopen_AlwaysTrue_586) {
  MemIo memIo;
  // MemIo is typically always considered open
  EXPECT_TRUE(memIo.isopen());
}

TEST_F(MemIoTest_586, Isopen_AfterOpen_586) {
  MemIo memIo;
  memIo.open();
  EXPECT_TRUE(memIo.isopen());
}

TEST_F(MemIoTest_586, Isopen_AfterClose_586) {
  MemIo memIo;
  memIo.open();
  memIo.close();
  // MemIo should still report as open (memory is always accessible)
  EXPECT_TRUE(memIo.isopen());
}

// ==================== error() Tests ====================

TEST_F(MemIoTest_586, Error_InitiallyNoError_586) {
  MemIo memIo;
  EXPECT_EQ(memIo.error(), 0);
}

TEST_F(MemIoTest_586, Error_AfterNormalOperations_586) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  memIo.read(3);
  EXPECT_EQ(memIo.error(), 0);
}

// ==================== eof() Tests ====================

TEST_F(MemIoTest_586, Eof_InitiallyFalse_586) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  EXPECT_FALSE(memIo.eof());
}

TEST_F(MemIoTest_586, Eof_AfterReadingAll_586) {
  const byte data[] = {0x01, 0x02};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  byte buf[10];
  memIo.read(buf, 10);  // Try to read more than available
  EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_586, Eof_AfterGetbPastEnd_586) {
  const byte data[] = {0x01};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  memIo.getb();
  memIo.getb();  // This should hit EOF
  EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_586, Eof_ResetByOpen_586) {
  const byte data[] = {0x01};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  memIo.getb();
  memIo.getb();
  EXPECT_TRUE(memIo.eof());
  memIo.open();
  EXPECT_FALSE(memIo.eof());
}

TEST_F(MemIoTest_586, Eof_EmptyMemIo_586) {
  MemIo memIo;
  memIo.open();
  // Reading from empty should trigger EOF
  memIo.getb();
  EXPECT_TRUE(memIo.eof());
}

// ==================== path() Tests ====================

TEST_F(MemIoTest_586, Path_ReturnsNonEmpty_586) {
  MemIo memIo;
  const std::string& p = memIo.path();
  // MemIo should have some path representation (even if synthetic)
  EXPECT_FALSE(p.empty());
}

// ==================== mmap/munmap Tests ====================

TEST_F(MemIoTest_586, Mmap_ReturnsNonNullForNonEmpty_586) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  byte* mapped = memIo.mmap(false);
  EXPECT_NE(mapped, nullptr);
  EXPECT_EQ(mapped[0], 0x01);
  EXPECT_EQ(mapped[1], 0x02);
  EXPECT_EQ(mapped[2], 0x03);
  memIo.munmap();
}

TEST_F(MemIoTest_586, Munmap_ReturnsZero_586) {
  const byte data[] = {0x01, 0x02};
  MemIo memIo(data, sizeof(data));
  memIo.mmap(false);
  int result = memIo.munmap();
  EXPECT_EQ(result, 0);
}

// ==================== transfer() Tests ====================

TEST_F(MemIoTest_586, Transfer_MovesDataFromSource_586) {
  const byte data[] = {0x0A, 0x0B, 0x0C, 0x0D};
  MemIo src(data, sizeof(data));
  MemIo dest;
  dest.transfer(src);
  EXPECT_EQ(dest.size(), sizeof(data));
}

TEST_F(MemIoTest_586, Transfer_EmptySource_586) {
  MemIo src;
  MemIo dest;
  const byte initialData[] = {0x01};
  dest.write(initialData, 1);
  dest.transfer(src);
  EXPECT_EQ(dest.size(), 0u);
}

// ==================== Write then Read Tests ====================

TEST_F(MemIoTest_586, WriteAndRead_RoundTrip_586) {
  MemIo memIo;
  const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
  memIo.write(data, sizeof(data));
  memIo.seek(0, BasicIo::beg);
  byte buf[4] = {};
  size_t bytesRead = memIo.read(buf, 4);
  EXPECT_EQ(bytesRead, 4u);
  EXPECT_EQ(buf[0], 0xDE);
  EXPECT_EQ(buf[1], 0xAD);
  EXPECT_EQ(buf[2], 0xBE);
  EXPECT_EQ(buf[3], 0xEF);
}

TEST_F(MemIoTest_586, PutbAndGetb_RoundTrip_586) {
  MemIo memIo;
  memIo.putb(0x55);
  memIo.putb(0xAA);
  memIo.seek(0, BasicIo::beg);
  EXPECT_EQ(memIo.getb(), 0x55);
  EXPECT_EQ(memIo.getb(), 0xAA);
  EXPECT_EQ(memIo.getb(), EOF);
}

// ==================== Large Data Tests ====================

TEST_F(MemIoTest_586, Write_LargeData_586) {
  MemIo memIo;
  const size_t largeSize = 1024 * 1024;  // 1 MB
  std::vector<byte> data(largeSize, 0x42);
  size_t written = memIo.write(data.data(), largeSize);
  EXPECT_EQ(written, largeSize);
  EXPECT_EQ(memIo.size(), largeSize);
}

// ==================== Seek and Read Combination ====================

TEST_F(MemIoTest_586, SeekAndRead_FromMiddle_586) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  memIo.seek(2, BasicIo::beg);
  int b = memIo.getb();
  EXPECT_EQ(b, 0x03);
}

TEST_F(MemIoTest_586, SeekBackward_FromCurrent_586) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.open();
  memIo.seek(4, BasicIo::beg);
  memIo.seek(-2, BasicIo::cur);
  EXPECT_EQ(memIo.tell(), 2u);
  EXPECT_EQ(memIo.getb(), 0x03);
}

// ==================== populateFakeData Tests ====================

TEST_F(MemIoTest_586, PopulateFakeData_DoesNotCrash_586) {
  MemIo memIo;
  EXPECT_NO_THROW(memIo.populateFakeData());
}
