#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"

// Mock callback function type
using UnderlayCbkType = void (*)(PSOutputDev* psOut, void* data);

// Test fixture class
class PSOutputDevTest_1304 : public ::testing::Test {
protected:
    PSOutputDev* psOutputDev;
    
    // Setup before each test
    void SetUp() override {
        // Initialize PSOutputDev object with mock parameters
        psOutputDev = new PSOutputDev("test.ps", nullptr, "Test Title", 1, PSOutMode::psLevel3, 
                                      8, 11, true, false, 0, 0, 100, 100, PSForceRasterize::None, 
                                      false, nullptr, nullptr, PSLevel::psLevel3);
    }

    // Cleanup after each test
    void TearDown() override {
        delete psOutputDev;
    }
};

// Mock callback function
void mockUnderlayCallback(PSOutputDev* psOut, void* data) {
    // Just a dummy callback to test functionality
    EXPECT_EQ(psOut, nullptr);
    EXPECT_EQ(data, nullptr);
}

// Normal operation: Test setting the underlay callback function
TEST_F(PSOutputDevTest_1304, SetUnderlayCallback_Normal_1304) {
    // Arrange
    UnderlayCbkType cbk = mockUnderlayCallback;
    void* data = nullptr;

    // Act
    psOutputDev->setUnderlayCbk(cbk, data);

    // Assert
    // Since this function does not provide a direct observable behavior 
    // (it just sets the callback), we can't check internal state, 
    // but we can test that the function doesn't crash or throw.
    SUCCEED();  // Test passes if no exceptions or crashes occur
}

// Boundary Condition: Test setting underlay callback with null callback
TEST_F(PSOutputDevTest_1304, SetUnderlayCallback_NullCallback_1304) {
    // Arrange
    UnderlayCbkType cbk = nullptr;
    void* data = nullptr;

    // Act
    psOutputDev->setUnderlayCbk(cbk, data);

    // Assert
    SUCCEED();  // Test passes if no exceptions or crashes occur
}

// Boundary Condition: Test setting underlay callback with null data
TEST_F(PSOutputDevTest_1304, SetUnderlayCallback_NullData_1304) {
    // Arrange
    UnderlayCbkType cbk = mockUnderlayCallback;
    void* data = nullptr;

    // Act
    psOutputDev->setUnderlayCbk(cbk, data);

    // Assert
    SUCCEED();  // Test passes if no exceptions or crashes occur
}

// Exceptional case: Test setting underlay callback after object destruction
TEST_F(PSOutputDevTest_1304, SetUnderlayCallback_AfterDestruction_1304) {
    // Arrange
    psOutputDev->~PSOutputDev();  // Manually destroy the object
    UnderlayCbkType cbk = mockUnderlayCallback;
    void* data = nullptr;

    // Act & Assert
    EXPECT_DEATH(psOutputDev->setUnderlayCbk(cbk, data), ".*");  // Expect a crash since object is destroyed
}