// File: test_gfile_makeFileDescriptorCloexec_38.cpp
//
// Unit tests for makeFileDescriptorCloexec(int fd) from poppler/goo/gfile.cc
// TEST_ID: 38
//
// Notes:
// - The function under test is `static` in gfile.cc, so we include the .cc file
//   into this test translation unit to access it without changing production code.
// - Tests only assert observable behavior via public OS APIs (fcntl), treating the
//   function as a black box.

#include <gtest/gtest.h>

#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

#if defined(__has_include)
  #if __has_include("TestProjects/poppler/goo/gfile.cc")
    #include "TestProjects/poppler/goo/gfile.cc"
  #elif __has_include("poppler/goo/gfile.cc")
    #include "poppler/goo/gfile.cc"
  #elif __has_include("goo/gfile.cc")
    #include "goo/gfile.cc"
  #else
    #error "Unable to locate gfile.cc for inclusion. Adjust include paths or the include list above."
  #endif
#else
  // Fallback if __has_include is not supported by the compiler:
  #include "goo/gfile.cc"
#endif

namespace {

class MakeFileDescriptorCloexecTest_38 : public ::testing::Test {
protected:
  static int OpenDevNullOrSkip() {
#if defined(_WIN32)
    GTEST_SKIP() << "fcntl/FD_CLOEXEC tests are POSIX-specific.";
    return -1;
#else
    int fd = ::open("/dev/null", O_RDONLY);
    if (fd < 0) {
      GTEST_SKIP() << "open(/dev/null) failed: errno=" << errno;
    }
    return fd;
#endif
  }
};

#if defined(FD_CLOEXEC)

TEST_F(MakeFileDescriptorCloexecTest_38, SetsCloexecWhenNotSet_38) {
  const int fd = OpenDevNullOrSkip();
  ASSERT_GE(fd, 0);

  int flags = ::fcntl(fd, F_GETFD);
  ASSERT_GE(flags, 0);

  // Ensure FD_CLOEXEC is NOT set before calling the function.
  ASSERT_GE(::fcntl(fd, F_SETFD, flags & ~FD_CLOEXEC), 0);

  EXPECT_TRUE(makeFileDescriptorCloexec(fd));

  int after = ::fcntl(fd, F_GETFD);
  ASSERT_GE(after, 0);
  EXPECT_NE(after & FD_CLOEXEC, 0) << "FD_CLOEXEC should be set after call";

  ::close(fd);
}

TEST_F(MakeFileDescriptorCloexecTest_38, ReturnsTrueWhenAlreadySet_38) {
  const int fd = OpenDevNullOrSkip();
  ASSERT_GE(fd, 0);

  int flags = ::fcntl(fd, F_GETFD);
  ASSERT_GE(flags, 0);

  // Ensure FD_CLOEXEC IS set before calling the function.
  ASSERT_GE(::fcntl(fd, F_SETFD, flags | FD_CLOEXEC), 0);

  EXPECT_TRUE(makeFileDescriptorCloexec(fd));

  int after = ::fcntl(fd, F_GETFD);
  ASSERT_GE(after, 0);
  EXPECT_NE(after & FD_CLOEXEC, 0) << "FD_CLOEXEC should remain set";

  ::close(fd);
}

TEST_F(MakeFileDescriptorCloexecTest_38, ReturnsFalseOnInvalidFd_38) {
  // Observable error case: fcntl should fail on invalid fd, function should return false.
  EXPECT_FALSE(makeFileDescriptorCloexec(-1));
}

TEST_F(MakeFileDescriptorCloexecTest_38, WorksWithPipeReadEnd_38) {
  int fds[2] = {-1, -1};
  ASSERT_EQ(::pipe(fds), 0);

  const int readFd = fds[0];
  const int writeFd = fds[1];

  int flags = ::fcntl(readFd, F_GETFD);
  ASSERT_GE(flags, 0);
  ASSERT_GE(::fcntl(readFd, F_SETFD, flags & ~FD_CLOEXEC), 0);

  EXPECT_TRUE(makeFileDescriptorCloexec(readFd));

  int after = ::fcntl(readFd, F_GETFD);
  ASSERT_GE(after, 0);
  EXPECT_NE(after & FD_CLOEXEC, 0);

  ::close(readFd);
  ::close(writeFd);
}

#else  // !FD_CLOEXEC

TEST_F(MakeFileDescriptorCloexecTest_38, AlwaysReturnsTrueWhenFdCloexecUnavailable_38) {
  // When FD_CLOEXEC is not available, the implementation returns true.
  EXPECT_TRUE(makeFileDescriptorCloexec(-1));
}

#endif  // FD_CLOEXEC

}  // namespace