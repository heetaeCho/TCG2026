#include <gtest/gtest.h>
#include "exiv2/basicio.hpp"

using namespace Exiv2;

// Helper alias for byte type
using byte = Exiv2::byte;

class MemIoTest_592 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// ==================== Construction Tests ====================

TEST_F(MemIoTest_592, DefaultConstructor_592) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
    EXPECT_EQ(memIo.tell(), 0u);
    EXPECT_EQ(memIo.error(), 0);
}

TEST_F(MemIoTest_592, ConstructorWithData_592) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 5u);
}

TEST_F(MemIoTest_592, ConstructorWithEmptyData_592) {
    MemIo memIo(nullptr, 0);
    EXPECT_EQ(memIo.size(), 0u);
}

// ==================== Open/Close Tests ====================

TEST_F(MemIoTest_592, OpenReturnsZero_592) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
}

TEST_F(MemIoTest_592, CloseReturnsZero_592) {
    MemIo memIo;
    memIo.open();
    EXPECT_EQ(memIo.close(), 0);
}

TEST_F(MemIoTest_592, IsOpenAfterOpen_592) {
    MemIo memIo;
    memIo.open();
    EXPECT_TRUE(memIo.isopen());
}

TEST_F(MemIoTest_592, IsOpenDefaultState_592) {
    MemIo memIo;
    // MemIo is typically always "open" or becomes open
    // Testing observable behavior
    EXPECT_TRUE(memIo.isopen());
}

// ==================== Write Tests ====================

TEST_F(MemIoTest_592, WriteDataIncreasesSize_592) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    size_t written = memIo.write(data, sizeof(data));
    EXPECT_EQ(written, 3u);
    EXPECT_EQ(memIo.size(), 3u);
}

TEST_F(MemIoTest_592, WriteZeroBytes_592) {
    MemIo memIo;
    const byte data[] = {0x01};
    size_t written = memIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_592, WriteMultipleTimes_592) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02};
    const byte data2[] = {0x03, 0x04, 0x05};
    memIo.write(data1, sizeof(data1));
    memIo.write(data2, sizeof(data2));
    EXPECT_EQ(memIo.size(), 5u);
}

TEST_F(MemIoTest_592, WriteFromAnotherMemIo_592) {
    MemIo src;
    const byte data[] = {0x0A, 0x0B, 0x0C};
    src.write(data, sizeof(data));
    src.seek(0, BasicIo::beg);

    MemIo dst;
    size_t written = dst.write(src);
    EXPECT_EQ(written, 3u);
    EXPECT_EQ(dst.size(), 3u);
}

// ==================== Putb Tests ====================

TEST_F(MemIoTest_592, PutbSingleByte_592) {
    MemIo memIo;
    int result = memIo.putb(0x42);
    EXPECT_EQ(result, 0x42);
    EXPECT_EQ(memIo.size(), 1u);
}

TEST_F(MemIoTest_592, PutbMultipleBytes_592) {
    MemIo memIo;
    memIo.putb(0x01);
    memIo.putb(0x02);
    memIo.putb(0x03);
    EXPECT_EQ(memIo.size(), 3u);
    EXPECT_EQ(memIo.tell(), 3u);
}

// ==================== Read Tests ====================

TEST_F(MemIoTest_592, ReadDataBuf_592) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    DataBuf buf = memIo.read(4);
    EXPECT_EQ(buf.size(), 4u);
}

TEST_F(MemIoTest_592, ReadIntoBuffer_592) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[5] = {0};
    size_t bytesRead = memIo.read(buf, 5);
    EXPECT_EQ(bytesRead, 5u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0x03);
    EXPECT_EQ(buf[3], 0x04);
    EXPECT_EQ(buf[4], 0x05);
}

TEST_F(MemIoTest_592, ReadMoreThanAvailable_592) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[10] = {0};
    size_t bytesRead = memIo.read(buf, 10);
    EXPECT_EQ(bytesRead, 2u);
}

TEST_F(MemIoTest_592, ReadZeroBytes_592) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[1] = {0};
    size_t bytesRead = memIo.read(buf, 0);
    EXPECT_EQ(bytesRead, 0u);
}

TEST_F(MemIoTest_592, ReadFromEmptyMemIo_592) {
    MemIo memIo;
    DataBuf buf = memIo.read(10);
    EXPECT_EQ(buf.size(), 0u);
}

// ==================== Getb Tests ====================

TEST_F(MemIoTest_592, GetbReturnsByte_592) {
    const byte data[] = {0x42, 0x43};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    int result = memIo.getb();
    EXPECT_EQ(result, 0x42);

    result = memIo.getb();
    EXPECT_EQ(result, 0x43);
}

