// ErrnoGuard_tests_601.cpp
#include <gtest/gtest.h>
#include <cerrno>

// Include the header under test (path based on the prompt).
// If your project uses a different include path, adjust accordingly.
#include "catch2/internal/catch_errno_guard.hpp"

using Catch::ErrnoGuard;

class ErrnoGuardTest_601 : public ::testing::Test {
protected:
    int saved_{};
    void SetUp() override { saved_ = errno; }
    void TearDown() override { errno = saved_; }
};

// Helper used by an exception-focused test.
static void FunctionThatThrowsWithErrnoGuard_601(int during_value) {
    ErrnoGuard guard;           // captures current errno at construction
    errno = during_value;       // mutate errno while guard is active
    throw std::runtime_error("boom");
}

// Normal operation: destructor restores errno on scope exit.
TEST_F(ErrnoGuardTest_601, RestoresErrnoOnScopeExit_601) {
    errno = 0;                  // initial observable state
    {
        ErrnoGuard guard;       // captures 0
        errno = EINVAL;         // mutate
        ASSERT_EQ(errno, EINVAL);
    }                           // RAII restore should fire here
    EXPECT_EQ(errno, 0);
}

// Boundary: captures errno exactly at construction (later changes do not alter the saved value).
TEST_F(ErrnoGuardTest_601, CapturesInitialValueAtConstruction_601) {
    errno = ENOENT;             // initial
    {
        ErrnoGuard guard;       // captures ENOENT
        errno = EACCES;         // change after construction
    }                           // should restore to ENOENT
    EXPECT_EQ(errno, ENOENT);
}

// Boundary: nested guards restore in LIFO order.
TEST_F(ErrnoGuardTest_601, NestedGuardsRestoreInOrder_601) {
    errno = 0;                  // A
    {
        ErrnoGuard outer;       // saves A (0)
        errno = EACCES;         // B
        {
            ErrnoGuard inner;   // saves B (EACCES)
            errno = ENOSPC;     // C
            ASSERT_EQ(errno, ENOSPC);
        }                       // inner restores to B
        EXPECT_EQ(errno, EACCES);
    }                           // outer restores to A
    EXPECT_EQ(errno, 0);
}

// Exceptional flow: errno is restored even if an exception unwinds the scope.
TEST_F(ErrnoGuardTest_601, RestoresErrnoAcrossException_601) {
    errno = EBUSY;              // initial
    try {
        FunctionThatThrowsWithErrnoGuard_601(ERANGE);
        FAIL() << "Expected exception not thrown";
    } catch (const std::runtime_error&) {
        // expected
    }
    // After unwinding, errno should be restored to initial value (EBUSY).
    EXPECT_EQ(errno, EBUSY);
}

// No-op case: if errno is not modified inside the guarded scope, it remains the same.
TEST_F(ErrnoGuardTest_601, NoChangeWhenErrnoUnmodified_601) {
    errno = ETIMEDOUT;          // initial
    {
        ErrnoGuard guard;       // captures ETIMEDOUT
        // no change to errno in this scope
    }                           // restore to the same value
    EXPECT_EQ(errno, ETIMEDOUT);
}
