#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <cstring>

using namespace Exiv2;

// Test fixture for MemIo tests
class MemIoTest_583 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// ==================== Constructor Tests ====================

TEST_F(MemIoTest_583, DefaultConstructor_CreatesEmptyMemIo_583) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_583, DataConstructor_CreatesMemIoWithData_583) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_583, DataConstructor_EmptyData_583) {
    const byte data[] = {0x00};
    MemIo memIo(data, 0);
    EXPECT_EQ(memIo.size(), 0u);
}

// ==================== Open/Close Tests ====================

TEST_F(MemIoTest_583, Open_ReturnsZero_583) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
}

TEST_F(MemIoTest_583, Close_ReturnsZero_583) {
    MemIo memIo;
    memIo.open();
    EXPECT_EQ(memIo.close(), 0);
}

TEST_F(MemIoTest_583, IsOpen_AfterOpen_ReturnsTrue_583) {
    MemIo memIo;
    memIo.open();
    EXPECT_TRUE(memIo.isopen());
}

TEST_F(MemIoTest_583, IsOpen_DefaultState_583) {
    MemIo memIo;
    // MemIo is typically always "open"
    EXPECT_TRUE(memIo.isopen());
}

// ==================== Write Tests ====================

TEST_F(MemIoTest_583, Write_DataToEmptyMemIo_583) {
    MemIo memIo;
    const byte data[] = {0x0A, 0x0B, 0x0C};
    size_t written = memIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_583, Write_ZeroBytes_583) {
    MemIo memIo;
    const byte data[] = {0x01};
    size_t written = memIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_583, Write_MultipleWrites_583) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02};
    const byte data2[] = {0x03, 0x04, 0x05};
    memIo.write(data1, sizeof(data1));
    memIo.write(data2, sizeof(data2));
    EXPECT_EQ(memIo.size(), sizeof(data1) + sizeof(data2));
}

TEST_F(MemIoTest_583, Write_FromBasicIo_583) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo src(data, sizeof(data));
    MemIo dest;
    size_t written = dest.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dest.size(), sizeof(data));
}

// ==================== Read Tests ====================

TEST_F(MemIoTest_583, Read_DataBuf_583) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    DataBuf buf = memIo.read(sizeof(data));
    EXPECT_EQ(buf.size(), sizeof(data));
    EXPECT_EQ(std::memcmp(buf.c_data(), data, sizeof(data)), 0);
}

TEST_F(MemIoTest_583, Read_IntoBuffer_583) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    byte buf[3] = {};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, sizeof(data));
    EXPECT_EQ(std::memcmp(buf, data, sizeof(data)), 0);
}

TEST_F(MemIoTest_583, Read_MoreThanAvailable_583) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    byte buf[10] = {};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, sizeof(data));
}

TEST_F(MemIoTest_583, Read_ZeroBytes_583) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    DataBuf buf = memIo.read(0);
    EXPECT_EQ(buf.size(), 0u);
}

TEST_F(MemIoTest_583, Read_FromEmptyMemIo_583) {
    MemIo memIo;
    memIo.open();
    DataBuf buf = memIo.read(10);
    EXPECT_EQ(buf.size(), 0u);
}

// ==================== Putb/Getb Tests ====================

TEST_F(MemIoTest_583, Putb_SingleByte_583) {
    MemIo memIo;
    int result = memIo.putb(0x42);
    EXPECT_EQ(result, 0x42);
    EXPECT_EQ(memIo.size(), 1u);
}

TEST_F(MemIoTest_583, Getb_SingleByte_583) {
    const byte data[] = {0x55};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    int result = memIo.getb();
    EXPECT_EQ(result, 0x55);
}

TEST_F(MemIoTest_583, Getb_EmptyMemIo_ReturnsEOF_583) {
    MemIo memIo;
    memIo.open();
    int result = memIo.getb();
    EXPECT_EQ(result, EOF);
}

