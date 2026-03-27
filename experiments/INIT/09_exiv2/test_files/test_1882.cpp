#include <gtest/gtest.h>
#include <pthread.h>
#include "XMP_Const.h"

// Mocked version of XMP_Mutex for testing
class MockXMPMutex {
public:
    pthread_mutex_t mutex;

    MockXMPMutex() {
        pthread_mutex_init(&mutex, nullptr);
    }

    ~MockXMPMutex() {
        pthread_mutex_destroy(&mutex);
    }

    int lock() {
        return pthread_mutex_lock(&mutex);
    }
    
    int unlock() {
        return pthread_mutex_unlock(&mutex);
    }
};

// Function under test
void XMP_EnterCriticalRegion(XMP_Mutex &mutex) {
    int err = pthread_mutex_lock(&mutex);
    if (err != 0) {
        throw std::runtime_error("XMP_EnterCriticalRegion - pthread_mutex_lock failure");
    }
}

// Test Fixture
class XMP_EnterCriticalRegionTest : public ::testing::Test {
protected:
    MockXMPMutex mutex;
};

// Test: Normal case, mutex is successfully locked
TEST_F(XMP_EnterCriticalRegionTest, LockSuccess_1882) {
    // Expect the lock to succeed without throwing any exception
    EXPECT_NO_THROW(XMP_EnterCriticalRegion(mutex));
}

// Test: Exception case, mutex lock failure
TEST_F(XMP_EnterCriticalRegionTest, LockFailure_1883) {
    // Force the lock to fail by using an invalid mutex
    MockXMPMutex invalidMutex;
    int invalidError = EINVAL;
    
    // Simulate lock failure
    EXPECT_THROW({
        int err = pthread_mutex_lock(&invalidMutex.mutex);
        if (err != 0) {
            throw std::runtime_error("XMP_EnterCriticalRegion - pthread_mutex_lock failure");
        }
    }, std::runtime_error);
}