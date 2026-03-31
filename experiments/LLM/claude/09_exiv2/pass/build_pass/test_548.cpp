#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>

namespace {

// Helper to create a temporary file with content
std::string createTempFile(const std::string& prefix, const std::string& content = "") {
    std::string path = prefix + "_test_548.tmp";
    if (!content.empty()) {
        std::ofstream ofs(path, std::ios::binary);
        ofs.write(content.data(), content.size());
        ofs.close();
    }
    return path;
}

void removeTempFile(const std::string& path) {
    std::remove(path.c_str());
}

class FileIoTest_548 : public ::testing::Test {
protected:
    std::vector<std::string> tempFiles;

    std::string makeTempFile(const std::string& prefix, const std::string& content = "") {
        std::string path = createTempFile(prefix, content);
        tempFiles.push_back(path);
        return path;
    }

    void TearDown() override {
        for (auto& f : tempFiles) {
            removeTempFile(f);
        }
    }
};

// Test: Constructor sets the path correctly
TEST_F(FileIoTest_548, ConstructorSetsPath_548) {
    std::string path = "/some/test/path.jpg";
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(fileIo.path(), path);
}

// Test: path() returns the correct path after construction
TEST_F(FileIoTest_548, PathReturnsCorrectValue_548) {
    std::string path = makeTempFile("path_test", "hello");
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(fileIo.path(), path);
}

// Test: isopen() returns false before open
TEST_F(FileIoTest_548, IsOpenReturnsFalseBeforeOpen_548) {
    std::string path = makeTempFile("isopen_test", "data");
    Exiv2::FileIo fileIo(path);
    EXPECT_FALSE(fileIo.isopen());
}

// Test: open() on existing file succeeds
TEST_F(FileIoTest_548, OpenExistingFileSucceeds_548) {
    std::string path = makeTempFile("open_test", "test content");
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(0, fileIo.open());
    EXPECT_TRUE(fileIo.isopen());
    fileIo.close();
}

// Test: open() on non-existing file fails
TEST_F(FileIoTest_548, OpenNonExistingFileFails_548) {
    Exiv2::FileIo fileIo("/nonexistent/path/to/file_548.tmp");
    EXPECT_NE(0, fileIo.open());
    EXPECT_FALSE(fileIo.isopen());
}

// Test: open with mode "r" on existing file succeeds
TEST_F(FileIoTest_548, OpenWithModeReadSucceeds_548) {
    std::string path = makeTempFile("open_mode_r", "content");
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(0, fileIo.open("r"));
    EXPECT_TRUE(fileIo.isopen());
    fileIo.close();
}

// Test: close() on an open file
TEST_F(FileIoTest_548, CloseOpenFile_548) {
    std::string path = makeTempFile("close_test", "data");
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    EXPECT_TRUE(fileIo.isopen());
    EXPECT_EQ(0, fileIo.close());
    EXPECT_FALSE(fileIo.isopen());
}

// Test: close() on already closed file doesn't fail
TEST_F(FileIoTest_548, CloseAlreadyClosedFile_548) {
    std::string path = makeTempFile("close_closed", "data");
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(0, fileIo.close());
}

// Test: size() returns correct file size
TEST_F(FileIoTest_548, SizeReturnsCorrectValue_548) {
    std::string content = "Hello, World!";
    std::string path = makeTempFile("size_test", content);
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(content.size(), fileIo.size());
}

// Test: size() on empty file
TEST_F(FileIoTest_548, SizeOfEmptyFile_548) {
    std::string path = makeTempFile("size_empty", "");
    // Create empty file
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.close();
    }
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(0u, fileIo.size());
}

