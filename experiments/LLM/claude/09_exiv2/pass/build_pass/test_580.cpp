#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <cstring>

using namespace Exiv2;

class MemIoTest_580 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// === Constructor Tests ===

TEST_F(MemIoTest_580, DefaultConstructor_CreatesEmptyIo_580) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_580, DataConstructor_CreatesIoWithData_580) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_580, DataConstructor_EmptyData_580) {
    MemIo memIo(nullptr, 0);
    EXPECT_EQ(memIo.size(), 0u);
}

// === open/close/isopen Tests ===

TEST_F(MemIoTest_580, Open_ReturnsZero_580) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
}

TEST_F(MemIoTest_580, Close_ReturnsZero_580) {
    MemIo memIo;
    EXPECT_EQ(memIo.close(), 0);
}

TEST_F(MemIoTest_580, IsOpen_ReturnsTrueByDefault_580) {
    MemIo memIo;
    EXPECT_TRUE(memIo.isopen());
}

TEST_F(MemIoTest_580, IsOpen_AfterOpenAndClose_580) {
    MemIo memIo;
    memIo.open();
    EXPECT_TRUE(memIo.isopen());
    memIo.close();
    // MemIo is always considered open
    EXPECT_TRUE(memIo.isopen());
}

// === putb Tests ===

TEST_F(MemIoTest_580, Putb_SingleByte_ReturnsData_580) {
    MemIo memIo;
    int result = memIo.putb(0x42);
    EXPECT_EQ(result, 0x42);
}

TEST_F(MemIoTest_580, Putb_IncreasesSize_580) {
    MemIo memIo;
    memIo.putb(0x01);
    EXPECT_EQ(memIo.size(), 1u);
}

TEST_F(MemIoTest_580, Putb_MultipleBytes_580) {
    MemIo memIo;
    memIo.putb(0x01);
    memIo.putb(0x02);
    memIo.putb(0x03);
    EXPECT_EQ(memIo.size(), 3u);
}

TEST_F(MemIoTest_580, Putb_ZeroByte_580) {
    MemIo memIo;
    int result = memIo.putb(0x00);
    EXPECT_EQ(result, 0x00);
    EXPECT_EQ(memIo.size(), 1u);
}

TEST_F(MemIoTest_580, Putb_MaxByte_580) {
    MemIo memIo;
    int result = memIo.putb(0xFF);
    EXPECT_EQ(result, 0xFF);
}

TEST_F(MemIoTest_580, Putb_ThenReadBack_580) {
    MemIo memIo;
    memIo.putb(0xAB);
    memIo.seek(0, BasicIo::beg);
    int val = memIo.getb();
    EXPECT_EQ(val, 0xAB);
}

// === write Tests ===

TEST_F(MemIoTest_580, Write_DataArray_580) {
    MemIo memIo;
    const byte data[] = {0x10, 0x20, 0x30};
    size_t written = memIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_580, Write_ZeroBytes_580) {
    MemIo memIo;
    const byte data[] = {0x10};
    size_t written = memIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_580, Write_FromBasicIo_580) {
    MemIo src;
    const byte data[] = {0xAA, 0xBB, 0xCC};
    src.write(data, sizeof(data));
    src.seek(0, BasicIo::beg);

    MemIo dest;
    size_t written = dest.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dest.size(), sizeof(data));
}

TEST_F(MemIoTest_580, Write_LargeData_580) {
    MemIo memIo;
    std::vector<byte> data(10000, 0x55);
    size_t written = memIo.write(data.data(), data.size());
    EXPECT_EQ(written, data.size());
    EXPECT_EQ(memIo.size(), data.size());
}

// === read Tests ===

TEST_F(MemIoTest_580, Read_DataBuf_580) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    DataBuf buf = memIo.read(3);
    EXPECT_EQ(buf.size(), 3u);
    EXPECT_EQ(buf.data()[0], 0x01);
    EXPECT_EQ(buf.data()[1], 0x02);
    EXPECT_EQ(buf.data()[2], 0x03);
}

TEST_F(MemIoTest_580, Read_IntoBuf_580) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    MemIo memIo(data, sizeof(data));
    byte buf[3] = {};
    size_t readCount = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, sizeof(buf));
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
    EXPECT_EQ(buf[2], 0xCC);
}

