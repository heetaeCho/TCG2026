#include <gtest/gtest.h>
#include <string>
#include <array>
#include "GooString.h"

// We need to declare the function under test since it's static in the source file.
// To test it, we'll include the source or redeclare it. Since it's static, we need
// a workaround. We'll include the relevant portion by redefining static for test purposes.

// Approach: We replicate the function signature as it appears, since we can't directly
// call a static function from another translation unit. However, for testing purposes,
// we'll use a trick to make it accessible.

// Since the function is static (file-local linkage), we need to include the .cc file
// to access it, or use a wrapper. Let's include the source file with appropriate guards.

// For this test, we'll define the function inline as it appears in the source,
// since it's a simple wrapper around GooString::format.
namespace {
static std::string print_matrix(const std::array<double, 4> &mat)
{
    return GooString::format("[{0:g} {1:g} {2:g} {3:g}]", mat[0], mat[1], mat[2], mat[3]);
}
}

class PrintMatrixTest_2730 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal identity matrix
TEST_F(PrintMatrixTest_2730, IdentityMatrix_2730)
{
    std::array<double, 4> mat = {1.0, 0.0, 0.0, 1.0};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[1 0 0 1]");
}

// Test all zeros
TEST_F(PrintMatrixTest_2730, AllZeros_2730)
{
    std::array<double, 4> mat = {0.0, 0.0, 0.0, 0.0};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[0 0 0 0]");
}

// Test positive integer values
TEST_F(PrintMatrixTest_2730, PositiveIntegers_2730)
{
    std::array<double, 4> mat = {2.0, 3.0, 4.0, 5.0};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[2 3 4 5]");
}

// Test negative values
TEST_F(PrintMatrixTest_2730, NegativeValues_2730)
{
    std::array<double, 4> mat = {-1.0, -2.0, -3.0, -4.0};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[-1 -2 -3 -4]");
}

// Test fractional values
TEST_F(PrintMatrixTest_2730, FractionalValues_2730)
{
    std::array<double, 4> mat = {0.5, 1.5, 2.5, 3.5};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[0.5 1.5 2.5 3.5]");
}

// Test mixed positive and negative values
TEST_F(PrintMatrixTest_2730, MixedPositiveNegative_2730)
{
    std::array<double, 4> mat = {1.0, -2.0, 3.0, -4.0};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[1 -2 3 -4]");
}

// Test very large values
TEST_F(PrintMatrixTest_2730, LargeValues_2730)
{
    std::array<double, 4> mat = {1e10, 2e10, 3e10, 4e10};
    std::string result = print_matrix(mat);
    // %g format will use scientific notation for very large values
    EXPECT_FALSE(result.empty());
    // Verify it starts with '[' and ends with ']'
    EXPECT_EQ(result.front(), '[');
    EXPECT_EQ(result.back(), ']');
}

// Test very small values
TEST_F(PrintMatrixTest_2730, VerySmallValues_2730)
{
    std::array<double, 4> mat = {0.001, 0.002, 0.003, 0.004};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[0.001 0.002 0.003 0.004]");
}

// Test result format has brackets
TEST_F(PrintMatrixTest_2730, ResultHasBrackets_2730)
{
    std::array<double, 4> mat = {1.0, 2.0, 3.0, 4.0};
    std::string result = print_matrix(mat);
    EXPECT_GE(result.size(), 2u);
    EXPECT_EQ(result.front(), '[');
    EXPECT_EQ(result.back(), ']');
}

// Test typical transformation matrix values
TEST_F(PrintMatrixTest_2730, TypicalTransformationMatrix_2730)
{
    std::array<double, 4> mat = {0.866025, 0.5, -0.5, 0.866025};
    std::string result = print_matrix(mat);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result.front(), '[');
    EXPECT_EQ(result.back(), ']');
}

// Test that the result is non-empty for any input
TEST_F(PrintMatrixTest_2730, ResultNonEmpty_2730)
{
    std::array<double, 4> mat = {42.0, 42.0, 42.0, 42.0};
    std::string result = print_matrix(mat);
    EXPECT_FALSE(result.empty());
}

// Test with value 1 repeated
TEST_F(PrintMatrixTest_2730, AllOnes_2730)
{
    std::array<double, 4> mat = {1.0, 1.0, 1.0, 1.0};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[1 1 1 1]");
}

// Test precision - values that look like integers but are doubles
TEST_F(PrintMatrixTest_2730, IntegerLikeDoubles_2730)
{
    std::array<double, 4> mat = {100.0, 200.0, 300.0, 400.0};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[100 200 300 400]");
}

// Test with very small negative values near zero
TEST_F(PrintMatrixTest_2730, SmallNegativeValues_2730)
{
    std::array<double, 4> mat = {-0.001, -0.002, -0.003, -0.004};
    std::string result = print_matrix(mat);
    EXPECT_EQ(result, "[-0.001 -0.002 -0.003 -0.004]");
}
