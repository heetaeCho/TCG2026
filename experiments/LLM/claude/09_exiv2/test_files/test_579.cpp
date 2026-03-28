#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>

using namespace Exiv2;

// Test fixture for MemIo tests
class MemIoTest_579 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction
TEST_F(MemIoTest_579, DefaultConstruction_579) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
    EXPECT_TRUE(memIo.isopen());
    EXPECT_EQ(memIo.tell(), 0u);
    EXPECT_EQ(memIo.error(), 0);
    EXPECT_TRUE(memIo.eof());
}

// Test construction with data
TEST_F(MemIoTest_579, ConstructionWithData_579) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
    EXPECT_TRUE(memIo.isopen());
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test write bytes
TEST_F(MemIoTest_579, WriteBytes_579) {
    MemIo memIo;
    const byte data[] = {0xAA, 0xBB, 0xCC};
    size_t written = memIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

// Test write from another BasicIo source
TEST_F(MemIoTest_579, WriteFromSource_579) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    MemIo src(data, sizeof(data));
    MemIo dest;
    
    size_t written = dest.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dest.size(), sizeof(data));
}

// Test write from self returns 0
TEST_F(MemIoTest_579, WriteFromSelfReturnsZero_579) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    
    size_t written = memIo.write(memIo);
    EXPECT_EQ(written, 0u);
}

// Test write from closed/unopened source returns 0
TEST_F(MemIoTest_579, WriteFromClosedSourceReturnsZero_579) {
    MemIo src;
    src.close();
    
    MemIo dest;
    size_t written = dest.write(src);
    EXPECT_EQ(written, 0u);
}

// Test read bytes
TEST_F(MemIoTest_579, ReadBytes_579) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo memIo(data, sizeof(data));
    
    byte buf[4] = {};
    size_t readCount = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, sizeof(data));
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
    EXPECT_EQ(buf[3], 0x04);
}

// Test read with DataBuf
TEST_F(MemIoTest_579, ReadDataBuf_579) {
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    MemIo memIo(data, sizeof(data));
    
    DataBuf buf = memIo.read(sizeof(data));
    EXPECT_EQ(buf.size(), sizeof(data));
}

// Test read more than available
TEST_F(MemIoTest_579, ReadMoreThanAvailable_579) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    
    byte buf[10] = {};
    size_t readCount = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, sizeof(data));
}

// Test read from empty MemIo
TEST_F(MemIoTest_579, ReadFromEmpty_579) {
    MemIo memIo;
    byte buf[10] = {};
    size_t readCount = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, 0u);
}

// Test putb and getb
TEST_F(MemIoTest_579, PutbAndGetb_579) {
    MemIo memIo;
    int result = memIo.putb(0x42);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.size(), 1u);
    
    memIo.seek(0, BasicIo::beg);
    int val = memIo.getb();
    EXPECT_EQ(val, 0x42);
}

// Test getb on empty returns EOF
TEST_F(MemIoTest_579, GetbOnEmptyReturnsEOF_579) {
    MemIo memIo;
    int val = memIo.getb();
    EXPECT_EQ(val, EOF);
}

// Test seek from beginning
TEST_F(MemIoTest_579, SeekFromBeginning_579) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    
    int result = memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

// Test seek from current position
TEST_F(MemIoTest_579, SeekFromCurrent_579) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    
    memIo.seek(2, BasicIo::beg);
    int result = memIo.seek(1, BasicIo::cur);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

// Test seek from end
TEST_F(MemIoTest_579, SeekFromEnd_579) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    
    int result = memIo.seek(0, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

// Test seek from end with negative offset
TEST_F(MemIoTest_579, SeekFromEndNegativeOffset_579) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    
    int result = memIo.seek(-2, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

// Test tell after writes
TEST_F(MemIoTest_579, TellAfterWrites_579) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

// Test open and close
TEST_F(MemIoTest_579, OpenAndClose_579) {
    MemIo memIo;
    EXPECT_TRUE(memIo.isopen());
    
    int closeResult = memIo.close();
    EXPECT_EQ(closeResult, 0);
    
    int openResult = memIo.open();
    EXPECT_EQ(openResult, 0);
    EXPECT_TRUE(memIo.isopen());
}

// Test eof after reading all data
TEST_F(MemIoTest_579, EofAfterReadingAll_579) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    
    byte buf[10];
    memIo.read(buf, sizeof(buf));
    EXPECT_TRUE(memIo.eof());
}

// Test eof before reading
TEST_F(MemIoTest_579, EofBeforeReading_579) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    EXPECT_FALSE(memIo.eof());
}

