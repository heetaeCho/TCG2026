#include <gtest/gtest.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>

// Declaration of the function under test
int openFileDescriptor(const char *path, int flags);

class OpenFileDescriptorTest_39 : public ::testing::Test {
protected:
    std::string tempFilePath;

    void SetUp() override {
        // Create a temporary file for testing
        char tmpName[] = "/tmp/openFileDescriptorTest_XXXXXX";
        int fd = mkstemp(tmpName);
        ASSERT_NE(fd, -1) << "Failed to create temp file";
        close(fd);
        tempFilePath = tmpName;
    }

    void TearDown() override {
        if (!tempFilePath.empty()) {
            unlink(tempFilePath.c_str());
        }
    }
};

// Test opening an existing file for reading
TEST_F(OpenFileDescriptorTest_39, OpenExistingFileReadOnly_39) {
    int fd = openFileDescriptor(tempFilePath.c_str(), O_RDONLY);
    ASSERT_NE(fd, -1) << "Failed to open existing file for reading";
    close(fd);
}

// Test opening an existing file for writing
TEST_F(OpenFileDescriptorTest_39, OpenExistingFileWriteOnly_39) {
    int fd = openFileDescriptor(tempFilePath.c_str(), O_WRONLY);
    ASSERT_NE(fd, -1) << "Failed to open existing file for writing";
    close(fd);
}

// Test opening an existing file for read/write
TEST_F(OpenFileDescriptorTest_39, OpenExistingFileReadWrite_39) {
    int fd = openFileDescriptor(tempFilePath.c_str(), O_RDWR);
    ASSERT_NE(fd, -1) << "Failed to open existing file for read/write";
    close(fd);
}

// Test opening a non-existent file without O_CREAT returns -1
TEST_F(OpenFileDescriptorTest_39, OpenNonExistentFileWithoutCreat_39) {
    int fd = openFileDescriptor("/tmp/nonexistent_file_openFileDescriptorTest_39_xyz", O_RDONLY);
    EXPECT_EQ(fd, -1);
}

// Test opening a non-existent file with O_CREAT creates the file
TEST_F(OpenFileDescriptorTest_39, OpenNonExistentFileWithCreat_39) {
    std::string newFile = tempFilePath + "_new";
    int fd = openFileDescriptor(newFile.c_str(), O_RDWR | O_CREAT);
    ASSERT_NE(fd, -1) << "Failed to create new file with O_CREAT";
    close(fd);
    // Verify the file exists
    struct stat st;
    EXPECT_EQ(stat(newFile.c_str(), &st), 0);
    unlink(newFile.c_str());
}

// Test that the returned file descriptor is valid and usable
TEST_F(OpenFileDescriptorTest_39, ReturnedFdIsUsable_39) {
    // Write some data to the temp file first
    {
        int fd = open(tempFilePath.c_str(), O_WRONLY);
        ASSERT_NE(fd, -1);
        const char *data = "hello";
        write(fd, data, strlen(data));
        close(fd);
    }

    int fd = openFileDescriptor(tempFilePath.c_str(), O_RDONLY);
    ASSERT_NE(fd, -1);

    char buf[16] = {};
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    EXPECT_EQ(n, 5);
    EXPECT_STREQ(buf, "hello");
    close(fd);
}

// Test that the file descriptor has close-on-exec flag set
TEST_F(OpenFileDescriptorTest_39, FdHasCloexecFlag_39) {
    int fd = openFileDescriptor(tempFilePath.c_str(), O_RDONLY);
    ASSERT_NE(fd, -1);

    int flags = fcntl(fd, F_GETFD);
    ASSERT_NE(flags, -1);
    EXPECT_NE(flags & FD_CLOEXEC, 0) << "FD_CLOEXEC should be set";
    close(fd);
}

// Test opening with null path
TEST_F(OpenFileDescriptorTest_39, OpenNullPath_39) {
    int fd = openFileDescriptor(nullptr, O_RDONLY);
    EXPECT_EQ(fd, -1);
}

// Test opening an empty string path
TEST_F(OpenFileDescriptorTest_39, OpenEmptyPath_39) {
    int fd = openFileDescriptor("", O_RDONLY);
    EXPECT_EQ(fd, -1);
}

// Test opening a directory path for reading
TEST_F(OpenFileDescriptorTest_39, OpenDirectoryReadOnly_39) {
    int fd = openFileDescriptor("/tmp", O_RDONLY);
    // Opening a directory for reading should succeed on most systems
    if (fd != -1) {
        int flags = fcntl(fd, F_GETFD);
        EXPECT_NE(flags & FD_CLOEXEC, 0);
        close(fd);
    }
}

// Test that returned fd is a non-negative integer on success
TEST_F(OpenFileDescriptorTest_39, ReturnedFdIsNonNegative_39) {
    int fd = openFileDescriptor(tempFilePath.c_str(), O_RDONLY);
    EXPECT_GE(fd, 0);
    if (fd >= 0) {
        close(fd);
    }
}

// Test opening with O_APPEND flag
TEST_F(OpenFileDescriptorTest_39, OpenWithAppendFlag_39) {
    int fd = openFileDescriptor(tempFilePath.c_str(), O_WRONLY | O_APPEND);
    ASSERT_NE(fd, -1);

    // Verify CLOEXEC is still set even with additional flags
    int fdFlags = fcntl(fd, F_GETFD);
    EXPECT_NE(fdFlags & FD_CLOEXEC, 0);

    close(fd);
}

// Test opening the same file multiple times returns different fds
TEST_F(OpenFileDescriptorTest_39, MultipleFdsForSameFile_39) {
    int fd1 = openFileDescriptor(tempFilePath.c_str(), O_RDONLY);
    int fd2 = openFileDescriptor(tempFilePath.c_str(), O_RDONLY);
    ASSERT_NE(fd1, -1);
    ASSERT_NE(fd2, -1);
    EXPECT_NE(fd1, fd2);
    close(fd1);
    close(fd2);
}

// Test opening with O_TRUNC truncates file
TEST_F(OpenFileDescriptorTest_39, OpenWithTrunc_39) {
    // Write data first
    {
        int fd = open(tempFilePath.c_str(), O_WRONLY);
        ASSERT_NE(fd, -1);
        const char *data = "some data";
        write(fd, data, strlen(data));
        close(fd);
    }

    int fd = openFileDescriptor(tempFilePath.c_str(), O_WRONLY | O_TRUNC);
    ASSERT_NE(fd, -1);
    close(fd);

    // Verify file is empty
    struct stat st;
    ASSERT_EQ(stat(tempFilePath.c_str(), &st), 0);
    EXPECT_EQ(st.st_size, 0);
}

// Test opening a path that is too long
TEST_F(OpenFileDescriptorTest_39, OpenPathTooLong_39) {
    std::string longPath(PATH_MAX + 100, 'a');
    int fd = openFileDescriptor(longPath.c_str(), O_RDONLY);
    EXPECT_EQ(fd, -1);
}
