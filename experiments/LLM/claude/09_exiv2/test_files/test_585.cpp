#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <cstring>

using namespace Exiv2;

class MemIoTest_585 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Default constructor tests
// ============================================================

TEST_F(MemIoTest_585, DefaultConstructor_SizeIsZero_585) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_585, DefaultConstructor_TellIsZero_585) {
    MemIo memIo;
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_585, DefaultConstructor_EofIsTrue_585) {
    MemIo memIo;
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_585, DefaultConstructor_ErrorIsZero_585) {
    MemIo memIo;
    EXPECT_EQ(memIo.error(), 0);
}

TEST_F(MemIoTest_585, DefaultConstructor_PathIsEmpty_585) {
    MemIo memIo;
    // Path should exist (possibly empty or some default)
    const std::string& p = memIo.path();
    // Just check it doesn't throw
    (void)p;
}

// ============================================================
// Constructor with data tests
// ============================================================

TEST_F(MemIoTest_585, DataConstructor_SizeMatchesInput_585) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_585, DataConstructor_TellIsZero_585) {
    const byte data[] = {10, 20, 30};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_585, DataConstructor_EmptyData_585) {
    MemIo memIo(nullptr, 0);
    EXPECT_EQ(memIo.size(), 0u);
}

// ============================================================
// open / close / isopen tests
// ============================================================

TEST_F(MemIoTest_585, OpenReturnsZero_585) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
}

TEST_F(MemIoTest_585, IsOpenAfterOpen_585) {
    MemIo memIo;
    memIo.open();
    EXPECT_TRUE(memIo.isopen());
}

TEST_F(MemIoTest_585, CloseReturnsZero_585) {
    MemIo memIo;
    memIo.open();
    EXPECT_EQ(memIo.close(), 0);
}

// ============================================================
// write(const byte*, size_t) tests
// ============================================================

TEST_F(MemIoTest_585, WriteIncreasesSize_585) {
    MemIo memIo;
    const byte data[] = {0xAA, 0xBB, 0xCC};
    size_t written = memIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_585, WriteZeroBytes_585) {
    MemIo memIo;
    const byte data[] = {0x01};
    size_t written = memIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_585, WriteUpdatesTell_585) {
    MemIo memIo;
    const byte data[] = {1, 2, 3, 4, 5};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

TEST_F(MemIoTest_585, MultipleWrites_585) {
    MemIo memIo;
    const byte data1[] = {1, 2, 3};
    const byte data2[] = {4, 5};
    memIo.write(data1, sizeof(data1));
    memIo.write(data2, sizeof(data2));
    EXPECT_EQ(memIo.size(), sizeof(data1) + sizeof(data2));
    EXPECT_EQ(memIo.tell(), sizeof(data1) + sizeof(data2));
}

// ============================================================
// write(BasicIo&) tests
// ============================================================

TEST_F(MemIoTest_585, WriteFromBasicIo_585) {
    const byte data[] = {10, 20, 30, 40, 50};
    MemIo src(data, sizeof(data));
    MemIo dst;
    size_t written = dst.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dst.size(), sizeof(data));
}

TEST_F(MemIoTest_585, WriteFromEmptyBasicIo_585) {
    MemIo src;
    MemIo dst;
    size_t written = dst.write(src);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(dst.size(), 0u);
}

// ============================================================
// read(size_t) tests
// ============================================================

TEST_F(MemIoTest_585, ReadReturnsCorrectData_585) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo memIo(data, sizeof(data));
    DataBuf buf = memIo.read(sizeof(data));
    EXPECT_EQ(buf.size(), sizeof(data));
    EXPECT_EQ(std::memcmp(buf.c_data(), data, sizeof(data)), 0);
}

TEST_F(MemIoTest_585, ReadMoreThanAvailable_585) {
    const byte data[] = {0x0A, 0x0B};
    MemIo memIo(data, sizeof(data));
    DataBuf buf = memIo.read(100);
    EXPECT_EQ(buf.size(), sizeof(data));
}

TEST_F(MemIoTest_585, ReadZeroBytes_585) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    DataBuf buf = memIo.read(0);
    EXPECT_EQ(buf.size(), 0u);
}

TEST_F(MemIoTest_585, ReadFromEmptyMemIo_585) {
    MemIo memIo;
    DataBuf buf = memIo.read(10);
    EXPECT_EQ(buf.size(), 0u);
}

