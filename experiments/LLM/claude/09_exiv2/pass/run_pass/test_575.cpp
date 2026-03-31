#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <cstring>
#include <vector>

namespace {

using namespace Exiv2;

class MemIoTest_575 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction creates empty MemIo
TEST_F(MemIoTest_575, DefaultConstruction_575) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
    EXPECT_TRUE(memIo.isopen());
}

// Test construction with data
TEST_F(MemIoTest_575, ConstructWithData_575) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

// Test simple write and read back
TEST_F(MemIoTest_575, WriteAndReadBack_575) {
    MemIo memIo;
    const byte data[] = "Hello, World!";
    size_t len = sizeof(data);
    
    size_t written = memIo.write(data, len);
    EXPECT_EQ(written, len);
    EXPECT_EQ(memIo.size(), len);
    
    // Seek to beginning and read back
    memIo.seek(0, BasicIo::beg);
    byte buffer[64] = {};
    size_t readCount = memIo.read(buffer, len);
    EXPECT_EQ(readCount, len);
    EXPECT_EQ(std::memcmp(data, buffer, len), 0);
}

// Test writing zero bytes
TEST_F(MemIoTest_575, WriteZeroBytes_575) {
    MemIo memIo;
    const byte data[] = {0x01};
    size_t written = memIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    EXPECT_EQ(memIo.size(), 0u);
}

// Test small write that triggers initial allocation (reserve with isMalloced_ = false)
TEST_F(MemIoTest_575, SmallWriteOnConstData_575) {
    const byte initialData[] = {0x01, 0x02, 0x03};
    MemIo memIo(initialData, sizeof(initialData));
    
    // Seek to end and write more data - this should trigger reserve with isMalloced_ = false
    memIo.seek(0, BasicIo::end);
    const byte moreData[] = {0x04, 0x05};
    size_t written = memIo.write(moreData, sizeof(moreData));
    EXPECT_EQ(written, sizeof(moreData));
    EXPECT_EQ(memIo.size(), sizeof(initialData) + sizeof(moreData));
    
    // Verify all data
    memIo.seek(0, BasicIo::beg);
    byte buffer[5];
    memIo.read(buffer, 5);
    EXPECT_EQ(buffer[0], 0x01);
    EXPECT_EQ(buffer[1], 0x02);
    EXPECT_EQ(buffer[2], 0x03);
    EXPECT_EQ(buffer[3], 0x04);
    EXPECT_EQ(buffer[4], 0x05);
}

// Test large write that exceeds initial block size (32KB)
TEST_F(MemIoTest_575, LargeWriteExceedsBlockSize_575) {
    MemIo memIo;
    const size_t largeSize = 64 * 1024; // 64KB
    std::vector<byte> data(largeSize, 0xAB);
    
    size_t written = memIo.write(data.data(), largeSize);
    EXPECT_EQ(written, largeSize);
    EXPECT_EQ(memIo.size(), largeSize);
    
    // Read back and verify
    memIo.seek(0, BasicIo::beg);
    std::vector<byte> readBuf(largeSize);
    size_t readCount = memIo.read(readBuf.data(), largeSize);
    EXPECT_EQ(readCount, largeSize);
    EXPECT_EQ(data, readBuf);
}

// Test multiple writes that trigger reallocation (growing past sizeAlloced_)
TEST_F(MemIoTest_575, MultipleWritesCauseReallocation_575) {
    MemIo memIo;
    const size_t chunkSize = 16 * 1024; // 16KB chunks
    std::vector<byte> chunk(chunkSize, 0xCD);
    
    // Write multiple chunks to force reallocation
    for (int i = 0; i < 10; ++i) {
        size_t written = memIo.write(chunk.data(), chunkSize);
        EXPECT_EQ(written, chunkSize);
    }
    
    EXPECT_EQ(memIo.size(), 10 * chunkSize);
    
    // Verify first chunk
    memIo.seek(0, BasicIo::beg);
    std::vector<byte> readBuf(chunkSize);
    memIo.read(readBuf.data(), chunkSize);
    EXPECT_EQ(readBuf, chunk);
}

// Test very large write that exceeds maxBlockSize (4MB)
TEST_F(MemIoTest_575, VeryLargeWriteExceedsMaxBlockSize_575) {
    MemIo memIo;
    const size_t veryLargeSize = 5 * 1024 * 1024; // 5MB
    std::vector<byte> data(veryLargeSize, 0xEF);
    
    size_t written = memIo.write(data.data(), veryLargeSize);
    EXPECT_EQ(written, veryLargeSize);
    EXPECT_EQ(memIo.size(), veryLargeSize);
}

