#include <gtest/gtest.h>



// Assuming the function getLum is part of a class or namespace, we will mock it up for testing purposes.

// Since the function is static and not part of a class, we can directly test it.



// Test fixture for getLum function

class GetLumTest_1588 : public ::testing::Test {

protected:

    // Additional setup if needed

};



// Test normal operation with typical values

TEST_F(GetLumTest_1588, NormalOperation_1588) {

    EXPECT_EQ(getLum(255, 0, 0), 76);   // Red

    EXPECT_EQ(getLum(0, 255, 0), 149);  // Green

    EXPECT_EQ(getLum(0, 0, 255), 30);   // Blue

}



// Test boundary conditions with minimum and maximum values

TEST_F(GetLumTest_1588, BoundaryConditions_1588) {

    EXPECT_EQ(getLum(0, 0, 0), 0);      // Black

    EXPECT_EQ(getLum(255, 255, 255), 255); // White

}



// Test exceptional or error cases (if applicable)

TEST_F(GetLumTest_1588, ExceptionalCases_1588) {

    // Since the function is deterministic and operates on fixed-size integers,

    // there are no exceptional cases to test here. All inputs within int range are valid.

}



// Test edge cases around boundary values

TEST_F(GetLumTest_1588, EdgeCasesAroundBoundaryValues_1588) {

    EXPECT_EQ(getLum(0, 0, 1), 3);

    EXPECT_EQ(getLum(0, 1, 0), 151);

    EXPECT_EQ(getLum(1, 0, 0), 77);

}



// Test specific combinations that might highlight edge behavior

TEST_F(GetLumTest_1588, SpecificCombinations_1588) {

    EXPECT_EQ(getLum(128, 128, 128), 128); // Gray

    EXPECT_EQ(getLum(64, 64, 64), 64);     // Dark gray

    EXPECT_EQ(getLum(192, 192, 192), 192);   // Light gray

}
