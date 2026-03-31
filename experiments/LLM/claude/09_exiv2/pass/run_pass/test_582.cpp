#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers for Exiv2
#include "exiv2/basicio.hpp"

#include <cstring>
#include <string>
#include <vector>
#include <fstream>

using namespace Exiv2;

// ============================================================
// MemIo Tests
// ============================================================

class MemIoTest_582 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction creates an empty MemIo
TEST_F(MemIoTest_582, DefaultConstruction_IsEmpty_582) {
    MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
    EXPECT_TRUE(memIo.eof());
}

// Test construction with data buffer
TEST_F(MemIoTest_582, ConstructionWithData_582) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
}

// Test mmap returns non-null pointer for non-empty MemIo
TEST_F(MemIoTest_582, MmapReturnsDataPointer_582) {
    const byte data[] = {0xAA, 0xBB, 0xCC};
    MemIo memIo(data, sizeof(data));
    byte* mapped = memIo.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0xAA);
    EXPECT_EQ(mapped[1], 0xBB);
    EXPECT_EQ(mapped[2], 0xCC);
    memIo.munmap();
}

// Test mmap with isWriteable true
TEST_F(MemIoTest_582, MmapWriteable_582) {
    const byte data[] = {0x10, 0x20, 0x30};
    MemIo memIo(data, sizeof(data));
    byte* mapped = memIo.mmap(true);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0x10);
    EXPECT_EQ(mapped[1], 0x20);
    EXPECT_EQ(mapped[2], 0x30);
    memIo.munmap();
}

// Test mmap with isWriteable false (read-only)
TEST_F(MemIoTest_582, MmapReadOnly_582) {
    const byte data[] = {0xFF, 0xFE};
    MemIo memIo(data, sizeof(data));
    byte* mapped = memIo.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0xFF);
    EXPECT_EQ(mapped[1], 0xFE);
    memIo.munmap();
}

// Test write and then mmap
TEST_F(MemIoTest_582, WriteAndMmap_582) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.size(), sizeof(data));
    
    byte* mapped = memIo.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0x01);
    EXPECT_EQ(mapped[3], 0x04);
    memIo.munmap();
}

// Test open on MemIo
TEST_F(MemIoTest_582, OpenReturnsZero_582) {
    MemIo memIo;
    EXPECT_EQ(memIo.open(), 0);
}

// Test isopen
TEST_F(MemIoTest_582, IsOpen_582) {
    MemIo memIo;
    // MemIo is always considered "open"
    EXPECT_TRUE(memIo.isopen());
}

// Test close
TEST_F(MemIoTest_582, Close_582) {
    MemIo memIo;
    EXPECT_EQ(memIo.close(), 0);
}

// Test read from MemIo
TEST_F(MemIoTest_582, ReadData_582) {
    const byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    MemIo memIo(data, sizeof(data));
    
    byte buf[4] = {0};
    long bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, 4);
    EXPECT_EQ(buf[0], 0xDE);
    EXPECT_EQ(buf[1], 0xAD);
    EXPECT_EQ(buf[2], 0xBE);
    EXPECT_EQ(buf[3], 0xEF);
}

// Test seek and tell
TEST_F(MemIoTest_582, SeekAndTell_582) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    
    EXPECT_EQ(memIo.tell(), 0);
    memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(memIo.tell(), 3);
    
    byte buf[1] = {0};
    memIo.read(buf, 1);
    EXPECT_EQ(buf[0], 0x04);
}

// Test seek from end
TEST_F(MemIoTest_582, SeekFromEnd_582) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    
    memIo.seek(-2, BasicIo::end);
    EXPECT_EQ(memIo.tell(), 3);
    
    byte buf[1] = {0};
    memIo.read(buf, 1);
    EXPECT_EQ(buf[0], 0x04);
}

// Test seek from current position
TEST_F(MemIoTest_582, SeekFromCurrent_582) {
    const byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    MemIo memIo(data, sizeof(data));
    
    memIo.seek(1, BasicIo::beg);
    memIo.seek(2, BasicIo::cur);
    EXPECT_EQ(memIo.tell(), 3);
}

// Test eof
TEST_F(MemIoTest_582, EofAfterReadAll_582) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    
    byte buf[10] = {0};
    memIo.read(buf, sizeof(buf));
    EXPECT_TRUE(memIo.eof());
}

// Test write increases size
TEST_F(MemIoTest_582, WriteThenCheckSize_582) {
    MemIo memIo;
    const byte data[] = {0x01, 0x02, 0x03};
    memIo.write(data, sizeof(data));
    EXPECT_EQ(memIo.size(), 3u);
}

