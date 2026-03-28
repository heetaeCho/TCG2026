#include <gtest/gtest.h>
#include <string>
#include <array>
#include "GooString.h"

// We need to declare the function under test since it's static in the .cc file.
// To test it, we either need to include the .cc or re-declare it.
// Since it's a static function in a .cc file, we include the source to access it.
// Alternatively, we can extract and test it directly.

// Forward declaration approach: include the implementation file to access the static function
// This is necessary because `print_matrix` is declared static (file-local linkage)
#include "HtmlOutputDev.cc"

class PrintMatrixTest_2731 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with identity matrix
TEST_F(PrintMatrixTest_2731, IdentityMatrix_2731)
{
    std::array<double, 6> mat = {1, 0, 0, 1, 0, 0};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[1 0 0 1 0 0]");
}

// Test with all zeros
TEST_F(PrintMatrixTest_2731, AllZeros_2731)
{
    std::array<double, 6> mat = {0, 0, 0, 0, 0, 0};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[0 0 0 0 0 0]");
}

// Test with positive integer values
TEST_F(PrintMatrixTest_2731, PositiveIntegers_2731)
{
    std::array<double, 6> mat = {1, 2, 3, 4, 5, 6};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[1 2 3 4 5 6]");
}

// Test with negative values
TEST_F(PrintMatrixTest_2731, NegativeValues_2731)
{
    std::array<double, 6> mat = {-1, -2, -3, -4, -5, -6};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[-1 -2 -3 -4 -5 -6]");
}

// Test with floating point values
TEST_F(PrintMatrixTest_2731, FloatingPointValues_2731)
{
    std::array<double, 6> mat = {1.5, 2.5, 3.5, 4.5, 5.5, 6.5};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[1.5 2.5 3.5 4.5 5.5 6.5]");
}

// Test with mixed positive and negative values
TEST_F(PrintMatrixTest_2731, MixedPositiveNegative_2731)
{
    std::array<double, 6> mat = {1, -2, 3.5, -4.5, 0, 100};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[1 -2 3.5 -4.5 0 100]");
}

// Test with very large values
TEST_F(PrintMatrixTest_2731, LargeValues_2731)
{
    std::array<double, 6> mat = {1e10, 2e10, 3e10, 4e10, 5e10, 6e10};
    std::string result = print_matrix(mat);
    // %g format will use scientific notation for very large numbers
    EXPECT_FALSE(result.empty());
    // Result should start with '[' and end with ']'
    EXPECT_EQ(result.front(), '[');
    EXPECT_EQ(result.back(), ']');
}

// Test with very small values
TEST_F(PrintMatrixTest_2731, VerySmallValues_2731)
{
    std::array<double, 6> mat = {0.001, 0.002, 0.003, 0.004, 0.005, 0.006};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[0.001 0.002 0.003 0.004 0.005 0.006]");
}

// Test result format - starts with '[' and ends with ']'
TEST_F(PrintMatrixTest_2731, FormatBrackets_2731)
{
    std::array<double, 6> mat = {7, 8, 9, 10, 11, 12};
    std::string result = print_matrix(mat);
    ASSERT_GE(result.size(), 2u);
    EXPECT_EQ(result.front(), '[');
    EXPECT_EQ(result.back(), ']');
}

// Test with a typical transformation matrix (scaling)
TEST_F(PrintMatrixTest_2731, ScalingMatrix_2731)
{
    std::array<double, 6> mat = {2, 0, 0, 2, 0, 0};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[2 0 0 2 0 0]");
}

// Test with a typical transformation matrix (translation)
TEST_F(PrintMatrixTest_2731, TranslationMatrix_2731)
{
    std::array<double, 6> mat = {1, 0, 0, 1, 100, 200};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[1 0 0 1 100 200]");
}

// Test with fractional values that have many decimal places
TEST_F(PrintMatrixTest_2731, PrecisionValues_2731)
{
    // %g typically uses up to 6 significant digits
    std::array<double, 6> mat = {1.23456, 2.34567, 3.45678, 4.56789, 5.67891, 6.78912};
    std::string result = print_matrix(mat);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.front(), '[');
    EXPECT_EQ(result.back(), ']');
}

// Test that result is not empty for any valid input
TEST_F(PrintMatrixTest_2731, ResultNotEmpty_2731)
{
    std::array<double, 6> mat = {0, 0, 0, 0, 0, 0};
    std::string result = print_matrix(mat);
    EXPECT_FALSE(result.empty());
}

// Test with values containing trailing zeros
TEST_F(PrintMatrixTest_2731, TrailingZeroValues_2731)
{
    std::array<double, 6> mat = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    std::string result = print_matrix(mat);
    // %g format strips trailing zeros
    EXPECT_EQ(result, "[1 2 3 4 5 6]");
}

// Test with very small negative values
TEST_F(PrintMatrixTest_2731, VerySmallNegativeValues_2731)
{
    std::array<double, 6> mat = {-0.001, -0.002, -0.003, -0.004, -0.005, -0.006};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[-0.001 -0.002 -0.003 -0.004 -0.005 -0.006]");
}
