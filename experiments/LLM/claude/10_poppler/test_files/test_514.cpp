#include <gtest/gtest.h>
#include <memory>
#include <array>
#include <vector>
#include "GfxState.h"
#include "Function.h"

class GfxFunctionShadingTest_514 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test getDomain returns the domain values that were set during construction
TEST_F(GfxFunctionShadingTest_514, GetDomainReturnsCorrectValues_514) {
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

// Test getDomain with non-zero origin domain values
TEST_F(GfxFunctionShadingTest_514, GetDomainNonZeroOrigin_514) {
    double x0 = 2.5, y0 = 3.5, x1 = 10.0, y1 = 20.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    double rx0, ry0, rx1, ry1;
    shading.getDomain(&rx0, &ry0, &rx1, &ry1);

    EXPECT_DOUBLE_EQ(rx0, 2.5);
    EXPECT_DOUBLE_EQ(ry0, 3.5);
    EXPECT_DOUBLE_EQ(rx1, 10.0);
    EXPECT_DOUBLE_EQ(ry1, 20.0);
}

// Test getDomain with negative domain values
TEST_F(GfxFunctionShadingTest_514, GetDomainNegativeValues_514) {
    double x0 = -5.0, y0 = -10.0, x1 = -1.0, y1 = -2.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    double rx0, ry0, rx1, ry1;
    shading.getDomain(&rx0, &ry0, &rx1, &ry1);

    EXPECT_DOUBLE_EQ(rx0, -5.0);
    EXPECT_DOUBLE_EQ(ry0, -10.0);
    EXPECT_DOUBLE_EQ(rx1, -1.0);
    EXPECT_DOUBLE_EQ(ry1, -2.0);
}

// Test getDomain with zero-width domain (degenerate case)
TEST_F(GfxFunctionShadingTest_514, GetDomainZeroWidth_514) {
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

// Test getDomain with very large domain values
TEST_F(GfxFunctionShadingTest_514, GetDomainLargeValues_514) {
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

// Test copy constructor preserves domain
TEST_F(GfxFunctionShadingTest_514, CopyConstructorPreservesDomain_514) {
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

// Test getMatrix returns the matrix set during construction
TEST_F(GfxFunctionShadingTest_514, GetMatrixReturnsCorrectValues_514) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {2.0, 0.0, 0.0, 3.0, 1.0, 2.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    const std::array<double, 6> &result = shading.getMatrix();

    EXPECT_DOUBLE_EQ(result[0], 2.0);
    EXPECT_DOUBLE_EQ(result[1], 0.0);
    EXPECT_DOUBLE_EQ(result[2], 0.0);
    EXPECT_DOUBLE_EQ(result[3], 3.0);
    EXPECT_DOUBLE_EQ(result[4], 1.0);
    EXPECT_DOUBLE_EQ(result[5], 2.0);
}

// Test getNFuncs with empty functions vector
TEST_F(GfxFunctionShadingTest_514, GetNFuncsEmptyVector_514) {
    double x0 = 0.0, y0 = 0.0, x1 = 1.0, y1 = 1.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    EXPECT_EQ(shading.getNFuncs(), 0);
}

// Test getDomain with inverted domain (x0 > x1)
TEST_F(GfxFunctionShadingTest_514, GetDomainInvertedValues_514) {
    double x0 = 10.0, y0 = 20.0, x1 = 1.0, y1 = 2.0;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    double rx0, ry0, rx1, ry1;
    shading.getDomain(&rx0, &ry0, &rx1, &ry1);

    EXPECT_DOUBLE_EQ(rx0, 10.0);
    EXPECT_DOUBLE_EQ(ry0, 20.0);
    EXPECT_DOUBLE_EQ(rx1, 1.0);
    EXPECT_DOUBLE_EQ(ry1, 2.0);
}

// Test copy method preserves domain
TEST_F(GfxFunctionShadingTest_514, CopyMethodPreservesDomain_514) {
    double x0 = 1.5, y0 = 2.5, x1 = 3.5, y1 = 4.5;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading original(x0, y0, x1, y1, matrix, std::move(funcs));
    std::unique_ptr<GfxShading> copyPtr = original.copy();

    ASSERT_NE(copyPtr, nullptr);

    GfxFunctionShading *copiedShading = dynamic_cast<GfxFunctionShading *>(copyPtr.get());
    ASSERT_NE(copiedShading, nullptr);

    double rx0, ry0, rx1, ry1;
    copiedShading->getDomain(&rx0, &ry0, &rx1, &ry1);

    EXPECT_DOUBLE_EQ(rx0, 1.5);
    EXPECT_DOUBLE_EQ(ry0, 2.5);
    EXPECT_DOUBLE_EQ(rx1, 3.5);
    EXPECT_DOUBLE_EQ(ry1, 4.5);
}

// Test getDomain with fractional precision values
TEST_F(GfxFunctionShadingTest_514, GetDomainFractionalPrecision_514) {
    double x0 = 0.123456789, y0 = 0.987654321, x1 = 1.111111111, y1 = 2.222222222;
    std::array<double, 6> matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    std::vector<std::unique_ptr<Function>> funcs;

    GfxFunctionShading shading(x0, y0, x1, y1, matrix, std::move(funcs));

    double rx0, ry0, rx1, ry1;
    shading.getDomain(&rx0, &ry0, &rx1, &ry1);

    EXPECT_DOUBLE_EQ(rx0, 0.123456789);
    EXPECT_DOUBLE_EQ(ry0, 0.987654321);
    EXPECT_DOUBLE_EQ(rx1, 1.111111111);
    EXPECT_DOUBLE_EQ(ry1, 2.222222222);
}
