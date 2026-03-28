#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

// Declaration of the function under test
FILE *openFile(const char *path, const char *mode);

class OpenFileTest_40 : public ::testing::Test {
protected:
    std::string testDir;
    std::vector<std::string> tempFiles;

    void SetUp() override {
        testDir = "/tmp/openfile_test_40_XXXXXX";
        char *dir = mkdtemp(&testDir[0]);
        ASSERT_NE(dir, nullptr) << "Failed to create temp directory";
    }

    void TearDown() override {
        for (const auto &f : tempFiles) {
            unlink(f.c_str());
        }
        rmdir(testDir.c_str());
    }

    std::string createTempFilePath(const std::string &name) {
        std::string path = testDir + "/" + name;
        tempFiles.push_back(path);
        return path;
    }

    void createFileWithContent(const std::string &path, const std::string &content) {
        FILE *f = fopen(path.c_str(), "w");
        ASSERT_NE(f, nullptr);
        fwrite(content.c_str(), 1, content.size(), f);
        fclose(f);
    }
};

// Test opening a file for writing creates the file and returns non-null
TEST_F(OpenFileTest_40, OpenForWriteCreatesFile_40) {
    std::string path = createTempFilePath("test_write.txt");
    FILE *file = openFile(path.c_str(), "w");
    ASSERT_NE(file, nullptr);
    fprintf(file, "hello");
    fclose(file);

    // Verify file exists and has content
    struct stat st;
    EXPECT_EQ(stat(path.c_str(), &st), 0);
    EXPECT_GT(st.st_size, 0);
}

// Test opening a file for reading when file exists
TEST_F(OpenFileTest_40, OpenForReadExistingFile_40) {
    std::string path = createTempFilePath("test_read.txt");
    createFileWithContent(path, "test content");

    FILE *file = openFile(path.c_str(), "r");
    ASSERT_NE(file, nullptr);

    char buf[64] = {0};
    size_t bytesRead = fread(buf, 1, sizeof(buf) - 1, file);
    fclose(file);

    EXPECT_GT(bytesRead, 0u);
    EXPECT_STREQ(buf, "test content");
}

// Test opening a nonexistent file for reading returns nullptr
TEST_F(OpenFileTest_40, OpenNonexistentFileForReadReturnsNull_40) {
    std::string path = testDir + "/nonexistent_file_40.txt";
    FILE *file = openFile(path.c_str(), "r");
    EXPECT_EQ(file, nullptr);
}

// Test opening a file for append mode
TEST_F(OpenFileTest_40, OpenForAppend_40) {
    std::string path = createTempFilePath("test_append.txt");
    createFileWithContent(path, "first");

    FILE *file = openFile(path.c_str(), "a");
    ASSERT_NE(file, nullptr);
    fprintf(file, "second");
    fclose(file);

    FILE *readFile = openFile(path.c_str(), "r");
    ASSERT_NE(readFile, nullptr);
    char buf[64] = {0};
    fread(buf, 1, sizeof(buf) - 1, readFile);
    fclose(readFile);

    EXPECT_STREQ(buf, "firstsecond");
}

// Test opening with "rb" mode (binary read)
TEST_F(OpenFileTest_40, OpenForBinaryRead_40) {
    std::string path = createTempFilePath("test_binary.bin");
    unsigned char data[] = {0x00, 0x01, 0x02, 0xFF, 0xFE};

    FILE *wf = fopen(path.c_str(), "wb");
    ASSERT_NE(wf, nullptr);
    fwrite(data, 1, sizeof(data), wf);
    fclose(wf);

    FILE *file = openFile(path.c_str(), "rb");
    ASSERT_NE(file, nullptr);

    unsigned char readBuf[5] = {0};
    size_t bytesRead = fread(readBuf, 1, sizeof(readBuf), file);
    fclose(file);

    EXPECT_EQ(bytesRead, sizeof(data));
    EXPECT_EQ(memcmp(data, readBuf, sizeof(data)), 0);
}

// Test opening with "wb" mode (binary write)
TEST_F(OpenFileTest_40, OpenForBinaryWrite_40) {
    std::string path = createTempFilePath("test_bwrite.bin");

    FILE *file = openFile(path.c_str(), "wb");
    ASSERT_NE(file, nullptr);

    unsigned char data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    fwrite(data, 1, sizeof(data), file);
    fclose(file);

    FILE *rf = fopen(path.c_str(), "rb");
    ASSERT_NE(rf, nullptr);
    unsigned char readBuf[4] = {0};
    size_t bytesRead = fread(readBuf, 1, sizeof(readBuf), rf);
    fclose(rf);

    EXPECT_EQ(bytesRead, sizeof(data));
    EXPECT_EQ(memcmp(data, readBuf, sizeof(data)), 0);
}

