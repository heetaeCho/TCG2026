#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
    #include "poppler-media.h"
}

// Mock class for external dependencies (if applicable)
class MockPopplerMediaClass : public _PopplerMediaClass {
public:
    MOCK_METHOD(void, finalize, (), ());
};

// TEST_F(poppler_media_class_init, NormalOperation_2030)
TEST_F(PopplerMediaClassInitTest_2030, NormalOperation_2030) {
    // Create a mock PopplerMediaClass object
    MockPopplerMediaClass mock_klass;
    
    // Setup expectations on the mock object (if necessary)
    // Example: EXPECT_CALL(mock_klass, finalize()).Times(1);
    
    // Call the function under test
    poppler_media_class_init(reinterpret_cast<PopplerMediaClass*>(&mock_klass));

    // Verify external interaction (finalize method should be invoked)
    EXPECT_CALL(mock_klass, finalize()).Times(1);
}

// TEST_F(poppler_media_class_init, NullClassPointer_2030)
TEST_F(PopplerMediaClassInitTest_2030, NullClassPointer_2030) {
    // Test with a nullptr (edge case for boundary conditions)
    ASSERT_NO_FATAL_FAILURE({
        poppler_media_class_init(nullptr);
    });
}

// TEST_F(poppler_media_class_init, VerifyFinalizeInteraction_2030)
TEST_F(PopplerMediaClassInitTest_2030, VerifyFinalizeInteraction_2030) {
    // Create a mock PopplerMediaClass object
    MockPopplerMediaClass mock_klass;
    
    // Setup the expectation for finalize call
    EXPECT_CALL(mock_klass, finalize()).Times(1);
    
    // Call the function under test
    poppler_media_class_init(reinterpret_cast<PopplerMediaClass*>(&mock_klass));
    
    // Ensure the finalize method is invoked
    testing::Mock::VerifyAndClearExpectations(&mock_klass);
}