// Test: read data from file
TEST_F(FileIoTest_548, ReadDataFromFile_548) {
    std::string content = "Test data for reading";
    std::string path = makeTempFile("read_test", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();

    Exiv2::byte buf[64] = {0};
    size_t bytesRead = fileIo.read(buf, content.size());
    EXPECT_EQ(content.size(), bytesRead);
    EXPECT_EQ(0, std::memcmp(buf, content.data(), content.size()));
    fileIo.close();
}

// Test: read() with DataBuf overload
TEST_F(FileIoTest_548, ReadDataBuf_548) {
    std::string content = "DataBuf read test";
    std::string path = makeTempFile("readbuf_test", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();

    Exiv2::DataBuf buf = fileIo.read(content.size());
    EXPECT_EQ(content.size(), buf.size());
    EXPECT_EQ(0, std::memcmp(buf.data(), content.data(), content.size()));
    fileIo.close();
}

// Test: read more bytes than available
TEST_F(FileIoTest_548, ReadMoreThanAvailable_548) {
    std::string content = "short";
    std::string path = makeTempFile("read_more", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();

    Exiv2::byte buf[100] = {0};
    size_t bytesRead = fileIo.read(buf, 100);
    EXPECT_EQ(content.size(), bytesRead);
    fileIo.close();
}

// Test: write data to file
TEST_F(FileIoTest_548, WriteDataToFile_548) {
    std::string path = makeTempFile("write_test", "");
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.close();
    }
    Exiv2::FileIo fileIo(path);
    fileIo.open("w");

    const std::string data = "Written data";
    size_t written = fileIo.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    EXPECT_EQ(data.size(), written);
    fileIo.close();

    // Verify by reading back
    Exiv2::FileIo fileIo2(path);
    fileIo2.open();
    Exiv2::byte buf[64] = {0};
    size_t bytesRead = fileIo2.read(buf, 64);
    EXPECT_EQ(data.size(), bytesRead);
    EXPECT_EQ(0, std::memcmp(buf, data.data(), data.size()));
    fileIo2.close();
}

// Test: write from BasicIo source
TEST_F(FileIoTest_548, WriteFromBasicIoSource_548) {
    std::string srcContent = "Source file content";
    std::string srcPath = makeTempFile("write_src", srcContent);
    std::string dstPath = makeTempFile("write_dst", "");
    {
        std::ofstream ofs(dstPath, std::ios::binary);
        ofs.close();
    }

    Exiv2::FileIo srcIo(srcPath);
    srcIo.open();

    Exiv2::FileIo dstIo(dstPath);
    dstIo.open("w");

    size_t written = dstIo.write(srcIo);
    EXPECT_EQ(srcContent.size(), written);

    srcIo.close();
    dstIo.close();
}

// Test: putb writes a single byte
TEST_F(FileIoTest_548, PutbWritesSingleByte_548) {
    std::string path = makeTempFile("putb_test", "");
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.close();
    }
    Exiv2::FileIo fileIo(path);
    fileIo.open("w");

    int result = fileIo.putb(0x42);
    EXPECT_EQ(0x42, result);
    fileIo.close();

    // Verify
    Exiv2::FileIo fileIo2(path);
    fileIo2.open();
    int byte = fileIo2.getb();
    EXPECT_EQ(0x42, byte);
    fileIo2.close();
}

// Test: getb reads a single byte
TEST_F(FileIoTest_548, GetbReadsSingleByte_548) {
    std::string path = makeTempFile("getb_test", "A");
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    int byte = fileIo.getb();
    EXPECT_EQ('A', byte);
    fileIo.close();
}

// Test: getb at EOF returns EOF
TEST_F(FileIoTest_548, GetbAtEofReturnsEof_548) {
    std::string path = makeTempFile("getb_eof", "");
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.close();
    }
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    int byte = fileIo.getb();
    EXPECT_EQ(EOF, byte);
    fileIo.close();
}

