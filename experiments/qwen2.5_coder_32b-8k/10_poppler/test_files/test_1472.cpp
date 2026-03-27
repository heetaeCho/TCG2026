#include <gtest/gtest.h>

#include "GfxState.h"

#include "Gfx.cc"



class GfxRadialShadingMock : public GfxRadialShading {

public:

    MOCK_METHOD2(getColor, int(double t, GfxColor *color));

    MOCK_METHOD0(getDomain0, double());

    MOCK_METHOD0(getDomain1, double());



    GfxRadialShadingMock(double x0A, double y0A, double r0A, double x1A, double y1A, double r1A, double t0A, double t1A,

                         std::vector<std::unique_ptr<Function>> &&funcsA, bool extend0A, bool extend1A)

            : GfxRadialShading(x0A, y0A, r0A, x1A, y1A, r1A, t0A, t1A, std::move(funcsA), extend0A, extend1A) {}



    GfxRadialShadingMock(const GfxRadialShading *shading) : GfxRadialShading(shading) {}

};



class ShadingColorHelperTest_1472 : public ::testing::Test {

protected:

    void SetUp() override {

        t0 = 0.0;

        t1 = 1.0;

        t_within_range = 0.5;

        t_below_range = -0.1;

        t_above_range = 1.1;



        shading_mock = std::make_unique<GfxRadialShadingMock>(0, 0, 0, 1, 1, 1, t0, t1, {}, true, true);

        color = GfxColor();

    }



    double t0;

    double t1;

    double t_within_range;

    double t_below_range;

    double t_above_range;

    std::unique_ptr<GfxRadialShadingMock> shading_mock;

    GfxColor color;

};



TEST_F(ShadingColorHelperTest_1472, PutWithinRange_1472) {

    EXPECT_CALL(*shading_mock, getColor(t_within_range, &color));

    getShadingColorRadialHelper(t0, t1, t_within_range, shading_mock.get(), &color);

}



TEST_F(ShadingColorHelperTest_1472, PutBelowRange_1472) {

    EXPECT_CALL(*shading_mock, getColor(t0, &color));

    getShadingColorRadialHelper(t0, t1, t_below_range, shading_mock.get(), &color);

}



TEST_F(ShadingColorHelperTest_1472, PutAboveRange_1472) {

    EXPECT_CALL(*shading_mock, getColor(t1, &color));

    getShadingColorRadialHelper(t0, t1, t_above_range, shading_mock.get(), &color);

}



TEST_F(ShadingColorHelperTest_1472, PutT0GreaterThanT1WithinRange_1472) {

    double t0 = 1.0;

    double t1 = 0.0;

    EXPECT_CALL(*shading_mock, getColor(t_within_range, &color));

    getShadingColorRadialHelper(t0, t1, t_within_range, shading_mock.get(), &color);

}



TEST_F(ShadingColorHelperTest_1472, PutT0GreaterThanT1BelowRange_1472) {

    double t0 = 1.0;

    double t1 = 0.0;

    EXPECT_CALL(*shading_mock, getColor(t0, &color));

    getShadingColorRadialHelper(t0, t1, t_above_range, shading_mock.get(), &color);

}



TEST_F(ShadingColorHelperTest_1472, PutT0GreaterThanT1AboveRange_1472) {

    double t0 = 1.0;

    double t1 = 0.0;

    EXPECT_CALL(*shading_mock, getColor(t1, &color));

    getShadingColorRadialHelper(t0, t1, t_below_range, shading_mock.get(), &color);

}
