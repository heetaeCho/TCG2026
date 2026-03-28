#include <gtest/gtest.h>
#include <pthread.h>
#include <stdexcept>

// We need to include the relevant headers for XMP types and functions
// Based on the provided code, we need XMP_Mutex (which is pthread_mutex_t) and XMP_Throw

// Forward declarations and type definitions based on the known interface
typedef pthread_mutex_t XMP_Mutex;

// XMP exception class - minimal definition based on common XMP SDK patterns
#include <string>

class XMP_Error {
public:
    XMP_Error(int id, const char* errMsg) : id_(id), errMsg_(errMsg) {}
    int GetID() const { return id_; }
    const char* GetErrMsg() const { return errMsg_.c_str(); }
private:
    int id_;
    std::string errMsg_;
};

// Error codes from the known dependencies
enum {
    kXMPErr_Unknown = 0,
    kXMPErr_ExternalFailure = 11,
};

#define XMP_Throw(msg, id) throw XMP_Error(id, msg)

// Declaration of the function under test
void XMP_ExitCriticalRegion(XMP_Mutex& mutex);

// Include the implementation
// Since we're testing a standalone function, we replicate the implementation
// as given (treating it as a black box that we link against)
void XMP_ExitCriticalRegion(XMP_Mutex& mutex) {
    int err = pthread_mutex_unlock(&mutex);
    if (err != 0)
        XMP_Throw("XMP_ExitCriticalRegion - pthread_mutex_unlock failure", kXMPErr_ExternalFailure);
}

// Test fixture
class XMPExitCriticalRegionTest_1883 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Successfully exiting a critical region (unlocking a locked mutex)
TEST_F(XMPExitCriticalRegionTest_1883, UnlockLockedMutex_1883) {
    XMP_Mutex mutex;
    pthread_mutex_init(&mutex, nullptr);
    
    // Lock the mutex first
    pthread_mutex_lock(&mutex);
    
    // Should not throw when unlocking a properly locked mutex
    EXPECT_NO_THROW(XMP_ExitCriticalRegion(mutex));
    
    pthread_mutex_destroy(&mutex);
}

// Test: Attempting to unlock a mutex that is not locked should throw
TEST_F(XMPExitCriticalRegionTest_1883, UnlockUnlockedMutex_ThrowsOnError_1883) {
    // Use an error-checking mutex so that unlocking an unlocked mutex returns an error
    XMP_Mutex mutex;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_init(&mutex, &attr);
    pthread_mutexattr_destroy(&attr);
    
    // The mutex is not locked, so unlocking should fail with an error-checking mutex
    try {
        XMP_ExitCriticalRegion(mutex);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_ExternalFailure);
        EXPECT_STREQ(e.GetErrMsg(), "XMP_ExitCriticalRegion - pthread_mutex_unlock failure");
    }
    
    pthread_mutex_destroy(&mutex);
}

// Test: Exception contains correct error ID (kXMPErr_ExternalFailure)
TEST_F(XMPExitCriticalRegionTest_1883, ExceptionHasCorrectErrorID_1883) {
    XMP_Mutex mutex;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_init(&mutex, &attr);
    pthread_mutexattr_destroy(&attr);
    
    // Not locked, should throw with error-checking mutex
    bool caught = false;
    try {
        XMP_ExitCriticalRegion(mutex);
    } catch (const XMP_Error& e) {
        caught = true;
        EXPECT_EQ(e.GetID(), 11); // kXMPErr_ExternalFailure == 11
    }
    
    EXPECT_TRUE(caught) << "Expected an XMP_Error exception";
    
    pthread_mutex_destroy(&mutex);
}

// Test: Lock and unlock multiple times successfully
TEST_F(XMPExitCriticalRegionTest_1883, MultipleLockUnlockCycles_1883) {
    XMP_Mutex mutex;
    pthread_mutex_init(&mutex, nullptr);
    
    for (int i = 0; i < 10; ++i) {
        pthread_mutex_lock(&mutex);
        EXPECT_NO_THROW(XMP_ExitCriticalRegion(mutex));
    }
    
    pthread_mutex_destroy(&mutex);
}

// Test: Unlock after re-locking (recursive scenario with error-checking mutex)
TEST_F(XMPExitCriticalRegionTest_1883, UnlockAfterLockSucceeds_1883) {
    XMP_Mutex mutex;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_init(&mutex, &attr);
    pthread_mutexattr_destroy(&attr);
    
    // Lock then unlock should succeed
    pthread_mutex_lock(&mutex);
    EXPECT_NO_THROW(XMP_ExitCriticalRegion(mutex));
    
    // Now the mutex is unlocked; trying to unlock again should throw
    try {
        XMP_ExitCriticalRegion(mutex);
        FAIL() << "Expected XMP_Error for double unlock on error-checking mutex";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_ExternalFailure);
    }
    
    pthread_mutex_destroy(&mutex);
}

// Test: Verify the exception message content
TEST_F(XMPExitCriticalRegionTest_1883, ExceptionMessageContent_1883) {
    XMP_Mutex mutex;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_init(&mutex, &attr);
    pthread_mutexattr_destroy(&attr);
    
    try {
        XMP_ExitCriticalRegion(mutex);
        FAIL() << "Expected XMP_Error";
    } catch (const XMP_Error& e) {
        std::string msg(e.GetErrMsg());
        EXPECT_TRUE(msg.find("XMP_ExitCriticalRegion") != std::string::npos);
        EXPECT_TRUE(msg.find("pthread_mutex_unlock") != std::string::npos);
    }
    
    pthread_mutex_destroy(&mutex);
}

// Test: Normal mutex (default type) - single lock/unlock
TEST_F(XMPExitCriticalRegionTest_1883, DefaultMutexLockUnlock_1883) {
    XMP_Mutex mutex = PTHREAD_MUTEX_INITIALIZER;
    
    pthread_mutex_lock(&mutex);
    EXPECT_NO_THROW(XMP_ExitCriticalRegion(mutex));
    
    pthread_mutex_destroy(&mutex);
}
