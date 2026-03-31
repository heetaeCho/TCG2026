#include <gtest/gtest.h>
#include "exiv2/basicio.hpp"

using namespace Exiv2;

class MemIoTest_591 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ========== Construction Tests ==========

TEST_F(MemIoTest_591, DefaultConstructor_CreatesEmptyIo_591) {
    MemIo io;
    EXPECT_EQ(io.size(), 0u);
}

TEST_F(MemIoTest_591, ConstructorWithData_CopiesData_591) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo io(data, sizeof(data));
    EXPECT_EQ(io.size(), sizeof(data));
}

TEST_F(MemIoTest_591, ConstructorWithEmptyData_591) {
    MemIo io(nullptr, 0);
    EXPECT_EQ(io.size(), 0u);
}

// ========== open/close/isopen Tests ==========

TEST_F(MemIoTest_591, OpenReturnsZero_591) {
    MemIo io;
    EXPECT_EQ(io.open(), 0);
}

TEST_F(MemIoTest_591, IsOpenAfterOpen_591) {
    MemIo io;
    io.open();
    EXPECT_TRUE(io.isopen());
}

TEST_F(MemIoTest_591, CloseReturnsZero_591) {
    MemIo io;
    io.open();
    EXPECT_EQ(io.close(), 0);
}

// ========== getb Tests ==========

TEST_F(MemIoTest_591, GetbReturnsFirstByte_591) {
    const byte data[] = {0xAB, 0xCD, 0xEF};
    MemIo io(data, sizeof(data));
    EXPECT_EQ(io.getb(), 0xAB);
}

TEST_F(MemIoTest_591, GetbAdvancesPosition_591) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo io(data, sizeof(data));
    EXPECT_EQ(io.getb(), 0x01);
    EXPECT_EQ(io.getb(), 0x02);
    EXPECT_EQ(io.getb(), 0x03);
}

TEST_F(MemIoTest_591, GetbReturnsEOFWhenEmpty_591) {
    MemIo io;
    EXPECT_EQ(io.getb(), EOF);
}

TEST_F(MemIoTest_591, GetbReturnsEOFAtEnd_591) {
    const byte data[] = {0x42};
    MemIo io(data, sizeof(data));
    EXPECT_EQ(io.getb(), 0x42);
    EXPECT_EQ(io.getb(), EOF);
}

TEST_F(MemIoTest_591, GetbSetsEofFlag_591) {
    MemIo io;
    EXPECT_FALSE(io.eof());
    io.getb();
    EXPECT_TRUE(io.eof());
}

TEST_F(MemIoTest_591, GetbReadsAllBytes_591) {
    const byte data[] = {0x00, 0xFF, 0x7F, 0x80};
    MemIo io(data, sizeof(data));
    EXPECT_EQ(io.getb(), 0x00);
    EXPECT_EQ(io.getb(), 0xFF);
    EXPECT_EQ(io.getb(), 0x7F);
    EXPECT_EQ(io.getb(), 0x80);
    EXPECT_EQ(io.getb(), EOF);
}

// ========== putb Tests ==========

TEST_F(MemIoTest_591, PutbWritesByte_591) {
    MemIo io;
    EXPECT_EQ(io.putb(0x42), 0);
    EXPECT_EQ(io.size(), 1u);
}

TEST_F(MemIoTest_591, PutbThenGetb_591) {
    MemIo io;
    io.putb(0xAA);
    io.seek(0, BasicIo::beg);
    EXPECT_EQ(io.getb(), 0xAA);
}

TEST_F(MemIoTest_591, PutbMultipleBytes_591) {
    MemIo io;
    io.putb(0x01);
    io.putb(0x02);
    io.putb(0x03);
    EXPECT_EQ(io.size(), 3u);
    io.seek(0, BasicIo::beg);
    EXPECT_EQ(io.getb(), 0x01);
    EXPECT_EQ(io.getb(), 0x02);
    EXPECT_EQ(io.getb(), 0x03);
}

// ========== write Tests ==========

TEST_F(MemIoTest_591, WriteData_591) {
    MemIo io;
    const byte data[] = {0x01, 0x02, 0x03};
    size_t written = io.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(io.size(), sizeof(data));
}

TEST_F(MemIoTest_591, WriteZeroBytes_591) {
    MemIo io;
    const byte data[] = {0x01};
    size_t written = io.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(io.size(), 0u);
}

TEST_F(MemIoTest_591, WriteThenRead_591) {
    MemIo io;
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    io.write(data, sizeof(data));
    io.seek(0, BasicIo::beg);
    
    byte buf[4];
    size_t readCount = io.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, 4u);
    EXPECT_EQ(buf[0], 0xDE);
    EXPECT_EQ(buf[1], 0xAD);
    EXPECT_EQ(buf[2], 0xBE);
    EXPECT_EQ(buf[3], 0xEF);
}

