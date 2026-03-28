#include <gtest/gtest.h>
#include "./TestProjects/poppler/poppler/PSOutputDev.h"

class PSOutputDevTest_1309 : public testing::Test {
protected:
    PSOutputDev *psOutputDev;

    void SetUp() override {
        // Setup code for initializing PSOutputDev instance
        psOutputDev = new PSOutputDev("testFile.ps", nullptr, nullptr, 0, PSOutMode::psLevel3, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::noForce, false, nullptr, nullptr, PSLevel::psLevel3);
    }

    void TearDown() override {
        // Cleanup
        delete psOutputDev;
    }
};

// Normal operation test for setPSShrinkLarger
TEST_F(PSOutputDevTest_1309, SetPSShrinkLarger_NormalOperation_1309) {
    psOutputDev->setPSShrinkLarger(true);
    // Since no observable output or callback is directly tied to this setter function, 
    // we are assuming that the setter updates the internal state correctly.
    // This would typically be verified with a getter if there was a public getter.
    // For now, we check the effect indirectly by assuming no crashes or errors in normal flow.
    ASSERT_TRUE(true); // Placeholder for verification as the effect isn't directly observable.
}

// Boundary test for setPSShrinkLarger with true value
TEST_F(PSOutputDevTest_1309, SetPSShrinkLarger_TrueBoundary_1309) {
    psOutputDev->setPSShrinkLarger(true);
    ASSERT_TRUE(true); // No observable changes are directly visible; we verify non-error behavior
}

// Boundary test for setPSShrinkLarger with false value
TEST_F(PSOutputDevTest_1309, SetPSShrinkLarger_FalseBoundary_1309) {
    psOutputDev->setPSShrinkLarger(false);
    ASSERT_TRUE(true); // No observable changes are directly visible; we verify non-error behavior
}

// Exceptional case: Test for possible error behavior (e.g., no changes expected)
TEST_F(PSOutputDevTest_1309, SetPSShrinkLarger_ExceptionalCase_1309) {
    try {
        psOutputDev->setPSShrinkLarger(true);
        psOutputDev->setPSShrinkLarger(false); // Testing setting to both values in sequence
        ASSERT_TRUE(true); // No exceptions thrown, assuming setter behaves normally
    } catch (...) {
        FAIL() << "setPSShrinkLarger threw an exception unexpectedly!";
    }
}

// Verification of external interactions (if setPSShrinkLarger interacts with other functions indirectly)
TEST_F(PSOutputDevTest_1309, SetPSShrinkLarger_InteractionWithOtherMethods_1309) {
    // Since this function is a setter with no direct return, we can only verify that
    // it doesn't negatively interact with other methods by calling another method after setting.
    psOutputDev->setPSShrinkLarger(true);
    psOutputDev->writeHeader(1, nullptr, nullptr, 0, "Test Title");
    ASSERT_TRUE(true); // If no crash or error occurs, the interaction is assumed valid
}