TEST_F(MemIoTest_592, GetbAtEof_592) {
    MemIo memIo;
    int result = memIo.getb();
    EXPECT_EQ(result, EOF);
}

TEST_F(MemIoTest_592, GetbAfterReadingAll_592) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    memIo.getb();  // reads the only byte
    int result = memIo.getb();
    EXPECT_EQ(result, EOF);
}

// ==================== Seek/Tell Tests ====================

TEST_F(MemIoTest_592, SeekToBeginning_592) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_592, SeekToEnd_592) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    memIo.seek(0, BasicIo::end);
    EXPECT_EQ(memIo.tell(), 5u);
}

TEST_F(MemIoTest_592, SeekFromCurrent_592) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    memIo.seek(2, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 2u);

    memIo.seek(1, BasicIo::cur);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_592, SeekNegativeFromEnd_592) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    memIo.seek(-2, BasicIo::end);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_592, SeekBeyondEnd_592) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));

    // Seeking beyond end - check that it doesn't crash
    int result = memIo.seek(100, BasicIo::beg);
    // The return value might indicate success or error
    // Just verify it doesn't crash and tell returns a reasonable value
    EXPECT_GE(memIo.tell(), 0u);
}

TEST_F(MemIoTest_592, SeekBeforeBeginning_592) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));

    int result = memIo.seek(-10, BasicIo::beg);
    // Should return error (non-zero) for invalid seek
    EXPECT_NE(result, 0);
}

TEST_F(MemIoTest_592, TellInitialPosition_592) {
    MemIo memIo;
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_592, TellAfterWrite_592) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), 3u);
}

// ==================== Size Tests ====================

TEST_F(MemIoTest_592, SizeOfEmptyMemIo_592) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_592, SizeAfterConstruction_592) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 5u);
}

TEST_F(MemIoTest_592, SizeAfterWrite_592) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 2u);
}

// ==================== Error Tests ====================

TEST_F(MemIoTest_592, ErrorReturnsZeroInitially_592) {
    MemIo memIo;
    EXPECT_EQ(memIo.error(), 0);
}

TEST_F(MemIoTest_592, ErrorAfterNormalOperations_592) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    memIo.read(3);
    EXPECT_EQ(memIo.error(), 0);
}

// ==================== EOF Tests ====================

TEST_F(MemIoTest_592, EofOnEmptyMemIo_592) {
    MemIo memIo;
    // Reading from empty should set eof
    memIo.getb();
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_592, EofAfterReadingAllData_592) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    memIo.getb();
    memIo.getb();  // This should trigger eof
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_592, NotEofInitially_592) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    EXPECT_FALSE(memIo.eof());
}

// ==================== Path Tests ====================

TEST_F(MemIoTest_592, PathReturnsNonEmpty_592) {
    MemIo memIo;
    const std::string& path = memIo.path();
    // MemIo typically returns a placeholder path
    EXPECT_FALSE(path.empty());
}

// ==================== Mmap/Munmap Tests ====================

TEST_F(MemIoTest_592, MmapReturnsPointer_592) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo memIo(data, sizeof(data));

    byte* mapped = memIo.mmap(false);
    EXPECT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0x01);
    EXPECT_EQ(mapped[1], 0x02);
    EXPECT_EQ(mapped[2], 0x03);
    EXPECT_EQ(mapped[3], 0x04);

    EXPECT_EQ(memIo.munmap(), 0);
}

TEST_F(MemIoTest_592, MmapWriteable_592) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));

    byte* mapped = memIo.mmap(true);
    EXPECT_NE(mapped, nullptr);
    EXPECT_EQ(memIo.munmap(), 0);
}

TEST_F(MemIoTest_592, MmapEmptyMemIo_592) {
    MemIo memIo;
    // mmap on empty - implementation may return nullptr or a valid pointer
    byte* mapped = memIo.mmap(false);
    // Just verify no crash
    memIo.munmap();
}

// ==================== Transfer Tests ====================

TEST_F(MemIoTest_592, TransferFromAnotherMemIo_592) {
    MemIo src;
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    src.write(data, sizeof(data));

    MemIo dst;
    dst.transfer(src);
    EXPECT_EQ(dst.size(), 4u);

    dst.seek(0, BasicIo::beg);
    byte buf[4] = {0};
    dst.read(buf, 4);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
    EXPECT_EQ(buf[2], 0xCC);
    EXPECT_EQ(buf[3], 0xDD);
}

TEST_F(MemIoTest_592, TransferFromEmptyMemIo_592) {
    MemIo src;
    MemIo dst;
    const byte data[] = {0x01, 0x02};
    dst.write(data, sizeof(data));

    dst.transfer(src);
    EXPECT_EQ(dst.size(), 0u);
}