TEST_F(MemIoTest_591, WriteFromBasicIo_591) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo src(data, sizeof(data));
    MemIo dst;
    size_t written = dst.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dst.size(), sizeof(data));
}

// ========== read Tests ==========

TEST_F(MemIoTest_591, ReadIntoBuffer_591) {
    const byte data[] = {0x10, 0x20, 0x30};
    MemIo io(data, sizeof(data));
    byte buf[3];
    size_t count = io.read(buf, sizeof(buf));
    EXPECT_EQ(count, 3u);
    EXPECT_EQ(buf[0], 0x10);
    EXPECT_EQ(buf[1], 0x20);
    EXPECT_EQ(buf[2], 0x30);
}

TEST_F(MemIoTest_591, ReadMoreThanAvailable_591) {
    const byte data[] = {0x10, 0x20};
    MemIo io(data, sizeof(data));
    byte buf[10];
    size_t count = io.read(buf, sizeof(buf));
    EXPECT_EQ(count, 2u);
}

TEST_F(MemIoTest_591, ReadReturnsDataBuf_591) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    MemIo io(data, sizeof(data));
    DataBuf buf = io.read(3);
    EXPECT_EQ(buf.size(), 3u);
}

TEST_F(MemIoTest_591, ReadZeroBytes_591) {
    const byte data[] = {0x01};
    MemIo io(data, sizeof(data));
    byte buf[1];
    size_t count = io.read(buf, 0);
    EXPECT_EQ(count, 0u);
}

TEST_F(MemIoTest_591, ReadFromEmptyIo_591) {
    MemIo io;
    byte buf[10];
    size_t count = io.read(buf, sizeof(buf));
    EXPECT_EQ(count, 0u);
}

// ========== seek/tell Tests ==========

TEST_F(MemIoTest_591, SeekToBeginning_591) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo io(data, sizeof(data));
    io.getb();
    io.getb();
    EXPECT_EQ(io.tell(), 2u);
    io.seek(0, BasicIo::beg);
    EXPECT_EQ(io.tell(), 0u);
}

TEST_F(MemIoTest_591, SeekFromCurrent_591) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo io(data, sizeof(data));
    io.seek(2, BasicIo::beg);
    io.seek(1, BasicIo::cur);
    EXPECT_EQ(io.tell(), 3u);
}

TEST_F(MemIoTest_591, SeekFromEnd_591) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo io(data, sizeof(data));
    io.seek(0, BasicIo::end);
    EXPECT_EQ(io.tell(), 4u);
}

TEST_F(MemIoTest_591, SeekFromEndNegativeOffset_591) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo io(data, sizeof(data));
    io.seek(-2, BasicIo::end);
    EXPECT_EQ(io.tell(), 2u);
    EXPECT_EQ(io.getb(), 0x03);
}

TEST_F(MemIoTest_591, TellInitiallyZero_591) {
    MemIo io;
    EXPECT_EQ(io.tell(), 0u);
}

TEST_F(MemIoTest_591, SeekBeyondSize_591) {
    const byte data[] = {0x01, 0x02};
    MemIo io(data, sizeof(data));
    // Seeking beyond the end - behavior depends on implementation
    int result = io.seek(100, BasicIo::beg);
    // Just verify it doesn't crash; result may vary
    (void)result;
}

TEST_F(MemIoTest_591, SeekBeforeBeginning_591) {
    const byte data[] = {0x01, 0x02};
    MemIo io(data, sizeof(data));
    int result = io.seek(-10, BasicIo::beg);
    // Should return non-zero error
    EXPECT_NE(result, 0);
}

// ========== eof/error Tests ==========

TEST_F(MemIoTest_591, EofInitiallyFalse_591) {
    const byte data[] = {0x01};
    MemIo io(data, sizeof(data));
    EXPECT_FALSE(io.eof());
}

TEST_F(MemIoTest_591, EofAfterReadingAll_591) {
    const byte data[] = {0x01};
    MemIo io(data, sizeof(data));
    io.getb();
    io.getb(); // this should trigger EOF
    EXPECT_TRUE(io.eof());
}

TEST_F(MemIoTest_591, ErrorInitiallyZero_591) {
    MemIo io;
    EXPECT_EQ(io.error(), 0);
}

// ========== size Tests ==========

TEST_F(MemIoTest_591, SizeEmpty_591) {
    MemIo io;
    EXPECT_EQ(io.size(), 0u);
}

TEST_F(MemIoTest_591, SizeWithData_591) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo io(data, sizeof(data));
    EXPECT_EQ(io.size(), 5u);
}

TEST_F(MemIoTest_591, SizeAfterWrite_591) {
    MemIo io;
    const byte data[] = {0x01, 0x02};
    io.write(data, sizeof(data));
    EXPECT_EQ(io.size(), 2u);
}

// ========== path Tests ==========

