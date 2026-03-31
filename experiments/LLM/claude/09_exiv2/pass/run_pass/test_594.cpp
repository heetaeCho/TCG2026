#include <gtest/gtest.h>
#include "exiv2/basicio.hpp"

using namespace Exiv2;

class MemIoTest_594 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor and path
TEST_F(MemIoTest_594, DefaultConstructor_PathIsMemIo_594) {
    MemIo memIo;
    EXPECT_EQ(memIo.path(), "MemIo");
}

// Test constructor with data
TEST_F(MemIoTest_594, DataConstructor_SizeMatchesInput_594) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

// Test open and close
TEST_F(MemIoTest_594, OpenAndClose_ReturnsZero_594) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
    EXPECT_TRUE(memIo.isopen());
    EXPECT_EQ(memIo.close(), 0);
}

// Test isopen on default constructed MemIo
TEST_F(MemIoTest_594, DefaultConstructed_IsOpen_594) {
    MemIo memIo;
    // MemIo is typically always "open" since it's memory-based
    EXPECT_TRUE(memIo.isopen());
}

// Test size of empty MemIo
TEST_F(MemIoTest_594, EmptyMemIo_SizeIsZero_594) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

// Test tell on fresh MemIo
TEST_F(MemIoTest_594, FreshMemIo_TellIsZero_594) {
    MemIo memIo;
    EXPECT_EQ(memIo.tell(), 0u);
}

// Test write data
TEST_F(MemIoTest_594, WriteData_IncreasesSize_594) {
    MemIo memIo;
    const byte data[] = {0x41, 0x42, 0x43};
    size_t written = memIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

// Test write and read back
TEST_F(MemIoTest_594, WriteAndRead_DataMatches_594) {
    MemIo memIo;
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    memIo.write(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[4] = {};
    size_t readCount = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, sizeof(data));
    EXPECT_EQ(buf[0], 0x10);
    EXPECT_EQ(buf[1], 0x20);
    EXPECT_EQ(buf[2], 0x30);
    EXPECT_EQ(buf[3], 0x40);
}

// Test read with DataBuf
TEST_F(MemIoTest_594, ReadDataBuf_ReturnsCorrectData_594) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    DataBuf buf = memIo.read(3);
    EXPECT_EQ(buf.size(), 3u);
}

// Test putb
TEST_F(MemIoTest_594, Putb_WritesSingleByte_594) {
    MemIo memIo;
    int result = memIo.putb(0x55);
    EXPECT_EQ(result, 0x55);
    EXPECT_EQ(memIo.size(), 1u);
}

// Test getb
TEST_F(MemIoTest_594, Getb_ReadsSingleByte_594) {
    const byte data[] = {0x77};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    int result = memIo.getb();
    EXPECT_EQ(result, 0x77);
}

// Test getb on empty MemIo returns EOF
TEST_F(MemIoTest_594, Getb_OnEmpty_ReturnsEOF_594) {
    MemIo memIo;
    int result = memIo.getb();
    EXPECT_EQ(result, EOF);
}

// Test seek from beginning
TEST_F(MemIoTest_594, SeekFromBeginning_TellUpdated_594) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    int result = memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

// Test seek from current position
TEST_F(MemIoTest_594, SeekFromCurrent_TellUpdated_594) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    memIo.seek(2, BasicIo::beg);
    int result = memIo.seek(1, BasicIo::cur);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

// Test seek from end
TEST_F(MemIoTest_594, SeekFromEnd_TellUpdated_594) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    int result = memIo.seek(0, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 5u);
}

// Test seek from end with negative offset
TEST_F(MemIoTest_594, SeekFromEndNegative_TellUpdated_594) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    int result = memIo.seek(-2, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

// Test eof
TEST_F(MemIoTest_594, Eof_AfterReadingAll_ReturnsTrue_594) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));

    byte buf[10];
    memIo.read(buf, 10);  // Try to read more than available
    EXPECT_TRUE(memIo.eof());
}

// Test eof on fresh object
TEST_F(MemIoTest_594, Eof_OnFreshEmpty_594) {
    MemIo memIo;
    // An empty MemIo reading should set eof
    EXPECT_TRUE(memIo.eof());
}

// Test error on fresh object
TEST_F(MemIoTest_594, Error_OnFreshObject_ReturnsZero_594) {
    MemIo memIo;
    EXPECT_EQ(memIo.error(), 0);
}

// Test mmap and munmap
TEST_F(MemIoTest_594, MmapAndMunmap_594) {
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    MemIo memIo(data, sizeof(data));

    byte* mapped = memIo.mmap(false);
    EXPECT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0xDE);
    EXPECT_EQ(mapped[1], 0xAD);
    EXPECT_EQ(mapped[2], 0xBE);
    EXPECT_EQ(mapped[3], 0xEF);

    int result = memIo.munmap();
    EXPECT_EQ(result, 0);
}

