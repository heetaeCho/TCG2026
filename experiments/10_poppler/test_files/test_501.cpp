#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/GfxState.h"



class GfxShadingPatternMock : public GfxShadingPattern {

public:

    MOCK_METHOD(GfxShading*, getShading, (), (override));

    MOCK_METHOD(const std::unique_ptr<GfxPattern>, copy, (), (const override));



    using GfxShadingPattern::GfxShadingPattern;

};



// Test Suite for GfxShadingPattern

class GfxShadingPatternTest_501 : public ::testing::Test {

protected:

    void SetUp() override {

        std::array<double, 6> matrix = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

        pattern = std::make_unique<GfxShadingPatternMock>(std::make_unique<GfxShading>(), matrix, 1);

    }



    void TearDown() override {

        pattern.reset();

    }



    std::unique_ptr<GfxShadingPatternMock> pattern;

};



// Test case for normal operation of getMatrix

TEST_F(GfxShadingPatternTest_501, GetMatrixReturnsCorrectValue_501) {

    const auto& matrix = pattern->getMatrix();

    EXPECT_EQ(matrix, std::array<double, 6>({0.0, 1.0, 2.0, 3.0, 4.0, 5.0}));

}



// Test case for boundary condition of getMatrix (empty array)

TEST_F(GfxShadingPatternTest_501, GetMatrixBoundaryCondition_501) {

    // Since the matrix is a fixed size array, we cannot test empty condition directly.

    // However, we can test if it returns a default constructed array with all zeros.

    GfxShadingPatternMock patternWithZeroMatrix(std::make_unique<GfxShading>(), std::array<double, 6>({0.0}), 1);

    const auto& matrix = patternWithZeroMatrix.getMatrix();

    EXPECT_EQ(matrix, std::array<double, 6>({0.0, 0.0, 0.0, 0.0, 0.0, 0.0}));

}



// Test case for getShading method invocation

TEST_F(GfxShadingPatternTest_501, GetShadingInvokesCorrectly_501) {

    EXPECT_CALL(*pattern, getShading()).Times(1);

    pattern->getShading();

}



// Test case for copy method invocation

TEST_F(GfxShadingPatternTest_501, CopyInvokesCorrectly_501) {

    EXPECT_CALL(*pattern, copy()).Times(1);

    pattern->copy();

}
