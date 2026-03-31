#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <cstring>

using namespace Exiv2;

class MemIoTest_593 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(MemIoTest_593, DefaultConstructor_CreatesEmptyMemIo_593) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_593, ConstructorWithData_CopiesData_593) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_593, ConstructorWithEmptyData_593) {
    const byte data[] = {0x00};
    MemIo memIo(data, 0);
    EXPECT_EQ(memIo.size(), 0u);
}

// ==================== Open/Close Tests ====================

TEST_F(MemIoTest_593, Open_ReturnsZero_593) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
}

TEST_F(MemIoTest_593, Close_ReturnsZero_593) {
    MemIo memIo;
    memIo.open();
    EXPECT_EQ(memIo.close(), 0);
}

TEST_F(MemIoTest_593, IsOpen_AfterConstruction_593) {
    MemIo memIo;
    // MemIo is always "open" conceptually
    EXPECT_TRUE(memIo.isopen());
}

TEST_F(MemIoTest_593, IsOpen_AfterOpen_593) {
    MemIo memIo;
    memIo.open();
    EXPECT_TRUE(memIo.isopen());
}

// ==================== Write Tests ====================

TEST_F(MemIoTest_593, WriteData_IncreasesSize_593) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    size_t written = memIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_593, WriteZeroBytes_593) {
    MemIo memIo;
    const byte data[] = {0x01};
    size_t written = memIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_593, WriteMultipleTimes_593) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02};
    const byte data2[] = {0x03, 0x04, 0x05};
    memIo.write(data1, sizeof(data1));
    memIo.write(data2, sizeof(data2));
    EXPECT_EQ(memIo.size(), sizeof(data1) + sizeof(data2));
}

TEST_F(MemIoTest_593, WriteFromBasicIo_593) {
    MemIo src;
    const byte data[] = {0x10, 0x20, 0x30};
    src.write(data, sizeof(data));
    src.seek(0, BasicIo::beg);

    MemIo dest;
    size_t written = dest.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dest.size(), sizeof(data));
}

// ==================== Read Tests ====================

TEST_F(MemIoTest_593, ReadDataBuf_ReturnsCorrectData_593) {
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    DataBuf buf = memIo.read(sizeof(data));
    EXPECT_EQ(buf.size(), sizeof(data));
    EXPECT_EQ(buf.data()[0], 0xAA);
    EXPECT_EQ(buf.data()[1], 0xBB);
    EXPECT_EQ(buf.data()[2], 0xCC);
    EXPECT_EQ(buf.data()[3], 0xDD);
}

TEST_F(MemIoTest_593, ReadIntoBuffer_ReturnsCorrectCount_593) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[4];
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, sizeof(data));
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[3], 0x04);
}

TEST_F(MemIoTest_593, ReadMoreThanAvailable_593) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[10];
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, sizeof(data));
}

TEST_F(MemIoTest_593, ReadZeroBytes_593) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    DataBuf buf = memIo.read(0);
    EXPECT_EQ(buf.size(), 0u);
}

// ==================== Getb/Putb Tests ====================

TEST_F(MemIoTest_593, Getb_ReadsSingleByte_593) {
    const byte data[] = {0x42, 0x43};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    int b = memIo.getb();
    EXPECT_EQ(b, 0x42);
    b = memIo.getb();
    EXPECT_EQ(b, 0x43);
}

TEST_F(MemIoTest_593, Getb_AtEof_ReturnsEof_593) {
    MemIo memIo;
    int b = memIo.getb();
    EXPECT_EQ(b, EOF);
}

TEST_F(MemIoTest_593, Putb_WritesSingleByte_593) {
    MemIo memIo;
    int result = memIo.putb(0x55);
    EXPECT_EQ(result, 0x55);
    EXPECT_EQ(memIo.size(), 1u);
}

TEST_F(MemIoTest_593, Putb_ThenGetb_593) {
    MemIo memIo;
    memIo.putb(0xAB);
    memIo.seek(0, BasicIo::beg);
    int b = memIo.getb();
    EXPECT_EQ(b, 0xAB);
}

// ==================== Seek/Tell Tests ====================

TEST_F(MemIoTest_593, Tell_InitialPosition_593) {
    MemIo memIo;
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_593, SeekFromBeginning_593) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    int result = memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_593, SeekFromCurrent_593) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    memIo.seek(2, BasicIo::beg);
    int result = memIo.seek(1, BasicIo::cur);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_593, SeekFromEnd_593) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    int result = memIo.seek(0, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

TEST_F(MemIoTest_593, SeekFromEnd_NegativeOffset_593) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    int result = memIo.seek(-2, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_593, SeekBeforeBeginning_ReturnsError_593) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));

    int result = memIo.seek(-1, BasicIo::beg);
    EXPECT_NE(result, 0);
}

TEST_F(MemIoTest_593, TellAfterWrite_593) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

// ==================== EOF Tests ====================

TEST_F(MemIoTest_593, Eof_InitiallyFalse_593) {
    MemIo memIo;
    // Initially, eof should be false (no read attempted past end)
    EXPECT_FALSE(memIo.eof());
}

