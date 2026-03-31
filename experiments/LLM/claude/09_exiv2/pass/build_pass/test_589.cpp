#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <vector>

using namespace Exiv2;

class MemIoTest_589 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Construction Tests ---

TEST_F(MemIoTest_589, DefaultConstructor_CreatesEmptyIo_589) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_589, ConstructorWithData_StoresData_589) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

// --- Open/Close Tests ---

TEST_F(MemIoTest_589, Open_ReturnsZero_589) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
}

TEST_F(MemIoTest_589, Close_ReturnsZero_589) {
    MemIo memIo;
    memIo.open();
    EXPECT_EQ(memIo.close(), 0);
}

TEST_F(MemIoTest_589, IsOpen_AfterOpen_ReturnsTrue_589) {
    MemIo memIo;
    memIo.open();
    EXPECT_TRUE(memIo.isopen());
}

// --- Write Tests ---

TEST_F(MemIoTest_589, WriteBytes_IncreasesSize_589) {
    MemIo memIo;
    const byte data[] = {0xAA, 0xBB, 0xCC};
    size_t written = memIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_589, WriteZeroBytes_SizeRemainsZero_589) {
    MemIo memIo;
    const byte data[] = {0x00};
    size_t written = memIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_589, WriteFromBasicIo_CopiesData_589) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo src(data, sizeof(data));
    MemIo dest;
    size_t written = dest.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dest.size(), sizeof(data));
}

// --- Putb Tests ---

TEST_F(MemIoTest_589, Putb_WritesSingleByte_589) {
    MemIo memIo;
    int result = memIo.putb(0x42);
    EXPECT_EQ(result, 0x42);
    EXPECT_EQ(memIo.size(), 1u);
}

// --- Read Tests ---

TEST_F(MemIoTest_589, ReadDataBuf_ReturnsCorrectData_589) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    DataBuf buf = memIo.read(sizeof(data));
    EXPECT_EQ(buf.size(), sizeof(data));
    EXPECT_EQ(std::memcmp(buf.c_data(0), data, sizeof(data)), 0);
}

TEST_F(MemIoTest_589, ReadIntoBuffer_ReturnsCorrectCount_589) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    byte buf[3] = {};
    size_t readCount = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, sizeof(data));
    EXPECT_EQ(std::memcmp(buf, data, sizeof(data)), 0);
}

TEST_F(MemIoTest_589, ReadMoreThanAvailable_ReturnsTruncated_589) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    DataBuf buf = memIo.read(100);
    EXPECT_EQ(buf.size(), sizeof(data));
}

TEST_F(MemIoTest_589, ReadZeroBytes_ReturnsEmptyBuffer_589) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    DataBuf buf = memIo.read(0);
    EXPECT_EQ(buf.size(), 0u);
}

TEST_F(MemIoTest_589, ReadFromEmptyIo_ReturnsEmptyBuffer_589) {
    MemIo memIo;
    DataBuf buf = memIo.read(10);
    EXPECT_EQ(buf.size(), 0u);
}

// --- Getb Tests ---

TEST_F(MemIoTest_589, Getb_ReturnsByteValue_589) {
    const byte data[] = {0x42};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    int result = memIo.getb();
    EXPECT_EQ(result, 0x42);
}

TEST_F(MemIoTest_589, Getb_AtEof_ReturnsEof_589) {
    MemIo memIo;
    int result = memIo.getb();
    EXPECT_EQ(result, EOF);
}

TEST_F(MemIoTest_589, Getb_SequentialReads_589) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.getb(), 0x01);
    EXPECT_EQ(memIo.getb(), 0x02);
    EXPECT_EQ(memIo.getb(), 0x03);
    EXPECT_EQ(memIo.getb(), EOF);
}

// --- Seek/Tell Tests ---

TEST_F(MemIoTest_589, SeekBeg_SetsPosition_589) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.seek(3, BasicIo::beg), 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_589, SeekCur_AdvancesPosition_589) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.seek(2, BasicIo::beg);
    EXPECT_EQ(memIo.seek(1, BasicIo::cur), 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_589, SeekEnd_SetsPositionFromEnd_589) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.seek(0, BasicIo::end), 0);
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

TEST_F(MemIoTest_589, SeekEnd_NegativeOffset_589) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.seek(-2, BasicIo::end), 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_589, Tell_InitialPositionIsZero_589) {
    MemIo memIo;
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_589, SeekBeyondEnd_ReturnsNonZero_589) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    // Seeking before the beginning should fail
    int result = memIo.seek(-10, BasicIo::beg);
    EXPECT_NE(result, 0);
}

// --- Eof Tests ---

TEST_F(MemIoTest_589, Eof_InitiallyFalse_589) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    EXPECT_FALSE(memIo.eof());
}

TEST_F(MemIoTest_589, Eof_AfterReadingAll_ReturnsTrue_589) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    memIo.getb();
    memIo.getb();  // This should trigger EOF
    EXPECT_TRUE(memIo.eof());
}

// --- Error Tests ---

TEST_F(MemIoTest_589, Error_InitiallyZero_589) {
    MemIo memIo;
    EXPECT_EQ(memIo.error(), 0);
}

// --- Size Tests ---

TEST_F(MemIoTest_589, Size_EmptyIo_589) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_589, Size_AfterWrite_589) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 3u);
}

TEST_F(MemIoTest_589, Size_AfterMultipleWrites_589) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02};
    const byte data2[] = {0x03, 0x04, 0x05};
    memIo.write(data1, sizeof(data1));
    memIo.write(data2, sizeof(data2));
    EXPECT_EQ(memIo.size(), 5u);
}

