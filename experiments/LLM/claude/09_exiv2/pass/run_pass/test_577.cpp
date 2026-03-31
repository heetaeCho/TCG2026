#include <gtest/gtest.h>
#include "exiv2/basicio.hpp"

using namespace Exiv2;

class MemIoTest_577 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// ==================== Constructor Tests ====================

TEST_F(MemIoTest_577, DefaultConstructorCreatesEmptyIo_577) {
    MemIo io;
    EXPECT_EQ(io.size(), 0u);
    EXPECT_EQ(io.tell(), 0u);
}

TEST_F(MemIoTest_577, ConstructorWithDataInitializesCorrectly_577) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo io(data, sizeof(data));
    EXPECT_EQ(io.size(), sizeof(data));
}

// ==================== Write Tests ====================

TEST_F(MemIoTest_577, WriteReturnsCorrectCount_577) {
    MemIo io;
    const byte data[] = {0x01, 0x02, 0x03};
    size_t written = io.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
}

TEST_F(MemIoTest_577, WriteIncreasesSize_577) {
    MemIo io;
    const byte data[] = {0x01, 0x02, 0x03};
    io.write(data, sizeof(data));
    EXPECT_EQ(io.size(), sizeof(data));
}

TEST_F(MemIoTest_577, WriteUpdatesTellPosition_577) {
    MemIo io;
    const byte data[] = {0x01, 0x02, 0x03};
    io.write(data, sizeof(data));
    EXPECT_EQ(io.tell(), sizeof(data));
}

TEST_F(MemIoTest_577, WriteZeroBytesSucceeds_577) {
    MemIo io;
    const byte data[] = {0x01};
    size_t written = io.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(io.size(), 0u);
}

TEST_F(MemIoTest_577, MultipleWritesAccumulateData_577) {
    MemIo io;
    const byte data1[] = {0x01, 0x02};
    const byte data2[] = {0x03, 0x04, 0x05};
    io.write(data1, sizeof(data1));
    io.write(data2, sizeof(data2));
    EXPECT_EQ(io.size(), sizeof(data1) + sizeof(data2));
    EXPECT_EQ(io.tell(), sizeof(data1) + sizeof(data2));
}

TEST_F(MemIoTest_577, WriteDataCanBeReadBack_577) {
    MemIo io;
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    io.write(data, sizeof(data));
    
    io.seek(0, BasicIo::beg);
    byte buf[4] = {};
    size_t readCount = io.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, sizeof(data));
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
    EXPECT_EQ(buf[2], 0xCC);
    EXPECT_EQ(buf[3], 0xDD);
}

TEST_F(MemIoTest_577, WriteWithNullDataStillAdvancesPosition_577) {
    MemIo io;
    size_t written = io.write(nullptr, 5);
    EXPECT_EQ(written, 5u);
    EXPECT_EQ(io.tell(), 5u);
}

TEST_F(MemIoTest_577, WriteLargeDataBlock_577) {
    MemIo io;
    std::vector<byte> data(10000, 0x42);
    size_t written = io.write(data.data(), data.size());
    EXPECT_EQ(written, 10000u);
    EXPECT_EQ(io.size(), 10000u);
}

// ==================== Write from BasicIo Tests ====================

TEST_F(MemIoTest_577, WriteFromAnotherMemIo_577) {
    const byte data[] = {0x10, 0x20, 0x30};
    MemIo src(data, sizeof(data));
    MemIo dest;
    
    size_t written = dest.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dest.size(), sizeof(data));
}

// ==================== Read Tests ====================

TEST_F(MemIoTest_577, ReadIntoBuffer_577) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo io(data, sizeof(data));
    
    byte buf[4] = {};
    size_t readCount = io.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, sizeof(data));
    for (size_t i = 0; i < sizeof(data); ++i) {
        EXPECT_EQ(buf[i], data[i]);
    }
}

TEST_F(MemIoTest_577, ReadReturnsDataBuf_577) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo io(data, sizeof(data));
    
    DataBuf buf = io.read(sizeof(data));
    EXPECT_EQ(buf.size(), sizeof(data));
}

