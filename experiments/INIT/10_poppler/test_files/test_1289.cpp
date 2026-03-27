#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-private.h"

namespace Poppler {

class DocumentDataTest_1289 : public ::testing::Test {
protected:
    DocumentDataTest_1289() {
        // Set up any necessary objects or mocks before each test
    }
    
    ~DocumentDataTest_1289() override {
        // Clean up after tests if needed
    }
};

// Normal Operation Tests

TEST_F(DocumentDataTest_1289, NotifyXRefReconstructed_NotifyCallbackCalled_1289) {
    // Arrange
    DocumentData docData("dummy/path", {}, {});
    bool callbackCalled = false;
    docData.xrefReconstructedCallback = [&callbackCalled]() {
        callbackCalled = true;
    };
    
    // Act
    docData.notifyXRefReconstructed();
    
    // Assert
    EXPECT_TRUE(callbackCalled) << "Expected callback to be called after notifyXRefReconstructed.";
}

TEST_F(DocumentDataTest_1289, NotifyXRefReconstructed_CallbackNotCalledWhenXRefReconstructed_1289) {
    // Arrange
    DocumentData docData("dummy/path", {}, {});
    docData.xrefReconstructedCallback = []() {
        FAIL() << "Callback should not be called.";
    };
    
    // Initially set xrefReconstructed to false
    docData.notifyXRefReconstructed();
    
    // Act
    docData.notifyXRefReconstructed();
    
    // Assert
    // No assertion needed as failing callback indicates the test failure if called
}

TEST_F(DocumentDataTest_1289, NotifyXRefReconstructed_RepeatedCallsOnlyTriggerCallbackOnce_1289) {
    // Arrange
    DocumentData docData("dummy/path", {}, {});
    int callbackCalls = 0;
    docData.xrefReconstructedCallback = [&callbackCalls]() {
        ++callbackCalls;
    };
    
    // Act
    docData.notifyXRefReconstructed(); // first call
    docData.notifyXRefReconstructed(); // second call
    
    // Assert
    EXPECT_EQ(callbackCalls, 1) << "Callback should be called only once even with multiple calls to notifyXRefReconstructed.";
}

// Boundary Condition Tests

TEST_F(DocumentDataTest_1289, NotifyXRefReconstructed_InitialStateXRefReconstructedFalse_1289) {
    // Arrange
    DocumentData docData("dummy/path", {}, {});
    
    // Act
    docData.notifyXRefReconstructed();
    
    // Assert
    // The callback should be called on first notification
    EXPECT_TRUE(docData.xrefReconstructed) << "Expected xrefReconstructed to be true after first notify.";
}

TEST_F(DocumentDataTest_1289, NotifyXRefReconstructed_NotifyBeforeCallbackAssignment_1289) {
    // Arrange
    DocumentData docData("dummy/path", {}, {});
    
    // Act
    docData.notifyXRefReconstructed();  // Notify before assigning the callback
    
    // Assert
    // The function should still complete without error
    EXPECT_TRUE(true) << "Function should handle notify before callback assignment gracefully.";
}

// Exceptional/Error Case Tests

TEST_F(DocumentDataTest_1289, NotifyXRefReconstructed_ExceptionIfCallbackThrows_1289) {
    // Arrange
    DocumentData docData("dummy/path", {}, {});
    docData.xrefReconstructedCallback = []() {
        throw std::runtime_error("Callback exception");
    };
    
    // Act & Assert
    EXPECT_THROW(docData.notifyXRefReconstructed(), std::runtime_error) 
        << "Expected exception to be thrown when the callback throws.";
}

TEST_F(DocumentDataTest_1289, NotifyXRefReconstructed_NoCallbackSet_1289) {
    // Arrange
    DocumentData docData("dummy/path", {}, {});
    
    // Act
    EXPECT_NO_THROW(docData.notifyXRefReconstructed()) << "Expected notifyXRefReconstructed to work even without a callback set.";
}

}  // namespace Poppler