#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <string>
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

}  // namespace

class FileIoTest_555 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that path() returns the path given at construction
TEST_F(FileIoTest_555, PathReturnsConstructionPath_555) {
    std::string testPath = "test_path_file_555.tmp";
    Exiv2::FileIo io(testPath);
    EXPECT_EQ(io.path(), testPath);
}

// Test open and close basic flow
TEST_F(FileIoTest_555, OpenAndCloseSucceed_555) {
    TempFile tmp("test_open_close_555.tmp", "hello");
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    EXPECT_TRUE(io.isopen());
    EXPECT_EQ(io.close(), 0);
    EXPECT_FALSE(io.isopen());
}

// Test open with explicit mode
TEST_F(FileIoTest_555, OpenWithModeSucceeds_555) {
    TempFile tmp("test_open_mode_555.tmp", "data");
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open("rb"), 0);
    EXPECT_TRUE(io.isopen());
    EXPECT_EQ(io.close(), 0);
}

// Test that isopen returns false before opening
TEST_F(FileIoTest_555, IsOpenReturnsFalseBeforeOpen_555) {
    Exiv2::FileIo io("nonexistent_file_555.tmp");
    EXPECT_FALSE(io.isopen());
}

// Test open on nonexistent file returns error
TEST_F(FileIoTest_555, OpenNonexistentFileFails_555) {
    std::remove("nonexistent_for_test_555.tmp");
    Exiv2::FileIo io("nonexistent_for_test_555.tmp");
    // Default open should fail for nonexistent file
    EXPECT_NE(io.open(), 0);
    EXPECT_FALSE(io.isopen());
}

// Test size() returns correct size
TEST_F(FileIoTest_555, SizeReturnsCorrectValue_555) {
    std::string content = "Hello, World!";
    TempFile tmp("test_size_555.tmp", content);
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    EXPECT_EQ(io.size(), content.size());
    io.close();
}

// Test tell() starts at 0
TEST_F(FileIoTest_555, TellStartsAtZero_555) {
    TempFile tmp("test_tell_555.tmp", "abcdef");
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    EXPECT_EQ(io.tell(), 0u);
    io.close();
}

// Test read returns correct data
TEST_F(FileIoTest_555, ReadReturnsCorrectData_555) {
    std::string content = "TestData123";
    TempFile tmp("test_read_555.tmp", content);
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    Exiv2::DataBuf buf = io.read(content.size());
    EXPECT_EQ(buf.size(), content.size());
    EXPECT_EQ(std::string(reinterpret_cast<const char*>(buf.data()), buf.size()), content);
    io.close();
}

// Test read into buffer
TEST_F(FileIoTest_555, ReadIntoBufferReturnsCorrectCount_555) {
    std::string content = "ABCDEFGHIJ";
    TempFile tmp("test_read_buf_555.tmp", content);
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    Exiv2::byte buf[20] = {};
    size_t n = io.read(buf, 5);
    EXPECT_EQ(n, 5u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), 5), "ABCDE");
    io.close();
}

// Test getb returns bytes in order
TEST_F(FileIoTest_555, GetbReturnsBytesSequentially_555) {
    std::string content = "XY";
    TempFile tmp("test_getb_555.tmp", content);
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    EXPECT_EQ(io.getb(), 'X');
    EXPECT_EQ(io.getb(), 'Y');
    io.close();
}

// Test getb returns EOF at end of file
TEST_F(FileIoTest_555, GetbReturnsEofAtEnd_555) {
    std::string content = "A";
    TempFile tmp("test_getb_eof_555.tmp", content);
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    io.getb();  // consume 'A'
    int result = io.getb();
    EXPECT_EQ(result, EOF);
    io.close();
}

// Test putb writes a byte
TEST_F(FileIoTest_555, PutbWritesByte_555) {
    std::string filePath = "test_putb_555.tmp";
    {
        Exiv2::FileIo io(filePath);
        EXPECT_EQ(io.open("w+b"), 0);
        EXPECT_NE(io.putb(0x42), EOF);
        io.close();
    }
    // Verify the byte was written
    {
        Exiv2::FileIo io(filePath);
        EXPECT_EQ(io.open(), 0);
        EXPECT_EQ(io.getb(), 0x42);
        io.close();
    }
    std::remove(filePath.c_str());
}

// Test putb returns EOF when file is not open
TEST_F(FileIoTest_555, PutbReturnsEofWhenNotOpen_555) {
    Exiv2::FileIo io("test_putb_notopen_555.tmp");
    // Not opened, should return EOF
    int result = io.putb(0x00);
    EXPECT_EQ(result, EOF);
}

