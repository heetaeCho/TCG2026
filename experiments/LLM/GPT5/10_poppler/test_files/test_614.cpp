#include <gtest/gtest.h>
#include "GfxState.h"
#include <memory>

class GfxStateTest_614 : public ::testing::Test {
protected:
    // Initialize GfxState object for each test
    GfxStateTest_614() : gfxState(72.0, 72.0, nullptr, 0, false) {}

    GfxState gfxState;
};

// Test for normal operation of getRenderingIntent
TEST_F(GfxStateTest_614, GetRenderingIntent_Normal_614) {
    const char* renderingIntent = gfxState.getRenderingIntent();
    ASSERT_STREQ(renderingIntent, "DefaultRenderingIntent");  // Adjust based on actual expected default value
}

// Test for boundary condition: testing null or empty string in renderingIntent
TEST_F(GfxStateTest_614, GetRenderingIntent_Empty_614) {
    // Assuming setRenderingIntent function can set it to empty or null
    gfxState.setRenderingIntent("");
    const char* renderingIntent = gfxState.getRenderingIntent();
    ASSERT_STREQ(renderingIntent, "");  // Expecting empty string if set to empty
}

// Test for boundary condition: verifying setting and getting different rendering intents
TEST_F(GfxStateTest_614, GetRenderingIntent_SettingCustom_614) {
    // Setting a custom rendering intent
    gfxState.setRenderingIntent("CustomIntent");
    const char* renderingIntent = gfxState.getRenderingIntent();
    ASSERT_STREQ(renderingIntent, "CustomIntent");
}

// Test for edge case: verifying if renderingIntent is null
TEST_F(GfxStateTest_614, GetRenderingIntent_Null_614) {
    // Assuming setRenderingIntent allows setting a null value
    gfxState.setRenderingIntent(nullptr);
    const char* renderingIntent = gfxState.getRenderingIntent();
    ASSERT_EQ(renderingIntent, nullptr);  // Expecting null if set to nullptr
}

// Test for boundary condition: setting renderingIntent to a large string
TEST_F(GfxStateTest_614, GetRenderingIntent_LargeString_614) {
    std::string largeIntent(1000, 'A');  // Large string of 1000 'A' characters
    gfxState.setRenderingIntent(largeIntent.c_str());
    const char* renderingIntent = gfxState.getRenderingIntent();
    ASSERT_STREQ(renderingIntent, largeIntent.c_str());  // Expecting the large string to be returned
}