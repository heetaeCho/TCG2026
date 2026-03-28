#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "SplashOutputDev.h"

#include "GfxState.h"



using ::testing::NiceMock;

using ::testing::StrictMock;



class MockGfxGouraudTriangleShading : public GfxGouraudTriangleShading {

public:

    MOCK_METHOD(void, getTriangle, (int i, double * x0, double * y0, GfxColor * color0, 

                                      double * x1, double * y1, GfxColor * color1, 

                                      double * x2, double * y2, GfxColor * color2), (const override));

    MOCK_METHOD(int, getNTriangles, (), (const override));

};



class SplashGouraudPatternTest : public ::testing::Test {

protected:

    NiceMock<MockGfxGouraudTriangleShading> mock_shading;

    bool bDirectColorTranslation = false;

    std::unique_ptr<SplashGouraudPattern> pattern;



    void SetUp() override {

        pattern.reset(new SplashGouraudPattern(bDirectColorTranslation, &mock_shading));

    }

};



TEST_F(SplashGouraudPatternTest_1103, GetParametrizedTriangle_ValidIndex_1103) {

    int i = 0;

    double x0, y0, color0[4];

    double x1, y1, color1[4];

    double x2, y2, color2[4];



    EXPECT_CALL(mock_shading, getTriangle(i, &x0, &y0, reinterpret_cast<GfxColor*>(color0),

                                           &x1, &y1, reinterpret_cast<GfxColor*>(color1),

                                           &x2, &y2, reinterpret_cast<GfxColor*>(color2)));



    pattern->getParametrizedTriangle(i, &x0, &y0, color0, 

                                      &x1, &y1, color1,

                                      &x2, &y2, color2);

}



TEST_F(SplashGouraudPatternTest_1103, GetParametrizedTriangle_OutOfBoundsIndex_1103) {

    int i = -1; // Assuming out of bounds index

    double x0, y0, color0[4];

    double x1, y1, color1[4];

    double x2, y2, color2[4];



    EXPECT_CALL(mock_shading, getTriangle(i, &x0, &y0, reinterpret_cast<GfxColor*>(color0),

                                           &x1, &y1, reinterpret_cast<GfxColor*>(color1),

                                           &x2, &y2, reinterpret_cast<GfxColor*>(color2)))

        .WillOnce(::testing::Throw(std::out_of_range("Index out of range")));



    EXPECT_THROW(pattern->getParametrizedTriangle(i, &x0, &y0, color0,

                                                   &x1, &y1, color1,

                                                   &x2, &y2, color2), std::out_of_range);

}



TEST_F(SplashGouraudPatternTest_1103, GetNTriangles_ReturnsCorrectValue_1103) {

    int expected_nTriangles = 5; // Assuming some value

    EXPECT_CALL(mock_shading, getNTriangles()).WillOnce(::testing::Return(expected_nTriangles));



    int actual_nTriangles = pattern->getNTriangles();



    EXPECT_EQ(actual_nTriangles, expected_nTriangles);

}



TEST_F(SplashGouraudPatternTest_1103, IsParameterized_DelegatesToShading_1103) {

    bool isParametrizedResult = true; // Assuming some value

    EXPECT_CALL(mock_shading, isParameterized()).WillOnce(::testing::Return(isParametrizedResult));



    bool actualIsParametrized = pattern->isParameterized();



    EXPECT_EQ(actualIsParametrized, isParametrizedResult);

}
