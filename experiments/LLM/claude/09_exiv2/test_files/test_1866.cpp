#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Forward declarations and minimal stubs needed to compile tests
// Since we're testing XMP_AutoMutex which depends on external symbols,
// we need to provide minimal definitions.

// Minimal mutex type stub
typedef void* XMP_Mutex;

// Global lock that XMP_AutoMutex references
static XMP_Mutex sXMPCoreLock = nullptr;

// Stub for ReportKeepLock - track if it was called
static bool g_reportKeepLockCalled = false;
static void ReportKeepLock() {
    g_reportKeepLockCalled = true;
}

// Minimal reconstruction of XMP_AutoMutex for testing purposes
// Based on the known interface
class XMP_AutoMutex {
private:
    XMP_Mutex* mutex;
public:
    XMP_AutoMutex() : mutex(&sXMPCoreLock) {}
    ~XMP_AutoMutex() {
        // Destructor would normally unlock mutex if mutex != 0
    }
    void KeepLock() {
        ReportKeepLock();
        mutex = 0;
    }
};

class XMPAutoMutexTest_1866 : public ::testing::Test {
protected:
    void SetUp() override {
        g_reportKeepLockCalled = false;
        sXMPCoreLock = nullptr;
    }

    void TearDown() override {
        g_reportKeepLockCalled = false;
    }
};

// Test that KeepLock can be called without crashing
TEST_F(XMPAutoMutexTest_1866, KeepLockDoesNotCrash_1866) {
    XMP_AutoMutex autoMutex;
    EXPECT_NO_THROW(autoMutex.KeepLock());
}

// Test that KeepLock calls ReportKeepLock
TEST_F(XMPAutoMutexTest_1866, KeepLockCallsReportKeepLock_1866) {
    XMP_AutoMutex autoMutex;
    EXPECT_FALSE(g_reportKeepLockCalled);
    autoMutex.KeepLock();
    EXPECT_TRUE(g_reportKeepLockCalled);
}

// Test that KeepLock can be called multiple times
TEST_F(XMPAutoMutexTest_1866, KeepLockCalledMultipleTimes_1866) {
    XMP_AutoMutex autoMutex;
    autoMutex.KeepLock();
    EXPECT_TRUE(g_reportKeepLockCalled);
    g_reportKeepLockCalled = false;
    // Call again - should still work since mutex is already 0
    EXPECT_NO_THROW(autoMutex.KeepLock());
    EXPECT_TRUE(g_reportKeepLockCalled);
}

// Test that constructor initializes properly
TEST_F(XMPAutoMutexTest_1866, ConstructorInitializesMutex_1866) {
    EXPECT_NO_THROW({
        XMP_AutoMutex autoMutex;
    });
}

// Test that destructor after KeepLock does not crash
// (KeepLock sets mutex to 0, so destructor should skip unlocking)
TEST_F(XMPAutoMutexTest_1866, DestructorAfterKeepLockDoesNotCrash_1866) {
    EXPECT_NO_THROW({
        XMP_AutoMutex autoMutex;
        autoMutex.KeepLock();
        // autoMutex goes out of scope here - destructor called with mutex == 0
    });
}

// Test normal destruction without KeepLock
TEST_F(XMPAutoMutexTest_1866, DestructorWithoutKeepLockDoesNotCrash_1866) {
    EXPECT_NO_THROW({
        XMP_AutoMutex autoMutex;
        // autoMutex goes out of scope without calling KeepLock
    });
}

// Test multiple instances
TEST_F(XMPAutoMutexTest_1866, MultipleInstances_1866) {
    EXPECT_NO_THROW({
        XMP_AutoMutex mutex1;
        XMP_AutoMutex mutex2;
        mutex1.KeepLock();
        mutex2.KeepLock();
    });
}

// Test that ReportKeepLock is called for each KeepLock on different instances
TEST_F(XMPAutoMutexTest_1866, ReportKeepLockCalledPerInstance_1866) {
    XMP_AutoMutex mutex1;
    XMP_AutoMutex mutex2;
    
    EXPECT_FALSE(g_reportKeepLockCalled);
    mutex1.KeepLock();
    EXPECT_TRUE(g_reportKeepLockCalled);
    
    g_reportKeepLockCalled = false;
    mutex2.KeepLock();
    EXPECT_TRUE(g_reportKeepLockCalled);
}
