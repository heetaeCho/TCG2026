#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <cstring>
#include <fstream>

// Helper to create a temporary file with known content
class MemIoMmapTest_610 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test mmap on empty MemIo
TEST_F(MemIoMmapTest_610, MmapEmptyMemIo_610) {
    Exiv2::MemIo memIo;
    EXPECT_EQ(memIo.size(), 0u);
    Exiv2::byte* data = memIo.mmap(false);
    // For empty IO, mmap may return nullptr or a valid pointer with size 0
    // The key observable behavior is it doesn't crash
    memIo.munmap();
}

// Test mmap on MemIo with data (read-only)
TEST_F(MemIoMmapTest_610, MmapReadOnlyWithData_610) {
    const Exiv2::byte testData[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    Exiv2::MemIo memIo(testData, sizeof(testData));
    
    Exiv2::byte* mapped = memIo.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(memIo.size(), sizeof(testData));
    EXPECT_EQ(std::memcmp(mapped, testData, sizeof(testData)), 0);
    memIo.munmap();
}

// Test mmap on MemIo with data (writeable)
TEST_F(MemIoMmapTest_610, MmapWriteableWithData_610) {
    const Exiv2::byte testData[] = {0x10, 0x20, 0x30};
    Exiv2::MemIo memIo(testData, sizeof(testData));
    
    Exiv2::byte* mapped = memIo.mmap(true);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(memIo.size(), sizeof(testData));
    EXPECT_EQ(mapped[0], 0x10);
    EXPECT_EQ(mapped[1], 0x20);
    EXPECT_EQ(mapped[2], 0x30);
    memIo.munmap();
}

// Test that calling mmap twice returns same pointer (caching behavior)
TEST_F(MemIoMmapTest_610, MmapCalledTwiceReturnsSameData_610) {
    const Exiv2::byte testData[] = {0xAA, 0xBB, 0xCC, 0xDD};
    Exiv2::MemIo memIo(testData, sizeof(testData));
    
    Exiv2::byte* mapped1 = memIo.mmap(false);
    Exiv2::byte* mapped2 = memIo.mmap(false);
    ASSERT_NE(mapped1, nullptr);
    ASSERT_NE(mapped2, nullptr);
    // Both calls should return data that matches the original
    EXPECT_EQ(std::memcmp(mapped1, testData, sizeof(testData)), 0);
    EXPECT_EQ(std::memcmp(mapped2, testData, sizeof(testData)), 0);
    memIo.munmap();
}

// Test mmap with single byte data
TEST_F(MemIoMmapTest_610, MmapSingleByte_610) {
    const Exiv2::byte testData[] = {0xFF};
    Exiv2::MemIo memIo(testData, 1);
    
    Exiv2::byte* mapped = memIo.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(mapped[0], 0xFF);
    EXPECT_EQ(memIo.size(), 1u);
    memIo.munmap();
}

// Test mmap with larger data block
TEST_F(MemIoMmapTest_610, MmapLargerData_610) {
    std::vector<Exiv2::byte> testData(4096, 0x42);
    Exiv2::MemIo memIo(testData.data(), testData.size());
    
    Exiv2::byte* mapped = memIo.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(memIo.size(), 4096u);
    for (size_t i = 0; i < testData.size(); ++i) {
        EXPECT_EQ(mapped[i], 0x42) << "Mismatch at index " << i;
    }
    memIo.munmap();
}

// Test FileIo mmap with a temporary file
class FileIoMmapTest_610 : public ::testing::Test {
protected:
    std::string tempFile_;
    
    void SetUp() override {
        tempFile_ = "test_mmap_610.tmp";
        std::ofstream ofs(tempFile_, std::ios::binary);
        const char data[] = "Hello, mmap test!";
        ofs.write(data, sizeof(data) - 1);
        ofs.close();
    }
    
    void TearDown() override {
        std::remove(tempFile_.c_str());
    }
};

TEST_F(FileIoMmapTest_610, MmapFileIoReadsCorrectData_610) {
    Exiv2::FileIo fileIo(tempFile_);
    ASSERT_EQ(fileIo.open(), 0);
    
    Exiv2::byte* mapped = fileIo.mmap(false);
    ASSERT_NE(mapped, nullptr);
    
    const char expected[] = "Hello, mmap test!";
    EXPECT_EQ(fileIo.size(), sizeof(expected) - 1);
    EXPECT_EQ(std::memcmp(mapped, expected, sizeof(expected) - 1), 0);
    
    fileIo.munmap();
    fileIo.close();
}

TEST_F(FileIoMmapTest_610, MmapFileIoWriteable_610) {
    Exiv2::FileIo fileIo(tempFile_);
    ASSERT_EQ(fileIo.open(), 0);
    
    Exiv2::byte* mapped = fileIo.mmap(true);
    ASSERT_NE(mapped, nullptr);
    EXPECT_GT(fileIo.size(), 0u);
    
    fileIo.munmap();
    fileIo.close();
}

// Test munmap without mmap should not crash
TEST_F(MemIoMmapTest_610, MunmapWithoutMmap_610) {
    const Exiv2::byte testData[] = {0x01, 0x02};
    Exiv2::MemIo memIo(testData, sizeof(testData));
    // Calling munmap without mmap should be safe
    EXPECT_NO_THROW(memIo.munmap());
}

// Test mmap followed by munmap followed by mmap again
TEST_F(MemIoMmapTest_610, MmapAfterMunmap_610) {
    const Exiv2::byte testData[] = {0xDE, 0xAD, 0xBE, 0xEF};
    Exiv2::MemIo memIo(testData, sizeof(testData));
    
    Exiv2::byte* mapped1 = memIo.mmap(false);
    ASSERT_NE(mapped1, nullptr);
    memIo.munmap();
    
    Exiv2::byte* mapped2 = memIo.mmap(false);
    ASSERT_NE(mapped2, nullptr);
    EXPECT_EQ(std::memcmp(mapped2, testData, sizeof(testData)), 0);
    memIo.munmap();
}
