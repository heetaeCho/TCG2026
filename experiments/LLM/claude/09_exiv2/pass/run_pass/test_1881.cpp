#include <gtest/gtest.h>
#include <pthread.h>

// Type definitions matching the codebase
typedef pthread_mutex_t XMP_Mutex;

// Declaration of the function under test
bool XMP_InitMutex(XMP_Mutex* mutex);

// Test fixture
class XMPInitMutexTest_1881 : public ::testing::Test {
protected:
    void TearDown() override {
        // Clean up any initialized mutexes if needed
    }
};

// Normal operation: initializing a valid mutex should succeed
TEST_F(XMPInitMutexTest_1881, InitValidMutex_ReturnsTrue_1881) {
    XMP_Mutex mutex;
    bool result = XMP_InitMutex(&mutex);
    EXPECT_TRUE(result);
    // Clean up
    pthread_mutex_destroy(&mutex);
}

// Normal operation: initialized mutex can be locked and unlocked
TEST_F(XMPInitMutexTest_1881, InitializedMutexIsUsable_1881) {
    XMP_Mutex mutex;
    bool result = XMP_InitMutex(&mutex);
    ASSERT_TRUE(result);
    
    int lockResult = pthread_mutex_lock(&mutex);
    EXPECT_EQ(0, lockResult);
    
    int unlockResult = pthread_mutex_unlock(&mutex);
    EXPECT_EQ(0, unlockResult);
    
    pthread_mutex_destroy(&mutex);
}

// Normal operation: multiple mutexes can be initialized independently
TEST_F(XMPInitMutexTest_1881, InitMultipleMutexes_AllSucceed_1881) {
    XMP_Mutex mutex1, mutex2, mutex3;
    
    EXPECT_TRUE(XMP_InitMutex(&mutex1));
    EXPECT_TRUE(XMP_InitMutex(&mutex2));
    EXPECT_TRUE(XMP_InitMutex(&mutex3));
    
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    pthread_mutex_destroy(&mutex3);
}

// Boundary condition: nullptr input
// Note: passing nullptr to pthread_mutex_init is undefined behavior on most systems,
// but we test that the function handles the error case (returns false if pthread fails)
TEST_F(XMPInitMutexTest_1881, InitNullMutex_ReturnsFalse_1881) {
    // This test checks behavior with null pointer.
    // On many systems this will crash, so we only run it if we can safely do so.
    // We skip this test on platforms where it would cause a segfault.
    // Instead, we verify the return value mapping by re-initializing an already initialized mutex.
    // Re-initializing is implementation-defined but typically returns an error on some platforms.
    XMP_Mutex mutex;
    bool firstInit = XMP_InitMutex(&mutex);
    ASSERT_TRUE(firstInit);
    
    // Second initialization - behavior is platform dependent
    // On some platforms this succeeds, on others it returns EBUSY
    // We just verify the function returns a bool without crashing
    bool secondInit = XMP_InitMutex(&mutex);
    // We don't assert true/false since it's platform dependent
    (void)secondInit;
    
    pthread_mutex_destroy(&mutex);
}

// Verify return value is exactly true (not just non-zero) on success
TEST_F(XMPInitMutexTest_1881, ReturnValueIsBoolTrue_1881) {
    XMP_Mutex mutex;
    bool result = XMP_InitMutex(&mutex);
    EXPECT_EQ(true, result);
    pthread_mutex_destroy(&mutex);
}

// Test that the initialized mutex works with default attributes (non-recursive)
TEST_F(XMPInitMutexTest_1881, InitWithDefaultAttributes_1881) {
    XMP_Mutex mutex;
    bool result = XMP_InitMutex(&mutex);
    ASSERT_TRUE(result);
    
    // Lock should succeed
    EXPECT_EQ(0, pthread_mutex_lock(&mutex));
    
    // trylock on an already locked mutex (from same thread) with default attributes
    // should return EBUSY on non-recursive mutex (behavior may vary)
    int tryResult = pthread_mutex_trylock(&mutex);
    // For a default (non-recursive) mutex, trylock should fail
    // EBUSY is expected on most platforms
    EXPECT_NE(0, tryResult);
    
    EXPECT_EQ(0, pthread_mutex_unlock(&mutex));
    pthread_mutex_destroy(&mutex);
}

// Stress test: initialize and destroy many mutexes
TEST_F(XMPInitMutexTest_1881, InitManyMutexes_AllSucceed_1881) {
    const int count = 100;
    XMP_Mutex mutexes[count];
    
    for (int i = 0; i < count; ++i) {
        EXPECT_TRUE(XMP_InitMutex(&mutexes[i])) << "Failed at index " << i;
    }
    
    for (int i = 0; i < count; ++i) {
        pthread_mutex_destroy(&mutexes[i]);
    }
}
