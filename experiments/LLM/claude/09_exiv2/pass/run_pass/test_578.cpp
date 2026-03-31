#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <cstring>

using namespace Exiv2;

class MemIoTest_578 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor creates empty MemIo
TEST_F(MemIoTest_578, DefaultConstructorCreatesEmptyMemIo_578) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test constructor with data
TEST_F(MemIoTest_578, DataConstructorCopiesData_578) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

// Test open returns 0
TEST_F(MemIoTest_578, OpenReturnsZero_578) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
}

// Test close returns 0
TEST_F(MemIoTest_578, CloseReturnsZero_578) {
    MemIo memIo;
    EXPECT_EQ(memIo.close(), 0);
}

// Test isopen after construction
TEST_F(MemIoTest_578, IsOpenAfterConstruction_578) {
    MemIo memIo;
    EXPECT_TRUE(memIo.isopen());
}

// Test write data
TEST_F(MemIoTest_578, WriteDataIncreasesSize_578) {
    MemIo memIo;
    const byte data[] = {0x41, 0x42, 0x43};
    size_t written = memIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

// Test write zero bytes
TEST_F(MemIoTest_578, WriteZeroBytesDoesNotChangeSize_578) {
    MemIo memIo;
    const byte data[] = {0x01};
    size_t written = memIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(memIo.size(), 0u);
}

// Test read after write
TEST_F(MemIoTest_578, ReadAfterWriteReturnsCorrectData_578) {
    MemIo memIo;
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    memIo.write(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    
    byte buf[4] = {};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, sizeof(data));
    EXPECT_EQ(std::memcmp(buf, data, sizeof(data)), 0);
}

// Test seek to beginning
TEST_F(MemIoTest_578, SeekToBeginning_578) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    int result = memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test seek to end
TEST_F(MemIoTest_578, SeekToEnd_578) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    memIo.seek(0, BasicIo::end);
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

// Test seek from current position
TEST_F(MemIoTest_578, SeekFromCurrentPosition_578) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    memIo.write(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    memIo.seek(2, BasicIo::cur);
    EXPECT_EQ(memIo.tell(), 2u);
}

// Test tell after write
TEST_F(MemIoTest_578, TellAfterWriteIsAtEnd_578) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

// Test putb writes single byte
TEST_F(MemIoTest_578, PutbWritesSingleByte_578) {
    MemIo memIo;
    int result = memIo.putb(0x42);
    EXPECT_EQ(result, 0x42);
    EXPECT_EQ(memIo.size(), 1u);
}

// Test getb reads single byte
TEST_F(MemIoTest_578, GetbReadsSingleByte_578) {
    const byte data[] = {0x42};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    int result = memIo.getb();
    EXPECT_EQ(result, 0x42);
}

// Test getb returns EOF at end
TEST_F(MemIoTest_578, GetbReturnsEofAtEnd_578) {
    MemIo memIo;
    int result = memIo.getb();
    EXPECT_EQ(result, EOF);
}

// Test eof
TEST_F(MemIoTest_578, EofReturnsTrueWhenAtEnd_578) {
    MemIo memIo;
    const byte data[] = {0x01};
    memIo.write(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    memIo.read(const_cast<byte*>(data), 1);
    // After reading all data, try reading one more to trigger EOF
    byte buf[1];
    memIo.read(buf, 1);
    EXPECT_TRUE(memIo.eof());
}

// Test error returns 0 normally
TEST_F(MemIoTest_578, ErrorReturnsZeroNormally_578) {
    MemIo memIo;
    EXPECT_EQ(memIo.error(), 0);
}

// Test path returns non-empty string
TEST_F(MemIoTest_578, PathReturnsString_578) {
    MemIo memIo;
    const std::string& p = memIo.path();
    EXPECT_FALSE(p.empty());
}

// Test transfer between two MemIo objects
TEST_F(MemIoTest_578, TransferBetweenMemIos_578) {
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    MemIo src(data, sizeof(data));
    MemIo dst;
    
    dst.transfer(src);
    
    EXPECT_EQ(dst.size(), sizeof(data));
    EXPECT_EQ(src.size(), 0u);
    
    // Verify transferred data is correct
    dst.seek(0, BasicIo::beg);
    byte buf[4] = {};
    dst.read(buf, sizeof(buf));
    EXPECT_EQ(std::memcmp(buf, data, sizeof(data)), 0);
}

// Test transfer empties source MemIo
TEST_F(MemIoTest_578, TransferEmptiesSource_578) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo src(data, sizeof(data));
    MemIo dst;
    
    dst.transfer(src);
    
    EXPECT_EQ(src.size(), 0u);
    EXPECT_EQ(src.tell(), 0u);
}

// Test transfer resets destination index
TEST_F(MemIoTest_578, TransferResetsDestinationIndex_578) {
    const byte srcData[] = {0x01, 0x02};
    const byte dstData[] = {0xAA, 0xBB, 0xCC};
    
    MemIo src(srcData, sizeof(srcData));
    MemIo dst(dstData, sizeof(dstData));
    
    // Move dst position
    dst.seek(2, BasicIo::beg);
    EXPECT_EQ(dst.tell(), 2u);
    
    dst.transfer(src);
    
    // After transfer, the tell should reflect the state of the transferred data
    // The implementation resets idx to 0
    EXPECT_EQ(dst.tell(), 0u);
}

// Test transfer from empty MemIo
TEST_F(MemIoTest_578, TransferFromEmptyMemIo_578) {
    MemIo src;
    MemIo dst;
    const byte data[] = {0x01, 0x02};
    dst.write(data, sizeof(data));
    
    dst.transfer(src);
    
    EXPECT_EQ(dst.size(), 0u);
    EXPECT_EQ(src.size(), 0u);
}

// Test write from another BasicIo (MemIo)
TEST_F(MemIoTest_578, WriteFromAnotherMemIo_578) {
    const byte data[] = {0x10, 0x20, 0x30};
    MemIo src(data, sizeof(data));
    MemIo dst;
    
    size_t written = dst.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dst.size(), sizeof(data));
}

