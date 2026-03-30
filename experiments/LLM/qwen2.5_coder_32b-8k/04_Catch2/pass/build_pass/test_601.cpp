#include <gtest/gtest.h>

#include <cerrno>



// Assuming the correct header file is included for ErrnoGuard

#include "catch_errno_guard.hpp"



namespace Catch {

    class ErrnoGuard;

}



class ErrnoGuardTest_601 : public ::testing::Test {

protected:

    void SetUp() override {

        // Store the original errno to restore it after tests

        originalErrno = errno;

    }



    void TearDown() override {

        // Restore the original errno

        errno = originalErrno;

    }



    int originalErrno;

};



// Test that ErrnoGuard correctly restores errno on destruction under normal conditions

TEST_F(ErrnoGuardTest_601, RestoresErrnoOnDestruction_NormalOperation_601) {

    errno = 2; // Set errno to a non-zero value

    {

        Catch::ErrnoGuard guard;

        errno = 3; // Change errno while ErrnoGuard is active

    }

    EXPECT_EQ(errno, 2); // Check that errno was restored to its original value

}



// Test that ErrnoGuard correctly handles boundary conditions with errno set to zero

TEST_F(ErrnoGuardTest_601, RestoresErrnoToZero_BoundaryCondition_601) {

    errno = 0; // Set errno to zero

    {

        Catch::ErrnoGuard guard;

        errno = 3; // Change errno while ErrnoGuard is active

    }

    EXPECT_EQ(errno, 0); // Check that errno was restored to its original value (zero)

}



// Test that ErrnoGuard correctly handles boundary conditions with errno set to a large value

TEST_F(ErrnoGuardTest_601, RestoresErrnoToLargeValue_BoundaryCondition_601) {

    errno = 255; // Set errno to a large value

    {

        Catch::ErrnoGuard guard;

        errno = 3; // Change errno while ErrnoGuard is active

    }

    EXPECT_EQ(errno, 255); // Check that errno was restored to its original value (large)

}



// Test that ErrnoGuard does not change errno if it hasn't been modified

TEST_F(ErrnoGuardTest_601, DoesNotChangeUnmodifiedErrno_NormalOperation_601) {

    errno = 42; // Set errno to a specific value

    {

        Catch::ErrnoGuard guard;

    }

    EXPECT_EQ(errno, 42); // Check that errno remains unchanged

}
