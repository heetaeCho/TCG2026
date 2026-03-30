#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    PSOutputDev* psOutputDev;



    void SetUp() override {

        // Assuming a dummy constructor for the sake of setting up the test object

        psOutputDev = new PSOutputDev(nullptr, nullptr, nullptr, std::vector<int>(), PSOutMode::PSModeEPS, 0, 0, false, false, 0, 0, 0, 0, PSForceRasterize::PSDoNotRasterize, false, nullptr, nullptr, PSLevel::level1);

    }



    void TearDown() override {

        delete psOutputDev;

    }

};



TEST_F(PSOutputDevTest_1302, SetRotate_DefaultValue_1302) {

    EXPECT_EQ(psOutputDev->rotate0, 0); // Assuming default value is set to 0

}



TEST_F(PSOutputDevTest_1302, SetRotate_PositiveRotation_1302) {

    psOutputDev->setRotate(90);

    EXPECT_EQ(psOutputDev->rotate0, 90);

}



TEST_F(PSOutputDevTest_1302, SetRotate_ZeroRotation_1302) {

    psOutputDev->setRotate(0);

    EXPECT_EQ(psOutputDev->rotate0, 0);

}



TEST_F(PSOutputDevTest_1302, SetRotate_NegativeRotation_1302) {

    psOutputDev->setRotate(-90);

    EXPECT_EQ(psOutputDev->rotate0, -90);

}



TEST_F(PSOutputDevTest_1302, SetRotate_BoundaryConditionMax_1302) {

    psOutputDev->setRotate(360);

    EXPECT_EQ(psOutputDev->rotate0, 360);

}



TEST_F(PSOutputDevTest_1302, SetRotate_BoundaryConditionMin_1302) {

    psOutputDev->setRotate(-360);

    EXPECT_EQ(psOutputDev->rotate0, -360);

}