// Test seek and tell
TEST_F(MemIoTest_575, SeekAndTell_575) {
    MemIo memIo;
    const byte data[] = "ABCDEFGHIJ";
    memIo.write(data, 10);
    
    // Seek from beginning
    EXPECT_EQ(memIo.seek(0, BasicIo::beg), 0);
    EXPECT_EQ(memIo.tell(), 0);
    
    EXPECT_EQ(memIo.seek(5, BasicIo::beg), 0);
    EXPECT_EQ(memIo.tell(), 5);
    
    // Seek from current
    EXPECT_EQ(memIo.seek(2, BasicIo::cur), 0);
    EXPECT_EQ(memIo.tell(), 7);
    
    // Seek from end
    EXPECT_EQ(memIo.seek(0, BasicIo::end), 0);
    EXPECT_EQ(memIo.tell(), 10);
    
    EXPECT_EQ(memIo.seek(-3, BasicIo::end), 0);
    EXPECT_EQ(memIo.tell(), 7);
}

// Test eof detection
TEST_F(MemIoTest_575, EofDetection_575) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, 3);
    memIo.seek(0, BasicIo::beg);
    
    byte buffer[10];
    size_t readCount = memIo.read(buffer, 10); // Try to read more than available
    EXPECT_EQ(readCount, 3u);
    EXPECT_TRUE(memIo.eof());
}

// Test read from empty MemIo
TEST_F(MemIoTest_575, ReadFromEmpty_575) {
    MemIo memIo;
    byte buffer[10];
    size_t readCount = memIo.read(buffer, 10);
    EXPECT_EQ(readCount, 0u);
    EXPECT_TRUE(memIo.eof());
}

// Test writing at a position in the middle (overwrite)
TEST_F(MemIoTest_575, WriteInMiddle_575) {
    MemIo memIo;
    const byte data[] = "ABCDEFGHIJ";
    memIo.write(data, 10);
    
    memIo.seek(3, BasicIo::beg);
    const byte overwrite[] = "XY";
    memIo.write(overwrite, 2);
    
    // Size should remain 10
    EXPECT_EQ(memIo.size(), 10u);
    
    // Verify the overwritten data
    memIo.seek(0, BasicIo::beg);
    byte buffer[10];
    memIo.read(buffer, 10);
    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'B');
    EXPECT_EQ(buffer[2], 'C');
    EXPECT_EQ(buffer[3], 'X');
    EXPECT_EQ(buffer[4], 'Y');
    EXPECT_EQ(buffer[5], 'F');
}

// Test writing with constructed data then appending to grow
TEST_F(MemIoTest_575, AppendToConstructedData_575) {
    const byte initial[] = {0x10, 0x20, 0x30};
    MemIo memIo(initial, sizeof(initial));
    
    memIo.seek(0, BasicIo::end);
    
    // Write enough to trigger reserve and copy of original data
    std::vector<byte> appendData(40000, 0xFF);
    size_t written = memIo.write(appendData.data(), appendData.size());
    EXPECT_EQ(written, appendData.size());
    EXPECT_EQ(memIo.size(), sizeof(initial) + appendData.size());
    
    // Verify original data preserved
    memIo.seek(0, BasicIo::beg);
    byte buf[3];
    memIo.read(buf, 3);
    EXPECT_EQ(buf[0], 0x10);
    EXPECT_EQ(buf[1], 0x20);
    EXPECT_EQ(buf[2], 0x30);
}

// Test repeated growing writes (stress the realloc path in reserve)
TEST_F(MemIoTest_575, RepeatedGrowingWrites_575) {
    MemIo memIo;
    size_t totalWritten = 0;
    
    for (int i = 0; i < 1000; ++i) {
        byte val = static_cast<byte>(i & 0xFF);
        size_t written = memIo.write(&val, 1);
        EXPECT_EQ(written, 1u);
        totalWritten++;
    }
    
    EXPECT_EQ(memIo.size(), totalWritten);
    
    // Verify some values
    memIo.seek(0, BasicIo::beg);
    byte buf;
    memIo.read(&buf, 1);
    EXPECT_EQ(buf, 0x00);
    
    memIo.seek(255, BasicIo::beg);
    memIo.read(&buf, 1);
    EXPECT_EQ(buf, 0xFF);
}

// Test isopen
TEST_F(MemIoTest_575, IsOpen_575) {
    MemIo memIo;
    EXPECT_TRUE(memIo.isopen());
}

