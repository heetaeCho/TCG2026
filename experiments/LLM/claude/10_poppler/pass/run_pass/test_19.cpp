#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "gfile.h"

class GooFileTest_19 : public ::testing::Test {
protected:
    std::string tempFileName;

    void SetUp() override {
        tempFileName = "/tmp/goofile_test_19_XXXXXX";
        int fd = mkstemp(&tempFileName[0]);
        ASSERT_NE(fd, -1);
        close(fd);
    }

    void TearDown() override {
        unlink(tempFileName.c_str());
    }

    void writeToFile(const std::string &filename, const std::string &content) {
        std::ofstream ofs(filename, std::ios::binary);
        ofs << content;
        ofs.close();
    }
};

TEST_F(GooFileTest_19, OpenValidFileName_19) {
    writeToFile(tempFileName, "Hello, World!");
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);
}

TEST_F(GooFileTest_19, OpenInvalidFileName_19) {
    auto file = GooFile::open("/nonexistent/path/to/file_that_does_not_exist_19.txt");
    EXPECT_EQ(file, nullptr);
}

TEST_F(GooFileTest_19, OpenEmptyFileName_19) {
    auto file = GooFile::open(std::string(""));
    EXPECT_EQ(file, nullptr);
}

TEST_F(GooFileTest_19, OpenWithValidFileDescriptor_19) {
    writeToFile(tempFileName, "Test content");
    int fd = ::open(tempFileName.c_str(), O_RDONLY);
    ASSERT_NE(fd, -1);
    auto file = GooFile::open(fd);
    ASSERT_NE(file, nullptr);
}

TEST_F(GooFileTest_19, SizeReturnsCorrectValue_19) {
    std::string content = "Hello, World!";
    writeToFile(tempFileName, content);
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);
    EXPECT_EQ(file->size(), static_cast<Goffset>(content.size()));
}

TEST_F(GooFileTest_19, SizeOfEmptyFile_19) {
    writeToFile(tempFileName, "");
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);
    EXPECT_EQ(file->size(), 0);
}

TEST_F(GooFileTest_19, ReadEntireFile_19) {
    std::string content = "Hello, GooFile!";
    writeToFile(tempFileName, content);
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);

    char buf[256] = {0};
    int bytesRead = file->read(buf, content.size(), 0);
    EXPECT_EQ(bytesRead, static_cast<int>(content.size()));
    EXPECT_EQ(std::string(buf, bytesRead), content);
}

TEST_F(GooFileTest_19, ReadWithOffset_19) {
    std::string content = "Hello, GooFile!";
    writeToFile(tempFileName, content);
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);

    char buf[256] = {0};
    int offset = 7;
    int bytesRead = file->read(buf, content.size() - offset, offset);
    EXPECT_EQ(bytesRead, static_cast<int>(content.size() - offset));
    EXPECT_EQ(std::string(buf, bytesRead), content.substr(offset));
}

TEST_F(GooFileTest_19, ReadPartialFile_19) {
    std::string content = "Hello, GooFile!";
    writeToFile(tempFileName, content);
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);

    char buf[256] = {0};
    int bytesRead = file->read(buf, 5, 0);
    EXPECT_EQ(bytesRead, 5);
    EXPECT_EQ(std::string(buf, 5), "Hello");
}

TEST_F(GooFileTest_19, ReadBeyondFileSize_19) {
    std::string content = "Short";
    writeToFile(tempFileName, content);
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);

    char buf[256] = {0};
    int bytesRead = file->read(buf, 256, 0);
    // Should read only available bytes
    EXPECT_EQ(bytesRead, static_cast<int>(content.size()));
    EXPECT_EQ(std::string(buf, bytesRead), content);
}

TEST_F(GooFileTest_19, ReadFromOffsetBeyondFileSize_19) {
    std::string content = "Short";
    writeToFile(tempFileName, content);
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);

    char buf[256] = {0};
    int bytesRead = file->read(buf, 5, 100);
    // Reading beyond file should return 0 or error
    EXPECT_LE(bytesRead, 0);
}

TEST_F(GooFileTest_19, ReadZeroBytes_19) {
    std::string content = "Hello";
    writeToFile(tempFileName, content);
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);

    char buf[256] = {0};
    int bytesRead = file->read(buf, 0, 0);
    EXPECT_EQ(bytesRead, 0);
}

TEST_F(GooFileTest_19, ModificationTimeNotChangedInitially_19) {
    writeToFile(tempFileName, "Test content");
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);
    EXPECT_FALSE(file->modificationTimeChangedSinceOpen());
}

TEST_F(GooFileTest_19, ModificationTimeChangedAfterModification_19) {
    writeToFile(tempFileName, "Initial content");
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);

    // Wait a bit and modify the file to ensure timestamp changes
    sleep(1);
    writeToFile(tempFileName, "Modified content with more data");

    EXPECT_TRUE(file->modificationTimeChangedSinceOpen());
}

TEST_F(GooFileTest_19, SizeLargeFile_19) {
    // Create a file with known large-ish size
    std::string content(10000, 'A');
    writeToFile(tempFileName, content);
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);
    EXPECT_EQ(file->size(), 10000);
}

TEST_F(GooFileTest_19, ReadLargeFile_19) {
    std::string content(10000, 'B');
    writeToFile(tempFileName, content);
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);

    std::vector<char> buf(10000, 0);
    int bytesRead = file->read(buf.data(), 10000, 0);
    EXPECT_EQ(bytesRead, 10000);
    EXPECT_EQ(std::string(buf.data(), bytesRead), content);
}

TEST_F(GooFileTest_19, MultipleReadsFromSameFile_19) {
    std::string content = "ABCDEFGHIJ";
    writeToFile(tempFileName, content);
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);

    char buf1[5] = {0};
    char buf2[5] = {0};
    int read1 = file->read(buf1, 5, 0);
    int read2 = file->read(buf2, 5, 5);

    EXPECT_EQ(read1, 5);
    EXPECT_EQ(read2, 5);
    EXPECT_EQ(std::string(buf1, 5), "ABCDE");
    EXPECT_EQ(std::string(buf2, 5), "FGHIJ");
}

TEST_F(GooFileTest_19, CopyConstructorDeleted_19) {
    // Verify copy constructor is deleted (compile-time check)
    EXPECT_FALSE(std::is_copy_constructible<GooFile>::value);
}

TEST_F(GooFileTest_19, CopyAssignmentDeleted_19) {
    // Verify copy assignment is deleted (compile-time check)
    EXPECT_FALSE(std::is_copy_assignable<GooFile>::value);
}

TEST_F(GooFileTest_19, OpenWithDuplicatedFd_19) {
    writeToFile(tempFileName, "Dup test");
    int fd = ::open(tempFileName.c_str(), O_RDONLY);
    ASSERT_NE(fd, -1);
    int dupFd = ::dup(fd);
    ASSERT_NE(dupFd, -1);
    ::close(fd);

    auto file = GooFile::open(dupFd);
    ASSERT_NE(file, nullptr);
    EXPECT_EQ(file->size(), 8);
}

TEST_F(GooFileTest_19, ReadFromEmptyFile_19) {
    writeToFile(tempFileName, "");
    auto file = GooFile::open(tempFileName);
    ASSERT_NE(file, nullptr);

    char buf[256] = {0};
    int bytesRead = file->read(buf, 10, 0);
    EXPECT_LE(bytesRead, 0);
}
