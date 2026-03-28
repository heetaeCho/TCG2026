#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include "SplashOutputDev.h"



using namespace testing;



// Mock class for GfxGouraudTriangleShading

class MockGfxGouraudTriangleShading : public GfxGouraudTriangleShading {

public:

    MOCK_METHOD(int, getNTriangles, (), (const, override));

};



class SplashGouraudPatternTest_1102 : public Test {

protected:

    std::unique_ptr<MockGfxGouraudTriangleShading> mockShading;

    std::unique_ptr<SplashGouraudPattern> pattern;



    void SetUp() override {

        mockShading = std::make_unique<MockGfxGouraudTriangleShading>();

        pattern = std::make_unique<SplashGouraudPattern>(false, mockShading.get());

    }

};



TEST_F(SplashGouraudPatternTest_1102, GetNTriangles_DelegatesToShading_1102) {

    EXPECT_CALL(*mockShading, getNTriangles()).WillOnce(Return(42));

    EXPECT_EQ(pattern->getNTriangles(), 42);

}



TEST_F(SplashGouraudPatternTest_1102, GetNTriangles_ReturnsZeroWhenShadingIsNull_1102) {

    pattern.reset(new SplashGouraudPattern(false, nullptr));

    EXPECT_EQ(pattern->getNTriangles(), 0);

}
