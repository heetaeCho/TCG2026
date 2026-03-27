#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



class GfxPatternTest_490 : public ::testing::Test {

protected:

    std::unique_ptr<GfxPattern> pattern;



    void SetUp() override {

        pattern = std::make_unique<GfxPattern>(1, 2);

    }

};



TEST_F(GfxPatternTest_490, GetType_ReturnsCorrectType_490) {

    EXPECT_EQ(pattern->getType(), 1);

}



TEST_F(GfxPatternTest_490, GetPatternRefNum_ReturnsCorrectRefNum_490) {

    EXPECT_EQ(pattern->getPatternRefNum(), 2);

}



TEST_F(GfxPatternTest_490, Copy_ReturnsNewInstanceWithSameTypeAndRefNum_490) {

    auto copiedPattern = pattern->copy();

    EXPECT_EQ(copiedPattern->getType(), 1);

    EXPECT_EQ(copiedPattern->getPatternRefNum(), 2);

}



TEST_F(GfxPatternTest_490, Copy_ReturnsDifferentInstance_490) {

    auto copiedPattern = pattern->copy();

    EXPECT_NE(pattern.get(), copiedPattern.get());

}
