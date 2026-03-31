#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <cstring>

using namespace Exiv2;

class MemIoTest_584 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== tell() tests ====================

TEST_F(MemIoTest_584, TellReturnsZeroOnDefaultConstruction_584) {
  MemIo memIo;
  EXPECT_EQ(0u, memIo.tell());
}

TEST_F(MemIoTest_584, TellReturnsZeroOnConstructionWithData_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  EXPECT_EQ(0u, memIo.tell());
}

TEST_F(MemIoTest_584, TellAdvancesAfterRead_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  byte buf[3];
  size_t bytesRead = memIo.read(buf, 3);
  EXPECT_EQ(3u, bytesRead);
  EXPECT_EQ(3u, memIo.tell());
}

TEST_F(MemIoTest_584, TellAdvancesAfterWrite_584) {
  MemIo memIo;
  const byte data[] = {0x01, 0x02, 0x03};
  size_t written = memIo.write(data, sizeof(data));
  EXPECT_EQ(3u, written);
  EXPECT_EQ(3u, memIo.tell());
}

TEST_F(MemIoTest_584, TellUpdatesAfterSeekFromBeginning_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.seek(2, BasicIo::beg);
  EXPECT_EQ(2u, memIo.tell());
}

TEST_F(MemIoTest_584, TellUpdatesAfterSeekFromCurrent_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.seek(2, BasicIo::beg);
  memIo.seek(1, BasicIo::cur);
  EXPECT_EQ(3u, memIo.tell());
}

TEST_F(MemIoTest_584, TellUpdatesAfterSeekFromEnd_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.seek(0, BasicIo::end);
  EXPECT_EQ(5u, memIo.tell());
}

TEST_F(MemIoTest_584, TellAfterSeekToBeginning_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.read(3);
  EXPECT_EQ(3u, memIo.tell());
  memIo.seek(0, BasicIo::beg);
  EXPECT_EQ(0u, memIo.tell());
}

TEST_F(MemIoTest_584, TellAfterGetb_584) {
  const byte data[] = {0x41, 0x42, 0x43};
  MemIo memIo(data, sizeof(data));
  memIo.getb();
  EXPECT_EQ(1u, memIo.tell());
  memIo.getb();
  EXPECT_EQ(2u, memIo.tell());
}

TEST_F(MemIoTest_584, TellAfterPutb_584) {
  MemIo memIo;
  memIo.putb(0x41);
  EXPECT_EQ(1u, memIo.tell());
  memIo.putb(0x42);
  EXPECT_EQ(2u, memIo.tell());
}

// ==================== size() tests ====================

TEST_F(MemIoTest_584, SizeReturnsZeroOnDefaultConstruction_584) {
  MemIo memIo;
  EXPECT_EQ(0u, memIo.size());
}

TEST_F(MemIoTest_584, SizeReturnsCorrectSizeOnConstructionWithData_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  EXPECT_EQ(5u, memIo.size());
}

TEST_F(MemIoTest_584, SizeIncreasesAfterWrite_584) {
  MemIo memIo;
  const byte data[] = {0x01, 0x02, 0x03};
  memIo.write(data, sizeof(data));
  EXPECT_EQ(3u, memIo.size());
}

TEST_F(MemIoTest_584, SizeDoesNotChangeAfterRead_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  byte buf[3];
  memIo.read(buf, 3);
  EXPECT_EQ(5u, memIo.size());
}

// ==================== open()/close()/isopen() tests ====================

TEST_F(MemIoTest_584, IsOpenReturnsTrueByDefault_584) {
  MemIo memIo;
  EXPECT_TRUE(memIo.isopen());
}

TEST_F(MemIoTest_584, OpenReturnsZero_584) {
  MemIo memIo;
  EXPECT_EQ(0, memIo.open());
}

TEST_F(MemIoTest_584, CloseReturnsZero_584) {
  MemIo memIo;
  EXPECT_EQ(0, memIo.close());
}

// ==================== read() tests ====================

TEST_F(MemIoTest_584, ReadReturnsCorrectData_584) {
  const byte data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
  MemIo memIo(data, sizeof(data));
  byte buf[5];
  size_t bytesRead = memIo.read(buf, 5);
  EXPECT_EQ(5u, bytesRead);
  EXPECT_EQ(0, std::memcmp(data, buf, 5));
}

TEST_F(MemIoTest_584, ReadDataBufReturnsCorrectSize_584) {
  const byte data[] = {0x41, 0x42, 0x43, 0x44, 0x45};
  MemIo memIo(data, sizeof(data));
  DataBuf buf = memIo.read(3);
  EXPECT_EQ(3u, buf.size());
}

TEST_F(MemIoTest_584, ReadBeyondSizeReturnsAvailableBytes_584) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  byte buf[10];
  size_t bytesRead = memIo.read(buf, 10);
  EXPECT_EQ(3u, bytesRead);
}

