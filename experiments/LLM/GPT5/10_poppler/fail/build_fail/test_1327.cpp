#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PSOutputDev.h"

class PSOutputDevTest_1327 : public ::testing::Test {
protected:
    PSOutputDev *psOutputDev;

    void SetUp() override {
        // Assuming a constructor and necessary setup for PSOutputDev, adjust as per actual constructor
        psOutputDev = new PSOutputDev("dummyFileName", nullptr, nullptr, 1, PSOutMode::psOutMode, 100, 100, false, false, 0, 0, 0, 0, PSForceRasterize::None, true, nullptr, nullptr, PSLevel::psLevel1);
    }

    void TearDown() override {
        delete psOutputDev;
    }
};

TEST_F(PSOutputDevTest_1327, SetAndGetEmbedCIDPostScript_1327) {
    // Test normal behavior for setting and getting embedCIDPostScript flag
    psOutputDev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(psOutputDev->getEmbedCIDPostScript());
    
    psOutputDev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(psOutputDev->getEmbedCIDPostScript());
}

TEST_F(PSOutputDevTest_1327, SetEmbedCIDPostScriptWithInvalidValue_1327) {
    // Test exceptional case for setting invalid embedCIDPostScript value (e.g., invalid type, etc.)
    // Assuming a setter accepts only boolean, this test ensures proper handling of the setter
    // PSOutputDev::setEmbedCIDPostScript doesn't throw, it sets values so we are testing state change
    psOutputDev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(psOutputDev->getEmbedCIDPostScript());
    psOutputDev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(psOutputDev->getEmbedCIDPostScript());
}

TEST_F(PSOutputDevTest_1327, SetEmbedCIDPostScriptTwice_1327) {
    // Test for setting embedCIDPostScript multiple times
    psOutputDev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(psOutputDev->getEmbedCIDPostScript());
    psOutputDev->setEmbedCIDPostScript(true); // Redundant set
    EXPECT_TRUE(psOutputDev->getEmbedCIDPostScript());
    
    psOutputDev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(psOutputDev->getEmbedCIDPostScript());
}

TEST_F(PSOutputDevTest_1327, CheckEmbedCIDPostScriptStateAfterMultipleOperations_1327) {
    // Check that setting and getting embedCIDPostScript behaves correctly across multiple operations
    psOutputDev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(psOutputDev->getEmbedCIDPostScript());

    psOutputDev->setEmbedCIDPostScript(false);
    EXPECT_FALSE(psOutputDev->getEmbedCIDPostScript());

    psOutputDev->setEmbedCIDPostScript(true);
    EXPECT_TRUE(psOutputDev->getEmbedCIDPostScript());
}