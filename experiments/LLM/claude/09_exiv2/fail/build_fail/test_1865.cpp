#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers for XMP_AutoMutex
#include "XMPCore_Impl.hpp"

class XMPAutoMutexTest_1865 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure the global lock is initialized if needed
    }

    void TearDown() override {
    }
};

// Test that XMP_AutoMutex can be constructed and destructed without crashing
TEST_F(XMPAutoMutexTest_1865, ConstructAndDestruct_1865) {
    EXPECT_NO_THROW({
        XMP_AutoMutex autoMutex;
    });
}

// Test that KeepLock prevents the destructor from unlocking
TEST_F(XMPAutoMutexTest_1865, KeepLockPreventsUnlock_1865) {
    EXPECT_NO_THROW({
        XMP_AutoMutex autoMutex;
        autoMutex.KeepLock();
        // Destructor should not call unlock since KeepLock was called
    });
    // After KeepLock, we need to manually manage the lock
    // Release it manually to avoid deadlock in subsequent tests
    XMP_ExitCriticalRegion(sXMPCoreLock);
}

// Test that destructor properly resets mutex to null (no double unlock)
TEST_F(XMPAutoMutexTest_1865, DestructorResetsState_1865) {
    EXPECT_NO_THROW({
        XMP_AutoMutex autoMutex;
        // Let destructor handle cleanup
    });
    // Verify we can create another AutoMutex without deadlock
    EXPECT_NO_THROW({
        XMP_AutoMutex autoMutex2;
    });
}

// Test multiple sequential lock/unlock cycles work correctly
TEST_F(XMPAutoMutexTest_1865, MultipleSequentialLockUnlock_1865) {
    for (int i = 0; i < 5; ++i) {
        EXPECT_NO_THROW({
            XMP_AutoMutex autoMutex;
        });
    }
}

// Test that KeepLock can be called and object still destructs safely
TEST_F(XMPAutoMutexTest_1865, KeepLockDestructorSafe_1865) {
    {
        XMP_AutoMutex autoMutex;
        autoMutex.KeepLock();
        // mutex is set to 0, destructor should be a no-op
    }
    // Manually release the lock that was kept
    XMP_ExitCriticalRegion(sXMPCoreLock);
}

// Test nested scope behavior - inner scope releases before outer is created
TEST_F(XMPAutoMutexTest_1865, SequentialScopeRelease_1865) {
    EXPECT_NO_THROW({
        {
            XMP_AutoMutex autoMutex1;
        }
        {
            XMP_AutoMutex autoMutex2;
        }
    });
}

// Test that KeepLock called multiple times doesn't cause issues
TEST_F(XMPAutoMutexTest_1865, KeepLockCalledMultipleTimes_1865) {
    EXPECT_NO_THROW({
        XMP_AutoMutex autoMutex;
        autoMutex.KeepLock();
        autoMutex.KeepLock(); // Calling again should be safe
    });
    // Manually release the kept lock
    XMP_ExitCriticalRegion(sXMPCoreLock);
}
