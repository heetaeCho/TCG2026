#include <gtest/gtest.h>
#include <array>
#include <memory>
#include <vector>

#include "GfxState.h"

class GfxFunctionShadingTest_515 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getMatrix returns a reference to an array of 6 doubles
TEST_F(GfxFunctionShadingTest_515, GetMatrixReturnsArrayOfSixDoubles_515) {
    // We need to construct a GfxFunctionShading object to test getMatrix.
    // Using the constructor that takes basic parameters.
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    const std::array<double, 6> &result = shading.getMatrix();
    EXPECT_EQ(result.size(), 6u);
    EXPECT_DOUBLE_EQ(result[0], 1.0);
    EXPECT_DOUBLE_EQ(result[1], 0.0);
    EXPECT_DOUBLE_EQ(result[2], 0.0);
    EXPECT_DOUBLE_EQ(result[3], 1.0);
    EXPECT_DOUBLE_EQ(result[4], 0.0);
    EXPECT_DOUBLE_EQ(result[5], 0.0);
}

// Test getMatrix with identity-like matrix values
TEST_F(GfxFunctionShadingTest_515, GetMatrixIdentityMatrix_515) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    const auto &result = shading.getMatrix();
    for (size_t i = 0; i < 6; ++i) {
        EXPECT_DOUBLE_EQ(result[i], matrix[i]);
    }
}

// Test getMatrix with non-trivial matrix values
TEST_F(GfxFunctionShadingTest_515, GetMatrixNonTrivialValues_515) {
    double x0 = -1.0, y0 = -2.0, x1 = 3.0, y1 = 4.0;
    std::array<double, 6> matrix = {2.5, -1.3, 0.7, 3.14, -100.0, 999.999};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    const auto &result = shading.getMatrix();
    EXPECT_DOUBLE_EQ(result[0], 2.5);
    EXPECT_DOUBLE_EQ(result[1], -1.3);
    EXPECT_DOUBLE_EQ(result[2], 0.7);
    EXPECT_DOUBLE_EQ(result[3], 3.14);
    EXPECT_DOUBLE_EQ(result[4], -100.0);
    EXPECT_DOUBLE_EQ(result[5], 999.999);
}

// Test getMatrix with all zeros
TEST_F(GfxFunctionShadingTest_515, GetMatrixAllZeros_515) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    const auto &result = shading.getMatrix();
    for (size_t i = 0; i < 6; ++i) {
        EXPECT_DOUBLE_EQ(result[i], 0.0);
    }
}

// Test getMatrix returns a const reference (consistency check - calling twice should yield same address)
TEST_F(GfxFunctionShadingTest_515, GetMatrixReturnsSameReference_515) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    const std::array<double, 6> &result1 = shading.getMatrix();
    const std::array<double, 6> &result2 = shading.getMatrix();
    EXPECT_EQ(&result1, &result2);
}

// Test getDomain returns the domain values set during construction
TEST_F(GfxFunctionShadingTest_515, GetDomainReturnsCorrectValues_515) {
    double x0 = -5.0, y0 = -10.0, x1 = 5.0, y1 = 10.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    double rx0, ry0, rx1, ry1;
    shading.getDomain(&rx0, &ry0, &rx1, &ry1);
    EXPECT_DOUBLE_EQ(rx0, -5.0);
    EXPECT_DOUBLE_EQ(ry0, -10.0);
    EXPECT_DOUBLE_EQ(rx1, 5.0);
    EXPECT_DOUBLE_EQ(ry1, 10.0);
}

// Test getNFuncs with no functions
TEST_F(GfxFunctionShadingTest_515, GetNFuncsWithNoFunctions_515) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    EXPECT_EQ(shading.getNFuncs(), 0);
}

// Test getMatrix with very large values
TEST_F(GfxFunctionShadingTest_515, GetMatrixLargeValues_515) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {1e300, -1e300, 1e-300, -1e-300, 1e150, -1e150};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    const auto &result = shading.getMatrix();
    EXPECT_DOUBLE_EQ(result[0], 1e300);
    EXPECT_DOUBLE_EQ(result[1], -1e300);
    EXPECT_DOUBLE_EQ(result[2], 1e-300);
    EXPECT_DOUBLE_EQ(result[3], -1e-300);
    EXPECT_DOUBLE_EQ(result[4], 1e150);
    EXPECT_DOUBLE_EQ(result[5], -1e150);
}

// Test copy constructor preserves matrix
TEST_F(GfxFunctionShadingTest_515, CopyConstructorPreservesMatrix_515) {
    double x0 = 1.0, y0 = 2.0, x1 = 3.0, y1 = 4.0;
    std::array<double, 6> matrix = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading original(x0, y0, x1, y1, matrix, std::move(funcs));
    GfxFunctionShading copied(&original);

    const auto &origMatrix = original.getMatrix();
    const auto &copyMatrix = copied.getMatrix();

    for (size_t i = 0; i < 6; ++i) {
        EXPECT_DOUBLE_EQ(origMatrix[i], copyMatrix[i]);
    }
}

// Test copy constructor preserves domain
TEST_F(GfxFunctionShadingTest_515, CopyConstructorPreservesDomain_515) {
    double x0 = -3.0, y0 = -7.0, x1 = 3.0, y1 = 7.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading original(x0, y0, x1, y1, matrix, std::move(funcs));
    GfxFunctionShading copied(&original);

    double rx0, ry0, rx1, ry1;
    copied.getDomain(&rx0, &ry0, &rx1, &ry1);
    EXPECT_DOUBLE_EQ(rx0, -3.0);
    EXPECT_DOUBLE_EQ(ry0, -7.0);
    EXPECT_DOUBLE_EQ(rx1, 3.0);
    EXPECT_DOUBLE_EQ(ry1, 7.0);
}
