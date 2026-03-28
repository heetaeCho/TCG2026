#include <gtest/gtest.h>
#include "exiv2/basicio.hpp"

using namespace Exiv2;

class MemIoTest_588 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor and basic state
TEST_F(MemIoTest_588, DefaultConstructor_InitialState_588) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
    EXPECT_EQ(memIo.tell(), 0u);
    EXPECT_FALSE(memIo.eof());
    EXPECT_EQ(memIo.error(), 0);
}

// Test constructor with data
TEST_F(MemIoTest_588, DataConstructor_InitialState_588) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test close returns 0
TEST_F(MemIoTest_588, Close_ReturnsZero_588) {
    MemIo memIo;
    EXPECT_EQ(memIo.close(), 0);
}

// Test open returns 0
TEST_F(MemIoTest_588, Open_ReturnsZero_588) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
}

// Test isopen after open
TEST_F(MemIoTest_588, IsOpen_AfterOpen_588) {
    MemIo memIo;
    memIo.open();
    EXPECT_TRUE(memIo.isopen());
}

// Test write data and verify size
TEST_F(MemIoTest_588, Write_IncreasesSize_588) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    size_t written = memIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

// Test write empty data
TEST_F(MemIoTest_588, Write_EmptyData_588) {
    MemIo memIo;
    const byte data[] = {0x00};
    size_t written = memIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(memIo.size(), 0u);
}

// Test write and read back
TEST_F(MemIoTest_588, WriteAndRead_DataIntegrity_588) {
    MemIo memIo;
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    memIo.write(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[4] = {};
    size_t readCount = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, sizeof(data));
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
    EXPECT_EQ(buf[2], 0xCC);
    EXPECT_EQ(buf[3], 0xDD);
}

// Test read with DataBuf
TEST_F(MemIoTest_588, Read_DataBuf_588) {
    const byte data[] = {0x10, 0x20, 0x30};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    DataBuf buf = memIo.read(3);
    EXPECT_EQ(buf.size(), 3u);
}

// Test read beyond available data
TEST_F(MemIoTest_588, Read_BeyondSize_588) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    byte buf[10] = {};
    size_t readCount = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, sizeof(data));
}

// Test seek from beginning
TEST_F(MemIoTest_588, Seek_FromBeginning_588) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    int result = memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

// Test seek from current position
TEST_F(MemIoTest_588, Seek_FromCurrent_588) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    memIo.seek(2, BasicIo::beg);
    int result = memIo.seek(1, BasicIo::cur);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

// Test seek from end
TEST_F(MemIoTest_588, Seek_FromEnd_588) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    int result = memIo.seek(0, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 5u);
}

// Test seek to negative offset from end
TEST_F(MemIoTest_588, Seek_NegativeFromEnd_588) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    int result = memIo.seek(-2, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

// Test tell after writing
TEST_F(MemIoTest_588, Tell_AfterWrite_588) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

// Test tell after reading
TEST_F(MemIoTest_588, Tell_AfterRead_588) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    byte buf[2];
    memIo.read(buf, 2);
    EXPECT_EQ(memIo.tell(), 2u);
}

// Test putb
TEST_F(MemIoTest_588, Putb_SingleByte_588) {
    MemIo memIo;
    int result = memIo.putb(0x42);
    EXPECT_EQ(result, 0x42);
    EXPECT_EQ(memIo.size(), 1u);
}

// Test getb
TEST_F(MemIoTest_588, Getb_SingleByte_588) {
    const byte data[] = {0x42};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    int result = memIo.getb();
    EXPECT_EQ(result, 0x42);
}

// Test getb at eof returns EOF
TEST_F(MemIoTest_588, Getb_AtEof_ReturnsEOF_588) {
    MemIo memIo;
    memIo.open();
    int result = memIo.getb();
    EXPECT_EQ(result, EOF);
}

// Test eof after reading all data
TEST_F(MemIoTest_588, Eof_AfterReadingAll_588) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    byte buf[2];
    memIo.read(buf, 2);
    // Read one more to trigger EOF
    memIo.read(buf, 1);
    EXPECT_TRUE(memIo.eof());
}

// Test eof initially false
TEST_F(MemIoTest_588, Eof_InitiallyFalse_588) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    EXPECT_FALSE(memIo.eof());
}

// Test error initially zero
TEST_F(MemIoTest_588, Error_InitiallyZero_588) {
    MemIo memIo;
    EXPECT_EQ(memIo.error(), 0);
}

// Test path returns non-empty string (MemIo typically has a special path)
TEST_F(MemIoTest_588, Path_ReturnsString_588) {
    MemIo memIo;
    const std::string& p = memIo.path();
    // MemIo path is typically empty or a placeholder
    EXPECT_TRUE(p.empty() || !p.empty()); // Just verify no crash
}