// Test read with DataBuf
TEST_F(MemIoTest_578, ReadReturnsDataBuf_578) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    
    DataBuf buf = memIo.read(sizeof(data));
    EXPECT_EQ(buf.size(), sizeof(data));
}

// Test read more than available
TEST_F(MemIoTest_578, ReadMoreThanAvailable_578) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    
    byte buf[10] = {};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, sizeof(data));
}

// Test multiple writes
TEST_F(MemIoTest_578, MultipleWritesConcatenate_578) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02};
    const byte data2[] = {0x03, 0x04};
    
    memIo.write(data1, sizeof(data1));
    memIo.write(data2, sizeof(data2));
    
    EXPECT_EQ(memIo.size(), sizeof(data1) + sizeof(data2));
    
    memIo.seek(0, BasicIo::beg);
    byte buf[4] = {};
    memIo.read(buf, 4);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
    EXPECT_EQ(buf[3], 0x04);
}

// Test mmap
TEST_F(MemIoTest_578, MmapReturnsPointerToData_578) {
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    MemIo memIo(data, sizeof(data));
    
    byte* ptr = memIo.mmap(false);
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 0xDE);
    EXPECT_EQ(ptr[1], 0xAD);
    EXPECT_EQ(ptr[2], 0xBE);
    EXPECT_EQ(ptr[3], 0xEF);
    
    memIo.munmap();
}

// Test munmap
TEST_F(MemIoTest_578, MunmapReturnsZero_578) {
    MemIo memIo;
    int result = memIo.munmap();
    EXPECT_EQ(result, 0);
}

// Test seek with negative offset from end
TEST_F(MemIoTest_578, SeekNegativeFromEnd_578) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    
    int result = memIo.seek(-2, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

// Test seek beyond end returns error
TEST_F(MemIoTest_578, SeekBeyondEndReturnsError_578) {
    MemIo memIo;
    int result = memIo.seek(-1, BasicIo::beg);
    EXPECT_NE(result, 0);
}

// Test size after construction with data
TEST_F(MemIoTest_578, SizeAfterDataConstruction_578) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 8u);
}

