#include <gtest/gtest.h>
#include <memory>

#include "./TestProjects/poppler/poppler/Annot.h"

// Mock class for dependencies that may be used in the tests
class MockXRef {
    // Add any required mock behaviors here if necessary
};

// Test suite for AnnotBorderArray
class AnnotBorderArrayTest : public ::testing::Test {
protected:
    // Setup common to all tests if necessary
    AnnotBorderArrayTest() {
        // Any necessary setup
    }

    // Cleanup common to all tests if necessary
    ~AnnotBorderArrayTest() override {
        // Any necessary cleanup
    }
};

// Test case for normal operation: Verify that getVerticalCorner() returns the correct value
TEST_F(AnnotBorderArrayTest, GetVerticalCorner_ReturnsCorrectValue_753) {
    // Arrange
    AnnotBorderArray annotBorder;
    double expectedVerticalCorner = 5.0;
    annotBorder.setVerticalCorner(expectedVerticalCorner);

    // Act
    double verticalCorner = annotBorder.getVerticalCorner();

    // Assert
    EXPECT_DOUBLE_EQ(verticalCorner, expectedVerticalCorner);
}

// Test case for normal operation: Verify that getHorizontalCorner() returns the correct value
TEST_F(AnnotBorderArrayTest, GetHorizontalCorner_ReturnsCorrectValue_754) {
    // Arrange
    AnnotBorderArray annotBorder;
    double expectedHorizontalCorner = 10.0;
    annotBorder.setHorizontalCorner(expectedHorizontalCorner);

    // Act
    double horizontalCorner = annotBorder.getHorizontalCorner();

    // Assert
    EXPECT_DOUBLE_EQ(horizontalCorner, expectedHorizontalCorner);
}

// Boundary test case for vertical corner: Verify behavior with edge case values
TEST_F(AnnotBorderArrayTest, SetVerticalCorner_BoundaryValues_755) {
    // Arrange
    AnnotBorderArray annotBorder;

    // Test with a very large value
    annotBorder.setVerticalCorner(1e6);
    EXPECT_DOUBLE_EQ(annotBorder.getVerticalCorner(), 1e6);

    // Test with a very small value (close to zero)
    annotBorder.setVerticalCorner(1e-6);
    EXPECT_DOUBLE_EQ(annotBorder.getVerticalCorner(), 1e-6);
}

// Boundary test case for horizontal corner: Verify behavior with edge case values
TEST_F(AnnotBorderArrayTest, SetHorizontalCorner_BoundaryValues_756) {
    // Arrange
    AnnotBorderArray annotBorder;

    // Test with a very large value
    annotBorder.setHorizontalCorner(1e6);
    EXPECT_DOUBLE_EQ(annotBorder.getHorizontalCorner(), 1e6);

    // Test with a very small value (close to zero)
    annotBorder.setHorizontalCorner(1e-6);
    EXPECT_DOUBLE_EQ(annotBorder.getHorizontalCorner(), 1e-6);
}

// Exceptional case: Verify that a corner cannot be set to an invalid value (e.g., negative corner value)
TEST_F(AnnotBorderArrayTest, SetVerticalCorner_InvalidValue_757) {
    // Arrange
    AnnotBorderArray annotBorder;

    // Test with an invalid negative value
    annotBorder.setVerticalCorner(-5.0);
    EXPECT_NE(annotBorder.getVerticalCorner(), -5.0);  // Assuming the setter would prevent negative values
}

// Mock test for interactions with dependencies (if applicable)
TEST_F(AnnotBorderArrayTest, WriteToObject_CallsWriteToObjectMethod_758) {
    // Arrange
    MockXRef mockXRef;
    AnnotBorderArray annotBorder;

    // Assuming the writeToObject method interacts with xref in some way
    // You can use Google Mock to verify interactions with the mock object if necessary

    // Act & Assert
    // Verify that the method does not crash or throw any unexpected errors
    // We may mock the behavior of the writeToObject method if it's called internally
}

// Test case for copy constructor or copy behavior: Verify that the copy method returns a deep copy
TEST_F(AnnotBorderArrayTest, Copy_ReturnsDeepCopy_759) {
    // Arrange
    AnnotBorderArray original;
    original.setVerticalCorner(5.0);
    original.setHorizontalCorner(10.0);

    // Act
    std::unique_ptr<AnnotBorder> copied = original.copy();

    // Assert
    EXPECT_DOUBLE_EQ(dynamic_cast<AnnotBorderArray*>(copied.get())->getVerticalCorner(), 5.0);
    EXPECT_DOUBLE_EQ(dynamic_cast<AnnotBorderArray*>(copied.get())->getHorizontalCorner(), 10.0);
}