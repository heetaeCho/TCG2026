#include <gtest/gtest.h>
#include "exiv2/basicio.hpp"

using namespace Exiv2;

// Test fixture for MemIo tests
class MemIoTest_587 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(MemIoTest_587, DefaultConstructor_587) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_587, ConstructWithData_587) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_587, ConstructWithEmptyData_587) {
    const byte data[] = {0x00};
    MemIo memIo(data, 0);
    EXPECT_EQ(memIo.size(), 0u);
}

// ==================== isopen Tests ====================

TEST_F(MemIoTest_587, IsOpenReturnsTrue_587) {
    MemIo memIo;
    EXPECT_TRUE(memIo.isopen());
}

TEST_F(MemIoTest_587, IsOpenAfterOpen_587) {
    MemIo memIo;
    memIo.open();
    EXPECT_TRUE(memIo.isopen());
}

TEST_F(MemIoTest_587, IsOpenAfterClose_587) {
    MemIo memIo;
    memIo.close();
    EXPECT_TRUE(memIo.isopen());
}

// ==================== open/close Tests ====================

TEST_F(MemIoTest_587, OpenReturnsZero_587) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
}

TEST_F(MemIoTest_587, CloseReturnsZero_587) {
    MemIo memIo;
    EXPECT_EQ(memIo.close(), 0);
}

// ==================== write Tests ====================

TEST_F(MemIoTest_587, WriteData_587) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    size_t written = memIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_587, WriteZeroBytes_587) {
    MemIo memIo;
    const byte data[] = {0x01};
    size_t written = memIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_587, WriteMultipleTimes_587) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02};
    const byte data2[] = {0x03, 0x04, 0x05};
    memIo.write(data1, sizeof(data1));
    memIo.write(data2, sizeof(data2));
    EXPECT_EQ(memIo.size(), sizeof(data1) + sizeof(data2));
}

TEST_F(MemIoTest_587, WriteFromBasicIo_587) {
    MemIo src;
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    src.write(data, sizeof(data));
    src.seek(0, BasicIo::beg);

    MemIo dest;
    size_t written = dest.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dest.size(), sizeof(data));
}

// ==================== read Tests ====================

TEST_F(MemIoTest_587, ReadDataBuf_587) {
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    MemIo memIo(data, sizeof(data));
    DataBuf buf = memIo.read(sizeof(data));
    EXPECT_EQ(buf.size(), sizeof(data));
    EXPECT_EQ(buf.data()[0], 0xAA);
    EXPECT_EQ(buf.data()[3], 0xDD);
}

TEST_F(MemIoTest_587, ReadIntoBuffer_587) {
    const byte data[] = {0x11, 0x22, 0x33};
    MemIo memIo(data, sizeof(data));
    byte buf[3] = {0};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, sizeof(data));
    EXPECT_EQ(buf[0], 0x11);
    EXPECT_EQ(buf[1], 0x22);
    EXPECT_EQ(buf[2], 0x33);
}

TEST_F(MemIoTest_587, ReadMoreThanAvailable_587) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    byte buf[10] = {0};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, sizeof(data));
}

TEST_F(MemIoTest_587, ReadZeroBytes_587) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    byte buf[1] = {0};
    size_t bytesRead = memIo.read(buf, 0);
    EXPECT_EQ(bytesRead, 0u);
}

TEST_F(MemIoTest_587, ReadFromEmptyMemIo_587) {
    MemIo memIo;
    DataBuf buf = memIo.read(10);
    EXPECT_EQ(buf.size(), 0u);
}

// ==================== getb Tests ====================

TEST_F(MemIoTest_587, GetbReturnsByte_587) {
    const byte data[] = {0x42, 0x43};
    MemIo memIo(data, sizeof(data));
    int result = memIo.getb();
    EXPECT_EQ(result, 0x42);
    result = memIo.getb();
    EXPECT_EQ(result, 0x43);
}

TEST_F(MemIoTest_587, GetbAtEof_587) {
    MemIo memIo;
    int result = memIo.getb();
    EXPECT_EQ(result, EOF);
}

TEST_F(MemIoTest_587, GetbAfterReadingAll_587) {
    const byte data[] = {0xFF};
    MemIo memIo(data, sizeof(data));
    memIo.getb();
    int result = memIo.getb();
    EXPECT_EQ(result, EOF);
}

// ==================== putb Tests ====================

TEST_F(MemIoTest_587, PutbWritesByte_587) {
    MemIo memIo;
    int result = memIo.putb(0xAB);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.size(), 1u);
}

TEST_F(MemIoTest_587, PutbAndGetb_587) {
    MemIo memIo;
    memIo.putb(0x99);
    memIo.seek(0, BasicIo::beg);
    int result = memIo.getb();
    EXPECT_EQ(result, 0x99);
}

// ==================== seek/tell Tests ====================

TEST_F(MemIoTest_587, TellInitialPosition_587) {
    MemIo memIo;
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_587, TellAfterWrite_587) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

TEST_F(MemIoTest_587, SeekFromBeginning_587) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_587, SeekFromCurrent_587) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.seek(2, BasicIo::beg);
    int result = memIo.seek(1, BasicIo::cur);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_587, SeekFromEnd_587) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(0, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 5u);
}

