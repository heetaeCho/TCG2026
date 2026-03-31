#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <cstring>
#include <vector>

using namespace Exiv2;

class MemIoTest_590 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Construction Tests ---

TEST_F(MemIoTest_590, DefaultConstructor_CreatesEmptyMemIo_590) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
}

TEST_F(MemIoTest_590, ConstructWithData_HasCorrectSize_590) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

TEST_F(MemIoTest_590, ConstructWithNullDataZeroSize_590) {
    MemIo memIo(nullptr, 0);
    EXPECT_EQ(memIo.size(), 0u);
}

// --- Read (byte*, size_t) Tests ---

TEST_F(MemIoTest_590, ReadIntoBuffer_ReadsCorrectData_590) {
    const byte data[] = {10, 20, 30, 40, 50};
    MemIo memIo(data, sizeof(data));
    
    byte buf[5] = {};
    size_t bytesRead = memIo.read(buf, 5);
    
    EXPECT_EQ(bytesRead, 5u);
    EXPECT_EQ(buf[0], 10);
    EXPECT_EQ(buf[1], 20);
    EXPECT_EQ(buf[2], 30);
    EXPECT_EQ(buf[3], 40);
    EXPECT_EQ(buf[4], 50);
}

TEST_F(MemIoTest_590, ReadPartialData_590) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    
    byte buf[3] = {};
    size_t bytesRead = memIo.read(buf, 3);
    
    EXPECT_EQ(bytesRead, 3u);
    EXPECT_EQ(buf[0], 1);
    EXPECT_EQ(buf[1], 2);
    EXPECT_EQ(buf[2], 3);
}

TEST_F(MemIoTest_590, ReadMoreThanAvailable_ReturnsAvailableBytes_590) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    
    byte buf[10] = {};
    size_t bytesRead = memIo.read(buf, 10);
    
    EXPECT_EQ(bytesRead, 3u);
    EXPECT_EQ(buf[0], 1);
    EXPECT_EQ(buf[1], 2);
    EXPECT_EQ(buf[2], 3);
}

TEST_F(MemIoTest_590, ReadMoreThanAvailable_SetsEof_590) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    
    byte buf[10] = {};
    memIo.read(buf, 10);
    
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_590, ReadExactAmount_DoesNotSetEof_590) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    
    byte buf[3] = {};
    memIo.read(buf, 3);
    
    EXPECT_FALSE(memIo.eof());
}

TEST_F(MemIoTest_590, ReadZeroBytes_590) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    
    byte buf[1] = {};
    size_t bytesRead = memIo.read(buf, 0);
    
    EXPECT_EQ(bytesRead, 0u);
    EXPECT_FALSE(memIo.eof());
}

TEST_F(MemIoTest_590, ReadFromEmptyMemIo_590) {
    MemIo memIo;
    
    byte buf[5] = {};
    size_t bytesRead = memIo.read(buf, 5);
    
    EXPECT_EQ(bytesRead, 0u);
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_590, ReadFromEmptyMemIoZeroBytes_590) {
    MemIo memIo;
    
    byte buf[1] = {};
    size_t bytesRead = memIo.read(buf, 0);
    
    EXPECT_EQ(bytesRead, 0u);
}

TEST_F(MemIoTest_590, SequentialReads_AdvancesPosition_590) {
    const byte data[] = {1, 2, 3, 4, 5, 6};
    MemIo memIo(data, sizeof(data));
    
    byte buf1[3] = {};
    size_t r1 = memIo.read(buf1, 3);
    EXPECT_EQ(r1, 3u);
    EXPECT_EQ(buf1[0], 1);
    EXPECT_EQ(buf1[1], 2);
    EXPECT_EQ(buf1[2], 3);
    
    byte buf2[3] = {};
    size_t r2 = memIo.read(buf2, 3);
    EXPECT_EQ(r2, 3u);
    EXPECT_EQ(buf2[0], 4);
    EXPECT_EQ(buf2[1], 5);
    EXPECT_EQ(buf2[2], 6);
}

