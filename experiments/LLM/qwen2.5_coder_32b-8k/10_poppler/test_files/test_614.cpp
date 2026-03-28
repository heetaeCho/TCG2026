#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/GfxState.h"



// Test fixture for GfxState class tests

class GfxStateTest_614 : public ::testing::Test {

protected:

    GfxStateTest_614() : gfxState(72.0, 72.0, nullptr, 0, false) {}



    GfxState gfxState;

};



// Test normal operation of getRenderingIntent

TEST_F(GfxStateTest_614, GetRenderingIntent_Default_614) {

    const char* intent = gfxState.getRenderingIntent();

    EXPECT_STREQ(intent, ""); // Assuming default rendering intent is an empty string

}



// Test setting and getting a custom rendering intent

TEST_F(GfxStateTest_614, SetAndGetRenderingIntent_Custom_614) {

    const char* customIntent = "Perceptual";

    gfxState.setRenderingIntent(customIntent);

    EXPECT_STREQ(gfxState.getRenderingIntent(), customIntent);

}



// Test boundary condition with an empty string as rendering intent

TEST_F(GfxStateTest_614, SetAndGetRenderingIntent_EmptyString_614) {

    const char* emptyIntent = "";

    gfxState.setRenderingIntent(emptyIntent);

    EXPECT_STREQ(gfxState.getRenderingIntent(), emptyIntent);

}



// Test exceptional case with null pointer as rendering intent

TEST_F(GfxStateTest_614, SetAndGetRenderingIntent_NullPointer_614) {

    gfxState.setRenderingIntent(nullptr);

    EXPECT_STREQ(gfxState.getRenderingIntent(), ""); // Assuming setting nullptr resets to default empty string

}