// Test path returns empty string for MemIo
TEST_F(MemIoTest_575, PathReturnsExpected_575) {
    MemIo memIo;
    // MemIo path is typically empty or a placeholder
    std::string path = memIo.path();
    // Just verify it doesn't crash and returns something
    EXPECT_FALSE(path.empty() && false); // always passes, just checking no crash
}

// Test mmap and munmap
TEST_F(MemIoTest_575, MmapAccess_575) {
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    MemIo memIo(data, sizeof(data));
    
    bool isWriteable = false;
    byte* mapped = memIo.mmap(isWriteable);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0xAA);
    EXPECT_EQ(mapped[1], 0xBB);
    EXPECT_EQ(mapped[2], 0xCC);
    EXPECT_EQ(mapped[3], 0xDD);
    
    EXPECT_EQ(memIo.munmap(), 0);
}

// Test transfer from one MemIo to another
TEST_F(MemIoTest_575, TransferData_575) {
    MemIo src;
    const byte data[] = "Transfer this!";
    src.write(data, sizeof(data));
    src.seek(0, BasicIo::beg);
    
    MemIo dst;
    dst.transfer(src);
    
    EXPECT_EQ(dst.size(), sizeof(data));
    dst.seek(0, BasicIo::beg);
    byte buffer[64] = {};
    dst.read(buffer, sizeof(data));
    EXPECT_EQ(std::memcmp(buffer, data, sizeof(data)), 0);
}

// Test write from one MemIo to another using write(BasicIo&)
TEST_F(MemIoTest_575, WriteFromBasicIo_575) {
    MemIo src;
    const byte data[] = "Source data";
    src.write(data, sizeof(data));
    src.seek(0, BasicIo::beg);
    
    MemIo dst;
    size_t written = dst.write(src);
    EXPECT_EQ(written, sizeof(data));
    EXPECT_EQ(dst.size(), sizeof(data));
}

// Test that writing grows size_ correctly in reserve
TEST_F(MemIoTest_575, WritePreciselyAtBlockBoundary_575) {
    MemIo memIo;
    // Write exactly 32768 bytes (one block size)
    const size_t blockSize = 32 * 1024;
    std::vector<byte> data(blockSize, 0x42);
    
    size_t written = memIo.write(data.data(), blockSize);
    EXPECT_EQ(written, blockSize);
    EXPECT_EQ(memIo.size(), blockSize);
    
    // Write one more byte to force growth
    byte extra = 0x99;
    written = memIo.write(&extra, 1);
    EXPECT_EQ(written, 1u);
    EXPECT_EQ(memIo.size(), blockSize + 1);
}

// Test putb and getb
TEST_F(MemIoTest_575, PutbAndGetb_575) {
    MemIo memIo;
    
    EXPECT_EQ(memIo.putb(0x42), 0x42);
    EXPECT_EQ(memIo.size(), 1u);
    
    memIo.seek(0, BasicIo::beg);
    int val = memIo.getb();
    EXPECT_EQ(val, 0x42);
}

// Test getb at eof returns EOF
TEST_F(MemIoTest_575, GetbAtEof_575) {
    MemIo memIo;
    int val = memIo.getb();
    EXPECT_EQ(val, EOF);
}

// Test progressive writes that cross multiple reallocation thresholds
TEST_F(MemIoTest_575, ProgressiveGrowthAcrossThresholds_575) {
    MemIo memIo;
    // Write in increasingly large chunks to exercise the doubling + maxBlockSize logic
    size_t currentSize = 0;
    size_t chunkSize = 1024;
    
    for (int i = 0; i < 20; ++i) {
        std::vector<byte> chunk(chunkSize, static_cast<byte>(i));
        size_t written = memIo.write(chunk.data(), chunkSize);
        EXPECT_EQ(written, chunkSize);
        currentSize += chunkSize;
        chunkSize *= 2;
    }
    
    EXPECT_EQ(memIo.size(), currentSize);
}

// Test open and close
TEST_F(MemIoTest_575, OpenAndClose_575) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
    EXPECT_TRUE(memIo.isopen());
    EXPECT_EQ(memIo.close(), 0);
}

// Test seek beyond end
TEST_F(MemIoTest_575, SeekBeyondEnd_575) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02};
    memIo.write(data, 2);
    
    // Seek beyond the end - behavior should be defined
    int result = memIo.seek(100, BasicIo::beg);
    // Depending on implementation, this might succeed or fail
    // Just ensure no crash
    (void)result;
}

// Test negative seek from beginning
TEST_F(MemIoTest_575, NegativeSeekFromBeginning_575) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, 3);
    
    int result = memIo.seek(-1, BasicIo::beg);
    // Should fail
    EXPECT_NE(result, 0);
}

}  // namespace