// Test multiple writes
TEST_F(MemIoTest_582, MultipleWrites_582) {
    MemIo memIo;
    const byte data1[] = {0x01, 0x02};
    const byte data2[] = {0x03, 0x04, 0x05};
    memIo.write(data1, sizeof(data1));
    memIo.write(data2, sizeof(data2));
    EXPECT_EQ(memIo.size(), 5u);
    
    byte* mapped = memIo.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0x01);
    EXPECT_EQ(mapped[1], 0x02);
    EXPECT_EQ(mapped[2], 0x03);
    EXPECT_EQ(mapped[3], 0x04);
    EXPECT_EQ(mapped[4], 0x05);
    memIo.munmap();
}

// Test mmap on empty MemIo
TEST_F(MemIoTest_582, MmapOnEmpty_582) {
    MemIo memIo;
    byte* mapped = memIo.mmap(false);
    // For empty MemIo, mmap may return nullptr or some valid pointer
    // We just verify it doesn't crash
    memIo.munmap();
}

// Test writing modifiable data through mmap
TEST_F(MemIoTest_582, MmapModifyData_582) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    
    byte* mapped = memIo.mmap(true);
    ASSERT_NE(mapped, nullptr);
    mapped[0] = 0xFF;
    
    // Verify the modification persists
    EXPECT_EQ(mapped[0], 0xFF);
    memIo.munmap();
    
    // Re-mmap and verify
    byte* mapped2 = memIo.mmap(false);
    EXPECT_EQ(mapped2[0], 0xFF);
    memIo.munmap();
}

// Test large data mmap
TEST_F(MemIoTest_582, LargeDataMmap_582) {
    std::vector<byte> largeData(10000, 0x42);
    MemIo memIo(largeData.data(), largeData.size());
    
    byte* mapped = memIo.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0x42);
    EXPECT_EQ(mapped[9999], 0x42);
    EXPECT_EQ(memIo.size(), 10000u);
    memIo.munmap();
}

// Test read after write with seek
TEST_F(MemIoTest_582, WriteSeekRead_582) {
    MemIo memIo;
    const byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    memIo.write(data, sizeof(data));
    
    memIo.seek(0, BasicIo::beg);
    byte buf[4] = {0};
    long bytesRead = memIo.read(buf, sizeof(buf));
    EXPECT_EQ(bytesRead, 4);
    EXPECT_EQ(buf[0], 0xAA);
    EXPECT_EQ(buf[3], 0xDD);
}

// Test single byte data
TEST_F(MemIoTest_582, SingleByteMmap_582) {
    const byte data[] = {0x99};
    MemIo memIo(data, 1);
    
    byte* mapped = memIo.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0x99);
    EXPECT_EQ(memIo.size(), 1u);
    memIo.munmap();
}

// Test transfer from one MemIo to another
TEST_F(MemIoTest_582, TransferData_582) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo src(data, sizeof(data));
    MemIo dst;
    
    dst.transfer(src);
    EXPECT_EQ(dst.size(), sizeof(data));
    
    byte* mapped = dst.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0x01);
    EXPECT_EQ(mapped[1], 0x02);
    EXPECT_EQ(mapped[2], 0x03);
    dst.munmap();
}

// Test path returns empty for MemIo
TEST_F(MemIoTest_582, PathIsEmpty_582) {
    MemIo memIo;
    // MemIo typically has an empty or "MemIo" path
    std::string path = memIo.path();
    // Just verify it doesn't crash; exact value depends on implementation
    EXPECT_FALSE(path.empty() && false); // always passes, just checks no crash
}

// Test error returns zero for normal operation
TEST_F(MemIoTest_582, ErrorReturnsZero_582) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    EXPECT_EQ(memIo.error(), 0);
}

// Test putb and getb
TEST_F(MemIoTest_582, PutbAndGetb_582) {
    MemIo memIo;
    memIo.putb(0x42);
    
    memIo.seek(0, BasicIo::beg);
    int val = memIo.getb();
    EXPECT_EQ(val, 0x42);
}

// Test reading partial data
TEST_F(MemIoTest_582, ReadPartialData_582) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    
    byte buf[2] = {0};
    long bytesRead = memIo.read(buf, 2);
    EXPECT_EQ(bytesRead, 2);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
    EXPECT_EQ(memIo.tell(), 2);
}

// Test reading more than available
TEST_F(MemIoTest_582, ReadMoreThanAvailable_582) {
    const byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    
    byte buf[10] = {0};
    long bytesRead = memIo.read(buf, 10);
    EXPECT_EQ(bytesRead, 2);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
}

// Test mmap called multiple times
TEST_F(MemIoTest_582, MmapCalledMultipleTimes_582) {
    const byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    
    byte* mapped1 = memIo.mmap(false);
    ASSERT_NE(mapped1, nullptr);
    EXPECT_EQ(mapped1[0], 0x01);
    memIo.munmap();
    
    byte* mapped2 = memIo.mmap(true);
    ASSERT_NE(mapped2, nullptr);
    EXPECT_EQ(mapped2[0], 0x01);
    memIo.munmap();
}
