// File: goo_gfile_goo_file_test_19.cpp
// Unit tests for GooFile (./TestProjects/poppler/goo/gfile.h)

#include <gtest/gtest.h>

#include <cerrno>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "TestProjects/poppler/goo/gfile.h"

namespace {

class GooFileTest_19 : public ::testing::Test {
protected:
  std::string tempPath_;

  static std::string MakeTempPath() {
    // mkstemp requires a writable buffer
    std::string tpl = "/tmp/goofile_test_XXXXXX";
    std::vector<char> buf(tpl.begin(), tpl.end());
    buf.push_back('\0');
    int fd = ::mkstemp(buf.data());
    if (fd >= 0) {
      ::close(fd);
      return std::string(buf.data());
    }
    // If mkstemp fails, fall back to a predictable-ish path (best effort).
    return "/tmp/goofile_test_fallback_19";
  }

  static bool WriteAll(int fd, const void* data, size_t n) {
    const uint8_t* p = static_cast<const uint8_t*>(data);
    size_t written = 0;
    while (written < n) {
      ssize_t rc = ::write(fd, p + written, n - written);
      if (rc < 0) return false;
      written += static_cast<size_t>(rc);
    }
    return true;
  }

  static bool SetMTime(const std::string& path, time_t sec, long nsec) {
    timespec ts[2];
    ts[0].tv_sec = sec;   // atime
    ts[0].tv_nsec = nsec;
    ts[1].tv_sec = sec;   // mtime
    ts[1].tv_nsec = nsec;
#if defined(__linux__)
    return ::utimensat(AT_FDCWD, path.c_str(), ts, 0) == 0;
#else
    // Best-effort for platforms without utimensat: use utime-like behavior via futimens if possible.
    // If not available, return false and let test degrade gracefully.
    (void)path;
    (void)sec;
    (void)nsec;
    return false;
#endif
  }

  void SetUp() override { tempPath_ = MakeTempPath(); }

  void TearDown() override {
    if (!tempPath_.empty()) {
      ::unlink(tempPath_.c_str());
    }
  }

