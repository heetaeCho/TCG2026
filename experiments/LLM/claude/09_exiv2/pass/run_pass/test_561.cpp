#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <filesystem>

#include "exiv2/basicio.hpp"

namespace {

// Helper to create a temporary file with given content
class TempFile {
public:
    explicit TempFile(const std::string& name, const std::string& content = "") : path_(name) {
        std::ofstream ofs(path_, std::ios::binary);
        if (!content.empty()) {
            ofs.write(content.data(), content.size());
        }
        ofs.close();
    }
    ~TempFile() {
        std::remove(path_.c_str());
    }
    const std::string& path() const { return path_; }
private:
    std::string path_;
};

} // namespace

class FileIoTest_561 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test: Constructor sets the path correctly
TEST_F(FileIoTest_561, ConstructorSetsPath_561) {
    std::string testPath = "test_file_constructor_561.tmp";
    Exiv2::FileIo fileIo(testPath);
    EXPECT_EQ(fileIo.path(), testPath);
}

// Test: Newly constructed FileIo is not open
TEST_F(FileIoTest_561, InitiallyNotOpen_561) {
    std::string testPath = "test_file_not_open_561.tmp";
    Exiv2::FileIo fileIo(testPath);
    EXPECT_FALSE(fileIo.isopen());
}

// Test: Open an existing file returns success
TEST_F(FileIoTest_561, OpenExistingFileReturnsSuccess_561) {
    TempFile tmp("test_open_existing_561.tmp", "hello");
    Exiv2::FileIo fileIo(tmp.path());
    int result = fileIo.open();
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(fileIo.isopen());
    fileIo.close();
}

// Test: Open a non-existing file returns error
TEST_F(FileIoTest_561, OpenNonExistingFileReturnsError_561) {
    Exiv2::FileIo fileIo("nonexistent_file_561_xyz.tmp");
    int result = fileIo.open();
    EXPECT_NE(result, 0);
    EXPECT_FALSE(fileIo.isopen());
}

// Test: Open with mode "w" creates a file
TEST_F(FileIoTest_561, OpenWithWriteMode_561) {
    std::string testPath = "test_open_write_mode_561.tmp";
    // Make sure file doesn't exist
    std::remove(testPath.c_str());
    
    Exiv2::FileIo fileIo(testPath);
    int result = fileIo.open("w");
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(fileIo.isopen());
    fileIo.close();
    
    // Cleanup
    std::remove(testPath.c_str());
}

// Test: Close a file makes isopen return false
TEST_F(FileIoTest_561, CloseFile_561) {
    TempFile tmp("test_close_561.tmp", "data");
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_TRUE(fileIo.isopen());
    int result = fileIo.close();
    EXPECT_EQ(result, 0);
    EXPECT_FALSE(fileIo.isopen());
}

// Test: Close on an already closed file
TEST_F(FileIoTest_561, CloseAlreadyClosed_561) {
    TempFile tmp("test_close_already_561.tmp", "data");
    Exiv2::FileIo fileIo(tmp.path());
    // Not opened, close should still work (or at least not crash)
    int result = fileIo.close();
    EXPECT_EQ(result, 0);
}

