#include <gtest/gtest.h>

#include "PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    PSOutputDev* psOutputDev;



    virtual void SetUp() {

        // Mocking a constructor call with dummy parameters as the actual constructor is not provided.

        psOutputDev = new PSOutputDev("dummy_file", nullptr, nullptr, 1, 0, 612, 792, false, false, 0, 0, 612, 792, PSForceRasterize::none, false, nullptr, nullptr, psLevel1);

    }



    virtual void TearDown() {

        delete psOutputDev;

    }

};



TEST_F(PSOutputDevTest_1329, SetFontPassthroughTrue_1329) {

    psOutputDev->setFontPassthrough(true);

    EXPECT_TRUE(psOutputDev->getFontPassthrough());

}



TEST_F(PSOutputDevTest_1329, SetFontPassthroughFalse_1329) {

    psOutputDev->setFontPassthrough(false);

    EXPECT_FALSE(psOutputDev->getFontPassthrough());

}



TEST_F(PSOutputDevTest_1329, DefaultFontPassthroughValue_1329) {

    // Assuming default value is false based on typical behavior of boolean flags.

    EXPECT_FALSE(psOutputDev->getFontPassthrough());

}
