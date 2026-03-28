#include <gtest/gtest.h>
#include <memory>
#include "Annot.h"

// Mock class for testing
class MockAnnotBorder : public AnnotBorder {
public:
    MOCK_METHOD0(get, AnnotBorder*());
};

// Test class for Annot
class AnnotTest_791 : public ::testing::Test {
protected:
    // Setup and teardown logic can go here
    void SetUp() override {
        // Setup Annot instance if needed
    }

    void TearDown() override {
        // Cleanup after each test if needed
    }
};

// Normal operation test for getBorder function
TEST_F(AnnotTest_791, GetBorder_ValidAnnot_791) {
    // Create a mock AnnotBorder to return
    std::unique_ptr<MockAnnotBorder> mockBorder = std::make_unique<MockAnnotBorder>();
    Annot annot;

    // Use gmock to verify that the correct border is returned
    EXPECT_CALL(*mockBorder, get()).Times(1);

    // Set the border of annot
    annot.setBorder(std::move(mockBorder));

    // Verify that the border is correctly returned
    ASSERT_EQ(annot.getBorder(), mockBorder.get());
}

// Boundary condition for getBorder function when the border is null
TEST_F(AnnotTest_791, GetBorder_NullBorder_791) {
    Annot annot;

    // Verify that when no border is set, the return value is nullptr
    ASSERT_EQ(annot.getBorder(), nullptr);
}

// Exceptional case test for getBorder if the border is invalid (mocked as nullptr)
TEST_F(AnnotTest_791, GetBorder_InvalidBorder_791) {
    std::unique_ptr<MockAnnotBorder> mockBorder = nullptr;  // Simulating invalid border
    Annot annot;

    // Set invalid border
    annot.setBorder(std::move(mockBorder));

    // Expect nullptr when attempting to get an invalid border
    ASSERT_EQ(annot.getBorder(), nullptr);
}

// Test the border with a non-null AnnotBorder
TEST_F(AnnotTest_791, GetBorder_ValidPointer_791) {
    // Create a mock AnnotBorder to return
    std::unique_ptr<MockAnnotBorder> mockBorder = std::make_unique<MockAnnotBorder>();
    Annot annot;

    // Set the mock border
    annot.setBorder(std::move(mockBorder));

    // Expect the mock border to be returned
    ASSERT_NE(annot.getBorder(), nullptr);
}

// Edge case test for setBorder with a nullptr
TEST_F(AnnotTest_791, SetBorder_Nullptr_791) {
    Annot annot;

    // Set a nullptr border
    annot.setBorder(nullptr);

    // Verify the border is null after setting nullptr
    ASSERT_EQ(annot.getBorder(), nullptr);
}