// Test putb with various byte values including boundary
TEST_F(FileIoTest_555, PutbBoundaryValues_555) {
    std::string filePath = "test_putb_boundary_555.tmp";
    {
        Exiv2::FileIo io(filePath);
        EXPECT_EQ(io.open("w+b"), 0);
        EXPECT_NE(io.putb(0x00), EOF);
        EXPECT_NE(io.putb(0xFF), EOF);
        EXPECT_NE(io.putb(0x7F), EOF);
        EXPECT_NE(io.putb(0x80), EOF);
        io.close();
    }
    // Verify
    {
        Exiv2::FileIo io(filePath);
        EXPECT_EQ(io.open(), 0);
        EXPECT_EQ(io.getb(), 0x00);
        EXPECT_EQ(io.getb(), 0xFF);
        EXPECT_EQ(io.getb(), 0x7F);
        EXPECT_EQ(io.getb(), 0x80);
        io.close();
    }
    std::remove(filePath.c_str());
}

// Test write with byte data
TEST_F(FileIoTest_555, WriteByteDataSucceeds_555) {
    std::string filePath = "test_write_555.tmp";
    {
        Exiv2::FileIo io(filePath);
        EXPECT_EQ(io.open("w+b"), 0);
        Exiv2::byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
        size_t written = io.write(data, sizeof(data));
        EXPECT_EQ(written, sizeof(data));
        io.close();
    }
    // Verify
    {
        Exiv2::FileIo io(filePath);
        EXPECT_EQ(io.open(), 0);
        EXPECT_EQ(io.size(), 5u);
        io.close();
    }
    std::remove(filePath.c_str());
}

// Test seek to beginning
TEST_F(FileIoTest_555, SeekToBeginning_555) {
    TempFile tmp("test_seek_beg_555.tmp", "ABCDEF");
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    io.read(3);  // advance to position 3
    EXPECT_EQ(io.tell(), 3u);
    EXPECT_EQ(io.seek(0, Exiv2::BasicIo::beg), 0);
    EXPECT_EQ(io.tell(), 0u);
    io.close();
}

// Test seek from current position
TEST_F(FileIoTest_555, SeekFromCurrent_555) {
    TempFile tmp("test_seek_cur_555.tmp", "ABCDEFGHIJ");
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    io.read(2);  // position at 2
    EXPECT_EQ(io.seek(3, Exiv2::BasicIo::cur), 0);
    EXPECT_EQ(io.tell(), 5u);
    EXPECT_EQ(io.getb(), 'F');
    io.close();
}

// Test seek from end
TEST_F(FileIoTest_555, SeekFromEnd_555) {
    std::string content = "ABCDEFGHIJ";
    TempFile tmp("test_seek_end_555.tmp", content);
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    EXPECT_EQ(io.seek(-1, Exiv2::BasicIo::end), 0);
    EXPECT_EQ(io.getb(), 'J');
    io.close();
}

// Test eof
TEST_F(FileIoTest_555, EofAfterReadingAll_555) {
    TempFile tmp("test_eof_555.tmp", "AB");
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    EXPECT_FALSE(io.eof());
    io.getb();
    io.getb();
    io.getb();  // This should trigger EOF
    EXPECT_TRUE(io.eof());
    io.close();
}

// Test error returns 0 normally
TEST_F(FileIoTest_555, ErrorReturnsZeroNormally_555) {
    TempFile tmp("test_error_555.tmp", "data");
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    EXPECT_EQ(io.error(), 0);
    io.close();
}

// Test write from BasicIo source
TEST_F(FileIoTest_555, WriteFromBasicIoSource_555) {
    std::string srcContent = "SourceContent";
    TempFile srcFile("test_write_src_555.tmp", srcContent);
    std::string dstPath = "test_write_dst_555.tmp";
    
    {
        Exiv2::FileIo src(srcFile.path());
        Exiv2::FileIo dst(dstPath);
        EXPECT_EQ(src.open(), 0);
        EXPECT_EQ(dst.open("w+b"), 0);
        size_t written = dst.write(src);
        EXPECT_EQ(written, srcContent.size());
        dst.close();
        src.close();
    }
    
    // Verify
    {
        Exiv2::FileIo dst(dstPath);
        EXPECT_EQ(dst.open(), 0);
        EXPECT_EQ(dst.size(), srcContent.size());
        dst.close();
    }
    std::remove(dstPath.c_str());
}

// Test close on already closed file
TEST_F(FileIoTest_555, CloseAlreadyClosed_555) {
    TempFile tmp("test_close_twice_555.tmp", "data");
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    EXPECT_EQ(io.close(), 0);
    // Closing again should not crash; behavior may vary
    int result = io.close();
    (void)result;  // Just ensure no crash
}

// Test setPath changes the path
TEST_F(FileIoTest_555, SetPathChangesPath_555) {
    Exiv2::FileIo io("original_555.tmp");
    EXPECT_EQ(io.path(), "original_555.tmp");
    io.setPath("new_path_555.tmp");
    EXPECT_EQ(io.path(), "new_path_555.tmp");
}

