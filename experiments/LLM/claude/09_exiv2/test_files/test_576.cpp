#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <cstring>
#include <vector>

using namespace Exiv2;

class MemIoTest_576 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(MemIoTest_576, DefaultConstructor_CreatesEmptyMemIo_576) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_576, ConstructorWithData_CopiesData_576) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_576, ConstructorWithNullDataAndZeroSize_576) {
    MemIo memIo(nullptr, 0);
    EXPECT_EQ(memIo.size(), 0u);
}

// ==================== Open/Close Tests ====================

TEST_F(MemIoTest_576, Open_ReturnsZeroOnSuccess_576) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
}

TEST_F(MemIoTest_576, Close_ReturnsZeroOnSuccess_576) {
    MemIo memIo;
    memIo.open();
    EXPECT_EQ(memIo.close(), 0);
}

TEST_F(MemIoTest_576, IsOpen_AfterOpen_ReturnsTrue_576) {
    MemIo memIo;
    memIo.open();
    EXPECT_TRUE(memIo.isopen());
}

TEST_F(MemIoTest_576, IsOpen_DefaultState_576) {
    MemIo memIo;
    // MemIo is typically always "open" since it's memory-based
    EXPECT_TRUE(memIo.isopen());
}

// ==================== Write Tests ====================

TEST_F(MemIoTest_576, WriteData_ReturnsWrittenCount_576) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    size_t written = memIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_576, WriteZeroBytes_576) {
    MemIo memIo;
    const byte data[] = {0x01};
    size_t written = memIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_576, WriteMultipleTimes_AppendsData_576) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02};
    const byte data2[] = {0x03, 0x04, 0x05};
    memIo.write(data1, sizeof(data1));
    memIo.write(data2, sizeof(data2));
    EXPECT_EQ(memIo.size(), sizeof(data1) + sizeof(data2));
}

TEST_F(MemIoTest_576, WriteFromBasicIo_576) {
    MemIo src;
    const byte data[] = {0x0A, 0x0B, 0x0C, 0x0D};
    src.write(data, sizeof(data));
    src.seek(0, BasicIo::beg);

    MemIo dst;
    size_t written = dst.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dst.size(), sizeof(data));
}

// ==================== Read Tests ====================

TEST_F(MemIoTest_576, ReadIntoDataBuf_576) {
    const byte data[] = {0x10, 0x20, 0x30, 0x40};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    DataBuf buf = memIo.read(sizeof(data));
    EXPECT_EQ(buf.size(), sizeof(data));
    EXPECT_EQ(std::memcmp(buf.data(), data, sizeof(data)), 0);
}

TEST_F(MemIoTest_576, ReadIntoBuffer_576) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[3] = {};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, sizeof(data));
    EXPECT_EQ(std::memcmp(buf, data, sizeof(data)), 0);
}

TEST_F(MemIoTest_576, ReadMoreThanAvailable_576) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[10] = {};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, sizeof(data));
}

TEST_F(MemIoTest_576, ReadZeroBytes_576) {
    const byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[1] = {};
    size_t bytesRead = memIo.read(buf, 0);
    EXPECT_EQ(bytesRead, 0u);
}

TEST_F(MemIoTest_576, ReadFromEmptyMemIo_576) {
    MemIo memIo;
    DataBuf buf = memIo.read(10);
    EXPECT_EQ(buf.size(), 0u);
}

// ==================== Getb/Putb Tests ====================

TEST_F(MemIoTest_576, Putb_WritesSingleByte_576) {
    MemIo memIo;
    int result = memIo.putb(0x42);
    EXPECT_EQ(result, 0x42);
    EXPECT_EQ(memIo.size(), 1u);
}

TEST_F(MemIoTest_576, Getb_ReadsSingleByte_576) {
    const byte data[] = {0x55};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    int result = memIo.getb();
    EXPECT_EQ(result, 0x55);
}

