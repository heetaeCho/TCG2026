#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPCore_Impl.hpp"

// Mocking the mutex-related interactions
class MockXMP_Mutex : public XMP_Mutex {
public:
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
    MOCK_METHOD(void, ReportUnlock, (), ());
};

class XMP_AutoMutexTest : public ::testing::Test {
protected:
    MockXMP_Mutex mockMutex;
    XMP_AutoMutex* autoMutex;

    void SetUp() override {
        // Using the mock mutex in the XMP_AutoMutex
        autoMutex = new XMP_AutoMutex(&mockMutex);
    }

    void TearDown() override {
        delete autoMutex;
    }
};

// Test case for normal operation: Constructor and Destructor
TEST_F(XMP_AutoMutexTest, ConstructorAndDestructor_1865) {
    // Verify that the mutex lock is called during construction
    EXPECT_CALL(mockMutex, Lock()).Times(1);
    
    // Create the auto mutex which will lock the mutex
    XMP_AutoMutex autoMutexInstance(&mockMutex);

    // Verify that the mutex unlock is called during destruction
    EXPECT_CALL(mockMutex, Unlock()).Times(1);

    // The autoMutex instance will be destroyed here, so the unlock should be called
}

// Test case for boundary condition: Locking and unlocking multiple times
TEST_F(XMP_AutoMutexTest, MultipleLocksAndUnlocks_1866) {
    // Set up expectations for multiple lock and unlock operations
    EXPECT_CALL(mockMutex, Lock()).Times(2);
    EXPECT_CALL(mockMutex, Unlock()).Times(2);

    // Lock twice using the XMP_AutoMutex
    XMP_AutoMutex autoMutexInstance1(&mockMutex);
    XMP_AutoMutex autoMutexInstance2(&mockMutex);
    
    // The destructors will unlock the mutex
}

// Test case for exceptional case: Invalid mutex pointer passed
TEST_F(XMP_AutoMutexTest, InvalidMutexPointer_1867) {
    // Pass a null mutex pointer, which should not affect the behavior but is a boundary case
    EXPECT_THROW({
        XMP_AutoMutex autoMutexInstance(nullptr);
    }, std::invalid_argument);
}

// Test case for verifying external interactions: Lock and unlock calls in the destructor
TEST_F(XMP_AutoMutexTest, VerifyExternalInteractions_1868) {
    // Expect that Lock is called once when autoMutex is constructed
    EXPECT_CALL(mockMutex, Lock()).Times(1);

    // Create an instance of the auto mutex, which should trigger Lock
    XMP_AutoMutex autoMutexInstance(&mockMutex);

    // Expect that Unlock is called once during the destruction
    EXPECT_CALL(mockMutex, Unlock()).Times(1);
}

// Test case for verifying behavior when the mutex is already locked
TEST_F(XMP_AutoMutexTest, MutexAlreadyLocked_1869) {
    // Verify that the lock count is correctly incremented and decremented
    EXPECT_CALL(mockMutex, Lock()).Times(1);  // First Lock
    EXPECT_CALL(mockMutex, Unlock()).Times(1);  // Unlock after destruction
    
    // Lock mutex once
    XMP_AutoMutex autoMutexInstance1(&mockMutex);
    
    // Lock it again (simulating recursive lock scenario)
    EXPECT_CALL(mockMutex, Lock()).Times(1);  // Second Lock
    XMP_AutoMutex autoMutexInstance2(&mockMutex);

    // The second destructor will unlock the mutex again
}