TEST_F(MemIoTest_580, Read_MoreThanAvailable_580) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    byte buf[10] = {};
    size_t readCount = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, 2u);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
}

TEST_F(MemIoTest_580, Read_ZeroBytes_580) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    byte buf[1] = {};
    size_t readCount = memIo.read(buf, 0);
    EXPECT_EQ(readCount, 0u);
}

TEST_F(MemIoTest_580, Read_FromEmptyIo_580) {
    MemIo memIo;
    DataBuf buf = memIo.read(10);
    EXPECT_EQ(buf.size(), 0u);
}

// === getb Tests ===

TEST_F(MemIoTest_580, Getb_SingleByte_580) {
    const byte data[] = {0x42};
    MemIo memIo(data, sizeof(data));
    int val = memIo.getb();
    EXPECT_EQ(val, 0x42);
}

TEST_F(MemIoTest_580, Getb_MultipleCalls_580) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.getb(), 0x01);
    EXPECT_EQ(memIo.getb(), 0x02);
    EXPECT_EQ(memIo.getb(), 0x03);
}

TEST_F(MemIoTest_580, Getb_AtEof_ReturnsEof_580) {
    MemIo memIo;
    int val = memIo.getb();
    EXPECT_EQ(val, EOF);
}

TEST_F(MemIoTest_580, Getb_PastEnd_580) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.getb(); // read the one byte
    int val = memIo.getb();
    EXPECT_EQ(val, EOF);
}

// === seek/tell Tests ===

TEST_F(MemIoTest_580, Tell_InitialPositionIsZero_580) {
    MemIo memIo;
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_580, Tell_AfterWrite_580) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_580, Seek_Beginning_580) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.read(3);
    EXPECT_EQ(memIo.tell(), 3u);
    int result = memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_580, Seek_Current_580) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.seek(2, BasicIo::beg);
    memIo.seek(1, BasicIo::cur);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_580, Seek_End_580) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::end);
    EXPECT_EQ(memIo.tell(), 5u);
}

TEST_F(MemIoTest_580, Seek_EndWithNegativeOffset_580) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.seek(-2, BasicIo::end);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_580, Seek_NegativeFromBeginning_ReturnsError_580) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(-1, BasicIo::beg);
    EXPECT_NE(result, 0);
}

TEST_F(MemIoTest_580, Seek_BeyondEnd_580) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    int result = memIo.seek(10, BasicIo::beg);
    // Seeking beyond end might expand or return error depending on implementation
    // Just verify it doesn't crash
    (void)result;
}

// === eof Tests ===

TEST_F(MemIoTest_580, Eof_InitiallyFalse_580) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    EXPECT_FALSE(memIo.eof());
}

TEST_F(MemIoTest_580, Eof_AfterReadingAllData_580) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.getb();
    memIo.getb(); // attempt to read past end
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_580, Eof_EmptyIo_580) {
    MemIo memIo;
    // Try to read from empty
    memIo.getb();
    EXPECT_TRUE(memIo.eof());
}

// === error Tests ===

TEST_F(MemIoTest_580, Error_InitiallyZero_580) {
    MemIo memIo;
    EXPECT_EQ(memIo.error(), 0);
}

// === size Tests ===

TEST_F(MemIoTest_580, Size_EmptyIo_580) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_580, Size_AfterWriteData_580) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 5u);
}

TEST_F(MemIoTest_580, Size_AfterPutb_580) {
    MemIo memIo;
    for (int i = 0; i < 10; i++) {
        memIo.putb(static_cast<byte>(i));
    }
    EXPECT_EQ(memIo.size(), 10u);
}

TEST_F(MemIoTest_580, Size_ConstructedWithData_580) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 3u);
}

// === path Tests ===

TEST_F(MemIoTest_580, Path_ReturnsNonEmptyOrEmpty_580) {
    MemIo memIo;
    const std::string& path = memIo.path();
    // MemIo path is typically empty or some default - just verify no crash
    (void)path;
}

// === mmap/munmap Tests ===

TEST_F(MemIoTest_580, Mmap_ReturnsNonNull_580) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    byte* mapped = memIo.mmap(false);
    EXPECT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0x01);
    EXPECT_EQ(mapped[1], 0x02);
    EXPECT_EQ(mapped[2], 0x03);
    memIo.munmap();
}

