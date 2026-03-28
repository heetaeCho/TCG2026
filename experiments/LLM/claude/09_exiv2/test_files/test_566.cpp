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

class FileIoTest_566 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that constructor sets the path correctly
TEST_F(FileIoTest_566, ConstructorSetsPath_566) {
    std::string testPath = "test_constructor_566.tmp";
    Exiv2::FileIo fileIo(testPath);
    EXPECT_EQ(fileIo.path(), testPath);
}

// Test that a newly created FileIo is not open
TEST_F(FileIoTest_566, InitiallyNotOpen_566) {
    Exiv2::FileIo fileIo("nonexistent_file_566.tmp");
    EXPECT_FALSE(fileIo.isopen());
}

// Test that error() returns 0 when file is not open
TEST_F(FileIoTest_566, ErrorReturnsZeroWhenNotOpen_566) {
    Exiv2::FileIo fileIo("nonexistent_file_566.tmp");
    EXPECT_EQ(fileIo.error(), 0);
}

// Test opening a file that exists
TEST_F(FileIoTest_566, OpenExistingFile_566) {
    TempFile tmp("test_open_566.tmp", "hello");
    Exiv2::FileIo fileIo(tmp.path());
    EXPECT_EQ(fileIo.open(), 0);
    EXPECT_TRUE(fileIo.isopen());
    fileIo.close();
}

// Test opening a file with a specific mode
TEST_F(FileIoTest_566, OpenWithMode_566) {
    TempFile tmp("test_open_mode_566.tmp", "hello");
    Exiv2::FileIo fileIo(tmp.path());
    EXPECT_EQ(fileIo.open("rb"), 0);
    EXPECT_TRUE(fileIo.isopen());
    fileIo.close();
}

// Test opening a nonexistent file fails
TEST_F(FileIoTest_566, OpenNonexistentFileFails_566) {
    Exiv2::FileIo fileIo("this_file_does_not_exist_566.tmp");
    EXPECT_NE(fileIo.open(), 0);
    EXPECT_FALSE(fileIo.isopen());
}

// Test close on a file that was opened
TEST_F(FileIoTest_566, CloseAfterOpen_566) {
    TempFile tmp("test_close_566.tmp", "data");
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_TRUE(fileIo.isopen());
    EXPECT_EQ(fileIo.close(), 0);
    EXPECT_FALSE(fileIo.isopen());
}

// Test close on a file that was never opened
TEST_F(FileIoTest_566, CloseWithoutOpen_566) {
    Exiv2::FileIo fileIo("test_close_no_open_566.tmp");
    // Should not crash; close on unopened file
    EXPECT_EQ(fileIo.close(), 0);
}

// Test size() returns correct file size
TEST_F(FileIoTest_566, SizeReturnsCorrectValue_566) {
    std::string content = "Hello, World!";
    TempFile tmp("test_size_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_EQ(fileIo.size(), content.size());
    fileIo.close();
}

// Test tell() returns 0 after opening
TEST_F(FileIoTest_566, TellReturnsZeroAfterOpen_566) {
    TempFile tmp("test_tell_566.tmp", "data");
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_EQ(fileIo.tell(), 0u);
    fileIo.close();
}

// Test reading data from file
TEST_F(FileIoTest_566, ReadDataFromFile_566) {
    std::string content = "TestContent";
    TempFile tmp("test_read_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    Exiv2::DataBuf buf = fileIo.read(content.size());
    EXPECT_EQ(buf.size(), content.size());
    EXPECT_EQ(std::string(reinterpret_cast<const char*>(buf.c_data()), buf.size()), content);
    fileIo.close();
}

// Test reading into a buffer
TEST_F(FileIoTest_566, ReadIntoBuffer_566) {
    std::string content = "BufferRead";
    TempFile tmp("test_read_buf_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    std::vector<Exiv2::byte> buffer(content.size());
    size_t bytesRead = fileIo.read(buffer.data(), buffer.size());
    EXPECT_EQ(bytesRead, content.size());
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buffer.data()), bytesRead), content);
    fileIo.close();
}

