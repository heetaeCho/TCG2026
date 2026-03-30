#include <gtest/gtest.h>
#include "tiffimage.hpp"  // Include the appropriate header file for mimeType

namespace Exiv2 {

    // TEST_ID: 1728
    TEST_F(mimeTypeTest_1728, EqualOperatorComparison_1728) {
        // Arrange
        mimeType type1;
        mimeType type2;
        type1.comp = 5;
        type2.comp = 5;

        // Act & Assert
        EXPECT_TRUE(type1 == 5);   // Test if operator== correctly compares values
        EXPECT_TRUE(type2 == 5);   // Test if operator== correctly compares values
        EXPECT_FALSE(type1 == 10); // Test if operator== correctly identifies inequality
    }

    // TEST_ID: 1729
    TEST_F(mimeTypeTest_1729, TypeMemberValue_1729) {
        // Arrange
        mimeType type1;
        type1.comp = 5;
        type1.type = "image/tiff";

        // Act & Assert
        EXPECT_EQ(type1.type, "image/tiff");  // Test if 'type' member holds the correct value
    }

    // TEST_ID: 1730
    TEST_F(mimeTypeTest_1730, BoundaryConditions_1730) {
        // Arrange
        mimeType type1;
        mimeType type2;
        type1.comp = INT_MIN;  // Test with the smallest int value
        type2.comp = INT_MAX;  // Test with the largest int value

        // Act & Assert
        EXPECT_TRUE(type1 == INT_MIN);  // Check comparison with boundary value
        EXPECT_TRUE(type2 == INT_MAX);  // Check comparison with boundary value
        EXPECT_FALSE(type1 == INT_MAX); // Check comparison for inequality with boundary value
    }

    // TEST_ID: 1731
    TEST_F(mimeTypeTest_1731, ExceptionalCases_1731) {
        // Arrange
        mimeType type1;
        type1.comp = 0;

        // Act & Assert
        EXPECT_FALSE(type1 == -1);  // Test for non-matching values (edge case)
        EXPECT_FALSE(type1 == 1000); // Test for non-matching values (edge case)
    }
}