TEST_F(MemIoTest_584, ReadZeroBytesReturnsZero_584) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  byte buf[1];
  size_t bytesRead = memIo.read(buf, 0);
  EXPECT_EQ(0u, bytesRead);
  EXPECT_EQ(0u, memIo.tell());
}

// ==================== write() tests ====================

TEST_F(MemIoTest_584, WriteDataAndReadBack_584) {
  MemIo memIo;
  const byte data[] = {0x41, 0x42, 0x43};
  memIo.write(data, sizeof(data));
  memIo.seek(0, BasicIo::beg);
  byte buf[3];
  size_t bytesRead = memIo.read(buf, 3);
  EXPECT_EQ(3u, bytesRead);
  EXPECT_EQ(0, std::memcmp(data, buf, 3));
}

TEST_F(MemIoTest_584, WriteZeroBytesDoesNotChangeSize_584) {
  MemIo memIo;
  const byte data[] = {0x01};
  size_t written = memIo.write(data, 0);
  EXPECT_EQ(0u, written);
  EXPECT_EQ(0u, memIo.size());
}

TEST_F(MemIoTest_584, WriteFromBasicIo_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04};
  MemIo src(data, sizeof(data));
  MemIo dest;
  size_t written = dest.write(src);
  EXPECT_EQ(4u, written);
  EXPECT_EQ(4u, dest.size());
}

// ==================== getb() tests ====================

TEST_F(MemIoTest_584, GetbReturnsCorrectByte_584) {
  const byte data[] = {0x41, 0x42, 0x43};
  MemIo memIo(data, sizeof(data));
  EXPECT_EQ(0x41, memIo.getb());
  EXPECT_EQ(0x42, memIo.getb());
  EXPECT_EQ(0x43, memIo.getb());
}

TEST_F(MemIoTest_584, GetbReturnsEOFAtEnd_584) {
  const byte data[] = {0x41};
  MemIo memIo(data, sizeof(data));
  EXPECT_EQ(0x41, memIo.getb());
  EXPECT_EQ(EOF, memIo.getb());
}

TEST_F(MemIoTest_584, GetbReturnsEOFOnEmpty_584) {
  MemIo memIo;
  EXPECT_EQ(EOF, memIo.getb());
}

// ==================== putb() tests ====================

TEST_F(MemIoTest_584, PutbWritesByteAndReturnsZero_584) {
  MemIo memIo;
  int result = memIo.putb(0x41);
  EXPECT_EQ(0, result);
  EXPECT_EQ(1u, memIo.size());
  memIo.seek(0, BasicIo::beg);
  EXPECT_EQ(0x41, memIo.getb());
}

// ==================== seek() tests ====================

TEST_F(MemIoTest_584, SeekBegSetsPositionCorrectly_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  int result = memIo.seek(3, BasicIo::beg);
  EXPECT_EQ(0, result);
  EXPECT_EQ(3u, memIo.tell());
}

TEST_F(MemIoTest_584, SeekCurAdvancesPosition_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  memIo.seek(2, BasicIo::beg);
  int result = memIo.seek(2, BasicIo::cur);
  EXPECT_EQ(0, result);
  EXPECT_EQ(4u, memIo.tell());
}

TEST_F(MemIoTest_584, SeekEndSetsPositionFromEnd_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  int result = memIo.seek(-2, BasicIo::end);
  EXPECT_EQ(0, result);
  EXPECT_EQ(3u, memIo.tell());
}

TEST_F(MemIoTest_584, SeekNegativeOffsetFromBeg_584) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  int result = memIo.seek(-1, BasicIo::beg);
  EXPECT_NE(0, result);
}

// ==================== eof() tests ====================

TEST_F(MemIoTest_584, EofReturnsFalseInitially_584) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  EXPECT_FALSE(memIo.eof());
}

TEST_F(MemIoTest_584, EofReturnsTrueAfterReadingAll_584) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  byte buf[5];
  memIo.read(buf, 5);  // Read more than available
  EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_584, EofOnEmptyMemIo_584) {
  MemIo memIo;
  // Try to read from empty
  memIo.getb();
  EXPECT_TRUE(memIo.eof());
}

// ==================== error() tests ====================

TEST_F(MemIoTest_584, ErrorReturnsZeroInitially_584) {
  MemIo memIo;
  EXPECT_EQ(0, memIo.error());
}

TEST_F(MemIoTest_584, ErrorReturnsZeroAfterNormalOperations_584) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  byte buf[3];
  memIo.read(buf, 3);
  EXPECT_EQ(0, memIo.error());
}

// ==================== path() tests ====================

