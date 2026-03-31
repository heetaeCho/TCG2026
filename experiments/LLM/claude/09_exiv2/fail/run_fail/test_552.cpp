#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <filesystem>

#include "exiv2/basicio.hpp"

namespace {

// Helper to create a temporary file path
std::string getTempFilePath(const std::string& suffix = "") {
    static int counter = 0;
    std::string path = std::string("test_fileio_552_") + std::to_string(counter++) + suffix + ".tmp";
    return path;
}

// Helper to create a file with specific content
void createFileWithContent(const std::string& path, const std::string& content) {
    std::ofstream ofs(path, std::ios::binary);
    ofs.write(content.data(), content.size());
    ofs.close();
}

// Helper to read file content
std::string readFileContent(const std::string& path) {
    std::ifstream ifs(path, std::ios::binary);
    return std::string((std::istreambuf_iterator<char>(ifs)),
                       std::istreambuf_iterator<char>());
}

// Helper to remove temp file
void removeFile(const std::string& path) {
    std::remove(path.c_str());
}

class FileIoTest_552 : public ::testing::Test {
protected:
    std::vector<std::string> tempFiles_;

    void TearDown() override {
        for (const auto& f : tempFiles_) {
            removeFile(f);
        }
    }

    std::string createTempFile(const std::string& content = "", const std::string& suffix = "") {
        std::string path = getTempFilePath(suffix);
        if (!content.empty()) {
            createFileWithContent(path, content);
        }
        tempFiles_.push_back(path);
        return path;
    }
};

// Test: Constructor sets path correctly
TEST_F(FileIoTest_552, ConstructorSetsPath_552) {
    std::string path = "/some/test/path.jpg";
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(fileIo.path(), path);
}

// Test: File is not open after construction
TEST_F(FileIoTest_552, NotOpenAfterConstruction_552) {
    std::string path = createTempFile("hello");
    Exiv2::FileIo fileIo(path);
    EXPECT_FALSE(fileIo.isopen());
}

// Test: Open existing file returns 0
TEST_F(FileIoTest_552, OpenExistingFileReturnsZero_552) {
    std::string path = createTempFile("test content");
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(fileIo.open(), 0);
    EXPECT_TRUE(fileIo.isopen());
    fileIo.close();
}

// Test: Open non-existing file returns non-zero
TEST_F(FileIoTest_552, OpenNonExistingFileReturnsNonZero_552) {
    Exiv2::FileIo fileIo("/non/existing/path/file_552.tmp");
    EXPECT_NE(fileIo.open(), 0);
}

// Test: Open with mode string
TEST_F(FileIoTest_552, OpenWithModeString_552) {
    std::string path = createTempFile("data");
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(fileIo.open("r"), 0);
    EXPECT_TRUE(fileIo.isopen());
    fileIo.close();
}

// Test: Close returns 0 on open file
TEST_F(FileIoTest_552, CloseOpenFileReturnsZero_552) {
    std::string path = createTempFile("data");
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    EXPECT_EQ(fileIo.close(), 0);
    EXPECT_FALSE(fileIo.isopen());
}

// Test: Close without open
TEST_F(FileIoTest_552, CloseWithoutOpen_552) {
    std::string path = createTempFile("data");
    Exiv2::FileIo fileIo(path);
    // Close on a non-open file should not crash
    int result = fileIo.close();
    // Result may be 0 since nothing is open
    EXPECT_FALSE(fileIo.isopen());
}

// Test: Write data to file
TEST_F(FileIoTest_552, WriteDataToFile_552) {
    std::string path = createTempFile();
    Exiv2::FileIo fileIo(path);
    fileIo.open("w+b");
    
    const std::string data = "Hello, World!";
    size_t written = fileIo.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    EXPECT_EQ(written, data.size());
    
    fileIo.close();
    
    std::string content = readFileContent(path);
    EXPECT_EQ(content, data);
}

// Test: Write zero bytes
TEST_F(FileIoTest_552, WriteZeroBytes_552) {
    std::string path = createTempFile();
    Exiv2::FileIo fileIo(path);
    fileIo.open("w+b");
    
    const Exiv2::byte data[] = {0x01};
    size_t written = fileIo.write(data, 0);
    EXPECT_EQ(written, 0u);
    
    fileIo.close();
}

// Test: Write without open returns 0
TEST_F(FileIoTest_552, WriteWithoutOpenReturnsZero_552) {
    std::string path = createTempFile();
    Exiv2::FileIo fileIo(path);
    
    const std::string data = "test";
    size_t written = fileIo.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    EXPECT_EQ(written, 0u);
}

// Test: Read data from file
TEST_F(FileIoTest_552, ReadDataFromFile_552) {
    std::string content = "Hello, FileIo!";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    Exiv2::byte buf[256] = {};
    size_t bytesRead = fileIo.read(buf, content.size());
    EXPECT_EQ(bytesRead, content.size());
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), content);
    
    fileIo.close();
}

