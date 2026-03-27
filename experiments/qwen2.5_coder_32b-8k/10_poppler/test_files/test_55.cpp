#include <gtest/gtest.h>

#include "SignatureInfo.h"



class SignatureInfoTest_55 : public ::testing::Test {

protected:

    SignatureInfo* signatureInfo;



    void SetUp() override {

        signatureInfo = new SignatureInfo();

    }



    void TearDown() override {

        delete signatureInfo;

    }

};



TEST_F(SignatureInfoTest_55, SetSubFilterSupport_DefaultValue_55) {

    EXPECT_EQ(signatureInfo->isSubfilterSupported(), false);

}



TEST_F(SignatureInfoTest_55, SetSubFilterSupport_Enable_55) {

    signatureInfo->setSubFilterSupport(true);

    EXPECT_EQ(signatureInfo->isSubfilterSupported(), true);

}



TEST_F(SignatureInfoTest_55, SetSubFilterSupport_Disable_55) {

    signatureInfo->setSubFilterSupport(false);

    EXPECT_EQ(signatureInfo->isSubfilterSupported(), false);

}



TEST_F(SignatureInfoTest_55, SetSubFilterSupport_ToggleMultipleTimes_55) {

    signatureInfo->setSubFilterSupport(true);

    EXPECT_EQ(signatureInfo->isSubfilterSupported(), true);



    signatureInfo->setSubFilterSupport(false);

    EXPECT_EQ(signatureInfo->isSubfilterSupported(), false);



    signatureInfo->setSubFilterSupport(true);

    EXPECT_EQ(signatureInfo->isSubfilterSupported(), true);

}