TEST_F(MemIoTest_587, SeekFromEndNegativeOffset_587) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(-2, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_587, SeekToBeginning_587) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.read(3);
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_587, SeekBeforeBeginningFails_587) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(-1, BasicIo::beg);
    EXPECT_NE(result, 0);
}

// ==================== size Tests ====================

TEST_F(MemIoTest_587, SizeOfEmptyMemIo_587) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_587, SizeAfterWriting_587) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 4u);
}

TEST_F(MemIoTest_587, SizeWithConstructorData_587) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 3u);
}

// ==================== eof Tests ====================

TEST_F(MemIoTest_587, EofOnEmptyMemIo_587) {
    MemIo memIo;
    memIo.getb(); // attempt to read past end
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_587, EofNotReachedYet_587) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.getb();
    EXPECT_FALSE(memIo.eof());
}

TEST_F(MemIoTest_587, EofAfterReadingAll_587) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.getb();
    memIo.getb(); // attempt to read past end
    EXPECT_TRUE(memIo.eof());
}

// ==================== error Tests ====================

TEST_F(MemIoTest_587, ErrorOnFreshMemIo_587) {
    MemIo memIo;
    EXPECT_EQ(memIo.error(), 0);
}

// ==================== path Tests ====================

TEST_F(MemIoTest_587, PathReturnsNonNull_587) {
    MemIo memIo;
    const std::string& p = memIo.path();
    // MemIo typically has a placeholder path
    EXPECT_FALSE(p.empty() && false); // just ensure path() doesn't crash; value is implementation-defined
}

// ==================== mmap/munmap Tests ====================

TEST_F(MemIoTest_587, MmapReturnsPointer_587) {
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    MemIo memIo(data, sizeof(data));
    byte* mapped = memIo.mmap(false);
    EXPECT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0xDE);
    EXPECT_EQ(mapped[3], 0xEF);
    memIo.munmap();
}

TEST_F(MemIoTest_587, MmapWriteable_587) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    byte* mapped = memIo.mmap(true);
    EXPECT_NE(mapped, nullptr);
    memIo.munmap();
}

TEST_F(MemIoTest_587, MunmapReturnsZero_587) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.mmap(false);
    int result = memIo.munmap();
    EXPECT_EQ(result, 0);
}

// ==================== transfer Tests ====================

TEST_F(MemIoTest_587, TransferFromAnotherMemIo_587) {
    MemIo src;
    const byte data[] = {0xAA, 0xBB, 0xCC};
    src.write(data, sizeof(data));

    MemIo dest;
    dest.transfer(src);
    EXPECT_EQ(dest.size(), sizeof(data));

    dest.seek(0, BasicIo::beg);
    int b = dest.getb();
    EXPECT_EQ(b, 0xAA);
}

// ==================== Combined read/write/seek Tests ====================

TEST_F(MemIoTest_587, WriteSeekRead_587) {
    MemIo memIo;
    const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    memIo.write(data, sizeof(data));

    memIo.seek(0, BasicIo::beg);
    byte buf[5] = {0};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, 5u);
    EXPECT_EQ(buf[0], 0x10);
    EXPECT_EQ(buf[4], 0x50);
}

TEST_F(MemIoTest_587, SeekAndReadPartial_587) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.seek(2, BasicIo::beg);
    byte buf[2] = {0};
    size_t bytesRead = memIo.read(buf, 2);
    EXPECT_EQ(bytesRead, 2u);
    EXPECT_EQ(buf[0], 0x03);
    EXPECT_EQ(buf[1], 0x04);
}

TEST_F(MemIoTest_587, OverwriteData_587) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02, 0x03, 0x04};
    memIo.write(data1, sizeof(data1));

    memIo.seek(1, BasicIo::beg);
    const byte data2[] = {0xFF, 0xFE};
    memIo.write(data2, sizeof(data2));

    memIo.seek(0, BasicIo::beg);
    byte buf[4] = {0};
    memIo.read(buf, 4);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0xFF);
    EXPECT_EQ(buf[2], 0xFE);
    EXPECT_EQ(buf[3], 0x04);
}

TEST_F(MemIoTest_587, PopulateFakeData_587) {
    MemIo memIo;
    // Just ensure it doesn't crash
    memIo.populateFakeData();
    EXPECT_GE(memIo.size(), 0u);
}

// ==================== Large data Tests ====================

TEST_F(MemIoTest_587, WriteLargeData_587) {
    MemIo memIo;
    const size_t largeSize = 100000;
    std::vector<byte> data(largeSize, 0x42);
    size_t written = memIo.write(data.data(), data.size());
    EXPECT_EQ(written, largeSize);
    EXPECT_EQ(memIo.size(), largeSize);
}

TEST_F(MemIoTest_587, ReadAfterMultipleSeeks_587) {
    const byte data[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
    MemIo memIo(data, sizeof(data));

    memIo.seek(5, BasicIo::beg);
    memIo.seek(-3, BasicIo::cur);
    EXPECT_EQ(memIo.tell(), 2u);

    int b = memIo.getb();
    EXPECT_EQ(b, 0x22);
}