// Test: Read with DataBuf
TEST_F(FileIoTest_552, ReadDataBuf_552) {
    std::string content = "DataBuf test";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    Exiv2::DataBuf buf = fileIo.read(content.size());
    EXPECT_EQ(buf.size(), content.size());
    EXPECT_EQ(std::memcmp(buf.data(), content.data(), content.size()), 0);
    
    fileIo.close();
}

// Test: Read more than available
TEST_F(FileIoTest_552, ReadMoreThanAvailable_552) {
    std::string content = "short";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    Exiv2::byte buf[256] = {};
    size_t bytesRead = fileIo.read(buf, 256);
    EXPECT_EQ(bytesRead, content.size());
    
    fileIo.close();
}

// Test: Size of file
TEST_F(FileIoTest_552, SizeReturnsCorrectValue_552) {
    std::string content = "1234567890";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    EXPECT_EQ(fileIo.size(), content.size());
    
    fileIo.close();
}

// Test: Tell position after open
TEST_F(FileIoTest_552, TellAfterOpen_552) {
    std::string content = "some data";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    EXPECT_EQ(fileIo.tell(), 0u);
    
    fileIo.close();
}

// Test: Tell position after read
TEST_F(FileIoTest_552, TellAfterRead_552) {
    std::string content = "0123456789";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    Exiv2::byte buf[5];
    fileIo.read(buf, 5);
    EXPECT_EQ(fileIo.tell(), 5u);
    
    fileIo.close();
}

// Test: Seek from beginning
TEST_F(FileIoTest_552, SeekFromBeginning_552) {
    std::string content = "0123456789";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    EXPECT_EQ(fileIo.seek(5, Exiv2::BasicIo::beg), 0);
    EXPECT_EQ(fileIo.tell(), 5u);
    
    fileIo.close();
}

// Test: Seek from current position
TEST_F(FileIoTest_552, SeekFromCurrent_552) {
    std::string content = "0123456789";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    fileIo.seek(3, Exiv2::BasicIo::beg);
    EXPECT_EQ(fileIo.seek(2, Exiv2::BasicIo::cur), 0);
    EXPECT_EQ(fileIo.tell(), 5u);
    
    fileIo.close();
}

// Test: Seek from end
TEST_F(FileIoTest_552, SeekFromEnd_552) {
    std::string content = "0123456789";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    EXPECT_EQ(fileIo.seek(-3, Exiv2::BasicIo::end), 0);
    EXPECT_EQ(fileIo.tell(), 7u);
    
    fileIo.close();
}

// Test: getb reads single byte
TEST_F(FileIoTest_552, GetbReadsSingleByte_552) {
    std::string content = "AB";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    int byte1 = fileIo.getb();
    EXPECT_EQ(byte1, 'A');
    
    int byte2 = fileIo.getb();
    EXPECT_EQ(byte2, 'B');
    
    fileIo.close();
}

// Test: getb at EOF returns EOF
TEST_F(FileIoTest_552, GetbAtEofReturnsEof_552) {
    std::string content = "X";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    fileIo.getb(); // Read 'X'
    int result = fileIo.getb(); // Should be EOF
    EXPECT_EQ(result, EOF);
    
    fileIo.close();
}

