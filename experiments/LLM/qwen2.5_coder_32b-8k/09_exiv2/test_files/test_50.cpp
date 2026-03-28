#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class XmpDataTest_50 : public ::testing::Test {

protected:

    XmpData xmpData;

};



TEST_F(XmpDataTest_50, UsePacket_DefaultValue_50) {

    EXPECT_EQ(xmpData.usePacket(), false);

}



TEST_F(XmpDataTest_50, UsePacket_SetTrue_ReturnsFalse_50) {

    EXPECT_EQ(xmpData.usePacket(true), false);

    EXPECT_EQ(xmpData.usePacket(), true);

}



TEST_F(XmpDataTest_50, UsePacket_SetFalse_ReturnsTrue_50) {

    xmpData.usePacket(true);

    EXPECT_EQ(xmpData.usePacket(false), true);

    EXPECT_EQ(xmpData.usePacket(), false);

}



TEST_F(XmpDataTest_50, UsePacket_ToggleMultipleTimes_50) {

    EXPECT_EQ(xmpData.usePacket(true), false);

    EXPECT_EQ(xmpData.usePacket(true), true);

    EXPECT_EQ(xmpData.usePacket(false), true);

    EXPECT_EQ(xmpData.usePacket(false), false);

}



TEST_F(XmpDataTest_50, Empty_DefaultState_ReturnsTrue_50) {

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_50, Count_DefaultState_ReturnsZero_50) {

    EXPECT_EQ(xmpData.count(), 0);

}