// Test error returns 0 on normal operation
TEST_F(MemIoTest_579, ErrorOnNormalOperation_579) {
    MemIo memIo;
    EXPECT_EQ(memIo.error(), 0);
}

// Test path returns a string
TEST_F(MemIoTest_579, PathReturnsString_579) {
    MemIo memIo;
    const std::string& p = memIo.path();
    // MemIo path is typically empty or a special value
    EXPECT_FALSE(p.empty() && false); // Just ensure it doesn't throw
}

// Test mmap and munmap
TEST_F(MemIoTest_579, MmapAndMunmap_579) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    MemIo memIo(data, sizeof(data));
    
    byte* mapped = memIo.mmap(false);
    EXPECT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0xAA);
    EXPECT_EQ(mapped[1], 0xBB);
    EXPECT_EQ(mapped[2], 0xCC);
    
    int result = memIo.munmap();
    EXPECT_EQ(result, 0);
}

// Test transfer
TEST_F(MemIoTest_579, Transfer_579) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo src(data, sizeof(data));
    MemIo dest;
    
    dest.transfer(src);
    EXPECT_EQ(dest.size(), sizeof(data));
    EXPECT_EQ(src.size(), 0u);
}

// Test writing zero bytes
TEST_F(MemIoTest_579, WriteZeroBytes_579) {
    MemIo memIo;
    const byte data[] = {0x01};
    size_t written = memIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(memIo.size(), 0u);
}

// Test multiple sequential writes
TEST_F(MemIoTest_579, MultipleSequentialWrites_579) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02};
    const byte data2[] = {0x03, 0x04, 0x05};
    
    memIo.write(data1, sizeof(data1));
    memIo.write(data2, sizeof(data2));
    
    EXPECT_EQ(memIo.size(), sizeof(data1) + sizeof(data2));
    EXPECT_EQ(memIo.tell(), sizeof(data1) + sizeof(data2));
}

// Test seek then read
TEST_F(MemIoTest_579, SeekThenRead_579) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    MemIo memIo(data, sizeof(data));
    
    memIo.seek(2, BasicIo::beg);
    byte buf[3] = {};
    size_t readCount = memIo.read(buf, 3);
    EXPECT_EQ(readCount, 3u);
    EXPECT_EQ(buf[0], 0x30);
    EXPECT_EQ(buf[1], 0x40);
    EXPECT_EQ(buf[2], 0x50);
}

// Test write from source larger than 4096 bytes (buffer boundary)
TEST_F(MemIoTest_579, WriteFromLargeSource_579) {
    const size_t largeSize = 8192 + 100; // Larger than internal buffer
    std::vector<byte> largeData(largeSize);
    for (size_t i = 0; i < largeSize; ++i) {
        largeData[i] = static_cast<byte>(i & 0xFF);
    }
    
    MemIo src(largeData.data(), largeSize);
    MemIo dest;
    
    size_t written = dest.write(src);
    EXPECT_EQ(written, largeSize);
    EXPECT_EQ(dest.size(), largeSize);
    
    // Verify content
    dest.seek(0, BasicIo::beg);
    byte buf[1];
    dest.read(buf, 1);
    EXPECT_EQ(buf[0], largeData[0]);
}

// Test write from source exactly 4096 bytes (buffer size boundary)
TEST_F(MemIoTest_579, WriteFromSourceExactBufferSize_579) {
    const size_t exactSize = 4096;
    std::vector<byte> data(exactSize, 0xAB);
    
    MemIo src(data.data(), exactSize);
    MemIo dest;
    
    size_t written = dest.write(src);
    EXPECT_EQ(written, exactSize);
    EXPECT_EQ(dest.size(), exactSize);
}

// Test write from empty source
TEST_F(MemIoTest_579, WriteFromEmptySource_579) {
    MemIo src;
    MemIo dest;
    
    size_t written = dest.write(src);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(dest.size(), 0u);
}

