#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"

// Mock external callback function signatures for the test
void mockUnderlayCbk(PSOutputDev* psOut, void* data) {}
void mockOverlayCbk(PSOutputDev* psOut, void* data) {}

class PSOutputDevTest_1294 : public ::testing::Test {
protected:
    PSOutputDevTest_1294() {
        // Setup code for initializing the PSOutputDev object, if needed
    }
};

// Test for the 'useDrawChar' method (Test ID: 1294)
TEST_F(PSOutputDevTest_1294, UseDrawChar_1294) {
    PSOutputDev psOut("test.ps", nullptr, "Test Title", 1, PSOutMode::text, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level2);
    EXPECT_FALSE(psOut.useDrawChar());
}

// Test for boundary condition: an empty paper size (Test ID: 1295)
TEST_F(PSOutputDevTest_1294, PaperSize_Empty_1295) {
    PSOutputDev psOut("test.ps", nullptr, "Test Title", 1, PSOutMode::text, 0, 0, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level2);
    // Check if it handles the zero-size paper correctly
    EXPECT_EQ(psOut.paperWidth, 0);
    EXPECT_EQ(psOut.paperHeight, 0);
}

// Test for boundary condition: maximum paper size (Test ID: 1296)
TEST_F(PSOutputDevTest_1294, PaperSize_Maximum_1296) {
    PSOutputDev psOut("test.ps", nullptr, "Test Title", 1, PSOutMode::text, INT_MAX, INT_MAX, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level2);
    // Check if the maximum values are correctly handled
    EXPECT_EQ(psOut.paperWidth, INT_MAX);
    EXPECT_EQ(psOut.paperHeight, INT_MAX);
}

// Test for 'setOffset' method (Test ID: 1297)
TEST_F(PSOutputDevTest_1294, SetOffset_1297) {
    PSOutputDev psOut("test.ps", nullptr, "Test Title", 1, PSOutMode::text, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level2);
    psOut.setOffset(10.0, 20.0);
    // Check if the offset was set correctly (Note: actual getter for offset may need to be added in the class for validation)
    EXPECT_DOUBLE_EQ(psOut.tx, 10.0);
    EXPECT_DOUBLE_EQ(psOut.ty, 20.0);
}

// Test for callback functions (Test ID: 1298)
TEST_F(PSOutputDevTest_1294, SetUnderlayCbk_1298) {
    PSOutputDev psOut("test.ps", nullptr, "Test Title", 1, PSOutMode::text, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level2);
    psOut.setUnderlayCbk(mockUnderlayCbk, nullptr);
    // Check if the callback function pointer is set correctly
    // (This requires that the class allows you to test this behavior, perhaps by calling the callback)
}

// Test for 'isOk' method, boundary condition (Test ID: 1299)
TEST_F(PSOutputDevTest_1294, IsOk_1299) {
    PSOutputDev psOut("test.ps", nullptr, "Test Title", 1, PSOutMode::text, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level2);
    EXPECT_TRUE(psOut.isOk()); // Assuming that 'isOk' should return true by default for a well-formed PSOutputDev object
}

// Test for 'useShadedFills' method with valid type (Test ID: 1300)
TEST_F(PSOutputDevTest_1294, UseShadedFills_ValidType_1300) {
    PSOutputDev psOut("test.ps", nullptr, "Test Title", 1, PSOutMode::text, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level2);
    EXPECT_TRUE(psOut.useShadedFills(1)); // Assuming 1 is a valid type
}

// Test for 'useShadedFills' method with invalid type (Test ID: 1301)
TEST_F(PSOutputDevTest_1294, UseShadedFills_InvalidType_1301) {
    PSOutputDev psOut("test.ps", nullptr, "Test Title", 1, PSOutMode::text, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level2);
    EXPECT_FALSE(psOut.useShadedFills(-1)); // Assuming -1 is an invalid type
}

// Test for 'checkPageSlice' method, boundary condition (Test ID: 1302)
TEST_F(PSOutputDevTest_1294, CheckPageSlice_Boundary_1302) {
    PSOutputDev psOut("test.ps", nullptr, "Test Title", 1, PSOutMode::text, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level2);
    Page* page = nullptr; // Mock or create a dummy Page object
    EXPECT_FALSE(psOut.checkPageSlice(page, 300.0, 300.0, 0, true, true, 0, 0, 0, 0, false, nullptr, nullptr, nullptr, nullptr)); // Expect false for the default case
}

// Test for 'startPage' and 'endPage' methods (Test ID: 1303)
TEST_F(PSOutputDevTest_1294, StartEndPage_1303) {
    PSOutputDev psOut("test.ps", nullptr, "Test Title", 1, PSOutMode::text, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::no, false, nullptr, nullptr, PSLevel::level2);
    psOut.startPage(1, nullptr, nullptr); // Mocked state and xref objects
    EXPECT_NO_THROW(psOut.endPage()); // Should not throw any exception
}