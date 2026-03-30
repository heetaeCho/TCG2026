#include <gtest/gtest.h>
#include "PSOutputDev.h"

class PSOutputDevTest_1330 : public ::testing::Test {
protected:
    PSOutputDevTest_1330() {
        // Initialization if needed
    }
};

// Test normal operation of setOptimizeColorSpace
TEST_F(PSOutputDevTest_1330, SetOptimizeColorSpaceNormal_1330) {
    PSOutputDev psOutputDev("test.ps", nullptr, "Title", 1, PSOutMode::PSOutDefault, 8.5, 11.0, false, false, 0, 0, 0, 0, PSForceRasterize::PSForceRasterizeNone, false, nullptr, nullptr, PSLevel::PSLevel2);

    // Verify initial state of optimizeColorSpace (it should be false by default)
    EXPECT_FALSE(psOutputDev.getOptimizeColorSpace());

    // Set optimizeColorSpace to true and verify the change
    psOutputDev.setOptimizeColorSpace(true);
    EXPECT_TRUE(psOutputDev.getOptimizeColorSpace());
}

// Test boundary conditions for setOptimizeColorSpace
TEST_F(PSOutputDevTest_1330, SetOptimizeColorSpaceBoundary_1330) {
    PSOutputDev psOutputDev("test.ps", nullptr, "Title", 1, PSOutMode::PSOutDefault, 8.5, 11.0, false, false, 0, 0, 0, 0, PSForceRasterize::PSForceRasterizeNone, false, nullptr, nullptr, PSLevel::PSLevel2);

    // Test setting optimizeColorSpace to false after being true
    psOutputDev.setOptimizeColorSpace(true);
    EXPECT_TRUE(psOutputDev.getOptimizeColorSpace());
    
    psOutputDev.setOptimizeColorSpace(false);
    EXPECT_FALSE(psOutputDev.getOptimizeColorSpace());
}

// Test exceptional cases for setOptimizeColorSpace (checking invalid behavior, if any)
TEST_F(PSOutputDevTest_1330, SetOptimizeColorSpaceExceptional_1330) {
    PSOutputDev psOutputDev("test.ps", nullptr, "Title", 1, PSOutMode::PSOutDefault, 8.5, 11.0, false, false, 0, 0, 0, 0, PSForceRasterize::PSForceRasterizeNone, false, nullptr, nullptr, PSLevel::PSLevel2);

    // Set to true and then false, the method should work without errors
    EXPECT_NO_THROW(psOutputDev.setOptimizeColorSpace(true));
    EXPECT_NO_THROW(psOutputDev.setOptimizeColorSpace(false));
}

// Verify interactions (mocking)
class MockPSOutputDev : public PSOutputDev {
public:
    MockPSOutputDev(const char *fileName, PDFDoc *docA, char *psTitleA, const int &pages, PSOutMode modeA, int paperWidthA, int paperHeightA, bool noCrop, bool duplexA, int imgLLXA, int imgLLYA, int imgURXA, int imgURYA, PSForceRasterize forceRasterizeA, bool manualCtrlA, PSOutCustomCodeCbk customCodeCbkA, void *customCodeCbkDataA, PSLevel levelA)
        : PSOutputDev(fileName, docA, psTitleA, pages, modeA, paperWidthA, paperHeightA, noCrop, duplexA, imgLLXA, imgLLYA, imgURXA, imgURYA, forceRasterizeA, manualCtrlA, customCodeCbkA, customCodeCbkDataA, levelA) {}

    MOCK_METHOD(void, setOptimizeColorSpace, (bool b), (override));
};

TEST_F(PSOutputDevTest_1330, SetOptimizeColorSpaceMockInteraction_1330) {
    MockPSOutputDev mockPSOutputDev("test.ps", nullptr, "Title", 1, PSOutMode::PSOutDefault, 8.5, 11.0, false, false, 0, 0, 0, 0, PSForceRasterize::PSForceRasterizeNone, false, nullptr, nullptr, PSLevel::PSLevel2);

    // Expect that setOptimizeColorSpace will be called with true
    EXPECT_CALL(mockPSOutputDev, setOptimizeColorSpace(true)).Times(1);
    mockPSOutputDev.setOptimizeColorSpace(true);

    // Expect that setOptimizeColorSpace will be called with false
    EXPECT_CALL(mockPSOutputDev, setOptimizeColorSpace(false)).Times(1);
    mockPSOutputDev.setOptimizeColorSpace(false);
}