// Test that the file descriptor is cloexec (on non-Windows)
#ifndef _WIN32
TEST_F(OpenFileTest_40, FileDescriptorIsCloexec_40) {
    std::string path = createTempFilePath("test_cloexec.txt");
    createFileWithContent(path, "cloexec test");

    FILE *file = openFile(path.c_str(), "r");
    ASSERT_NE(file, nullptr);

    int fd = fileno(file);
    int flags = fcntl(fd, F_GETFD);
    EXPECT_NE(flags, -1);
    EXPECT_NE(flags & FD_CLOEXEC, 0) << "File descriptor should have FD_CLOEXEC set";

    fclose(file);
}
#endif

// Test opening a file in an invalid/nonexistent directory returns nullptr
TEST_F(OpenFileTest_40, OpenInNonexistentDirectoryReturnsNull_40) {
    FILE *file = openFile("/nonexistent_dir_40/file.txt", "w");
    EXPECT_EQ(file, nullptr);
}

// Test opening with "r+" mode on existing file
TEST_F(OpenFileTest_40, OpenForReadWriteExistingFile_40) {
    std::string path = createTempFilePath("test_rw.txt");
    createFileWithContent(path, "original");

    FILE *file = openFile(path.c_str(), "r+");
    ASSERT_NE(file, nullptr);

    // Overwrite beginning
    fprintf(file, "OVER");
    fseek(file, 0, SEEK_SET);

    char buf[64] = {0};
    fread(buf, 1, sizeof(buf) - 1, file);
    fclose(file);

    EXPECT_STREQ(buf, "OVERinal");
}

// Test opening an empty path returns nullptr
TEST_F(OpenFileTest_40, OpenEmptyPathReturnsNull_40) {
    FILE *file = openFile("", "r");
    EXPECT_EQ(file, nullptr);
}

// Test write then read back verifies data integrity
TEST_F(OpenFileTest_40, WriteAndReadBackIntegrity_40) {
    std::string path = createTempFilePath("test_integrity.txt");
    const std::string content = "The quick brown fox jumps over the lazy dog 0123456789";

    FILE *wf = openFile(path.c_str(), "w");
    ASSERT_NE(wf, nullptr);
    fwrite(content.c_str(), 1, content.size(), wf);
    fclose(wf);

    FILE *rf = openFile(path.c_str(), "r");
    ASSERT_NE(rf, nullptr);
    char buf[128] = {0};
    size_t bytesRead = fread(buf, 1, sizeof(buf) - 1, rf);
    fclose(rf);

    EXPECT_EQ(bytesRead, content.size());
    EXPECT_EQ(std::string(buf, bytesRead), content);
}

// Test opening with "w" truncates existing file
TEST_F(OpenFileTest_40, OpenForWriteTruncatesExistingFile_40) {
    std::string path = createTempFilePath("test_truncate.txt");
    createFileWithContent(path, "this is a long content that should be truncated");

    FILE *file = openFile(path.c_str(), "w");
    ASSERT_NE(file, nullptr);
    fprintf(file, "short");
    fclose(file);

    FILE *rf = openFile(path.c_str(), "r");
    ASSERT_NE(rf, nullptr);
    char buf[128] = {0};
    size_t bytesRead = fread(buf, 1, sizeof(buf) - 1, rf);
    fclose(rf);

    EXPECT_EQ(bytesRead, 5u);
    EXPECT_STREQ(buf, "short");
}

// Test opening a directory for reading (should fail or return something we can detect)
TEST_F(OpenFileTest_40, OpenDirectoryForRead_40) {
    // Attempting to open a directory for reading with fopen typically fails on most systems
    // or returns a FILE* that fails on read. We just check it doesn't crash.
    FILE *file = openFile(testDir.c_str(), "r");
    if (file != nullptr) {
        // If it opens, it should at least not crash on close
        fclose(file);
    }
    // No assertion failure means the test passes - we're testing no crash
}

// Test multiple opens of the same file
TEST_F(OpenFileTest_40, MultipleOpensOfSameFile_40) {
    std::string path = createTempFilePath("test_multi.txt");
    createFileWithContent(path, "multi open test");

    FILE *file1 = openFile(path.c_str(), "r");
    FILE *file2 = openFile(path.c_str(), "r");

    ASSERT_NE(file1, nullptr);
    ASSERT_NE(file2, nullptr);
    EXPECT_NE(file1, file2);

    char buf1[64] = {0}, buf2[64] = {0};
    fread(buf1, 1, sizeof(buf1) - 1, file1);
    fread(buf2, 1, sizeof(buf2) - 1, file2);

    EXPECT_STREQ(buf1, buf2);

    fclose(file1);
    fclose(file2);
}