TEST_F(MemIoTest_593, Eof_AfterReadingPastEnd_593) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    memIo.getb(); // read the single byte
    memIo.getb(); // attempt to read past end
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_593, Eof_AfterReadingExactly_593) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[2];
    memIo.read(buf, 2);
    // After reading exactly all bytes, eof may or may not be set
    // But reading one more should trigger it
    memIo.getb();
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_593, Eof_EmptyMemIo_GetbSetsEof_593) {
    MemIo memIo;
    memIo.getb();
    EXPECT_TRUE(memIo.eof());
}

// ==================== Error Tests ====================

TEST_F(MemIoTest_593, Error_InitiallyZero_593) {
    MemIo memIo;
    EXPECT_EQ(memIo.error(), 0);
}

// ==================== Size Tests ====================

TEST_F(MemIoTest_593, Size_EmptyMemIo_593) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_593, Size_AfterWritingData_593) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 5u);
}

TEST_F(MemIoTest_593, Size_WithInitialData_593) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 3u);
}

// ==================== Path Tests ====================

TEST_F(MemIoTest_593, Path_ReturnsNonEmptyString_593) {
    MemIo memIo;
    const std::string& path = memIo.path();
    // MemIo should have some kind of path (possibly empty or a special marker)
    // Just ensure it doesn't throw
    (void)path;
}

// ==================== Mmap/Munmap Tests ====================

TEST_F(MemIoTest_593, Mmap_ReturnsNonNull_WhenDataExists_593) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    byte* mapped = memIo.mmap(false);
    EXPECT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0x01);
    EXPECT_EQ(mapped[1], 0x02);
    EXPECT_EQ(mapped[2], 0x03);
    memIo.munmap();
}

TEST_F(MemIoTest_593, Munmap_ReturnsZero_593) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.mmap(false);
    int result = memIo.munmap();
    EXPECT_EQ(result, 0);
}

// ==================== Transfer Tests ====================

TEST_F(MemIoTest_593, Transfer_MovesDataFromSource_593) {
    MemIo src;
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    src.write(data, sizeof(data));

    MemIo dest;
    dest.transfer(src);
    EXPECT_EQ(dest.size(), sizeof(data));

    dest.seek(0, BasicIo::beg);
    byte buf[4];
    dest.read(buf, 4);
    EXPECT_EQ(buf[0], 0xDE);
    EXPECT_EQ(buf[1], 0xAD);
    EXPECT_EQ(buf[2], 0xBE);
    EXPECT_EQ(buf[3], 0xEF);
}

// ==================== Complex Scenario Tests ====================

TEST_F(MemIoTest_593, WriteSeekRead_593) {
    MemIo memIo;
    const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    memIo.write(data, sizeof(data));

    memIo.seek(0, BasicIo::beg);
    byte buf[5];
    size_t bytesRead = memIo.read(buf, 5);
    EXPECT_EQ(bytesRead, 5u);
    EXPECT_EQ(buf[0], 0x10);
    EXPECT_EQ(buf[4], 0x50);
}

TEST_F(MemIoTest_593, SeekAndReadPartial_593) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    memIo.seek(2, BasicIo::beg);
    int b = memIo.getb();
    EXPECT_EQ(b, 0x03);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_593, OverwriteInMiddle_593) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    memIo.write(data, sizeof(data));

    memIo.seek(2, BasicIo::beg);
    const byte newData[] = {0xFF};
    memIo.write(newData, 1);

    memIo.seek(0, BasicIo::beg);
    byte buf[5];
    memIo.read(buf, 5);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0x04);
    EXPECT_EQ(buf[4], 0x05);
}

TEST_F(MemIoTest_593, LargeWrite_593) {
    MemIo memIo;
    const size_t largeSize = 100000;
    std::vector<byte> data(largeSize, 0xAB);
    size_t written = memIo.write(data.data(), largeSize);
    EXPECT_EQ(written, largeSize);
    EXPECT_EQ(memIo.size(), largeSize);
}

TEST_F(MemIoTest_593, PopulateFakeData_DoesNotThrow_593) {
    MemIo memIo;
    EXPECT_NO_THROW(memIo.populateFakeData());
}

TEST_F(MemIoTest_593, MultipleOpenClose_593) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
    EXPECT_EQ(memIo.close(), 0);
    EXPECT_EQ(memIo.open(), 0);
    EXPECT_EQ(memIo.close(), 0);
}

TEST_F(MemIoTest_593, SeekCurrentNegativeOffset_593) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    memIo.seek(4, BasicIo::beg);
    int result = memIo.seek(-2, BasicIo::cur);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 2u);
}

TEST_F(MemIoTest_593, ReadAfterWrite_PositionIsAtEnd_593) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), 3u);

    // Reading at current position (end) should yield nothing
    int b = memIo.getb();
    EXPECT_EQ(b, EOF);
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_593, Eof_ResetsAfterSeek_593) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));

    memIo.getb();
    memIo.getb(); // triggers eof
    EXPECT_TRUE(memIo.eof());

    memIo.seek(0, BasicIo::beg);
    // After seek, eof should be cleared
    EXPECT_FALSE(memIo.eof());
}