TEST_F(MemIoTest_580, Munmap_ReturnsZero_580) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.mmap(false);
    int result = memIo.munmap();
    EXPECT_EQ(result, 0);
}

// === transfer Tests ===

TEST_F(MemIoTest_580, Transfer_MovesData_580) {
    MemIo src;
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    src.write(data, sizeof(data));

    MemIo dest;
    dest.transfer(src);
    EXPECT_EQ(dest.size(), sizeof(data));

    dest.seek(0, BasicIo::beg);
    byte buf[4] = {};
    dest.read(buf, 4);
    EXPECT_EQ(buf[0], 0xDE);
    EXPECT_EQ(buf[1], 0xAD);
    EXPECT_EQ(buf[2], 0xBE);
    EXPECT_EQ(buf[3], 0xEF);
}

// === Combined Operation Tests ===

TEST_F(MemIoTest_580, WriteSeekRead_RoundTrip_580) {
    MemIo memIo;
    const byte data[] = {0x11, 0x22, 0x33, 0x44};
    memIo.write(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[4] = {};
    size_t readCount = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(readCount, 4u);
    EXPECT_EQ(buf[0], 0x11);
    EXPECT_EQ(buf[1], 0x22);
    EXPECT_EQ(buf[2], 0x33);
    EXPECT_EQ(buf[3], 0x44);
}

TEST_F(MemIoTest_580, PutbThenSeekAndGetb_580) {
    MemIo memIo;
    memIo.putb(0xAA);
    memIo.putb(0xBB);
    memIo.putb(0xCC);

    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.getb(), 0xAA);
    EXPECT_EQ(memIo.getb(), 0xBB);
    EXPECT_EQ(memIo.getb(), 0xCC);
    EXPECT_EQ(memIo.getb(), EOF);
}

TEST_F(MemIoTest_580, SeekMiddleAndWrite_580) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    memIo.write(data, sizeof(data));

    memIo.seek(2, BasicIo::beg);
    memIo.putb(0xFF);

    memIo.seek(0, BasicIo::beg);
    byte buf[4] = {};
    memIo.read(buf, 4);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0x04);
}

TEST_F(MemIoTest_580, ReadPartial_ThenReadRemaining_580) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    MemIo memIo(data, sizeof(data));

    byte buf1[2] = {};
    memIo.read(buf1, 2);
    EXPECT_EQ(buf1[0], 0x10);
    EXPECT_EQ(buf1[1], 0x20);
    EXPECT_EQ(memIo.tell(), 2u);

    byte buf2[3] = {};
    memIo.read(buf2, 3);
    EXPECT_EQ(buf2[0], 0x30);
    EXPECT_EQ(buf2[1], 0x40);
    EXPECT_EQ(buf2[2], 0x50);
    EXPECT_EQ(memIo.tell(), 5u);
}

TEST_F(MemIoTest_580, ConstructorWithData_TellIsZero_580) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_580, Putb_AdvancesTell_580) {
    MemIo memIo;
    EXPECT_EQ(memIo.tell(), 0u);
    memIo.putb(0x01);
    EXPECT_EQ(memIo.tell(), 1u);
    memIo.putb(0x02);
    EXPECT_EQ(memIo.tell(), 2u);
}

TEST_F(MemIoTest_580, Seek_CurrentNegative_580) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    memIo.seek(4, BasicIo::beg);
    int result = memIo.seek(-2, BasicIo::cur);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(memIo.tell(), 2u);
}

TEST_F(MemIoTest_580, Mmap_Writable_580) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    byte* mapped = memIo.mmap(true);
    EXPECT_NE(mapped, nullptr);
    // Modify via mmap
    mapped[0] = 0xFF;
    memIo.munmap();

    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.getb(), 0xFF);
}

TEST_F(MemIoTest_580, EmptyMmap_580) {
    MemIo memIo;
    byte* mapped = memIo.mmap(false);
    // Empty io mmap behavior - should not crash
    (void)mapped;
    memIo.munmap();
}

TEST_F(MemIoTest_580, PopulateFakeData_DoesNotCrash_580) {
    MemIo memIo;
    memIo.populateFakeData();
    // Just verify it doesn't crash and possibly changes size
    EXPECT_GE(memIo.size(), 0u);
}
