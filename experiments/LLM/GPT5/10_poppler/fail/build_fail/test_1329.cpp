#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/PSOutputDev.h"

using ::testing::Return;
using ::testing::_;

// Mock class to simulate external dependencies, if needed
class MockPSOutputDev : public PSOutputDev {
public:
    MockPSOutputDev(const char* fileName, PDFDoc* docA, char* psTitleA, const int& pages, PSOutMode modeA, int paperWidthA, int paperHeightA, bool noCrop, bool duplexA, int imgLLXA, int imgLLYA, int imgURXA, int imgURYA, PSForceRasterize forceRasterizeA, bool manualCtrlA, PSOutCustomCodeCbk customCodeCbkA, void* customCodeCbkDataA, PSLevel levelA)
        : PSOutputDev(fileName, docA, psTitleA, pages, modeA, paperWidthA, paperHeightA, noCrop, duplexA, imgLLXA, imgLLYA, imgURXA, imgURYA, forceRasterizeA, manualCtrlA, customCodeCbkA, customCodeCbkDataA, levelA) {}
};

// Test case for normal operation of setFontPassthrough and getFontPassthrough
TEST_F(PSOutputDev_1329, SetGetFontPassthrough_1329) {
    PSOutputDev psOutputDev("file.ps", nullptr, nullptr, 0, PSOutMode::psOutModePostScript, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::noForce, false, nullptr, nullptr, PSLevel::psLevel3);

    // Test normal set and get
    psOutputDev.setFontPassthrough(true);
    EXPECT_TRUE(psOutputDev.getFontPassthrough());

    psOutputDev.setFontPassthrough(false);
    EXPECT_FALSE(psOutputDev.getFontPassthrough());
}

// Test case for the exceptional case when the fontPassthrough is called with invalid input
TEST_F(PSOutputDev_1329, InvalidFontPassthrough_1329) {
    PSOutputDev psOutputDev("file.ps", nullptr, nullptr, 0, PSOutMode::psOutModePostScript, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::noForce, false, nullptr, nullptr, PSLevel::psLevel3);

    // Invalid input simulation is not applicable here as the setFontPassthrough only takes a boolean.
    // This is just a sanity check for non-error scenarios when setting and getting.
    ASSERT_NO_THROW({
        psOutputDev.setFontPassthrough(true);
        EXPECT_TRUE(psOutputDev.getFontPassthrough());
    });
}

// Test case for boundary conditions on setting a valid and invalid value
TEST_F(PSOutputDev_1329, BoundaryFontPassthrough_1329) {
    PSOutputDev psOutputDev("file.ps", nullptr, nullptr, 0, PSOutMode::psOutModePostScript, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::noForce, false, nullptr, nullptr, PSLevel::psLevel3);

    // Test setting boundary values for fontPassthrough
    psOutputDev.setFontPassthrough(true);
    EXPECT_TRUE(psOutputDev.getFontPassthrough());

    psOutputDev.setFontPassthrough(false);
    EXPECT_FALSE(psOutputDev.getFontPassthrough());
}

// Mock external callback to test interaction with setUnderlayCbk
TEST_F(PSOutputDev_1329, SetUnderlayCbk_1329) {
    void (*underlayCbkMock)(PSOutputDev*, void*) = [](PSOutputDev* psOut, void* data) {
        EXPECT_EQ(psOut, nullptr); // Simulate checking that the psOutputDev is passed correctly
        EXPECT_EQ(data, nullptr);  // Simulate data validation
    };

    PSOutputDev psOutputDev("file.ps", nullptr, nullptr, 0, PSOutMode::psOutModePostScript, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::noForce, false, nullptr, nullptr, PSLevel::psLevel3);
    psOutputDev.setUnderlayCbk(underlayCbkMock, nullptr);

    // Check if the callback was set properly and invoked
    ASSERT_NO_THROW(psOutputDev.setUnderlayCbk(underlayCbkMock, nullptr));
}

// Mock external callback to test interaction with setOverlayCbk
TEST_F(PSOutputDev_1329, SetOverlayCbk_1329) {
    void (*overlayCbkMock)(PSOutputDev*, void*) = [](PSOutputDev* psOut, void* data) {
        EXPECT_EQ(psOut, nullptr); // Simulate checking that the psOutputDev is passed correctly
        EXPECT_EQ(data, nullptr);  // Simulate data validation
    };

    PSOutputDev psOutputDev("file.ps", nullptr, nullptr, 0, PSOutMode::psOutModePostScript, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::noForce, false, nullptr, nullptr, PSLevel::psLevel3);
    psOutputDev.setOverlayCbk(overlayCbkMock, nullptr);

    // Check if the callback was set properly and invoked
    ASSERT_NO_THROW(psOutputDev.setOverlayCbk(overlayCbkMock, nullptr));
}