TEST_F(MemIoTest_576, Getb_AtEof_ReturnsEof_576) {
    MemIo memIo;
    int result = memIo.getb();
    EXPECT_EQ(result, EOF);
}

TEST_F(MemIoTest_576, Getb_SequentialReads_576) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    EXPECT_EQ(memIo.getb(), 0x01);
    EXPECT_EQ(memIo.getb(), 0x02);
    EXPECT_EQ(memIo.getb(), 0x03);
    EXPECT_EQ(memIo.getb(), EOF);
}

// ==================== Seek/Tell Tests ====================

TEST_F(MemIoTest_576, SeekBeg_SetsPositionFromBeginning_576) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    EXPECT_EQ(memIo.seek(2, BasicIo::beg), 0);
    EXPECT_EQ(memIo.tell(), 2u);
}

TEST_F(MemIoTest_576, SeekCur_SetsPositionRelativeToCurrent_576) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    memIo.seek(2, BasicIo::beg);
    EXPECT_EQ(memIo.seek(1, BasicIo::cur), 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_576, SeekEnd_SetsPositionFromEnd_576) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    EXPECT_EQ(memIo.seek(0, BasicIo::end), 0);
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

TEST_F(MemIoTest_576, SeekEnd_NegativeOffset_576) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    EXPECT_EQ(memIo.seek(-2, BasicIo::end), 0);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_576, SeekToBeginning_576) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));

    memIo.read(2);
    EXPECT_EQ(memIo.tell(), 2u);
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_576, SeekBeyondEnd_576) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));

    // Seeking beyond end - behavior depends on implementation
    int result = memIo.seek(100, BasicIo::beg);
    // Just check it doesn't crash; result may be 0 or error
    (void)result;
}

TEST_F(MemIoTest_576, SeekNegativeFromBeginning_ReturnsError_576) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));

    int result = memIo.seek(-1, BasicIo::beg);
    EXPECT_NE(result, 0);
}

TEST_F(MemIoTest_576, Tell_InitialPositionIsZero_576) {
    MemIo memIo;
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_576, Tell_AfterWrite_576) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.tell(), sizeof(data));
}

// ==================== Size Tests ====================

TEST_F(MemIoTest_576, Size_EmptyMemIo_576) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_576, Size_AfterWriting_576) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_576, Size_WithConstructorData_576) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

// ==================== EOF Tests ====================

TEST_F(MemIoTest_576, Eof_InitialState_576) {
    MemIo memIo;
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_576, Eof_AfterReadingAllData_576) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    byte buf[2];
    memIo.read(buf, sizeof(buf));
    // After reading all data, eof may not be set until next read attempt
    memIo.getb(); // trigger eof
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_576, Eof_NotAtEnd_576) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);

    memIo.getb(); // read one byte
    EXPECT_FALSE(memIo.eof());
}

// ==================== Error Tests ====================

TEST_F(MemIoTest_576, Error_InitialState_576) {
    MemIo memIo;
    EXPECT_EQ(memIo.error(), 0);
}

TEST_F(MemIoTest_576, Error_AfterNormalOperations_576) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    memIo.read(2);
    EXPECT_EQ(memIo.error(), 0);
}

// ==================== Path Tests ====================

TEST_F(MemIoTest_576, Path_ReturnsNonEmptyString_576) {
    MemIo memIo;
    const std::string& p = memIo.path();
    // MemIo typically returns some placeholder path
    EXPECT_FALSE(p.empty());
}

// ==================== Mmap/Munmap Tests ====================

TEST_F(MemIoTest_576, Mmap_ReturnsPointerToData_576) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));

    byte* mapped = memIo.mmap(false);
    EXPECT_NE(mapped, nullptr);
    EXPECT_EQ(std::memcmp(mapped, data, sizeof(data)), 0);

    EXPECT_EQ(memIo.munmap(), 0);
}

TEST_F(MemIoTest_576, Mmap_EmptyMemIo_576) {
    MemIo memIo;
    byte* mapped = memIo.mmap(false);
    // For empty MemIo, behavior is implementation-dependent
    // Just ensure no crash
    memIo.munmap();
}

