#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"
#include "poppler-private.h"

class PopplerAnnotTest_2067 : public ::testing::Test {
protected:
    PopplerAnnot *poppler_annot;
    
    // Mock class for Annot used in PopplerAnnot
    class MockAnnot {
    public:
        MOCK_METHOD(PopplerAnnotFlag, getFlags, (), ());
    };
    
    void SetUp() override {
        // Initialize PopplerAnnot with a mock Annot object
        poppler_annot = new PopplerAnnot();
        poppler_annot->annot = std::make_shared<MockAnnot>();
    }

    void TearDown() override {
        delete poppler_annot;
    }
};

// Test case for normal operation
TEST_F(PopplerAnnotTest_2067, popplerAnnotGetFlags_NormalOperation_2067) {
    // Arrange
    PopplerAnnotFlag expected_flag = PopplerAnnotFlag::POPPLER_ANNOT_FLAG_NONE;
    EXPECT_CALL(*poppler_annot->annot, getFlags()).WillOnce(::testing::Return(expected_flag));

    // Act
    PopplerAnnotFlag result = poppler_annot_get_flags(poppler_annot);

    // Assert
    EXPECT_EQ(result, expected_flag);
}

// Test case for null PopplerAnnot pointer (boundary condition)
TEST_F(PopplerAnnotTest_2067, popplerAnnotGetFlags_NullAnnotPointer_2067) {
    // Arrange
    poppler_annot = nullptr;

    // Act and Assert
    EXPECT_EQ(poppler_annot_get_flags(poppler_annot), (PopplerAnnotFlag)0);
}

// Test case for invalid PopplerAnnot object (boundary condition)
TEST_F(PopplerAnnotTest_2067, popplerAnnotGetFlags_InvalidAnnotObject_2067) {
    // Arrange
    PopplerAnnot invalid_annot;
    invalid_annot.annot = nullptr;  // Invalid Annot pointer

    // Act and Assert
    EXPECT_EQ(poppler_annot_get_flags(&invalid_annot), (PopplerAnnotFlag)0);
}

// Test case for exception handling or errors when getFlags fails (mocking behavior)
TEST_F(PopplerAnnotTest_2067, popplerAnnotGetFlags_ErrorHandling_2067) {
    // Arrange
    EXPECT_CALL(*poppler_annot->annot, getFlags()).WillOnce(::testing::Throw(std::runtime_error("Error retrieving flags")));

    // Act and Assert
    EXPECT_EQ(poppler_annot_get_flags(poppler_annot), (PopplerAnnotFlag)0);
}