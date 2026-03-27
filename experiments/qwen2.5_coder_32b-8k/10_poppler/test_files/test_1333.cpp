#include <gtest/gtest.h>

#include "poppler/PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize PSOutputDev with dummy values as required by constructors

        psOut = new PSOutputDev("dummy.ps", nullptr, const_cast<char*>("Title"), std::vector<int>{1}, 

                                static_cast<PSOutMode>(0), 800, 600, false, false, 

                                0, 0, 800, 600, PSForceRasterize::always, false, nullptr, nullptr, static_cast<PSLevel>(3));

    }



    void TearDown() override {

        delete psOut;

    }



    PSOutputDev* psOut;

};



TEST_F(PSOutputDevTest_1333, SetGenerateOPITrue_1333) {

    // Test setting generateOPI to true

    psOut->setGenerateOPI(true);

    EXPECT_TRUE(psOut->generateOPI);

}



TEST_F(PSOutputDevTest_1333, SetGenerateOPIFalse_1333) {

    // Test setting generateOPI to false

    psOut->setGenerateOPI(false);

    EXPECT_FALSE(psOut->generateOPI);

}