// ============================================================
// read(byte*, size_t) tests
// ============================================================

TEST_F(MemIoTest_585, ReadIntoBuf_585) {
    const byte data[] = {5, 10, 15, 20};
    MemIo memIo(data, sizeof(data));
    byte buf[4] = {};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, sizeof(data));
    EXPECT_EQ(std::memcmp(buf, data, sizeof(data)), 0);
}

TEST_F(MemIoTest_585, ReadIntoBufPartial_585) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    byte buf[3] = {};
    size_t bytesRead = memIo.read(buf, 3);
    EXPECT_EQ(bytesRead, 3u);
    EXPECT_EQ(buf[0], 1);
    EXPECT_EQ(buf[1], 2);
    EXPECT_EQ(buf[2], 3);
}

TEST_F(MemIoTest_585, ReadIntoBufAdvancesTell_585) {
    const byte data[] = {1, 2, 3, 4};
    MemIo memIo(data, sizeof(data));
    byte buf[2] = {};
    memIo.read(buf, 2);
    EXPECT_EQ(memIo.tell(), 2u);
}

// ============================================================
// putb / getb tests
// ============================================================

TEST_F(MemIoTest_585, PutbIncreasesSize_585) {
    MemIo memIo;
    int result = memIo.putb(0x42);
    EXPECT_EQ(result, 0x42);
    EXPECT_EQ(memIo.size(), 1u);
}

TEST_F(MemIoTest_585, GetbReturnsCorrectByte_585) {
    const byte data[] = {0xDE, 0xAD};
    MemIo memIo(data, sizeof(data));
    int b = memIo.getb();
    EXPECT_EQ(b, 0xDE);
    b = memIo.getb();
    EXPECT_EQ(b, 0xAD);
}

TEST_F(MemIoTest_585, GetbAtEofReturnsEOF_585) {
    MemIo memIo;
    int b = memIo.getb();
    EXPECT_EQ(b, EOF);
}

TEST_F(MemIoTest_585, GetbAfterReadingAll_585) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.getb();
    int b = memIo.getb();
    EXPECT_EQ(b, EOF);
}

// ============================================================
// seek tests
// ============================================================

TEST_F(MemIoTest_585, SeekFromBeginning_585) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_585, SeekFromCurrent_585) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    memIo.seek(2, BasicIo::beg);
    int result = memIo.seek(1, BasicIo::cur);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_585, SeekFromEnd_585) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(0, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

TEST_F(MemIoTest_585, SeekFromEndWithOffset_585) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(-2, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_585, SeekToBeginning_585) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    memIo.read(3);
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_585, SeekNegativeFromBeginning_585) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(-1, BasicIo::beg);
    EXPECT_NE(result, 0);
}

// ============================================================
// eof tests
// ============================================================

TEST_F(MemIoTest_585, EofAfterReadingAll_585) {
    const byte data[] = {1, 2};
    MemIo memIo(data, sizeof(data));
    memIo.read(sizeof(data));
    // After reading exactly all bytes, trying to read more triggers eof
    memIo.getb();
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_585, NotEofBeforeReading_585) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    EXPECT_FALSE(memIo.eof());
}

// ============================================================
// mmap / munmap tests
// ============================================================

TEST_F(MemIoTest_585, MmapReturnsNonNullForNonEmpty_585) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    byte* mapped = memIo.mmap(false);
    EXPECT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0x01);
    EXPECT_EQ(mapped[1], 0x02);
    EXPECT_EQ(mapped[2], 0x03);
    EXPECT_EQ(memIo.munmap(), 0);
}

TEST_F(MemIoTest_585, MmapEmptyMemIo_585) {
    MemIo memIo;
    byte* mapped = memIo.mmap(false);
    // For empty MemIo, mapped pointer behavior is implementation defined
    // but munmap should still work
    EXPECT_EQ(memIo.munmap(), 0);
    (void)mapped;
}

// ============================================================
// transfer tests
// ============================================================

TEST_F(MemIoTest_585, TransferFromAnotherMemIo_585) {
    const byte data[] = {100, 200};
    MemIo src(data, sizeof(data));
    MemIo dst;
    dst.transfer(src);
    EXPECT_EQ(dst.size(), sizeof(data));
    // Source should be empty or reset after transfer
    EXPECT_EQ(src.size(), 0u);
}