// Test: Size of a file
TEST_F(FileIoTest_561, SizeOfFile_561) {
    std::string content = "Hello, World!";
    TempFile tmp("test_size_561.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_EQ(fileIo.size(), content.size());
    fileIo.close();
}

// Test: Size of empty file
TEST_F(FileIoTest_561, SizeOfEmptyFile_561) {
    TempFile tmp("test_size_empty_561.tmp", "");
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_EQ(fileIo.size(), 0u);
    fileIo.close();
}

// Test: Tell returns 0 at beginning
TEST_F(FileIoTest_561, TellAtBeginning_561) {
    TempFile tmp("test_tell_561.tmp", "some content");
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_EQ(fileIo.tell(), 0u);
    fileIo.close();
}

// Test: Write data and verify size
TEST_F(FileIoTest_561, WriteDataAndCheckSize_561) {
    std::string testPath = "test_write_561.tmp";
    std::remove(testPath.c_str());
    
    Exiv2::FileIo fileIo(testPath);
    fileIo.open("w");
    
    const Exiv2::byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    size_t written = fileIo.write(data, sizeof(data));
    EXPECT_EQ(written, sizeof(data));
    fileIo.close();
    
    // Re-open and check size
    fileIo.open();
    EXPECT_EQ(fileIo.size(), sizeof(data));
    fileIo.close();
    
    std::remove(testPath.c_str());
}

// Test: Read data back after writing
TEST_F(FileIoTest_561, ReadDataAfterWrite_561) {
    std::string testPath = "test_readwrite_561.tmp";
    std::remove(testPath.c_str());
    
    const Exiv2::byte writeData[] = {0xAA, 0xBB, 0xCC, 0xDD};
    
    {
        Exiv2::FileIo fileIo(testPath);
        fileIo.open("w");
        fileIo.write(writeData, sizeof(writeData));
        fileIo.close();
    }
    
    {
        Exiv2::FileIo fileIo(testPath);
        fileIo.open();
        Exiv2::byte readBuf[4] = {};
        size_t bytesRead = fileIo.read(readBuf, sizeof(readBuf));
        EXPECT_EQ(bytesRead, sizeof(writeData));
        EXPECT_EQ(readBuf[0], 0xAA);
        EXPECT_EQ(readBuf[1], 0xBB);
        EXPECT_EQ(readBuf[2], 0xCC);
        EXPECT_EQ(readBuf[3], 0xDD);
        fileIo.close();
    }
    
    std::remove(testPath.c_str());
}

// Test: Read using DataBuf overload
TEST_F(FileIoTest_561, ReadDataBuf_561) {
    std::string content = "TestData";
    TempFile tmp("test_readbuf_561.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    Exiv2::DataBuf buf = fileIo.read(content.size());
    EXPECT_EQ(buf.size(), content.size());
    fileIo.close();
}

// Test: Read more bytes than available
TEST_F(FileIoTest_561, ReadMoreThanAvailable_561) {
    std::string content = "short";
    TempFile tmp("test_read_more_561.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    Exiv2::byte readBuf[100] = {};
    size_t bytesRead = fileIo.read(readBuf, 100);
    EXPECT_EQ(bytesRead, content.size());
    fileIo.close();
}

// Test: getb reads single byte
TEST_F(FileIoTest_561, GetbReadsSingleByte_561) {
    std::string content = "A";
    TempFile tmp("test_getb_561.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    int byte = fileIo.getb();
    EXPECT_EQ(byte, 'A');
    fileIo.close();
}

// Test: getb returns EOF when file is empty
TEST_F(FileIoTest_561, GetbOnEmptyFile_561) {
    TempFile tmp("test_getb_empty_561.tmp", "");
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    int byte = fileIo.getb();
    EXPECT_EQ(byte, EOF);
    fileIo.close();
}

// Test: putb writes a single byte
TEST_F(FileIoTest_561, PutbWritesByte_561) {
    std::string testPath = "test_putb_561.tmp";
    std::remove(testPath.c_str());
    
    Exiv2::FileIo fileIo(testPath);
    fileIo.open("w");
    int result = fileIo.putb(0x42);
    EXPECT_EQ(result, 0x42);
    fileIo.close();
    
    // Verify
    fileIo.open();
    EXPECT_EQ(fileIo.size(), 1u);
    int readByte = fileIo.getb();
    EXPECT_EQ(readByte, 0x42);
    fileIo.close();
    
    std::remove(testPath.c_str());
}

// Test: Seek to beginning
TEST_F(FileIoTest_561, SeekToBeginning_561) {
    std::string content = "0123456789";
    TempFile tmp("test_seek_beg_561.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    
    // Read some bytes first
    Exiv2::byte buf[5];
    fileIo.read(buf, 5);
    EXPECT_EQ(fileIo.tell(), 5u);
    
    // Seek back to beginning
    int result = fileIo.seek(0, Exiv2::BasicIo::beg);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(fileIo.tell(), 0u);
    fileIo.close();
}

// Test: Seek to end
TEST_F(FileIoTest_561, SeekToEnd_561) {
    std::string content = "0123456789";
    TempFile tmp("test_seek_end_561.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    
    int result = fileIo.seek(0, Exiv2::BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(fileIo.tell(), content.size());
    fileIo.close();
}

// Test: Seek with current position
TEST_F(FileIoTest_561, SeekFromCurrent_561) {
    std::string content = "0123456789";
    TempFile tmp("test_seek_cur_561.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    
    fileIo.seek(3, Exiv2::BasicIo::beg);
    EXPECT_EQ(fileIo.tell(), 3u);
    
    fileIo.seek(2, Exiv2::BasicIo::cur);
    EXPECT_EQ(fileIo.tell(), 5u);
    fileIo.close();
}

// Test: eof returns false initially
TEST_F(FileIoTest_561, EofInitiallyFalse_561) {
    std::string content = "data";
    TempFile tmp("test_eof_false_561.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_FALSE(fileIo.eof());
    fileIo.close();
}

// Test: eof returns true after reading past end
TEST_F(FileIoTest_561, EofAfterReadPastEnd_561) {
    std::string content = "ab";
    TempFile tmp("test_eof_true_561.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    
    Exiv2::byte buf[10];
    fileIo.read(buf, 10);  // read more than available
    EXPECT_TRUE(fileIo.eof());
    fileIo.close();
}

// Test: error returns 0 on no error
TEST_F(FileIoTest_561, ErrorReturnsZeroOnSuccess_561) {
    TempFile tmp("test_error_561.tmp", "data");
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_EQ(fileIo.error(), 0);
    fileIo.close();
}

// Test: path returns correct path
TEST_F(FileIoTest_561, PathReturnsCorrectPath_561) {
    std::string testPath = "my_test_path_561.tmp";
    Exiv2::FileIo fileIo(testPath);
    EXPECT_EQ(fileIo.path(), testPath);
}

// Test: setPath changes the path
TEST_F(FileIoTest_561, SetPathChangesPath_561) {
    Exiv2::FileIo fileIo("original_path_561.tmp");
    EXPECT_EQ(fileIo.path(), "original_path_561.tmp");
    fileIo.setPath("new_path_561.tmp");
    EXPECT_EQ(fileIo.path(), "new_path_561.tmp");
}

// Test: Write from another BasicIo source
TEST_F(FileIoTest_561, WriteFromAnotherIo_561) {
    std::string srcContent = "source data 561";
    TempFile tmpSrc("test_write_src_561.tmp", srcContent);
    std::string dstPath = "test_write_dst_561.tmp";
    std::remove(dstPath.c_str());
    
    Exiv2::FileIo srcIo(tmpSrc.path());
    srcIo.open();
    
    Exiv2::FileIo dstIo(dstPath);
    dstIo.open("w");
    
    size_t written = dstIo.write(srcIo);
    EXPECT_EQ(written, srcContent.size());
    
    srcIo.close();
    dstIo.close();
    
    // Verify destination content
    Exiv2::FileIo verifyIo(dstPath);
    verifyIo.open();
    EXPECT_EQ(verifyIo.size(), srcContent.size());
    verifyIo.close();
    
    std::remove(dstPath.c_str());
}

// Test: Transfer replaces content
TEST_F(FileIoTest_561, TransferFromAnotherIo_561) {
    std::string srcContent = "transferred data 561";
    std::string srcPath = "test_transfer_src_561.tmp";
    std::string dstPath = "test_transfer_dst_561.tmp";
    
    // Create source file
    {
        std::ofstream ofs(srcPath, std::ios::binary);
        ofs.write(srcContent.data(), srcContent.size());
    }
    
    // Create destination with some existing content
    {
        std::ofstream ofs(dstPath, std::ios::binary);
        ofs.write("old", 3);
    }
    
    Exiv2::FileIo srcIo(srcPath);
    Exiv2::FileIo dstIo(dstPath);
    
    dstIo.transfer(srcIo);
    
    // After transfer, destination should have source content
    dstIo.open();
    EXPECT_EQ(dstIo.size(), srcContent.size());
    dstIo.close();
    
    std::remove(srcPath.c_str());
    std::remove(dstPath.c_str());
}

// Test: mmap and munmap
TEST_F(FileIoTest_561, MmapAndMunmap_561) {
    std::string content = "mmap test data 561";
    TempFile tmp("test_mmap_561.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    
    Exiv2::byte* mapped = fileIo.mmap(false);
    EXPECT_NE(mapped, nullptr);
    
    // Verify first few bytes match content
    for (size_t i = 0; i < content.size(); ++i) {
        EXPECT_EQ(mapped[i], static_cast<Exiv2::byte>(content[i]));
    }
    
    int result = fileIo.munmap();
    EXPECT_EQ(result, 0);
    fileIo.close();
}

// Test: Write zero bytes
TEST_F(FileIoTest_561, WriteZeroBytes_561) {
    std::string testPath = "test_write_zero_561.tmp";
    std::remove(testPath.c_str());
    
    Exiv2::FileIo fileIo(testPath);
    fileIo.open("w");
    
    const Exiv2::byte data[] = {0x01};
    size_t written = fileIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    fileIo.close();
    
    std::remove(testPath.c_str());
}

// Test: Multiple sequential reads
TEST_F(FileIoTest_561, MultipleSequentialReads_561) {
    std::string content = "ABCDEF";
    TempFile tmp("test_multi_read_561.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    
    Exiv2::byte buf1[3], buf2[3];
    size_t r1 = fileIo.read(buf1, 3);
    size_t r2 = fileIo.read(buf2, 3);
    
    EXPECT_EQ(r1, 3u);
    EXPECT_EQ(r2, 3u);
    EXPECT_EQ(buf1[0], 'A');
    EXPECT_EQ(buf1[1], 'B');
    EXPECT_EQ(buf1[2], 'C');
    EXPECT_EQ(buf2[0], 'D');
    EXPECT_EQ(buf2[1], 'E');
    EXPECT_EQ(buf2[2], 'F');
    
    fileIo.close();
}

// Test: Seek with negative offset from end
TEST_F(FileIoTest_561, SeekNegativeFromEnd_561) {
    std::string content = "0123456789";
    TempFile tmp("test_seek_neg_end_561.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    
    int result = fileIo.seek(-3, Exiv2::BasicIo::end);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(fileIo.tell(), content.size() - 3);
    
    int byte = fileIo.getb();
    EXPECT_EQ(byte, '7');
    
    fileIo.close();
}

// Test: populateFakeData doesn't crash
TEST_F(FileIoTest_561, PopulateFakeDataDoesNotCrash_561) {
    Exiv2::FileIo fileIo("fake_data_561.tmp");
    EXPECT_NO_THROW(fileIo.populateFakeData());
}

// Test: Large write and read back
TEST_F(FileIoTest_561, LargeWriteAndRead_561) {
    std::string testPath = "test_large_561.tmp";
    std::remove(testPath.c_str());
    
    const size_t dataSize = 100000;
    std::vector<Exiv2::byte> data(dataSize);
    for (size_t i = 0; i < dataSize; ++i) {
        data[i] = static_cast<Exiv2::byte>(i % 256);
    }
    
    Exiv2::FileIo fileIo(testPath);
    fileIo.open("w");
    size_t written = fileIo.write(data.data(), dataSize);
    EXPECT_EQ(written, dataSize);
    fileIo.close();
    
    fileIo.open();
    EXPECT_EQ(fileIo.size(), dataSize);
    
    std::vector<Exiv2::byte> readData(dataSize);
    size_t bytesRead = fileIo.read(readData.data(), dataSize);
    EXPECT_EQ(bytesRead, dataSize);
    
    for (size_t i = 0; i < dataSize; ++i) {
        EXPECT_EQ(readData[i], static_cast<Exiv2::byte>(i % 256)) << "Mismatch at index " << i;
    }
    
    fileIo.close();
    std::remove(testPath.c_str());
}

// Test: Open with "rb" mode
TEST_F(FileIoTest_561, OpenWithReadBinaryMode_561) {
    TempFile tmp("test_open_rb_561.tmp", "binary data");
    Exiv2::FileIo fileIo(tmp.path());
    int result = fileIo.open("rb");
    EXPECT_EQ(result, 0);
    EXPECT_TRUE(fileIo.isopen());
    fileIo.close();
}

// Test: Double open should work
TEST_F(FileIoTest_561, DoubleOpen_561) {
    TempFile tmp("test_double_open_561.tmp", "data");
    Exiv2::FileIo fileIo(tmp.path());
    
    int result1 = fileIo.open();
    EXPECT_EQ(result1, 0);
    EXPECT_TRUE(fileIo.isopen());
    
    // Opening again - behavior may vary, but should not crash
    int result2 = fileIo.open();
    EXPECT_EQ(result2, 0);
    EXPECT_TRUE(fileIo.isopen());
    
    fileIo.close();
}
