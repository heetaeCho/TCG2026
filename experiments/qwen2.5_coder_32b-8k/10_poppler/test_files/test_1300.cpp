#include <gtest/gtest.h>

#include "PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    PSOutputDev* psOutputDev;



    void SetUp() override {

        // Assuming a dummy implementation for PDFDoc and other parameters is available

        // Here we use nullptr as placeholders since actual construction is not allowed.

        psOutputDev = new PSOutputDev(nullptr, nullptr, nullptr, 0, (PSOutMode)0, 0, 0, false, false, 0, 0, 0, 0, (PSForceRasterize)0, false, nullptr, nullptr, (PSLevel)0);

    }



    void TearDown() override {

        delete psOutputDev;

    }

};



TEST_F(PSOutputDevTest_1300, SetOffset_SetsCorrectValues_1300) {

    double x = 5.5;

    double y = -2.3;



    psOutputDev->setOffset(x, y);



    // Assuming there's a way to verify the offset values, e.g., through a getter or indirect effect

    EXPECT_EQ(psOutputDev->tx0, x);

    EXPECT_EQ(psOutputDev->ty0, y);

}



TEST_F(PSOutputDevTest_1300, SetOffset_ZeroValues_1300) {

    double x = 0.0;

    double y = 0.0;



    psOutputDev->setOffset(x, y);



    EXPECT_EQ(psOutputDev->tx0, x);

    EXPECT_EQ(psOutputDev->ty0, y);

}



TEST_F(PSOutputDevTest_1300, SetOffset_NegativeValues_1300) {

    double x = -10.5;

    double y = -20.5;



    psOutputDev->setOffset(x, y);



    EXPECT_EQ(psOutputDev->tx0, x);

    EXPECT_EQ(psOutputDev->ty0, y);

}



TEST_F(PSOutputDevTest_1300, SetOffset_PositiveLargeValues_1300) {

    double x = 1e6;

    double y = 2e6;



    psOutputDev->setOffset(x, y);



    EXPECT_EQ(psOutputDev->tx0, x);

    EXPECT_EQ(psOutputDev->ty0, y);

}



TEST_F(PSOutputDevTest_1300, SetOffset_NegativeLargeValues_1300) {

    double x = -1e6;

    double y = -2e6;



    psOutputDev->setOffset(x, y);



    EXPECT_EQ(psOutputDev->tx0, x);

    EXPECT_EQ(psOutputDev->ty0, y);

}
