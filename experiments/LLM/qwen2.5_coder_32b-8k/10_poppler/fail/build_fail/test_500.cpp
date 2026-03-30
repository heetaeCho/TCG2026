#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



// Mock class for GfxShading to simulate its behavior in tests

class MockGfxShading : public GfxShading {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



TEST_F(GfxShadingPatternTest_500, GetShadingReturnsValidPointer_500) {

    auto mockShading = std::make_unique<MockGfxShading>();

    auto* rawPtr = mockShading.get();

    GfxShadingPattern pattern(std::move(mockShading), {1.0, 0.0, 0.0, 1.0, 0.0, 0.0}, 42);



    EXPECT_EQ(pattern.getShading(), rawPtr);

}



TEST_F(GfxShadingPatternTest_500, GetMatrixReturnsCorrectValues_500) {

    GfxShadingPattern pattern(nullptr, {1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 42);

    const std::array<double, 6> expectedMatrix = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};



    EXPECT_EQ(pattern.getMatrix(), expectedMatrix);

}



TEST_F(GfxShadingPatternTest_500, GetShadingReturnsNullptrWhenNotInitialized_500) {

    GfxShadingPattern pattern(nullptr, {1.0, 0.0, 0.0, 1.0, 0.0, 0.0}, 42);



    EXPECT_EQ(pattern.getShading(), nullptr);

}



TEST_F(GfxShadingPatternTest_500, CopyReturnsNewInstanceWithSameMatrix_500) {

    GfxShadingPattern pattern(nullptr, {1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 42);

    const auto copy = dynamic_cast<GfxShadingPattern*>(pattern.copy().release());



    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(pattern.getMatrix(), copy->getMatrix());

    delete copy;

}
