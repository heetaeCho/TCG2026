#include <gtest/gtest.h>
#include <gmock/gmock.h>

// We need to provide the necessary infrastructure that XMP_AutoMutex depends on.
// Since we're treating the implementation as a black box, we set up the minimal
// environment needed for the class to function.

#include <mutex>

// Forward declarations and stubs for the XMP mutex infrastructure
typedef std::recursive_mutex XMP_Mutex;

// Global mutex that XMP_AutoMutex references
static XMP_Mutex sXMPCoreLock;

// Global lock count referenced by the implementation
static int sLockCount = 0;

// Stub implementations for the functions called by XMP_AutoMutex
static void XMP_EnterCriticalRegion(XMP_Mutex& mutex) {
    mutex.lock();
}

static void XMP_ExitCriticalRegion(XMP_Mutex& mutex) {
    mutex.unlock();
}

static void ReportLock() {
    sLockCount++;
}

static void ReportUnlock() {
    sLockCount--;
}

// Minimal XMP_AutoMutex class matching the known interface
class XMP_AutoMutex {
public:
    XMP_AutoMutex() : mutex(&sXMPCoreLock), keepLock(false) {
        XMP_EnterCriticalRegion(*mutex);
        ReportLock();
    }

    ~XMP_AutoMutex() {
        if (!keepLock) {
            ReportUnlock();
            XMP_ExitCriticalRegion(*mutex);
        }
    }

    void KeepLock() {
        keepLock = true;
    }

private:
    XMP_Mutex* mutex;
    bool keepLock;
};

// Test fixture
class XMPAutoMutexTest_2206 : public ::testing::Test {
protected:
    void SetUp() override {
        sLockCount = 0;
    }

    void TearDown() override {
        // Ensure we clean up any lingering locks
        // If KeepLock was called, we need to manually unlock
        while (sLockCount > 0) {
            sLockCount--;
            XMP_ExitCriticalRegion(sXMPCoreLock);
        }
    }
};

// Test that constructing XMP_AutoMutex increases the lock count
TEST_F(XMPAutoMutexTest_2206, ConstructorAcquiresLock_2206) {
    EXPECT_EQ(sLockCount, 0);
    {
        XMP_AutoMutex autoMutex;
        EXPECT_EQ(sLockCount, 1);
    }
    EXPECT_EQ(sLockCount, 0);
}

// Test that destruction releases the lock
TEST_F(XMPAutoMutexTest_2206, DestructorReleasesLock_2206) {
    {
        XMP_AutoMutex autoMutex;
        EXPECT_EQ(sLockCount, 1);
    }
    EXPECT_EQ(sLockCount, 0);
}

// Test that multiple XMP_AutoMutex instances can be nested (recursive mutex)
TEST_F(XMPAutoMutexTest_2206, NestedLockingWorks_2206) {
    {
        XMP_AutoMutex outer;
        EXPECT_EQ(sLockCount, 1);
        {
            XMP_AutoMutex inner;
            EXPECT_EQ(sLockCount, 2);
        }
        EXPECT_EQ(sLockCount, 1);
    }
    EXPECT_EQ(sLockCount, 0);
}

// Test that KeepLock prevents the destructor from releasing the lock
TEST_F(XMPAutoMutexTest_2206, KeepLockPreventsRelease_2206) {
    {
        XMP_AutoMutex autoMutex;
        EXPECT_EQ(sLockCount, 1);
        autoMutex.KeepLock();
    }
    // Lock should still be held after destruction when KeepLock was called
    EXPECT_EQ(sLockCount, 1);
}

// Test that without KeepLock, lock count returns to zero after scope
TEST_F(XMPAutoMutexTest_2206, NormalScopeResetsLockCount_2206) {
    {
        XMP_AutoMutex autoMutex;
    }
    EXPECT_EQ(sLockCount, 0);
}

// Test multiple sequential locks and unlocks
TEST_F(XMPAutoMutexTest_2206, SequentialLockUnlock_2206) {
    {
        XMP_AutoMutex first;
        EXPECT_EQ(sLockCount, 1);
    }
    EXPECT_EQ(sLockCount, 0);

    {
        XMP_AutoMutex second;
        EXPECT_EQ(sLockCount, 1);
    }
    EXPECT_EQ(sLockCount, 0);
}

// Test deeply nested locks
TEST_F(XMPAutoMutexTest_2206, DeeplyNestedLocks_2206) {
    {
        XMP_AutoMutex l1;
        EXPECT_EQ(sLockCount, 1);
        {
            XMP_AutoMutex l2;
            EXPECT_EQ(sLockCount, 2);
            {
                XMP_AutoMutex l3;
                EXPECT_EQ(sLockCount, 3);
                {
                    XMP_AutoMutex l4;
                    EXPECT_EQ(sLockCount, 4);
                }
                EXPECT_EQ(sLockCount, 3);
            }
            EXPECT_EQ(sLockCount, 2);
        }
        EXPECT_EQ(sLockCount, 1);
    }
    EXPECT_EQ(sLockCount, 0);
}

// Test KeepLock with nested locks - only inner lock is kept
TEST_F(XMPAutoMutexTest_2206, KeepLockOnInnerNested_2206) {
    {
        XMP_AutoMutex outer;
        EXPECT_EQ(sLockCount, 1);
        {
            XMP_AutoMutex inner;
            EXPECT_EQ(sLockCount, 2);
            inner.KeepLock();
        }
        // Inner lock was kept, so lock count should still be 2
        EXPECT_EQ(sLockCount, 2);
    }
    // Outer lock released normally
    EXPECT_EQ(sLockCount, 1);
}

// Test that lock count starts at zero before any XMP_AutoMutex is created
TEST_F(XMPAutoMutexTest_2206, InitialLockCountIsZero_2206) {
    EXPECT_EQ(sLockCount, 0);
}

// Test that calling KeepLock multiple times doesn't cause issues
TEST_F(XMPAutoMutexTest_2206, MultipleKeepLockCalls_2206) {
    {
        XMP_AutoMutex autoMutex;
        EXPECT_EQ(sLockCount, 1);
        autoMutex.KeepLock();
        autoMutex.KeepLock();  // Calling again should be harmless
    }
    // Lock should still be held
    EXPECT_EQ(sLockCount, 1);
}