// Test: putb writes single byte
TEST_F(FileIoTest_552, PutbWritesSingleByte_552) {
    std::string path = createTempFile();
    Exiv2::FileIo fileIo(path);
    fileIo.open("w+b");
    
    int result = fileIo.putb(0x42);
    EXPECT_EQ(result, 0x42);
    
    fileIo.close();
    
    std::string content = readFileContent(path);
    EXPECT_EQ(content.size(), 1u);
    EXPECT_EQ(static_cast<Exiv2::byte>(content[0]), 0x42);
}

// Test: EOF detection
TEST_F(FileIoTest_552, EofDetection_552) {
    std::string content = "A";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    EXPECT_FALSE(fileIo.eof());
    
    fileIo.getb(); // Read 'A'
    fileIo.getb(); // Attempt to read past end
    
    EXPECT_TRUE(fileIo.eof());
    
    fileIo.close();
}

// Test: Error returns 0 on normal operation
TEST_F(FileIoTest_552, ErrorReturnsZeroOnNormal_552) {
    std::string content = "data";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    EXPECT_EQ(fileIo.error(), 0);
    
    fileIo.close();
}

// Test: setPath changes the path
TEST_F(FileIoTest_552, SetPathChangesPath_552) {
    std::string path1 = createTempFile("data1");
    std::string path2 = createTempFile("data2");
    Exiv2::FileIo fileIo(path1);
    
    EXPECT_EQ(fileIo.path(), path1);
    fileIo.setPath(path2);
    EXPECT_EQ(fileIo.path(), path2);
}

// Test: Write large data
TEST_F(FileIoTest_552, WriteLargeData_552) {
    std::string path = createTempFile();
    Exiv2::FileIo fileIo(path);
    fileIo.open("w+b");
    
    std::vector<Exiv2::byte> largeData(100000, 0xAB);
    size_t written = fileIo.write(largeData.data(), largeData.size());
    EXPECT_EQ(written, largeData.size());
    
    fileIo.close();
    
    std::string content = readFileContent(path);
    EXPECT_EQ(content.size(), 100000u);
}

// Test: Multiple writes
TEST_F(FileIoTest_552, MultipleWrites_552) {
    std::string path = createTempFile();
    Exiv2::FileIo fileIo(path);
    fileIo.open("w+b");
    
    const std::string data1 = "Hello";
    const std::string data2 = " World";
    
    fileIo.write(reinterpret_cast<const Exiv2::byte*>(data1.data()), data1.size());
    fileIo.write(reinterpret_cast<const Exiv2::byte*>(data2.data()), data2.size());
    
    fileIo.close();
    
    std::string content = readFileContent(path);
    EXPECT_EQ(content, "Hello World");
}

// Test: Write from BasicIo source
TEST_F(FileIoTest_552, WriteFromBasicIoSource_552) {
    std::string srcContent = "source content";
    std::string srcPath = createTempFile(srcContent);
    std::string dstPath = createTempFile();
    
    Exiv2::FileIo srcIo(srcPath);
    Exiv2::FileIo dstIo(dstPath);
    
    srcIo.open();
    dstIo.open("w+b");
    
    size_t written = dstIo.write(srcIo);
    EXPECT_EQ(written, srcContent.size());
    
    srcIo.close();
    dstIo.close();
    
    std::string content = readFileContent(dstPath);
    EXPECT_EQ(content, srcContent);
}

// Test: Read after write with seek
TEST_F(FileIoTest_552, ReadAfterWriteWithSeek_552) {
    std::string path = createTempFile();
    Exiv2::FileIo fileIo(path);
    fileIo.open("w+b");
    
    const std::string data = "ReadAfterWrite";
    fileIo.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    
    fileIo.seek(0, Exiv2::BasicIo::beg);
    
    Exiv2::byte buf[256] = {};
    size_t bytesRead = fileIo.read(buf, data.size());
    EXPECT_EQ(bytesRead, data.size());
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), bytesRead), data);
    
    fileIo.close();
}

