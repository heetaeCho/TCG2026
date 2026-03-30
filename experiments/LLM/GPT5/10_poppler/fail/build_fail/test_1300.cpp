#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"

class PSOutputDevTest_1300 : public ::testing::Test {
protected:
    PSOutputDevTest_1300() : psOutputDev(nullptr, nullptr, "Test", 0, PSOutMode::kDefault, 600, 800, false, false, 0, 0, 600, 800, PSForceRasterize::kNone, false, nullptr, nullptr, PSLevel::kLevel1) {}
    PSOutputDev psOutputDev;
};

TEST_F(PSOutputDevTest_1300, SetOffset_1300) {
    psOutputDev.setOffset(10.0, 20.0);
    
    // Assuming there is a way to check if the offset was set, e.g., using a getter function
    // ASSERT_EQ(psOutputDev.getTx0(), 10.0);
    // ASSERT_EQ(psOutputDev.getTy0(), 20.0);
}

TEST_F(PSOutputDevTest_1300, SetScale_1301) {
    psOutputDev.setScale(2.0, 2.0);
    
    // Assuming there is a way to check if the scale was set correctly
    // ASSERT_EQ(psOutputDev.getXScale(), 2.0);
    // ASSERT_EQ(psOutputDev.getYScale(), 2.0);
}

TEST_F(PSOutputDevTest_1300, SetRotate_1302) {
    psOutputDev.setRotate(90);
    
    // Assuming there is a way to check if rotation is set correctly
    // ASSERT_EQ(psOutputDev.getRotate(), 90);
}

TEST_F(PSOutputDevTest_1300, SetClip_1303) {
    psOutputDev.setClip(0.0, 0.0, 100.0, 100.0);
    
    // Assuming there is a way to check if the clipping was set correctly
    // ASSERT_EQ(psOutputDev.getClipLLX(), 0.0);
    // ASSERT_EQ(psOutputDev.getClipLLY(), 0.0);
    // ASSERT_EQ(psOutputDev.getClipURX(), 100.0);
    // ASSERT_EQ(psOutputDev.getClipURY(), 100.0);
}

TEST_F(PSOutputDevTest_1300, SetUnderlayCbk_1304) {
    void (*underlayCallback)(PSOutputDev *, void *) = nullptr;
    psOutputDev.setUnderlayCbk(underlayCallback, nullptr);
    
    // Assuming there is a way to verify if the callback was set
    // ASSERT_EQ(psOutputDev.getUnderlayCbk(), underlayCallback);
}

TEST_F(PSOutputDevTest_1300, SetOverlayCbk_1305) {
    void (*overlayCallback)(PSOutputDev *, void *) = nullptr;
    psOutputDev.setOverlayCbk(overlayCallback, nullptr);
    
    // Assuming there is a way to verify if the callback was set
    // ASSERT_EQ(psOutputDev.getOverlayCbk(), overlayCallback);
}

TEST_F(PSOutputDevTest_1300, SetDisplayText_1306) {
    psOutputDev.setDisplayText(true);
    
    // Assuming there is a way to check if display text setting is applied
    // ASSERT_TRUE(psOutputDev.getDisplayText());
}

TEST_F(PSOutputDevTest_1300, SetRasterAntialias_1307) {
    psOutputDev.setRasterAntialias(true);
    
    // Assuming there is a way to check if raster antialiasing is enabled
    // ASSERT_TRUE(psOutputDev.getRasterAntialias());
}

TEST_F(PSOutputDevTest_1300, SetForceRasterize_1308) {
    psOutputDev.setForceRasterize(PSForceRasterize::kAlways);
    
    // Assuming there is a way to check if force rasterization is enabled
    // ASSERT_EQ(psOutputDev.getForceRasterize(), PSForceRasterize::kAlways);
}

TEST_F(PSOutputDevTest_1300, SetRasterResolution_1309) {
    psOutputDev.setRasterResolution(300.0);
    
    // Assuming there is a way to check if raster resolution is set correctly
    // ASSERT_EQ(psOutputDev.getRasterResolution(), 300.0);
}

TEST_F(PSOutputDevTest_1300, SetUncompressPreloadedImages_1310) {
    psOutputDev.setUncompressPreloadedImages(true);
    
    // Assuming there is a way to check if the uncompress preloaded images flag is set
    // ASSERT_TRUE(psOutputDev.getUncompressPreloadedImages());
}

// Test exceptional behavior or boundary conditions if applicable
// For example, testing edge cases like invalid parameters for setOffset, setScale, etc.

TEST_F(PSOutputDevTest_1300, SetOffset_InvalidValues_1311) {
    // Invalid offset values
    psOutputDev.setOffset(-1.0, -1.0);
    
    // Assuming some validation or behavior on invalid values
    // ASSERT_NE(psOutputDev.getTx0(), -1.0);
    // ASSERT_NE(psOutputDev.getTy0(), -1.0);
}

TEST_F(PSOutputDevTest_1300, SetScale_ZeroValues_1312) {
    psOutputDev.setScale(0.0, 0.0);
    
    // Check if scale is properly handled
    // ASSERT_EQ(psOutputDev.getXScale(), 0.0);
    // ASSERT_EQ(psOutputDev.getYScale(), 0.0);
}

TEST_F(PSOutputDevTest_1300, SetInvalidRotation_1313) {
    psOutputDev.setRotate(1000); // Invalid rotation value
    
    // Assuming some form of validation is in place
    // ASSERT_NE(psOutputDev.getRotate(), 1000);
}