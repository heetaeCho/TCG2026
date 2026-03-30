// posix_logger_destructor_test_427.cc

#include "util/posix_logger.h"

#include <gtest/gtest.h>

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

// Helper to write a byte to an fd and return errno on failure.
static int TryWriteByte(int fd) {
  const char ch = 'x';
  errno = 0;
  ssize_t n = ::write(fd, &ch, 1);
  if (n == 1) return 0;
  return errno;
}

// Verifies that when PosixLogger is destroyed, it fclose()s the provided FILE*,
// which closes the underlying file descriptor.
// Naming requirement: include TEST_ID (427) in the test name.
TEST(PosixLoggerTest_427, DestructorClosesUnderlyingFd_427) {
  // Create a temporary FILE* owned by PosixLogger.
  std::FILE* fp = std::tmpfile();
  ASSERT_NE(fp, nullptr) << "tmpfile() failed";

  const int fd = ::fileno(fp);
  ASSERT_GE(fd, 0) << "fileno() failed";

  // Keep a duplicate of the fd to prevent the underlying file description
  // from disappearing from the system entirely; this also lets us assert
  // that only the logger-owned fd is closed.
  const int fd_dup = ::dup(fd);
  ASSERT_GE(fd_dup, 0) << "dup() failed: " << std::strerror(errno);

  {
    // Construct and immediately destroy the logger to trigger ~PosixLogger().
    leveldb::PosixLogger logger(fp);
    // Scope end -> destructor runs here, which should fclose(fp) and close fd.
  }

  // The original fd should now be invalid.
  const int err = TryWriteByte(fd);
  EXPECT_EQ(err, EBADF) << "Expected EBADF writing to closed fd, got errno=" << err;

  // Clean up the duplicate fd we kept open.
  ::close(fd_dup);
}

// Verifies that closing done by the PosixLogger does not invalidate other
// file descriptors that refer to the same underlying file description (e.g., a dup).
TEST(PosixLoggerTest_427, DestructorDoesNotInvalidateDuplicatedFd_427) {
  std::FILE* fp = std::tmpfile();
  ASSERT_NE(fp, nullptr) << "tmpfile() failed";

  const int fd = ::fileno(fp);
  ASSERT_GE(fd, 0);

  // Duplicate before handing fp to PosixLogger.
  const int fd_dup = ::dup(fd);
  ASSERT_GE(fd_dup, 0) << "dup() failed: " << std::strerror(errno);

  {
    leveldb::PosixLogger logger(fp);
    // Destructor should fclose(fp) at scope exit (closing 'fd').
  }

  // The dup'd descriptor should remain valid and writable.
  errno = 0;
  const char ch = 'y';
  ssize_t written = ::write(fd_dup, &ch, 1);
  EXPECT_EQ(written, 1) << "Expected write to succeed on dup'd fd, errno=" << errno;

  // Original fd should be closed.
  const int err = TryWriteByte(fd);
  EXPECT_EQ(err, EBADF);

  ::close(fd_dup);
}
