#include <gtest/gtest.h>

#include "PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    PSOutputDev* psOutputDev;



    virtual void SetUp() {

        // Assuming a default constructor or mock-up for testing purposes.

        // Since the constructors require parameters, we would need to create mocks or use a specific setup.

        // For simplicity, let's assume there's a way to initialize with default values in tests.

        psOutputDev = new PSOutputDev(/* parameters */);

    }



    virtual void TearDown() {

        delete psOutputDev;

    }

};



TEST_F(PSOutputDevTest_1317, GetEmbedTrueType_DefaultValue_1317) {

    EXPECT_FALSE(psOutputDev->getEmbedTrueType());

}



TEST_F(PSOutputDevTest_1317, SetEmbedTrueType_ToggleOnOff_1317) {

    psOutputDev->setEmbedTrueType(true);

    EXPECT_TRUE(psOutputDev->getEmbedTrueType());



    psOutputDev->setEmbedTrueType(false);

    EXPECT_FALSE(psOutputDev->getEmbedTrueType());

}



TEST_F(PSOutputDevTest_1317, SetEmbedTrueType_MultipleSetCalls_1317) {

    psOutputDev->setEmbedTrueType(true);

    psOutputDev->setEmbedTrueType(true);

    EXPECT_TRUE(psOutputDev->getEmbedTrueType());



    psOutputDev->setEmbedTrueType(false);

    psOutputDev->setEmbedTrueType(false);

    EXPECT_FALSE(psOutputDev->getEmbedTrueType());

}