// --- Path Tests ---

TEST_F(MemIoTest_589, Path_ReturnsNonEmptyPath_589) {
    MemIo memIo;
    const std::string& path = memIo.path();
    // MemIo should have some path representation (even if it's a placeholder)
    EXPECT_FALSE(path.empty());
}

// --- Mmap/Munmap Tests ---

TEST_F(MemIoTest_589, Mmap_ReturnsNonNull_589) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    byte* mapped = memIo.mmap(false);
    EXPECT_NE(mapped, nullptr);
    EXPECT_EQ(memIo.munmap(), 0);
}

TEST_F(MemIoTest_589, Mmap_DataMatchesOriginal_589) {
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    MemIo memIo(data, sizeof(data));
    byte* mapped = memIo.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(std::memcmp(mapped, data, sizeof(data)), 0);
    memIo.munmap();
}

// --- Transfer Tests ---

TEST_F(MemIoTest_589, Transfer_CopiesDataFromSource_589) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo src(data, sizeof(data));
    MemIo dest;
    dest.transfer(src);
    EXPECT_EQ(dest.size(), sizeof(data));
    dest.seek(0, BasicIo::beg);
    DataBuf buf = dest.read(sizeof(data));
    EXPECT_EQ(buf.size(), sizeof(data));
    EXPECT_EQ(std::memcmp(buf.c_data(0), data, sizeof(data)), 0);
}

// --- Sequential Read After Seek Tests ---

TEST_F(MemIoTest_589, ReadAfterSeek_ReadsFromCorrectPosition_589) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    MemIo memIo(data, sizeof(data));
    memIo.seek(2, BasicIo::beg);
    DataBuf buf = memIo.read(2);
    EXPECT_EQ(buf.size(), 2u);
    EXPECT_EQ(buf.read_uint8(0), 0x30);
    EXPECT_EQ(buf.read_uint8(1), 0x40);
}

// --- Write Then Read Tests ---

TEST_F(MemIoTest_589, WriteThenRead_ReturnsWrittenData_589) {
    MemIo memIo;
    const byte data[] = {0xCA, 0xFE, 0xBA, 0xBE};
    memIo.write(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    byte buf[4] = {};
    size_t readCount = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, sizeof(data));
    EXPECT_EQ(std::memcmp(buf, data, sizeof(data)), 0);
}

// --- Multiple Putb Then Read Tests ---

TEST_F(MemIoTest_589, MultiplePutb_ThenRead_589) {
    MemIo memIo;
    memIo.putb(0x01);
    memIo.putb(0x02);
    memIo.putb(0x03);
    EXPECT_EQ(memIo.size(), 3u);
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.getb(), 0x01);
    EXPECT_EQ(memIo.getb(), 0x02);
    EXPECT_EQ(memIo.getb(), 0x03);
}

// --- Large Data Test ---

TEST_F(MemIoTest_589, LargeData_WriteAndRead_589) {
    const size_t dataSize = 100000;
    std::vector<byte> data(dataSize);
    for (size_t i = 0; i < dataSize; ++i) {
        data[i] = static_cast<byte>(i & 0xFF);
    }
    MemIo memIo;
    size_t written = memIo.write(data.data(), data.size());
    EXPECT_EQ(written, dataSize);
    EXPECT_EQ(memIo.size(), dataSize);

    memIo.seek(0, BasicIo::beg);
    DataBuf buf = memIo.read(dataSize);
    EXPECT_EQ(buf.size(), dataSize);
    EXPECT_EQ(std::memcmp(buf.c_data(0), data.data(), dataSize), 0);
}

// --- Read Partial Then Continue ---

TEST_F(MemIoTest_589, ReadPartialThenContinue_589) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    DataBuf buf1 = memIo.read(3);
    EXPECT_EQ(buf1.size(), 3u);
    EXPECT_EQ(memIo.tell(), 3u);

    DataBuf buf2 = memIo.read(3);
    EXPECT_EQ(buf2.size(), 3u);
    EXPECT_EQ(memIo.tell(), 6u);

    EXPECT_EQ(buf1.read_uint8(0), 0x01);
    EXPECT_EQ(buf2.read_uint8(0), 0x04);
}

// --- Seek Cur Negative ---

TEST_F(MemIoTest_589, SeekCurNegative_MovesBackward_589) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.seek(4, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 4u);
    memIo.seek(-2, BasicIo::cur);
    EXPECT_EQ(memIo.tell(), 2u);
    EXPECT_EQ(memIo.getb(), 0x03);
}

// --- Open Multiple Times ---

TEST_F(MemIoTest_589, OpenMultipleTimes_NoError_589) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
    EXPECT_EQ(memIo.open(), 0);
    EXPECT_TRUE(memIo.isopen());
}

// --- Close Then Reopen ---

TEST_F(MemIoTest_589, CloseThenReopen_DataPersists_589) {
    const byte data[] = {0xDE, 0xAD};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    memIo.close();
    memIo.open();
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.getb(), 0xDE);
    EXPECT_EQ(memIo.getb(), 0xAD);
}

// --- PopulateFakeData ---

TEST_F(MemIoTest_589, PopulateFakeData_IncreasesSize_589) {
    MemIo memIo;
    memIo.populateFakeData();
    // After populating fake data, size should be non-zero
    EXPECT_GT(memIo.size(), 0u);
}