// Test write from another BasicIo
TEST_F(MemIoTest_594, WriteFromBasicIo_594) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo src(data, sizeof(data));
    MemIo dest;

    size_t written = dest.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dest.size(), sizeof(data));
}

// Test transfer
TEST_F(MemIoTest_594, Transfer_MovesData_594) {
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    MemIo src(data, sizeof(data));
    MemIo dest;

    dest.transfer(src);
    EXPECT_EQ(dest.size(), sizeof(data));
}

// Test reading more bytes than available
TEST_F(MemIoTest_594, ReadMoreThanAvailable_ReturnsActualCount_594) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));

    byte buf[10] = {};
    size_t readCount = memIo.read(buf, 10);
    EXPECT_EQ(readCount, 3u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
}

// Test writing zero bytes
TEST_F(MemIoTest_594, WriteZeroBytes_SizeUnchanged_594) {
    MemIo memIo;
    const byte data[] = {0x01};
    size_t written = memIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(memIo.size(), 0u);
}

// Test reading zero bytes
TEST_F(MemIoTest_594, ReadZeroBytes_ReturnsZero_594) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));

    byte buf[1];
    size_t readCount = memIo.read(buf, 0);
    EXPECT_EQ(readCount, 0u);
}

// Test multiple writes accumulate
TEST_F(MemIoTest_594, MultipleWrites_SizeAccumulates_594) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02};
    const byte data2[] = {0x03, 0x04, 0x05};

    memIo.write(data1, sizeof(data1));
    memIo.write(data2, sizeof(data2));

    EXPECT_EQ(memIo.size(), 5u);
}

// Test seek beyond end
TEST_F(MemIoTest_594, SeekBeyondEnd_594) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));

    // Seeking beyond end - behavior may vary, but shouldn't crash
    int result = memIo.seek(100, BasicIo::beg);
    // Just verify it doesn't crash; result may be 0 or non-zero
    (void)result;
}

// Test seek to negative position from beginning
TEST_F(MemIoTest_594, SeekNegativeFromBeginning_ReturnsError_594) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));

    int result = memIo.seek(-1, BasicIo::beg);
    EXPECT_NE(result, 0);  // Should indicate error
}

// Test path is consistent across calls
TEST_F(MemIoTest_594, Path_ConsistentAcrossCalls_594) {
    MemIo memIo;
    const std::string& path1 = memIo.path();
    const std::string& path2 = memIo.path();
    EXPECT_EQ(path1, path2);
    EXPECT_EQ(&path1, &path2);  // Should be the same reference
}

// Test write and seek back and read
TEST_F(MemIoTest_594, WriteSeekBackRead_Correct_594) {
    MemIo memIo;
    const byte data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F};  // "Hello"
    memIo.write(data, sizeof(data));

    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 0u);

    int ch = memIo.getb();
    EXPECT_EQ(ch, 0x48);  // 'H'

    ch = memIo.getb();
    EXPECT_EQ(ch, 0x65);  // 'e'
}

// Test multiple open/close cycles
TEST_F(MemIoTest_594, MultipleOpenClose_594) {
    MemIo memIo;
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(memIo.open(), 0);
        EXPECT_EQ(memIo.close(), 0);
    }
}

// Test constructor with empty data (size 0)
TEST_F(MemIoTest_594, ConstructorWithZeroSize_594) {
    const byte data[] = {0x01};
    MemIo memIo(data, 0);
    EXPECT_EQ(memIo.size(), 0u);
}

// Test populateFakeData
TEST_F(MemIoTest_594, PopulateFakeData_NoThrow_594) {
    MemIo memIo;
    EXPECT_NO_THROW(memIo.populateFakeData());
}

// Test mmap on empty MemIo
TEST_F(MemIoTest_594, MmapOnEmpty_594) {
    MemIo memIo;
    byte* mapped = memIo.mmap(false);
    // For empty MemIo, mapped may be nullptr or a valid pointer
    // Just ensure no crash
    int result = memIo.munmap();
    EXPECT_EQ(result, 0);
    (void)mapped;
}

// Test tell after write advances position
TEST_F(MemIoTest_594, TellAfterWrite_AdvancesPosition_594) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

// Test tell after read advances position
TEST_F(MemIoTest_594, TellAfterRead_AdvancesPosition_594) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    byte buf[3];
    memIo.read(buf, 3);
    EXPECT_EQ(memIo.tell(), 3u);
}

// Test large write
TEST_F(MemIoTest_594, LargeWrite_594) {
    MemIo memIo;
    std::vector<byte> largeData(100000, 0xAB);
    size_t written = memIo.write(largeData.data(), largeData.size());
    EXPECT_EQ(written, largeData.size());
    EXPECT_EQ(memIo.size(), largeData.size());
}

// Test overwrite in the middle
TEST_F(MemIoTest_594, OverwriteMiddle_594) {
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
