#include <gtest/gtest.h>

#include "poppler/PSOutputDev.h"



class PSOutputDevTest_1309 : public ::testing::Test {

protected:

    PSOutputDev* psOutputDev;



    void SetUp() override {

        // Assuming a default constructor is available or mock dependencies if necessary.

        // Since no constructor parameters are provided, we assume a parameterless one exists for testing purposes.

        psOutputDev = new PSOutputDev();

    }



    void TearDown() override {

        delete psOutputDev;

    }

};



TEST_F(PSOutputDevTest_1309, SetPSShrinkLarger_DefaultValue_1309) {

    // Assuming the default value of psShrinkLarger is true

    EXPECT_EQ(true, psOutputDev->psShrinkLarger);

}



TEST_F(PSOutputDevTest_1309, SetPSShrinkLarger_SetToTrue_1309) {

    psOutputDev->setPSShrinkLarger(true);

    EXPECT_EQ(true, psOutputDev->psShrinkLarger);

}



TEST_F(PSOutputDevTest_1309, SetPSShrinkLarger_SetToFalse_1309) {

    psOutputDev->setPSShrinkLarger(false);

    EXPECT_EQ(false, psOutputDev->psShrinkLarger);

}



// Boundary conditions

TEST_F(PSOutputDevTest_1309, SetPSShrinkLarger_BoundaryTrue_1309) {

    psOutputDev->setPSShrinkLarger(true);

    EXPECT_TRUE(psOutputDev->psShrinkLarger);

}



TEST_F(PSOutputDevTest_1309, SetPSShrinkLarger_BoundaryFalse_1309) {

    psOutputDev->setPSShrinkLarger(false);

    EXPECT_FALSE(psOutputDev->psShrinkLarger);

}
