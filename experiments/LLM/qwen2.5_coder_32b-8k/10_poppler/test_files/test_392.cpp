#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/GfxState.h"



TEST(byteToColTest_392, ZeroInput_ReturnsZero_392) {

    EXPECT_EQ(byteToCol(0), static_cast<GfxColorComp>(0));

}



TEST(byteToColTest_392, MaxInput_ReturnsMaxGfxColorComp_392) {

    EXPECT_EQ(byteToCol(255), static_cast<GfxColorComp>(65792));

}



TEST(byteToColTest_392, MidRangeInput_ReturnsExpectedValue_392) {

    EXPECT_EQ(byteToCol(128), static_cast<GfxColorComp>(32896));

}



TEST(byteToColTest_392, OneInput_ReturnsCorrectValue_392) {

    EXPECT_EQ(byteToCol(1), static_cast<GfxColorComp>(259));

}