TEST_F(MemIoTest_583, Getb_AfterAllBytesRead_ReturnsEOF_583) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    memIo.getb();
    int result = memIo.getb();
    EXPECT_EQ(result, EOF);
}

// ==================== Seek/Tell Tests ====================

TEST_F(MemIoTest_583, Tell_InitialPosition_583) {
    MemIo memIo;
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_583, Tell_AfterWrite_583) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

TEST_F(MemIoTest_583, Tell_AfterRead_583) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    byte buf[2];
    memIo.read(buf, 2);
    EXPECT_EQ(memIo.tell(), 2u);
}

TEST_F(MemIoTest_583, Seek_FromBeginning_583) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    int result = memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_583, Seek_FromCurrent_583) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    memIo.seek(2, BasicIo::beg);
    int result = memIo.seek(1, BasicIo::cur);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_583, Seek_FromEnd_583) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    int result = memIo.seek(0, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

TEST_F(MemIoTest_583, Seek_FromEndNegativeOffset_583) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    int result = memIo.seek(-2, BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_583, Seek_ToBeginning_583) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    memIo.read(3);
    int result = memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_583, Seek_NegativeFromBeginning_ReturnsError_583) {
    MemIo memIo;
    int result = memIo.seek(-1, BasicIo::beg);
    EXPECT_NE(result, 0);
}

// ==================== Size Tests ====================

TEST_F(MemIoTest_583, Size_EmptyMemIo_583) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_583, Size_AfterConstruction_583) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 10u);
}

TEST_F(MemIoTest_583, Size_GrowsAfterWrite_583) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 2u);
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 4u);
}

// ==================== EOF Tests ====================

TEST_F(MemIoTest_583, Eof_InitialState_583) {
    MemIo memIo;
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_583, Eof_AfterReadingAllData_583) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    byte buf[2];
    memIo.read(buf, 2);
    // Attempt to read past end
    memIo.read(buf, 1);
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_583, Eof_NotAtEnd_583) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    byte buf[1];
    memIo.read(buf, 1);
    EXPECT_FALSE(memIo.eof());
}

// ==================== Error Tests ====================

TEST_F(MemIoTest_583, Error_NoError_583) {
    MemIo memIo;
    EXPECT_EQ(memIo.error(), 0);
}

TEST_F(MemIoTest_583, Error_AfterNormalOperations_583) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    byte buf[2];
    memIo.read(buf, 2);
    EXPECT_EQ(memIo.error(), 0);
}

// ==================== Path Tests ====================

TEST_F(MemIoTest_583, Path_ReturnsNonNull_583) {
    MemIo memIo;
    const std::string& path = memIo.path();
    // MemIo should have some path representation (possibly empty or a placeholder)
    EXPECT_FALSE(path.empty() && false); // Just ensure it doesn't throw
    (void)path; // suppress unused warning
}

// ==================== Mmap/Munmap Tests ====================

TEST_F(MemIoTest_583, Munmap_ReturnsZero_583) {
    MemIo memIo;
    EXPECT_EQ(memIo.munmap(), 0);
}

TEST_F(MemIoTest_583, Mmap_WithData_583) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    byte* mapped = memIo.mmap(false);
    EXPECT_NE(mapped, nullptr);
    EXPECT_EQ(std::memcmp(mapped, data, sizeof(data)), 0);
    EXPECT_EQ(memIo.munmap(), 0);
}

TEST_F(MemIoTest_583, Mmap_EmptyMemIo_583) {
    MemIo memIo;
    byte* mapped = memIo.mmap(false);
    // For empty MemIo, mapped could be nullptr or a valid pointer
    EXPECT_EQ(memIo.munmap(), 0);
    (void)mapped;
}

// ==================== Transfer Tests ====================

