#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState *gfxState;



    void SetUp() override {

        gfxState = new GfxState(300, 300, nullptr, 0, false);

    }



    void TearDown() override {

        delete gfxState;

    }

};



TEST_F(GfxStateTest_653, SetRenderingIntent_DefaultValue_653) {

    const char* intent = "Default";

    gfxState->setRenderingIntent(intent);

    EXPECT_STREQ(gfxState->getRenderingIntent(), intent);

}



TEST_F(GfxStateTest_653, SetRenderingIntent_MaxLength_653) {

    const char* maxLengthIntent = "1234567890123456789012345678901";

    gfxState->setRenderingIntent(maxLengthIntent);

    EXPECT_STREQ(gfxState->getRenderingIntent(), maxLengthIntent);

}



TEST_F(GfxStateTest_653, SetRenderingIntent_ExceedMaxLength_Truncated_653) {

    const char* exceedMaxLengthIntent = "12345678901234567890123456789012";

    gfxState->setRenderingIntent(exceedMaxLengthIntent);

    EXPECT_STREQ(gfxState->getRenderingIntent(), "123456789012345678901234567890");

}



TEST_F(GfxStateTest_653, SetRenderingIntent_EmptyString_653) {

    const char* emptyIntent = "";

    gfxState->setRenderingIntent(emptyIntent);

    EXPECT_STREQ(gfxState->getRenderingIntent(), "");

}