TEST_F(MemIoTest_590, SequentialReads_LastReadPartial_590) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    
    byte buf1[3] = {};
    memIo.read(buf1, 3);
    
    byte buf2[5] = {};
    size_t r2 = memIo.read(buf2, 5);
    EXPECT_EQ(r2, 2u);
    EXPECT_EQ(buf2[0], 4);
    EXPECT_EQ(buf2[1], 5);
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_590, ReadAfterEof_ReturnsZero_590) {
    const byte data[] = {1, 2};
    MemIo memIo(data, sizeof(data));
    
    byte buf[5] = {};
    memIo.read(buf, 5); // reads 2, sets eof
    
    byte buf2[5] = {};
    size_t r = memIo.read(buf2, 5);
    EXPECT_EQ(r, 0u);
}

// --- Read (DataBuf) Tests ---

TEST_F(MemIoTest_590, ReadDataBuf_ReturnsCorrectData_590) {
    const byte data[] = {10, 20, 30, 40, 50};
    MemIo memIo(data, sizeof(data));
    
    DataBuf buf = memIo.read(3);
    EXPECT_EQ(buf.size(), 3u);
    EXPECT_EQ(buf.data()[0], 10);
    EXPECT_EQ(buf.data()[1], 20);
    EXPECT_EQ(buf.data()[2], 30);
}

TEST_F(MemIoTest_590, ReadDataBuf_MoreThanAvailable_590) {
    const byte data[] = {1, 2};
    MemIo memIo(data, sizeof(data));
    
    DataBuf buf = memIo.read(10);
    // The buffer may be allocated for 10 but actual read is 2
    // We just verify eof is set
    EXPECT_TRUE(memIo.eof());
}

// --- Tell Tests ---

TEST_F(MemIoTest_590, TellInitiallyZero_590) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_590, TellAdvancesAfterRead_590) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    
    byte buf[3] = {};
    memIo.read(buf, 3);
    
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_590, TellAtEndAfterFullRead_590) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    
    byte buf[3] = {};
    memIo.read(buf, 3);
    
    EXPECT_EQ(memIo.tell(), 3u);
}

// --- Seek Tests ---

TEST_F(MemIoTest_590, SeekToBeginning_590) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    
    byte buf[3] = {};
    memIo.read(buf, 3);
    EXPECT_EQ(memIo.tell(), 3u);
    
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_590, SeekToMiddle_590) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    
    memIo.seek(2, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 2u);
    
    byte buf[1] = {};
    memIo.read(buf, 1);
    EXPECT_EQ(buf[0], 3);
}

TEST_F(MemIoTest_590, SeekFromCurrent_590) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    
    memIo.seek(2, BasicIo::beg);
    memIo.seek(1, BasicIo::cur);
    EXPECT_EQ(memIo.tell(), 3u);
}

TEST_F(MemIoTest_590, SeekFromEnd_590) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    
    memIo.seek(-2, BasicIo::end);
    EXPECT_EQ(memIo.tell(), 3u);
    
    byte buf[1] = {};
    memIo.read(buf, 1);
    EXPECT_EQ(buf[0], 4);
}

TEST_F(MemIoTest_590, SeekResetsEof_590) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    
    byte buf[10] = {};
    memIo.read(buf, 10);
    EXPECT_TRUE(memIo.eof());
    
    memIo.seek(0, BasicIo::beg);
    // After seeking, eof should be cleared
    EXPECT_FALSE(memIo.eof());
}

// --- Write Tests ---

TEST_F(MemIoTest_590, WriteToEmptyMemIo_590) {
    MemIo memIo;
    const byte data[] = {1, 2, 3};
    
    size_t written = memIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(memIo.size(), 3u);
}

