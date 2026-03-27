#include <gtest/gtest.h>

#include "PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    std::unique_ptr<PSOutputDev> psOutputDev;



    void SetUp() override {

        // Minimal initialization for the test cases.

        // Note: Actual construction requires parameters that we assume are not necessary for testing setEmbedCIDTrueType.

        psOutputDev = std::make_unique<PSOutputDev>(nullptr, nullptr, nullptr, 0, PSOutMode(), 0, 0, false, false, 0, 0, 0, 0,

                                                   PSForceRasterize(), false, nullptr, nullptr, PSLevel());

    }

};



TEST_F(PSOutputDevTest_1328, SetEmbedCIDTrueType_DefaultValueFalse_1328) {

    EXPECT_FALSE(psOutputDev->getEmbedCIDTrueType());

}



TEST_F(PSOutputDevTest_1328, SetEmbedCIDTrueType_SetToTrue_ReturnsTrue_1328) {

    psOutputDev->setEmbedCIDTrueType(true);

    EXPECT_TRUE(psOutputDev->getEmbedCIDTrueType());

}



TEST_F(PSOutputDevTest_1328, SetEmbedCIDTrueType_SetToFalse_ReturnsFalse_1328) {

    psOutputDev->setEmbedCIDTrueType(false);

    EXPECT_FALSE(psOutputDev->getEmbedCIDTrueType());

}



TEST_F(PSOutputDevTest_1328, SetEmbedCIDTrueType_ToggleMultipleTimes_ConsistentState_1328) {

    psOutputDev->setEmbedCIDTrueType(true);

    EXPECT_TRUE(psOutputDev->getEmbedCIDTrueType());



    psOutputDev->setEmbedCIDTrueType(false);

    EXPECT_FALSE(psOutputDev->getEmbedCIDTrueType());



    psOutputDev->setEmbedCIDTrueType(true);

    EXPECT_TRUE(psOutputDev->getEmbedCIDTrueType());

}
