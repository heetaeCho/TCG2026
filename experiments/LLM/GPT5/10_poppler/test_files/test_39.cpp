// File: openFileDescriptor_test_39.cc
#include <gtest/gtest.h>

#include <cerrno>
#include <climits>
#include <cstdio>
#include <cstring>
#include <string>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Provided by ./TestProjects/poppler/goo/gfile.cc (linked from production code).
extern "C" int openFileDescriptor(const char* path, int flags);

namespace {

class OpenFileDescriptorTest_39 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (fd_to_cleanup_ >= 0) {
      close(fd_to_cleanup_);
      fd_to_cleanup_ = -1;
    }
    if (!temp_path_.empty()) {
      unlink(temp_path_.c_str());
      temp_path_.clear();
    }
  }

  std::string CreateTempFile() {
    char tmpl[] = "/tmp/openFileDescriptorTest_39_XXXXXX";
    int fd = mkstemp(tmpl);
    EXPECT_GE(fd, 0) << "mkstemp failed: errno=" << errno << " (" << std::strerror(errno) << ")";
    if (fd >= 0) {
      // Ensure the file exists; content doesn't matter.
      const char kData[] = "x";
      (void)write(fd, kData, sizeof(kData) - 1);
      close(fd);
    }
    temp_path_ = tmpl;
    return temp_path_;
  }

  int fd_to_cleanup_ = -1;
  std::string temp_path_;
};

}  // namespace

TEST_F(OpenFileDescriptorTest_39, OpensExistingFile_ReturnsValidFd_39) {
  const std::string path = CreateTempFile();

  errno = 0;
  int fd = openFileDescriptor(path.c_str(), O_RDONLY);
  ASSERT_GE(fd, 0) << "Expected a valid fd. errno=" << errno << " (" << std::strerror(errno) << ")";

  fd_to_cleanup_ = fd;  // cleaned up in TearDown
}

TEST_F(OpenFileDescriptorTest_39, SetsCloseOnExecFlag_39) {
  const std::string path = CreateTempFile();

  int fd = openFileDescriptor(path.c_str(), O_RDONLY);
  ASSERT_GE(fd, 0);
  fd_to_cleanup_ = fd;

  int fd_flags = fcntl(fd, F_GETFD);
  ASSERT_NE(fd_flags, -1) << "fcntl(F_GETFD) failed: errno=" << errno << " (" << std::strerror(errno) << ")";

  // Observable requirement: openFileDescriptor should create a CLOEXEC fd (either via O_CLOEXEC
  // at open() time, or by setting it afterward in fallback builds).
  EXPECT_NE(fd_flags & FD_CLOEXEC, 0) << "FD_CLOEXEC was not set on returned fd";
}

TEST_F(OpenFileDescriptorTest_39, NonexistentPath_ReturnsMinusOne_39) {
  std::string missing = "/tmp/openFileDescriptorTest_39_definitely_missing_";
  missing += std::to_string(getpid());
  missing += "_";
  missing += std::to_string(::time(nullptr));

  errno = 0;
  int fd = openFileDescriptor(missing.c_str(), O_RDONLY);
  EXPECT_EQ(fd, -1);
}

TEST_F(OpenFileDescriptorTest_39, EmptyPath_ReturnsMinusOne_39) {
  errno = 0;
  int fd = openFileDescriptor("", O_RDONLY);
  EXPECT_EQ(fd, -1);
}

TEST_F(OpenFileDescriptorTest_39, OpenWithWriteOnlyFlag_WorksForRegularFile_39) {
  const std::string path = CreateTempFile();

  int fd = openFileDescriptor(path.c_str(), O_WRONLY);
  ASSERT_GE(fd, 0) << "Expected to open existing file for writing. errno=" << errno << " ("
                   << std::strerror(errno) << ")";
  fd_to_cleanup_ = fd;

  // Basic observable behavior: writing should succeed on the returned fd.
  const char kMsg[] = "hello";
  ssize_t n = write(fd, kMsg, sizeof(kMsg) - 1);
  EXPECT_EQ(n, static_cast<ssize_t>(sizeof(kMsg) - 1))
      << "write failed: errno=" << errno << " (" << std::strerror(errno) << ")";
}