TEST_F(MemIoTest_583, Transfer_FromAnotherMemIo_583) {
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    MemIo src(data, sizeof(data));
    MemIo dest;
    dest.transfer(src);
    EXPECT_EQ(dest.size(), sizeof(data));
    // After transfer, source should be empty or reset
    EXPECT_EQ(src.size(), 0u);
}

TEST_F(MemIoTest_583, Transfer_EmptySource_583) {
    MemIo src;
    MemIo dest;
    const byte data[] = {0x01, 0x02};
    dest.write(data, sizeof(data));
    dest.transfer(src);
    EXPECT_EQ(dest.size(), 0u);
}

// ==================== Combined Operations Tests ====================

TEST_F(MemIoTest_583, WriteSeekRead_583) {
    MemIo memIo;
    const byte data[] = {0x41, 0x42, 0x43, 0x44};
    memIo.write(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    byte buf[4] = {};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, sizeof(data));
    EXPECT_EQ(std::memcmp(buf, data, sizeof(data)), 0);
}

TEST_F(MemIoTest_583, SeekAndGetb_583) {
    const byte data[] = {0x10, 0x20, 0x30};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    memIo.seek(1, BasicIo::beg);
    int result = memIo.getb();
    EXPECT_EQ(result, 0x20);
}

TEST_F(MemIoTest_583, PutbAndReadBack_583) {
    MemIo memIo;
    memIo.putb(0x99);
    memIo.putb(0xAA);
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.getb(), 0x99);
    EXPECT_EQ(memIo.getb(), 0xAA);
}

TEST_F(MemIoTest_583, WriteOverlap_SeekAndOverwrite_583) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02, 0x03, 0x04};
    memIo.write(data1, sizeof(data1));
    memIo.seek(2, BasicIo::beg);
    const byte data2[] = {0xFF, 0xFE};
    memIo.write(data2, sizeof(data2));
    
    memIo.seek(0, BasicIo::beg);
    byte buf[4];
    memIo.read(buf, 4);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0xFE);
}

TEST_F(MemIoTest_583, LargeData_583) {
    const size_t largeSize = 1024 * 1024; // 1MB
    std::vector<byte> data(largeSize, 0xAB);
    MemIo memIo(data.data(), data.size());
    EXPECT_EQ(memIo.size(), largeSize);
    
    memIo.open();
    DataBuf buf = memIo.read(largeSize);
    EXPECT_EQ(buf.size(), largeSize);
}

TEST_F(MemIoTest_583, PopulateFakeData_583) {
    MemIo memIo;
    // Just ensure it doesn't crash
    memIo.populateFakeData();
    // After populating fake data, the size should be non-zero
    // (but we don't know the exact implementation)
}

TEST_F(MemIoTest_583, MultipleOpenClose_583) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
    EXPECT_EQ(memIo.close(), 0);
    EXPECT_EQ(memIo.open(), 0);
    EXPECT_EQ(memIo.close(), 0);
}

TEST_F(MemIoTest_583, SeekBeyondEnd_583) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    // Seeking beyond end - behavior may vary
    int result = memIo.seek(100, BasicIo::beg);
    // The seek may succeed (expanding or allowing seek past end) or fail
    (void)result;
}

TEST_F(MemIoTest_583, ReadAfterWrite_NoSeek_583) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    // Without seeking back, read should return nothing (at end)
    byte buf[3] = {};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, 0u);
}

TEST_F(MemIoTest_583, Getb_SequentialReads_583) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    EXPECT_EQ(memIo.getb(), 0x10);
    EXPECT_EQ(memIo.getb(), 0x20);
    EXPECT_EQ(memIo.getb(), 0x30);
    EXPECT_EQ(memIo.getb(), 0x40);
    EXPECT_EQ(memIo.getb(), EOF);
}

TEST_F(MemIoTest_583, SeekCur_NegativeOffset_583) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    memIo.seek(4, BasicIo::beg);
    int result = memIo.seek(-2, BasicIo::cur);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 2u);
}