TEST_F(MemIoTest_591, PathIsNotEmpty_591) {
    MemIo io;
    const std::string& p = io.path();
    // MemIo typically returns a non-empty path string
    // Just ensure it doesn't crash
    EXPECT_FALSE(p.empty());
}

// ========== mmap/munmap Tests ==========

TEST_F(MemIoTest_591, MmapReturnsSomething_591) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo io(data, sizeof(data));
    byte* mapped = io.mmap(false);
    EXPECT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0x01);
    EXPECT_EQ(mapped[1], 0x02);
    EXPECT_EQ(mapped[2], 0x03);
    io.munmap();
}

TEST_F(MemIoTest_591, MunmapReturnsZero_591) {
    const byte data[] = {0x01};
    MemIo io(data, sizeof(data));
    io.mmap(false);
    EXPECT_EQ(io.munmap(), 0);
}

// ========== transfer Tests ==========

TEST_F(MemIoTest_591, TransferFromAnotherMemIo_591) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    MemIo src(data, sizeof(data));
    MemIo dst;
    dst.transfer(src);
    EXPECT_EQ(dst.size(), sizeof(data));
    dst.seek(0, BasicIo::beg);
    EXPECT_EQ(dst.getb(), 0xAA);
    EXPECT_EQ(dst.getb(), 0xBB);
    EXPECT_EQ(dst.getb(), 0xCC);
}

// ========== Combined Operations Tests ==========

TEST_F(MemIoTest_591, SeekThenGetb_591) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    MemIo io(data, sizeof(data));
    io.seek(3, BasicIo::beg);
    EXPECT_EQ(io.getb(), 0x40);
}

TEST_F(MemIoTest_591, WriteSeekReadSequence_591) {
    MemIo io;
    const byte data1[] = {0x01, 0x02, 0x03};
    io.write(data1, sizeof(data1));
    const byte data2[] = {0x04, 0x05};
    io.write(data2, sizeof(data2));
    
    EXPECT_EQ(io.size(), 5u);
    
    io.seek(0, BasicIo::beg);
    byte buf[5];
    size_t count = io.read(buf, 5);
    EXPECT_EQ(count, 5u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
    EXPECT_EQ(buf[3], 0x04);
    EXPECT_EQ(buf[4], 0x05);
}

TEST_F(MemIoTest_591, SeekResetEofAndGetb_591) {
    const byte data[] = {0x42};
    MemIo io(data, sizeof(data));
    io.getb();
    EXPECT_EQ(io.getb(), EOF);
    EXPECT_TRUE(io.eof());
    io.seek(0, BasicIo::beg);
    EXPECT_EQ(io.getb(), 0x42);
}

TEST_F(MemIoTest_591, LargeDataWrite_591) {
    MemIo io;
    const size_t largeSize = 10000;
    std::vector<byte> data(largeSize, 0x55);
    io.write(data.data(), data.size());
    EXPECT_EQ(io.size(), largeSize);
    io.seek(0, BasicIo::beg);
    EXPECT_EQ(io.getb(), 0x55);
    io.seek(static_cast<int64_t>(largeSize - 1), BasicIo::beg);
    EXPECT_EQ(io.getb(), 0x55);
    EXPECT_EQ(io.getb(), EOF);
}

TEST_F(MemIoTest_591, OverwriteInMiddle_591) {
    MemIo io;
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    io.write(data, sizeof(data));
    io.seek(2, BasicIo::beg);
    io.putb(0xFF);
    io.seek(0, BasicIo::beg);
    EXPECT_EQ(io.getb(), 0x01);
    EXPECT_EQ(io.getb(), 0x02);
    EXPECT_EQ(io.getb(), 0xFF);
    EXPECT_EQ(io.getb(), 0x04);
    EXPECT_EQ(io.getb(), 0x05);
}

TEST_F(MemIoTest_591, PopulateFakeData_591) {
    MemIo io;
    // Just verify it doesn't crash
    io.populateFakeData();
}

TEST_F(MemIoTest_591, GetbReturnsCorrectValueForAllByteValues_591) {
    // Test that getb correctly returns all possible byte values (0-255)
    std::vector<byte> data(256);
    for (int i = 0; i < 256; i++) {
        data[i] = static_cast<byte>(i);
    }
    MemIo io(data.data(), data.size());
    for (int i = 0; i < 256; i++) {
        int val = io.getb();
        EXPECT_EQ(val, i) << "Failed at byte value " << i;
    }
    EXPECT_EQ(io.getb(), EOF);
}

TEST_F(MemIoTest_591, MultipleGetbCallsOnSingleByte_591) {
    const byte data[] = {0x42};
    MemIo io(data, 1);
    EXPECT_EQ(io.getb(), 0x42);
    EXPECT_EQ(io.getb(), EOF);
    EXPECT_EQ(io.getb(), EOF); // Multiple EOF reads
    EXPECT_TRUE(io.eof());
}
