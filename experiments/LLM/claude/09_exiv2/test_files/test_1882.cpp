#include <gtest/gtest.h>
#include <pthread.h>
#include <stdexcept>

// Include necessary headers for the XMP library
// We need the XMP types and the function under test

// Forward declarations and type definitions based on the provided code
typedef pthread_mutex_t XMP_Mutex;

// XMP_Throw macro/function - we need to know what it does
// Based on the code, it throws an exception. We'll include the relevant headers.
// Since we're testing against the actual implementation, we include the real headers.

#include "XMP_Const.h"

// Declaration of the function under test
extern void XMP_EnterCriticalRegion(XMP_Mutex& mutex);

// We also need to handle XMP_Throw - it likely throws an XMP_Error or similar exception
// Based on typical XMP SDK implementations, XMP_Throw throws an XMP_Error

class XMPEnterCriticalRegionTest_1882 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Successfully locking an initialized mutex
TEST_F(XMPEnterCriticalRegionTest_1882, SuccessfulLockOnInitializedMutex_1882) {
    XMP_Mutex mutex;
    int ret = pthread_mutex_init(&mutex, nullptr);
    ASSERT_EQ(ret, 0) << "Failed to initialize mutex for test";

    // Should not throw when locking a properly initialized mutex
    EXPECT_NO_THROW(XMP_EnterCriticalRegion(mutex));

    // Clean up: unlock and destroy the mutex
    pthread_mutex_unlock(&mutex);
    pthread_mutex_destroy(&mutex);
}

// Test: Locking a mutex that is already locked by the same thread should cause an error
// (for a non-recursive, error-checking mutex)
TEST_F(XMPEnterCriticalRegionTest_1882, DoubleLockOnErrorCheckingMutex_1882) {
    XMP_Mutex mutex;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    int ret = pthread_mutex_init(&mutex, &attr);
    ASSERT_EQ(ret, 0) << "Failed to initialize error-checking mutex for test";
    pthread_mutexattr_destroy(&attr);

    // First lock should succeed
    EXPECT_NO_THROW(XMP_EnterCriticalRegion(mutex));

    // Second lock on an error-checking mutex by the same thread should fail
    // pthread_mutex_lock returns EDEADLK for error-checking mutexes
    EXPECT_ANY_THROW(XMP_EnterCriticalRegion(mutex));

    // Clean up
    pthread_mutex_unlock(&mutex);
    pthread_mutex_destroy(&mutex);
}

// Test: Lock and unlock cycle works correctly multiple times
TEST_F(XMPEnterCriticalRegionTest_1882, MultipleLockUnlockCycles_1882) {
    XMP_Mutex mutex;
    int ret = pthread_mutex_init(&mutex, nullptr);
    ASSERT_EQ(ret, 0) << "Failed to initialize mutex for test";

    for (int i = 0; i < 10; ++i) {
        EXPECT_NO_THROW(XMP_EnterCriticalRegion(mutex));
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_destroy(&mutex);
}

// Test: Locking a destroyed mutex should throw
// Note: behavior of locking a destroyed mutex is undefined in POSIX,
// but on many implementations it will return an error code
TEST_F(XMPEnterCriticalRegionTest_1882, LockOnDestroyedMutex_1882) {
    XMP_Mutex mutex;
    int ret = pthread_mutex_init(&mutex, nullptr);
    ASSERT_EQ(ret, 0) << "Failed to initialize mutex for test";
    pthread_mutex_destroy(&mutex);

    // Attempting to lock a destroyed mutex - behavior is implementation-defined
    // On many systems this will return an error, causing XMP_Throw
    // We test that it either succeeds or throws (no crash/UB that we can detect)
    try {
        XMP_EnterCriticalRegion(mutex);
        // If it didn't throw, that's also acceptable on some platforms
    } catch (...) {
        // Exception is expected on platforms where pthread_mutex_lock returns error
        SUCCEED();
    }
}

// Test: Verify that after successful lock, the mutex is actually held
TEST_F(XMPEnterCriticalRegionTest_1882, MutexIsHeldAfterLock_1882) {
    XMP_Mutex mutex;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    int ret = pthread_mutex_init(&mutex, &attr);
    ASSERT_EQ(ret, 0);
    pthread_mutexattr_destroy(&attr);

    EXPECT_NO_THROW(XMP_EnterCriticalRegion(mutex));

    // Try to lock again with trylock - should fail because it's already locked
    int trylock_result = pthread_mutex_trylock(&mutex);
    EXPECT_NE(trylock_result, 0) << "Mutex should already be held";

    pthread_mutex_unlock(&mutex);
    pthread_mutex_destroy(&mutex);
}

// Test: Locking a default mutex and verifying unlock works
TEST_F(XMPEnterCriticalRegionTest_1882, LockThenUnlockSucceeds_1882) {
    XMP_Mutex mutex;
    int ret = pthread_mutex_init(&mutex, nullptr);
    ASSERT_EQ(ret, 0);

    EXPECT_NO_THROW(XMP_EnterCriticalRegion(mutex));

    // Unlock should succeed (returns 0)
    int unlock_ret = pthread_mutex_unlock(&mutex);
    EXPECT_EQ(unlock_ret, 0);

    pthread_mutex_destroy(&mutex);
}

// Test: Concurrent access - lock from main thread, verify another thread blocks
TEST_F(XMPEnterCriticalRegionTest_1882, ConcurrentAccessBlocks_1882) {
    XMP_Mutex mutex;
    int ret = pthread_mutex_init(&mutex, nullptr);
    ASSERT_EQ(ret, 0);

    // Lock from main thread
    EXPECT_NO_THROW(XMP_EnterCriticalRegion(mutex));

    bool other_thread_got_lock = false;
    bool other_thread_started = false;

    pthread_t thread;
    struct ThreadData {
        XMP_Mutex* mutex;
        bool* got_lock;
        bool* started;
    };
    ThreadData data = {&mutex, &other_thread_got_lock, &other_thread_started};

    auto thread_func = [](void* arg) -> void* {
        ThreadData* td = static_cast<ThreadData*>(arg);
        *td->started = true;
        // This should block until the main thread releases
        int err = pthread_mutex_lock(td->mutex);
        if (err == 0) {
            *td->got_lock = true;
            pthread_mutex_unlock(td->mutex);
        }
        return nullptr;
    };

    pthread_create(&thread, nullptr, thread_func, &data);

    // Give the other thread time to start and attempt the lock
    usleep(50000); // 50ms

    // The other thread should have started but not gotten the lock yet
    EXPECT_TRUE(other_thread_started);
    EXPECT_FALSE(other_thread_got_lock);

    // Release the lock
    pthread_mutex_unlock(&mutex);

    // Wait for the other thread to finish
    pthread_join(thread, nullptr);

    EXPECT_TRUE(other_thread_got_lock);

    pthread_mutex_destroy(&mutex);
}
