#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <array>

#include "GfxState.h"
#include "Function.h"

class GfxFunctionShadingTest_517 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getDomain returns the domain values set during construction
TEST_F(GfxFunctionShadingTest_517, GetDomainReturnsConstructedValues_517) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    double rx0, ry0, rx1, ry1;
    shading.getDomain(&rx0, &ry0, &rx1, &ry1);

    EXPECT_DOUBLE_EQ(rx0, 0.0);
    EXPECT_DOUBLE_EQ(ry0, 0.0);
    EXPECT_DOUBLE_EQ(rx1, 1.0);
    EXPECT_DOUBLE_EQ(ry1, 1.0);
}

// Test getDomain with non-standard domain values
TEST_F(GfxFunctionShadingTest_517, GetDomainNonStandardValues_517) {
    double x0 = -5.5, y0 = -3.3, x1 = 10.7, y1 = 20.1;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    double rx0, ry0, rx1, ry1;
    shading.getDomain(&rx0, &ry0, &rx1, &ry1);

    EXPECT_DOUBLE_EQ(rx0, -5.5);
    EXPECT_DOUBLE_EQ(ry0, -3.3);
    EXPECT_DOUBLE_EQ(rx1, 10.7);
    EXPECT_DOUBLE_EQ(ry1, 20.1);
}

// Test that getMatrix returns the matrix set during construction
TEST_F(GfxFunctionShadingTest_517, GetMatrixReturnsConstructedValues_517) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {2.0, 0.5, -0.5, 2.0, 10.0, 20.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    const std::array<double, 6> &result = shading.getMatrix();

    EXPECT_DOUBLE_EQ(result[0], 2.0);
    EXPECT_DOUBLE_EQ(result[1], 0.5);
    EXPECT_DOUBLE_EQ(result[2], -0.5);
    EXPECT_DOUBLE_EQ(result[3], 2.0);
    EXPECT_DOUBLE_EQ(result[4], 10.0);
    EXPECT_DOUBLE_EQ(result[5], 20.0);
}

// Test getNFuncs with no functions
TEST_F(GfxFunctionShadingTest_517, GetNFuncsWithNoFunctions_517) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    EXPECT_EQ(shading.getNFuncs(), 0);
}

// Test getMatrix returns identity matrix
TEST_F(GfxFunctionShadingTest_517, GetMatrixIdentity_517) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    const std::array<double, 6> &result = shading.getMatrix();

    EXPECT_DOUBLE_EQ(result[0], 1.0);
    EXPECT_DOUBLE_EQ(result[1], 0.0);
    EXPECT_DOUBLE_EQ(result[2], 0.0);
    EXPECT_DOUBLE_EQ(result[3], 1.0);
    EXPECT_DOUBLE_EQ(result[4], 0.0);
    EXPECT_DOUBLE_EQ(result[5], 0.0);
}

// Test getDomain with zero-size domain
TEST_F(GfxFunctionShadingTest_517, GetDomainZeroSize_517) {
    double x0 = 5.0, y0 = 5.0, x1 = 5.0, y1 = 5.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    double rx0, ry0, rx1, ry1;
    shading.getDomain(&rx0, &ry0, &rx1, &ry1);

    EXPECT_DOUBLE_EQ(rx0, 5.0);
    EXPECT_DOUBLE_EQ(ry0, 5.0);
    EXPECT_DOUBLE_EQ(rx1, 5.0);
    EXPECT_DOUBLE_EQ(ry1, 5.0);
}

// Test copy constructor preserves domain
TEST_F(GfxFunctionShadingTest_517, CopyConstructorPreservesDomain_517) {
    double x0 = 1.0, y0 = 2.0, x1 = 3.0, y1 = 4.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading original(x0, y0, x1, y1, matrix, std::move(funcs));
    GfxFunctionShading copied(&original);

    double rx0, ry0, rx1, ry1;
    copied.getDomain(&rx0, &ry0, &rx1, &ry1);

    EXPECT_DOUBLE_EQ(rx0, 1.0);
    EXPECT_DOUBLE_EQ(ry0, 2.0);
    EXPECT_DOUBLE_EQ(rx1, 3.0);
    EXPECT_DOUBLE_EQ(ry1, 4.0);
}

