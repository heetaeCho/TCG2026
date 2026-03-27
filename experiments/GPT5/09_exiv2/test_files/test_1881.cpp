#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <pthread.h>

// Mocking pthread_mutex_init to simulate different behaviors.
class MockMutex {
public:
    MOCK_METHOD(int, pthread_mutex_init, (XMP_Mutex * mutex, const pthread_mutexattr_t *attr), ());
};

class XMP_InitMutexTest : public testing::Test {
protected:
    MockMutex mockMutex;
};

// Test for normal operation
TEST_F(XMP_InitMutexTest, InitMutexSuccess_1881) {
    XMP_Mutex mutex;
    EXPECT_CALL(mockMutex, pthread_mutex_init(&mutex, nullptr))
        .WillOnce(testing::Return(0));  // Simulate successful mutex initialization

    bool result = XMP_InitMutex(&mutex);
    EXPECT_TRUE(result);
}

// Test for failure when pthread_mutex_init returns an error
TEST_F(XMP_InitMutexTest, InitMutexFailure_1882) {
    XMP_Mutex mutex;
    EXPECT_CALL(mockMutex, pthread_mutex_init(&mutex, nullptr))
        .WillOnce(testing::Return(1));  // Simulate failure in mutex initialization

    bool result = XMP_InitMutex(&mutex);
    EXPECT_FALSE(result);
}

// Test for boundary conditions (passing a null mutex)
TEST_F(XMP_InitMutexTest, InitMutexNullPointer_1883) {
    EXPECT_THROW(XMP_InitMutex(nullptr), std::invalid_argument);
}