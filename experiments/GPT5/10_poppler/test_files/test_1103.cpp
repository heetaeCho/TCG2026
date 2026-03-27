#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SplashOutputDev.h"
#include "GfxState.h"

// Mocking GfxGouraudTriangleShading for external interactions
class MockGfxGouraudTriangleShading : public GfxGouraudTriangleShading {
public:
    MOCK_METHOD(void, getTriangle, (int i, double* x0, double* y0, double* color0, 
                                    double* x1, double* y1, double* color1, 
                                    double* x2, double* y2, double* color2), (const, override));
};

// Test Fixture for SplashGouraudPattern
class SplashGouraudPatternTest_1103 : public ::testing::Test {
protected:
    MockGfxGouraudTriangleShading* mockShading;
    SplashGouraudPattern* pattern;

    void SetUp() override {
        mockShading = new MockGfxGouraudTriangleShading(0, nullptr, 0, nullptr, 0, {});
        pattern = new SplashGouraudPattern(true, mockShading);
    }

    void TearDown() override {
        delete pattern;
        delete mockShading;
    }
};

// Test: Normal operation of getParametrizedTriangle
TEST_F(SplashGouraudPatternTest_1103, GetParametrizedTriangle_NormalOperation_1103) {
    double x0 = 0.0, y0 = 0.0, color0 = 0.0;
    double x1 = 1.0, y1 = 1.0, color1 = 1.0;
    double x2 = 2.0, y2 = 2.0, color2 = 2.0;
    EXPECT_CALL(*mockShading, getTriangle(0, &x0, &y0, &color0, &x1, &y1, &color1, &x2, &y2, &color2))
        .Times(1);

    pattern->getParametrizedTriangle(0, &x0, &y0, &color0, &x1, &y1, &color1, &x2, &y2, &color2);
}

// Test: Boundary condition for getParametrizedTriangle with extreme values
TEST_F(SplashGouraudPatternTest_1103, GetParametrizedTriangle_BoundaryCondition_1103) {
    double x0 = -1000.0, y0 = -1000.0, color0 = 0.0;
    double x1 = 1000.0, y1 = 1000.0, color1 = 1.0;
    double x2 = 0.0, y2 = 0.0, color2 = 0.5;
    EXPECT_CALL(*mockShading, getTriangle(0, &x0, &y0, &color0, &x1, &y1, &color1, &x2, &y2, &color2))
        .Times(1);

    pattern->getParametrizedTriangle(0, &x0, &y0, &color0, &x1, &y1, &color1, &x2, &y2, &color2);
}

// Test: Exceptional case for getParametrizedTriangle (mock does nothing)
TEST_F(SplashGouraudPatternTest_1103, GetParametrizedTriangle_ExceptionalCase_1103) {
    double x0 = 0.0, y0 = 0.0, color0 = 0.0;
    double x1 = 1.0, y1 = 1.0, color1 = 1.0;
    double x2 = 2.0, y2 = 2.0, color2 = 2.0;
    
    // Simulate a failure in the mocked function call
    EXPECT_CALL(*mockShading, getTriangle(0, &x0, &y0, &color0, &x1, &y1, &color1, &x2, &y2, &color2))
        .WillOnce(testing::Throw(std::runtime_error("Error in getTriangle")));

    try {
        pattern->getParametrizedTriangle(0, &x0, &y0, &color0, &x1, &y1, &color1, &x2, &y2, &color2);
        FAIL() << "Expected exception not thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Error in getTriangle");
    }
}

// Test: Verify interaction with external mock
TEST_F(SplashGouraudPatternTest_1103, VerifyExternalInteraction_1103) {
    double x0 = 0.0, y0 = 0.0, color0 = 0.0;
    double x1 = 1.0, y1 = 1.0, color1 = 1.0;
    double x2 = 2.0, y2 = 2.0, color2 = 2.0;
    
    EXPECT_CALL(*mockShading, getTriangle(0, &x0, &y0, &color0, &x1, &y1, &color1, &x2, &y2, &color2))
        .Times(1);

    pattern->getParametrizedTriangle(0, &x0, &y0, &color0, &x1, &y1, &color1, &x2, &y2, &color2);
}