#include <gtest/gtest.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>

// We need to test makeFileDescriptorCloexec, which is a static function in gfile.cc
// Since it's static, we cannot directly call it from outside the translation unit.
// However, we can test it indirectly if it's exposed through a header, or we need
// to include the source file directly.

// Include the header that may expose the function
// Based on the poppler project structure, gfile.h typically exposes file utility functions
#include "goo/gfile.h"

// If makeFileDescriptorCloexec is truly static and not exposed via header,
// we include the .cc file to access it (common testing technique for static functions)
// This is a pragmatic approach when testing static/internal functions.

// Forward declaration or include as needed. Since the function is static,
// we may need to use a workaround. Let's try including the source:
// Note: In practice, you'd need to handle this based on build system.

// We'll test through any public API that uses makeFileDescriptorCloexec,
// or test the behavior directly if we can access it.

// Since we must treat implementation as black box but the function IS the interface
// given to us, let's test it by including the source file to get access to the static function.

// Workaround: redefine static to nothing for testing purposes
#define static
#include "goo/gfile.cc"
#undef static

class MakeFileDescriptorCloexecTest_38 : public ::testing::Test {
protected:
    int fd_ = -1;

    void SetUp() override {
        // Create a valid file descriptor for testing
        fd_ = open("/dev/null", O_RDONLY);
    }

    void TearDown() override {
        if (fd_ >= 0) {
            close(fd_);
            fd_ = -1;
        }
    }
};

// Test that a valid file descriptor gets the CLOEXEC flag set
TEST_F(MakeFileDescriptorCloexecTest_38, ValidFdReturnsTrueAndSetsCloexec_38) {
    ASSERT_GE(fd_, 0) << "Failed to create test file descriptor";
    
    bool result = makeFileDescriptorCloexec(fd_);
    EXPECT_TRUE(result);

#ifdef FD_CLOEXEC
    int flags = fcntl(fd_, F_GETFD);
    EXPECT_GE(flags, 0);
    EXPECT_TRUE(flags & FD_CLOEXEC) << "FD_CLOEXEC flag should be set after call";
#endif
}

// Test with an invalid file descriptor
TEST_F(MakeFileDescriptorCloexecTest_38, InvalidFdReturnsFalse_38) {
#ifdef FD_CLOEXEC
    bool result = makeFileDescriptorCloexec(-1);
    EXPECT_FALSE(result);
#else
    // Without FD_CLOEXEC support, function always returns true
    bool result = makeFileDescriptorCloexec(-1);
    EXPECT_TRUE(result);
#endif
}

// Test that calling on an already-cloexec fd still succeeds
TEST_F(MakeFileDescriptorCloexecTest_38, AlreadyCloexecFdReturnsTrueAndPreservesFlag_38) {
    ASSERT_GE(fd_, 0) << "Failed to create test file descriptor";

#ifdef FD_CLOEXEC
    // First, manually set CLOEXEC
    int flags = fcntl(fd_, F_GETFD);
    ASSERT_GE(flags, 0);
    fcntl(fd_, F_SETFD, flags | FD_CLOEXEC);

    // Now call the function
    bool result = makeFileDescriptorCloexec(fd_);
    EXPECT_TRUE(result);

    // Verify flag is still set
    flags = fcntl(fd_, F_GETFD);
    EXPECT_GE(flags, 0);
    EXPECT_TRUE(flags & FD_CLOEXEC);
#endif
}

// Test with a closed file descriptor
TEST_F(MakeFileDescriptorCloexecTest_38, ClosedFdReturnsFalse_38) {
    ASSERT_GE(fd_, 0);
    int closed_fd = fd_;
    close(fd_);
    fd_ = -1; // Prevent double close in TearDown

#ifdef FD_CLOEXEC
    bool result = makeFileDescriptorCloexec(closed_fd);
    EXPECT_FALSE(result);
#else
    bool result = makeFileDescriptorCloexec(closed_fd);
    EXPECT_TRUE(result);
#endif
}

// Test with a pipe file descriptor
TEST_F(MakeFileDescriptorCloexecTest_38, PipeFdSetsCloexec_38) {
    int pipefd[2];
    int rc = pipe(pipefd);
    ASSERT_EQ(rc, 0) << "Failed to create pipe";

    bool result_read = makeFileDescriptorCloexec(pipefd[0]);
    bool result_write = makeFileDescriptorCloexec(pipefd[1]);

    EXPECT_TRUE(result_read);
    EXPECT_TRUE(result_write);

#ifdef FD_CLOEXEC
    int flags_read = fcntl(pipefd[0], F_GETFD);
    int flags_write = fcntl(pipefd[1], F_GETFD);
    EXPECT_TRUE(flags_read & FD_CLOEXEC);
    EXPECT_TRUE(flags_write & FD_CLOEXEC);
#endif

    close(pipefd[0]);
    close(pipefd[1]);
}

// Test with a large (but potentially valid) file descriptor number that is invalid
TEST_F(MakeFileDescriptorCloexecTest_38, LargeInvalidFdReturnsFalse_38) {
#ifdef FD_CLOEXEC
    bool result = makeFileDescriptorCloexec(99999);
    EXPECT_FALSE(result);
#else
    bool result = makeFileDescriptorCloexec(99999);
    EXPECT_TRUE(result);
#endif
}

// Test with fd = 0 (stdin), which should be valid
TEST_F(MakeFileDescriptorCloexecTest_38, StdinFdReturnsTrueAndSetsCloexec_38) {
    // fd 0 (stdin) should be valid in a normal test environment
    bool result = makeFileDescriptorCloexec(STDIN_FILENO);
    EXPECT_TRUE(result);

#ifdef FD_CLOEXEC
    int flags = fcntl(STDIN_FILENO, F_GETFD);
    EXPECT_GE(flags, 0);
    EXPECT_TRUE(flags & FD_CLOEXEC);
    
    // Clean up: remove CLOEXEC from stdin to not affect other tests
    fcntl(STDIN_FILENO, F_SETFD, flags & ~FD_CLOEXEC);
#endif
}

// Test with a temporary file descriptor
TEST_F(MakeFileDescriptorCloexecTest_38, TempFileFdSetsCloexec_38) {
    char tmpname[] = "/tmp/cloexec_test_XXXXXX";
    int tmpfd = mkstemp(tmpname);
    ASSERT_GE(tmpfd, 0) << "Failed to create temp file";
    unlink(tmpname); // Remove the file, but fd remains valid

    bool result = makeFileDescriptorCloexec(tmpfd);
    EXPECT_TRUE(result);

#ifdef FD_CLOEXEC
    int flags = fcntl(tmpfd, F_GETFD);
    EXPECT_GE(flags, 0);
    EXPECT_TRUE(flags & FD_CLOEXEC);
#endif

    close(tmpfd);
}
