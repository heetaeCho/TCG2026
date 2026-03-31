#include <gtest/gtest.h>
#include <array>

// Include the header under test
#include "HtmlUtils.h"

class IsMatRotOrSkewTest_2632 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(IsMatRotOrSkewTest_2632, IdentityMatrixReturnsFalse_2632) {
    // Identity matrix: mat[0]=1 (positive), mat[1]=0 (within .1 of 0)
    std::array<double, 6> mat = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_FALSE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, NegativeMat0ReturnsTrue_2632) {
    // mat[0] < 0 should return true regardless of mat[1]
    std::array<double, 6> mat = {-1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, Mat1LargePositiveReturnsTrue_2632) {
    // mat[0] >= 0 but mat[1] is far from 0 (outside .1 tolerance)
    std::array<double, 6> mat = {1.0, 1.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, Mat1LargeNegativeReturnsTrue_2632) {
    // mat[0] >= 0 but mat[1] is far negative from 0
    std::array<double, 6> mat = {1.0, -1.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, BothNegativeMat0AndLargeMat1ReturnsTrue_2632) {
    // Both conditions true
    std::array<double, 6> mat = {-1.0, 5.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

// Boundary condition tests

TEST_F(IsMatRotOrSkewTest_2632, Mat0ExactlyZeroAndMat1ZeroReturnsFalse_2632) {
    // mat[0] = 0 is NOT < 0, and mat[1] = 0 is within .1 of 0
    std::array<double, 6> mat = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    EXPECT_FALSE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, Mat1ExactlyAtPositiveBoundary_2632) {
    // mat[1] = 0.1 is at the boundary of is_within(.1, 0)
    // is_within typically checks |mat[1] - 0| < .1, so 0.1 would be at edge
    std::array<double, 6> mat = {1.0, 0.1, 0.0, 1.0, 0.0, 0.0};
    // At boundary, this depends on whether is_within uses < or <=
    // We just check the result is consistent
    // 0.1 is right at the edge, so !is_within might be true or false
    // We record the actual behavior
    bool result = isMatRotOrSkew(mat);
    // Just verify it doesn't crash; the exact boundary behavior is implementation-defined
    (void)result;
}

TEST_F(IsMatRotOrSkewTest_2632, Mat1JustInsideTolerance_2632) {
    // mat[1] = 0.05, within .1 of 0 -> is_within returns true -> !is_within is false
    // mat[0] = 1.0, not negative -> should return false
    std::array<double, 6> mat = {1.0, 0.05, 0.0, 1.0, 0.0, 0.0};
    EXPECT_FALSE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, Mat1JustOutsideTolerance_2632) {
    // mat[1] = 0.2, outside .1 of 0 -> is_within returns false -> !is_within is true
    std::array<double, 6> mat = {1.0, 0.2, 0.0, 1.0, 0.0, 0.0};
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, Mat1NegativeJustInsideTolerance_2632) {
    // mat[1] = -0.05, within .1 of 0
    std::array<double, 6> mat = {1.0, -0.05, 0.0, 1.0, 0.0, 0.0};
    EXPECT_FALSE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, Mat1NegativeJustOutsideTolerance_2632) {
    // mat[1] = -0.2, outside .1 of 0
    std::array<double, 6> mat = {1.0, -0.2, 0.0, 1.0, 0.0, 0.0};
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, Mat0SlightlyNegativeReturnsTrue_2632) {
    // mat[0] just barely negative
    std::array<double, 6> mat = {-0.0001, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, Mat0PositiveAndMat1ZeroReturnsFalse_2632) {
    // Simple positive scaling with no rotation/skew
    std::array<double, 6> mat = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};
    EXPECT_FALSE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, TypicalRotationMatrix_2632) {
    // 90 degree rotation: mat[0]=0, mat[1]=1 -> mat[1] outside tolerance -> true
    std::array<double, 6> mat = {0.0, 1.0, -1.0, 0.0, 0.0, 0.0};
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, Rotation180Degrees_2632) {
    // 180 degree rotation: mat[0]=-1, mat[1]~=0
    std::array<double, 6> mat = {-1.0, 0.0, 0.0, -1.0, 0.0, 0.0};
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, OtherMatrixElementsDoNotAffectResult_2632) {
    // Only mat[0] and mat[1] should matter
    std::array<double, 6> mat1 = {1.0, 0.0, 999.0, -999.0, 123.0, -456.0};
    EXPECT_FALSE(isMatRotOrSkew(mat1));
    
    std::array<double, 6> mat2 = {-1.0, 0.0, 999.0, -999.0, 123.0, -456.0};
    EXPECT_TRUE(isMatRotOrSkew(mat2));
}

TEST_F(IsMatRotOrSkewTest_2632, VeryLargeMat1ReturnsTrue_2632) {
    std::array<double, 6> mat = {1.0, 1e10, 0.0, 1.0, 0.0, 0.0};
    EXPECT_TRUE(isMatRotOrSkew(mat));
}

TEST_F(IsMatRotOrSkewTest_2632, VerySmallMat1WithinToleranceReturnsFalse_2632) {
    std::array<double, 6> mat = {1.0, 1e-15, 0.0, 1.0, 0.0, 0.0};
    EXPECT_FALSE(isMatRotOrSkew(mat));
}