TEST_F(MemIoTest_577, ReadMoreThanAvailable_577) {
    const byte data[] = {0x01, 0x02};
    MemIo io(data, sizeof(data));
    
    byte buf[10] = {};
    size_t readCount = io.read(buf, 10);
    EXPECT_EQ(readCount, sizeof(data));
}

TEST_F(MemIoTest_577, ReadFromEmptyIo_577) {
    MemIo io;
    byte buf[5] = {};
    size_t readCount = io.read(buf, 5);
    EXPECT_EQ(readCount, 0u);
}

TEST_F(MemIoTest_577, ReadUpdatesTellPosition_577) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo io(data, sizeof(data));
    
    byte buf[2] = {};
    io.read(buf, 2);
    EXPECT_EQ(io.tell(), 2u);
}

// ==================== getb / putb Tests ====================

TEST_F(MemIoTest_577, PutbWritesSingleByte_577) {
    MemIo io;
    int result = io.putb(0xAB);
    EXPECT_EQ(result, 0xAB);
    EXPECT_EQ(io.size(), 1u);
    EXPECT_EQ(io.tell(), 1u);
}

TEST_F(MemIoTest_577, GetbReadsSingleByte_577) {
    const byte data[] = {0x42};
    MemIo io(data, sizeof(data));
    
    int val = io.getb();
    EXPECT_EQ(val, 0x42);
    EXPECT_EQ(io.tell(), 1u);
}

TEST_F(MemIoTest_577, GetbAtEofReturnsEof_577) {
    MemIo io;
    int val = io.getb();
    EXPECT_EQ(val, EOF);
}

TEST_F(MemIoTest_577, PutbThenGetb_577) {
    MemIo io;
    io.putb(0x7F);
    io.seek(0, BasicIo::beg);
    int val = io.getb();
    EXPECT_EQ(val, 0x7F);
}

// ==================== Seek Tests ====================

TEST_F(MemIoTest_577, SeekFromBeginning_577) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo io(data, sizeof(data));
    
    int result = io.seek(3, BasicIo::beg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(io.tell(), 3u);
}

TEST_F(MemIoTest_577, SeekFromCurrent_577) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo io(data, sizeof(data));
    
    io.seek(2, BasicIo::beg);
    int result = io.seek(1, BasicIo::cur);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(io.tell(), 3u);
}

TEST_F(MemIoTest_577, SeekFromEnd_577) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo io(data, sizeof(data));
    
    int result = io.seek(0, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(io.tell(), sizeof(data));
}

TEST_F(MemIoTest_577, SeekToZero_577) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo io(data, sizeof(data));
    
    io.read(io.size());
    io.seek(0, BasicIo::beg);
    EXPECT_EQ(io.tell(), 0u);
}

TEST_F(MemIoTest_577, SeekNegativeFromEnd_577) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo io(data, sizeof(data));
    
    int result = io.seek(-2, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(io.tell(), 3u);
}

// ==================== Open / Close Tests ====================

TEST_F(MemIoTest_577, OpenReturnsZero_577) {
    MemIo io;
    EXPECT_EQ(io.open(), 0);
}

TEST_F(MemIoTest_577, CloseReturnsZero_577) {
    MemIo io;
    EXPECT_EQ(io.close(), 0);
}

TEST_F(MemIoTest_577, IsOpenAfterConstruction_577) {
    MemIo io;
    EXPECT_TRUE(io.isopen());
}

// ==================== Size / Tell Tests ====================

TEST_F(MemIoTest_577, SizeAfterConstruction_577) {
    MemIo io;
    EXPECT_EQ(io.size(), 0u);
}

TEST_F(MemIoTest_577, TellAfterConstruction_577) {
    MemIo io;
    EXPECT_EQ(io.tell(), 0u);
}

TEST_F(MemIoTest_577, SizeWithInitialData_577) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo io(data, sizeof(data));
    EXPECT_EQ(io.size(), 3u);
}

// ==================== EOF / Error Tests ====================

TEST_F(MemIoTest_577, EofInitiallyFalse_577) {
    const byte data[] = {0x01};
    MemIo io(data, sizeof(data));
    EXPECT_FALSE(io.eof());
}