// Test transfer with large data
TEST_F(MemIoTest_578, TransferLargeData_578) {
    std::vector<byte> largeData(10000);
    for (size_t i = 0; i < largeData.size(); ++i) {
        largeData[i] = static_cast<byte>(i % 256);
    }
    
    MemIo src(largeData.data(), largeData.size());
    MemIo dst;
    
    dst.transfer(src);
    
    EXPECT_EQ(dst.size(), largeData.size());
    EXPECT_EQ(src.size(), 0u);
    
    dst.seek(0, BasicIo::beg);
    byte buf[10000];
    size_t bytesRead = dst.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, largeData.size());
    EXPECT_EQ(std::memcmp(buf, largeData.data(), largeData.size()), 0);
}

// Test double transfer
TEST_F(MemIoTest_578, DoubleTransfer_578) {
    const byte data[] = {0x11, 0x22, 0x33};
    MemIo a(data, sizeof(data));
    MemIo b;
    MemIo c;
    
    b.transfer(a);
    EXPECT_EQ(b.size(), sizeof(data));
    EXPECT_EQ(a.size(), 0u);
    
    c.transfer(b);
    EXPECT_EQ(c.size(), sizeof(data));
    EXPECT_EQ(b.size(), 0u);
    
    c.seek(0, BasicIo::beg);
    byte buf[3];
    c.read(buf, 3);
    EXPECT_EQ(std::memcmp(buf, data, sizeof(data)), 0);
}

// Test eof on empty MemIo
TEST_F(MemIoTest_578, EofOnEmptyMemIo_578) {
    MemIo memIo;
    // Try to read from empty
    byte buf[1];
    memIo.read(buf, 1);
    EXPECT_TRUE(memIo.eof());
}

// Test writing after seek overwrites data
TEST_F(MemIoTest_578, WriteAfterSeekOverwrites_578) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo memIo(data, sizeof(data));
    
    memIo.seek(1, BasicIo::beg);
    const byte newData[] = {0xFF};
    memIo.write(newData, sizeof(newData));
    
    memIo.seek(0, BasicIo::beg);
    byte buf[4];
    memIo.read(buf, 4);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0x03);
    EXPECT_EQ(buf[3], 0x04);
}

// Test putb followed by getb
TEST_F(MemIoTest_578, PutbThenGetb_578) {
    MemIo memIo;
    memIo.putb(0x99);
    memIo.seek(0, BasicIo::beg);
    int val = memIo.getb();
    EXPECT_EQ(val, 0x99);
}

// Test populateFakeData doesn't crash
TEST_F(MemIoTest_578, PopulateFakeDataDoesNotCrash_578) {
    MemIo memIo;
    EXPECT_NO_THROW(memIo.populateFakeData());
}

// Test transfer self-consistency after source depleted
TEST_F(MemIoTest_578, SourceAfterTransferIsEmpty_578) {
    const byte data[] = {0xAB, 0xCD};
    MemIo src(data, sizeof(data));
    MemIo dst;
    
    dst.transfer(src);
    
    // Source should be empty and usable
    EXPECT_EQ(src.size(), 0u);
    EXPECT_EQ(src.tell(), 0u);
    EXPECT_EQ(src.error(), 0);
    
    // Writing to depleted source should still work
    const byte newData[] = {0xEF};
    size_t written = src.write(newData, sizeof(newData));
    EXPECT_EQ(written, 1u);
    EXPECT_EQ(src.size(), 1u);
}

// Test open and close cycle
TEST_F(MemIoTest_578, OpenCloseCycle_578) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    
    EXPECT_EQ(memIo.open(), 0);
    EXPECT_TRUE(memIo.isopen());
    EXPECT_EQ(memIo.close(), 0);
}

// Test read DataBuf with zero count
TEST_F(MemIoTest_578, ReadDataBufZeroCount_578) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    
    DataBuf buf = memIo.read(0);
    EXPECT_EQ(buf.size(), 0u);
}
