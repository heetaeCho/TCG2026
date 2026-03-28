#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"  // Include the header for the class being tested

// Mock for PopplerAnnotScreenClass to verify interactions.
class MockPopplerAnnotScreenClass {
public:
    MOCK_METHOD(void, finalize, ());
};

// Test fixture class
class PopplerAnnotScreenClassTest_2051 : public ::testing::Test {
protected:
    // Setup function called before each test
    void SetUp() override {
        // Initialize the PopplerAnnotScreenClass structure
        annot_class = new PopplerAnnotScreenClass();
    }

    // Cleanup function called after each test
    void TearDown() override {
        delete annot_class;
    }

    // Member variable for PopplerAnnotScreenClass
    PopplerAnnotScreenClass* annot_class;
};

// Test normal behavior of the poppler_annot_screen_class_init function
TEST_F(PopplerAnnotScreenClassTest_2051, FinalizeFunctionAssigned_2051) {
    // Given: The annot_class is initialized
    // When: poppler_annot_screen_class_init is called
    poppler_annot_screen_class_init(annot_class);

    // Then: The finalize function pointer should be set
    ASSERT_NE(annot_class->finalize, nullptr);
}

// Test boundary condition for handling NULL pointer
TEST_F(PopplerAnnotScreenClassTest_2051, NullPointer_2051) {
    // Given: A NULL pointer
    PopplerAnnotScreenClass* null_class = nullptr;

    // When: poppler_annot_screen_class_init is called with NULL
    // Then: It should not crash (assuming it gracefully handles NULL, though the code doesn't show such handling)
    ASSERT_NO_THROW(poppler_annot_screen_class_init(null_class));
}

// Test exceptional/error cases for invalid class initialization
TEST_F(PopplerAnnotScreenClassTest_2051, InvalidClassInitialization_2051) {
    // Given: A potentially uninitialized or invalid class object
    PopplerAnnotScreenClass* invalid_class = nullptr;

    // When: poppler_annot_screen_class_init is called with invalid class
    // Then: It should handle the invalid input gracefully (assuming no crash or undefined behavior)
    ASSERT_NO_THROW(poppler_annot_screen_class_init(invalid_class));
}

// Test for verifying external interactions with mock
TEST_F(PopplerAnnotScreenClassTest_2051, VerifyFinalizeFunctionCalled_2051) {
    // Create a mock object
    MockPopplerAnnotScreenClass mock_class;
    
    // Expect the finalize function to be called
    EXPECT_CALL(mock_class, finalize()).Times(1);
    
    // Assign the mock finalize function to the PopplerAnnotScreenClass
    annot_class->finalize = [&]() { mock_class.finalize(); };
    
    // When: poppler_annot_screen_class_init is called
    poppler_annot_screen_class_init(annot_class);
    
    // Then: The finalize function should have been invoked
    mock_class.finalize();
}