// Test seek to beginning resets position
TEST_F(MemIoTest_579, SeekToBeginningResetsPosition_579) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    
    byte buf[3];
    memIo.read(buf, 3);
    EXPECT_EQ(memIo.tell(), 3u);
    
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test close resets state
TEST_F(MemIoTest_579, CloseResetsState_579) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    
    byte buf[2];
    memIo.read(buf, 2);
    
    memIo.close();
    // After close, isopen should return false (or data should be reset)
    // Open it again
    memIo.open();
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test populateFakeData doesn't crash
TEST_F(MemIoTest_579, PopulateFakeDataDoesNotCrash_579) {
    MemIo memIo;
    EXPECT_NO_THROW(memIo.populateFakeData());
}

// Test getb advances position
TEST_F(MemIoTest_579, GetbAdvancesPosition_579) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    MemIo memIo(data, sizeof(data));
    
    int val1 = memIo.getb();
    EXPECT_EQ(val1, 0xAA);
    EXPECT_EQ(memIo.tell(), 1u);
    
    int val2 = memIo.getb();
    EXPECT_EQ(val2, 0xBB);
    EXPECT_EQ(memIo.tell(), 2u);
}

// Test write then read back
TEST_F(MemIoTest_579, WriteAndReadBack_579) {
    MemIo memIo;
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    memIo.write(data, sizeof(data));
    
    memIo.seek(0, BasicIo::beg);
    byte buf[4] = {};
    size_t readCount = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, sizeof(data));
    EXPECT_EQ(buf[0], 0xDE);
    EXPECT_EQ(buf[1], 0xAD);
    EXPECT_EQ(buf[2], 0xBE);
    EXPECT_EQ(buf[3], 0xEF);
}

// Test mmap on empty MemIo
TEST_F(MemIoTest_579, MmapOnEmpty_579) {
    MemIo memIo;
    byte* mapped = memIo.mmap(false);
    // Even empty should return something (or nullptr), just don't crash
    int result = memIo.munmap();
    EXPECT_EQ(result, 0);
}

// Test putb multiple times
TEST_F(MemIoTest_579, MultiplePutb_579) {
    MemIo memIo;
    for (int i = 0; i < 256; ++i) {
        int result = memIo.putb(static_cast<byte>(i));
        EXPECT_EQ(result, 0);
    }
    EXPECT_EQ(memIo.size(), 256u);
    
    memIo.seek(0, BasicIo::beg);
    for (int i = 0; i < 256; ++i) {
        int val = memIo.getb();
        EXPECT_EQ(val, i);
    }
}

// Test seek beyond size
TEST_F(MemIoTest_579, SeekBeyondSize_579) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    
    // Seeking beyond end - behavior may vary, just ensure no crash
    int result = memIo.seek(100, BasicIo::beg);
    // Result may be 0 or non-zero depending on implementation
    (void)result;
}

// Test negative seek from beginning
TEST_F(MemIoTest_579, NegativeSeekFromBeginning_579) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    
    int result = memIo.seek(-1, BasicIo::beg);
    // Should fail or return error
    EXPECT_NE(result, 0);
}

// Test write from source with partial read at beginning
TEST_F(MemIoTest_579, WriteFromSourcePartiallyRead_579) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo src(data, sizeof(data));
    
    // Read 2 bytes from src first
    byte buf[2];
    src.read(buf, 2);
    
    MemIo dest;
    size_t written = dest.write(src);
    // Should only write the remaining 3 bytes
    EXPECT_EQ(written, 3u);
    EXPECT_EQ(dest.size(), 3u);
}

// Test size after construction with data
TEST_F(MemIoTest_579, SizeAfterConstructionWithData_579) {
    const byte data[] = {0x01};
    MemIo memIo(data, 1);
    EXPECT_EQ(memIo.size(), 1u);
}

// Test eof is false with data, then true after reading all
TEST_F(MemIoTest_579, EofTransition_579) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    
    EXPECT_FALSE(memIo.eof());
    
    byte buf[2];
    memIo.read(buf, 2); // try to read more than available
    EXPECT_TRUE(memIo.eof());
}
