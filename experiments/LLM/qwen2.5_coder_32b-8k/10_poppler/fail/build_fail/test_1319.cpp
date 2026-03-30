#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    PSOutputDev* psOutputDev;



    virtual void SetUp() {

        // Assuming a default constructor or mockable setup for testing purposes.

        // Since actual constructors require parameters, we will use pointers and mocks if necessary.

        // For this test, we'll assume a way to instantiate the class is available.

        psOutputDev = new PSOutputDev(nullptr, nullptr, nullptr, std::vector<int>(), (PSOutMode)0, 0, 0, false, false, 0, 0, 0, 0, (PSForceRasterize)0, false, nullptr, nullptr, (PSLevel)0);

    }



    virtual void TearDown() {

        delete psOutputDev;

    }

};



TEST_F(PSOutputDevTest_1319, GetEmbedCIDTrueType_DefaultValue_1319) {

    EXPECT_FALSE(psOutputDev->getEmbedCIDTrueType());

}



TEST_F(PSOutputDevTest_1319, SetAndGetEmbedCIDTrueType_1319) {

    psOutputDev->setEmbedCIDTrueType(true);

    EXPECT_TRUE(psOutputDev->getEmbedCIDTrueType());



    psOutputDev->setEmbedCIDTrueType(false);

    EXPECT_FALSE(psOutputDev->getEmbedCIDTrueType());

}
