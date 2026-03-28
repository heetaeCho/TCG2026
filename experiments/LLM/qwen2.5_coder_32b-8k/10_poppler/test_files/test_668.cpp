#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_668 : public ::testing::Test {

protected:

    GfxStateTest_668() : gfxState(72.0, 72.0, nullptr, 0, false) {}



    GfxState gfxState;

};



TEST_F(GfxStateTest_668, GetReusablePath_ReturnsNonNullPointer_668) {

    auto pathIterator = gfxState.getReusablePath();

    EXPECT_NE(pathIterator, nullptr);

}



TEST_F(GfxStateTest_668, GetReusablePath_CreatesUniqueInstanceEachTime_668) {

    auto firstPathIterator = gfxState.getReusablePath();

    auto secondPathIterator = gfxState.getReusablePath();

    EXPECT_NE(firstPathIterator.get(), secondPathIterator.get());

}