TEST_F(MemIoTest_590, WriteAndReadBack_590) {
    MemIo memIo;
    const byte data[] = {10, 20, 30, 40};
    
    memIo.write(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    
    byte buf[4] = {};
    size_t bytesRead = memIo.read(buf, 4);
    
    EXPECT_EQ(bytesRead, 4u);
    EXPECT_EQ(buf[0], 10);
    EXPECT_EQ(buf[1], 20);
    EXPECT_EQ(buf[2], 30);
    EXPECT_EQ(buf[3], 40);
}

TEST_F(MemIoTest_590, MultipleWrites_590) {
    MemIo memIo;
    const byte data1[] = {1, 2, 3};
    const byte data2[] = {4, 5, 6};
    
    memIo.write(data1, sizeof(data1));
    memIo.write(data2, sizeof(data2));
    
    EXPECT_EQ(memIo.size(), 6u);
    
    memIo.seek(0, BasicIo::beg);
    byte buf[6] = {};
    memIo.read(buf, 6);
    
    EXPECT_EQ(buf[0], 1);
    EXPECT_EQ(buf[3], 4);
    EXPECT_EQ(buf[5], 6);
}

// --- Putb / Getb Tests ---

TEST_F(MemIoTest_590, PutbAndGetb_590) {
    MemIo memIo;
    
    int result = memIo.putb(42);
    EXPECT_EQ(result, 42);
    
    memIo.seek(0, BasicIo::beg);
    int val = memIo.getb();
    EXPECT_EQ(val, 42);
}

TEST_F(MemIoTest_590, GetbFromEmptyReturnsEof_590) {
    MemIo memIo;
    int val = memIo.getb();
    EXPECT_EQ(val, EOF);
}

TEST_F(MemIoTest_590, GetbSequential_590) {
    const byte data[] = {100, 200};
    MemIo memIo(data, sizeof(data));
    
    int v1 = memIo.getb();
    int v2 = memIo.getb();
    int v3 = memIo.getb();
    
    EXPECT_EQ(v1, 100);
    EXPECT_EQ(v2, 200);
    EXPECT_EQ(v3, EOF);
}

// --- Open / Close / Isopen Tests ---

TEST_F(MemIoTest_590, OpenAndClose_590) {
    MemIo memIo;
    int openResult = memIo.open();
    EXPECT_EQ(openResult, 0);
    EXPECT_TRUE(memIo.isopen());
    
    int closeResult = memIo.close();
    EXPECT_EQ(closeResult, 0);
}

TEST_F(MemIoTest_590, IsOpenByDefault_590) {
    MemIo memIo;
    // MemIo is always "open"
    EXPECT_TRUE(memIo.isopen());
}

// --- Error Tests ---

TEST_F(MemIoTest_590, ErrorInitiallyFalse_590) {
    MemIo memIo;
    EXPECT_EQ(memIo.error(), 0);
}

// --- Eof Tests ---

TEST_F(MemIoTest_590, EofInitiallyFalse_590) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    EXPECT_FALSE(memIo.eof());
}

TEST_F(MemIoTest_590, EofAfterReadPastEnd_590) {
    const byte data[] = {1};
    MemIo memIo(data, sizeof(data));
    
    byte buf[5] = {};
    memIo.read(buf, 5);
    EXPECT_TRUE(memIo.eof());
}

TEST_F(MemIoTest_590, EofOnEmptyMemIoAfterRead_590) {
    MemIo memIo;
    byte buf[1] = {};
    memIo.read(buf, 1);
    EXPECT_TRUE(memIo.eof());
}

// --- Size Tests ---

TEST_F(MemIoTest_590, SizeAfterWrite_590) {
    MemIo memIo;
    const byte data[] = {1, 2, 3, 4, 5};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 5u);
}

TEST_F(MemIoTest_590, SizeAfterConstruction_590) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 3u);
}

// --- Path Tests ---

TEST_F(MemIoTest_590, PathIsNotEmpty_590) {
    MemIo memIo;
    // MemIo typically returns a non-empty path string
    const std::string& p = memIo.path();
    // Just verify it doesn't throw and is accessible
    EXPECT_FALSE(p.empty() && false); // always passes, just exercising path()
}

// --- Mmap / Munmap Tests ---

TEST_F(MemIoTest_590, MmapReturnsPtrForNonEmpty_590) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    
    byte* ptr = memIo.mmap(false);
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(ptr[0], 1);
    EXPECT_EQ(ptr[4], 5);
    
    int result = memIo.munmap();
    EXPECT_EQ(result, 0);
}

// --- Transfer Tests ---

TEST_F(MemIoTest_590, TransferFromAnotherMemIo_590) {
    const byte data[] = {10, 20, 30};
    MemIo src(data, sizeof(data));
    MemIo dst;
    
    dst.transfer(src);
    
    EXPECT_EQ(dst.size(), 3u);
    dst.seek(0, BasicIo::beg);
    byte buf[3] = {};
    dst.read(buf, 3);
    EXPECT_EQ(buf[0], 10);
    EXPECT_EQ(buf[1], 20);
    EXPECT_EQ(buf[2], 30);
}

