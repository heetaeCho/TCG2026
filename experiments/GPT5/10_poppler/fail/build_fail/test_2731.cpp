// File: print_matrix_test_2731.cc
#include <gtest/gtest.h>

#include <array>
#include <string>

// NOTE: print_matrix() is a static function in HtmlOutputDev.cc (internal linkage).
// To test it as a black box without modifying production code, we include the .cc
// so the function is available in this translation unit.
#include "utils/HtmlOutputDev.cc"

namespace {

using Mat6 = std::array<double, 6>;

TEST(PrintMatrixTest_2731, FormatsSimpleIntegers_2731)
{
    const Mat6 mat{{1, 2, 3, 4, 5, 6}};
    const std::string out = print_matrix(mat);
    EXPECT_EQ(out, "[1 2 3 4 5 6]");
}

TEST(PrintMatrixTest_2731, FormatsZerosAndNegatives_2731)
{
    const Mat6 mat{{0, -1, 2, -3, 0, 4}};
    const std::string out = print_matrix(mat);
    EXPECT_EQ(out, "[0 -1 2 -3 0 4]");
}

TEST(PrintMatrixTest_2731, FormatsFractionalValuesWithGeneralFormat_2731)
{
    const Mat6 mat{{0.5, 1.25, -2.5, 3.0, 10.75, -0.125}};
    const std::string out = print_matrix(mat);

    // With %g-style formatting, 3.0 should typically appear as "3" (not "3.0").
    EXPECT_EQ(out, "[0.5 1.25 -2.5 3 10.75 -0.125]");
}

TEST(PrintMatrixTest_2731, UsesScientificNotationForLargeMagnitude_2731)
{
    const Mat6 mat{{1e10, -1e10, 1e-10, -1e-10, 123456789.0, -123456789.0}};
    const std::string out = print_matrix(mat);

    // We avoid over-assuming exact exponent formatting beyond %g conventions.
    // Still, it should contain 'e' for very large/small values.
    EXPECT_NE(out.find('e'), std::string::npos);

    // Basic shape check.
    EXPECT_TRUE(out.size() >= 2);
    EXPECT_EQ(out.front(), '[');
    EXPECT_EQ(out.back(), ']');
}

TEST(PrintMatrixTest_2731, DoesNotModifyInputArray_2731)
{
    Mat6 mat{{1, 2, 3, 4, 5, 6}};
    const Mat6 before = mat;

    (void)print_matrix(mat);

    EXPECT_EQ(mat, before);
}

TEST(PrintMatrixTest_2731, FormatsNegativeZeroConsistently_2731)
{
    // -0.0 is observable in some formatting paths; we only require that the
    // function returns a well-formed bracketed list with six entries.
    const Mat6 mat{{-0.0, 0.0, -0.0, 0.0, -0.0, 0.0}};
    const std::string out = print_matrix(mat);

    EXPECT_FALSE(out.empty());
    EXPECT_EQ(out.front(), '[');
    EXPECT_EQ(out.back(), ']');

    // Must contain 5 spaces separating 6 values: "[v0 v1 v2 v3 v4 v5]"
    int space_count = 0;
    for (char c : out) {
        if (c == ' ') {
            ++space_count;
        }
    }
    EXPECT_EQ(space_count, 5);
}

} // namespace