TEST_F(MemIoTest_576, Munmap_WithoutMmap_576) {
    MemIo memIo;
    int result = memIo.munmap();
    EXPECT_EQ(result, 0);
}

// ==================== Transfer Tests ====================

TEST_F(MemIoTest_576, Transfer_MovesDataFromSource_576) {
    MemIo src;
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    src.write(data, sizeof(data));

    MemIo dst;
    dst.transfer(src);

    EXPECT_EQ(dst.size(), sizeof(data));
    dst.seek(0, BasicIo::beg);
    byte buf[4] = {};
    dst.read(buf, sizeof(buf));
    EXPECT_EQ(std::memcmp(buf, data, sizeof(data)), 0);
}

TEST_F(MemIoTest_576, Transfer_EmptySource_576) {
    MemIo src;
    MemIo dst;
    const byte data[] = {0x01};
    dst.write(data, sizeof(data));

    dst.transfer(src);
    EXPECT_EQ(dst.size(), 0u);
}

// ==================== Write after Seek Tests ====================

TEST_F(MemIoTest_576, WriteAfterSeekToBeginning_OverwritesData_576) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02, 0x03, 0x04};
    memIo.write(data1, sizeof(data1));

    memIo.seek(0, BasicIo::beg);
    const byte data2[] = {0xAA, 0xBB};
    memIo.write(data2, sizeof(data2));

    memIo.seek(0, BasicIo::beg);
    byte buf[4] = {};
    memIo.read(buf, 4);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[1], 0xBB);
    EXPECT_EQ(buf[2], 0x03);
    EXPECT_EQ(buf[3], 0x04);
}

// ==================== Large Data Tests ====================

TEST_F(MemIoTest_576, LargeDataWriteAndRead_576) {
    MemIo memIo;
    std::vector<byte> data(100000);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = static_cast<byte>(i & 0xFF);
    }

    size_t written = memIo.write(data.data(), data.size());
    EXPECT_EQ(written, data.size());
    EXPECT_EQ(memIo.size(), data.size());

    memIo.seek(0, BasicIo::beg);
    std::vector<byte> readBuf(data.size());
    size_t bytesRead = memIo.read(readBuf.data(), readBuf.size());
    EXPECT_EQ(bytesRead, data.size());
    EXPECT_EQ(data, readBuf);
}

// ==================== PopulateFakeData Test ====================

TEST_F(MemIoTest_576, PopulateFakeData_DoesNotCrash_576) {
    MemIo memIo;
    EXPECT_NO_THROW(memIo.populateFakeData());
}

// ==================== Multiple Open/Close Cycles ====================

TEST_F(MemIoTest_576, MultipleOpenCloseCycles_576) {
    MemIo memIo;
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(memIo.open(), 0);
        EXPECT_EQ(memIo.close(), 0);
    }
}

// ==================== Read after Write without Seek ====================

TEST_F(MemIoTest_576, ReadAfterWriteWithoutSeek_ReturnsNoData_576) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));

    // Position is at end after write, so read should return 0 bytes
    byte buf[3] = {};
    size_t bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, 0u);
}

// ==================== Putb Sequential ====================

TEST_F(MemIoTest_576, Putb_SequentialWrites_576) {
    MemIo memIo;
    memIo.putb(0x41);
    memIo.putb(0x42);
    memIo.putb(0x43);

    EXPECT_EQ(memIo.size(), 3u);

    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.getb(), 0x41);
    EXPECT_EQ(memIo.getb(), 0x42);
    EXPECT_EQ(memIo.getb(), 0x43);
}

// ==================== Seek cur negative ====================

TEST_F(MemIoTest_576, SeekCurNegative_MovesBackward_576) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));

    memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 3u);

    memIo.seek(-2, BasicIo::cur);
    EXPECT_EQ(memIo.tell(), 1u);

    EXPECT_EQ(memIo.getb(), 0x02);
}
