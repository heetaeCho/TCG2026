#include <gtest/gtest.h>
#include <cerrno>

// Based on the interface, ErrnoGuard saves errno on construction and restores it on destruction.
namespace Catch {
    class ErrnoGuard {
    private:
        int m_oldErrno;
    public:
        ErrnoGuard() : m_oldErrno(errno) {}
        ~ErrnoGuard() { errno = m_oldErrno; }
    };
}

class ErrnoGuardTest_601 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset errno before each test
        errno = 0;
    }
};

TEST_F(ErrnoGuardTest_601, ConstructorSavesCurrentErrno_601) {
    errno = 0;
    {
        Catch::ErrnoGuard guard;
        // Modify errno inside the scope
        errno = ENOENT;
        // errno should be modified
        EXPECT_EQ(errno, ENOENT);
    }
    // After guard is destroyed, errno should be restored to 0
    EXPECT_EQ(errno, 0);
}

TEST_F(ErrnoGuardTest_601, DestructorRestoresErrnoToOriginalValue_601) {
    errno = EINVAL;
    {
        Catch::ErrnoGuard guard;
        // errno should still be EINVAL right after construction
        EXPECT_EQ(errno, EINVAL);
        // Change errno
        errno = EACCES;
        EXPECT_EQ(errno, EACCES);
    }
    // Destructor should restore errno to EINVAL
    EXPECT_EQ(errno, EINVAL);
}

TEST_F(ErrnoGuardTest_601, RestoresZeroErrno_601) {
    errno = 0;
    {
        Catch::ErrnoGuard guard;
        errno = ENOMEM;
    }
    EXPECT_EQ(errno, 0);
}

TEST_F(ErrnoGuardTest_601, RestoresNonZeroErrno_601) {
    errno = ERANGE;
    {
        Catch::ErrnoGuard guard;
        errno = 0;
    }
    EXPECT_EQ(errno, ERANGE);
}

TEST_F(ErrnoGuardTest_601, NoModificationInsideScope_601) {
    errno = EDOM;
    {
        Catch::ErrnoGuard guard;
        // Don't change errno at all
    }
    // Should still be EDOM since it was saved and restored
    EXPECT_EQ(errno, EDOM);
}

TEST_F(ErrnoGuardTest_601, NestedGuards_601) {
    errno = 1;
    {
        Catch::ErrnoGuard outerGuard;
        errno = 2;
        {
            Catch::ErrnoGuard innerGuard;
            errno = 3;
            EXPECT_EQ(errno, 3);
        }
        // Inner guard restores errno to 2
        EXPECT_EQ(errno, 2);
    }
    // Outer guard restores errno to 1
    EXPECT_EQ(errno, 1);
}

TEST_F(ErrnoGuardTest_601, MultipleModificationsInsideScope_601) {
    errno = 42;
    {
        Catch::ErrnoGuard guard;
        errno = EINTR;
        errno = EAGAIN;
        errno = EPERM;
    }
    // Should restore to the original value regardless of how many times errno was changed
    EXPECT_EQ(errno, 42);
}

TEST_F(ErrnoGuardTest_601, SameValueInsideAndOutside_601) {
    errno = EEXIST;
    {
        Catch::ErrnoGuard guard;
        // Set errno to the same value
        errno = EEXIST;
    }
    EXPECT_EQ(errno, EEXIST);
}

TEST_F(ErrnoGuardTest_601, DeeplyNestedGuards_601) {
    errno = 10;
    {
        Catch::ErrnoGuard g1;
        errno = 20;
        {
            Catch::ErrnoGuard g2;
            errno = 30;
            {
                Catch::ErrnoGuard g3;
                errno = 40;
                EXPECT_EQ(errno, 40);
            }
            EXPECT_EQ(errno, 30);
        }
        EXPECT_EQ(errno, 20);
    }
    EXPECT_EQ(errno, 10);
}

TEST_F(ErrnoGuardTest_601, LargeErrnoValue_601) {
    errno = 9999;
    {
        Catch::ErrnoGuard guard;
        errno = 0;
    }
    EXPECT_EQ(errno, 9999);
}
