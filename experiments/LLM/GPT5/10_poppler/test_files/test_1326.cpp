#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"

class PSOutputDevTest_1326 : public testing::Test {
protected:
    PSOutputDev *psOutputDev;

    void SetUp() override {
        psOutputDev = new PSOutputDev("test.ps", nullptr, "Test Title", 1, PSOutMode::ePSLevel2, 600, 800, false, false, 0, 0, 0, 0, PSForceRasterize::eNoRasterize, false, nullptr, nullptr, PSLevel::ePSLevel1);
    }

    void TearDown() override {
        delete psOutputDev;
    }
};

TEST_F(PSOutputDevTest_1326, SetEmbedTrueType_True_1326) {
    // Test for setting embedTrueType to true
    psOutputDev->setEmbedTrueType(true);
    ASSERT_TRUE(psOutputDev->getEmbedTrueType());
}

TEST_F(PSOutputDevTest_1326, SetEmbedTrueType_False_1326) {
    // Test for setting embedTrueType to false
    psOutputDev->setEmbedTrueType(false);
    ASSERT_FALSE(psOutputDev->getEmbedTrueType());
}

TEST_F(PSOutputDevTest_1326, SetEmbedTrueType_ExceptionalCase_1326) {
    // Test exceptional or error case, where an invalid value might be passed (simulated behavior).
    // Here we can assume that the setter will not accept non-bool values and won't throw in the given implementation.
    // The method setEmbedTrueType will not throw exceptions, but a check for an invalid setter could be tested like this:
    ASSERT_NO_THROW(psOutputDev->setEmbedTrueType(true));
    ASSERT_NO_THROW(psOutputDev->setEmbedTrueType(false));
}

TEST_F(PSOutputDevTest_1326, CheckInitialEmbedTrueType_1326) {
    // Verify the initial value of embedTrueType before calling setter
    ASSERT_FALSE(psOutputDev->getEmbedTrueType());  // assuming default value is false
}

TEST_F(PSOutputDevTest_1326, SetEmbedTrueTypeAfterOtherSetters_1326) {
    // Test that setting embedTrueType after other setters works as expected
    psOutputDev->setEmbedTrueType(true);
    psOutputDev->setEmbedCIDPostScript(true);
    ASSERT_TRUE(psOutputDev->getEmbedTrueType());
}

TEST_F(PSOutputDevTest_1326, SetEmbedTrueTypeAndVerifyExternalInteraction_1326) {
    // Mock external interaction, example: setting callbacks or validating external state changes (hypothetical in this case)
    // Since no callbacks are specified for embedTrueType, we only test state change here.
    psOutputDev->setEmbedTrueType(false);
    ASSERT_FALSE(psOutputDev->getEmbedTrueType());
}