TEST_F(MemIoTest_577, EofAfterReadingAllData_577) {
    const byte data[] = {0x01};
    MemIo io(data, sizeof(data));
    
    byte buf[1];
    io.read(buf, 1);
    // Attempt to read past end
    io.read(buf, 1);
    EXPECT_TRUE(io.eof());
}

TEST_F(MemIoTest_577, ErrorInitiallyZero_577) {
    MemIo io;
    EXPECT_EQ(io.error(), 0);
}

// ==================== Path Tests ====================

TEST_F(MemIoTest_577, PathIsNotEmpty_577) {
    MemIo io;
    const std::string& p = io.path();
    // MemIo typically returns a placeholder path
    EXPECT_FALSE(p.empty());
}

// ==================== Mmap / Munmap Tests ====================

TEST_F(MemIoTest_577, MmapReturnsNonNullForNonEmpty_577) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo io(data, sizeof(data));
    
    byte* ptr = io.mmap(false);
    EXPECT_NE(ptr, nullptr);
    io.munmap();
}

TEST_F(MemIoTest_577, MunmapReturnsZero_577) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo io(data, sizeof(data));
    
    io.mmap(false);
    int result = io.munmap();
    EXPECT_EQ(result, 0);
}

// ==================== Transfer Tests ====================

TEST_F(MemIoTest_577, TransferFromAnotherMemIo_577) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    MemIo src(data, sizeof(data));
    MemIo dest;
    
    dest.transfer(src);
    EXPECT_EQ(dest.size(), sizeof(data));
    
    dest.seek(0, BasicIo::beg);
    byte buf[3] = {};
    dest.read(buf, 3);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
    EXPECT_EQ(buf[2], 0xCC);
}

// ==================== Overwrite Tests ====================

TEST_F(MemIoTest_577, WriteOverwritesExistingData_577) {
    const byte initial[] = {0x01, 0x02, 0x03, 0x04};
    MemIo io(initial, sizeof(initial));
    
    io.seek(1, BasicIo::beg);
    const byte overwrite[] = {0xFF, 0xFE};
    io.write(overwrite, sizeof(overwrite));
    
    io.seek(0, BasicIo::beg);
    byte buf[4] = {};
    io.read(buf, 4);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFE);
    EXPECT_EQ(buf[3], 0x04);
}

TEST_F(MemIoTest_577, WriteExtendsBuffer_577) {
    const byte initial[] = {0x01, 0x02};
    MemIo io(initial, sizeof(initial));
    
    io.seek(0, BasicIo::end);
    const byte extra[] = {0x03, 0x04};
    io.write(extra, sizeof(extra));
    
    EXPECT_EQ(io.size(), 4u);
    
    io.seek(0, BasicIo::beg);
    byte buf[4] = {};
    io.read(buf, 4);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
    EXPECT_EQ(buf[3], 0x04);
}

// ==================== PopulateFakeData Tests ====================

TEST_F(MemIoTest_577, PopulateFakeDataDoesNotCrash_577) {
    MemIo io;
    EXPECT_NO_THROW(io.populateFakeData());
}

// ==================== Sequential Read/Write Tests ====================

TEST_F(MemIoTest_577, SequentialWriteAndRead_577) {
    MemIo io;
    
    for (byte i = 0; i < 10; ++i) {
        io.putb(i);
    }
    
    EXPECT_EQ(io.size(), 10u);
    EXPECT_EQ(io.tell(), 10u);
    
    io.seek(0, BasicIo::beg);
    for (byte i = 0; i < 10; ++i) {
        int val = io.getb();
        EXPECT_EQ(val, static_cast<int>(i));
    }
}

TEST_F(MemIoTest_577, ReadAfterSeekToBeg_577) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    MemIo io(data, sizeof(data));
    
    // Read all
    byte buf[5];
    io.read(buf, 5);
    EXPECT_EQ(io.tell(), 5u);
    
    // Seek back to beginning and read again
    io.seek(0, BasicIo::beg);
    byte buf2[5] = {};
    size_t count = io.read(buf2, 5);
    EXPECT_EQ(count, 5u);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(buf2[i], data[i]);
    }
}

TEST_F(MemIoTest_577, EmptyIoEof_577) {
    MemIo io;
    EXPECT_TRUE(io.eof());
}
