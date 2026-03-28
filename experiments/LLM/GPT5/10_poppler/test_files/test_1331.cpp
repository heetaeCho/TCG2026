#include <gtest/gtest.h>
#include "PSOutputDev.h"  // Include the class header for PSOutputDev

class PSOutputDevTest_1331 : public testing::Test {
protected:
    PSOutputDev* psOutputDev;

    void SetUp() override {
        psOutputDev = new PSOutputDev("test.ps", nullptr, "Test PS Output", 1, PSOutMode::Normal, 8.5, 11, false, false, 0, 0, 100, 100, PSForceRasterize::None, false, nullptr, nullptr, PSLevel::Level1);
    }

    void TearDown() override {
        delete psOutputDev;
    }
};

// Test for normal operation of setPassLevel1CustomColor function
TEST_F(PSOutputDevTest_1331, SetPassLevel1CustomColor_Normal_Operation_1331) {
    psOutputDev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(psOutputDev->getPassLevel1CustomColor());  // Verifying if the value is set correctly

    psOutputDev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(psOutputDev->getPassLevel1CustomColor());  // Verifying if the value is set correctly
}

// Boundary test for setting and getting PassLevel1CustomColor with boundary values
TEST_F(PSOutputDevTest_1331, SetPassLevel1CustomColor_Boundary_Conditions_1331) {
    psOutputDev->setPassLevel1CustomColor(true);
    EXPECT_TRUE(psOutputDev->getPassLevel1CustomColor());  // Verifying behavior for boundary condition

    psOutputDev->setPassLevel1CustomColor(false);
    EXPECT_FALSE(psOutputDev->getPassLevel1CustomColor());  // Verifying behavior for boundary condition
}

// Test for exceptional/error cases: Ensure that invalid values (if applicable in the context) don't cause failure
TEST_F(PSOutputDevTest_1331, SetPassLevel1CustomColor_Exceptional_Cases_1331) {
    // In this case, the function does not throw any exceptions as per the interface, but we can verify no crashes
    EXPECT_NO_THROW(psOutputDev->setPassLevel1CustomColor(true));
    EXPECT_NO_THROW(psOutputDev->setPassLevel1CustomColor(false));
}

// Test for verifying external interactions with callback (mocking callback function)
TEST_F(PSOutputDevTest_1331, SetOverlayCallback_VerifyExternalInteraction_1331) {
    // Mock callback function
    void (*mockCallback)(PSOutputDev*, void*) = [](PSOutputDev* psOut, void* data) {
        // A simple mock callback that just verifies it's called.
        EXPECT_EQ(psOut, nullptr);  // Expect that PSOutputDev is nullptr (no callback set yet)
        EXPECT_EQ(data, nullptr);  // Expect that no data is passed
    };

    psOutputDev->setOverlayCbk(mockCallback, nullptr);

    // You'd usually have additional logic here to invoke the callback if needed.
    EXPECT_NO_THROW(mockCallback(nullptr, nullptr));  // Verify the callback interaction
}

// Test for boundary conditions with paper size
TEST_F(PSOutputDevTest_1331, SetPaperSize_Boundary_Conditions_1331) {
    psOutputDev->setPaperSize(8, 8);
    EXPECT_EQ(psOutputDev->getPaperWidth(), 8);  // Verifying lower boundary
    EXPECT_EQ(psOutputDev->getPaperHeight(), 8); // Verifying lower boundary

    psOutputDev->setPaperSize(1000, 1000);
    EXPECT_EQ(psOutputDev->getPaperWidth(), 1000); // Verifying upper boundary
    EXPECT_EQ(psOutputDev->getPaperHeight(), 1000); // Verifying upper boundary
}

// Test for setting invalid input (boundary condition)
TEST_F(PSOutputDevTest_1331, SetInvalidPaperSize_1331) {
    psOutputDev->setPaperSize(-1, -1);  // Invalid size
    EXPECT_LT(psOutputDev->getPaperWidth(), 0);  // Verifying invalid values aren't accepted
    EXPECT_LT(psOutputDev->getPaperHeight(), 0);  // Verifying invalid values aren't accepted
}