// Test size of empty file
TEST_F(FileIoTest_555, SizeOfEmptyFile_555) {
    TempFile tmp("test_empty_555.tmp", "");
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    EXPECT_EQ(io.size(), 0u);
    io.close();
}

// Test read zero bytes
TEST_F(FileIoTest_555, ReadZeroBytes_555) {
    TempFile tmp("test_read_zero_555.tmp", "data");
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    Exiv2::DataBuf buf = io.read(0);
    EXPECT_EQ(buf.size(), 0u);
    EXPECT_EQ(io.tell(), 0u);
    io.close();
}

// Test write zero bytes
TEST_F(FileIoTest_555, WriteZeroBytes_555) {
    std::string filePath = "test_write_zero_555.tmp";
    {
        Exiv2::FileIo io(filePath);
        EXPECT_EQ(io.open("w+b"), 0);
        Exiv2::byte data[] = {0x01};
        size_t written = io.write(data, 0);
        EXPECT_EQ(written, 0u);
        io.close();
    }
    std::remove(filePath.c_str());
}

// Test reading more than file size
TEST_F(FileIoTest_555, ReadMoreThanFileSize_555) {
    std::string content = "Short";
    TempFile tmp("test_read_more_555.tmp", content);
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    Exiv2::DataBuf buf = io.read(1000);
    EXPECT_EQ(buf.size(), content.size());
    io.close();
}

// Test multiple putb calls in sequence
TEST_F(FileIoTest_555, MultiplePutbCalls_555) {
    std::string filePath = "test_multi_putb_555.tmp";
    {
        Exiv2::FileIo io(filePath);
        EXPECT_EQ(io.open("w+b"), 0);
        for (int i = 0; i < 256; i++) {
            EXPECT_NE(io.putb(static_cast<Exiv2::byte>(i)), EOF);
        }
        io.close();
    }
    // Verify
    {
        Exiv2::FileIo io(filePath);
        EXPECT_EQ(io.open(), 0);
        EXPECT_EQ(io.size(), 256u);
        for (int i = 0; i < 256; i++) {
            EXPECT_EQ(io.getb(), i);
        }
        io.close();
    }
    std::remove(filePath.c_str());
}

// Test seek and then putb
TEST_F(FileIoTest_555, SeekThenPutb_555) {
    std::string filePath = "test_seek_putb_555.tmp";
    {
        Exiv2::FileIo io(filePath);
        EXPECT_EQ(io.open("w+b"), 0);
        Exiv2::byte data[] = {'A', 'B', 'C', 'D', 'E'};
        io.write(data, 5);
        EXPECT_EQ(io.seek(2, Exiv2::BasicIo::beg), 0);
        EXPECT_NE(io.putb('Z'), EOF);
        io.close();
    }
    // Verify
    {
        Exiv2::FileIo io(filePath);
        EXPECT_EQ(io.open(), 0);
        EXPECT_EQ(io.getb(), 'A');
        EXPECT_EQ(io.getb(), 'B');
        EXPECT_EQ(io.getb(), 'Z');
        EXPECT_EQ(io.getb(), 'D');
        EXPECT_EQ(io.getb(), 'E');
        io.close();
    }
    std::remove(filePath.c_str());
}

// Test mmap and munmap
TEST_F(FileIoTest_555, MmapAndMunmap_555) {
    std::string content = "MmapTest";
    TempFile tmp("test_mmap_555.tmp", content);
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    Exiv2::byte* mapped = io.mmap(false);
    ASSERT_NE(mapped, nullptr);
    // Verify mapped data matches
    for (size_t i = 0; i < content.size(); i++) {
        EXPECT_EQ(mapped[i], static_cast<Exiv2::byte>(content[i]));
    }
    EXPECT_EQ(io.munmap(), 0);
    io.close();
}

// Test tell after various operations
TEST_F(FileIoTest_555, TellAfterOperations_555) {
    std::string content = "0123456789";
    TempFile tmp("test_tell_ops_555.tmp", content);
    Exiv2::FileIo io(tmp.path());
    EXPECT_EQ(io.open(), 0);
    EXPECT_EQ(io.tell(), 0u);
    
    io.getb();
    EXPECT_EQ(io.tell(), 1u);
    
    Exiv2::byte buf[3];
    io.read(buf, 3);
    EXPECT_EQ(io.tell(), 4u);
    
    io.seek(0, Exiv2::BasicIo::beg);
    EXPECT_EQ(io.tell(), 0u);
    
    io.seek(0, Exiv2::BasicIo::end);
    EXPECT_EQ(io.tell(), content.size());
    
    io.close();
}