// Test copy constructor preserves matrix
TEST_F(GfxFunctionShadingTest_517, CopyConstructorPreservesMatrix_517) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {3.0, 1.0, -1.0, 3.0, 5.0, 7.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading original(x0, y0, x1, y1, matrix, std::move(funcs));
    GfxFunctionShading copied(&original);

    const std::array<double, 6> &result = copied.getMatrix();

    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 1.0);
    EXPECT_DOUBLE_EQ(result[2], -1.0);
    EXPECT_DOUBLE_EQ(result[3], 3.0);
    EXPECT_DOUBLE_EQ(result[4], 5.0);
    EXPECT_DOUBLE_EQ(result[5], 7.0);
}

// Test copy constructor preserves getNFuncs
TEST_F(GfxFunctionShadingTest_517, CopyConstructorPreservesNFuncs_517) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading original(x0, y0, x1, y1, matrix, std::move(funcs));
    GfxFunctionShading copied(&original);

    EXPECT_EQ(copied.getNFuncs(), original.getNFuncs());
}

// Test copy method creates a valid copy
TEST_F(GfxFunctionShadingTest_517, CopyMethodCreatesCopy_517) {
    double x0 = 2.0, y0 = 3.0, x1 = 8.0, y1 = 9.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading original(x0, y0, x1, y1, matrix, std::move(funcs));
    std::unique_ptr<GfxShading> copyPtr = original.copy();

    ASSERT_NE(copyPtr, nullptr);

    // We can verify the copy is a GfxFunctionShading by dynamic cast
    GfxFunctionShading *copiedShading = dynamic_cast<GfxFunctionShading *>(copyPtr.get());
    ASSERT_NE(copiedShading, nullptr);

    double rx0, ry0, rx1, ry1;
    copiedShading->getDomain(&rx0, &ry0, &rx1, &ry1);

    EXPECT_DOUBLE_EQ(rx0, 2.0);
    EXPECT_DOUBLE_EQ(ry0, 3.0);
    EXPECT_DOUBLE_EQ(rx1, 8.0);
    EXPECT_DOUBLE_EQ(ry1, 9.0);
}

// Test getDomain with negative coordinates
TEST_F(GfxFunctionShadingTest_517, GetDomainNegativeCoordinates_517) {
    double x0 = -100.0, y0 = -200.0, x1 = -50.0, y1 = -75.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    double rx0, ry0, rx1, ry1;
    shading.getDomain(&rx0, &ry0, &rx1, &ry1);

    EXPECT_DOUBLE_EQ(rx0, -100.0);
    EXPECT_DOUBLE_EQ(ry0, -200.0);
    EXPECT_DOUBLE_EQ(rx1, -50.0);
    EXPECT_DOUBLE_EQ(ry1, -75.0);
}

// Test getFunc returns nullptr when no functions are present (index 0)
TEST_F(GfxFunctionShadingTest_517, GetFuncNoFunctions_517) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    // With no functions, getNFuncs should be 0
    EXPECT_EQ(shading.getNFuncs(), 0);
}

// Test getMatrix with all-zero matrix
TEST_F(GfxFunctionShadingTest_517, GetMatrixAllZeros_517) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    const std::array<double, 6> &result = shading.getMatrix();

    for (int i = 0; i < 6; ++i) {
        EXPECT_DOUBLE_EQ(result[i], 0.0);
    }
}

// Test getDomain with very large values
TEST_F(GfxFunctionShadingTest_517, GetDomainLargeValues_517) {
    double x0 = -1e10, y0 = -1e10, x1 = 1e10, y1 = 1e10;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    double rx0, ry0, rx1, ry1;
    shading.getDomain(&rx0, &ry0, &rx1, &ry1);

    EXPECT_DOUBLE_EQ(rx0, -1e10);
    EXPECT_DOUBLE_EQ(ry0, -1e10);
    EXPECT_DOUBLE_EQ(rx1, 1e10);
    EXPECT_DOUBLE_EQ(ry1, 1e10);
}