// Test reading more bytes than available
TEST_F(FileIoTest_566, ReadMoreThanAvailable_566) {
    std::string content = "Short";
    TempFile tmp("test_read_more_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    std::vector<Exiv2::byte> buffer(100);
    size_t bytesRead = fileIo.read(buffer.data(), buffer.size());
    EXPECT_EQ(bytesRead, content.size());
    fileIo.close();
}

// Test getb returns correct byte
TEST_F(FileIoTest_566, GetbReturnsCorrectByte_566) {
    std::string content = "AB";
    TempFile tmp("test_getb_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    int b = fileIo.getb();
    EXPECT_EQ(b, 'A');
    b = fileIo.getb();
    EXPECT_EQ(b, 'B');
    fileIo.close();
}

// Test getb returns EOF at end of file
TEST_F(FileIoTest_566, GetbReturnsEofAtEnd_566) {
    std::string content = "X";
    TempFile tmp("test_getb_eof_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    fileIo.getb(); // consume 'X'
    int b = fileIo.getb();
    EXPECT_EQ(b, EOF);
    fileIo.close();
}

// Test write data to file
TEST_F(FileIoTest_566, WriteDataToFile_566) {
    std::string filePath = "test_write_566.tmp";
    {
        // Create the file first
        std::ofstream ofs(filePath);
        ofs.close();
    }
    Exiv2::FileIo fileIo(filePath);
    fileIo.open("wb");
    std::string data = "WriteTest";
    size_t written = fileIo.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    EXPECT_EQ(written, data.size());
    fileIo.close();

    // Verify by reading back
    Exiv2::FileIo readIo(filePath);
    readIo.open();
    Exiv2::DataBuf buf = readIo.read(data.size());
    EXPECT_EQ(buf.size(), data.size());
    EXPECT_EQ(std::string(reinterpret_cast<const char*>(buf.c_data()), buf.size()), data);
    readIo.close();
    std::remove(filePath.c_str());
}

// Test putb writes a single byte
TEST_F(FileIoTest_566, PutbWritesByte_566) {
    std::string filePath = "test_putb_566.tmp";
    {
        std::ofstream ofs(filePath);
        ofs.close();
    }
    Exiv2::FileIo fileIo(filePath);
    fileIo.open("wb");
    int result = fileIo.putb('Z');
    EXPECT_EQ(result, 'Z');
    fileIo.close();

    // Verify
    Exiv2::FileIo readIo(filePath);
    readIo.open();
    int b = readIo.getb();
    EXPECT_EQ(b, 'Z');
    readIo.close();
    std::remove(filePath.c_str());
}

// Test seek from beginning
TEST_F(FileIoTest_566, SeekFromBeginning_566) {
    std::string content = "0123456789";
    TempFile tmp("test_seek_beg_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_EQ(fileIo.seek(5, Exiv2::BasicIo::beg), 0);
    EXPECT_EQ(fileIo.tell(), 5u);
    int b = fileIo.getb();
    EXPECT_EQ(b, '5');
    fileIo.close();
}

// Test seek from current position
TEST_F(FileIoTest_566, SeekFromCurrent_566) {
    std::string content = "0123456789";
    TempFile tmp("test_seek_cur_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    fileIo.seek(3, Exiv2::BasicIo::beg);
    EXPECT_EQ(fileIo.seek(2, Exiv2::BasicIo::cur), 0);
    EXPECT_EQ(fileIo.tell(), 5u);
    fileIo.close();
}

// Test seek from end
TEST_F(FileIoTest_566, SeekFromEnd_566) {
    std::string content = "0123456789";
    TempFile tmp("test_seek_end_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_EQ(fileIo.seek(-3, Exiv2::BasicIo::end), 0);
    EXPECT_EQ(fileIo.tell(), 7u);
    fileIo.close();
}

// Test eof() after reading all data
TEST_F(FileIoTest_566, EofAfterReadAll_566) {
    std::string content = "AB";
    TempFile tmp("test_eof_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    fileIo.read(100); // Read more than available
    EXPECT_TRUE(fileIo.eof());
    fileIo.close();
}

// Test eof() before reaching end
TEST_F(FileIoTest_566, NotEofBeforeEnd_566) {
    std::string content = "ABCDEFGH";
    TempFile tmp("test_not_eof_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    fileIo.read(2);
    EXPECT_FALSE(fileIo.eof());
    fileIo.close();
}

// Test error() returns 0 on a healthy open file
TEST_F(FileIoTest_566, ErrorReturnsZeroOnHealthyFile_566) {
    TempFile tmp("test_error_healthy_566.tmp", "data");
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_EQ(fileIo.error(), 0);
    fileIo.close();
}

// Test setPath changes the path
TEST_F(FileIoTest_566, SetPathChangesPath_566) {
    Exiv2::FileIo fileIo("original_path_566.tmp");
    EXPECT_EQ(fileIo.path(), "original_path_566.tmp");
    fileIo.setPath("new_path_566.tmp");
    EXPECT_EQ(fileIo.path(), "new_path_566.tmp");
}

// Test write from another BasicIo source
TEST_F(FileIoTest_566, WriteFromBasicIoSource_566) {
    std::string content = "SourceContent";
    TempFile srcTmp("test_write_src_566.tmp", content);
    std::string destPath = "test_write_dst_566.tmp";
    {
        std::ofstream ofs(destPath);
        ofs.close();
    }

    Exiv2::FileIo srcIo(srcTmp.path());
    srcIo.open();

    Exiv2::FileIo dstIo(destPath);
    dstIo.open("wb");
    size_t written = dstIo.write(srcIo);
    EXPECT_EQ(written, content.size());
    dstIo.close();
    srcIo.close();

    // Verify
    Exiv2::FileIo verifyIo(destPath);
    verifyIo.open();
    Exiv2::DataBuf buf = verifyIo.read(content.size());
    EXPECT_EQ(buf.size(), content.size());
    EXPECT_EQ(std::string(reinterpret_cast<const char*>(buf.c_data()), buf.size()), content);
    verifyIo.close();
    std::remove(destPath.c_str());
}

// Test reading from an empty file
TEST_F(FileIoTest_566, ReadFromEmptyFile_566) {
    TempFile tmp("test_empty_566.tmp", "");
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_EQ(fileIo.size(), 0u);
    Exiv2::DataBuf buf = fileIo.read(10);
    EXPECT_EQ(buf.size(), 0u);
    fileIo.close();
}

// Test getb on empty file returns EOF
TEST_F(FileIoTest_566, GetbOnEmptyFileReturnsEof_566) {
    TempFile tmp("test_getb_empty_566.tmp", "");
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    int b = fileIo.getb();
    EXPECT_EQ(b, EOF);
    fileIo.close();
}

// Test seek to position 0 on empty file
TEST_F(FileIoTest_566, SeekOnEmptyFile_566) {
    TempFile tmp("test_seek_empty_566.tmp", "");
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_EQ(fileIo.seek(0, Exiv2::BasicIo::beg), 0);
    EXPECT_EQ(fileIo.tell(), 0u);
    fileIo.close();
}

// Test reading zero bytes
TEST_F(FileIoTest_566, ReadZeroBytes_566) {
    TempFile tmp("test_read_zero_566.tmp", "SomeContent");
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    Exiv2::DataBuf buf = fileIo.read(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_EQ(fileIo.tell(), 0u);
    fileIo.close();
}

// Test writing zero bytes
TEST_F(FileIoTest_566, WriteZeroBytes_566) {
    std::string filePath = "test_write_zero_566.tmp";
    {
        std::ofstream ofs(filePath);
        ofs.close();
    }
    Exiv2::FileIo fileIo(filePath);
    fileIo.open("wb");
    Exiv2::byte dummy = 0;
    size_t written = fileIo.write(&dummy, 0);
    EXPECT_EQ(written, 0u);
    fileIo.close();
    std::remove(filePath.c_str());
}

// Test multiple sequential reads advance position correctly
TEST_F(FileIoTest_566, SequentialReadsAdvancePosition_566) {
    std::string content = "ABCDEFGHIJ";
    TempFile tmp("test_seq_read_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();

    std::vector<Exiv2::byte> buf(3);
    fileIo.read(buf.data(), 3);
    EXPECT_EQ(fileIo.tell(), 3u);

    fileIo.read(buf.data(), 3);
    EXPECT_EQ(fileIo.tell(), 6u);

    fileIo.read(buf.data(), 3);
    EXPECT_EQ(fileIo.tell(), 9u);

    fileIo.close();
}

// Test mmap and munmap
TEST_F(FileIoTest_566, MmapAndMunmap_566) {
    std::string content = "MmapTest";
    TempFile tmp("test_mmap_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();

    Exiv2::byte* mapped = fileIo.mmap(false);
    ASSERT_NE(mapped, nullptr);
    // Verify content through mmap
    EXPECT_EQ(std::string(reinterpret_cast<char*>(mapped), content.size()), content);

    EXPECT_EQ(fileIo.munmap(), 0);
    fileIo.close();
}

// Test transfer from one FileIo to another
TEST_F(FileIoTest_566, TransferFromAnotherFileIo_566) {
    std::string srcContent = "TransferData";
    TempFile srcTmp("test_transfer_src_566.tmp", srcContent);
    std::string dstPath = "test_transfer_dst_566.tmp";
    {
        std::ofstream ofs(dstPath);
        ofs.close();
    }

    Exiv2::FileIo srcIo(srcTmp.path());
    Exiv2::FileIo dstIo(dstPath);

    dstIo.transfer(srcIo);

    dstIo.open();
    Exiv2::DataBuf buf = dstIo.read(srcContent.size());
    EXPECT_EQ(buf.size(), srcContent.size());
    EXPECT_EQ(std::string(reinterpret_cast<const char*>(buf.c_data()), buf.size()), srcContent);
    dstIo.close();
    std::remove(dstPath.c_str());
}

// Test path() returns noexcept
TEST_F(FileIoTest_566, PathIsNoexcept_566) {
    Exiv2::FileIo fileIo("some_path_566.tmp");
    EXPECT_NO_THROW(fileIo.path());
}

// Test open and close multiple times
TEST_F(FileIoTest_566, MultipleOpenClose_566) {
    TempFile tmp("test_multi_oc_566.tmp", "data");
    Exiv2::FileIo fileIo(tmp.path());

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(fileIo.open(), 0);
        EXPECT_TRUE(fileIo.isopen());
        EXPECT_EQ(fileIo.close(), 0);
        EXPECT_FALSE(fileIo.isopen());
    }
}

// Test error after close
TEST_F(FileIoTest_566, ErrorAfterClose_566) {
    TempFile tmp("test_error_close_566.tmp", "data");
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    fileIo.close();
    // After close, fp_ should be null, so error() returns 0
    EXPECT_EQ(fileIo.error(), 0);
}

// Test size of larger file
TEST_F(FileIoTest_566, SizeLargerFile_566) {
    std::string content(10000, 'X');
    TempFile tmp("test_large_566.tmp", content);
    Exiv2::FileIo fileIo(tmp.path());
    fileIo.open();
    EXPECT_EQ(fileIo.size(), 10000u);
    fileIo.close();
}