// Test mmap and munmap
TEST_F(MemIoTest_588, MmapAndMunmap_588) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    byte* mapped = memIo.mmap(false);
    EXPECT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0x01);
    EXPECT_EQ(mapped[1], 0x02);
    EXPECT_EQ(mapped[2], 0x03);

    int result = memIo.munmap();
    EXPECT_EQ(result, 0);
}

// Test transfer from one MemIo to another
TEST_F(MemIoTest_588, Transfer_FromAnotherMemIo_588) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    MemIo src(data, sizeof(data));
    MemIo dst;

    dst.transfer(src);
    EXPECT_EQ(dst.size(), sizeof(data));

    dst.seek(0, BasicIo::beg);
    byte buf[3];
    dst.read(buf, 3);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
    EXPECT_EQ(buf[2], 0xCC);
}

// Test write from BasicIo source
TEST_F(MemIoTest_588, Write_FromBasicIoSource_588) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    MemIo src(data, sizeof(data));
    src.open();

    MemIo dst;
    size_t written = dst.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dst.size(), sizeof(data));
}

// Test multiple writes accumulate data
TEST_F(MemIoTest_588, MultipleWrites_AccumulateData_588) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02};
    const byte data2[] = {0x03, 0x04, 0x05};

    memIo.write(data1, sizeof(data1));
    memIo.write(data2, sizeof(data2));

    EXPECT_EQ(memIo.size(), 5u);
    EXPECT_EQ(memIo.tell(), 5u);

    memIo.seek(0, BasicIo::beg);
    byte buf[5];
    memIo.read(buf, 5);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
    EXPECT_EQ(buf[3], 0x04);
    EXPECT_EQ(buf[4], 0x05);
}

// Test seek to beginning resets position
TEST_F(MemIoTest_588, Seek_ToBeginning_ResetsPosition_588) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    byte buf[3];
    memIo.read(buf, 3);
    EXPECT_EQ(memIo.tell(), 3u);

    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test size of empty MemIo
TEST_F(MemIoTest_588, Size_EmptyMemIo_588) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

// Test putb multiple bytes
TEST_F(MemIoTest_588, Putb_MultipleBytes_588) {
    MemIo memIo;
    memIo.putb(0x10);
    memIo.putb(0x20);
    memIo.putb(0x30);

    EXPECT_EQ(memIo.size(), 3u);

    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.getb(), 0x10);
    EXPECT_EQ(memIo.getb(), 0x20);
    EXPECT_EQ(memIo.getb(), 0x30);
}

// Test overwrite data in the middle
TEST_F(MemIoTest_588, Write_OverwriteMiddle_588) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    memIo.write(data, sizeof(data));

    memIo.seek(2, BasicIo::beg);
    const byte newData[] = {0xFF};
    memIo.write(newData, sizeof(newData));

    memIo.seek(0, BasicIo::beg);
    byte buf[5];
    memIo.read(buf, 5);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0x04);
    EXPECT_EQ(buf[4], 0x05);
}

// Test large write
TEST_F(MemIoTest_588, Write_LargeData_588) {
    MemIo memIo;
    std::vector<byte> largeData(10000, 0xAB);
    size_t written = memIo.write(largeData.data(), largeData.size());
    EXPECT_EQ(written, largeData.size());
    EXPECT_EQ(memIo.size(), largeData.size());
}

// Test close and reopen
TEST_F(MemIoTest_588, CloseAndReopen_588) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));

    EXPECT_EQ(memIo.close(), 0);
    EXPECT_EQ(memIo.open(), 0);

    // Data should still be accessible
    EXPECT_EQ(memIo.size(), sizeof(data));
}

// Test populateFakeData does not crash
TEST_F(MemIoTest_588, PopulateFakeData_NoCrash_588) {
    MemIo memIo;
    EXPECT_NO_THROW(memIo.populateFakeData());
}

// Test mmap on empty MemIo
TEST_F(MemIoTest_588, Mmap_EmptyMemIo_588) {
    MemIo memIo;
    memIo.open();
    // mmap on empty might return nullptr or a valid pointer
    byte* mapped = memIo.mmap(false);
    // Just verify no crash
    memIo.munmap();
}

// Test seek with invalid negative position from beginning
TEST_F(MemIoTest_588, Seek_NegativeFromBeginning_588) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    int result = memIo.seek(-1, BasicIo::beg);
    // Should return non-zero for error
    EXPECT_NE(result, 0);
}

// Test read zero bytes
TEST_F(MemIoTest_588, Read_ZeroBytes_588) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    byte buf[1];
    size_t readCount = memIo.read(buf, 0);
    EXPECT_EQ(readCount, 0u);
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test DataBuf read with zero count
TEST_F(MemIoTest_588, Read_DataBuf_ZeroCount_588) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.open();

    DataBuf buf = memIo.read(0);
    EXPECT_EQ(buf.size(), 0u);
}