  bool CreateFileWithContents(const std::string& content) {
    int fd = ::open(tempPath_.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (fd < 0) return false;
    bool ok = WriteAll(fd, content.data(), content.size());
    ::fsync(fd);
    ::close(fd);
    return ok;
  }
};

TEST_F(GooFileTest_19, OpenByFilenameAndSizeMatches_19) {
  const std::string content = "hello goo file";
  ASSERT_TRUE(CreateFileWithContents(content));

  std::unique_ptr<GooFile> gf = GooFile::open(tempPath_);
  ASSERT_TRUE(gf) << "Expected GooFile::open(filename) to succeed for an existing file";

  const Goffset sz = gf->size();
  EXPECT_EQ(static_cast<long long>(sz), static_cast<long long>(content.size()));
}

TEST_F(GooFileTest_19, ReadReturnsExpectedBytesFromOffset_19) {
  const std::string content = "0123456789abcdef";
  ASSERT_TRUE(CreateFileWithContents(content));

  std::unique_ptr<GooFile> gf = GooFile::open(tempPath_);
  ASSERT_TRUE(gf);

  char buf[8] = {};
  // Read 4 bytes from offset 3: expects "3456"
  const int n = gf->read(buf, 4, static_cast<Goffset>(3));
  ASSERT_GE(n, 0) << "read() should not fail for valid range";
  ASSERT_EQ(n, 4);
  EXPECT_EQ(std::string(buf, buf + 4), "3456");
}

TEST_F(GooFileTest_19, ReadZeroBytesIsNoop_19) {
  const std::string content = "abc";
  ASSERT_TRUE(CreateFileWithContents(content));

  std::unique_ptr<GooFile> gf = GooFile::open(tempPath_);
  ASSERT_TRUE(gf);

  char buf[4] = {'x', 'x', 'x', '\0'};
  const int n = gf->read(buf, 0, static_cast<Goffset>(0));
  EXPECT_EQ(n, 0);
  // Buffer should remain unchanged (observable from our side).
  EXPECT_EQ(buf[0], 'x');
  EXPECT_EQ(buf[1], 'x');
  EXPECT_EQ(buf[2], 'x');
}

TEST_F(GooFileTest_19, ReadAtEndOfFileReturnsZero_19) {
  const std::string content = "abcd";
  ASSERT_TRUE(CreateFileWithContents(content));

  std::unique_ptr<GooFile> gf = GooFile::open(tempPath_);
  ASSERT_TRUE(gf);

  char buf[4] = {};
  const int n = gf->read(buf, 4, static_cast<Goffset>(content.size()));
  ASSERT_GE(n, 0);
  EXPECT_EQ(n, 0);
}

TEST_F(GooFileTest_19, ReadPastEndOfFileDoesNotCrashAndReturnsNonNegativeOrError_19) {
  const std::string content = "abcd";
  ASSERT_TRUE(CreateFileWithContents(content));

  std::unique_ptr<GooFile> gf = GooFile::open(tempPath_);
  ASSERT_TRUE(gf);

  char buf[8] = {};
  // Offset well past EOF. We only assert "no crash" and that it returns either 0 or an error (<0).
  const int n = gf->read(buf, 4, static_cast<Goffset>(content.size() + 1000));
  EXPECT_TRUE(n == 0 || n < 0);
}

TEST_F(GooFileTest_19, OpenNonExistentFileFails_19) {
  // Ensure the path does not exist.
  ::unlink(tempPath_.c_str());

  std::unique_ptr<GooFile> gf = GooFile::open(tempPath_);

  // Observable failure mode could be nullptr; if implementation uses a non-null sentinel,
  // it should still behave like an unopened file. Prefer the simplest observable contract.
  EXPECT_FALSE(gf);
}

TEST_F(GooFileTest_19, OpenFromFdAllowsReadingAndClosingOnDestruction_19) {
  const std::string content = "fd-open-test";
  ASSERT_TRUE(CreateFileWithContents(content));

  int fd = ::open(tempPath_.c_str(), O_RDONLY);
  ASSERT_GE(fd, 0);

  // Duplicate fd so we can prove closure precisely on the wrapped one.
  int wrappedFd = ::dup(fd);
  ASSERT_GE(wrappedFd, 0);
  ::close(fd);

  {
    std::unique_ptr<GooFile> gf = GooFile::open(wrappedFd);
    ASSERT_TRUE(gf) << "Expected GooFile::open(fd) to succeed for a valid fd";

    char buf[32] = {};
    const int n = gf->read(buf, static_cast<int>(content.size()), static_cast<Goffset>(0));
    ASSERT_GE(n, 0);
    ASSERT_EQ(n, static_cast<int>(content.size()));
    EXPECT_EQ(std::string(buf, buf + n), content);
    // gf destroyed here; destructor should close its fd.
  }

  // Verify wrappedFd is now closed (observable externally).
  errno = 0;
  char tmp;
  const ssize_t rc = ::read(wrappedFd, &tmp, 1);
  EXPECT_EQ(rc, -1);
  EXPECT_EQ(errno, EBADF);
}

TEST_F(GooFileTest_19, ModificationTimeInitiallyUnchangedAndMayChangeAfterTouch_19) {
  const std::string content = "mtime-test";
  ASSERT_TRUE(CreateFileWithContents(content));

  std::unique_ptr<GooFile> gf = GooFile::open(tempPath_);
  ASSERT_TRUE(gf);

  // Immediately after open, it should not have changed.
  EXPECT_FALSE(gf->modificationTimeChangedSinceOpen());

  // Best-effort: force mtime to a clearly different value.
  struct stat st {};
  ASSERT_EQ(::stat(tempPath_.c_str(), &st), 0);

  const time_t newSec = st.st_mtime + 10;  // bump by 10s
  const bool touched = SetMTime(tempPath_, newSec, 0);

  if (!touched) {
    // If we cannot set mtime on this platform, at least ensure calling the method is safe.
    SUCCEED();
    return;
  }

  // After touching mtime, the method should report changed (observable behavior).
  EXPECT_TRUE(gf->modificationTimeChangedSinceOpen());
}

}  // namespace