TEST_F(MemIoTest_584, PathReturnsNonEmptyString_584) {
  MemIo memIo;
  const std::string& p = memIo.path();
  // MemIo typically returns some placeholder path
  EXPECT_FALSE(p.empty());
}

// ==================== transfer() tests ====================

TEST_F(MemIoTest_584, TransferMovesDataFromSource_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo src(data, sizeof(data));
  MemIo dest;
  dest.transfer(src);
  EXPECT_EQ(5u, dest.size());
  dest.seek(0, BasicIo::beg);
  byte buf[5];
  dest.read(buf, 5);
  EXPECT_EQ(0, std::memcmp(data, buf, 5));
}

// ==================== mmap()/munmap() tests ====================

TEST_F(MemIoTest_584, MmapReturnsNonNull_584) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  byte* mapped = memIo.mmap(false);
  EXPECT_NE(nullptr, mapped);
  EXPECT_EQ(0x01, mapped[0]);
  EXPECT_EQ(0x02, mapped[1]);
  EXPECT_EQ(0x03, mapped[2]);
  memIo.munmap();
}

TEST_F(MemIoTest_584, MunmapReturnsZero_584) {
  const byte data[] = {0x01, 0x02, 0x03};
  MemIo memIo(data, sizeof(data));
  memIo.mmap(false);
  EXPECT_EQ(0, memIo.munmap());
}

// ==================== Complex scenario tests ====================

TEST_F(MemIoTest_584, WriteReadSeqMaintainsConsistentTell_584) {
  MemIo memIo;
  const byte data1[] = {0x01, 0x02, 0x03};
  const byte data2[] = {0x04, 0x05};
  
  memIo.write(data1, 3);
  EXPECT_EQ(3u, memIo.tell());
  
  memIo.write(data2, 2);
  EXPECT_EQ(5u, memIo.tell());
  EXPECT_EQ(5u, memIo.size());
  
  memIo.seek(0, BasicIo::beg);
  EXPECT_EQ(0u, memIo.tell());
  
  byte buf[5];
  memIo.read(buf, 5);
  EXPECT_EQ(5u, memIo.tell());
  EXPECT_EQ(0x01, buf[0]);
  EXPECT_EQ(0x04, buf[3]);
  EXPECT_EQ(0x05, buf[4]);
}

TEST_F(MemIoTest_584, MultipleSeekAndReadOperations_584) {
  const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
  MemIo memIo(data, sizeof(data));
  
  memIo.seek(4, BasicIo::beg);
  EXPECT_EQ(0x50, memIo.getb());
  EXPECT_EQ(5u, memIo.tell());
  
  memIo.seek(-3, BasicIo::end);
  EXPECT_EQ(2u, memIo.tell());
  EXPECT_EQ(0x30, memIo.getb());
  
  memIo.seek(0, BasicIo::beg);
  EXPECT_EQ(0u, memIo.tell());
  EXPECT_EQ(0x10, memIo.getb());
}

TEST_F(MemIoTest_584, OverwriteExistingData_584) {
  const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  MemIo memIo(data, sizeof(data));
  
  memIo.seek(2, BasicIo::beg);
  const byte newData[] = {0xFF};
  memIo.write(newData, 1);
  
  memIo.seek(0, BasicIo::beg);
  byte buf[5];
  memIo.read(buf, 5);
  EXPECT_EQ(0x01, buf[0]);
  EXPECT_EQ(0x02, buf[1]);
  EXPECT_EQ(0xFF, buf[2]);
  EXPECT_EQ(0x04, buf[3]);
  EXPECT_EQ(0x05, buf[4]);
}

TEST_F(MemIoTest_584, LargeDataWriteAndRead_584) {
  MemIo memIo;
  const size_t size = 10000;
  std::vector<byte> data(size);
  for (size_t i = 0; i < size; i++) {
    data[i] = static_cast<byte>(i % 256);
  }
  
  memIo.write(data.data(), size);
  EXPECT_EQ(size, memIo.size());
  EXPECT_EQ(size, memIo.tell());
  
  memIo.seek(0, BasicIo::beg);
  std::vector<byte> buf(size);
  size_t bytesRead = memIo.read(buf.data(), size);
  EXPECT_EQ(size, bytesRead);
  EXPECT_EQ(0, std::memcmp(data.data(), buf.data(), size));
}

TEST_F(MemIoTest_584, EmptyMemIoOperations_584) {
  MemIo memIo;
  EXPECT_EQ(0u, memIo.tell());
  EXPECT_EQ(0u, memIo.size());
  EXPECT_EQ(0, memIo.error());
  
  byte buf[1];
  size_t read = memIo.read(buf, 1);
  EXPECT_EQ(0u, read);
}

TEST_F(MemIoTest_584, PopulateFakeDataDoesNotCrash_584) {
  MemIo memIo;
  EXPECT_NO_THROW(memIo.populateFakeData());
}