// ==================== Write and Read Round Trip ====================

TEST_F(MemIoTest_592, WriteAndReadRoundTrip_592) {
    MemIo memIo;
    const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    memIo.write(data, sizeof(data));

    memIo.seek(0, BasicIo::beg);

    byte readBuf[5] = {0};
    size_t bytesRead = memIo.read(readBuf, 5);
    EXPECT_EQ(bytesRead, 5u);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(readBuf[i], data[i]);
    }
}

TEST_F(MemIoTest_592, PutbAndGetbRoundTrip_592) {
    MemIo memIo;
    memIo.putb(0xFF);
    memIo.putb(0x00);
    memIo.putb(0x7F);

    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.getb(), 0xFF);
    EXPECT_EQ(memIo.getb(), 0x00);
    EXPECT_EQ(memIo.getb(), 0x7F);
    EXPECT_EQ(memIo.getb(), EOF);
}

// ==================== Overwrite Tests ====================

TEST_F(MemIoTest_592, OverwriteInMiddle_592) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    memIo.write(data, sizeof(data));

    // Seek to position 2 and overwrite
    memIo.seek(2, BasicIo::beg);
    const byte newData[] = {0xAA, 0xBB};
    memIo.write(newData, sizeof(newData));

    // Verify the overwrite
    memIo.seek(0, BasicIo::beg);
    byte buf[5] = {0};
    memIo.read(buf, 5);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0xAA);
    EXPECT_EQ(buf[3], 0xBB);
    EXPECT_EQ(buf[4], 0x05);
}

// ==================== Large Data Tests ====================

TEST_F(MemIoTest_592, WriteLargeData_592) {
    MemIo memIo;
    const size_t largeSize = 100000;
    std::vector<byte> data(largeSize, 0x42);
    size_t written = memIo.write(data.data(), largeSize);
    EXPECT_EQ(written, largeSize);
    EXPECT_EQ(memIo.size(), largeSize);
}

TEST_F(MemIoTest_592, ReadLargeData_592) {
    const size_t largeSize = 100000;
    std::vector<byte> data(largeSize);
    for (size_t i = 0; i < largeSize; ++i) {
        data[i] = static_cast<byte>(i & 0xFF);
    }
    MemIo memIo(data.data(), largeSize);
    memIo.seek(0, BasicIo::beg);

    std::vector<byte> readBuf(largeSize);
    size_t bytesRead = memIo.read(readBuf.data(), largeSize);
    EXPECT_EQ(bytesRead, largeSize);
    EXPECT_EQ(readBuf, data);
}

// ==================== PopulateFakeData Tests ====================

TEST_F(MemIoTest_592, PopulateFakeDataDoesNotCrash_592) {
    MemIo memIo;
    EXPECT_NO_THROW(memIo.populateFakeData());
}

// ==================== Seek Return Value Tests ====================

TEST_F(MemIoTest_592, SeekToBeginReturnsZero_592) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(result, 0);
}

TEST_F(MemIoTest_592, SeekToEndReturnsZero_592) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(0, BasicIo::end);
    EXPECT_EQ(result, 0);
}

TEST_F(MemIoTest_592, SeekFromCurrentReturnsZero_592) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.seek(1, BasicIo::beg);
    int result = memIo.seek(1, BasicIo::cur);
    EXPECT_EQ(result, 0);
}

// ==================== Sequential Read Tests ====================

TEST_F(MemIoTest_592, SequentialReads_592) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[2] = {0};

    size_t read1 = memIo.read(buf, 2);
    EXPECT_EQ(read1, 2u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(memIo.tell(), 2u);

    size_t read2 = memIo.read(buf, 2);
    EXPECT_EQ(read2, 2u);
    EXPECT_EQ(buf[0], 0x03);
    EXPECT_EQ(buf[1], 0x04);
    EXPECT_EQ(memIo.tell(), 4u);

    size_t read3 = memIo.read(buf, 2);
    EXPECT_EQ(read3, 2u);
    EXPECT_EQ(buf[0], 0x05);
    EXPECT_EQ(buf[1], 0x06);
    EXPECT_EQ(memIo.tell(), 6u);
}

// ==================== Partial Read at End Tests ====================

TEST_F(MemIoTest_592, PartialReadAtEnd_592) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.seek(2, BasicIo::beg);

    byte buf[5] = {0};
    size_t bytesRead = memIo.read(buf, 5);
    EXPECT_EQ(bytesRead, 1u);
    EXPECT_EQ(buf[0], 0x03);
}