TEST_F(MemIoTest_585, TransferFromEmptyMemIo_585) {
    MemIo src;
    MemIo dst;
    const byte dstData[] = {1, 2, 3};
    dst.write(dstData, sizeof(dstData));
    dst.transfer(src);
    // After transferring from empty source, dst should be empty/reset
    EXPECT_EQ(dst.size(), 0u);
}

// ============================================================
// Write then read back
// ============================================================

TEST_F(MemIoTest_585, WriteAndReadBack_585) {
    MemIo memIo;
    const byte data[] = {0xCA, 0xFE, 0xBA, 0xBE};
    memIo.write(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    byte buf[4] = {};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, sizeof(data));
    EXPECT_EQ(std::memcmp(buf, data, sizeof(data)), 0);
}

TEST_F(MemIoTest_585, PutbAndGetb_585) {
    MemIo memIo;
    memIo.putb(0x55);
    memIo.putb(0xAA);
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.getb(), 0x55);
    EXPECT_EQ(memIo.getb(), 0xAA);
    EXPECT_EQ(memIo.getb(), EOF);
}

// ============================================================
// Large data tests
// ============================================================

TEST_F(MemIoTest_585, LargeDataWriteAndRead_585) {
    const size_t largeSize = 100000;
    std::vector<byte> data(largeSize);
    for (size_t i = 0; i < largeSize; ++i) {
        data[i] = static_cast<byte>(i & 0xFF);
    }
    MemIo memIo;
    size_t written = memIo.write(data.data(), data.size());
    EXPECT_EQ(written, largeSize);
    EXPECT_EQ(memIo.size(), largeSize);

    memIo.seek(0, BasicIo::beg);
    std::vector<byte> readBuf(largeSize);
    size_t bytesRead = memIo.read(readBuf.data(), largeSize);
    EXPECT_EQ(bytesRead, largeSize);
    EXPECT_EQ(std::memcmp(readBuf.data(), data.data(), largeSize), 0);
}

// ============================================================
// Overwrite in the middle
// ============================================================

TEST_F(MemIoTest_585, OverwriteInMiddle_585) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    memIo.seek(2, BasicIo::beg);
    const byte newData[] = {99};
    memIo.write(newData, sizeof(newData));
    memIo.seek(0, BasicIo::beg);
    byte buf[5] = {};
    memIo.read(buf, 5);
    EXPECT_EQ(buf[0], 1);
    EXPECT_EQ(buf[1], 2);
    EXPECT_EQ(buf[2], 99);
    EXPECT_EQ(buf[3], 4);
    EXPECT_EQ(buf[4], 5);
}

// ============================================================
// populateFakeData test
// ============================================================

TEST_F(MemIoTest_585, PopulateFakeDataDoesNotThrow_585) {
    MemIo memIo;
    EXPECT_NO_THROW(memIo.populateFakeData());
}

// ============================================================
// error() tests
// ============================================================

TEST_F(MemIoTest_585, ErrorIsZeroNormally_585) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    memIo.read(3);
    EXPECT_EQ(memIo.error(), 0);
}

// ============================================================
// Seek beyond end
// ============================================================

TEST_F(MemIoTest_585, SeekBeyondEnd_585) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    // Seeking beyond the end - behavior depends on implementation
    // but it shouldn't crash
    int result = memIo.seek(100, BasicIo::beg);
    // If seek succeeds, tell should reflect it
    if (result == 0) {
        EXPECT_EQ(memIo.tell(), 100u);
    }
}

// ============================================================
// Consecutive open calls
// ============================================================

TEST_F(MemIoTest_585, MultipleOpenCalls_585) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
    EXPECT_EQ(memIo.open(), 0);
    EXPECT_TRUE(memIo.isopen());
}

// ============================================================
// Size after constructor with data
// ============================================================

TEST_F(MemIoTest_585, SizeWithSingleByte_585) {
    const byte data[] = {0xFF};
    MemIo memIo(data, 1);
    EXPECT_EQ(memIo.size(), 1u);
}

TEST_F(MemIoTest_585, SizeAfterWriteExtendsPastEnd_585) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::end);
    const byte extra[] = {4, 5};
    memIo.write(extra, sizeof(extra));
    EXPECT_EQ(memIo.size(), 5u);
}