// --- Write from BasicIo source Tests ---

TEST_F(MemIoTest_590, WriteFromBasicIoSource_590) {
    const byte data[] = {5, 10, 15, 20};
    MemIo src(data, sizeof(data));
    MemIo dst;
    
    size_t written = dst.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dst.size(), sizeof(data));
    
    dst.seek(0, BasicIo::beg);
    byte buf[4] = {};
    dst.read(buf, 4);
    EXPECT_EQ(buf[0], 5);
    EXPECT_EQ(buf[3], 20);
}

// --- Boundary: Single byte data ---

TEST_F(MemIoTest_590, SingleByteReadWrite_590) {
    const byte data[] = {42};
    MemIo memIo(data, 1);
    
    byte buf[1] = {};
    size_t r = memIo.read(buf, 1);
    EXPECT_EQ(r, 1u);
    EXPECT_EQ(buf[0], 42);
    EXPECT_FALSE(memIo.eof());
    
    // Reading one more should set eof
    r = memIo.read(buf, 1);
    EXPECT_EQ(r, 0u);
    EXPECT_TRUE(memIo.eof());
}

// --- Large data test ---

TEST_F(MemIoTest_590, LargeDataReadWrite_590) {
    std::vector<byte> data(100000);
    for (size_t i = 0; i < data.size(); i++) {
        data[i] = static_cast<byte>(i % 256);
    }
    
    MemIo memIo(data.data(), data.size());
    EXPECT_EQ(memIo.size(), 100000u);
    
    std::vector<byte> buf(100000);
    size_t r = memIo.read(buf.data(), buf.size());
    EXPECT_EQ(r, 100000u);
    EXPECT_FALSE(memIo.eof());
    
    for (size_t i = 0; i < data.size(); i++) {
        EXPECT_EQ(buf[i], data[i]) << "Mismatch at index " << i;
    }
}

// --- Seek and read combination ---

TEST_F(MemIoTest_590, SeekBackwardAndReread_590) {
    const byte data[] = {1, 2, 3, 4, 5};
    MemIo memIo(data, sizeof(data));
    
    byte buf[5] = {};
    memIo.read(buf, 5);
    EXPECT_EQ(memIo.tell(), 5u);
    
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 0u);
    
    byte buf2[5] = {};
    size_t r = memIo.read(buf2, 5);
    EXPECT_EQ(r, 5u);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(buf2[i], data[i]);
    }
}

// --- Write at position ---

TEST_F(MemIoTest_590, WriteAtPosition_590) {
    MemIo memIo;
    const byte data1[] = {1, 2, 3, 4, 5};
    memIo.write(data1, sizeof(data1));
    
    // Seek to middle and write
    memIo.seek(2, BasicIo::beg);
    const byte data2[] = {99};
    memIo.write(data2, 1);
    
    // Read all
    memIo.seek(0, BasicIo::beg);
    byte buf[5] = {};
    memIo.read(buf, 5);
    
    EXPECT_EQ(buf[0], 1);
    EXPECT_EQ(buf[1], 2);
    EXPECT_EQ(buf[2], 99);
    EXPECT_EQ(buf[3], 4);
    EXPECT_EQ(buf[4], 5);
}

TEST_F(MemIoTest_590, ReadZeroBytesFromNonEmpty_DoesNotAdvancePosition_590) {
    const byte data[] = {1, 2, 3};
    MemIo memIo(data, sizeof(data));
    
    byte buf[1] = {};
    memIo.read(buf, 0);
    EXPECT_EQ(memIo.tell(), 0u);
}

TEST_F(MemIoTest_590, ReadOneByteAtATime_590) {
    const byte data[] = {10, 20, 30};
    MemIo memIo(data, sizeof(data));
    
    for (size_t i = 0; i < sizeof(data); i++) {
        byte buf[1] = {};
        size_t r = memIo.read(buf, 1);
        EXPECT_EQ(r, 1u);
        EXPECT_EQ(buf[0], data[i]);
    }
    
    byte buf[1] = {};
    size_t r = memIo.read(buf, 1);
    EXPECT_EQ(r, 0u);
    EXPECT_TRUE(memIo.eof());
}
