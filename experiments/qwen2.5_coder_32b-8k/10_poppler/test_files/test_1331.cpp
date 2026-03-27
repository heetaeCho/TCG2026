#include <gtest/gtest.h>

#include "PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    PSOutputDev* psOutputDev;



    virtual void SetUp() {

        // Assuming a minimal constructor for demonstration purposes.

        // Replace with actual constructor if available.

        psOutputDev = new PSOutputDev(nullptr, nullptr, nullptr, std::vector<int>(), 0, 0, 0, false, false, 0, 0, 0, 0, PSForceRasterize::always, false, nullptr, nullptr, PSLevel::level2);

    }



    virtual void TearDown() {

        delete psOutputDev;

    }

};



TEST_F(PSOutputDevTest_SetPassLevel1CustomColor_Negative_1331, SetPassLevel1CustomColorFalse_1331) {

    psOutputDev->setPassLevel1CustomColor(false);

    EXPECT_FALSE(psOutputDev->getPassLevel1CustomColor());

}



TEST_F(PSOutputDevTest_SetPassLevel1CustomColor_Positive_1331, SetPassLevel1CustomColorTrue_1331) {

    psOutputDev->setPassLevel1CustomColor(true);

    EXPECT_TRUE(psOutputDev->getPassLevel1CustomColor());

}
