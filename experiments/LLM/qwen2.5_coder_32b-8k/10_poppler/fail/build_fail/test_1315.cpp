#include <gtest/gtest.h>

#include "PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Initialize the PSOutputDev with some default values for testing.

        // Since we are treating this as a black box, we assume these parameters are valid.

        psOutputDev = new PSOutputDev("output.ps", nullptr, "testTitle", 1, psOutModeBinary,

                                      612, 792, false, false, 0, 0, 0, 0, forceRasterizeAuto,

                                      false, nullptr, nullptr, psLevel2);

    }



    virtual void TearDown() {

        delete psOutputDev;

    }



    PSOutputDev* psOutputDev;

};



TEST_F(PSOutputDevTest_SetUncompressPreloadedImages_1315, DefaultStateFalse_1315) {

    EXPECT_FALSE(psOutputDev->getEmbedType1());

}



TEST_F(PSOutputDevTest_SetUncompressPreloadedImages_1315, SetTrueAndGetTrue_1315) {

    psOutputDev->setUncompressPreloadedImages(true);

    EXPECT_TRUE(psOutputDev->getEmbedType1()); // Assuming getEmbedType1 is tied to the flag we're testing.

}



TEST_F(PSOutputDevTest_SetUncompressPreloadedImages_1315, SetFalseAndGetFalse_1315) {

    psOutputDev->setUncompressPreloadedImages(false);

    EXPECT_FALSE(psOutputDev->getEmbedType1()); // Assuming getEmbedType1 is tied to the flag we're testing.

}



TEST_F(PSOutputDevTest_SetUncompressPreloadedImages_1315, ToggleMultipleTimes_1315) {

    psOutputDev->setUncompressPreloadedImages(true);

    EXPECT_TRUE(psOutputDev->getEmbedType1());

    psOutputDev->setUncompressPreloadedImages(false);

    EXPECT_FALSE(psOutputDev->getEmbedType1());

    psOutputDev->setUncompressPreloadedImages(true);

    EXPECT_TRUE(psOutputDev->getEmbedType1());

}
