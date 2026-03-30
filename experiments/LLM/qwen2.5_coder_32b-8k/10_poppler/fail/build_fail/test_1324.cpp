#include <gtest/gtest.h>

#include "PSOutputDev.h"



class PSOutputDevTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize PSOutputDev with default parameters for testing.

        doc = new PDFDoc("dummy.pdf");

        psOutputDev = new PSOutputDev("output.ps", doc, nullptr, 1, psOutModeNormal, 500, 600, false, false, 0, 0, 500, 600, psForceRasterizeNone, false, nullptr, nullptr, psLevel2);

    }



    void TearDown() override {

        delete psOutputDev;

        delete doc;

    }



    PSOutputDev* psOutputDev;

    PDFDoc* doc;

};



TEST_F(PSOutputDevTest_1324, GetEnableFlate_ReturnsFalseByDefault_1324) {

    EXPECT_FALSE(psOutputDev->getEnableFlate());

}



TEST_F(PSOutputDevTest_1324, SetEnableFlate_TogglesValueCorrectly_1324) {

    psOutputDev->setEnableFlate(true);

    EXPECT_TRUE(psOutputDev->getEnableFlate());



    psOutputDev->setEnableFlate(false);

    EXPECT_FALSE(psOutputDev->getEnableFlate());

}



TEST_F(PSOutputDevTest_1324, SetEnableFlate_IdempotentBehavior_1324) {

    psOutputDev->setEnableFlate(true);

    psOutputDev->setEnableFlate(true);

    EXPECT_TRUE(psOutputDev->getEnableFlate());



    psOutputDev->setEnableFlate(false);

    psOutputDev->setEnableFlate(false);

    EXPECT_FALSE(psOutputDev->getEnableFlate());

}



TEST_F(PSOutputDevTest_1324, SetEnableFlate_DoesNotAffectOtherSettings_1324) {

    psOutputDev->setEmbedType1(true);

    psOutputDev->setEnableFlate(true);



    EXPECT_TRUE(psOutputDev->getEnableFlate());

    EXPECT_TRUE(psOutputDev->getEmbedType1());



    psOutputDev->setEnableFlate(false);

    EXPECT_FALSE(psOutputDev->getEnableFlate());

    EXPECT_TRUE(psOutputDev->getEmbedType1());

}



TEST_F(PSOutputDevTest_1324, SetAndGetMethodConsistency_1324) {

    for (bool value : {true, false}) {

        psOutputDev->setEnableFlate(value);

        EXPECT_EQ(psOutputDev->getEnableFlate(), value);

    }

}
