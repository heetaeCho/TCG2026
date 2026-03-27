#include <gtest/gtest.h>
#include <pthread.h>
#include "XMP_Const.h"

// Assuming the prototype of the function is declared in the header somewhere
void XMP_ExitCriticalRegion(XMP_Mutex& mutex);

// Mock class to simulate the behavior of XMP_Mutex
class MockXMPMutex {
public:
    MOCK_METHOD(int, unlock, (), ());
};

class XMPExitCriticalRegionTest : public ::testing::Test {
protected:
    // Test fixture setup if needed
    XMP_Mutex mockMutex;
};

TEST_F(XMPExitCriticalRegionTest, UnlockMutexSuccessfully_1883) {
    // Arrange
    int err = 0;  // Simulate successful unlock
    EXPECT_CALL(mockMutex, unlock()).WillOnce(testing::Return(err));

    // Act
    // No specific return value to check from XMP_ExitCriticalRegion, but we need to ensure no exception is thrown.
    EXPECT_NO_THROW(XMP_ExitCriticalRegion(mockMutex));
}

TEST_F(XMPExitCriticalRegionTest, UnlockMutexFails_1884) {
    // Arrange
    int err = 1;  // Simulate failure in unlocking
    EXPECT_CALL(mockMutex, unlock()).WillOnce(testing::Return(err));

    // Act & Assert
    // Expect that XMP_Throw is called with the appropriate error message
    EXPECT_THROW(XMP_ExitCriticalRegion(mockMutex), std::runtime_error);
}

TEST_F(XMPExitCriticalRegionTest, ExceptionOnUnlockFailure_1885) {
    // Arrange
    int err = -1;  // Simulate an invalid failure code
    EXPECT_CALL(mockMutex, unlock()).WillOnce(testing::Return(err));

    // Act & Assert
    // Expect that XMP_Throw is called with the "XMP_ExitCriticalRegion - pthread_mutex_unlock failure" error message
    EXPECT_THROW(XMP_ExitCriticalRegion(mockMutex), std::runtime_error);
}