// Test: tell() returns current position
TEST_F(FileIoTest_548, TellReturnsCurrentPosition_548) {
    std::string content = "0123456789";
    std::string path = makeTempFile("tell_test", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    EXPECT_EQ(0u, fileIo.tell());

    Exiv2::byte buf[5];
    fileIo.read(buf, 5);
    EXPECT_EQ(5u, fileIo.tell());
    fileIo.close();
}

// Test: seek from beginning
TEST_F(FileIoTest_548, SeekFromBeginning_548) {
    std::string content = "ABCDEFGHIJ";
    std::string path = makeTempFile("seek_beg", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();

    EXPECT_EQ(0, fileIo.seek(5, Exiv2::BasicIo::beg));
    EXPECT_EQ(5u, fileIo.tell());
    int byte = fileIo.getb();
    EXPECT_EQ('F', byte);
    fileIo.close();
}

// Test: seek from current position
TEST_F(FileIoTest_548, SeekFromCurrent_548) {
    std::string content = "ABCDEFGHIJ";
    std::string path = makeTempFile("seek_cur", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();

    fileIo.seek(3, Exiv2::BasicIo::beg);
    EXPECT_EQ(0, fileIo.seek(2, Exiv2::BasicIo::cur));
    EXPECT_EQ(5u, fileIo.tell());
    fileIo.close();
}

// Test: seek from end
TEST_F(FileIoTest_548, SeekFromEnd_548) {
    std::string content = "ABCDEFGHIJ";
    std::string path = makeTempFile("seek_end", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();

    EXPECT_EQ(0, fileIo.seek(-3, Exiv2::BasicIo::end));
    EXPECT_EQ(content.size() - 3, fileIo.tell());
    int byte = fileIo.getb();
    EXPECT_EQ('H', byte);
    fileIo.close();
}

// Test: eof() returns true after reading past end
TEST_F(FileIoTest_548, EofAfterReadPastEnd_548) {
    std::string content = "AB";
    std::string path = makeTempFile("eof_test", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();

    Exiv2::byte buf[10];
    fileIo.read(buf, 10);
    EXPECT_TRUE(fileIo.eof());
    fileIo.close();
}

// Test: eof() returns false at beginning
TEST_F(FileIoTest_548, EofFalseAtBeginning_548) {
    std::string content = "Some data";
    std::string path = makeTempFile("eof_false", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    EXPECT_FALSE(fileIo.eof());
    fileIo.close();
}

// Test: error() returns 0 on normal operation
TEST_F(FileIoTest_548, ErrorReturnsZeroNormally_548) {
    std::string content = "data";
    std::string path = makeTempFile("error_test", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    EXPECT_EQ(0, fileIo.error());
    fileIo.close();
}

// Test: setPath changes the path
TEST_F(FileIoTest_548, SetPathChangesPath_548) {
    std::string path1 = "/original/path.jpg";
    std::string path2 = "/new/path.jpg";
    Exiv2::FileIo fileIo(path1);
    EXPECT_EQ(path1, fileIo.path());
    fileIo.setPath(path2);
    EXPECT_EQ(path2, fileIo.path());
}

// Test: transfer from another FileIo
TEST_F(FileIoTest_548, TransferFromAnotherFileIo_548) {
    std::string srcContent = "Transfer this content";
    std::string srcPath = makeTempFile("transfer_src", srcContent);
    std::string dstPath = makeTempFile("transfer_dst", "old content");

    Exiv2::FileIo srcIo(srcPath);
    Exiv2::FileIo dstIo(dstPath);

    dstIo.transfer(srcIo);

    // After transfer, dstIo should have the source content
    dstIo.open();
    Exiv2::byte buf[64] = {0};
    size_t bytesRead = dstIo.read(buf, 64);
    EXPECT_EQ(srcContent.size(), bytesRead);
    EXPECT_EQ(0, std::memcmp(buf, srcContent.data(), srcContent.size()));
    dstIo.close();
}

// Test: mmap and munmap
TEST_F(FileIoTest_548, MmapAndMunmap_548) {
    std::string content = "Memory mapped content";
    std::string path = makeTempFile("mmap_test", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();

    Exiv2::byte* data = fileIo.mmap(false);
    ASSERT_NE(nullptr, data);
    EXPECT_EQ(0, std::memcmp(data, content.data(), content.size()));

    EXPECT_EQ(0, fileIo.munmap());
    fileIo.close();
}

// Test: multiple open/close cycles
TEST_F(FileIoTest_548, MultipleOpenCloseCycles_548) {
    std::string content = "cycle test";
    std::string path = makeTempFile("cycle_test", content);
    Exiv2::FileIo fileIo(path);

    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(0, fileIo.open());
        EXPECT_TRUE(fileIo.isopen());
        EXPECT_EQ(0, fileIo.close());
        EXPECT_FALSE(fileIo.isopen());
    }
}

// Test: write zero bytes
TEST_F(FileIoTest_548, WriteZeroBytes_548) {
    std::string path = makeTempFile("write_zero", "");
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.close();
    }
    Exiv2::FileIo fileIo(path);
    fileIo.open("w");

    const Exiv2::byte data[] = {0};
    size_t written = fileIo.write(data, 0);
    EXPECT_EQ(0u, written);
    fileIo.close();
}

// Test: read zero bytes
TEST_F(FileIoTest_548, ReadZeroBytes_548) {
    std::string content = "some content";
    std::string path = makeTempFile("read_zero", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();

    Exiv2::byte buf[10];
    size_t bytesRead = fileIo.read(buf, 0);
    EXPECT_EQ(0u, bytesRead);
    EXPECT_EQ(0u, fileIo.tell());
    fileIo.close();
}

// Test: seek to position 0
TEST_F(FileIoTest_548, SeekToZero_548) {
    std::string content = "ABCDEF";
    std::string path = makeTempFile("seek_zero", content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();

    fileIo.read(nullptr, 0); // just to start
    fileIo.seek(3, Exiv2::BasicIo::beg);
    EXPECT_EQ(3u, fileIo.tell());

    fileIo.seek(0, Exiv2::BasicIo::beg);
    EXPECT_EQ(0u, fileIo.tell());

    int byte = fileIo.getb();
    EXPECT_EQ('A', byte);
    fileIo.close();
}

// Test: Destructor closes file properly (no crash)
TEST_F(FileIoTest_548, DestructorClosesFile_548) {
    std::string content = "destructor test";
    std::string path = makeTempFile("dtor_test", content);
    {
        Exiv2::FileIo fileIo(path);
        fileIo.open();
        // fileIo goes out of scope, destructor should close
    }
    // If we reach here without crash, test passes
    SUCCEED();
}

// Test: open with write mode "w+b"
TEST_F(FileIoTest_548, OpenWithWritePlusMode_548) {
    std::string path = makeTempFile("open_wp", "");
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.close();
    }
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(0, fileIo.open("w+b"));
    EXPECT_TRUE(fileIo.isopen());

    const std::string data = "read-write data";
    fileIo.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    fileIo.seek(0, Exiv2::BasicIo::beg);

    Exiv2::byte buf[64] = {0};
    size_t bytesRead = fileIo.read(buf, data.size());
    EXPECT_EQ(data.size(), bytesRead);
    EXPECT_EQ(0, std::memcmp(buf, data.data(), data.size()));
    fileIo.close();
}

} // anonymous namespace