// Test: Empty file size is zero
TEST_F(FileIoTest_552, EmptyFileSizeIsZero_552) {
    std::string path = createTempFile("");
    // Create an actual empty file
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.close();
    }
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    EXPECT_EQ(fileIo.size(), 0u);
    
    fileIo.close();
}

// Test: Path returns correct path
TEST_F(FileIoTest_552, PathReturnsCorrectPath_552) {
    std::string path = createTempFile("data");
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(fileIo.path(), path);
}

// Test: Seek to beginning after read
TEST_F(FileIoTest_552, SeekToBeginningAfterRead_552) {
    std::string content = "ABCDEF";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    Exiv2::byte buf[6];
    fileIo.read(buf, 6);
    EXPECT_EQ(fileIo.tell(), 6u);
    
    fileIo.seek(0, Exiv2::BasicIo::beg);
    EXPECT_EQ(fileIo.tell(), 0u);
    
    // Read again
    Exiv2::byte buf2[3];
    size_t bytesRead = fileIo.read(buf2, 3);
    EXPECT_EQ(bytesRead, 3u);
    EXPECT_EQ(buf2[0], 'A');
    EXPECT_EQ(buf2[1], 'B');
    EXPECT_EQ(buf2[2], 'C');
    
    fileIo.close();
}

// Test: mmap and munmap
TEST_F(FileIoTest_552, MmapAndMunmap_552) {
    std::string content = "mmap test data";
    std::string path = createTempFile(content);
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    Exiv2::byte* mapped = fileIo.mmap(false);
    ASSERT_NE(mapped, nullptr);
    EXPECT_EQ(std::memcmp(mapped, content.data(), content.size()), 0);
    
    EXPECT_EQ(fileIo.munmap(), 0);
    fileIo.close();
}

// Test: Transfer from another FileIo
TEST_F(FileIoTest_552, TransferFromFileIo_552) {
    std::string srcContent = "transfer data";
    std::string srcPath = createTempFile(srcContent);
    std::string dstPath = createTempFile();
    
    Exiv2::FileIo srcIo(srcPath);
    Exiv2::FileIo dstIo(dstPath);
    
    srcIo.open();
    dstIo.transfer(srcIo);
    
    // After transfer, dst should have the content
    dstIo.open();
    Exiv2::DataBuf buf = dstIo.read(srcContent.size());
    EXPECT_EQ(buf.size(), srcContent.size());
    EXPECT_EQ(std::memcmp(buf.data(), srcContent.data(), srcContent.size()), 0);
    
    dstIo.close();
}

// Test: Open with write mode creates file
TEST_F(FileIoTest_552, OpenWithWriteModeCreatesFile_552) {
    std::string path = getTempFilePath("_create");
    tempFiles_.push_back(path);
    removeFile(path); // Ensure it doesn't exist
    
    Exiv2::FileIo fileIo(path);
    EXPECT_EQ(fileIo.open("w+b"), 0);
    EXPECT_TRUE(fileIo.isopen());
    
    const std::string data = "new file";
    fileIo.write(reinterpret_cast<const Exiv2::byte*>(data.data()), data.size());
    fileIo.close();
    
    std::string content = readFileContent(path);
    EXPECT_EQ(content, data);
}

// Test: Isopen returns false after close
TEST_F(FileIoTest_552, IsOpenReturnsFalseAfterClose_552) {
    std::string path = createTempFile("data");
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    EXPECT_TRUE(fileIo.isopen());
    fileIo.close();
    EXPECT_FALSE(fileIo.isopen());
}

// Test: Read from empty file returns 0
TEST_F(FileIoTest_552, ReadFromEmptyFileReturnsZero_552) {
    std::string path = createTempFile();
    {
        std::ofstream ofs(path, std::ios::binary);
        ofs.close();
    }
    Exiv2::FileIo fileIo(path);
    fileIo.open();
    
    Exiv2::byte buf[10];
    size_t bytesRead = fileIo.read(buf, 10);
    EXPECT_EQ(bytesRead, 0u);
    
    fileIo.close();
}

}  // namespace
